/*
 * Turn.c
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Turn.h"
#include "WAIT1.h"
#include "Motor.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "Reflectance.h"
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
  #include "Pid.h"
#endif

#if PL_IS_ZUMO_ROBOT
  #define TURN_90_WAIT_TIME_MS       550 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_MS                170
    /*!< ms to do one step forward */
  #define TURN_MOTOR_DUTY_PERCENT      40
    /*!< maximum motor duty for turn operation */
#else
  #define TURN_90_WAIT_TIME_MS        250 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_MS                100 
    /*!< ms to do one step forward */
  #define TURN_MOTOR_DUTY_PERCENT      20
    /*!< maximum motor duty for turn operation */
#endif
#if PL_HAS_QUADRATURE
  #define TURN_STEPS_90      20
    /*!< number of steps for a 90 degree turn */
  #define TURN_STEPS_FW_BW   20
    /*!< number of steps for one inch forward/backward */
#endif

#if PL_IS_ZUMO_ROBOT
  #define TURN_WAIT_AFTER_STEP_MS  0   /* wait this time after a step to have the motor PWM effective, 0 for now wait */
  #define TURN_STOP_AFTER_TURN     0   /* 1 to stop after a turn */
#else
  #define TURN_WAIT_AFTER_STEP_MS  50  /* wait this time after a step to have the motor PWM effective */
  #define TURN_STOP_AFTER_TURN     1   /* 1 to stop after a turn */
#endif

#if PL_HAS_QUADRATURE
static uint16_t TURN_Steps90 = TURN_STEPS_90;
static uint16_t TURN_StepsFwBw = TURN_STEPS_FW_BW;
#else
static uint8_t TURN_DutyPercent = TURN_MOTOR_DUTY_PERCENT;
static uint16_t TURN_Time90ms = TURN_90_WAIT_TIME_MS;
static uint16_t TURN_StepFwBwMs = TURN_STEP_MS;
#endif

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

#if PL_HAS_QUADRATURE
static bool match(int16_t pos, int16_t target) {
  #define MATCH_MARGIN 1
  return (pos>=target-MATCH_MARGIN && pos<=target+MATCH_MARGIN);
}

void TURN_TurnSteps(int16_t stepsL, int16_t stepsR) {
  int16_t currLPos, currRPos, targetLPos, targetRPos;
  uint8_t matchCntr = 100;
  
  currLPos = Q4CLeft_GetPos();
  targetLPos = currLPos+stepsL;
  currRPos = Q4CRight_GetPos();
  targetRPos = currRPos+stepsR;
  for(;;) { /* breaks */
    if (match(currLPos,targetLPos) && match(currRPos,targetRPos)) {
      matchCntr--;
      if (matchCntr==0) {
        break; /* get out of loop */
      }
    }
    PID_Pos(Q4CLeft_GetPos(), targetLPos, TRUE);
    PID_Pos(Q4CRight_GetPos(), targetRPos, FALSE);
    WAIT1_WaitOSms(2);
    currLPos = Q4CLeft_GetPos();
    currRPos = Q4CRight_GetPos();
  } /* for */
}
#endif

void TURN_Turn(TURN_Kind kind) {
  switch(kind) {
    case TURN_LEFT90:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(-TURN_Steps90, TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_Time90ms); /* only use waiting time */
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
      break;
    case TURN_RIGHT90:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(TURN_Steps90, -TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_Time90ms); /* only use waiting time */
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
      break;
    case TURN_LEFT180:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(-(2*TURN_Steps90), 2*TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_Time90ms);
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
     break;
    case TURN_RIGHT180:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(2*TURN_Steps90, -(2*TURN_Steps90));
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_Time90ms);
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
     break;
    case TURN_STEP_FW:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(TURN_StepsFwBw, TURN_StepsFwBw);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepFwBwMs);
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
      break;
    case TURN_STEP_BW:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(-TURN_StepsFwBw, -TURN_StepsFwBw);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepFwBwMs);
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
#endif
      break;
    case TURN_STEP_BW_SMALL:
#if PL_HAS_QUADRATURE
      TURN_TurnSteps(-TURN_StepsFwBw/2, -TURN_StepsFwBw/2);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepFwBwMs/2);
#endif
#if TURN_STOP_AFTER_TURN
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#if TURN_WAIT_AFTER_STEP_MS > 0
      WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
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
  CLS1_SendHelpStr((unsigned char*)"  forward", (unsigned char*)"Move one step forward\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  backward", (unsigned char*)"Move one step backward\r\n", io->stdOut);
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  steps90 <steps>", (unsigned char*)"Number of steps for a 90 degree turn\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  stepsfw <steps>", (unsigned char*)"Number of steps for a step forward or backward\r\n", io->stdOut);
#else
  CLS1_SendHelpStr((unsigned char*)"  duty <percent>", (unsigned char*)"Turning motor PWM duty percent\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  time90 <ms>", (unsigned char*)"Time in milli-seconds for 90 degree\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  timefw <ms>", (unsigned char*)"Time in milli-seconds for a single step forward or backward\r\n", io->stdOut);
#endif
}

static void TURN_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

  CLS1_SendStatusStr((unsigned char*)"turn", (unsigned char*)"\r\n", io->stdOut);

#if PL_HAS_QUADRATURE
  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_Steps90);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  CLS1_SendStatusStr((unsigned char*)"  steps90", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepsFwBw);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  CLS1_SendStatusStr((unsigned char*)"  stepsfw", buf, io->stdOut);

  UTIL1_Num16sToStr(buf, sizeof(buf), Q4CLeft_GetPos());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
  UTIL1_strcatNum16u(buf, sizeof(buf), Q4CLeft_NofErrors());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" errors\r\n");
  CLS1_SendStatusStr((unsigned char*)"  left pos", buf, io->stdOut);
  
  UTIL1_Num16sToStr(buf, sizeof(buf), Q4CRight_GetPos());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
  UTIL1_strcatNum16u(buf, sizeof(buf), Q4CRight_NofErrors());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" errors\r\n");
  CLS1_SendStatusStr((unsigned char*)"  right pos", buf, io->stdOut);
#else
  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_DutyPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr((unsigned char*)"  duty", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_Time90ms);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  time90", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepFwBwMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  timefw", buf, io->stdOut);
#endif
}

uint8_t TURN_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
#if !PL_HAS_QUADRATURE
  uint8_t val8u;
#endif
  uint16_t val16u;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"turn help")==0) {
    TURN_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"turn status")==0) {
    TURN_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn left")==0) {
    TURN_Turn(TURN_LEFT90);
    TURN_Turn(TURN_STOP);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn right")==0) {
    TURN_Turn(TURN_RIGHT90);
    TURN_Turn(TURN_STOP);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn around")==0) {
    TURN_Turn(TURN_LEFT180);
    TURN_Turn(TURN_STOP);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn forward")==0) {
    REF_ClearHistory(); /* clear values */
    TURN_Turn(TURN_STEP_FW);
    TURN_Turn(TURN_STOP);
    CLS1_SendStr((unsigned char*)REF_LineKindStr(REF_HistoryLineKind()), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn backward")==0) {
    TURN_Turn(TURN_STEP_BW);
    TURN_Turn(TURN_STOP);
    *handled = TRUE;
#if PL_HAS_QUADRATURE
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn steps90 ", sizeof("turn steps90 ")-1)==0) {
    p = cmd+sizeof("turn steps90");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_Steps90 = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn stepsfw ", sizeof("turn stepsfw ")-1)==0) {
    p = cmd+sizeof("turn stepsfw");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepsFwBw = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#else
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn duty ", sizeof("turn duty ")-1)==0) {
    p = cmd+sizeof("turn duty");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      TURN_DutyPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn time90 ", sizeof("turn time90 ")-1)==0) {
    p = cmd+sizeof("turn time90");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_Time90ms = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn timefw ", sizeof("turn timefw ")-1)==0) {
    p = cmd+sizeof("turn timefw");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepFwBwMs = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
  }
  return res;
}

void TURN_Init(void) {
#if PL_HAS_QUADRATURE
  TURN_Steps90 = TURN_STEPS_90;
  TURN_StepsFwBw = TURN_StepsFwBw;
#else
  TURN_DutyPercent = TURN_MOTOR_DUTY_PERCENT;
  TURN_Time90ms = TURN_90_WAIT_TIME_MS;
  TURN_StepFwBwMs = TURN_STEP_MS;
#endif
}
