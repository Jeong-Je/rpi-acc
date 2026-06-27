/*
 * main.c
 *
 * TOF400F 센서 스레드 + Embedded Coder ACC MPC 루프
 *
 * 입력 구조체 (accsubsystem_U):
 *   set_velocity       — 설정 속도 (m/s)
 *   Timegap            — 목표 시간 간격 (s), 보통 1.4
 *   ego_velocity       — 자차 속도 (m/s)  ← CAN 등 별도 입력
 *   relativedistance   — 상대 거리 (m)    ← TOF400F
 *   relative_velocity  — 상대 속도 (m/s)  ← TOF400F
 *
 * 출력 구조체 (accsubsystem_Y):
 *   Longitudinalacceleration — 종방향 가속도 명령 (m/s²)
 *
 * 컴파일:
 *   make
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <math.h>

#include "tof_sensor.h"
#include "can.h"
#include "accsubsystem_ert_rtw/accsubsystem.h"

/* ── 전역: 공유메모리 + 종료 플래그 ───────────────────── */
TofSharedState g_tof;
atomic_int     g_running = 1;

/* ── 자차 속도: CAN으로 TC375에서 수신 ────────────────────
 * can_recv_ego_velocity() 실패 시 이전 값 유지              */
static double get_v_ego(void)
{
    static double last_v = 0.0;
    double v = can_recv_ego_velocity();
    if (v >= 0.0) last_v = v;   /* 수신 성공 시만 갱신 */
    return last_v;
}

/* ── 시간 유틸 ─────────────────────────────────────────── */
static long long now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

/* ── 시그널 핸들러 ─────────────────────────────────────── */
static void on_signal(int sig)
{
    (void)sig;
    printf("\n[main] 종료 신호 수신 → 정리 중...\n");
    atomic_store(&g_running, 0);
}

/* ── rt_OneStep: ert_main.c 패턴 그대로 ────────────────── */
static void rt_OneStep(void)
{
    static volatile int overrun = 0;

    if (overrun) {
        rtmSetErrorStatus(accsubsystem_M, "Overrun");
        return;
    }
    overrun = 1;

    accsubsystem_step();

    overrun = 0;
}

/* ══════════════════════════════════════════════════════════
 *  main
 * ══════════════════════════════════════════════════════════ */
int main(void)
{
    printf("===========================================\n");
    printf(" TOF400F + accsubsystem (Embedded Coder)\n");
    printf(" 센서: 50ms  /  MPC: 100ms\n");
    printf("===========================================\n\n");

    /* ── 1. 시그널 등록 ── */
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = on_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    /* ── 2. 공유메모리 초기화 ── */
    memset(&g_tof, 0, sizeof g_tof);
    if (pthread_mutex_init(&g_tof.lock, NULL) != 0) {
        fprintf(stderr, "[main] mutex 초기화 실패\n");
        return EXIT_FAILURE;
    }

    /* ── 3. Embedded Coder 모델 초기화 (step 전 반드시 1회) ── */
    accsubsystem_initialize();
    printf("[main] accsubsystem_initialize() 완료\n");

    /* ── 4. CAN 초기화 (PCAN USB / SocketCAN) ── */
    if (can_init() != 0) {
        fprintf(stderr, "[main] CAN 초기화 실패\n"
                        "       sudo ip link set can0 up type can bitrate 500000\n");
        accsubsystem_terminate();
        pthread_mutex_destroy(&g_tof.lock);
        return EXIT_FAILURE;
    }

    /* ── 5. TOF 센서 스레드 시작 ── */
    pthread_t t_sensor;
    if (pthread_create(&t_sensor, NULL, tof_sensor_thread, NULL) != 0) {
        fprintf(stderr, "[main] 센서 스레드 생성 실패\n");
        accsubsystem_terminate();
        can_close();
        pthread_mutex_destroy(&g_tof.lock);
        return EXIT_FAILURE;
    }

    /* 센서 첫 측정값 안정화 대기 */
    printf("[main] 센서 안정화 대기 (200ms)...\n\n");
    usleep(200000);

    /* ── 5. MPC 루프 (100ms, ert_main의 rt_OneStep 주기) ──────
     *
     *  ert_main.c 에서 rt_OneStep()을 타이머/인터럽트에 붙이라고
     *  안내하는데, 라즈베리파이에서는 POSIX 타이머 대신
     *  sleep_until 방식으로 100ms 주기를 맞춥니다.
     * ─────────────────────────────────────────────────────── */
    const int    MPC_PERIOD_MS  = 100;
    const int    STALE_LIMIT_MS = 300;
    const double DT             = MPC_PERIOD_MS / 1000.0;
    const double TIMEGAP        = 0.8;

    /* 속도 범위를 accsubsystem_data.c 값에서 직접 읽음
     * → accsubsystem_data.c 한 곳만 수정하면 전체 반영 */
    const double V_SET      = accsubsystem_P.Maximumvelocityconstant_Value * 0.8;
                              /* 최대속도의 80% = 0.8 m/s */
    const double V_MIN      = accsubsystem_P.Minimumvelocityconstant_Value;
    const double V_MAX      = accsubsystem_P.Maximumvelocityconstant_Value;

    double v_target = V_SET;  /* 적분 초기값 */
    int stale_count = 0;

    printf("[main] MPC 루프 시작\n\n");
    long long next_wake = now_ms();

    while (atomic_load(&g_running))
    {
        /* rtmGetErrorStatus 확인 — 루프 종료 대신 경고만 출력 */
        const char *err = rtmGetErrorStatus(accsubsystem_M);
        if (err != NULL) {
            fprintf(stderr, "[MPC] ⚠ 모델 오류: %s → 모델 재초기화\n", err);
            rtmSetErrorStatus(accsubsystem_M, NULL);
            accsubsystem_initialize();   /* 상태 리셋 후 계속 */
        }

        /* 100ms 주기 대기 */
        long long now = now_ms();
        if (now < next_wake)
            usleep((next_wake - now) * 1000);
        next_wake += MPC_PERIOD_MS;

        long long t_now = now_ms();

        /* ── 공유메모리 읽기 ── */
        double    d_rel, v_rel;
        long long ts;
        int       valid;

        pthread_mutex_lock(&g_tof.lock);
        d_rel = g_tof.d_rel;
        v_rel = g_tof.v_rel;
        ts    = g_tof.timestamp;
        valid = g_tof.valid;
        pthread_mutex_unlock(&g_tof.lock);

        int fresh = valid && ((t_now - ts) < STALE_LIMIT_MS);

        if (fresh) {
            stale_count = 0;

            double v_ego = get_v_ego();

            /* ── 입력 구조체 채우기 ── */
            accsubsystem_U.set_velocity      = V_SET;
            accsubsystem_U.Timegap           = TIMEGAP;
            accsubsystem_U.ego_velocity      = v_ego;
            accsubsystem_U.relativedistance  = d_rel;
            accsubsystem_U.relative_velocity = v_rel;

            /* ── MPC 1스텝 실행 ── */
            rt_OneStep();

            double a_cmd = accsubsystem_Y.Longitudinalacceleration;

            /*
             * 가속도 → 목표 속도 적분
             *   v_target(k+1) = v_target(k) + a_cmd * DT
             *
             * 클램프:
             *   - 하한 0 m/s : 후진 명령 방지
             *   - 상한 V_SET : 설정 속도 초과 방지
             */
            v_target += a_cmd * DT;
            if (v_target < V_MIN) v_target = V_MIN;
            if (v_target > V_MAX) v_target = V_MAX;

            printf("[MPC] D=%6.3fm  Vrel=%+6.3fm/s  Vego=%5.2fm/s"
                   "  a=%+.3fm/s²  → Vtgt=%5.2fm/s (%.1fkm/h)\n",
                   d_rel, v_rel, accsubsystem_U.ego_velocity,
                   a_cmd, v_target, v_target * 3.6);

            /* ── CAN 송신: 목표 속도 → TC375 ── */
            can_send_v_target(v_target);

        } else {
            stale_count++;
            printf("[MPC] ⚠ 센서 데이터 없음 (%d회 연속)\n", stale_count);

            if (stale_count >= 5) {
                /* 500ms 이상 데이터 없음 → 안전 감속 */
                printf("[MPC] 안전 감속 명령\n");
                accsubsystem_U.relative_velocity = 0.0;
                rt_OneStep();
                /* send_can_accel(-1.5); */
            }
        }
    }

    /* ── 6. 정상 종료 ── */
    printf("[main] 종료 처리 중...\n");

    pthread_cancel(t_sensor);
    pthread_join(t_sensor, NULL);

    accsubsystem_terminate();
    can_close();
    pthread_mutex_destroy(&g_tof.lock);

    printf("[main] 정상 종료\n");
    return EXIT_SUCCESS;
}