/**
 * \file
 * \brief Module to drive the robot.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module allows to drive the robot and to perform turns.
 */
#include "Platform.h"
#if PL_HAS_DRIVE
#include "Drive.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#include "Pid.h"
#include "Motor.h"
#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
#endif
#if configUSE_TRACE_HOOKS
  #include "PTRC1.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#include "Shell.h"
#include "WAIT1.h"

#define PRINT_DRIVE_INFO  0 /* if we print debug info */

struct {
  DRV_Mode mode;
  struct {
    int32_t left, right;
  } speed;
#if PL_HAS_QUADRATURE
  struct {
    int32_t left, right;
  } pos;
#endif
} DRV_Status;

typedef enum {
  DRV_SET_MODE,
  DRV_SET_SPEED,
#if PL_HAS_POS_PID
  DRV_SET_POS,
#endif
} DRV_Commands;

typedef struct {
  DRV_Commands cmd;
  union {
    DRV_Mode mode; /* DRV_SET_MODE */
    struct {
      int32_t left, right;
    } speed; /* DRV_SET_SPEED */
#if PL_HAS_POS_PID
   struct {
      int32_t left, right;
    } pos; /* DRV_SET_POS */
#endif
  } u;
} DRV_Command;

#define QUEUE_LENGTH      4 /* number of items in queue, that's my buffer size */
#define QUEUE_ITEM_SIZE   sizeof(DRV_Command) /* each item is a single drive command */
static QueueHandle_t DRV_Queue;

bool DRV_IsStopped(void) {
#if PL_HAS_MOTOR_TACHO
  Q4CLeft_QuadCntrType leftPos;
  Q4CRight_QuadCntrType rightPos;
#endif

  if (FRTOS1_uxQueueMessagesWaiting(DRV_Queue)>0) {
    return FALSE; /* still messages in command queue, so there is something pending */
  }
#if PL_HAS_MOTOR_TACHO
  /* do *not* use/calculate speed: too slow! Use position encoder instead */
  leftPos = Q4CLeft_GetPos();
  rightPos = Q4CRight_GetPos();
  if (DRV_Status.mode==DRV_MODE_POS) {
  #if PL_HAS_HIGH_RES_ENCODER
    if (DRV_Status.pos.left!=(int32_t)leftPos) {
      return FALSE;
    }
    if (DRV_Status.pos.right!=(int32_t)rightPos) {
      return FALSE;
    }
  #else
    if (DRV_Status.pos.left!=(int32_t)leftPos) {
      return FALSE;
    }
    if (DRV_Status.pos.right!=(int32_t)rightPos) {
      return FALSE;
    }
  #endif
    return TRUE;
  } if (DRV_Status.mode==DRV_MODE_STOP) {
    return TRUE;
  } else {
    /* ???? what to do otherwise ???? */
    return FALSE;
  }
#else
  return TRUE; /*! \todo */
#endif
}

uint8_t DRV_Stop(int32_t timeoutMs) {
  (void)DRV_SetMode(DRV_MODE_STOP); /* stop it */
  do {
    if (DRV_IsStopped()) {
      break;
    }
    WAIT1_WaitOSms(5);
    timeoutMs -= 5;
  } while (timeoutMs>0);
  if (timeoutMs<0) {
    return ERR_BUSY; /* timeout */
  }
  return ERR_OK;
}

bool DRV_IsDrivingBackward(void) {
  return DRV_Status.mode==DRV_MODE_SPEED
      && DRV_Status.speed.left<0
      && DRV_Status.speed.right<0;
}

#if PL_HAS_POS_PID
static bool match(int16_t pos, int16_t target) {
#if PL_HAS_HIGH_RES_ENCODER
  #define MATCH_MARGIN  50
#else
  #define MATCH_MARGIN 0
#endif
#if MATCH_MARGIN>0
  return (pos>=target-MATCH_MARGIN && pos<=target+MATCH_MARGIN);
#else
  return pos==target;
#endif
}
#endif 

bool DRV_HasTurned(void) {
#if PL_HAS_POS_PID
  int16_t pos;

  if (FRTOS1_uxQueueMessagesWaiting(DRV_Queue)>0) {
    return FALSE; /* still messages in command queue, so there is something pending */
  }
  if (DRV_Status.mode==DRV_MODE_POS) {
#if PL_HAS_MOTOR_TACHO
#if PL_HAS_HIGH_RES_ENCODER
  #define DRV_TURN_SPEED_LOW 50
#else
  #define DRV_TURN_SPEED_LOW 5
#endif
    int32_t speedL, speedR;

    speedL = TACHO_GetSpeed(TRUE);
    speedR = TACHO_GetSpeed(FALSE);
    if (speedL>-DRV_TURN_SPEED_LOW && speedL<DRV_TURN_SPEED_LOW && speedR>-DRV_TURN_SPEED_LOW && speedR<DRV_TURN_SPEED_LOW) { /* speed close to zero */
#endif
      pos = Q4CLeft_GetPos();
      if (match(pos, DRV_Status.pos.left)) {
        pos = Q4CRight_GetPos();
        if (match(pos, DRV_Status.pos.right)) {
          return TRUE;
        }
      }
#if PL_HAS_MOTOR_TACHO
    }
#endif
    return FALSE;
  } /* if */
  return TRUE;
#else
  return TRUE;
#endif
}

DRV_Mode DRV_GetMode(void) {
  return DRV_Status.mode;
}

uint8_t DRV_SetMode(DRV_Mode mode) {
  DRV_Command cmd;

#if PL_HAS_DRIVE_STOP_POS
  if (mode==DRV_MODE_STOP) {
    (void)DRV_SetPos(Q4CLeft_GetPos(), Q4CRight_GetPos()); /* set current position */
    PID_Start(); /* reset PID, especially integral counters */
    mode = DRV_MODE_POS;
  }
#endif
  cmd.cmd = DRV_SET_MODE;
  cmd.u.mode = mode;
  if (FRTOS1_xQueueSendToBack(DRV_Queue, &cmd, portMAX_DELAY)!=pdPASS) {
    return ERR_FAILED;
  }
  FRTOS1_taskYIELD(); /* yield so drive task has a chance to read message */
  return ERR_OK;
}

uint8_t DRV_SetSpeed(int32_t left, int32_t right) {
  DRV_Command cmd;
  
  cmd.cmd = DRV_SET_SPEED;
  cmd.u.speed.left = left;
  cmd.u.speed.right = right;
  if (FRTOS1_xQueueSendToBack(DRV_Queue, &cmd, portMAX_DELAY)!=pdPASS) {
    return ERR_FAILED;
  }
  FRTOS1_taskYIELD(); /* yield so drive task has a chance to read message */
  return ERR_OK;
}

#if PL_HAS_QUADRATURE
uint8_t DRV_SetPos(int32_t left, int32_t right) {
  DRV_Command cmd;
  
  cmd.cmd = DRV_SET_POS;
  cmd.u.pos.left = left;
  cmd.u.pos.right = right;
  if (FRTOS1_xQueueSendToBack(DRV_Queue, &cmd, portMAX_DELAY)!=pdPASS) {
    return ERR_FAILED;
  }
  FRTOS1_taskYIELD(); /* yield so drive task has a chance to read message */
  return ERR_OK;
}
#endif

#if PL_CONFIG_HAS_SHELL
static uint8_t *DRV_GetModeStr(DRV_Mode mode) {
  switch(mode) {
    case DRV_MODE_NONE:   return (uint8_t*)"NONE";
    case DRV_MODE_STOP:   return (uint8_t*)"STOP";
    case DRV_MODE_SPEED:  return (uint8_t*)"SPEED";
#if PL_HAS_QUADRATURE
    case DRV_MODE_POS:    return (uint8_t*)"POS";
#endif
    default: return (uint8_t*)"UNKNOWN";
  }
}

static void DRV_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"drive", (unsigned char*)"Group of drive commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows drive help or status\r\n", io->stdOut);
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  mode <mode>", (unsigned char*)"Set driving mode (none|stop|speed|pos)\r\n", io->stdOut);
#else
  CLS1_SendHelpStr((unsigned char*)"  mode <mode>", (unsigned char*)"Set driving mode (none|stop|speed)\r\n", io->stdOut);
#endif
  CLS1_SendHelpStr((unsigned char*)"  speed <left> <right>", (unsigned char*)"Move left and right motors with given speed\r\n", io->stdOut);
#if PL_HAS_POS_PID
  CLS1_SendHelpStr((unsigned char*)"  pos <left> <right>", (unsigned char*)"Move left and right wheels to given position\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  pos reset", (unsigned char*)"Reset drive and wheel position\r\n", io->stdOut);
#endif
}

static void DRV_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];

  CLS1_SendStatusStr((unsigned char*)"drive", (unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  mode", DRV_GetModeStr(DRV_Status.mode), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  UTIL1_Num32sToStr(buf, sizeof(buf), DRV_Status.speed.left);
#if PL_HAS_MOTOR_TACHO
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps/sec\r\n");
#else
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" % PWM\r\n");
#endif
  CLS1_SendStatusStr((unsigned char*)"  speed left", buf, io->stdOut);

  UTIL1_Num32sToStr(buf, sizeof(buf), DRV_Status.speed.right);
#if PL_HAS_MOTOR_TACHO
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps/sec\r\n");
#else
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" % PWM\r\n");
#endif
  CLS1_SendStatusStr((unsigned char*)"  speed right", buf, io->stdOut);

#if PL_HAS_POS_PID
  UTIL1_Num32sToStr(buf, sizeof(buf), DRV_Status.pos.left);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" (curr: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), (int32_t)Q4CLeft_GetPos());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");
  CLS1_SendStatusStr((unsigned char*)"  pos left", buf, io->stdOut);
  
  UTIL1_Num32sToStr(buf, sizeof(buf), DRV_Status.pos.right);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" (curr: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), (int32_t)Q4CRight_GetPos());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");
  CLS1_SendStatusStr((unsigned char*)"  pos right", buf, io->stdOut);
#endif
}

uint8_t DRV_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  int32_t val1, val2;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"drive help")==0) {
    DRV_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"drive status")==0) {
    DRV_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"drive speed ", sizeof("drive speed ")-1)==0) {
    p = cmd+sizeof("drive speed");
    if (UTIL1_xatoi(&p, &val1)==ERR_OK) {
      if (UTIL1_xatoi(&p, &val2)==ERR_OK) {
        if (DRV_SetSpeed(val1, val2)!=ERR_OK) {
          CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
        }
        *handled = TRUE;
      } else {
        CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
      }
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument(s)\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#if PL_HAS_POS_PID
  } else if (UTIL1_strncmp((char*)cmd, (char*)"drive pos reset", sizeof("drive pos reset")-1)==0) {
    Q4CLeft_SetPos(0);
    Q4CRight_SetPos(0);
    if (DRV_SetPos(0, 0)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"drive pos ", sizeof("drive pos ")-1)==0) {
    p = cmd+sizeof("drive pos");
    if (UTIL1_xatoi(&p, &val1)==ERR_OK) {
      if (UTIL1_xatoi(&p, &val2)==ERR_OK) {
        if (DRV_SetPos(val1, val2)!=ERR_OK) {
          CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
        }
        *handled = TRUE;
      } else {
        CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
      }
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument(s)\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
  } else if (UTIL1_strncmp((char*)cmd, (char*)"drive mode ", sizeof("drive mode ")-1)==0) {
    p = cmd+sizeof("drive mode");
    if (UTIL1_strcmp((char*)p, (char*)"none")==0) {
      if (DRV_SetMode(DRV_MODE_NONE)!=ERR_OK) {
        res = ERR_FAILED;
      }
    } else if (UTIL1_strcmp((char*)p, (char*)"stop")==0) {
      if (DRV_SetMode(DRV_MODE_STOP)!=ERR_OK) {
        res = ERR_FAILED;
      }
    } else if (UTIL1_strcmp((char*)p, (char*)"speed")==0) {
      if (DRV_SetMode(DRV_MODE_SPEED)!=ERR_OK) {
        res = ERR_FAILED;
      }
#if PL_HAS_QUADRATURE
    } else if (UTIL1_strcmp((char*)p, (char*)"pos")==0) {
      if (DRV_SetMode(DRV_MODE_POS)!=ERR_OK) {
        res = ERR_FAILED;
      }
#endif
    } else {
      res = ERR_FAILED;
    }
    if (res!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed\r\n", io->stdErr);
    }
    *handled = TRUE;
  }
  return res;
}
#endif /* PL_CONFIG_HAS_SHELL */

static uint8_t GetCmd(void) {
  DRV_Command cmd;
  portBASE_TYPE res;

  res = FRTOS1_xQueueReceive(DRV_Queue, &cmd, 0);
  if (res==errQUEUE_EMPTY) {
    return ERR_RXEMPTY; /* no command */
  } 
  /* process command */
  FRTOS1_taskENTER_CRITICAL();
  if (cmd.cmd==DRV_SET_MODE) {
#if PL_HAS_PID
    PID_Start(); /* reset PID, especially integral counters */
#endif
    DRV_Status.mode = cmd.u.mode;
  } else if (cmd.cmd==DRV_SET_SPEED) {
    DRV_Status.speed.left = cmd.u.speed.left;
    DRV_Status.speed.right = cmd.u.speed.right;
#if PL_HAS_POS_PID
  } else if (cmd.cmd==DRV_SET_POS) {
    DRV_Status.pos.left = cmd.u.pos.left;
    DRV_Status.pos.right = cmd.u.pos.right;
#endif
  }
  FRTOS1_taskEXIT_CRITICAL();
#if PRINT_DRIVE_INFO
  {
    uint8_t buf[32];

    if (cmd.cmd==DRV_SET_MODE) {
      UTIL1_strcpy(buf, sizeof(buf), "SETMODE: ");
      UTIL1_strcat(buf, sizeof(buf), DRV_GetModeStr(DRV_Status.mode));
    } else if (cmd.cmd==DRV_SET_SPEED) {
      UTIL1_strcpy(buf, sizeof(buf), "SETSPEED: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), DRV_Status.speed.left);
      UTIL1_strcat(buf, sizeof(buf), ", ");
      UTIL1_strcatNum32s(buf, sizeof(buf), DRV_Status.speed.right);
    } else if (cmd.cmd==DRV_SET_POS) {
      UTIL1_strcpy(buf, sizeof(buf), "SETPOS: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), DRV_Status.pos.left);
      UTIL1_strcat(buf, sizeof(buf), ", ");
      UTIL1_strcatNum32s(buf, sizeof(buf), DRV_Status.pos.right);
    } else {
      UTIL1_strcpy(buf, sizeof(buf), "ERROR!");
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    SHELL_SendString(buf);
  }
#endif
  return ERR_OK;
}

static void DriveTask(void *pvParameters) {
  TickType_t xLastWakeTime;
#if !PL_HAS_MOTOR_TACHO
  DRV_Mode prevMode;
#endif
  
  (void)pvParameters;
  xLastWakeTime = xTaskGetTickCount();
#if !PL_HAS_MOTOR_TACHO
  prevMode = DRV_MODE_NONE;
#endif
  for(;;) {
    while (GetCmd()==ERR_OK) { /* returns ERR_RXEMPTY if queue is empty */
      /* process incoming commands */
    }
#if PL_HAS_MOTOR_TACHO
    TACHO_CalcSpeed();
#endif
    if (DRV_Status.mode==DRV_MODE_SPEED) {
#if PL_HAS_SPEED_PID
      PID_Speed(TACHO_GetSpeed(TRUE), DRV_Status.speed.left, TRUE);
      PID_Speed(TACHO_GetSpeed(FALSE), DRV_Status.speed.right, FALSE);
#else
      {
        MOT_SpeedPercent speedL, speedR;
        
        if (DRV_Status.speed.left<-100) {
          speedL = -60; /* limit to avoid battery drop! */
        } else if (DRV_Status.speed.left>100) {
          speedL = 60; /* limit to avoid battery drop! */
        } else {
          speedL = DRV_Status.speed.left;
        }
        if (DRV_Status.speed.right<-100) {
          speedR = -60;
        } else if (DRV_Status.speed.right>100) {
          speedR = 60;
        } else {
          speedR = DRV_Status.speed.right;
        }
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), speedL);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), speedR);
      }
#endif
    } else if (DRV_Status.mode==DRV_MODE_STOP) {
#if PL_HAS_SPEED_PID
      PID_Speed(TACHO_GetSpeed(TRUE), 0, TRUE);
      PID_Speed(TACHO_GetSpeed(FALSE), 0, FALSE);
#elif !PL_HAS_MOTOR_TACHO
      if (prevMode!=DRV_MODE_STOP) { /* stop motors */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      }
#endif
#if PL_HAS_POS_PID
    } else if (DRV_Status.mode==DRV_MODE_POS) {
      PID_Pos(Q4CLeft_GetPos(), DRV_Status.pos.left, TRUE);
      PID_Pos(Q4CRight_GetPos(), DRV_Status.pos.right, FALSE);
#endif
    } else if (DRV_Status.mode==DRV_MODE_NONE) {
      /* do nothing */
    }
#if !PL_HAS_MOTOR_TACHO
    prevMode = DRV_Status.mode;
#endif
    vTaskDelayUntil(&xLastWakeTime, 5/portTICK_PERIOD_MS);
  } /* for */
}

void DRV_Deinit(void) {
  FRTOS1_vQueueDelete(DRV_Queue);
}

void DRV_Init(void) {
#if PL_HAS_REMOTE
  DRV_Status.mode = DRV_MODE_SPEED;
#else
  DRV_Status.mode = DRV_MODE_NONE;
#endif
  DRV_Status.speed.left = 0;
  DRV_Status.speed.right = 0;
#if PL_HAS_QUADRATURE
  DRV_Status.pos.left = 0;
  DRV_Status.pos.right = 0;
#endif
  DRV_Queue = FRTOS1_xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
  if (DRV_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  FRTOS1_vQueueAddToRegistry(DRV_Queue, "Drive");
#if configUSE_TRACE_HOOKS
  PTRC1_vTraceSetQueueName(DRV_Queue, "Drive");
#endif
  if (FRTOS1_xTaskCreate(DriveTask, "Drive", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_DRIVE */
