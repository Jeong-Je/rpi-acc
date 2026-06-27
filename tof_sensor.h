/*
 * tof_sensor.h
 * TOF400F 센서 스레드 인터페이스
 */
#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H

#include <pthread.h>
#include <stdatomic.h>

/* 센서 → MPC 공유 데이터 */
typedef struct {
    double          d_rel;       /* 상대 거리 (m)   */
    double          v_rel;       /* 상대 속도 (m/s) */
    long long       timestamp;   /* 마지막 갱신 (ms) */
    int             valid;
    pthread_mutex_t lock;
} TofSharedState;

extern TofSharedState g_tof;     /* main.c에서 정의, 모두가 참조 */
extern atomic_int     g_running; /* 0 = 전체 종료 */

/* 센서 스레드 진입점 — pthread_create에 직접 전달 */
void *tof_sensor_thread(void *arg);

#endif /* TOF_SENSOR_H */