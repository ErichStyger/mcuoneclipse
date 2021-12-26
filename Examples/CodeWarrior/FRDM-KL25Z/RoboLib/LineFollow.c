/*
 * LineFollow.c
 *
 *  Created on: Feb 15, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_LINE_SENSOR
#include "LineFollow.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LEDR.h"
#include "LEDG.h"
#include "Turn.h"
#include "WAIT1.h"
#include "Pid.h"
#include "Turn.h"
#include "Maze.h"
#include "UTIL1.h"
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif

#define LINE_DEBUG      1   /* careful: this will slow down the PID loop frequency! */
#define LINE_FOLLOW_FW  1   /* test setting to do forward line following */

typedef enum {
  STATE_IDLE,              /* idle, not doing anything */
  STATE_FOLLOW_SEGMENT,    /* line following segment, going forward */
#if PL_APP_LINE_MAZE
  STATE_FOLLOW_SEGMENT_BW, /* line following segment, going backward */
  STATE_TURN,              /* reached an intersection, turning around */
  STATE_FINISHED,          /* reached finish area */
#endif
  STATE_STOP               /* stop the engines */
} StateType;

static volatile StateType LF_currState = STATE_IDLE;
static volatile bool LF_stopIt = FALSE;
#if PL_APP_LINE_MAZE
static uint8_t LF_solvedIdx = 0; /*  index to iterate through the solution */
#endif

void LF_StartFollowing(void) {
#if PL_APP_LINE_MAZE
  if (!MAZE_IsSolved()) {
    MAZE_Init();
  } else {
    LF_solvedIdx = 0;
  }
#endif
  PID_Start();
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
static bool FollowSegment(bool forward) {
  uint16_t currLine;
  bool onLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue(&onLine);
  currLineKind = REF_GetLineKind();
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, REF_MIDDLE_LINE_VALUE, forward); /* move along the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

#if PL_APP_LINE_MAZE
/*!
 * \brief Performs a turn.
 * \return Returns TRUE while turn is still in progress.
 */
static uint8_t EvaluteTurn(bool *finished, bool *deadEndGoBw) {
  REF_LineKind historyLineKind, currLineKind;
  TURN_Kind turn;
  
  *finished = FALSE; /* defaults */
  *deadEndGoBw = FALSE; /* default */
  currLineKind = REF_GetLineKind();
  if (currLineKind==REF_LINE_NONE) { /* nothing, must be dead end */
#if PL_GO_DEADEND_BW
    TURN_Turn(TURN_STEP_BW); /* step back so we are again on the line for line following */
    turn = TURN_STRAIGHT;
    *deadEndGoBw = TRUE;
#else
    turn = TURN_LEFT180;
#endif
  } else {
    REF_ClearHistory(); /* clear values */
    REF_SampleHistory(); /* store current values */
    TURN_Turn(TURN_STEP_LINE_FW); /* make forward step over line */
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
  }
  if (turn==TURN_FINISHED) {
    *finished = TRUE;
    ChangeState(STATE_STOP);
    CLS1_SendStr((unsigned char*)"finished!\r\n", CLS1_GetStdio()->stdOut);
    return ERR_OK;
  } else if (turn==TURN_STRAIGHT && *deadEndGoBw) {
    MAZE_AddPath(TURN_LEFT180); /* would have been a turn around */
    MAZE_SimplifyPath();
    CLS1_SendStr((unsigned char*)"going backward\r\n", CLS1_GetStdio()->stdOut);
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
    if (turn==TURN_LEFT90 || turn==TURN_RIGHT90) {
      TURN_Turn(TURN_STEP_POST_LINE_FW); /* step before doing the turn so we turn on the middle of the intersection */
    }
    TURN_Turn(turn); /* make turn */
    MAZE_AddPath(turn);
    MAZE_SimplifyPath();
    return ERR_OK; /* turn finished */
  }
}

/* used to convert path items while running backwards */
static TURN_Kind MirrorTurn(TURN_Kind turn) {
  switch(turn) {
    case TURN_LEFT90: return TURN_RIGHT90;
    case TURN_RIGHT90: return TURN_LEFT90;
    case TURN_LEFT180: return TURN_STRAIGHT;
    case TURN_RIGHT180: return TURN_STRAIGHT;
    case TURN_STRAIGHT: return TURN_STRAIGHT;
    case TURN_STEP_LINE_FW: return TURN_STEP_LINE_BW;
    case TURN_STEP_LINE_BW: return TURN_STEP_LINE_FW;
    case TURN_STEP_POST_LINE_FW: return TURN_STEP_POST_LINE_BW;
    case TURN_STEP_POST_LINE_BW: return TURN_STEP_POST_LINE_FW;
    case TURN_STOP:
    case TURN_FINISHED:
    default:
      return TURN_STOP;
  }
}
#endif /* PL_APP_LINE_MAZE */

#if PL_APP_LINE_MAZE
/*!
 * \brief Performs a turn while doing backward line following.
 * \return Returns TRUE while turn is still in progress.
 */
static uint8_t EvaluateTurnBw(void) {
  REF_LineKind historyLineKind, currLineKind;
  TURN_Kind turn;
  
  REF_ClearHistory(); /* clear values */
  REF_SampleHistory(); /* store current values */
  TURN_Turn(TURN_STEP_LINE_BW); /* make step over line */
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
  turn = MAZE_SelectTurnBw(historyLineKind, currLineKind);
  if (turn==TURN_STOP) { /* should not happen here? */
    ChangeState(STATE_STOP);
    CLS1_SendStr((unsigned char*)"stopped\r\n", CLS1_GetStdio()->stdOut);
    return ERR_FAILED; /* error case */
  } else { /* turn or do something */
#if LINE_DEBUG
    CLS1_SendStr((unsigned char*)"bw turning ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)TURN_TurnKindStr(turn), CLS1_GetStdio()->stdOut);
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
#endif
    TURN_Turn(TURN_STEP_LINE_FW); /* step over intersection */
    TURN_Turn(TURN_STEP_POST_LINE_FW); /* step past intersection */
    TURN_Turn(turn); /* make turn */
    MAZE_AddPath(MirrorTurn(turn));
    MAZE_SimplifyPath();
    return ERR_OK; /* turn finished */
  }
}
#endif /* PL_APP_LINE_MAZE */

static void StateMachine(void) {
  switch (LF_currState) {
    case STATE_IDLE:
      break;
    case STATE_FOLLOW_SEGMENT:
      if (!FollowSegment(LINE_FOLLOW_FW)) {
#if PL_APP_LINE_MAZE
        LF_currState = STATE_TURN; /* make turn */
#else
        LF_currState = STATE_STOP; /* stop if we do not have a line any more */
#endif
      }
      break;
#if PL_APP_LINE_MAZE
    case STATE_FOLLOW_SEGMENT_BW:
      if (!FollowSegment(FALSE)) {
        TURN_Turn(TURN_STOP);
        if (EvaluateTurnBw()==ERR_OK) {
          LF_currState = STATE_FOLLOW_SEGMENT;
        } else {
          LF_currState = STATE_STOP;
        }
      }
      break;
#endif
#if PL_APP_LINE_MAZE
    case STATE_TURN:
      if (MAZE_IsSolved()) {
        TURN_Kind turn;
        
        turn = MAZE_GetSolvedTurn(&LF_solvedIdx);
        if (turn==TURN_STOP) { /* last turn reached */
          TURN_Turn(turn);
          LF_currState = STATE_FINISHED;
        } else { /* perform turning */
          TURN_Turn(TURN_STEP_LINE_FW); /* Step over line */
          TURN_Turn(TURN_STEP_POST_LINE_FW); /* step before doing the turn */
          TURN_Turn(turn);
          LF_currState = STATE_FOLLOW_SEGMENT;
        }
      } else { /* still evaluating maze */
        bool deadEndGoBw = FALSE;
        bool finished = FALSE;
        
        if (EvaluteTurn(&finished, &deadEndGoBw)==ERR_OK) { /* finished turning */
          if (finished) {
            LF_currState = STATE_FINISHED;
            MAZE_SetSolved();
#if PL_TURN_ON_FINISH
            /* turn the robot */
            TURN_Turn(TURN_LEFT180);
#endif
            TURN_Turn(TURN_STOP);
            /* now ready to do line following */
          } else if (deadEndGoBw) {
            LF_currState = STATE_FOLLOW_SEGMENT_BW;
          } else {
            LF_currState = STATE_FOLLOW_SEGMENT;
          }
        } else { /* error case */
          LF_currState = STATE_STOP;
        }
      }
      break;
#endif
#if PL_APP_LINE_MAZE
    case STATE_FINISHED:
#if PL_HAS_BUZZER
      {
        uint8_t i;
        
        for(i=0;i<4;i++) {
          (void)BUZ_Beep(300, 100);
          WAIT1_WaitOSms(500);
        }
      }
#endif
      LF_currState = STATE_STOP;
      break;
#endif
    case STATE_STOP:
      TURN_Turn(TURN_STOP);
      LF_currState = STATE_IDLE;
      break;
  } /* switch */
}

bool LF_IsFollowing(void) {
  return LF_currState!=STATE_IDLE;
}

static portTASK_FUNCTION(LineTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (LF_stopIt) {
      ChangeState(STATE_STOP);
      LF_stopIt = FALSE;
    }
    StateMachine();
    if (LF_IsFollowing()) {
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(5));
    } else {
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(100));
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
    case STATE_STOP: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"STOP\r\n", io->stdOut);
      break;
#if PL_APP_LINE_MAZE
    case STATE_TURN: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"TURN\r\n", io->stdOut);
      break;
    case STATE_FINISHED: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FINISHED\r\n", io->stdOut);
      break;
#endif
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
  PID_Init();
  LF_currState = STATE_IDLE;
  if (FRTOS1_xTaskCreate(LineTask, "Line", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_LINE_SENSOR */
