/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "DIRR.h"
#include "DIRL.h"
#include "PWML.h"
#include "PWMR.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDBY.h"
#include "Reflectance.h"
#include "SW3.h"
#include "WAIT1.h"
#include "Motor.h"
#include "Buzzer.h"
#include "LSM303.h"

typedef enum {
  STATE_INIT,
  STATE_CALIBRATE,
  STATE_RUN,
  STATE_STOP,
} StateType;

static StateType currState = STATE_INIT;
#define MAX_SPEED (0xffff-0xFFFF)
static uint16_t pFactor = 25;
static uint16_t dFactor = 60;

static void pidLine(uint16_t currLine, uint16_t setLine) {
  int16_t error;
  static int16_t lastError;
  int32_t motSpeed, speedL, speedR;
  
  error = currLine-setLine; /* calculate error */
  motSpeed = error*pFactor; /* P portion */
  motSpeed += (error-lastError)*dFactor; /* D portion */
  lastError = error; /* remember for next iteration */
  speedL = MAX_SPEED+motSpeed;
  speedR = MAX_SPEED-motSpeed;
  if (speedL<0) {
    speedL = 0;
  }
  if (speedR<0) {
    speedR = 0;
  }
  if (speedL>0xffff) {
    speedL = 0xffff;
  }
  if (speedR>0xffff) {
    speedR = 0xffff;
  }
  MOT_SetVal(&motorL, speedL);
  MOT_SetVal(&motorR, speedR);
#if 0
  {
    unsigned char buf[16];
    
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), 0xFFFF-speedL);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)" ", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), 0xFFFF-speedR);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
  }
#endif
}

static void FollowLine(void) {
  uint16_t currLine;
  bool onLine;

  currLine = REF_GetLine(&onLine);
  if (!onLine) { /* no line => stop */
    MOT_SetSpeedPercent(&motorL, 0);
    MOT_SetSpeedPercent(&motorR, 0);
    return;
  }
  pidLine(currLine, 2500);
}

static void StateMachine(bool buttonPress) {
  switch (currState) {
  case STATE_INIT:
    if (buttonPress) {
      REF_Calibrate(TRUE);
      currState = STATE_CALIBRATE;
    }
    break;
  case STATE_CALIBRATE:
    if (buttonPress) {
      REF_Calibrate(FALSE);
      currState = STATE_STOP;
    }
    break;
  case STATE_RUN:
    FollowLine();
    if (buttonPress) {
      currState = STATE_STOP;
    }
    break;
  case STATE_STOP:
    MOT_SetSpeedPercent(&motorL, 0);
    MOT_SetSpeedPercent(&motorR, 0);
    if (buttonPress) {
      currState = STATE_RUN;
    }
    break;
  } /* switch */
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    LEDBY_Neg();
    if (SW3_GetVal()==0) {
      WAIT1_Waitms(50); /* simple debounce */
      if (SW3_GetVal()==0) { /* still pressed */
        LEDG_On();
        while(SW3_GetVal()==0) {
        } /* wait until released */
        LEDG_Off();
        StateMachine(TRUE);
      }
    }
    StateMachine(FALSE);
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  REF_Init();
  MOT_Init();
  SHELL_Init();
  BUZ_Init();
  LSM_Init();
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}

