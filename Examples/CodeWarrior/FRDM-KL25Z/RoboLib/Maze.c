/*
 * Maze.c
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_APP_LINE_MAZE
#include "Maze.h"
#include "Turn.h"
#include "CLS1.h"
#include "UTIL1.h"

#define MAZE_MAX_PATH 32 /* maximum number of turns in path */
#define MAZE_LEFT_HAND_RULE  1  /* 1 for 'left-hand-on-the-wall, 0 otherwise */

static TURN_Kind path[MAZE_MAX_PATH];
static uint8_t pathLength;
static bool isSolved = FALSE;

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
#if MAZE_LEFT_HAND_RULE
    return TURN_RIGHT180; /* make U turn */
#else
    return TURN_LEFT180; /* make U turn */
#endif
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_NONE) { /* 'T' */
#if MAZE_LEFT_HAND_RULE
    return TURN_LEFT90;
#else
    return TURN_RIGHT90;
#endif
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_NONE) { /* right turn */
    return TURN_RIGHT90;
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_NONE) { /* left turn */
    return TURN_LEFT90;
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_STRAIGHT) { /* '+' intersection */
#if MAZE_LEFT_HAND_RULE
    return TURN_LEFT90;
#else
    return TURN_RIGHT90;
#endif
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_FULL) { /* finish area */
    return TURN_FINISHED;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_STRAIGHT) { /* forward and right turn */
    return TURN_STRAIGHT;
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_STRAIGHT) { /* forward and left turn */
#if MAZE_LEFT_HAND_RULE
    return TURN_LEFT90;
#else
    return TURN_RIGHT90;
#endif
  }
  return TURN_STOP; /* error case */
}

TURN_Kind MAZE_SelectTurnBw(REF_LineKind prev, REF_LineKind curr) {
  if (prev==REF_LINE_LEFT && curr==REF_LINE_NONE) { /* was turn to left */
    return TURN_LEFT90;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_NONE) { /* was turn to right */
    return TURN_RIGHT90;
  } else if (prev==REF_LINE_RIGHT && curr==REF_LINE_STRAIGHT) { /* |- */
#if MAZE_LEFT_HAND_RULE
    return TURN_RIGHT90;
#else
    return TURN_LEFT180;
#endif
  } else if (prev==REF_LINE_LEFT && curr==REF_LINE_STRAIGHT) { /* -| */
#if MAZE_LEFT_HAND_RULE
    return TURN_RIGHT180;
#else
    return TURN_LEFT90;
#endif
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_NONE) { /* T upside-down */
#if MAZE_LEFT_HAND_RULE
    return TURN_RIGHT90;
#else
    return TURN_LEFT90;
#endif
  } else if (prev==REF_LINE_FULL && curr==REF_LINE_STRAIGHT) { /* '+' intersection  */
#if MAZE_LEFT_HAND_RULE
    return TURN_RIGHT90;
#else
    return TURN_LEFT90;
#endif
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

static void MAZE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"maze", (unsigned char*)"Group of maze following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows maze help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  clear", (unsigned char*)"Clear the maze solution\r\n", io->stdOut);
}

static void MAZE_PrintStatus(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"maze", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  solved", MAZE_IsSolved()?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  path", (unsigned char*)"(", io->stdOut);
  CLS1_SendNum8u(pathLength, io->stdOut);
  CLS1_SendStr((unsigned char*)") ", io->stdOut);
  for(i=0;i<pathLength;i++) {
    CLS1_SendStr(TURN_TurnKindStr(path[i]), io->stdOut);
    CLS1_SendStr((unsigned char*)" ", io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
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

void MAZE_Init(void) {
  MAZE_ClearSolution();
}
#endif /* PL_HAS_LINE_SENSOR */
