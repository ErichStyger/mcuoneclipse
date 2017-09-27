/**
 * \file
 * \brief Implements line following of the robot
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This is the implementation of the line following.
 */

#include "Platform.h"
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
#include "LineFollow.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#include "WAIT1.h"
#include "Pid.h"
#include "Turn.h"
#include "Maze.h"
#include "Shell.h"
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_HAS_USER_LED
  #include "LED1.h"
  #include "LED2.h"
#endif

#define LINE_FOLLOW_FW  1   /* test setting to do forward line following */

typedef enum {
  STATE_IDLE,              /* idle, not doing anything */
  STATE_FOLLOW_SEGMENT,    /* line following segment, going forward */
#if PL_APP_LINE_MAZE && PL_GO_DEADEND_BW
  STATE_FOLLOW_SEGMENT_BW, /* line following segment, going backward */
#endif
#if PL_APP_LINE_MAZE
  STATE_TURN,              /* reached an intersection, turning around */
  STATE_FINISHED,          /* reached finish area */
#endif
  STATE_STOP               /* stop the engines */
} StateType;

/* task notification bits */
#define LF_START_FOLLOWING (1<<0)  /* start line following */
#define LF_STOP_FOLLOWING  (1<<1)  /* stop line following */
static xTaskHandle LFTaskHandle;

static volatile StateType LF_currState = STATE_IDLE;
#if PL_APP_LINE_MAZE
static uint8_t LF_solvedIdx = 0; /*  index to iterate through the solution, zero is the solution start index */
#endif

void LF_StartFollowing(void) {
  (void)xTaskNotify(LFTaskHandle, LF_START_FOLLOWING, eSetBits);
}

void LF_StopFollowing(void) {
  (void)xTaskNotify(LFTaskHandle, LF_STOP_FOLLOWING, eSetBits);
}

void LF_StartStopFollowing(void) {
  if (LF_IsFollowing()) {
    (void)xTaskNotify(LFTaskHandle, LF_STOP_FOLLOWING, eSetBits);
  } else {
    (void)xTaskNotify(LFTaskHandle, LF_START_FOLLOWING, eSetBits);
  }
}

/*!
 * \brief follows a line segment.
 * \return Returns TRUE if still on line segment
 */
bool LF_FollowSegment(REF_LineKindMode mode, bool forward) {
  uint16_t currLine;
  bool onLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue(&onLine);
  currLineKind = REF_GetLineKind(mode);
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, REF_MIDDLE_LINE_VALUE, REF_LineWidth(), forward); /* move along the line */
    return TRUE;
  } else { /* stop motors */
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

/*!
 * \brief Move from outside onto a line/segment to follow it.
 * \return Returns TRUE if still on line segment
 */
bool LF_MoveOnSegment(bool turningLeft) {
  uint16_t currLine, targetLine;
  int tmp;
  bool onLine;
  REF_LineKind currLineKind;
  uint16_t lineWidth;

  currLine = REF_GetLineValue(&onLine);
  currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_ALL);
  lineWidth = REF_LineWidth();
  if (lineWidth>2000) {
    if (turningLeft) {
      tmp = REF_MIDDLE_LINE_VALUE+lineWidth;
    } else {
      tmp = REF_MIDDLE_LINE_VALUE-lineWidth;
    }
    if (tmp<0) {
      tmp = 0;
    }
    if (tmp>REF_MAX_LINE_VALUE) {
      tmp = REF_MAX_LINE_VALUE;
    }
    targetLine = tmp;
  } else {
    targetLine = REF_MIDDLE_LINE_VALUE;
  }
  if (currLineKind==REF_LINE_STRAIGHT || currLineKind==REF_LINE_LEFT || currLineKind==REF_LINE_RIGHT || currLineKind==REF_LINE_FULL) {
    PID_Line(currLine, targetLine, REF_LineWidth(), TRUE); /* move along the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

bool LF_FollowSegmentLinePos(REF_LineKindMode mode, uint16_t setLinePos) {
  uint16_t currLine;
  bool onLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue(&onLine);
  currLineKind = REF_GetLineKind(mode);
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, setLinePos, REF_LineWidth(), TRUE); /* move along the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

static void StateMachine(void) {
  REF_LineKind currLineKind;

  for(;;) {
    switch (LF_currState) {
      case STATE_IDLE:
        break;
      case STATE_FOLLOW_SEGMENT:
#if PL_APP_LINE_MAZE
        if (!LF_FollowSegment(REF_LINE_KIND_MODE_MAZE, LINE_FOLLOW_FW)) {
          TURN_Turn(TURN_STOP, NULL);
          LF_currState = STATE_TURN; /* make turn */
          continue; /* process next step immediately */
        }
#else
        if (!LF_FollowSegment(REF_LINE_KIND_MODE_LINE_FOLLOW, LINE_FOLLOW_FW)) {
          SHELL_SendString((unsigned char*)"No segment any more!\r\n");
          currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
          if (currLineKind==REF_LINE_FULL) { /* turn around on finish area */
            SHELL_SendString((unsigned char*)"Full block!\r\n");
            LF_currState = STATE_STOP; /* stop  */
          } else if (currLineKind==REF_LINE_NONE) {
            SHELL_SendString((unsigned char*)"no line!\r\n");
            TURN_Turn(TURN_LEFT180, NULL);
        #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
        #endif
            /* stay in line following mode */
          } else {
            LF_currState = STATE_STOP; /* stop if we do not have a line any more */
          }
        }
#endif
        break;

  #if PL_APP_LINE_MAZE && PL_GO_DEADEND_BW
      case STATE_FOLLOW_SEGMENT_BW:
        if (!LF_FollowSegment(FALSE)) {
          TURN_Turn(TURN_STOP, NULL);
          if (MAZE_EvaluateTurnBw()==ERR_OK) {
        #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
        #endif
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
            TURN_Turn(turn, NULL);
          #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
          #endif
            LF_currState = STATE_STOP;
            SHELL_SendString((unsigned char *)"MAZE: I'm back to the start of maze!\r\n");
          #if PL_HAS_BUZZER
            BUZ_PlayTune(1);
          #endif
            MAZE_ClearSolution(); /* clear solution */
  #if PL_TURN_ON_START
            /* turn the robot on start so it is ready to run the maze again */
          #if PL_HAS_QUADRATURE
            TURN_Turn(TURN_LEFT180, NULL);
          #else /* not accurate enough without position sensor */
            TURN_Turn(TURN_LEFT90, NULL); /* do turn in two steps */
            TURN_Turn(TURN_LEFT90, NULL);
          #endif
  #endif
            TURN_Turn(TURN_STOP, NULL);
  #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
  #endif
            /* now ready to solve maze again */
            SHELL_SendString((unsigned char *)"MAZE: ready to start again!\r\n");
          } else { /* perform turning */
            TURN_Turn(TURN_STEP_LINE_FW_POST_LINE, NULL); /* Step over line */
            TURN_Turn(turn, NULL);
        #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode, so we can do line following (line following is PWM) */
        #endif
            LF_currState = STATE_FOLLOW_SEGMENT;
            continue; /* process next state immediately */
          }
        } else { /* still evaluating maze */
          bool deadEndGoBw = FALSE;
          bool finished = FALSE;

          if (MAZE_EvaluteTurn(&finished, &deadEndGoBw)==ERR_OK) { /* finished turning */
        #if PL_HAS_DRIVE
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
        #endif
            if (finished) {
              LF_currState = STATE_FINISHED;
              MAZE_SetSolved();
              LF_solvedIdx = 0; /* set index to start of solution */
  #if PL_TURN_ON_FINISH
              /* turn the robot */
            #if PL_HAS_QUADRATURE
              TURN_Turn(TURN_LEFT180, NULL);
            #else /* not accurate enough without position sensor */
              TURN_Turn(TURN_LEFT90, NULL); /* do turn in two steps */
              TURN_Turn(TURN_LEFT90, NULL);
            #endif
  #endif
            //  TURN_Turn(TURN_STOP, NULL);
  #if PL_HAS_DRIVE
              (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
  #endif
              /* now ready to do line following */
#if PL_GO_DEADEND_BW
            } else if (deadEndGoBw) {
              LF_currState = STATE_FOLLOW_SEGMENT_BW;
#endif
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
        SHELL_SendString((unsigned char *)"MAZE: Found maze destination!\r\n");
  #if PL_HAS_BUZZER
        BUZ_PlayTune(2);
  #endif
        SHELL_SendString((unsigned char *)"MAZE: Going back to start...\r\n");
        LF_currState = STATE_FOLLOW_SEGMENT; /* go back to start */
        break;
  #endif
      case STATE_STOP:
        SHELL_SendString((unsigned char *)"Stopped!\r\n");
        TURN_Turn(TURN_STOP, NULL);
        LF_currState = STATE_IDLE;
        break;
    } /* switch */
    break; /* get out of for loop */
  } /* for */
}

bool LF_IsFollowing(void) {
  return LF_currState!=STATE_IDLE;
}

static uint8_t LF_SetSpeed(bool slow) {
  uint8_t res;
  PID_Config *lineFwPid;

  res = PID_GetPIDConfig(PID_CONFIG_LINE_FW, &lineFwPid);
  if (res!=ERR_OK || lineFwPid==NULL) {
    return ERR_FAILED;
  }
  if (slow) {
    lineFwPid->maxSpeedPercent = 30;
    lineFwPid->pFactor100 = 5500;
    lineFwPid->iFactor100 = 15;
    lineFwPid->iAntiWindup = 100000;
    lineFwPid->dFactor100 = 100;
  } else {
    lineFwPid->maxSpeedPercent = 50;
    lineFwPid->pFactor100 = 3000;
    lineFwPid->iFactor100 = 2;
    lineFwPid->iAntiWindup = 50000;
    lineFwPid->dFactor100 = 0;
  }
  return ERR_OK;
}

static void LineTask (void *pvParameters) {
  uint32_t notifcationValue;
  BaseType_t notified;

  (void)pvParameters; /* not used */
  LF_SetSpeed(FALSE);
  for(;;) {
    notified = xTaskNotifyWait(0UL, LF_START_FOLLOWING|LF_STOP_FOLLOWING, &notifcationValue, 1); /* check flags, need to wait for one tick */
    if (notified==pdTRUE) { /* received notification */
      if (notifcationValue&LF_START_FOLLOWING) {
        if (REF_CanUseSensor()) {
          PID_Start();
          LF_currState = STATE_FOLLOW_SEGMENT;
      #if PL_HAS_DRIVE
          (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
      #endif
        } else {
          SHELL_SendString((unsigned char*)"Sensors not ready!\r\n");
      #if PL_HAS_BUZZER
          (void)BUZ_Beep(500, 500);
      #endif
        }
      }
      if (notifcationValue&LF_STOP_FOLLOWING) {
        LF_currState = STATE_STOP;
      }
    }
    StateMachine();
#if PL_APP_LINE_MAZE
    if (MAZE_IsLeftHandRule()) {
#if PL_CONFIG_BOARD_IS_ROBO_V2_2016
      LED2_Off(); LED1_Neg(); /* blink left LED */
#else
      LED1_Off(); LED2_Neg(); /* blink left LED */
#endif
    } else {
#if PL_CONFIG_BOARD_IS_ROBO_V2_2016
      LED1_Off(); LED2_Neg(); /* blink right LED */
#else
      LED2_Off(); LED1_Neg(); /* blink right LED */
#endif
    }
#endif
    if (LF_IsFollowing()) {
      FRTOS1_vTaskDelay(5/portTICK_PERIOD_MS);
    } else {
      FRTOS1_vTaskDelay(100/portTICK_PERIOD_MS);
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

void LF_Deinit(void) {
  /* nothing needed */
}

void LF_Init(void) {
  LF_currState = STATE_IDLE;
  if (FRTOS1_xTaskCreate(LineTask, "Line", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, &LFTaskHandle) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE */
