/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_MATRIX
#include "rs485.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "Stepper.h"
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif

#define MATRIX_BOARD_ARRANGEMENT  (0)  /* 0: first clock (3x8, black with red hands) or 1: second clock: (3x8, green hands) */

#define MATRIX_NOF_CLOCKS_Y       (3)  /* number of clocks in y direction */
#define MATRIX_NOF_CLOCKS_X       (2*4)  /* number of clocks in x direction */
#define MATRIX_NOF_BOARDS         (6)

#define MATRIX_NOF_CLOCKS_BOARD_X (4)  /* number of clocks on PCB in x direction */
#define MATRIX_NOF_CLOCKS_BOARD_Y (1)  /* number of clocks on PCB in y direction */
#define MATRIX_BOARD_CLOCK_NR_INC (0)  /* 1: clocks are numbered 0,1,2,3 on board */

#define MATRIX_NOF_BOARDS_Y       (MATRIX_NOF_CLOCKS_Y/MATRIX_NOF_CLOCKS_BOARD_Y) /* number of boards in Y (rows) direction */
#define MATRIX_NOF_BOARDS_X       (MATRIX_NOF_CLOCKS_X/MATRIX_NOF_CLOCKS_BOARD_X) /* number of boards in X (columns) direction */
#define MATRIX_CLOCKS_NOF_HAND    (2)  /* number of hands per clock */

typedef struct {
  uint8_t addr; /* RS-485 address */
  uint8_t nr;   /* clock number, 0..3 */
  bool enabled; /* if enabled or not */
} MatrixClock_t;

typedef struct {
  bool enabled; /* if board is enabled or not */
  uint8_t addr; /* RS-485 address of the board */
} MATRIX_Board;

#if MATRIX_BOARD_ARRANGEMENT==0
  static const MATRIX_Board MATRIX_Boards[MATRIX_NOF_BOARDS] =
    {
      {.enabled = true, .addr = 0x10},
      {.enabled = true, .addr = 0x11},
      {.enabled = true, .addr = 0x12},
      {.enabled = true, .addr = 0x13},
      {.enabled = true, .addr = 0x14},
      {.enabled = true, .addr = 0x15},
    };
#elif MATRIX_BOARD_ARRANGEMENT==1
  static const MATRIX_Board MATRIX_Boards[MATRIX_NOF_BOARDS] =
    {
      {.enabled = false, .addr = 0x20},
      {.enabled = false, .addr = 0x21},
      {.enabled = false, .addr = 0x22},
      {.enabled = false, .addr = 0x23},
      {.enabled = true, .addr = 0x24},
      {.enabled = false,  .addr = 0x25},
    };
#endif

static const MatrixClock_t clockMatrix[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y] = /* information about how the clocks are organized */
{
#if MATRIX_BOARD_ARRANGEMENT==0
  /* first 3 boards on the left */
  [0][0]={.addr=0x12, .nr=3, .enabled=true}, [1][0]={.addr=0x12, .nr=2, .enabled=true}, [2][0]={.addr=0x12, .nr=1, .enabled=true}, [3][0]={.addr=0x12, .nr=0, .enabled=true},
  [0][1]={.addr=0x11, .nr=3, .enabled=true}, [1][1]={.addr=0x11, .nr=2, .enabled=true}, [2][1]={.addr=0x11, .nr=1, .enabled=true}, [3][1]={.addr=0x11, .nr=0, .enabled=true},
  [0][2]={.addr=0x10, .nr=3, .enabled=true}, [1][2]={.addr=0x10, .nr=2, .enabled=true}, [2][2]={.addr=0x10, .nr=1, .enabled=true}, [3][2]={.addr=0x10, .nr=0, .enabled=true},

  /* second 3 boards on the right */
  [4][0]={.addr=0x14, .nr=3, .enabled=true}, [5][0]={.addr=0x14, .nr=2, .enabled=true}, [6][0]={.addr=0x14, .nr=1, .enabled=true}, [7][0]={.addr=0x14, .nr=0, .enabled=true},
  [4][1]={.addr=0x15, .nr=3, .enabled=true}, [5][1]={.addr=0x15, .nr=2, .enabled=true}, [6][1]={.addr=0x15, .nr=1, .enabled=true}, [7][1]={.addr=0x15, .nr=0, .enabled=true},
  [4][2]={.addr=0x13, .nr=3, .enabled=true}, [5][2]={.addr=0x13, .nr=2, .enabled=true}, [6][2]={.addr=0x13, .nr=1, .enabled=true}, [7][2]={.addr=0x13, .nr=0, .enabled=true},
#elif MATRIX_BOARD_ARRANGEMENT==1
  /* first 3 boards on the left */
  [0][0]={.addr=0x20, .nr=3, .enabled=true}, [1][0]={.addr=0x20, .nr=2, .enabled=true}, [2][0]={.addr=0x20, .nr=1, .enabled=true}, [3][0]={.addr=0x20, .nr=0, .enabled=true},
  [0][1]={.addr=0x21, .nr=3, .enabled=true}, [1][1]={.addr=0x21, .nr=2, .enabled=true}, [2][1]={.addr=0x21, .nr=1, .enabled=true}, [3][1]={.addr=0x21, .nr=0, .enabled=true},
  [0][2]={.addr=0x22, .nr=3, .enabled=true}, [1][2]={.addr=0x22, .nr=2, .enabled=true}, [2][2]={.addr=0x22, .nr=1, .enabled=true}, [3][2]={.addr=0x22, .nr=0, .enabled=true},

  /* second 3 boards on the right */
  [4][0]={.addr=0x23, .nr=3, .enabled=true}, [5][0]={.addr=0x23, .nr=2, .enabled=true}, [6][0]={.addr=0x23, .nr=1, .enabled=true}, [7][0]={.addr=0x23, .nr=0, .enabled=true},
  [4][1]={.addr=0x24, .nr=3, .enabled=true}, [5][1]={.addr=0x24, .nr=2, .enabled=true}, [6][1]={.addr=0x24, .nr=1, .enabled=true}, [7][1]={.addr=0x24, .nr=0, .enabled=true},
  [4][2]={.addr=0x25, .nr=3, .enabled=true}, [5][2]={.addr=0x25, .nr=2, .enabled=true}, [6][2]={.addr=0x25, .nr=1, .enabled=true}, [7][2]={.addr=0x25, .nr=0, .enabled=true},
#endif
};

/* map of clocks with their hand position */
static int16_t MATRIX_angleMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_CLOCKS_NOF_HAND]; /* two hands per clock */
/* map of clocks with their speed delay */
static int8_t MATRIX_delayMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_CLOCKS_NOF_HAND]; /* two motors per clock */
static STEPPER_MoveMode_e MATRIX_moveMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_CLOCKS_NOF_HAND];

static bool MATRIX_BoardIsEnabled(uint8_t addr) {
  for(int i=0; i<MATRIX_NOF_BOARDS; i++){
    if (MATRIX_Boards[i].addr==addr) {
      return MATRIX_Boards[i].enabled;
    }
  }
  return false;
}

static void MATRIX_Delay(int32_t ms) {
  while (ms>100) { /* wait in smaller pieces to keep watchdog task informed */
  vTaskDelay(pdMS_TO_TICKS(100));
#if PL_CONFIG_USE_WDT
  WDT_Report(WDT_REPORT_ID_CURR_TASK, 100);
#endif
    ms -= 100;
  }
  /* wait for the remaining time */
  vTaskDelay(pdMS_TO_TICKS(ms));
#if PL_CONFIG_USE_WDT
  WDT_Report(WDT_REPORT_ID_CURR_TASK, ms);
#endif
}

/*!
 * \brief Changes the clock position
 */
static uint8_t MATRIX_DrawClockHands(uint8_t x, uint8_t y, int16_t angle0, int16_t angle1) {
  if (x>=MATRIX_NOF_CLOCKS_X || y>=MATRIX_NOF_CLOCKS_Y) {
    return ERR_FRAMING;
  }
  MATRIX_angleMap[x][y][0] = angle0;
  MATRIX_angleMap[x][y][1] = angle1;
  return ERR_OK;
}

static uint8_t MATRIX_DrawAllClockHands(int16_t angle0, int16_t angle1) {
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      MATRIX_angleMap[x][y][0] = angle0;
      MATRIX_angleMap[x][y][1] = angle1;
    }
  }
  return ERR_OK;
}

static uint8_t MATRIX_DrawClockDelays(uint8_t x, uint8_t y, uint8_t delay0, uint8_t delay1) {
  if (x>=MATRIX_NOF_CLOCKS_X || y>=MATRIX_NOF_CLOCKS_Y) {
    return ERR_FRAMING;
  }
  MATRIX_delayMap[x][y][0] = delay0;
  MATRIX_delayMap[x][y][1] = delay1;
  return ERR_OK;
}

uint8_t MATRIX_DrawAllClockDelays(uint8_t delay0, uint8_t delay1) {
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      MATRIX_delayMap[x][y][0] = delay0;
      MATRIX_delayMap[x][y][1] = delay1;
    }
  }
  return ERR_OK;
}

static uint8_t MATRIX_DrawMoveMode(uint8_t x, uint8_t y, STEPPER_MoveMode_e mode0, STEPPER_MoveMode_e mode1) {
  if (x>=MATRIX_NOF_CLOCKS_X || y>=MATRIX_NOF_CLOCKS_Y) {
    return ERR_FRAMING;
  }
  MATRIX_moveMap[x][y][0] = mode0;
  MATRIX_moveMap[x][y][1] = mode1;
  return ERR_OK;
}

uint8_t MATRIX_DrawAllMoveMode(STEPPER_MoveMode_e mode0, STEPPER_MoveMode_e mode1) {
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      MATRIX_moveMap[x][y][0] = mode0;
      MATRIX_moveMap[x][y][1] = mode1;
    }
  }
  return ERR_OK;
}

static uint8_t MATRIX_WaitForIdle(int32_t timeoutMs) {
  bool boardIsIdle[MATRIX_NOF_BOARDS];
  uint8_t res;

  for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
    boardIsIdle[i] = false;
  }
  for(;;) { /* breaks */
    for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
      if (!boardIsIdle[i]) { /* ask board if it is still not idle */
        if (MATRIX_Boards[i].enabled) {
          res = RS485_SendCommand(MATRIX_Boards[i].addr, (unsigned char*)"stepper idle", 1000); /* ask board if it is idle */
          if (res==ERR_OK) { /* board is idle */
            boardIsIdle[i] = true;
          }
        } else { /* board is not enabled, so it is not busy */
          boardIsIdle[i] = true;
        }
      }
    } /* for */
    /* check if all are idle now */
    for(int i=0; /* breaks */; i++) {
      if (i==MATRIX_NOF_BOARDS) {
        return ERR_OK; /* all boards are idle now */
      }
      if (!boardIsIdle[i]) {
        break; /* at least one is still not idle: break loop */
      }
    } /* for */
    MATRIX_Delay(50);
  #if PL_CONFIG_USE_WDT
    WDT_Report(WDT_REPORT_ID_CURR_TASK, 50);
  #endif
    timeoutMs -= 50; /* more timeout if boards do not respond */
    if (timeoutMs<0) {
      return ERR_BUSY;
    }
  } /* for */
  return ERR_OK;
}

static uint8_t MATRIX_SendToQueue(void) {
  /* assuming that the clocks are organized horizontally, and that the clocks are in 3,2,1,0 order! */
  uint8_t buf[McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE];

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) { /* every clock row */
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) { /* every PCB in column */
      for(int h=0; h<MATRIX_CLOCKS_NOF_HAND; h++) {
        if (MATRIX_BoardIsEnabled(clockMatrix[x][y].addr) && clockMatrix[x][y].enabled) {
          /*  stepper q <c> <m> stepper m <c> <m> <a> <d> <md> */
          McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"stepper q ");
          McuUtility_strcatNum8u(buf, sizeof(buf), clockMatrix[x][y].nr); /* <c> */
          McuUtility_chcat(buf, sizeof(buf), ' ');
          McuUtility_strcatNum8u(buf, sizeof(buf), h); /* <m> */
          McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" stepper m ");
          McuUtility_strcatNum8u(buf, sizeof(buf), clockMatrix[x][y].nr); /* <c> */
          McuUtility_chcat(buf, sizeof(buf), ' ');
          McuUtility_strcatNum8u(buf, sizeof(buf), h); /* <m> */
          McuUtility_chcat(buf, sizeof(buf), ' ');
          McuUtility_strcatNum16u(buf, sizeof(buf), MATRIX_angleMap[x][y][h]); /* <a> */
          McuUtility_chcat(buf, sizeof(buf), ' ');
          McuUtility_strcatNum16u(buf, sizeof(buf), MATRIX_delayMap[x][y][h]); /* <d> */
          McuUtility_chcat(buf, sizeof(buf), ' ');
          switch(MATRIX_moveMap[x][y][h]) {
            default:
            case STEPPER_MOVE_MODE_SHORT:
              McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"sh");
              break;
            case STEPPER_MOVE_MODE_CW:
              McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"cw");
              break;
            case STEPPER_MOVE_MODE_CCW:
              McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"cc");
              break;
          }
          RS485_SendCommand(clockMatrix[x][y].addr, buf, 1000); /* queue the commands */
        }
      }
    }
  }
  return ERR_OK;
}

static uint8_t MATRIX_ExecQueue(void) {
  /* send broadcast execute queue command */
  RS485_SendCommand(RS485_BROADCAST_ADDRESS, (unsigned char*)"stepper exq", 1000); /* execute the queue */
  return ERR_OK;
}

typedef struct {
  int16_t angle; /* absolute angle for clock hand position */
} MHand_t;

typedef struct {
  MHand_t hands[2]; /* each clock has two hands */
} MClock_t;

typedef struct {
  MClock_t digit[3][2]; /* a digit is built by 3 (vertical) and 2 (horizontal) clocks */
} MClockDigit_t;

static MClockDigit_t clockDigits[10] = {
    [0].digit = {
        [0][0]={.hands={{180},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{  0},{180}}}, [1][1]={.hands={{  0},{180}}},
        [2][0]={.hands={{  0},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
    [1].digit = {
        [0][0]={.hands={{225},{225}}}, [0][1]={.hands={{180},{180}}},
        [1][0]={.hands={{225},{225}}}, [1][1]={.hands={{  0},{180}}},
        [2][0]={.hands={{225},{225}}}, [2][1]={.hands={{  0},{  0}}},
    },
    [2].digit = {
        [0][0]={.hands={{ 90},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{180},{ 90}}}, [1][1]={.hands={{270},{  0}}},
        [2][0]={.hands={{  0},{ 90}}}, [2][1]={.hands={{270},{270}}},
    },
    [3].digit = {
        [0][0]={.hands={{ 90},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{ 90},{ 90}}}, [1][1]={.hands={{270},{  0}}},
        [2][0]={.hands={{ 90},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
    [4].digit = {
        [0][0]={.hands={{180},{180}}}, [0][1]={.hands={{180},{180}}},
        [1][0]={.hands={{  0},{ 90}}}, [1][1]={.hands={{270},{  0}}},
        [2][0]={.hands={{225},{225}}}, [2][1]={.hands={{  0},{  0}}},
    },
    [5].digit = {
        [0][0]={.hands={{180},{ 90}}}, [0][1]={.hands={{270},{270}}},
        [1][0]={.hands={{  0},{ 90}}}, [1][1]={.hands={{270},{180}}},
        [2][0]={.hands={{ 90},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
    [6].digit = {
        [0][0]={.hands={{180},{ 90}}}, [0][1]={.hands={{270},{270}}},
        [1][0]={.hands={{  0},{180}}}, [1][1]={.hands={{270},{180}}},
        [2][0]={.hands={{  0},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
    [7].digit = {
        [0][0]={.hands={{ 90},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{225},{225}}}, [1][1]={.hands={{  0},{180}}},
        [2][0]={.hands={{225},{225}}}, [2][1]={.hands={{  0},{  0}}},
    },
    [8].digit = {
        [0][0]={.hands={{180},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{180},{ 90}}}, [1][1]={.hands={{270},{180}}},
        [2][0]={.hands={{  0},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
    [9].digit = {
        [0][0]={.hands={{180},{ 90}}}, [0][1]={.hands={{270},{180}}},
        [1][0]={.hands={{  0},{ 90}}}, [1][1]={.hands={{  0},{180}}},
        [2][0]={.hands={{ 90},{ 90}}}, [2][1]={.hands={{270},{  0}}},
    },
};

static void DrawNumber(MClockDigit_t *digit, uint8_t xPos, uint8_t yPos) {
  /* angle <c> <m> <deg> <md>; Move clock (0-3) and motor (0-1) to angle (0..359) using mode (ccw, cw, short)   */

  for(int y=0; y<3; y++) { /* every clock row */
    for(int x=0; x<2; x++) { /* every clock column */
      (void)MATRIX_DrawClockHands(xPos+x, yPos+y, digit->digit[y][x].hands[0].angle, digit->digit[y][x].hands[1].angle);
    }
  }
}

static uint8_t MATRIX_SendAndExecute(int32_t timeoutMs) {
  uint8_t res;

  res = MATRIX_WaitForIdle(timeoutMs);
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_SendToQueue();
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t MATRIX_MoveAllto12(int32_t timeoutMs, const McuShell_StdIOType *io) {
  uint8_t res;

  res = MATRIX_DrawAllClockHands(0, 0);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)("MoveAllto12: failed drawing hands!\r\n"), io->stdErr);
    return res;
  }
  res = MATRIX_DrawAllClockDelays(8, 8);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)("MoveAllto12: failed setting delays!\r\n"), io->stdErr);
    return res;
  }
  res = MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)("MoveAllto12: failed setting mode!\r\n"), io->stdErr);
    return res;
  }
  res = MATRIX_SendAndExecute(timeoutMs);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)("MoveAllto12: failed executing!\r\n"), io->stdErr);
    return res;
  }
  res = MATRIX_WaitForIdle(2000);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)("MoveAllto12: failed waiting for idle!\r\n"), io->stdErr);
    return res;
  }
  return ERR_OK;
}

void MATRIX_WriteNumber(const McuShell_StdIOType *io) {
  MATRIX_MoveAllto12(10000, io);
  DrawNumber(&clockDigits[0], 0, 0);
  DrawNumber(&clockDigits[1], 2, 0);
  DrawNumber(&clockDigits[2], 4, 0);
  DrawNumber(&clockDigits[3], 6, 0);
  (void)MATRIX_SendAndExecute(3000);
  MATRIX_Delay(4000);
  MATRIX_MoveAllto12(10000, io);

  DrawNumber(&clockDigits[4], 0, 0);
  DrawNumber(&clockDigits[5], 2, 0);
  DrawNumber(&clockDigits[6], 4, 0);
  DrawNumber(&clockDigits[7], 6, 0);
  (void)MATRIX_SendAndExecute(3000);
  MATRIX_Delay(4000);
  MATRIX_MoveAllto12(10000, io);

  DrawNumber(&clockDigits[8], 0, 0);
  DrawNumber(&clockDigits[9], 2, 0);
  DrawNumber(&clockDigits[8], 4, 0);
  DrawNumber(&clockDigits[9], 6, 0);
  (void)MATRIX_SendAndExecute(3000);
  MATRIX_Delay(4000);
  MATRIX_MoveAllto12(10000, io);
#if 0
  for(int i=0; i<=9; i++) {
    DrawNumber(&clockDigits[i], 0, 0);
    (void)MATRIX_Update();
    MATRIX_Delay(4000);
  }
  MATRIX_MoveAllto12(10000, io);
#endif
#if 0
  for(int i=0; i<=9; i++) {
    DrawNumber(&clockDigits[i], 2, 0);
    (void)MATRIX_Update();
   MATRIX_Delay(4000);
  }
#endif
}

static uint8_t MATRIX_FailedDemo(uint8_t res) {
  return res; /* used to set a breakpoint in case of failure */
}

static uint8_t MATRIX_Demo0(const McuShell_StdIOType *io) {
  uint8_t res;

  /* set move mode: */
  (void)MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      MATRIX_DrawClockDelays(x, y, 8+y, 8+y);
    }
  }
  /* set movement: */
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 90, 270);
    }
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 0, 180);
    }
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* execute */
  res = MATRIX_WaitForIdle(1000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* execute */
  res = MATRIX_WaitForIdle(20000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* move to park position */
  res = MATRIX_MoveAllto12(10000, io);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return res;
}

static uint8_t MATRIX_Demo1(const McuShell_StdIOType *io) {
  int angle0, angle1;
  uint8_t res;

  /* init at 12 */
  res = MATRIX_MoveAllto12(10000, io);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* move all clocks to '|' position */
  angle0 = 0;
  angle1 = 180;
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, angle0, angle1);
    }
  }
  (void)MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  (void)MATRIX_DrawAllClockDelays(6, 6);
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Failed Demo1: Point 1\r\n", io->stdErr);
    return MATRIX_FailedDemo(res);
  }
  /* rotate them to the next quadrant */
  (void)MATRIX_DrawAllClockDelays(6, 12);
  for(int i=0; i<3; i++) {
    angle0 = (angle0+90)%360;
    angle1 = (angle1+90)%360;
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
      for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
        (void)MATRIX_DrawClockHands(x, y, angle0, angle1);
      }
    }
    res = MATRIX_SendToQueue(); /* queue command */
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"Failed Demo1: Point 2\r\n", io->stdErr);
      return MATRIX_FailedDemo(res);
    }
  }
  /* execute */
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Failed Demo1: Point 3\r\n", io->stdErr);
    return MATRIX_FailedDemo(res);
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Failed Demo1: Point 4\r\n", io->stdErr);
    return MATRIX_FailedDemo(res);
  }
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
   McuShell_SendStr((unsigned char*)"Failed Demo1: Point 5\r\n", io->stdErr);
   return MATRIX_FailedDemo(res);
  }
  /* move to park position */
  res = MATRIX_MoveAllto12(10000, io);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return res;
}

static uint8_t MATRIX_Demo2(const McuShell_StdIOType *io) {
  int angle0, angle1;
  uint8_t res;

  /* init at 12 */
 // res = MATRIX_MoveAllto12(10000, io);
 // if (res!=ERR_OK) {
 //   return res;
 // }
  /* move all clocks to '|' position */
  (void)MATRIX_DrawAllClockHands(0, 180);
  res = MATRIX_SendToQueue(); /* queue command */
  if (res!=ERR_OK) {
    return res;
  }
  /* configure delays */
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockDelays(x, y, 5+x, 5+x);
    }
  }

  /* rotate them to the next quadrant */
  angle0 = angle1 = 0;
  for(int i=0; i<3; i++) {
    angle0 = (angle0+90)%360;
    angle1 = (angle1+90)%360;
    (void)MATRIX_DrawAllClockHands(angle0, angle1);
    res = MATRIX_SendToQueue(); /* queue command */
    if (res!=ERR_OK) {
      return res;
    }
  }

  /* execute */
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    return res;
  }
  /* move to park position */
  //return MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

static uint8_t MATRIX_Demo3(const McuShell_StdIOType *io) {
  uint8_t res;

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawMoveMode(x, y, STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
      MATRIX_DrawClockDelays(x, y, 8, 8);
    }
  }
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 0, 180);
    }
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_WaitForIdle(1000);
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    return res;
  }
////////////////////////
  res = MATRIX_WaitForIdle(5000);
  if (res!=ERR_OK) {
    return res;
  }

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawMoveMode(x, y, STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
      MATRIX_DrawClockDelays(x, y, 5+x, 5+x);
    }
  }
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 180, 0);
    }
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return res;
  }

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 0, 180);
    }
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return res;
  }
  /* execute */
  res = MATRIX_WaitForIdle(1000);
  if (res!=ERR_OK) {
    return res;
  }
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    return res;
  }
  /* move to park position */
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    return res;
  }
  //return MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

static uint8_t MATRIX_Demo4(const McuShell_StdIOType *io) {
  uint8_t res;

  MATRIX_MoveAllto12(10000, io);

  MATRIX_DrawAllClockDelays(8, 8);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(180, 180);
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed sending to the queue\r\n", io->stdErr);
    return res;
  }

  MATRIX_DrawAllClockHands(0, 0);
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed sending to the queue\r\n", io->stdErr);
    return res;
  }

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(0, 90);
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed sending to the queue\r\n", io->stdErr);
    return res;
  }

  MATRIX_DrawAllClockHands(270, 0);
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed sending to the queue\r\n", io->stdErr);
    return res;
  }
  /* execute */
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed executing queue\r\n", io->stdErr);
    return res;
  }
  res = MATRIX_WaitForIdle(8000);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed waiting\r\n", io->stdErr);
    return res;
  }

  /* move to park position */
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    return res;
  }
  return MATRIX_MoveAllto12(10000, io);
}

static uint8_t MATRIX_Demo5(const McuShell_StdIOType *io) {
  uint8_t res;

  //MATRIX_MoveAllto12(10000, io);

  MATRIX_DrawAllClockDelays(10, 10);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CW);
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x+=2) {
    MATRIX_DrawClockHands(x, 0, 135, 135);
    MATRIX_DrawClockHands(x, 1,  45,  45);
    MATRIX_DrawClockHands(x, 2, 135, 135);

    MATRIX_DrawClockHands(x+1, 0, 225, 225);
    MATRIX_DrawClockHands(x+1, 1, 315, 315);
    MATRIX_DrawClockHands(x+1, 2, 225, 225);
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed sending to the queue\r\n", io->stdErr);
    return res;
  }
  /* execute */
  res = MATRIX_ExecQueue();
  res = MATRIX_WaitForIdle(9000);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CCW);
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x+=2) {
    MATRIX_DrawClockHands(x, 0, 135-1, 135+1);
    MATRIX_DrawClockHands(x, 1,  45-1,  45+1);
    MATRIX_DrawClockHands(x, 2, 135-1, 135+1);

    MATRIX_DrawClockHands(x+1, 0, 225-1, 225+1);
    MATRIX_DrawClockHands(x+1, 1, 315-1, 315+1);
    MATRIX_DrawClockHands(x+1, 2, 225-1, 225+1);
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  res = MATRIX_ExecQueue();
  res = MATRIX_WaitForIdle(9000);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CW);
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x+=2) {
    MATRIX_DrawClockHands(x, 0, 135, 135);
    MATRIX_DrawClockHands(x, 1,  45,  45);
    MATRIX_DrawClockHands(x, 2, 135, 135);

    MATRIX_DrawClockHands(x+1, 0, 225, 225);
    MATRIX_DrawClockHands(x+1, 1, 315, 315);
    MATRIX_DrawClockHands(x+1, 2, 225, 225);
  }
  res = MATRIX_SendToQueue(); /* queue commands */
  res = MATRIX_ExecQueue();
  res = MATRIX_WaitForIdle(9000);

  /* execute */
  res = MATRIX_ExecQueue();
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed executing queue\r\n", io->stdErr);
    return res;
  }
  res = MATRIX_WaitForIdle(8000);
  if (res!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"Demo4: failed waiting\r\n", io->stdErr);
    return res;
  }

  /* move to park position */
  res = MATRIX_WaitForIdle(10000);
  if (res!=ERR_OK) {
    return res;
  }
  //return MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

uint8_t MATRIX_ShowTime(uint8_t hour, uint8_t minute) {
  DrawNumber(&clockDigits[hour/10], 0, 0);
  DrawNumber(&clockDigits[hour%10], 2, 0);
  DrawNumber(&clockDigits[minute/10], 4, 0);
  DrawNumber(&clockDigits[minute%10], 6, 0);
  return MATRIX_SendAndExecute(5000);
}

uint8_t MATRIX_ShowTemperature(uint8_t temperature) {
  /* number */
  DrawNumber(&clockDigits[temperature/10], 0, 0);
  DrawNumber(&clockDigits[temperature%10], 2, 0);
  /* degree */
  (void)MATRIX_DrawClockHands(4, 0, 180,  90);
  (void)MATRIX_DrawClockHands(5, 0, 270, 180);
  (void)MATRIX_DrawClockHands(4, 1,   0,  90);
  (void)MATRIX_DrawClockHands(5, 1, 270,   0);
  (void)MATRIX_DrawClockHands(4, 2, 225, 225);
  (void)MATRIX_DrawClockHands(5, 2, 225, 225);
  /* C */
  (void)MATRIX_DrawClockHands(6, 0,  90, 180);
  (void)MATRIX_DrawClockHands(7, 0, 270, 270);
  (void)MATRIX_DrawClockHands(6, 1,   0, 180);
  (void)MATRIX_DrawClockHands(7, 1, 225, 225);
  (void)MATRIX_DrawClockHands(6, 2,   0,  90);
  (void)MATRIX_DrawClockHands(7, 2, 270, 270);
  return MATRIX_SendAndExecute(5000);
}

static uint8_t MATRIX_Demo(const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  MATRIX_Demo5(io);
  res = MATRIX_WaitForIdle(15000);

  MATRIX_ShowTime(20, 34);
  res = MATRIX_WaitForIdle(15000);
  MATRIX_Delay(3000);

  MATRIX_Demo3(io);
  res = MATRIX_WaitForIdle(15000);

  MATRIX_ShowTemperature(22);
  MATRIX_Delay(3000);
  res = MATRIX_WaitForIdle(15000);

  MATRIX_Demo2(io);
  res = MATRIX_WaitForIdle(15000);

  MATRIX_ShowTime(20, 35);
  res = MATRIX_WaitForIdle(15000);
  MATRIX_Delay(3000);

//  MATRIX_Demo5(io);
  MATRIX_MoveAllto12(10000, io);

  return res;
}

static uint8_t MATRIX_Demo6(const McuShell_StdIOType *io) {
  MATRIX_DrawAllClockDelays(1, 1);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  for(int i=2;i<12;i++) {
    MATRIX_ShowTime(21, i);
    (void)MATRIX_WaitForIdle(10000);
    MATRIX_Delay(800);
  }

  MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

static uint8_t Intermezzo0(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 90);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  MATRIX_DrawAllClockDelays(30, 30);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CCW);
  MATRIX_DrawAllClockHands(90, 270);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  return ERR_OK;
}

static uint8_t Intermezzo1(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 90);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(315, 45);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  return ERR_OK;
}

static uint8_t Intermezzo2(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 180);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(180, 0);
  MATRIX_SendAndExecute(5000);
  MATRIX_WaitForIdle(5000);

  return ERR_OK;
}

uint8_t MATRIX_Intermezzo(uint8_t *nr) {
  /* iterate through the list of intermezzos */
  switch(*nr) {
    case 0:
      (*nr)++;
      return Intermezzo0();
    case 1:
      (*nr)++;
      return Intermezzo1();
    case 2:
      (*nr) = 0;
      return Intermezzo2();
    default:
      break;
  }
  return ERR_FAILED;
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];

  McuShell_SendStatusStr((unsigned char*)"matrix", (unsigned char*)"Matrix settings\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"x*y: ");
  McuUtility_strcatNum8u(buf, sizeof(buf), MATRIX_NOF_CLOCKS_X);
  McuUtility_chcat(buf, sizeof(buf), '*');
  McuUtility_strcatNum8u(buf, sizeof(buf), MATRIX_NOF_CLOCKS_Y);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  clocks", buf, io->stdOut);
  McuUtility_Num8uToStr(buf, sizeof(buf), MATRIX_BOARD_ARRANGEMENT);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  arrangement", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"matrix", (unsigned char*)"Group of matrix commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  12", (unsigned char*)"Set matrix to 12:00 position\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo", (unsigned char*)"General longer demo\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 0", (unsigned char*)"Demo with propeller\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 1", (unsigned char*)"Demo with clap effect\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 2", (unsigned char*)"Demo with changing angles\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 3", (unsigned char*)"Demo with propeller wave\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 4", (unsigned char*)"Demo turning clap\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 5", (unsigned char*)"Demo with squares\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 6", (unsigned char*)"Demo fast clock\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  intermezzo <nr>", (unsigned char*)"Play Intermezzo\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  delay <delay>", (unsigned char*)"Set default delay\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  time <time>", (unsigned char*)"Show time\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  temp <temp>", (unsigned char*)"Show temperature\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t MATRIX_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "matrix help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "matrix status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo")==0) {
    *handled = true;
    return MATRIX_Demo(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 0")==0) {
    *handled = true;
    return MATRIX_Demo0(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 1")==0) {
    *handled = true;
    return MATRIX_Demo1(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 2")==0) {
    *handled = true;
    return MATRIX_Demo2(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 3")==0) {
    *handled = true;
    return MATRIX_Demo3(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 4")==0) {
    *handled = true;
    return MATRIX_Demo4(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 5")==0) {
    *handled = true;
    return MATRIX_Demo5(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 6")==0) {
    *handled = true;
    return MATRIX_Demo6(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix 12")==0) {
    *handled = true;
    return MATRIX_MoveAllto12(10000, io);
  } else if (McuUtility_strncmp((char*)cmd, "matrix intermezzo ", sizeof("matrix intermezzo ")-1)==0) {
    uint8_t nr;

    *handled = TRUE;
    p = cmd + sizeof("matrix intermezzo ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &nr)==ERR_OK) {
      return MATRIX_Intermezzo(&nr);
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "matrix delay ", sizeof("matrix delay ")-1)==0) {
    uint8_t delay;

    *handled = TRUE;
    p = cmd + sizeof("matrix delay ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &delay)==ERR_OK) {
      return MATRIX_DrawAllClockDelays(delay, delay);
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "matrix time ", sizeof("matrix time ")-1)==0) {
    uint8_t hour, minute, second, hsec;

    *handled = TRUE;
    p = cmd + sizeof("matrix time ")-1;
    if (McuUtility_ScanTime(&p, &hour, &minute, &second, &hsec)==ERR_OK) {
      return MATRIX_ShowTime(hour, minute);
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "matrix temp ", sizeof("matrix temp ")-1)==0) {
    uint8_t temperature;

    *handled = TRUE;
    p = cmd + sizeof("matrix time ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &temperature)==ERR_OK) {
      return MATRIX_ShowTemperature(temperature);
    } else {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}
#endif

void MATRIX_Init(void) {
  MATRIX_DrawAllClockHands(0, 0);
  MATRIX_DrawAllClockDelays(0, 0);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
}

#endif /* PL_CONFIG_USE_MATRIX */
