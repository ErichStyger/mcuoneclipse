/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_MATRIX
#if PL_CONFIG_IS_MASTER
  #include "matrixconfig.h"
  #include "matrix.h"
#endif
#include "rs485.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "Stepper.h"
#include "Shell.h"
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#include "StepperBoard.h"
#if PL_CONFIG_USE_STEPPER_EMUL
  #include "NeoStepperRing.h"
#endif
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif

#define STEPPER_HAND_ZERO_DELAY     (6)

static bool MATRIX_ExecuteQueue = false;

#if PL_CONFIG_IS_MASTER /* master is able to control multiple clock boards: change X, Y and NOF_Boards */
  /* configuration is in matrixconfig.h */
#elif PL_CONFIG_IS_CLIENT /* only single board with 4 clocks */
  #define MATRIX_NOF_CLOCKS_X       (4)  /* number of clocks in x (horizontal) direction */
  #define MATRIX_NOF_CLOCKS_Y       (1)  /* number of clocks in y (vertical) direction */
  #define MATRIX_NOF_CLOCKS_Z       (2)  /* number of clocks in z direction */
  #define MATRIX_NOF_BOARDS         (1)  /* number of boards in matrix */
#endif

/* settings for a single board: */
#define MATRIX_NOF_CLOCKS_BOARD_X (4)  /* number of clocks on PCB in x direction */
#define MATRIX_NOF_CLOCKS_BOARD_Y (1)  /* number of clocks on PCB in y direction */
#define MATRIX_NOF_CLOCKS_BOARD_Z (2)  /* number of clocks on PCB in y direction */

#define MATRIX_NOF_BOARDS_Y       (MATRIX_NOF_CLOCKS_Y/MATRIX_NOF_CLOCKS_BOARD_Y) /* number of boards in Y (rows) direction */
#define MATRIX_NOF_BOARDS_X       (MATRIX_NOF_CLOCKS_X/MATRIX_NOF_CLOCKS_BOARD_X) /* number of boards in X (columns) direction */

#if PL_CONFIG_USE_STEPPER
  /* list of boards */
  static STEPBOARD_Handle_t MATRIX_Boards[MATRIX_NOF_BOARDS];
#else /* used in case no steppers and no LED rings are used */
  /* list of bards defined in matrixconfig.h */
#endif

#if PL_CONFIG_IS_MASTER
  /* map of clocks with their hand position */
  static int16_t MATRIX_angleMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_NOF_CLOCKS_Z]; /* two hands per clock */
  /* map of clocks with their speed delay */
  static int8_t MATRIX_delayMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_NOF_CLOCKS_Z]; /* two motors per clock */
  static STEPPER_MoveMode_e MATRIX_moveMap[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y][MATRIX_NOF_CLOCKS_Z];
#else
  static int const mapXBoardPosNr[] = {3, 2, 1, 0}; /* map steppers on x position for boards. This reflects the X (horizontal) order of steppers */
#endif /* PL_CONFIG_IS_MASTER */

#if PL_CONFIG_USE_STEPPER
#if !PL_CONFIG_USE_STEPPER_EMUL
typedef struct {
  McuX12_017_Handle_t x12device;
  McuX12_017_Motor_e x12motor;
#if PL_CONFIG_USE_MAG_SENSOR
  MAG_MagSensor_e mag;
#endif
} X12_Stepper_t;

static X12_Stepper_t x12Steppers[8]; /* the 8 stepper motors on a board */

static void X12_SingleStep(void *dev, int step) {
  X12_Stepper_t *device = (X12_Stepper_t*)dev;

  McuX12_017_SingleStep(device->x12device, device->x12motor, step);
}
#endif /* !PL_CONFIG_USE_STEPPER_EMUL */
#endif

#if PL_CONFIG_IS_MASTER
static bool MATRIX_BoardIsEnabled(uint8_t addr) {
  for(int i=0; i<MATRIX_NOF_BOARDS; i++){
#if PL_CONFIG_USE_STEPPER
    if (STEPBOARD_GetAddress(MATRIX_Boards[i])==addr) {
      return STEPBOARD_IsEnabled(MATRIX_Boards[i]);
    }
#else
    if (MATRIX_BoardList[i].addr==addr) {
      return MATRIX_BoardList[i].enabled;
    }
#endif
  }
  return false;
}
#endif

#if PL_CONFIG_USE_STEPPER
STEPBOARD_Handle_t MATRIX_AddrGetBoard(uint8_t addr) {
  for(int i=0; i<MATRIX_NOF_BOARDS; i++){
    if (STEPBOARD_GetAddress(MATRIX_Boards[i])==addr) {
      return MATRIX_Boards[i];
    }
  }
  return NULL;
}
#endif

#if PL_CONFIG_USE_STEPPER
static STEPPER_Handle_t MATRIX_GetStepper(int32_t x, int32_t y, int32_t z) {
  STEPPER_Handle_t stepper;
  STEPBOARD_Handle_t board;

  if (x>=MATRIX_NOF_CLOCKS_X || y>=MATRIX_NOF_CLOCKS_Y || z>=MATRIX_NOF_CLOCKS_Z) {
    return NULL;
  }
#if PL_CONFIG_IS_MASTER
  board = MATRIX_AddrGetBoard(clockMatrix[x][y].addr);
  if (board==NULL) {
    return NULL;
  }
  stepper = STEPBOARD_GetStepper(board, clockMatrix[x][y].nr, z);
#else
  board = STEPBOARD_GetBoard();
  if (board==NULL) {
    return NULL;
  }
  stepper = STEPBOARD_GetStepper(board, mapXBoardPosNr[x], z);
#endif
  return stepper;
}
#endif

#if PL_CONFIG_USE_STEPPER_EMUL
void MATRIX_RotorColor(int32_t x, int32_t y, int32_t z, uint8_t red, uint8_t green, uint8_t blue) {
  NEOSR_SetRotorColor(STEPPER_GetDevice(MATRIX_GetStepper(x, y, z)), red, green, blue);
}
#endif

uint8_t MATRIX_GetAddress(int32_t x, int32_t y, int32_t z) {
#if PL_CONFIG_IS_MASTER
  return clockMatrix[x][y].addr;
#else
  return RS485_GetAddress();
#endif
}

uint8_t MATRIX_GetPos(int32_t x, int32_t y, int32_t z) {
#if PL_CONFIG_IS_MASTER
  return clockMatrix[x][y].nr;
#else
  return mapXBoardPosNr[x];
#endif
}

#if PL_CONFIG_IS_MASTER
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
#endif

#if PL_CONFIG_IS_MASTER
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
#endif /* PL_CONFIG_IS_MASTER */

#if PL_CONFIG_IS_MASTER
static uint8_t MATRIX_WaitForIdle(int32_t timeoutMs) {
  bool boardIsIdle[MATRIX_NOF_BOARDS];
  uint8_t res;
  uint8_t addr;
  bool isEnabled;

  for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
    boardIsIdle[i] = false;
  }
  for(;;) { /* breaks */
    for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
      if (!boardIsIdle[i]) { /* ask board if it is still not idle */
  #if PL_CONFIG_USE_STEPPER
        isEnabled = STEPBOARD_IsEnabled(MATRIX_Boards[i]);
        addr = STEPBOARD_GetAddress(MATRIX_Boards[i]);
  #else
        isEnabled = MATRIX_BoardList[i].enabled;
        addr = MATRIX_BoardList[i].addr;
  #endif
        if (isEnabled) {
          res = RS485_SendCommand(addr, (unsigned char*)"idle", 1000, false, 0); /* ask board if it is idle */
          if (res==ERR_OK) { /* board is idle */
            boardIsIdle[i] = true;
          }
        } else { /* board is not enabled, so it is not busy */
          boardIsIdle[i] = true;
        }
      }
    } /* for */
    while(MATRIX_ExecuteQueue) {
      MATRIX_Delay(100); /* need to wait until we are not busy any more */
    }
    /* check if all are idle now */
    for(int i=0; /* breaks */; i++) {
      if (i==MATRIX_NOF_BOARDS) {
        return ERR_OK; /* all boards are idle now */
      }
      if (!boardIsIdle[i]) {
        break; /* at least one is still not idle: break loop */
      }
    } /* for */
    MATRIX_Delay(100);
  #if PL_CONFIG_USE_WDT
    WDT_Report(WDT_REPORT_ID_CURR_TASK, 50);
  #endif
    timeoutMs -= 100; /* more timeout if boards do not respond */
    if (timeoutMs<0) {
      return ERR_BUSY;
    }
  } /* for */
  return ERR_OK;
}

static const unsigned char*GetModeString(STEPPER_MoveMode_e mode, bool speedUp, bool slowDown) {
  const unsigned char *str = (unsigned char*)"SH"; /* default and error case */
  if (speedUp) {
    if (slowDown) {
      switch(mode) {
        case STEPPER_MOVE_MODE_SHORT: str = (unsigned char*)"sh";  break;
        case STEPPER_MOVE_MODE_CW:    str = (unsigned char*)"cw";  break;
        case STEPPER_MOVE_MODE_CCW:   str = (unsigned char*)"cc";  break;
      }
    } else {
      switch(mode) {
        case STEPPER_MOVE_MODE_SHORT: str = (unsigned char*)"sH";  break;
        case STEPPER_MOVE_MODE_CW:    str = (unsigned char*)"cW";  break;
        case STEPPER_MOVE_MODE_CCW:   str = (unsigned char*)"cC";  break;
      }
    }
  } else {
    if (slowDown) {
      switch(mode) {
        case STEPPER_MOVE_MODE_SHORT: str = (unsigned char*)"Sh";  break;
        case STEPPER_MOVE_MODE_CW:    str = (unsigned char*)"Cw";  break;
        case STEPPER_MOVE_MODE_CCW:   str = (unsigned char*)"Cc";  break;
      }
    } else {
      switch(mode) {
        case STEPPER_MOVE_MODE_SHORT: str = (unsigned char*)"SH";  break;
        case STEPPER_MOVE_MODE_CW:    str = (unsigned char*)"CW";  break;
        case STEPPER_MOVE_MODE_CCW:   str = (unsigned char*)"CC";  break;
      }
    }
  }
  return str;
}

static void QueueMoveCommand(int x, int y, int z, int angle, int delay, STEPPER_MoveMode_e mode, bool speedUp, bool slowDown, bool absolute) {
  uint8_t buf[McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE];

  /*  matrix q <x> <y> <z> a <angle> <delay> <mode> */
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"matrix q ");
  McuUtility_strcatNum8u(buf, sizeof(buf), clockMatrix[x][y].board.x); /* <x> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum8u(buf, sizeof(buf), clockMatrix[x][y].board.y); /* <y> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum8u(buf, sizeof(buf), z); /* <z> */
  McuUtility_strcat(buf, sizeof(buf), absolute?(unsigned char*)" a ":(unsigned char*)" r ");
  McuUtility_strcatNum16u(buf, sizeof(buf), angle); /* <a> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum16u(buf, sizeof(buf), delay); /* <d> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcat(buf, sizeof(buf), GetModeString(mode, speedUp, slowDown));
  (void)RS485_SendCommand(clockMatrix[x][y].addr, buf, 1000, true, 1); /* queue the command for the remote boards */
#if PL_CONFIG_USE_STEPPER_EMUL
  /* build a command for the LED rings:  */
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"matrix q ");
  McuUtility_strcatNum8u(buf, sizeof(buf), x); /* <x> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum8u(buf, sizeof(buf), y); /* <y> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum8u(buf, sizeof(buf), z); /* <z> */
  McuUtility_strcat(buf, sizeof(buf), absolute?(unsigned char*)" a ":(unsigned char*)" r ");
  McuUtility_strcatNum16u(buf, sizeof(buf), angle); /* <a> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum16u(buf, sizeof(buf), delay); /* <d> */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcat(buf, sizeof(buf), GetModeString(mode, speedUp, slowDown));
  (void)RS485_SendCommand(RS485_GetAddress(), buf, 1000, true, 1); /* queue the command for ourself (LED ring) */
#endif
}

static uint8_t MATRIX_SendToRemoteQueue(void) {
  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) { /* every clock row */
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) { /* every PCB in column */
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        if (MATRIX_BoardIsEnabled(clockMatrix[x][y].addr) && clockMatrix[x][y].enabled) { /* check if board and clock is enabled */
          QueueMoveCommand(x, y, z, MATRIX_angleMap[x][y][z], MATRIX_delayMap[x][y][z], MATRIX_moveMap[x][y][z], false, false, true);
        }
      }
    }
  }
  return ERR_OK;
}

static uint8_t MATRIX_ExecuteRemoteQueue(void) {
  /* send broadcast execute queue command */
  (void)RS485_SendCommand(RS485_BROADCAST_ADDRESS, (unsigned char*)"matrix exq", 1000, true, 0); /* execute the queue */
  /* send it again, just to make sure if a board has not received it: */
  (void)RS485_SendCommand(RS485_BROADCAST_ADDRESS, (unsigned char*)"matrix exq", 1000, true, 0); /* execute the queue */
  /* check with lastEror if all have received the message */

  bool boardHasError[MATRIX_NOF_BOARDS];
  uint8_t res;
  uint8_t addr;
  bool isEnabled;

  for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
    boardHasError[i] = false;
  }
  for(int i=0; i<MATRIX_NOF_BOARDS; i++) {
    if (!boardHasError[i]) { /* ask board if it is still not idle */
#if PL_CONFIG_USE_STEPPER
      isEnabled = STEPBOARD_IsEnabled(MATRIX_Boards[i]);
      addr = STEPBOARD_GetAddress(MATRIX_Boards[i]);
#else
      isEnabled = MATRIX_BoardList[i].enabled;
      addr = MATRIX_BoardList[i].addr;
#endif
      if (isEnabled) {
        res = RS485_SendCommand(addr, (unsigned char*)"lastError", 1000, false, 0); /* ask board if there was an error */
        if (res==ERR_OK) { /* no error */
          boardHasError[i] = false;
        } else { /* send command again! */
          boardHasError[i] = true;
          (void)RS485_SendCommand(addr, (unsigned char*)"matrix exq", 1000, true, 1); /* execute the queue */
        }
      } else { /* board is not enabled, so it is considered to be fine */
        boardHasError[i] = false;
      }
    }
  } /* for */
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

static uint8_t MATRIX_ExecuteRemoteQueueAndWait(const McuShell_StdIOType *io) {
  uint8_t res;

  res = MATRIX_ExecuteRemoteQueue();
  if (res!=ERR_OK) {
    //McuShell_SendStr((unsigned char*)("MATRIX_ExecuteRemoteQueueAndWait: failed executing!\r\n"), io->stdErr);
    return res;
  }
  MATRIX_Delay(500); /* give the clocks some time to start executing */
  res = MATRIX_WaitForIdle(30000);
  if (res!=ERR_OK) {
    //McuShell_SendStr((unsigned char*)("MATRIX_ExecuteRemoteQueueAndWait: failed waiting for idle!\r\n"), io->stdErr);
    return res;
  }
  return res;
}

static uint8_t MATRIX_SendToRemoteQueueExecuteAndWait(const McuShell_StdIOType *io) {
  uint8_t res;

  res = MATRIX_SendToRemoteQueue();
  if (res!=ERR_OK) {
    return res;
  }
  return MATRIX_ExecuteRemoteQueueAndWait(io);
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
  return MATRIX_SendToRemoteQueueExecuteAndWait(io);
}

void MATRIX_WriteNumber(const McuShell_StdIOType *io) {
  MATRIX_MoveAllto12(10000, io);
  DrawNumber(&clockDigits[0], 0, 0);
  DrawNumber(&clockDigits[1], 2, 0);
  DrawNumber(&clockDigits[2], 4, 0);
  DrawNumber(&clockDigits[3], 6, 0);
  (void)MATRIX_SendToRemoteQueueExecuteAndWait(io);
  MATRIX_Delay(4000);
  MATRIX_MoveAllto12(10000, io);

  DrawNumber(&clockDigits[4], 0, 0);
  DrawNumber(&clockDigits[5], 2, 0);
  DrawNumber(&clockDigits[6], 4, 0);
  DrawNumber(&clockDigits[7], 6, 0);
  (void)MATRIX_SendToRemoteQueueExecuteAndWait(io);
  MATRIX_Delay(4000);
  MATRIX_MoveAllto12(10000, io);

  DrawNumber(&clockDigits[8], 0, 0);
  DrawNumber(&clockDigits[9], 2, 0);
  DrawNumber(&clockDigits[8], 4, 0);
  DrawNumber(&clockDigits[9], 6, 0);
  (void)MATRIX_SendToRemoteQueueExecuteAndWait(io);
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
#endif /* PL_CONFIG_IS_MASTER */

#if PL_CONFIG_IS_MASTER
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
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 0, 180);
    }
  }
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* move to park position */
  res = MATRIX_MoveAllto12(20000, io);
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
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
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
    res = MATRIX_SendToRemoteQueue(); /* queue command */
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"Failed Demo1: Point 2\r\n", io->stdErr);
      return MATRIX_FailedDemo(res);
    }
  }
  /* execute */
  res = MATRIX_ExecuteRemoteQueueAndWait(io);
  if (res!=ERR_OK) {
   McuShell_SendStr((unsigned char*)"Failed Demo1: Point 5\r\n", io->stdErr);
   return MATRIX_FailedDemo(res);
  }
  /* move to park position */
  res = MATRIX_MoveAllto12(20000, io);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return res;
}

static uint8_t MATRIX_Demo2(const McuShell_StdIOType *io) {
  int angle0, angle1;
  uint8_t res;

  (void)MATRIX_DrawAllClockHands(0, 180);
  res = MATRIX_SendToRemoteQueue(); /* queue command */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
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
    res = MATRIX_SendToRemoteQueue(); /* queue command */
    if (res!=ERR_OK) {
      return MATRIX_FailedDemo(res);
    }
  }
  /* execute */
  res = MATRIX_ExecuteRemoteQueueAndWait(io);
  return res;
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
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
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
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      (void)MATRIX_DrawClockHands(x, y, 0, 180);
    }
  }
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return ERR_OK;
}

static uint8_t MATRIX_Demo4(const McuShell_StdIOType *io) {
  uint8_t res;

  MATRIX_MoveAllto12(10000, io);

  MATRIX_DrawAllClockDelays(8, 8);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(180, 180);
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_DrawAllClockHands(0, 0);
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(0, 90);
  res = MATRIX_SendToRemoteQueue(); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  MATRIX_DrawAllClockHands(270, 0);
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  /* move to park position */
  res = MATRIX_WaitForIdle(20000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return MATRIX_MoveAllto12(10000, io);
}

static uint8_t MATRIX_Demo5(const McuShell_StdIOType *io) {
  uint8_t res;

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
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CCW);
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x+=2) {
    MATRIX_DrawClockHands(x, 0, 135-1, 135+1);
    MATRIX_DrawClockHands(x, 1,  45-1,  45+1);
    MATRIX_DrawClockHands(x, 2, 135-1, 135+1);

    MATRIX_DrawClockHands(x+1, 0, 225-1, 225+1);
    MATRIX_DrawClockHands(x+1, 1, 315-1, 315+1);
    MATRIX_DrawClockHands(x+1, 2, 225-1, 225+1);
  }
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CW);
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x+=2) {
    MATRIX_DrawClockHands(x, 0, 135, 135);
    MATRIX_DrawClockHands(x, 1,  45,  45);
    MATRIX_DrawClockHands(x, 2, 135, 135);

    MATRIX_DrawClockHands(x+1, 0, 225, 225);
    MATRIX_DrawClockHands(x+1, 1, 315, 315);
    MATRIX_DrawClockHands(x+1, 2, 225, 225);
  }
  res = MATRIX_SendToRemoteQueueExecuteAndWait(io); /* queue commands */
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  return ERR_OK;
}

uint8_t MATRIX_ShowTime(uint8_t hour, uint8_t minute) {
  DrawNumber(&clockDigits[hour/10], 0, 0);
  DrawNumber(&clockDigits[hour%10], 2, 0);
  DrawNumber(&clockDigits[minute/10], 4, 0);
  DrawNumber(&clockDigits[minute%10], 6, 0);
  return MATRIX_SendToRemoteQueueExecuteAndWait(NULL);
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
  return MATRIX_SendToRemoteQueueExecuteAndWait(NULL);
}

static uint8_t MATRIX_Demo(const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  MATRIX_Demo5(io);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_ShowTime(20, 34);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  MATRIX_Delay(3000);

  MATRIX_Demo3(io);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_ShowTemperature(22);
  MATRIX_Delay(3000);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_Demo2(io);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }

  MATRIX_ShowTime(20, 35);
  res = MATRIX_WaitForIdle(15000);
  if (res!=ERR_OK) {
    return MATRIX_FailedDemo(res);
  }
  MATRIX_Delay(3000);

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

static uint8_t MATRIX_Demo7(const McuShell_StdIOType *io) {
  MATRIX_DrawAllClockDelays(10, 10);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(270, 180);
  MATRIX_SendToRemoteQueueExecuteAndWait(io);
  MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

static uint8_t MATRIX_Test0(const McuShell_StdIOType *io) {
  MATRIX_DrawAllClockDelays(0, 0);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(180, 0);
  MATRIX_SendToRemoteQueue();
  MATRIX_DrawAllClockHands(0, 0);
  MATRIX_SendToRemoteQueueExecuteAndWait(io);
  MATRIX_MoveAllto12(10000, io);
  return ERR_OK;
}

static uint8_t Intermezzo0(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 90);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);

  MATRIX_DrawAllClockDelays(30, 30);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CCW, STEPPER_MOVE_MODE_CCW);
  MATRIX_DrawAllClockHands(90, 270);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);
  return ERR_OK;
}

static uint8_t Intermezzo1(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 90);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(315, 45);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);
  return ERR_OK;
}

static uint8_t Intermezzo2(void) {
  MATRIX_DrawAllClockDelays(40, 40);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
  MATRIX_DrawAllClockHands(0, 180);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);

  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_CW, STEPPER_MOVE_MODE_CW);
  MATRIX_DrawAllClockHands(180, 0);
  MATRIX_SendToRemoteQueueExecuteAndWait(NULL);
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
#endif /* PL_CONFIG_IS_MASTER */

#if PL_CONFIG_USE_MAG_SENSOR

static void MATRIX_MoveByOffset(STEPPER_Handle_t *motors[], int16_t offsets[], size_t nofMotors, uint16_t delay) {
  /* here all hands are on the sensor: adjust with offset */
   for(int i=0; i<nofMotors; i++) {
     STEPPER_MoveMotorStepsRel(motors[i], offsets[i], delay);
   } /* for */
   STEPBOARD_MoveAndWait(STEPBOARD_GetBoard(), 10);
}

static void MATRIX_SetZeroPosition(STEPPER_Handle_t *motors[], size_t nofMotors) {
  /* set zero position */
  for(int i=0; i<nofMotors; i++) {
    STEPPER_SetPos(motors[i], 0);
  }
}

static uint8_t MATRIX_MoveHandOnSensor(STEPPER_Handle_t *motors[], size_t nofMotors, bool onSensor, int32_t stepSize, int32_t timeoutms, uint32_t waitms, uint16_t delay) {
  uint8_t res = ERR_OK;
  bool done;
  X12_Stepper_t *s;

  /* move hand over sensor */
  for(;;) { /* breaks */
    done = true;
    for(int i=0; i<nofMotors; i++) { /* check if all motors are on sensor */
      s = STEPPER_GetDevice(motors[i]);
      if (MAG_IsTriggered(s->mag)!=onSensor) {
        done = false; /* not yet */
        break;
      }
    }
    if (done || timeoutms<0) { /* all hands on sensor */
      break;
    }
    for(int i=0; i<nofMotors; i++) {
      s = STEPPER_GetDevice(motors[i]);
      if (MAG_IsTriggered(s->mag)!=onSensor) {
        STEPPER_MoveMotorStepsRel(motors[i], stepSize, delay); /* make by 1 degree */
      }
    } /* for */
    STEPBOARD_MoveAndWait(STEPBOARD_GetBoard(), waitms);
    timeoutms -= waitms;
  }
  if (timeoutms<0) {
    res = ERR_UNDERFLOW;
  }
  return res;
}

static uint8_t MATRIX_ZeroHand(STEPPER_Handle_t *motors[], int16_t offsets[], size_t nofMotors, uint16_t delay) {
  uint8_t res = ERR_OK;
  X12_Stepper_t *s;

  /* if hand is on sensor: move hand out of the sensor area */
  for(int i=0; i<nofMotors; i++) {
    s = STEPPER_GetDevice(motors[i]);
    if (MAG_IsTriggered(s->mag)) { /* hand on sensor? */
      STEPPER_MoveMotorDegreeRel(motors[i], 90, delay); /* move away from sensor */
    }
  } /* for */
  STEPBOARD_MoveAndWait(STEPBOARD_GetBoard(), 10);

  /* move forward in larger steps to find sensor */
  if (MATRIX_MoveHandOnSensor(motors, nofMotors, true, 10, 10000, 10, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step back in micro-steps just to leave the sensor */
  if (MATRIX_MoveHandOnSensor(motors, nofMotors, false, -1, 10000, 10, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step forward in micro-steps just to enter the sensor again */
  if (MATRIX_MoveHandOnSensor(motors, nofMotors, true, 1, 10000, 2, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* here all hands are on the sensor: adjust with offset */
  MATRIX_MoveByOffset(motors, offsets, nofMotors, delay);
  /* set zero position */
  MATRIX_SetZeroPosition(motors, nofMotors);
  return res;
}

static uint8_t MATRIX_ZeroAllHands(void) {
  uint8_t res = ERR_OK;
  STEPPER_Handle_t *motors[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  int16_t offsets[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  int i;

  /* fill in motor array information */
  i = 0;
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        motors[i] = MATRIX_GetStepper(x, y, z);
        offsets[i] = NVMC_GetStepperZeroOffset(x, z);
        i++;
      }
    }
  }
  /* zero all of them */
  if (MATRIX_ZeroHand(motors, offsets, STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t MATRIX_SetOffsetFrom12(void) {
  /* all hands shall be at 12-o-clock position */
  uint8_t res = ERR_OK;
  STEPPER_Handle_t *motors[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  int16_t offsets[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  STEPPER_Handle_t stepper;
  int i;

  /* first zero position at current position and set delay */
  i = 0;
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        stepper = MATRIX_GetStepper(x, y, z);
        STEPPER_SetPos(stepper, 0);
        motors[i] = stepper;
        i++;
      }
    }
  }

  /* move forward in larger steps to find sensor */
  if (MATRIX_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), true, -10, 10000, 5, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step back in micro-steps just to leave the sensor */
  if (MATRIX_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), false, 1, 10000, 2, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step forward in micro-steps just to enter the sensor again */
  if (MATRIX_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), true, -1, 10000, 2, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
    return res;
  }

  /* store new offsets */
  NVMC_Data_t data;

  data = *NVMC_GetDataPtr(); /* struct copy */
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        stepper = MATRIX_GetStepper(x, y, z);
        data.zeroOffsets[x][z] = -STEPPER_GetPos(stepper);
      }
    }
  }
  res = NVMC_WriteConfig(&data);
  if (res!=ERR_OK) {
    return res;
  }
  /* fill in motor array information */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      offsets[c*STEPPER_NOF_CLOCK_MOTORS + m] = NVMC_GetStepperZeroOffset(c, m);
    }
  }
  MATRIX_MoveByOffset(motors, offsets, sizeof(motors)/sizeof(motors[0]), STEPPER_HAND_ZERO_DELAY);
  return res;
}

static uint8_t MATRIX_Test(void) {
  /* Test the clock stepper motors. Pass -1 to run the test for all motors/clocks */
  for (int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        STEPPER_MoveClockDegreeRel(MATRIX_GetStepper(x, y, z), 90, STEPPER_MOVE_MODE_CW, 4, true, true);
        STEPBOARD_MoveAndWait(STEPBOARD_GetBoard(), 1000);
      }
    }
  }
  for (int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        STEPPER_MoveClockDegreeRel(MATRIX_GetStepper(x, y, z), -90, STEPPER_MOVE_MODE_CCW, 4, true, true);
        STEPBOARD_MoveAndWait(STEPBOARD_GetBoard(), 1000);
      }
    }
  }
  return ERR_OK;
}

#endif

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[128];
#if PL_CONFIG_USE_STEPPER
  uint8_t statusStr[16];
#endif

  McuShell_SendStatusStr((unsigned char*)"matrix", (unsigned char*)"Matrix settings\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"x*y: ");
  McuUtility_strcatNum8u(buf, sizeof(buf), MATRIX_NOF_CLOCKS_X);
  McuUtility_chcat(buf, sizeof(buf), '*');
  McuUtility_strcatNum8u(buf, sizeof(buf), MATRIX_NOF_CLOCKS_Y);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  clocks", buf, io->stdOut);

#if PL_CONFIG_USE_STEPPER
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
      for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
        STEPPER_Handle_t stepper;
        uint8_t addr, nr;

        stepper = MATRIX_GetStepper(x, y, z);
        addr = MATRIX_GetAddress(x, y, z);
        nr = MATRIX_GetPos(x, y, z);
        buf[0] = '\0';
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"addr:0x");
        McuUtility_strcatNum8Hex(buf, sizeof(buf), addr);
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", nr:");
        McuUtility_strcatNum8u(buf, sizeof(buf), nr);
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", Stepper ");
        STEPPER_StrCatStatus(stepper, buf, sizeof(buf));
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");

        McuUtility_strcpy(statusStr, sizeof(statusStr), (unsigned char*)"  M[");
        McuUtility_strcatNum8u(statusStr, sizeof(statusStr), x);
        McuUtility_chcat(statusStr, sizeof(statusStr), ',');
        McuUtility_strcatNum8u(statusStr, sizeof(statusStr), y);
        McuUtility_chcat(statusStr, sizeof(statusStr), ',');
        McuUtility_strcatNum8u(statusStr, sizeof(statusStr), z);
        McuUtility_strcat(statusStr, sizeof(statusStr), (unsigned char*)"]");
        McuShell_SendStatusStr(statusStr, buf, io->stdOut);
      }
    }
  } /* for */
#endif
#if 0 /*! \todo not ported yet */
#if PL_CONFIG_USE_X12_STEPPER
  McuX12_017_GetDeviceStatusString(STEPPER_Clocks[0].mot[X12_017_M0].device, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuUtility_strcpy(statStr, sizeof(statStr), (unsigned char*)"  X12.017[0]");
  McuShell_SendStatusStr(statStr, buf, io->stdOut);
#endif

#if PL_CONFIG_USE_X12_STEPPER
  McuX12_017_GetDeviceStatusString(STEPPER_Clocks[2].mot[X12_017_M0].device, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuUtility_strcpy(statStr, sizeof(statStr), (unsigned char*)"  X12.017[1]");
  McuShell_SendStatusStr(statStr, buf, io->stdOut);
#endif
#endif

  if (MATRIX_ExecuteQueue) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"execute: yes");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"execute: no");
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  queue", buf, io->stdOut);

  return ERR_OK;
}

#if PL_CONFIG_USE_STEPPER
static uint8_t ParseMatrixCommand(const unsigned char *cmd, int32_t *xp, int32_t *yp, int32_t *zp, int32_t *vp, uint8_t *dp, STEPPER_MoveMode_e *modep, bool *speedUpp, bool *slowDownp) {
  /* parse a string like <x> <y> <z> <v> <d> <md> */
  int32_t x, y, z, v, d;

  if (   McuUtility_xatoi(&cmd, &x)==ERR_OK && x>=0 && x<MATRIX_NOF_CLOCKS_X
      && McuUtility_xatoi(&cmd, &y)==ERR_OK && y>=0 && y<MATRIX_NOF_CLOCKS_Y
      && McuUtility_xatoi(&cmd, &z)==ERR_OK && z>=0 && z<MATRIX_NOF_CLOCKS_Z
      && McuUtility_xatoi(&cmd, &v)==ERR_OK
      && McuUtility_xatoi(&cmd, &d)==ERR_OK && d>=0
     )
  {
    if (*cmd==' ') {
      cmd++;
    }
    if (*cmd=='\0') { /* mode is optional, set it to defaults */
      *modep = STEPPER_MOVE_MODE_SHORT;
      *speedUpp = *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cw")==0) {
      *modep = STEPPER_MOVE_MODE_CW;
      *speedUpp = *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Cw")==0) {
      *modep = STEPPER_MOVE_MODE_CW;
      *speedUpp = false; *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cW")==0) {
      *modep = STEPPER_MOVE_MODE_CW;
      *speedUpp = true; *slowDownp = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"CW")==0) {
      *modep = STEPPER_MOVE_MODE_CW;
      *speedUpp = *slowDownp = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cc")==0) {
      *modep = STEPPER_MOVE_MODE_CCW;
      *speedUpp = *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Cc")==0) {
      *modep = STEPPER_MOVE_MODE_CCW;
      *speedUpp = false; *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cC")==0) {
      *modep = STEPPER_MOVE_MODE_CCW;
      *speedUpp = true; *slowDownp = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"CC")==0) {
      *modep = STEPPER_MOVE_MODE_CCW;
      *speedUpp = *slowDownp = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"sh")==0) {
      *modep = STEPPER_MOVE_MODE_SHORT;
      *speedUpp = *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Sh")==0) {
      *modep = STEPPER_MOVE_MODE_SHORT;
      *speedUpp = false; *slowDownp = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"sH")==0) {
      *modep = STEPPER_MOVE_MODE_SHORT;
      *speedUpp = true; *slowDownp = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"SH")==0) {
      *modep = STEPPER_MOVE_MODE_SHORT;
      *speedUpp = *slowDownp = false;
    } else {
      return ERR_FAILED;
    }
    *xp = x;
    *yp = y;
    *zp = z;
    *vp = v;
    *dp = d;
    return ERR_OK;
  }
  return ERR_FAILED;
}
#endif

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"matrix", (unsigned char*)"Group of matrix commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test", (unsigned char*)"Test the stepper on the board\r\n", io->stdOut);
#if PL_CONFIG_IS_MASTER
  McuShell_SendHelpStr((unsigned char*)"  12", (unsigned char*)"Set matrix to 12:00 position\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo", (unsigned char*)"General longer demo\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 0", (unsigned char*)"Demo with propeller\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 1", (unsigned char*)"Demo with clap effect\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 2", (unsigned char*)"Demo with changing angles\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 3", (unsigned char*)"Demo with propeller wave\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 4", (unsigned char*)"Demo turning clap\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 5", (unsigned char*)"Demo with squares\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 6", (unsigned char*)"Demo fast clock\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  demo 7", (unsigned char*)"Demo moving hand around\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test 0", (unsigned char*)"LED and hand test\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  intermezzo <nr>", (unsigned char*)"Play Intermezzo\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  delay <delay>", (unsigned char*)"Set default delay\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  time <time>", (unsigned char*)"Show time\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  temp <temp>", (unsigned char*)"Show temperature\r\n", io->stdOut);
#endif
#if PL_CONFIG_USE_STEPPER_EMUL
  McuShell_SendHelpStr((unsigned char*)"  color <x> <y> <z> <rgb>", (unsigned char*)"Set RGB color, <rgb> is three values <r> <g> <b>\r\n", io->stdOut);
#endif
#if PL_CONFIG_USE_STEPPER
  McuShell_SendHelpStr((unsigned char*)"", (unsigned char*)"<xyz>: coordinate, separated by space, e.g. 0 0 1\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"", (unsigned char*)"<md>: mode (cc, cw, sh), lowercase mode letter is with accel control for start/stop, e.g. Cw\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"", (unsigned char*)"<d>: delay, 0 is no delay\r\n", io->stdOut);
#if PL_CONFIG_USE_STEPPER_EMUL
  McuShell_SendHelpStr((unsigned char*)"  R <xyz> <a> <d> <md>", (unsigned char*)"Relative angle move for LED and motor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  A <xyz> <a> <d> <md>", (unsigned char*)"Absolute angle move for LED and motor\r\n", io->stdOut);
#endif
  McuShell_SendHelpStr((unsigned char*)"  r <xyz> <a> <d> <md>", (unsigned char*)"Relative angle move\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  a <xyz> <a> <d> <md>", (unsigned char*)"Absolute angle move\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  q <xyz> <cmd>", (unsigned char*)"Queue a 'r' or 'a' command, e.g. 'matrix q 0 0 0 r 90 8 cc'\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  exq", (unsigned char*)"Execute commands in queue\r\n", io->stdOut);
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  McuShell_SendHelpStr((unsigned char*)"  zero all", (unsigned char*)"Move all motors to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  zero <x> <y> <z>", (unsigned char*)"Move clock to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  offs <x> <y> <z> <v>", (unsigned char*)"Set offset value for clock\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  offs 12", (unsigned char*)"Calculate offset from 12-o-clock for all\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t MATRIX_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
#if PL_CONFIG_USE_STEPPER
  uint8_t res;
  int32_t x, y, z, v;
  uint8_t d;
  bool speedUp, slowDown;
  STEPPER_MoveMode_e mode;
#endif

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "matrix help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "matrix status")==0)) {
    *handled = true;
    return PrintStatus(io);
#if PL_CONFIG_IS_MASTER
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
  } else if (McuUtility_strcmp((char*)cmd, "matrix demo 7")==0) {
    *handled = true;
    return MATRIX_Demo7(io);
  } else if (McuUtility_strcmp((char*)cmd, "matrix test 0")==0) {
    *handled = true;
    return MATRIX_Test0(io);
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
#endif /* PL_CONFIG_IS_MASTER */
#if PL_CONFIG_USE_STEPPER
  #if PL_CONFIG_USE_STEPPER_EMUL
  } else if (McuUtility_strncmp((char*)cmd, "matrix A ", sizeof("matrix A ")-1)==0   /* "matrix A <x> <y> <z> <a> <d> <md> " */
          || McuUtility_strncmp((char*)cmd, "matrix R ", sizeof("matrix R ")-1)==0       /* "matrix R <x> <y> <z> <a> <d> <md> " */
            )
  {
    *handled = TRUE;
    res = ParseMatrixCommand(cmd+sizeof("matrix A ")-1, &x, &y, &z, &v, &d, &mode, &speedUp, &slowDown);
    if (res==ERR_OK) {
      QueueMoveCommand(x, y, z, v, d, mode, speedUp, slowDown, cmd[7]=='A');
      /* send execute to the device: */
      (void)RS485_SendCommand(clockMatrix[x][y].addr, (unsigned char*)"matrix exq", 1000, true, 0); /* execute the queue */
      /* send it to the master too: */
      (void)RS485_SendCommand(RS485_GetAddress(), (unsigned char*)"matrix exq", 1000, true, 0);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  #endif
  } else if (McuUtility_strncmp((char*)cmd, "matrix r ", sizeof("matrix r ")-1)==0) { /* "matrix r <x> <y> <z> <a> <d> <md> " */
    *handled = TRUE;
    res = ParseMatrixCommand(cmd+sizeof("matrix r ")-1, &x, &y, &z, &v, &d, &mode, &speedUp, &slowDown);
    if (res==ERR_OK) {
      STEPPER_MoveClockDegreeRel(MATRIX_GetStepper(x, y, z), v, mode, d, speedUp, slowDown);
      STEPPER_StartTimer();
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "matrix a ", sizeof("matrix a ")-1)==0) { /* "matrix a <x> <y> <z> <a> <d> <md> " */
    *handled = TRUE;
    res = ParseMatrixCommand(cmd+sizeof("matrix a ")-1, &x, &y, &z, &v, &d, &mode, &speedUp, &slowDown);
    if (res==ERR_OK) {
      STEPPER_MoveClockDegreeAbs(MATRIX_GetStepper(x, y, z), v, mode, d, speedUp, slowDown);
      STEPPER_StartTimer();
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "matrix q ", sizeof("matrix q ")-1)==0) {
    unsigned char *ptr, *data;
    STEPPER_Handle_t stepper;

    *handled = TRUE;
    p = cmd + sizeof("matrix q ")-1;
    if (   McuUtility_xatoi(&p, &x)==ERR_OK && x>=0 && x<MATRIX_NOF_CLOCKS_X
        && McuUtility_xatoi(&p, &y)==ERR_OK && y>=0 && y<MATRIX_NOF_CLOCKS_Y
        && McuUtility_xatoi(&p, &z)==ERR_OK && z>=0 && z<MATRIX_NOF_CLOCKS_Z
       )
    {
      data = (unsigned char*)p;
      while(*data==' ') {
        data++;
      }
      ptr = pvPortMalloc(McuUtility_strlen((char*)data)+1);
      if (ptr==NULL) {
        return ERR_FAILED;
      }
      stepper = MATRIX_GetStepper(x, y, z);
      strcpy((char*)ptr, (char*)data); /* copy command */
      if (xQueueSendToBack(STEPPER_GetQueue(stepper), &ptr, pdMS_TO_TICKS(100))!=pdTRUE) {
        return ERR_FAILED;
      }
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
#endif
#if PL_CONFIG_USE_STEPPER_EMUL
  } else if (McuUtility_strncmp((char*)cmd, "matrix color ", sizeof("matrix color ")-1)==0) {
    int32_t r,g,b;

    *handled = TRUE;
    p = cmd + sizeof("matrix color ")-1;
    if (   McuUtility_xatoi(&p, &x)==ERR_OK && x>=0 && x<MATRIX_NOF_CLOCKS_X
        && McuUtility_xatoi(&p, &y)==ERR_OK && y>=0 && y<MATRIX_NOF_CLOCKS_Y
        && McuUtility_xatoi(&p, &z)==ERR_OK && z>=0 && z<MATRIX_NOF_CLOCKS_Z
        && McuUtility_xatoi(&p, &r)==ERR_OK && r>=0 && r<=0xff
        && McuUtility_xatoi(&p, &g)==ERR_OK && g>=0 && g<=0xff
        && McuUtility_xatoi(&p, &b)==ERR_OK && b>=0 && b<=0xff
       )
    {
      MATRIX_RotorColor(x, y, z, r, g, b);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
#endif
  } else if (McuUtility_strcmp((char*)cmd, "matrix exq")==0) {
    MATRIX_ExecuteQueue = true;
    *handled = TRUE;
#if PL_CONFIG_USE_MAG_SENSOR
  } else if (McuUtility_strcmp((char*)cmd, "matrix zero all")==0) {
    *handled = TRUE;
    return MATRIX_ZeroAllHands();
  } else if (McuUtility_strncmp((char*)cmd, "matrix zero ", sizeof("matrix zero ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("matrix zero ")-1;
    if (   McuUtility_xatoi(&p, &x)==ERR_OK && x>=0 && x<MATRIX_NOF_CLOCKS_X
        && McuUtility_xatoi(&p, &y)==ERR_OK && y>=0 && y<MATRIX_NOF_CLOCKS_Y
        && McuUtility_xatoi(&p, &z)==ERR_OK && z>=0 && z<MATRIX_NOF_CLOCKS_Z
       )
    {
      STEPPER_Handle_t *motors[1];
      int16_t offset;

      motors[0] = MATRIX_GetStepper(x, y, z);
      offset = NVMC_GetStepperZeroOffset(x, z);
      res = MATRIX_ZeroHand(motors, &offset, 1, STEPPER_HAND_ZERO_DELAY);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed to find magnet/zero position\r\n", io->stdErr);
      }
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strcmp((char*)cmd, "matrix offs 12")==0) {
    *handled = TRUE;
    return MATRIX_SetOffsetFrom12();
  } else if (McuUtility_strcmp((char*)cmd, "matrix test")==0) {
    *handled = TRUE;
    return MATRIX_Test();
#endif
  }
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_STEPPER
void MATRIX_TimerCallback(void) {
  bool workToDo = false;
  STEPPER_Handle_t stepper;

  /* go through all boards and update steps */
  for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
    for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
       for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) { /* go through all motors */
         stepper = MATRIX_GetStepper(x, y, z);
         workToDo |= STEPPER_TimerClockCallback(stepper);
      } /* for */
    }
  }
  /* check if we can stop timer */
  if (!workToDo) {
    STEPPER_StopTimer();
  }
}
#endif

#if PL_CONFIG_USE_STEPPER_EMUL
#include "NeoPixel.h"
void MATRIX_SetLEDs(void) {
  for(int b=0; b<MATRIX_NOF_BOARDS; b++) {
    for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
      for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
        STEPPER_Handle_t stepper;

        stepper = STEPBOARD_GetStepper(MATRIX_Boards[b], i, j);
        NEOSR_SetRotorPixel(STEPPER_GetDevice(stepper), STEPPER_GetPos(stepper));
      }
    }
  } /* for */
}
#endif

#if PL_CONFIG_USE_STEPPER
static void MatrixQueueTask(void *pv) {
  uint8_t *cmd;
  bool noCommandsInQueue = true;
  McuShell_ConstStdIOType *io = McuShell_GetStdio();
  STEPPER_Handle_t stepper;
  uint8_t command[96];

  for(;;) {
    noCommandsInQueue = true;
    if (MATRIX_ExecuteQueue) {
      for(int x=0; x<MATRIX_NOF_CLOCKS_X; x++) {
        for(int y=0; y<MATRIX_NOF_CLOCKS_Y; y++) {
          for(int z=0; z<MATRIX_NOF_CLOCKS_Z; z++) {
            stepper = MATRIX_GetStepper(x, y, z);
            if (STEPPER_IsIdle(stepper)) { /* no steps to do? */
              if (xQueueReceive(STEPPER_GetQueue(stepper), &cmd, 0)==pdPASS) { /* check queue */
                noCommandsInQueue = false;
                McuUtility_strcpy(command, sizeof(command), (unsigned char*)"matrix ");
                if ((cmd[0]=='a' || cmd[0]=='r') && cmd[1] == ' ') {
                  McuUtility_chcat(command, sizeof(command), cmd[0]);
                  McuUtility_chcat(command, sizeof(command), ' ');
                  McuUtility_strcatNum8u(command, sizeof(command), x);
                  McuUtility_chcat(command, sizeof(command), ' ');
                  McuUtility_strcatNum8u(command, sizeof(command), y);
                  McuUtility_chcat(command, sizeof(command), ' ');
                  McuUtility_strcatNum8u(command, sizeof(command), z);
                  McuUtility_chcat(command, sizeof(command), ' ');
                  McuUtility_strcat(command, sizeof(command), cmd+2);
                } else { /* error? */
                  McuUtility_strcat(command, sizeof(command), cmd);
                }
                //McuShell_SendStr(command, io->stdOut);
                //McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
                if (SHELL_ParseCommand(command, io, true)!=ERR_OK) { /* parse and execute it */
                  McuShell_SendStr((unsigned char*)"Failed executing queued command!\r\n", io->stdErr);
                }
                vPortFree(cmd); /* free memory for command */
              }
            }
          } /* all motors on clock */
        } /* all clocks on board */
      } /* for all boards */
      if (noCommandsInQueue) { /* nothing pending in queues */
        bool allIdle = true;
        for(int b=0; b<MATRIX_NOF_BOARDS; b++) {
          if (STEPBOARD_IsIdle(MATRIX_Boards[b])) {
            //STEPBOARD_NormalizePosition(MATRIX_Boards[b]); /* \todo could get a race condition here! */
            /* system seems idle but is not:
             * matrix R 0 4 0 360 0 CW
             * matrix r 0 4 0 360 0 CC
             */
          } else {
            allIdle = false;
          }
        }
        if (allIdle) {
          MATRIX_ExecuteQueue = false;
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  } /* for */
}
#endif

#if PL_CONFIG_USE_STEPPER_EMUL
static void CreateLedRings(int boardNo, uint8_t addr, bool boardEnabled, int ledLane, int ledStartPos) {
  NEOSR_Config_t stepperRingConfig;
  NEOSR_Handle_t ring[8];
  STEPPER_Config_t stepperConfig;
  STEPPER_Handle_t stepper[8];
  STEPBOARD_Config_t stepBoardConfig;
  const uint8_t rgbRed = 0x5;

  /* get default configurations */
  STEPPER_GetDefaultConfig(&stepperConfig);
  STEPBOARD_GetDefaultConfig(&stepBoardConfig);
  NEOSR_GetDefaultConfig(&stepperRingConfig);

  /* setup ring */
  stepperRingConfig.ledLane = ledLane;
  stepperRingConfig.ledStartPos = ledStartPos;
  stepperRingConfig.ledCw = false;
  stepperRingConfig.ledRed = rgbRed;
  stepperRingConfig.ledGreen = 0;
  stepperRingConfig.ledBlue = 0;
  ring[0] = NEOSR_InitDevice(&stepperRingConfig);
  ring[1] = NEOSR_InitDevice(&stepperRingConfig);

  stepperRingConfig.ledStartPos = ledStartPos+40;
  ring[2] = NEOSR_InitDevice(&stepperRingConfig);
  ring[3] = NEOSR_InitDevice(&stepperRingConfig);

  stepperRingConfig.ledStartPos = ledStartPos+80;
  ring[4] = NEOSR_InitDevice(&stepperRingConfig);
  ring[5] = NEOSR_InitDevice(&stepperRingConfig);

  stepperRingConfig.ledStartPos = ledStartPos+120;
  ring[6] = NEOSR_InitDevice(&stepperRingConfig);
  ring[7] = NEOSR_InitDevice(&stepperRingConfig);

  /* setup stepper */
  stepperConfig.stepFn = NULL;//NEOSR_SingleStep;

  stepperConfig.device = ring[0];
  stepper[0] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[1];
  stepper[1] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[2];
  stepper[2] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[3];
  stepper[3] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[4];
  stepper[4] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[5];
  stepper[5] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[6];
  stepper[6] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = ring[7];
  stepper[7] = STEPPER_InitDevice(&stepperConfig);

  /* setup board */
  stepBoardConfig.addr = addr;
  stepBoardConfig.enabled = boardEnabled;
  stepBoardConfig.stepper[0][0] = stepper[7];
  stepBoardConfig.stepper[0][1] = stepper[6];
  stepBoardConfig.stepper[1][0] = stepper[5];
  stepBoardConfig.stepper[1][1] = stepper[4];
  stepBoardConfig.stepper[2][0] = stepper[3];
  stepBoardConfig.stepper[2][1] = stepper[2];
  stepBoardConfig.stepper[3][0] = stepper[1];
  stepBoardConfig.stepper[3][1] = stepper[0];

  MATRIX_Boards[boardNo] = STEPBOARD_InitDevice(&stepBoardConfig);
}

static void InitLedRings(void) {
#if MATRIX_NOF_BOARDS>=1
  CreateLedRings(0, BOARD_ADDR_00, true, 0, 0);
#endif
#if MATRIX_NOF_BOARDS>=2
  CreateLedRings(1, BOARD_ADDR_01, true, 1, 0);
#endif
#if MATRIX_NOF_BOARDS>=3
  CreateLedRings(2, BOARD_ADDR_02, true, 2, 0);
#endif
#if MATRIX_NOF_BOARDS>=4
  CreateLedRings(3, BOARD_ADDR_03, true, 3, 0);
#endif
#if MATRIX_NOF_BOARDS>=5
  CreateLedRings(4, BOARD_ADDR_04, true, 4, 0);
#endif

#if MATRIX_NOF_BOARDS>=6
  CreateLedRings(5, BOARD_ADDR_05, true, 0, 4*40);
#endif
#if MATRIX_NOF_BOARDS>=7
  CreateLedRings(6, BOARD_ADDR_06, true, 1, 4*40);
#endif
#if MATRIX_NOF_BOARDS>=8
  CreateLedRings(7, BOARD_ADDR_07, true, 2, 4*40);
#endif
#if MATRIX_NOF_BOARDS>=9
  CreateLedRings(8, BOARD_ADDR_08, true, 3, 4*40);
#endif
#if MATRIX_NOF_BOARDS>=10
  CreateLedRings(9, BOARD_ADDR_09, true, 4, 4*40);
#endif

#if MATRIX_NOF_BOARDS>=11
  CreateLedRings(10, BOARD_ADDR_10, true, 0, 8*40);
#endif
#if MATRIX_NOF_BOARDS>=12
  CreateLedRings(11, BOARD_ADDR_11, true, 1, 8*40);
#endif
#if MATRIX_NOF_BOARDS>=13
  CreateLedRings(12, BOARD_ADDR_12, true, 2, 8*40);
#endif
#if MATRIX_NOF_BOARDS>=14
  CreateLedRings(13, BOARD_ADDR_13, true, 3, 8*40);
#endif
#if MATRIX_NOF_BOARDS>=15
  CreateLedRings(14, BOARD_ADDR_14, true, 4, 8*40);
#endif
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

#if PL_CONFIG_USE_X12_STEPPER
static void InitSteppers(void) {
  McuX12_017_Config_t x12config;
  McuX12_017_Handle_t x12device[2];
  STEPPER_Config_t stepperConfig;
  STEPPER_Handle_t stepper[8];
  STEPBOARD_Config_t stepBoardConfig;

  /* get default configurations */
  McuX12_017_GetDefaultConfig(&x12config);
  STEPPER_GetDefaultConfig(&stepperConfig);
  STEPBOARD_GetDefaultConfig(&stepBoardConfig);

  /* -------- X12.017 devices: two on each board -------------- */
  /* initialize first X12.017 */
  /* DRV_RESET: PIO0_14 */
  x12config.hasReset = true;
  x12config.hw_reset.gpio = GPIO;
  x12config.hw_reset.port = 0U;
  x12config.hw_reset.pin  = 14U;

  /* M0_DIR: PIO1_9 */
  x12config.motor[X12_017_M0].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M0].hw_dir.port = 1U;
  x12config.motor[X12_017_M0].hw_dir.pin  = 9U;

  /* M0_STEP: PIO0_12 */
  x12config.motor[X12_017_M0].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M0].hw_step.port = 0U;
  x12config.motor[X12_017_M0].hw_step.pin  = 12U;

  /* M1_DIR: PIO0_13 */
  x12config.motor[X12_017_M1].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M1].hw_dir.port = 0U;
  x12config.motor[X12_017_M1].hw_dir.pin  = 13U;

  /* M1_STEP: PIO1_8 */
  x12config.motor[X12_017_M1].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M1].hw_step.port = 1U;
  x12config.motor[X12_017_M1].hw_step.pin  = 8U;

  /* M2_DIR: PIO0_4 */
  x12config.motor[X12_017_M2].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M2].hw_dir.port = 0U;
  x12config.motor[X12_017_M2].hw_dir.pin  = 4U;

  /* M2_STEP: PIO0_28 */
  x12config.motor[X12_017_M2].isInverted = true;
  x12config.motor[X12_017_M2].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M2].hw_step.port = 0U;
  x12config.motor[X12_017_M2].hw_step.pin  = 28U;

#if PL_CONFIG_BOARD_VERSION==1 /* PIO0_11 needs external pull-up! */
  /* M3_DIR: PIO0_11 */
  x12config.motor[X12_017_M3].isInverted = true;
  x12config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_dir.port = 0U;
  x12config.motor[X12_017_M3].hw_dir.pin  = 11U;
#else
  /* M3_DIR: PIO0_27 */
  x12config.motor[X12_017_M3].isInverted = true;
  x12config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_dir.port = 0U;
  x12config.motor[X12_017_M3].hw_dir.pin  = 27U;
#endif

#if PL_CONFIG_BOARD_VERSION==1
  /* M3_STEP: PIO1_0 */
  x12config.motor[X12_017_M3].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_step.port = 1U;
  x12config.motor[X12_017_M3].hw_step.pin  = 0U;
#else
  /* M3_STEP: PIO0_26 */
  x12config.motor[X12_017_M3].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_step.port = 0U;
  x12config.motor[X12_017_M3].hw_step.pin  = 26U;
#endif
  x12device[0] = McuX12_017_InitDevice(&x12config);

  /* initialize second X12.017 */
  x12config.hasReset = false; /* second device shares the reset line from the first */
  /* M4_DIR: PIO0_0 */
  x12config.motor[X12_017_M0].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M0].hw_dir.port = 0U;
  x12config.motor[X12_017_M0].hw_dir.pin  = 0U;

  /* M4_STEP: PIO1_7 */
  x12config.motor[X12_017_M0].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M0].hw_step.port = 1U;
  x12config.motor[X12_017_M0].hw_step.pin  = 7U;

  /* M5_DIR: PIO0_6 */
  x12config.motor[X12_017_M1].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M1].hw_dir.port = 0U;
  x12config.motor[X12_017_M1].hw_dir.pin  = 6U;

  /* M5_STEP: PIO0_7 */
  x12config.motor[X12_017_M1].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M1].hw_step.port = 0U;
  x12config.motor[X12_017_M1].hw_step.pin  = 7U;

  /* M6_DIR: PIO0_8 */
  x12config.motor[X12_017_M2].isInverted = true;
  x12config.motor[X12_017_M2].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M2].hw_dir.port = 0U;
  x12config.motor[X12_017_M2].hw_dir.pin  = 8U;

  /* M6_STEP: PIO0_9 */
  x12config.motor[X12_017_M2].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M2].hw_step.port = 0U;
  x12config.motor[X12_017_M2].hw_step.pin  = 9U;

  /* M7_DIR: PIO1_5 */
  x12config.motor[X12_017_M3].isInverted = true;
  x12config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_dir.port = 1U;
  x12config.motor[X12_017_M3].hw_dir.pin  = 5U;

  /* M7_STEP: PIO1_6 */
  x12config.motor[X12_017_M3].hw_step.gpio = GPIO;
  x12config.motor[X12_017_M3].hw_step.port = 1U;
  x12config.motor[X12_017_M3].hw_step.pin  = 6U;

  x12device[1] = McuX12_017_InitDevice(&x12config);

  /* setup the 8 stepper motors */
  x12Steppers[0].x12device = x12device[0];
  x12Steppers[0].x12motor = X12_017_M1;
  x12Steppers[1].x12device = x12device[0];
  x12Steppers[1].x12motor = X12_017_M0;
  x12Steppers[2].x12device = x12device[0];
  x12Steppers[2].x12motor = X12_017_M3;
  x12Steppers[3].x12device = x12device[0];
  x12Steppers[3].x12motor = X12_017_M2;
  x12Steppers[4].x12device = x12device[1];
  x12Steppers[4].x12motor = X12_017_M3;
  x12Steppers[5].x12device = x12device[1];
  x12Steppers[5].x12motor = X12_017_M2;
  x12Steppers[6].x12device = x12device[1];
  x12Steppers[6].x12motor = X12_017_M1;
  x12Steppers[7].x12device = x12device[1];
  x12Steppers[7].x12motor = X12_017_M0;
#if PL_CONFIG_USE_MAG_SENSOR
  x12Steppers[0].mag = MAG_MAG1;
  x12Steppers[1].mag = MAG_MAG0;
  x12Steppers[2].mag = MAG_MAG2;
  x12Steppers[3].mag = MAG_MAG3;
  x12Steppers[4].mag = MAG_MAG4;
  x12Steppers[5].mag = MAG_MAG5;
  x12Steppers[6].mag = MAG_MAG7;
  x12Steppers[7].mag = MAG_MAG6;
#endif
  /* initialize stepper, 4 for each X12 driver */
  stepperConfig.stepFn = X12_SingleStep;

  stepperConfig.device = &x12Steppers[0];
  stepper[0] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[1];
  stepper[1] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[2];
  stepper[2] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[3];
  stepper[3] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[4];
  stepper[4] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[5];
  stepper[5] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[6];
  stepper[6] = STEPPER_InitDevice(&stepperConfig);
  stepperConfig.device = &x12Steppers[7];
  stepper[7] = STEPPER_InitDevice(&stepperConfig);

  /* setup board */
  stepBoardConfig.addr = RS485_GetAddress();
  stepBoardConfig.enabled = true;
  stepBoardConfig.stepper[0][0] = stepper[0];
  stepBoardConfig.stepper[0][1] = stepper[1];
  stepBoardConfig.stepper[1][0] = stepper[2];
  stepBoardConfig.stepper[1][1] = stepper[3];
  stepBoardConfig.stepper[2][0] = stepper[4];
  stepBoardConfig.stepper[2][1] = stepper[5];
  stepBoardConfig.stepper[3][0] = stepper[6];
  stepBoardConfig.stepper[3][1] = stepper[7];

  MATRIX_Boards[0] = STEPBOARD_InitDevice(&stepBoardConfig);

#if PL_CONFIG_USE_X12_STEPPER
  McuX12_017_ResetDriver(x12device[0]); /* shared reset line with second device */
#endif
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

void MATRIX_Init(void) {
#if PL_CONFIG_USE_STEPPER_EMUL
  InitLedRings();
#elif PL_CONFIG_USE_X12_STEPPER
  InitSteppers();
#endif
#if PL_CONFIG_USE_STEPPER
  /* ---------------------------------------------------------- */
  /* default */
  STEPBOARD_SetBoard(MATRIX_Boards[0]);
  /* ---------------------------------------------------------- */
#endif

#if PL_CONFIG_IS_MASTER
  MATRIX_DrawAllClockHands(0, 0);
  MATRIX_DrawAllClockDelays(0, 0);
  MATRIX_DrawAllMoveMode(STEPPER_MOVE_MODE_SHORT, STEPPER_MOVE_MODE_SHORT);
#endif
#if PL_CONFIG_USE_STEPPER
  if (xTaskCreate(
      MatrixQueueTask,  /* pointer to the task */
      "StepperQueue", /* task name for kernel awareness debugging */
      800/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
#endif
}
#endif /* PL_CONFIG_USE_MATRIX */
