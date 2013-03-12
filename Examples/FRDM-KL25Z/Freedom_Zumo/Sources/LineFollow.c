/*
 * LineFollow.c
 *
 *  Created on: Feb 15, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "LineFollow.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LEDR.h"
#include "LEDG.h"
#include "SW1.h"
#include "Turn.h"
#include "WAIT1.h"
#include "Pid.h"
#include "Turn.h"

#define LINE_DEBUG 0 /* careful: this will slow down the PID loop frequency! */

typedef enum {
  STATE_INIT,
  STATE_CALIBRATE,
  STATE_IDLE,
  STATE_FOLLOW,
  STATE_BRAKE,
} StateType;

static StateType currState = STATE_INIT;

static void StartFollowing(void) {
  PID_Init();
  currState = STATE_FOLLOW;
}

static void ButtonPress(void) {
  switch (currState) { /* state before button press */
  case STATE_INIT:
    REF_Calibrate(TRUE); /* blink LED during calibration */
    currState = STATE_CALIBRATE;
    break;
  case STATE_CALIBRATE:
    REF_Calibrate(FALSE);
    currState = STATE_IDLE;
    break;
  case STATE_IDLE:
    StartFollowing();
    break;
  case STATE_FOLLOW:
    currState = STATE_BRAKE;
    break;
  case STATE_BRAKE:
    currState = STATE_IDLE;
    break;
  } /* switch */
}

#if PL_USE_TSS  
void LF_TouchPress(uint8_t position) {
  ButtonPress();
}
#endif

static void StateMachine(void);

static void FollowLine(void) {
  uint16_t currLine;
  bool onLine;
  REF_LineKind lineKind, nextLineKind;
  TURN_Kind turn;
#if LINE_DEBUG
  static int cnt=0;
#endif
  
  REF_Measure();
  currLine = REF_GetLineValue(&onLine);
  lineKind = REF_GetLineKind();
  turn = TURN_STRAIGHT; /* default */
  if (lineKind==REF_LINE_LEFT || lineKind==REF_LINE_RIGHT || lineKind==REF_LINE_FULL) {
    TURN_StepForward();
    REF_Measure();
    currLine = REF_GetLineValue(&onLine);
    nextLineKind = REF_GetLineKind();
    if (lineKind==REF_LINE_LEFT && nextLineKind==REF_LINE_FORWARD) { /* is -| */
      turn = TURN_SelectTurn(lineKind);
    } else if (lineKind==REF_LINE_RIGHT && nextLineKind==REF_LINE_FORWARD) { /* is |- */
      turn = TURN_SelectTurn(lineKind);
    } else if (lineKind==REF_LINE_LEFT && nextLineKind==REF_LINE_NONE) { /* is left turn */
      turn = TURN_LEFT90;
    } else if (lineKind==REF_LINE_RIGHT && nextLineKind==REF_LINE_NONE) { /* is right turn */
      turn = TURN_RIGHT90;
    } else if (lineKind==REF_LINE_FULL && nextLineKind==REF_LINE_NONE) { /* is T */
      turn = TURN_SelectTurn(REF_LINE_LEFT); /* follow left hand rule */
    } else if (lineKind==REF_LINE_FULL && nextLineKind==REF_LINE_FORWARD) { /* is + */
      turn = TURN_SelectTurn(REF_LINE_LEFT); /* follow left hand rule */
    } else if (lineKind==REF_LINE_FULL && nextLineKind==REF_LINE_FULL) { /* finish reached */
      turn = TURN_STOP;
    } else {
      turn = TURN_STOP; /* default value */
    }
  }
  if (turn==TURN_STOP) {
    currState = STATE_BRAKE;
    StateMachine(); /* need to handle new state */
    return;
  }
  if (turn!=TURN_STRAIGHT) { /* turn left, right or around */
    currState = STATE_BRAKE;
    StateMachine(); /* need to handle new state */
    WAIT1_WaitOSms(100);
    
    TURN_Turn(turn);
    WAIT1_WaitOSms(100);
    currState = STATE_FOLLOW; /* back to following mode */
    return;
  }
#if LINE_DEBUG
  cnt++;
  if (cnt>10) {
    cnt = 0;
    CLS1_SendStr((unsigned char*)LF_LineKindStr(lineKind), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
  }
#endif
#if 0
  if (lineKind==REF_LINE_NONE || lineKind==REF_LINE_AIR) { /* not calibrated or no line => stop */
    currState = STATE_BRAKE;
    StateMachine(); /* need to handle new state */
    return;
  }
#endif
  PID_Process(currLine, REF_MAX_LINE_VALUE/2);
}

static void StateMachine(void) {
  static uint16_t cnt;
  
  switch (currState) {
  case STATE_INIT:
    LEDG_Off();
    LEDR_On();
    break;
  case STATE_CALIBRATE:
    cnt++;
    if (cnt>50) {
      cnt = 0;
      LEDR_Neg();
    }
    if (!REF_IsCalibrating()) {
      currState = STATE_IDLE;
    }
    break;
  case STATE_IDLE:
    REF_Measure(); /* in order to show the current values */
    LEDR_Off();
    LEDG_On();
    break;
  case STATE_FOLLOW:
    if (!REF_CanUseSensor()) {
      currState = STATE_BRAKE;
    } else {
      LEDR_Off();
      LEDG_Off();
      FollowLine();
    }
    break;
  case STATE_BRAKE:
    LEDR_Off();
    LEDG_Off();
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    currState = STATE_IDLE;
    break;
  } /* switch */
}

static portTASK_FUNCTION(LineTask, pvParameters) {
  uint32_t cnt;
  
  (void)pvParameters; /* not used */
  for(;;) {
    if (SW1_GetVal()==0) { /* button pressed */
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS); /* simple debounce */
      if (SW1_GetVal()==0) { /* still pressed */
        LEDG_On();
        cnt = 0;
        while(SW1_GetVal()==0 && cnt<=10) {
          FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
          cnt++;
        } /* wait until released */
        if (cnt>10) {
          /* long press, calibrate again */
          currState = STATE_INIT;
        }
        ButtonPress();
        while (SW1_GetVal()==0) { /* wait until button is released */
          FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
        }
      }
    }
    if (REF_IsCalibrating()) {
      currState = STATE_CALIBRATE;
    }
    StateMachine();
    if (currState==STATE_FOLLOW) {
      FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
    } else {
      FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
    }
  }
}

static void LF_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"line", (unsigned char*)"Group of line following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or satus\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop|calibrate", (unsigned char*)"Starts or stops line following, or does calibration\r\n", io->stdOut);
}

static void LF_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"line", (unsigned char*)"\r\n", io->stdOut);
  switch (currState) {
    case STATE_INIT: 
      CLS1_SendStatusStr((unsigned char*)"  status", (unsigned char*)"INIT\r\n", io->stdOut);
      break;
    case STATE_CALIBRATE: 
      CLS1_SendStatusStr((unsigned char*)"  status", (unsigned char*)"CALIBRATE\r\n", io->stdOut);
      break;
    case STATE_IDLE: 
      CLS1_SendStatusStr((unsigned char*)"  status", (unsigned char*)"IDLE\r\n", io->stdOut);
      break;
    case STATE_FOLLOW: 
      CLS1_SendStatusStr((unsigned char*)"  status", (unsigned char*)"RUN\r\n", io->stdOut);
      break;
    case STATE_BRAKE: 
      CLS1_SendStatusStr((unsigned char*)"  status", (unsigned char*)"BRAKE\r\n", io->stdOut);
      break;
  } /* switch */
}

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"line help")==0) {
    LF_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"line status")==0) {
    LF_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line calibrate")==0) {
    REF_Calibrate(TRUE);
    currState = STATE_CALIBRATE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line start")==0) {
    StartFollowing();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line stop")==0) {
    currState = STATE_BRAKE;
    *handled = TRUE;
  }
  return res;
}

void LF_Init(void) {
  currState = STATE_INIT;
  if (FRTOS1_xTaskCreate(LineTask, (signed portCHAR *)"Line", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
