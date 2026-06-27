/*
 * tof_sensor.c
 * TOF400F 읽기 + 필터링 스레드
 *
 * 역할:
 *   50ms마다 TOF400F에서 거리를 읽고
 *   이동평균 + 칼만 필터로 D_rel, V_rel을 계산한 뒤
 *   g_tof (공유메모리)에 기록한다.
 *
 *   MPC 스레드는 g_tof를 읽어서 accsubsystem_step()에 넘긴다.
 */

#include "tof_sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <time.h>
#include <math.h>

/* ── 파라미터 ──────────────────────────────────────── */
#define SERIAL_PORT      "/dev/ttyS0"
#define BAUD_RATE        B115200
#define SLAVE_ADDR       0x01
#define SENSOR_PERIOD_MS 50
#define WINDOW_SIZE      5
#define DIST_MIN_M       0.02
#define DIST_MAX_M       4.0

/* ── 이동평균 ──────────────────────────────────────── */
typedef struct { double buf[WINDOW_SIZE]; int idx, count; } MovAvg;

static double mavg_push(MovAvg *m, double v)
{
    m->buf[m->idx] = v;
    m->idx = (m->idx + 1) % WINDOW_SIZE;
    if (m->count < WINDOW_SIZE) m->count++;
    double s = 0;
    for (int i = 0; i < m->count; i++) s += m->buf[i];
    return s / m->count;
}

/* ── 칼만 필터 ─────────────────────────────────────── */
typedef struct { double x, P, Q, R; } Kalman;

static double kalman_update(Kalman *k, double z)
{
    k->P += k->Q;
    double Kg = k->P / (k->P + k->R);
    k->x  += Kg * (z - k->x);
    k->P  *= (1.0 - Kg);
    return k->x;
}

/* ── 시간 ──────────────────────────────────────────── */
static long long now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

/* ── CRC-16/MODBUS ─────────────────────────────────── */
static uint16_t crc16(const uint8_t *d, size_t n)
{
    uint16_t c = 0xFFFF;
    for (size_t i = 0; i < n; i++) {
        c ^= d[i];
        for (int j = 0; j < 8; j++)
            c = (c & 1) ? (c >> 1) ^ 0xA001 : c >> 1;
    }
    return c;
}

/* ── UART 초기화 ───────────────────────────────────── */
static int serial_open(const char *port)
{
    int fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) { perror(port); return -1; }

    struct termios tty;
    memset(&tty, 0, sizeof tty);
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, BAUD_RATE);
    cfsetispeed(&tty, BAUD_RATE);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);
    tty.c_cflag |=  (CLOCAL | CREAD);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL | INLCR | IGNCR);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSANOW, &tty);
    tcflush(fd, TCIOFLUSH);
    return fd;
}

/* ── 정확히 n바이트 수신 ───────────────────────────── */
static int read_exact(int fd, uint8_t *buf, int n, int timeout_ms)
{
    int got = 0;
    long long dl = now_ms() + timeout_ms;
    while (got < n) {
        if (now_ms() > dl) return -1;
        ssize_t r = read(fd, buf + got, n - got);
        if (r > 0) got += (int)r;
        else usleep(500);
    }
    return got;
}

/* ── 거리 읽기 ─────────────────────────────────────── */
static const uint8_t READ_CMD[] = {0x01,0x03,0x00,0x10,0x00,0x01,0x85,0xCF};

static int read_distance_mm(int fd)
{
    tcflush(fd, TCIOFLUSH);
    if (write(fd, READ_CMD, sizeof READ_CMD) != (ssize_t)sizeof READ_CMD)
        return -1;

    uint8_t buf[7];
    if (read_exact(fd, buf, 7, 200) != 7) return -1;

    if (buf[0] != SLAVE_ADDR || buf[1] != 0x03 || buf[2] != 0x02) {
        tcflush(fd, TCIOFLUSH);
        return -1;
    }
    if (crc16(buf, 5) != ((uint16_t)(buf[6] << 8) | buf[5])) {
        tcflush(fd, TCIOFLUSH);
        return -1;
    }
    int dist = (buf[3] << 8) | buf[4];
    return (dist == 0xFFFF) ? -2 : dist;
}

/* ══════════════════════════════════════════════════════
 *  스레드 진입점
 * ══════════════════════════════════════════════════════ */
void *tof_sensor_thread(void *arg)
{
    (void)arg;

    int fd = serial_open(SERIAL_PORT);
    if (fd < 0) {
        fprintf(stderr, "[TOF] 포트 열기 실패 — ttyAMA0도 확인하세요\n");
        return NULL;
    }
    usleep(100000);          /* 센서 안정화 100ms */
    tcflush(fd, TCIOFLUSH);

    MovAvg mavg  = {0};
    Kalman kf    = { .x=0, .P=1.0, .Q=0.05, .R=0.01 };
    double prev_dist = -1.0;
    long long prev_t = 0;

    printf("[TOF] 센서 스레드 시작 (주기 %dms)\n", SENSOR_PERIOD_MS);

    while (atomic_load(&g_running)) {

        long long t_now = now_ms();
        int raw = read_distance_mm(fd);

        if (raw > 0) {
            double dist_m = raw / 1000.0;

            if (dist_m >= DIST_MIN_M && dist_m <= DIST_MAX_M) {

                /* 1. 이동평균으로 거리 스무딩 */
                double d_smooth = mavg_push(&mavg, dist_m);

                /* 2. 미분으로 상대속도 계산 */
                double v_raw = 0.0;
                if (prev_dist > 0 && prev_t > 0) {
                    double dt = (t_now - prev_t) / 1000.0;
                    if (dt > 0.001)
                        v_raw = (d_smooth - prev_dist) / dt;
                }

                /* 3. 칼만 필터로 속도 스무딩 */
                double v_filt = kalman_update(&kf, v_raw);

                /* 4. 공유메모리 write (잠금 최소화) */
                pthread_mutex_lock(&g_tof.lock);
                g_tof.d_rel     = d_smooth;
                g_tof.v_rel     = v_filt;
                g_tof.timestamp = t_now;
                g_tof.valid     = 1;
                pthread_mutex_unlock(&g_tof.lock);

                prev_dist = d_smooth;
                prev_t    = t_now;

                printf("[TOF] D=%6.3f m  V=%+6.3f m/s\n", d_smooth, v_filt);

            } else {
                /* 범위 밖: valid만 내림, 기존 값 유지 */
                pthread_mutex_lock(&g_tof.lock);
                g_tof.valid = 0;
                pthread_mutex_unlock(&g_tof.lock);
            }

        } else {
            pthread_mutex_lock(&g_tof.lock);
            g_tof.valid = 0;
            pthread_mutex_unlock(&g_tof.lock);
            printf("[TOF] 측정 실패 (raw=%d)\n", raw);
        }

        /* 50ms 주기 맞추기 */
        long long elapsed = now_ms() - t_now;
        if (elapsed < SENSOR_PERIOD_MS)
            usleep((SENSOR_PERIOD_MS - (int)elapsed) * 1000);
    }

    close(fd);
    printf("[TOF] 센서 스레드 종료\n");
    return NULL;
}