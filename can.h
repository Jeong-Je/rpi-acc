/*
 * can.h
 * SocketCAN 기반 CAN 통신 (PCAN USB)
 *
 * 하드웨어: PCAN-USB → 라즈베리파이4 USB → TC375 CANH/CANL
 * 드라이버: SocketCAN (can0)
 *
 * CAN ID 구성:
 *   0x100  TC375 → RPi  : 자차 속도 수신 (ego_velocity, m/s)
 *   0x200  RPi   → TC375: 목표 속도 송신 (v_target,    m/s)
 *
 * PCAN USB 초기화 (터미널에서 1회 실행):
 *   sudo ip link set can0 up type can bitrate 500000
 *   sudo ip link set can0 txqueuelen 1000
 *
 * can0 상태 확인:
 *   ip link show can0
 *   candump can0
 */

#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

/* ── CAN 인터페이스 설정 ───────────────────────────────── */
#define CAN_INTERFACE       "can0"
#define CAN_BITRATE         500000      /* 500 kbps */

/* ── CAN ID ────────────────────────────────────────────── */
#define CAN_ID_EGO_VELOCITY  0x100     /* 수신: TC375 → RPi  자차 속도 */
#define CAN_ID_V_TARGET      0x200     /* 송신: RPi   → TC375 목표 속도 */

/* ── 데이터 포맷 (각 8바이트 DLC) ─────────────────────── */
/*
 * ID 0x100 수신 페이로드 (TC375 → RPi):
 *   Byte 0~1 : uint16  ego_velocity × 100  (예: 0.30 m/s → 30)
 *   Byte 2~7 : 예약
 *
 * ID 0x200 송신 페이로드 (RPi → TC375):
 *   Byte 0~1 : uint16  v_target × 100      (예: 0.80 m/s → 80)
 *   Byte 2~7 : 예약 (0x00)
 */

/* ── 속도 범위 클램프 ──────────────────────────────────────
 * accsubsystem_P.Minimumvelocityconstant_Value
 * accsubsystem_P.Maximumvelocityconstant_Value
 * 위 값을 직접 참조하므로 여기서 따로 정의하지 않음.
 * can_send_v_target() 내부에서 accsubsystem_P를 읽어 클램프.
 * ─────────────────────────────────────────────────────────── */

/* ── API ───────────────────────────────────────────────── */

/* SocketCAN 소켓 열기. 성공 0, 실패 -1 */
int  can_init(void);

/* 자차 속도 수신 (TC375 → RPi). 성공 시 m/s 반환, 실패 -1 */
double can_recv_ego_velocity(void);

/* 목표 속도 송신 (RPi → TC375). 성공 0, 실패 -1 */
int  can_send_v_target(double v_target_mps);

/* 소켓 닫기 */
void can_close(void);

#endif /* CAN_H_ */