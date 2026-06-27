# ============================================================
#  Makefile — TOF400F + accsubsystem (Embedded Coder / ERT)
#
#  디렉토리 구조:
#    ./
#    ├── main.c
#    ├── tof_sensor.c
#    ├── tof_sensor.h
#    └── accsubsystem_ert_rtw/
#        ├── accsubsystem.c
#        ├── accsubsystem_data.c
#        ├── rt_nonfinite.c
#        ├── rtGetInf.c
#        └── rtGetNaN.c
#
#  사용법:
#    make        빌드
#    make clean  오브젝트 + 실행파일 삭제
#    make run    빌드 후 실행 (sudo: 실시간 스케줄러)
# ============================================================

TARGET  := acc_system
CC      := gcc

# _POSIX_C_SOURCE: clock_gettime, sigaction, usleep 활성화
CFLAGS  := -Wall -Wextra -O2 -std=c11 -D_GNU_SOURCE
LDFLAGS := -lpthread -lm

# ── Embedded Coder (ERT) 폴더 ─────────────────────────────
RTW_DIR := accsubsystem_ert_rtw

# ── include 경로 ──────────────────────────────────────────
INCLUDES := -I. -I$(RTW_DIR)

# ── 소스 파일 ─────────────────────────────────────────────
SRCS_LOCAL := main.c \
              tof_sensor.c \
              can.c

# Embedded Coder 생성 소스 (ert_main.c 는 제외 — main.c로 대체)
SRCS_RTW := $(RTW_DIR)/accsubsystem.c \
            $(RTW_DIR)/accsubsystem_data.c \
            $(RTW_DIR)/rt_nonfinite.c \
            $(RTW_DIR)/rtGetInf.c \
            $(RTW_DIR)/rtGetNaN.c

SRCS_ALL := $(SRCS_LOCAL) $(SRCS_RTW)

# ── 오브젝트 파일 (현재 폴더에 생성) ─────────────────────
OBJS := $(notdir $(SRCS_ALL:.c=.o))

# ============================================================
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo ""
	@echo "  빌드 완료: ./$(TARGET)"
	@echo "  실행:  make run  (또는 sudo ./$(TARGET))"

# 현재 폴더 .c → .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# RTW_DIR 안의 .c → .o
%.o: $(RTW_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "  clean 완료"

run: all
	sudo ./$(TARGET)