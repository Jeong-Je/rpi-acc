/*
 * can.c
 * SocketCAN 기반 CAN 송수신 구현 (PCAN USB)
 *
 * 컴파일:
 *   gcc ... can.c -lpthread -lm
 *   (별도 라이브러리 불필요 — SocketCAN은 Linux 커널 내장)
 */


#include "can.h"
#include "accsubsystem_ert_rtw/accsubsystem.h"  /* accsubsystem_P 참조 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

/* ── 내부 상태 ─────────────────────────────────────────── */
static int g_sock_send = -1;   /* 송신용 소켓 */
static int g_sock_recv = -1;   /* 수신용 소켓 */

/* ── uint16 ↔ 바이트 변환은 memcpy로 직접 처리 ────────── */

/* ── SocketCAN 소켓 생성 공통 함수 ─────────────────────── */
static int open_can_socket(const char *iface)
{
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sock < 0) {
        perror("[CAN] socket 생성 실패");
        return -1;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof ifr);
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        fprintf(stderr, "[CAN] 인터페이스 '%s' 없음: %s\n"
                        "      sudo ip link set %s up type can bitrate %d\n",
                iface, strerror(errno), iface, CAN_BITRATE);
        close(sock);
        return -1;
    }

    struct sockaddr_can addr = {
        .can_family  = AF_CAN,
        .can_ifindex = ifr.ifr_ifindex,
    };
    if (bind(sock, (struct sockaddr *)&addr, sizeof addr) < 0) {
        perror("[CAN] bind 실패");
        close(sock);
        return -1;
    }

    return sock;
}

/* ══════════════════════════════════════════════════════════
 *  can_init
 * ══════════════════════════════════════════════════════════ */
int can_init(void)
{
    /* 송신 소켓 */
    g_sock_send = open_can_socket(CAN_INTERFACE);
    if (g_sock_send < 0) return -1;

    /* 수신 소켓: ID 0x100 만 필터링 */
    g_sock_recv = open_can_socket(CAN_INTERFACE);
    if (g_sock_recv < 0) {
        close(g_sock_send);
        g_sock_send = -1;
        return -1;
    }

    struct can_filter filter = {
        .can_id   = CAN_ID_EGO_VELOCITY,
        .can_mask = CAN_SFF_MASK,   /* 11비트 전체 일치 */
    };
    setsockopt(g_sock_recv, SOL_CAN_RAW, CAN_RAW_FILTER,
               &filter, sizeof filter);

    /* 수신 타임아웃 10ms — 블로킹 방지 */
    struct timeval tv = { .tv_sec = 0, .tv_usec = 10000 };
    setsockopt(g_sock_recv, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);

    printf("[CAN] SocketCAN 초기화 완료 (%s)\n", CAN_INTERFACE);
    printf("[CAN] 수신 ID: 0x%03X (ego_velocity)\n", CAN_ID_EGO_VELOCITY);
    printf("[CAN] 송신 ID: 0x%03X (v_target)\n",     CAN_ID_V_TARGET);
    return 0;
}

/* ══════════════════════════════════════════════════════════
 *  can_recv_ego_velocity
 *  TC375 → RPi: 자차 속도 수신
 *  반환: 속도 (m/s), 수신 없으면 -1.0
 * ══════════════════════════════════════════════════════════ */
double can_recv_ego_velocity(void)
{
    if (g_sock_recv < 0) return -1.0;

    struct can_frame frame;
    ssize_t n = read(g_sock_recv, &frame, sizeof frame);

    if (n < (ssize_t)sizeof(struct can_frame)) {
        /* 타임아웃 또는 수신 없음 — 정상 상황, 조용히 반환 */
        return -1.0;
    }

    if (frame.can_id != CAN_ID_EGO_VELOCITY || frame.can_dlc < 2) {
        fprintf(stderr, "[CAN] 예상치 못한 ID 또는 DLC: id=0x%X dlc=%d\n",
                frame.can_id, frame.can_dlc);
        return -1.0;
    }

    /* Byte 0~1: uint16 리틀엔디안, 값 × 1000 */
    uint16_t raw;
    memcpy(&raw, frame.data, sizeof raw);
    double v = raw / 1000.0;

    /* 유효 범위 검사: 0 ~ 0.351 m/s (RC카) */
    if (v < 0.0 || v > 0.351) {
        fprintf(stderr, "[CAN] ego_velocity 범위 오류: %.3f m/s (raw=%u, ×1000)\n", v, raw);
        return -1.0;
    }

    return v;
}

/* ══════════════════════════════════════════════════════════
 *  can_send_v_target
 *  RPi → TC375: 목표 속도 송신 (× 100 정수)
 * ══════════════════════════════════════════════════════════ */
int can_send_v_target(double v_target_mps)
{
    if (g_sock_send < 0) {
        fprintf(stderr, "[CAN] 초기화되지 않음\n");
        return -1;
    }

    /* 범위 클램프: accsubsystem_data.c의 Min/MaxVelocity 값 그대로 사용 */
    double v_min = accsubsystem_P.Minimumvelocityconstant_Value;
    double v_max = accsubsystem_P.Maximumvelocityconstant_Value;
    if (v_target_mps < v_min) v_target_mps = v_min;
    if (v_target_mps > v_max) v_target_mps = v_max;

    /* × 1000 변환 후 uint16으로 송신 (예: 0.80 m/s → 800) */
    uint16_t raw = (uint16_t)(v_target_mps * 1000.0 + 0.5);  /* 반올림 */

    /* CAN 프레임 구성 */
    struct can_frame frame;
    memset(&frame, 0, sizeof frame);
    frame.can_id  = CAN_ID_V_TARGET;
    frame.can_dlc = 8;
    memcpy(frame.data, &raw, sizeof raw);   /* Byte 0~1: uint16 리틀엔디안 */
    /* Byte 2~7: 예약 (이미 0x00) */

    ssize_t sent = write(g_sock_send, &frame, sizeof frame);
    if (sent != (ssize_t)sizeof(struct can_frame)) {
        fprintf(stderr, "[CAN] 송신 실패: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}

/* ══════════════════════════════════════════════════════════
 *  can_close
 * ══════════════════════════════════════════════════════════ */
void can_close(void)
{
    if (g_sock_send >= 0) { close(g_sock_send); g_sock_send = -1; }
    if (g_sock_recv >= 0) { close(g_sock_recv); g_sock_recv = -1; }
    printf("[CAN] 소켓 닫힘\n");
}