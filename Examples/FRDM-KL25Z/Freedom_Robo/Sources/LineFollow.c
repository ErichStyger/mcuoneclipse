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
#include "Maze.h"
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif

#define LINE_DEBUG   1   /* careful: this will slow down the PID loop frequency! */

typedef enum {
  STATE_IDLE,
  STATE_FOLLOW_SEGMENT,
  STATE_TURN,
  STATE_FINISHED,
  STATE_STOP
} StateType;

static volatile StateType LF_currState = STATE_IDLE;
static volatile bool LF_stopIt = FALSE;
static uint8_t LF_solvedIdx = 0; /*  index to iterate through the solution */

void LF_StartFollowing(void) {
  if (!MAZE_IsSolved()) {
    MAZE_Init();
  } else {
    LF_solvedIdx = 0;
  }
  PID_Init();
  if (REF_CanUseSensor()) {
    LF_currState = STATE_FOLLOW_SEGMENT;
  } else {
    CLS1_SendStr((unsigned char*)"Sensors not ready!\r\n", CLS1_GetStdio()->stdOut);
  }
}

void LF_StopFollowing(void) {
  LF_stopIt = TRUE;
  LF_currState = STATE_IDLE;
}

static void StateMachine(void);

static void ChangeState(StateType newState) {
  LF_currState = newState;
  StateMachine(); /* need to handle new state */
}

/*!
 * \brief follows a line segment.
 * \return Returns TRUE if still on line segment
 */
static bool FollowSegment(void) {
  uint16_t currLine;
  bool onLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue(&onLine);
  currLineKind = REF_GetLineKind();
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, REF_MIDDLE_LINE_VALUE); /* move forward on the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

/*!
 * \brief Performs a turn.
 * \return Returns TRUE while turn is still in progress.
 */
static uint8_t EvaluteTurn(bool *finished) {
  REF_LineKind historyLineKind, currLineKind;
  TURN_Kind turn;
  
  *finished = FALSE; /* defaults */
  REF_ClearHistory(); /* clear values */
  REF_SampleHistory(); /* store current values */
  TURN_Turn(TURN_STEP_FW); /* make forward step */
  historyLineKind = REF_HistoryLineKind(); /* new read new values */
  currLineKind = REF_GetLineKind();
#if LINE_DEBUG
  REF_DumpHistory();
  CLS1_SendStr((unsigned char*)" history: ", CLS1_GetStdio()->stdOut);
  CLS1_SendStr((unsigned char*)REF_LineKindStr(historyLineKind), CLS1_GetStdio()->stdOut);
  CLS1_SendStr((unsigned char*)" curr: ", CLS1_GetStdio()->stdOut);
  CLS1_SendStr((unsigned char*)REF_LineKindStr(currLineKind), CLS1_GetStdio()->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
#endif
  turn = MAZE_SelectTurn(historyLineKind, currLineKind);
  if (turn==TURN_FINISHED) {
    *finished = TRUE;
    ChangeState(STATE_STOP);
    CLS1_SendStr((unsigned char*)"finished!\r\n", CLS1_GetStdio()->stdOut);
    return ERR_OK;
  } else if (turn==TURN_STRAIGHT) {
    MAZE_AddPath(turn);
    MAZE_SimplifyPath();
    CLS1_SendStr((unsigned char*)"going straight\r\n", CLS1_GetStdio()->stdOut);
    return ERR_OK; 
  } else if (turn==TURN_STOP) { /* should not happen here? */
    ChangeState(STATE_STOP);
    CLS1_SendStr((unsigned char*)"stopped\r\n", CLS1_GetStdio()->stdOut);
    return ERR_FAILED; /* error case */
  } else { /* turn or do something */
#if LINE_DEBUG
    CLS1_SendStr((unsigned char*)"turning ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)TURN_TurnKindStr(turn), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
#endif
    TURN_Turn(turn); /* make turn */
    MAZE_AddPath(turn);
    MAZE_SimplifyPath();
    return ERR_OK; /* turn finished */
  }
}

static void StateMachine(void) {
  bool finished=FALSE;
  
  switch (LF_currState) {
    case STATE_IDLE:
      break;
    case STATE_FOLLOW_SEGMENT:
      if (!FollowSegment()) {
        LF_currState = STATE_TURN;
      }
      break;
    case STATE_TURN:
      if (MAZE_IsSolved()) {
        TURN_Kind turn;
        
        turn = MAZE_GetSolvedTurn(&LF_solvedIdx);
        if (turn==TURN_STOP) { /* last turn reached */
          TURN_Turn(turn);
          LF_currState = STATE_FINISHED;
        } else { /* perform turning */
          TURN_Turn(TURN_STEP_FW); /* need to do this in order to turn on the middle of the intersection */
          TURN_Turn(turn);
          LF_currState = STATE_FOLLOW_SEGMENT;
        }
      } else { /* still evaluating maze */
        if (EvaluteTurn(&finished)==ERR_OK) { /* finished turning */
          if (finished) {
            LF_currState = STATE_FINISHED;
            MAZE_SetSolved();
#if PL_TURN_ON_FINISH
            /* turn the robot */
            TURN_Turn(TURN_LEFT180);
#endif
            TURN_Turn(TURN_STOP);
            /* now ready to do line following */
          } else {
            LF_currState = STATE_FOLLOW_SEGMENT;
          }
        } else { /* error case */
          LF_currState = STATE_STOP;
        }
      }
      break;
    case STATE_FINISHED:
#if PL_HAS_BUZZER
      {
        uint8_t i;
        
        for(i=0;i<4;i++) {
          BUZ_Beep(300, 100);
          WAIT1_WaitOSms(500);
        }
      }
#endif
      LF_currState = STATE_STOP;
      break;
    case STATE_STOP:
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      LF_currState = STATE_IDLE;
      break;
  } /* switch */
}

bool LF_IsFollowing(void) {
  return LF_currState==STATE_FOLLOW_SEGMENT || LF_currState==STATE_TURN || LF_currState==STATE_FINISHED;
}

static portTASK_FUNCTION(LineTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (LF_stopIt) {
      ChangeState(STATE_STOP);
      LF_stopIt = FALSE;
    }
    if (LF_IsFollowing()) {
      StateMachine();
      FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
    } else {
      FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
    }
  }
}

static void LF_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"line", (unsigned char*)"Group of line following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop", (unsigned char*)"Starts or stops line following\r\n", io->stdOut);
}

static void LF_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"line follow", (unsigned char*)"\r\n", io->stdOut);
  switch (LF_currState) {
    case STATE_IDLE: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"IDLE\r\n", io->stdOut);
      break;
    case STATE_FOLLOW_SEGMENT: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FOLLOW_SEGMENT\r\n", io->stdOut);
      break;
    case STATE_TURN: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"TURN\r\n", io->stdOut);
      break;
    case STATE_STOP: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"STOP\r\n", io->stdOut);
      break;
    case STATE_FINISHED: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FINISHED\r\n", io->stdOut);
      break;
    default: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"UNKNOWN\r\n", io->stdOut);
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
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line start")==0) {
    LF_StartFollowing();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line stop")==0) {
    LF_StopFollowing();
    *handled = TRUE;
  }
  return res;
}

void LF_Init(void) {
  LF_currState = STATE_IDLE;
  if (FRTOS1_xTaskCreate(LineTask, (signed portCHAR *)"Line", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
