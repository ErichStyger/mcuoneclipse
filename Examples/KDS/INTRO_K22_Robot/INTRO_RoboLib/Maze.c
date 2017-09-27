/**
 * \file
 * \brief Implementation of maze solving
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is used to solve a line maze.
 */

#include "Platform.h"
#if PL_APP_LINE_MAZE
#include "Maze.h"
#include "Turn.h"
#include "CLS1.h"
#if PL_HAS_LED_GREEN
  #include "LEDG.h"
#endif
#if PL_HAS_LED_RED
  #include "LEDR.h"
#endif
#include "LineFollow.h"
#include "LineHistory.h"
#include "Event.h"
#include "UTIL1.h"
#include "PID.h"
#include "Reflectance.h"
#include "Shell.h"
#if PL_CONFIG_HAS_NVM_CONFIG
  #include "NVM_Config.h"
#endif

#define LINE_DEBUG      0   /* careful: this will slow down the PID loop frequency! */

#define MAZE_MAX_PATH       64    /* maximum number of turns in path */
static TURN_Kind path[MAZE_MAX_PATH];
static uint8_t pathLength;
static bool isSolved = FALSE;
static bool useLeftHandOnTheWallRule = TRUE;

bool MAZE_IsLeftHandRule(void) {
  return useLeftHandOnTheWallRule;
}

uint8_t MAZE_SetHandRule(bool isLeft) {
  const NVMC_RobotData *ptr;
  NVMC_RobotData data;
  uint8_t res;

  res = ERR_OK;
  useLeftHandOnTheWallRule = isLeft;
  ptr = NVMC_GetRobotData();
  if (ptr!=NULL && ptr->MazeLeftHandOnTheWall!=useLeftHandOnTheWallRule) {
    data = *NVMC_GetRobotData();
    res = NVMC_SaveRobotData(&data);
  }
  return res;
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
    case TURN_STEP_LINE_FW_POST_LINE: return TURN_STEP_LINE_BW_POST_LINE;
    case TURN_STEP_LINE_BW_POST_LINE: return TURN_STEP_LINE_FW_POST_LINE;
    case TURN_STOP:
    case TURN_FINISHED:
    default:
      return TURN_STOP;
  }
}

TURN_Kind MAZE_SelectTurnBw(REF_LineKind prev, REF_LineKind curr);
/*!
 * \brief Performs a turn while doing backward line following.
 * \return Returns TRUE while turn is still in progress.
 */
uint8_t MAZE_EvaluateTurnBw(void) {
  REF_LineKind historyLineKind, currLineKind;
  TURN_Kind turn;

  HISTORY_Clear(); /* clear values */
  HISTORY_SampleSensors(); /* store current values */
  TURN_Turn(TURN_STEP_LINE_BW, HISTORY_SampleTurnStopFunction); /* make step over line */
  historyLineKind = HISTORY_LineKind(); /* new read new values */
  currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_MAZE);
#if LINE_DEBUG
  SHELL_SendString((unsigned char*)" history: ");
  SHELL_SendString((unsigned char*)REF_LineKindStr(historyLineKind));
  SHELL_SendString((unsigned char*)" curr: ");
  SHELL_SendString((unsigned char*)REF_LineKindStr(currLineKind));
  SHELL_SendString((unsigned char*)"\r\n");
#endif
  turn = MAZE_SelectTurnBw(historyLineKind, currLineKind);
  if (turn==TURN_STOP) { /* should not happen here? */
    LF_StopFollowing();
    SHELL_SendString((unsigned char*)"stopped\r\n");
    return ERR_FAILED; /* error case */
  } else { /* turn or do something */
#if LINE_DEBUG
    SHELL_SendString((unsigned char*)"bw turning ");
    SHELL_SendString((unsigned char*)TURN_TurnKindStr(turn));
    SHELL_SendString((unsigned char*)"\r\n");
#endif
    TURN_Turn(TURN_STEP_LINE_FW_POST_LINE, NULL); /* step over intersection */ /* ???? not good for going backward over -| */
    TURN_Turn(turn, NULL); /* make turn */
    MAZE_AddPath(MirrorTurn(turn));
    MAZE_SimplifyPath();
    return ERR_OK; /* turn finished */
  }
}

/*!
 * \brief Performs a turn.
 * \return Returns TRUE while turn is still in progress.
 */
uint8_t MAZE_EvaluteTurn(bool *finished, bool *deadEndGoBw) {
  REF_LineKind historyLineKind, currLineKind;
  TURN_Kind turn;

  *finished = FALSE; /* defaults */
  *deadEndGoBw = FALSE; /* default */
  currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_MAZE);
  if (currLineKind==REF_LINE_NONE) { /* nothing, must be dead end */
#if PL_GO_DEADEND_BW
    TURN_Turn(TURN_STEP_LINE_BW, NULL); /* step back so we are again on the line for line following */
    turn = TURN_STRAIGHT;
    *deadEndGoBw = TRUE;
#else
    turn = TURN_LEFT180;
#endif
  } else {
    HISTORY_Clear(); /* clear history values */
    HISTORY_SampleSensors(); /* store current values */
#if PL_HAS_QUADRATURE
    TURN_Turn(TURN_STEP_LINE_FW_POST_LINE, HISTORY_SampleTurnStopFunction); /* do the line and beyond in one step */
#else
    TURN_Turn(TURN_STEP_LINE_FW, NULL); /* make forward step over line */
#endif
    historyLineKind = HISTORY_LineKind(); /* new read new values */
    currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_MAZE);
    turn = MAZE_SelectTurn(historyLineKind, currLineKind);
#if LINE_DEBUG
    SHELL_SendString((unsigned char*)"selected turn: ");
    SHELL_SendString((unsigned char*)TURN_TurnKindStr(turn));
    SHELL_SendString((unsigned char*)"\r\n");
#endif
  }
  if (turn==TURN_FINISHED) {
    *finished = TRUE;
    SHELL_SendString((unsigned char*)"MAZE: finished!\r\n");
    return ERR_OK;
  } else if (turn==TURN_STRAIGHT && *deadEndGoBw) {
    MAZE_AddPath(TURN_LEFT180); /* would have been a turn around */
    MAZE_SimplifyPath();
    SHELL_SendString((unsigned char*)"going backward\r\n");
    return ERR_OK;
  } else if (turn==TURN_STRAIGHT) {
    MAZE_AddPath(turn);
    MAZE_SimplifyPath();
    SHELL_SendString((unsigned char*)"going straight\r\n");
    return ERR_OK;
  } else if (turn==TURN_STOP) { /* should not happen here? */
    LF_StopFollowing();
    SHELL_SendString((unsigned char*)"Failure, stopped!!!\r\n");
    return ERR_FAILED; /* error case */
  } else { /* turn or do something */
#if LINE_DEBUG
    SHELL_SendString((unsigned char*)"turning ");
    SHELL_SendString((unsigned char*)TURN_TurnKindStr(turn));
    SHELL_SendString((unsigned char*)"\r\n");
#endif
#if !PL_HAS_QUADRATURE /* if using quadrature, we stepped this piece already above */
    if (turn==TURN_LEFT90 || turn==TURN_RIGHT90) {
      TURN_Turn(TURN_STEP_POST_LINE_FW, NULL); /* step before doing the turn so we turn on the middle of the intersection */
    }
#endif
    TURN_Turn(turn, NULL); /* make turn */
    MAZE_AddPath(turn);
    MAZE_SimplifyPath();
    return ERR_OK; /* turn finished */
  }
}

static TURN_Kind RevertTurn(TURN_Kind turn) {
  if (turn==TURN_LEFT90) {
    turn = TURN_RIGHT90;
  } else if (turn==TURN_RIGHT90) {
    turn = TURN_LEFT90;
  }
  return turn;
}

/**
 * \brief Reverts the path 
 */
static void MAZE_RevertPath(void) {
  int i, j;
  TURN_Kind tmp;
  
  if (pathLength==0) {
    return;
  }
  j = pathLength-1;
  i = 0;
  while(i<=j) {
    tmp = path[i];
    path[i] = RevertTurn(path[j]);
    path[j] = RevertTurn(tmp);
    i++; j--;
  }
}

TURN_Kind MAZE_SelectTurn(REF_LineKind prev, REF_LineKind curr) {
  if (prev==REF_LINE_NONE && curr==REF_LINE_NONE) { /* dead end */
    if (MAZE_IsLeftHandRule()) {
      return TURN_RIGHT180; /* make U turn */
    } else {
      return TURN_LEFT180; /* make U turn */
    }
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_NONE) { /* 'T' */
    if (MAZE_IsLeftHandRule()) {
      return TURN_LEFT90;
    } else {
      return TURN_RIGHT90;
    }
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_NONE) { /* right turn */
    return TURN_RIGHT90;
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_NONE) { /* left turn */
    return TURN_LEFT90;
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_STRAIGHT) { /* '+' intersection */
    if (MAZE_IsLeftHandRule()) {
      return TURN_LEFT90;
    } else {
      return TURN_RIGHT90;
    }
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_FULL) { /* finish area */
    return TURN_FINISHED;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_STRAIGHT) { /* forward and right turn */
    if (MAZE_IsLeftHandRule()) {
      return TURN_STRAIGHT;
    } else {
      return TURN_RIGHT90;
    }
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_STRAIGHT) { /* forward and left turn */
    if (MAZE_IsLeftHandRule()) {
      return TURN_LEFT90;
    } else {
      return TURN_STRAIGHT;
    }
  }
  return TURN_STOP; /* error case */
}

TURN_Kind MAZE_SelectTurnBw(REF_LineKind prev, REF_LineKind curr) {
  if (prev==REF_LINE_LEFT && curr==REF_LINE_NONE) { /* was turn to left */
    return TURN_LEFT90;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_NONE) { /* was turn to right */
    return TURN_RIGHT90;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_STRAIGHT) { /* |- */
    if (MAZE_IsLeftHandRule()) {
      return TURN_RIGHT90;
    } else {
      return TURN_LEFT180;
    }
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_STRAIGHT) { /* -| */
    if (MAZE_IsLeftHandRule()) {
      return TURN_RIGHT180;
    } else {
      return TURN_LEFT90;
    }
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_NONE) { /* T upside-down */
    if (MAZE_IsLeftHandRule()) {
      return TURN_RIGHT90;
    } else {
      return TURN_LEFT90;
    }
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_STRAIGHT) { /* '+' intersection  */
    if (MAZE_IsLeftHandRule()) {
      return TURN_RIGHT90;
    } else {
      return TURN_LEFT90;
    }
  }
  return TURN_STOP; /* error case */
}

void MAZE_SetSolved(void) {
  isSolved = TRUE;
  MAZE_RevertPath();
  MAZE_AddPath(TURN_STOP); /* add an action to stop */
}

bool MAZE_IsSolved(void) {
  return isSolved;
}

void MAZE_AddPath(TURN_Kind kind) {
  if (pathLength<MAZE_MAX_PATH) {
    path[pathLength] = kind;
    pathLength++;
  } else {
    /* error! */
  }
}

/*!
 * \brief Performs path simplification.
 * The idea is that whenever we encounter x-TURN_RIGHT180-x or x-TURN_LEFT180-x, we simplify it by cutting the dead end.
 * For example if we have TURN_LEFT90-TURN_RIGHT180-TURN_LEFT90, this can be simplified with TURN_STRAIGHT.
 */
void MAZE_SimplifyPath(void) {
  /* implemented for left-hand-on-the-wall rule for now! */
  uint16_t totalAngle, i;
  
  if (pathLength<3) { /* we need at least 3 entries for simplification */
    return;
  }
  if (!(path[pathLength-2] == TURN_RIGHT180 || path[pathLength-2] == TURN_LEFT180)) {
    /* we simplify only if second-to-last is a dead-end */
    return;
  }
  totalAngle = 0;
  for (i=1; i<=3; i++) {
    switch(path[pathLength-i]) {
      case TURN_LEFT90: totalAngle += 270; break;
      case TURN_RIGHT90: totalAngle += 90; break;
      case TURN_LEFT180: totalAngle += 180; break;
      case TURN_RIGHT180: totalAngle += 180; break;
      default:
        /* would be an error? */
        break;
    } /* switch */
  }
  totalAngle %= 360; /* make sure angle is within 0...360 degrees */
  switch(totalAngle) {
    case 0:   path[pathLength-3] = TURN_STRAIGHT; break;
    case 90:  path[pathLength-3] = TURN_RIGHT90; break;
    case 180: path[pathLength-3] = TURN_LEFT180; break;
    case 270: path[pathLength-3] = TURN_LEFT90; break;
  }
  pathLength -= 2; /* was able to cut the path by 2 entries :-) */
}

typedef enum {
  MAZE_SPEED_LOW,
  MAZE_SPEED_MEDIUM,
  MAZE_SPEED_HIGH
} MAZE_SpeedMode;
static MAZE_SpeedMode mazeSpeed;

static const unsigned char *MAZE_SpeedModeString(MAZE_SpeedMode mode) {
  switch(mode) {
  case MAZE_SPEED_LOW: return (const unsigned char*)"LOW";
  case MAZE_SPEED_MEDIUM: return (const unsigned char*)"MEDIUM";
  case MAZE_SPEED_HIGH: return (const unsigned char*)"HIGH";
  default: break;
  }
  return (const unsigned char*)"UNKNOWN";
}

static uint8_t MAZE_SetSpeed(MAZE_SpeedMode speed) {
  uint8_t res;
  PID_Config *lineFwPid;

  res = PID_GetPIDConfig(PID_CONFIG_LINE_FW, &lineFwPid);
  if (res!=ERR_OK || lineFwPid==NULL) {
    return ERR_FAILED;
  }
  switch(speed) {
    case MAZE_SPEED_LOW:
      lineFwPid->maxSpeedPercent = 15;
      lineFwPid->pFactor100 = 4000;
      TURN_SetStepsLine(230, 160);
      break;
    case MAZE_SPEED_MEDIUM:
      lineFwPid->maxSpeedPercent = 35;
      lineFwPid->pFactor100 = 5500;
      lineFwPid->iAntiWindup = 100000;
      TURN_SetStepsLine(190, 100);
      break;
    case MAZE_SPEED_HIGH:
      lineFwPid->maxSpeedPercent = 50;
      lineFwPid->pFactor100 = 2000;
      lineFwPid->iAntiWindup = 30000;
      TURN_SetStepsLine(150, 80);
      break;
    default:
      return ERR_FAILED;
  } /* switch */
  mazeSpeed = speed;
  return ERR_OK;
}

static void MAZE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"maze", (unsigned char*)"Group of maze following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows maze help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  clear", (unsigned char*)"Clear the maze solution\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  rule (left|right)", (unsigned char*)"Left or Right-hand-on-the-wall rule\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  speed <mode>", (unsigned char*)"Maze solving speed, either low, medium or high\r\n", io->stdOut);
}

static void MAZE_PrintStatus(const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"maze", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  rule", MAZE_IsLeftHandRule()?(unsigned char*)"left-hand-on-the-wall\r\n":(unsigned char*)"right-hand-on-the-wall\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  solved", MAZE_IsSolved()?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  path", (unsigned char*)"(", io->stdOut);
  CLS1_SendNum8u(pathLength, io->stdOut);
  CLS1_SendStr((unsigned char*)") ", io->stdOut);
  for(i=0;i<pathLength;i++) {
    CLS1_SendStr(TURN_TurnKindStr(path[i]), io->stdOut);
    CLS1_SendStr((unsigned char*)" ", io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), MAZE_SpeedModeString(mazeSpeed));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  speed", buf, io->stdOut);
}

uint8_t MAZE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"maze help")==0) {
    MAZE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"maze status")==0) {
    MAZE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze clear")==0) {
    MAZE_ClearSolution();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze rule left")==0) {
    useLeftHandOnTheWallRule = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze rule right")==0) {
    useLeftHandOnTheWallRule = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze speed low")==0) {
    (void)MAZE_SetSpeed(MAZE_SPEED_LOW);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze speed medium")==0) {
    (void)MAZE_SetSpeed(MAZE_SPEED_MEDIUM);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze speed high")==0) {
    (void)MAZE_SetSpeed(MAZE_SPEED_HIGH);
    *handled = TRUE;
  }
  return res;
}

TURN_Kind MAZE_GetSolvedTurn(uint8_t *solvedIdx) {
  if (*solvedIdx < pathLength) {
    return path[(*solvedIdx)++];
  } else {
    return TURN_STOP; 
  }
}

void MAZE_ClearSolution(void) {
  isSolved = FALSE;
  pathLength = 0;
}

typedef enum {
  MAZE_STATE_INIT,
  MAZE_STATE_IDLE,
  MAZE_STATE_FOLLOW_LINE
} MazeStateType;

static MazeStateType mazeState = MAZE_STATE_INIT;

static void MAZE_StateMachine(void) {
  switch (mazeState) {
    case MAZE_STATE_INIT:
#if PL_HAS_LED_GREEN
      LEDG_Off();
#endif
#if PL_HAS_LED_RED
      LEDR_On();
#endif
      if (REF_CanUseSensor()) {
        mazeState = MAZE_STATE_IDLE;
      }
      break;
    case MAZE_STATE_IDLE:
      if (!REF_CanUseSensor()) { /* sensor not available any more? */
        mazeState = MAZE_STATE_INIT;
      }
#if PL_HAS_LED_RED
      LEDR_Off();
#endif
#if PL_HAS_LED_GREEN
      LEDG_On();
#endif
      if (EVNT_EventIsSet(EVNT_MAZE_BUTTON_PRESS)) {
        EVNT_ClearEvent(EVNT_MAZE_BUTTON_PRESS);
        LF_StartFollowing();
        mazeState = MAZE_STATE_FOLLOW_LINE;
      }
      break;
    case MAZE_STATE_FOLLOW_LINE:
#if PL_HAS_LED_RED
      LEDR_Off();
#endif
#if PL_HAS_LED_GREEN
      LEDG_Off();
#endif
      if (!LF_IsFollowing()) {
        mazeState = MAZE_STATE_IDLE;
      }
      if (EVNT_EventIsSet(EVNT_MAZE_BUTTON_PRESS)) {
        EVNT_ClearEvent(EVNT_MAZE_BUTTON_PRESS);
        LF_StopFollowing(); 
        mazeState = MAZE_STATE_IDLE;
      }
      break;
  } /* switch */
}

void MAZE_Init(void) {
  const NVMC_RobotData *ptr;

  ptr = NVMC_GetRobotData();
  if (ptr!=NULL) {
    (void)MAZE_SetHandRule(ptr->MazeLeftHandOnTheWall);
  }
  mazeState = MAZE_STATE_INIT;
  (void)MAZE_SetSpeed(MAZE_SPEED_LOW);
  //(void)MAZE_SetSpeed(MAZE_SPEED_MEDIUM);
  //(void)MAZE_SetSpeed(MAZE_SPEED_HIGH);
  MAZE_ClearSolution();
}
#endif /* PL_HAS_LINE_SENSOR */
