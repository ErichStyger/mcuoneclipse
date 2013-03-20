/*
 * Turn.c
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */
#include "Turn.h"
#include "WAIT1.h"
#include "Motor.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "Reflectance.h"

#if PL_IS_ZUMO_ROBOT
#define TURN_90_WAIT_TIME_MS  550 
  /*!< ms to wait for a 90 degree turn */
#define TURN_STEP_MS  150
  /*!< ms to do one step forward */
#define TURN_TURN_PERCENT     40
  /*!< maximum motor duty for turn operation */
#else
#define TURN_90_WAIT_TIME_MS  180 
  /*!< ms to wait for a 90 degree turn */
#define TURN_STEP_MS  50 
  /*!< ms to do one step forward */
#define TURN_TURN_PERCENT     20
  /*!< maximum motor duty for turn operation */
#endif

#define TURN_WAIT_AFTER_STEP_MS  0 /*10*/  /* wait this time after a step to have the motor PWM effective */

static uint8_t TURN_DutyPercent = TURN_TURN_PERCENT;
static uint16_t TURN_TimeMs = TURN_90_WAIT_TIME_MS;
static uint16_t TURN_StepMs = TURN_STEP_MS;

/*!
 * \brief Translate a turn kind into a string
 * \return Returns a descriptive string
 */
const unsigned char *TURN_TurnKindStr(TURN_Kind kind) {
  switch(kind) {
    case TURN_LEFT90:     return (const unsigned char*)"LEFT90";
    case TURN_RIGHT90:    return (const unsigned char*)"RIGHT90";
    case TURN_LEFT180:    return (const unsigned char*)"LEFT180";
    case TURN_RIGHT180:   return (const unsigned char*)"RIGHT180";
    case TURN_STRAIGHT:   return (const unsigned char*)"STRAIGHT";
    case TURN_STEP_FW:    return (const unsigned char*)"STEP_FW";
    case TURN_STEP_BW:    return (const unsigned char*)"STEP_BW";
    case TURN_STOP:       return (const unsigned char*)"STOP";
    case TURN_FINISHED:   return (const unsigned char*)"FINISHED";
    default:              return (const unsigned char*)"TURN_UNKNOWN!";
  }
}

void TURN_Turn(TURN_Kind kind, bool toLine) {
#if 0
  uint16_t lineVal;
  bool online;
#endif
  
  switch(kind) {
    case TURN_LEFT90:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
#if 0
      if (toLine) {
        WAIT1_WaitOSms(TURN_TimeMs*2/3); /* turn half way */
        do {
          lineVal = REF_GetLineValue(&online);
        } while(lineVal>REF_MIDDLE_LINE_VALUE);
      } else {
        WAIT1_WaitOSms(TURN_TimeMs); /* only use waiting time */
      }
#else
      WAIT1_WaitOSms(TURN_TimeMs); /* only use waiting time */
#endif
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
      break;
    case TURN_RIGHT90:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
#if 0
      if (toLine) {
        WAIT1_WaitOSms(TURN_TimeMs*2/3); /* turn half way */
        do {
          lineVal = REF_GetLineValue(&online);
        } while(lineVal<REF_MIDDLE_LINE_VALUE);
      } else {
        WAIT1_WaitOSms(TURN_TimeMs); /* only use waiting time */
      }
#else
      WAIT1_WaitOSms(TURN_TimeMs); /* only use waiting time */
#endif
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
      break;
    case TURN_LEFT180:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
     break;
    case TURN_RIGHT180:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
     break;
    case TURN_STEP_FW:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
      break;
    case TURN_STEP_BW:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
      break;
    case TURN_STOP:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
      break;
  default:
    break;
  }
}

static void TURN_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"turn", (unsigned char*)"Group of turning commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows turn help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  left|right|around", (unsigned char*)"Turn the robot\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  duty <percent>", (unsigned char*)"Turning motor PWM duty percent\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  time <ms>", (unsigned char*)"Turning time in milli-seconds for 90 degrees\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  step <ms>", (unsigned char*)"Time in milli-seconds for a single step\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  forward", (unsigned char*)"Move one step forward\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  backward", (unsigned char*)"Move one step backward\r\n", io->stdOut);
}

static void TURN_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

  CLS1_SendStatusStr((unsigned char*)"turn", (unsigned char*)"\r\n", io->stdOut);

  buf[0] = '\0';
  UTIL1_strcatNum16u(buf, sizeof(buf), TURN_StepMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  step time", buf, io->stdOut);

  buf[0] = '\0';
  UTIL1_strcatNum16u(buf, sizeof(buf), TURN_TimeMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  turn time", buf, io->stdOut);

  buf[0] = '\0';
  UTIL1_strcatNum16u(buf, sizeof(buf), TURN_DutyPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr((unsigned char*)"  duty", buf, io->stdOut);
}


uint8_t TURN_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint8_t val8u;
  uint16_t val16u;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"turn help")==0) {
    TURN_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"turn status")==0) {
    TURN_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn left")==0) {
    TURN_Turn(TURN_LEFT90, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn right")==0) {
    TURN_Turn(TURN_RIGHT90, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn around")==0) {
    TURN_Turn(TURN_LEFT180, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn forward")==0) {
    REF_ClearHistory(); /* clear values */
    TURN_Turn(TURN_STEP_FW, FALSE);
    CLS1_SendStr((unsigned char*)REF_LineKindStr(REF_HistoryLineKind()), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn backward")==0) {
    TURN_Turn(TURN_STEP_BW, FALSE);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn duty ", sizeof("turn duty ")-1)==0) {
    p = cmd+sizeof("turn duty");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      TURN_DutyPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn time ", sizeof("turn time ")-1)==0) {
    p = cmd+sizeof("turn time");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_TimeMs = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn step ", sizeof("turn step ")-1)==0) {
    p = cmd+sizeof("turn step");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepMs = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

void TURN_Init(void) {
  TURN_DutyPercent = TURN_TURN_PERCENT;
  TURN_TimeMs = TURN_90_WAIT_TIME_MS;
  TURN_StepMs = TURN_STEP_MS;
}
