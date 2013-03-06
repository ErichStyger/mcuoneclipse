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
#include "WAIT1.h"
#include "SW1.h"

typedef enum {
  STATE_INIT,
  STATE_CALIBRATE,
  STATE_IDLE,
  STATE_FOLLOW,
  STATE_BRAKE,
} StateType;

static StateType currState = STATE_INIT;
#if PL_IS_ZUMO_ROBOT
#define LF_MAX_FORWARD 0xffff  /* max speed if 100% on the line, 0xffff would be full speed */
#define LF_MAX_WHEEL   0xffff  /* max correction speed, 0xffff would be full speed */
  static uint32_t pFactor100 = 25*100;
  static uint32_t dFactor100 = 60*100;
  static uint32_t iFactor100 = 1*100;
#else
  #define LF_MAX_FORWARD maxForward  /* max speed if 100% on the line, 0xffff would be full speed */
  #define LF_MAX_WHEEL   maxWheel  /* max correction speed, 0xffff would be full speed */
  static uint16_t maxForward = 5000;
  static uint16_t maxWheel = 10000;
  static int32_t pFactor100 = 120;
  static int32_t iFactor100 = 1;
  static int32_t dFactor100 = 30000;
  static int32_t iAntiWindup = 5000;
#endif
#define FORWARD_PWM_BASE_SPEED  (0xffff-LF_MAX_FORWARD) /* speed for each motor if 100% on line */ 
#define MAX_PWM_VALUE           (0xffff) /* maximum PWM value. This means here zero speed */
#define MIN_PWM_VALUE           (0xffff-LF_MAX_WHEEL) /* maximum wheel speed for corrections */

#define PID_DEBUG 1
static void pidLine(uint16_t currLine, uint16_t setLine) {
  int32_t error;
  static int32_t lastError=0, integral=0;
  int32_t motSpeed, speedL, speedR;
#if PID_DEBUG
  unsigned char buf[16];
#endif
  
  error = currLine-setLine; /* calculate error */
  motSpeed = (error*pFactor100)/100; /* P portion */
  integral += error; /* integrate error */
  if (integral>iAntiWindup) {
    integral = iAntiWindup;
  } else if (integral<-iAntiWindup) {
    integral = -iAntiWindup;
  }
  motSpeed += (integral*iFactor100)/100;
  motSpeed += ((error-lastError)*dFactor100)/100; /* D portion */
  lastError = error; /* remember for next iteration */
  /* transform into different speed for motors */
  speedL = FORWARD_PWM_BASE_SPEED+motSpeed;
  speedR = FORWARD_PWM_BASE_SPEED-motSpeed;
  /* make sure the actual PWM is within allowed speed range */
  if (speedL<MIN_PWM_VALUE) {
    speedL = MIN_PWM_VALUE;
  } else if (speedL>MAX_PWM_VALUE) {
    speedL = MAX_PWM_VALUE;
  }
  if (speedR<MIN_PWM_VALUE) {
    speedR = MIN_PWM_VALUE;
  } else if (speedR>MAX_PWM_VALUE) {
    speedR = MAX_PWM_VALUE;
  }
  /* send new speed values to motor */
  MOT_SetVal(&motorL, speedL);
  MOT_SetVal(&motorR, speedR);
#if PID_DEBUG /* debug diagnostic */
  {
    CLS1_SendStr((unsigned char*)"line:", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum16u(buf, sizeof(buf), currLine);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);

    CLS1_SendStr((unsigned char*)" sum:", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum32Hex(buf, sizeof(buf), integral);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);

    CLS1_SendStr((unsigned char*)" left:", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), 0xFFFF-speedL);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);

    CLS1_SendStr((unsigned char*)" right:", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), 0xFFFF-speedR);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
  }
#endif
}

static void ButtonPress(void) {
  switch (currState) {
  case STATE_INIT:
    REF_Calibrate(TRUE); /* blink RED during calibration */
    currState = STATE_CALIBRATE;
    break;
  case STATE_CALIBRATE:
    REF_Calibrate(FALSE);
    currState = STATE_IDLE;
    break;
  case STATE_IDLE:
    currState = STATE_FOLLOW;
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
  REF_LineKind lineKind;

  currLine = REF_GetLineValue(&onLine);
  lineKind = REF_GetLineKind();
#if 1
  CLS1_SendStr((unsigned char*)LF_LineKindStr(lineKind), CLS1_GetStdio()->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
#endif
  if (!onLine || lineKind==REF_LINE_NONE) { /* not calibrated or no line => stop */
    currState = STATE_BRAKE;
    StateMachine(); /* need to handle new state asap */
    return;
  }
  pidLine(currLine, REF_MAX_LINE_VALUE/2);
}

static void StateMachine(void) {
  switch (currState) {
  case STATE_INIT:
    LEDG_Off();
    LEDR_On();
    break;
  case STATE_CALIBRATE:
    LEDR_Neg();
    WAIT1_Waitms(500);
    if (!REF_IsCalibrating()) {
      currState = STATE_IDLE;
    }
    break;
  case STATE_IDLE:
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
    MOT_SetSpeedPercent(&motorL, 0);
    MOT_SetSpeedPercent(&motorR, 0);
    currState = STATE_IDLE;
    break;
  } /* switch */
}

static portTASK_FUNCTION(LineTask, pvParameters) {
  uint32_t cnt;
  
  (void)pvParameters; /* not used */
  for(;;) {
#if 1 /* use button */
    if (SW1_GetVal()==0) {
      WAIT1_Waitms(50); /* simple debounce */
      if (SW1_GetVal()==0) { /* still pressed */
        LEDG_On();
        cnt = 0;
        while(SW1_GetVal()==0) {
          WAIT1_Waitms(1);
          cnt++;
        } /* wait until released */
        if (cnt>1000) {
          /* long press, calibrate again */
          currState = STATE_INIT;
        }
        ButtonPress();
      }
    }
#endif
    if (REF_IsCalibrating()) {
      currState = STATE_CALIBRATE;
    }
    StateMachine();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static void LF_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"line", (unsigned char*)"Group of line following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop|calibrate", (unsigned char*)"Enables or disables motor\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  forward <value>", (unsigned char*)"Maximum forward speed\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  wheel <value>", (unsigned char*)"Maximum wheel speed\r\n", io->stdOut);
}

static void LF_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

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
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"p: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), pFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" i: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), iFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" d: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), dFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  PID", buf, io->stdOut);

  buf[0]='\0';
  UTIL1_strcatNum32s(buf, sizeof(buf), iAntiWindup);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  anti-windup", buf, io->stdOut);

  buf[0]='\0';
  UTIL1_strcatNum16u(buf, sizeof(buf), maxForward);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  max forward", buf, io->stdOut);

  buf[0]='\0';
  UTIL1_strcatNum16u(buf, sizeof(buf), maxWheel);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  max wheel", buf, io->stdOut);
}

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint32_t val32u;
  uint16_t val16u;

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
    currState = STATE_FOLLOW;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line stop")==0) {
    currState = STATE_BRAKE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line p", sizeof("line p")-1)==0) {
    p = cmd+sizeof("line p");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      pFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line i", sizeof("line i")-1)==0) {
    p = cmd+sizeof("line i");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line d", sizeof("line d")-1)==0) {
    p = cmd+sizeof("line d");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      dFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line w", sizeof("line d")-1)==0) {
    p = cmd+sizeof("line w");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iAntiWindup = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line forward", sizeof("line forward")-1)==0) {
    p = cmd+sizeof("line forward");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      maxForward = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"line wheel", sizeof("line wheel")-1)==0) {
    p = cmd+sizeof("line wheel");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      maxWheel = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

void LF_Init(void) {
  currState = STATE_INIT;
  if (FRTOS1_xTaskCreate(LineTask, (signed portCHAR *)"Line", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
