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

#if PL_IS_ZUMO_ROBOT
#define TURN_90_WAIT_TIME_MS  500 
  /*!< ms to wait for a 90 degree turn */
#define TURN_STEP_MS  150 
  /*!< ms to do one step forward */
#define TURN_TURN_PERCENT     55
  /*!< maximum motor duty for turn operation */
#else
#define TURN_90_WAIT_TIME_MS  180 
  /*!< ms to wait for a 90 degree turn */
#define TURN_STEP_MS  50 
  /*!< ms to do one step forward */
#define TURN_TURN_PERCENT     20
  /*!< maximum motor duty for turn operation */
#endif

static uint8_t TURN_DutyPercent = TURN_TURN_PERCENT;
static uint16_t TURN_TimeMs = TURN_90_WAIT_TIME_MS;
static uint16_t TURN_StepMs = TURN_STEP_MS;

TURN_Kind TURN_SelectTurn(REF_LineKind line) {
  /* implements left-hand-on-the-wall strategy */
  switch(line) {
    case REF_LINE_FORWARD:
      return TURN_STRAIGHT;
    case REF_LINE_LEFT:
      return TURN_LEFT90;
    case REF_LINE_RIGHT:
      return TURN_RIGHT90;
    case REF_LINE_NONE:
      return TURN_LEFT180;
    case REF_LINE_FULL:
    case REF_LINE_AIR:
    default:
      return TURN_STOP;
  }
  return TURN_STOP;
}

void TURN_Turn(TURN_Kind kind) {
  switch(kind) {
    case TURN_LEFT90:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      break;
    case TURN_RIGHT90:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      break;
    case TURN_LEFT180:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
     break;
    case TURN_RIGHT180:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_TimeMs);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
     break;
  default:
    break;
  }
}

void TURN_StepForward(void) {
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
  WAIT1_WaitOSms(TURN_StepMs);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
}

void TURN_StepBackward(void) {
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
  WAIT1_WaitOSms(TURN_StepMs);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
}


static void TURN_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"turn", (unsigned char*)"Group of turning commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows turn help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  left|right|around", (unsigned char*)"Turn the robot\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  duty <percent>", (unsigned char*)"Turning motor PWM duty percent\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  turn time <ms>", (unsigned char*)"Turning time in milli-seconds for 90 degrees\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  step time <ms>", (unsigned char*)"Time in milli-seconds for a single step\r\n", io->stdOut);
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
    TURN_Turn(TURN_LEFT90);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn right")==0) {
    TURN_Turn(TURN_RIGHT90);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn around")==0) {
    TURN_Turn(TURN_LEFT180);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"forward")==0) {
    TURN_StepForward();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"backward")==0) {
    TURN_StepBackward();
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
  } else if (UTIL1_strncmp((char*)cmd, (char*)"step time ", sizeof("step time ")-1)==0) {
    p = cmd+sizeof("step time");
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
