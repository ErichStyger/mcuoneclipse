/*
 * Turn.c
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_TURN
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
  #define TURN_90_WAIT_TIME_MS        460 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_LINE_MS            90
    /*!< ms to do a step over the line */
  #define TURN_STEP_POST_LINE_MS       60
    /*!< ms to do a step over the line */
  #define TURN_MOTOR_DUTY_PERCENT      50
    /*!< maximum motor duty for turn operation */
#elif PL_IS_ROUND_ROBOT
  #define TURN_90_WAIT_TIME_MS        250 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_LINE_MS            50
    /*!< ms to do a step over the line */
  #define TURN_STEP_POST_LINE_MS       50
    /*!< ms to do a step over the line */
  #define TURN_MOTOR_DUTY_PERCENT      20
    /*!< maximum motor duty for turn operation */
#elif PL_IS_TRACK_ROBOT
  #define TURN_90_WAIT_TIME_MS       1050 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_LINE_MS           160
    /*!< ms to do a step over the line */
  #define TURN_STEP_POST_LINE_MS      170
    /*!< ms to do a step over the line */
  #define TURN_MOTOR_DUTY_PERCENT      25
    /*!< maximum motor duty for turn operation */
#elif PL_IS_INTRO_ZUMO_ROBOT
  #define TURN_90_WAIT_TIME_MS        470 
    /*!< ms to wait for a 90 degree turn */
  #define TURN_STEP_LINE_MS            80
    /*!< ms to do a step over the line */
  #define TURN_STEP_POST_LINE_MS       90
    /*!< ms to do a step over the line */
  #define TURN_MOTOR_DUTY_PERCENT      40
    /*!< maximum motor duty for turn operation */
#else
  #error "unknown configuration!"
#endif
#if PL_HAS_QUADRATURE
#if PL_IS_ROUND_ROBOT
  #define TURN_STEPS_90      20
    /*!< number of steps for a 90 degree turn */
  #define TURN_STEPS_FW_BW   20
    /*!< number of steps for one inch forward/backward */
#elif PL_IS_INTRO_ZUMO_ROBOT
  #define TURN_STEPS_90         34
    /*!< number of steps for a 90 degree turn */
  #define TURN_STEPS_LINE       12
    /*!< number of steps stepping over the line */
  #define TURN_STEPS_POST_LINE  7
    /*!< number of steps after the line, before making a turn */
#else
  #error "unknown configuration!"
#endif
#endif

#if PL_IS_ZUMO_ROBOT
  #define TURN_WAIT_AFTER_STEP_MS  0   /* wait this time after a step to have the motor PWM effective */
#elif PL_IS_ROUND_ROBOT
  #define TURN_WAIT_AFTER_STEP_MS  50  /* wait this time after a step to have the motor PWM effective */
#elif PL_IS_TRACK_ROBOT
  #define TURN_WAIT_AFTER_STEP_MS  50  /* wait this time after a step to have the motor PWM effective */
#elif PL_IS_INTRO_ZUMO_ROBOT
  #define TURN_WAIT_AFTER_STEP_MS  0   /* wait this time after a step to have the motor PWM effective */
#else
  #error "unknown configuration!"
#endif

#if PL_HAS_QUADRATURE
static uint16_t TURN_Steps90 = TURN_STEPS_90;
static uint16_t TURN_StepsLine = TURN_STEPS_LINE;
static uint16_t TURN_StepsPostLine = TURN_STEPS_POST_LINE;
#else
static uint8_t TURN_DutyPercent = TURN_MOTOR_DUTY_PERCENT;
static uint16_t TURN_Time90ms = TURN_90_WAIT_TIME_MS;
static uint16_t TURN_StepLineMs = TURN_STEP_LINE_MS;
static uint16_t TURN_StepPostLineMs = TURN_STEP_POST_LINE_MS;
#endif

/*!
 * \brief Translate a turn kind into a string
 * \return Returns a descriptive string
 */
const unsigned char *TURN_TurnKindStr(TURN_Kind kind) {
  switch(kind) {
    case TURN_LEFT45:             return (const unsigned char*)"LEFT45";
    case TURN_LEFT90:             return (const unsigned char*)"LEFT90";
    case TURN_RIGHT45:            return (const unsigned char*)"RIGHT45";
    case TURN_RIGHT90:            return (const unsigned char*)"RIGHT90";
    case TURN_LEFT180:            return (const unsigned char*)"LEFT180";
    case TURN_RIGHT180:           return (const unsigned char*)"RIGHT180";
    case TURN_STRAIGHT:           return (const unsigned char*)"STRAIGHT";
    case TURN_STEP_LINE_FW:       return (const unsigned char*)"STEP_LINE_FW";
    case TURN_STEP_LINE_BW:       return (const unsigned char*)"STEP_LINE_BW";
    case TURN_STEP_POST_LINE_FW:  return (const unsigned char*)"STEP_POST_LINE_FW";
    case TURN_STEP_POST_LINE_BW:  return (const unsigned char*)"STEP_POST_LINE_BW";
    case TURN_STOP:               return (const unsigned char*)"STOP";
    case TURN_FINISHED:           return (const unsigned char*)"FINISHED";
    default:                      return (const unsigned char*)"TURN_UNKNOWN!";
  }
}

#if PL_HAS_QUADRATURE
static bool match(int16_t pos, int16_t target) {
  #define MATCH_MARGIN 0
  return (pos>=target-MATCH_MARGIN && pos<=target+MATCH_MARGIN);
}

static void MoveToPos(int16_t targetLPos, int16_t targetRPos) {
  int16_t currLPos, currRPos;
  uint8_t matchLCntr = 16, matchRCntr = 16;
  
  for(;;) { /* breaks */
    currLPos = Q4CLeft_GetPos();
    currRPos = Q4CRight_GetPos();
    if (matchLCntr>0) {
      if (match(currLPos,targetLPos)) {
        matchLCntr--;
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      } else {
        PID_Pos(Q4CLeft_GetPos(), targetLPos, TRUE);
      }
    }
    if (matchRCntr>0) {
      if (match(currRPos,targetRPos)) {
        matchRCntr--;
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      } else {
        PID_Pos(Q4CRight_GetPos(), targetRPos, FALSE);
      }
    }
    if (matchLCntr==0 && matchRCntr==0) {
      break; /* get out of loop */
    }
  } /* for */
}

static void StepsTurn(int16_t stepsL, int16_t stepsR) {
  int16_t currLPos, currRPos, targetLPos, targetRPos;
  int i;
  
  currLPos = Q4CLeft_GetPos();
  targetLPos = currLPos+stepsL;
  currRPos = Q4CRight_GetPos();
  targetRPos = currRPos+stepsR;
  if (stepsL>16 || stepsR>16) { /* do in smaller incremental steps */
    for(i=0;i<16;i++) {
      currLPos += stepsL/16;
      currRPos += stepsR/16;
      MoveToPos(currLPos, currRPos);
    }
  }
  MoveToPos(targetLPos, targetRPos); /* go to final position */
}
#endif

static void PostTurn(void) {
#if !PL_HAS_QUADRATURE /* with quadrature counter we already stopped the motors */
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#endif
#if TURN_WAIT_AFTER_STEP_MS > 0
  WAIT1_WaitOSms(TURN_WAIT_AFTER_STEP_MS);
#endif
}

#if !PL_HAS_QUADRATURE
static void TimeTurn(bool isLeft, uint8_t duty, uint16_t val) {
  if (isLeft) {
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -duty);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), duty);
  } else {
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT),   duty);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -duty);
  }
  WAIT1_WaitOSms(val); /* waiting time */
}
#endif

void TURN_Turn(TURN_Kind kind) {
  switch(kind) {
    case TURN_LEFT45:
#if PL_HAS_QUADRATURE
      StepsTurn(-TURN_Steps90/2, TURN_Steps90/2);
#else
      TimeTurn(TRUE, TURN_DutyPercent, TURN_Time90ms/2);
#endif
      break;
    case TURN_RIGHT45:
#if PL_HAS_QUADRATURE
      StepsTurn(TURN_Steps90/2, -TURN_Steps90/2);
#else
      TimeTurn(FALSE, TURN_DutyPercent, TURN_Time90ms/2);
#endif
      break;
    case TURN_LEFT90:
#if PL_HAS_QUADRATURE
      StepsTurn(-TURN_Steps90, TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_Time90ms); /* only use waiting time */
#endif
      break;
    case TURN_RIGHT90:
#if PL_HAS_QUADRATURE
      StepsTurn(TURN_Steps90, -TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_Time90ms); /* only use waiting time */
#endif
      break;
    case TURN_LEFT180:
#if PL_HAS_QUADRATURE
      StepsTurn(-(2*TURN_Steps90), 2*TURN_Steps90);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_Time90ms);
#endif
     break;
    case TURN_RIGHT180:
#if PL_HAS_QUADRATURE
      StepsTurn(2*TURN_Steps90, -(2*TURN_Steps90));
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(2*TURN_Time90ms);
#endif
     break;
    case TURN_STEP_LINE_FW:
#if PL_HAS_QUADRATURE
      StepsTurn(TURN_StepsLine, TURN_StepsLine);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepLineMs);
#endif
      break;
    case TURN_STEP_LINE_BW:
#if PL_HAS_QUADRATURE
      StepsTurn(-TURN_StepsLine, -TURN_StepsLine);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepLineMs);
#endif
      break;
    case TURN_STEP_POST_LINE_FW:
#if PL_HAS_QUADRATURE
      StepsTurn(TURN_StepsPostLine, TURN_StepsPostLine);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepPostLineMs);
#endif
      break;
    case TURN_STEP_POST_LINE_BW:
#if PL_HAS_QUADRATURE
      StepsTurn(-TURN_StepsPostLine, -TURN_StepsPostLine);
#else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
      WAIT1_WaitOSms(TURN_StepPostLineMs);
#endif
      break;
    case TURN_STOP_LEFT:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      break;
    case TURN_STOP_RIGHT:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      break;
    case TURN_STOP:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      break;
  default:
    break;
  }
  PostTurn(); /* perform post-turn action */
}

void TURN_TurnAngle(int16_t angle) {
  bool isLeft = angle<0;
#if PL_HAS_QUADRATURE
  uint32_t steps;
#else
  uint32_t time;
#endif
  
  if (isLeft) {
    angle = -angle; /* make it positive */
  }
  angle %= 360; /* keep it inside 360° */
#if PL_HAS_QUADRATURE
  steps = (angle*TURN_Steps90)/90;
#else
  time = (angle*TURN_Time90ms)/90;
#endif
  if (isLeft) {
#if PL_HAS_QUADRATURE
    StepsTurn(-steps, steps);
#else
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -TURN_DutyPercent);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TURN_DutyPercent);
    WAIT1_WaitOSms(time);
#endif
  } else { /* right */
#if PL_HAS_QUADRATURE
    StepsTurn(steps, -steps);
#else
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TURN_DutyPercent);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -TURN_DutyPercent);
    WAIT1_WaitOSms(time);
#endif
  }
  PostTurn(); /* perform post-turn action */
}

static void TURN_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"turn", (unsigned char*)"Group of turning commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows turn help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  <angle>", (unsigned char*)"Turn the robot by angle, negative is counter-clockwise, e.g. 'turn -90'\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  forward", (unsigned char*)"Move one step forward\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  backward", (unsigned char*)"Move one step backward\r\n", io->stdOut);
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  steps90 <steps>", (unsigned char*)"Number of steps for a 90 degree turn\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  stepsline <steps>", (unsigned char*)"Number of steps for stepping over line\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  stepspostline <steps>", (unsigned char*)"Number of steps for a step post the line\r\n", io->stdOut);
#else
  CLS1_SendHelpStr((unsigned char*)"  duty <percent>", (unsigned char*)"Turning motor PWM duty percent\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  time90 <ms>", (unsigned char*)"Time in milli-seconds for 90 degree\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  timeline <ms>", (unsigned char*)"Time in milli-seconds for a single line step\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  timepostline <ms>", (unsigned char*)"Time in milli-seconds for a step post the line\r\n", io->stdOut);
#endif
}

static void TURN_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

  CLS1_SendStatusStr((unsigned char*)"turn", (unsigned char*)"\r\n", io->stdOut);
#if PL_HAS_QUADRATURE
  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_Steps90);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  CLS1_SendStatusStr((unsigned char*)"  90°", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepsLine);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  CLS1_SendStatusStr((unsigned char*)"  line", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepsPostLine);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  CLS1_SendStatusStr((unsigned char*)"  postline", buf, io->stdOut);

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

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepLineMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  line", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), TURN_StepPostLineMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  postline", buf, io->stdOut);
#endif
}

static bool isNumberStart(uint8_t ch) {
  if (ch=='-') { /* negative number start */
    return TRUE;
  } else if (ch>='0' && ch<='9') {
    return TRUE;
  }
  return FALSE;
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
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn ", sizeof("turn ")-1)==0 && isNumberStart(cmd[sizeof("turn ")-1])) {
    int32_t angle;

    p = cmd+sizeof("turn ")-1;
    if (UTIL1_xatoi(&p, &angle)==ERR_OK) {
      TURN_TurnAngle((int16_t)angle);
      TURN_Turn(TURN_STOP);
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn forward")==0) {
#if PL_APP_LINE_MAZE
    REF_ClearHistory(); /* clear values */
#endif
    TURN_Turn(TURN_STEP_LINE_FW);
    TURN_Turn(TURN_STOP);
#if PL_APP_LINE_MAZE
    CLS1_SendStr((unsigned char*)REF_LineKindStr(REF_HistoryLineKind()), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
#endif
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"turn backward")==0) {
    TURN_Turn(TURN_STEP_LINE_BW);
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
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn stepspostline ", sizeof("turn stepspostline ")-1)==0) {
    p = cmd+sizeof("turn stepspostline");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepsPostLine = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn stepsline ", sizeof("turn stepsline ")-1)==0) {
    p = cmd+sizeof("turn stepsline");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepsLine = val16u;
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
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn timeline ", sizeof("turn timeline ")-1)==0) {
    p = cmd+sizeof("turn timeline");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepLineMs = val16u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"turn timepostline ", sizeof("turn timepostline ")-1)==0) {
    p = cmd+sizeof("turn timepostline");
    if (UTIL1_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      TURN_StepPostLineMs = val16u;
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
  TURN_StepsPostLine = TURN_STEPS_POST_LINE;
  TURN_StepsLine = TURN_STEPS_LINE;
#else
  TURN_DutyPercent = TURN_MOTOR_DUTY_PERCENT;
  TURN_Time90ms = TURN_90_WAIT_TIME_MS;
  TURN_StepLineMs = TURN_STEP_LINE_MS;
  TURN_StepPostLineMs = TURN_STEP_POST_LINE_MS;
#endif
}
#endif /* PL_HAS_TURN */
