/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_STEPPER
#include "stepperConfig.h"
#include "stepper.h"
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#elif PL_CONFIG_USE_ULN2003
  #include "McuULN2003.h"
#elif PL_CONFIG_USE_STEPPER_EMUL
  #include "NeoStepperRing.h"
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "leds.h"
#include "Shell.h"
#include "matrix.h"
#if McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_ctimer.h"
  #include "fsl_sctimer.h"
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_pit.h"
#endif
#include "StepperBoard.h"

#define STEPPER_CMD_QUEUE_LENGTH    (8) /* maximum number of items in stepper command queue */

typedef enum {
  SCT_CHANNEL_MASK_0 = (1<<0),
  SCT_CHANNEL_MASK_1 = (1<<1),
  SCT_CHANNEL_MASK_2 = (1<<2),
  SCT_CHANNEL_MASK_3 = (1<<3),
  SCT_CHANNEL_MASK_4 = (1<<4),
  SCT_CHANNEL_MASK_5 = (1<<5),
  SCT_CHANNEL_MASK_6 = (1<<6),
  SCT_CHANNEL_MASK_7 = (1<<7)
} SCT_CHANNEL_MASK_e;


/* default configuration, used for initializing the config */
static const STEPPER_Config_t defaultConfig =
{
  .device = NULL, /* motor or LED device */
  .stepFn = NULL, /* callback to increment or decrement steps */
};

/* device for a single LED ring */
typedef struct {
  void *device; /* point to the actual motor device */
  void (*stepFn)(void *device, int step); /* function pointer to perform a single step forward (1) or backward (-1) */
  int32_t pos; /* current position */
  int32_t doSteps; /* != 0: steps to do */
  int16_t delay; /* shortest delay: 0 */
  int16_t delayCntr; /* in the range of delay..0, step will be done at counter of 0 */
  int32_t accelStepCntr; /* current counter of steps since start */
  bool speedup, slowdown;
  QueueHandle_t queue; /* queue for the motor */
} STEPPER_Device_t;

void STEPPER_GetDefaultConfig(STEPPER_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

STEPPER_Handle_t STEPPER_DeinitDevice(STEPPER_Handle_t device) {
#if STEPPER_CONFIG_USE_FREERTOS_HEAP
  vPortFree(device);
#else
  free(device);
#endif
  return NULL;
}

STEPPER_Handle_t STEPPER_InitDevice(STEPPER_Config_t *config) {
  STEPPER_Device_t *handle;

#if STEPPER_CONFIG_USE_FREERTOS_HEAP
  handle = (STEPPER_Device_t*)pvPortMalloc(sizeof(STEPPER_Device_t)); /* get a new device descriptor */
#else
  handle = (STEPPER_Device_t*)malloc(sizeof(STEPPER_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(STEPPER_Device_t)); /* init all fields */
    handle->device = config->device;
    handle->stepFn = config->stepFn;
    handle->pos = 0;
    handle->doSteps = 0;
    handle->delay = 0;
    handle->delayCntr = 0;
    handle->speedup = false;
    handle->slowdown = false;
    handle->queue = xQueueCreate(STEPPER_CMD_QUEUE_LENGTH, sizeof(uint8_t*));
    if (handle->queue==NULL) {
      for(;;){} /* out of memory? */
    }
    vQueueAddToRegistry(handle->queue, "Squeue");
  }
  return handle;
}

#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #define STEPPER_START_TIMER()        SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L)
  #define STEPPER_STOP_TIMER()         SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_L)
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define PIT_BASEADDR       PIT
  #define PIT_SOURCE_CLOCK   CLOCK_GetFreq(kCLOCK_BusClk)
  #define PIT_CHANNEL        kPIT_Chnl_0
  #define PIT_HANDLER        PIT0_IRQHandler
  #define PIT_IRQ_ID         PIT0_IRQn

  #define STEPPER_START_TIMER()        PIT_StartTimer(PIT_BASEADDR, PIT_CHANNEL)
  #define STEPPER_STOP_TIMER()         PIT_StopTimer(PIT_BASEADDR, PIT_CHANNEL)
#endif
#define STEPPER_ACCEL_HIGHEST_POS   (300)

void STEPPER_StopTimer(void) {
  STEPPER_STOP_TIMER();
}

void STEPPER_StartTimer(void) {
  STEPPER_START_TIMER();
}

#if STEPPER_CONFIG_IS_LED_RING
  #define STEP_SIZE  (12)
#else
  #define STEP_SIZE  (1)
#endif

static void AccelDelay(STEPPER_Device_t *mot, int32_t steps) {
  if (steps<=STEPPER_ACCEL_HIGHEST_POS) {
    if (steps<=50) {
      mot->delayCntr += 10*STEP_SIZE;
    } else if (steps<=100) {
      mot->delayCntr += 7*STEP_SIZE;
    } else if (steps<=150) {
      mot->delayCntr += 5*STEP_SIZE;
    } else if (steps<=250) {
      mot->delayCntr += 3*STEP_SIZE;
    } else if (steps<=STEPPER_ACCEL_HIGHEST_POS) {
      mot->delayCntr += 1*STEP_SIZE;
    }
  }
}

bool STEPPER_IsIdle(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *mot = (STEPPER_Device_t*)stepper;
  return mot->doSteps==0;
}

bool STEPPER_TimerClockCallback(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *mot = (STEPPER_Device_t*)stepper;
  int n;

  if (mot->doSteps==0) {
    return false; /* no work to do */
  }
  if (mot->delayCntr!=0) { /* delay going on? */
    mot->delayCntr -= STEP_SIZE; /* decrement delay counter */
    return true; /* still work go do */
  }
  if (mot->doSteps > 0) { /* forward */
    n = STEP_SIZE; /* number of steps in one iteration */
  } else { /* backward */
    n = -STEP_SIZE;
  }
  mot->pos += n; /* update position */
  if (mot->stepFn!=NULL) { /* call driver */
    mot->stepFn(mot->device, n);
  }
  mot->doSteps -= n; /* update remaining steps */
  mot->delayCntr = mot->delay*STEP_SIZE; /* reload delay counter */
#if 0
  /* check if we have to speed up or slow down */
  if (mot->speedup || mot->slowdown) {
    int32_t stepsToGo; /* where we are in the sequence */

    stepsToGo = mot->doSteps;
    if (stepsToGo<0) { /* make it positive */
      stepsToGo = -stepsToGo;
    }
    if (mot->speedup && stepsToGo>STEPPER_ACCEL_HIGHEST_POS) { /* accelerate */
      if (mot->accelStepCntr<=STEPPER_ACCEL_HIGHEST_POS) {
        mot->accelStepCntr += STEP_SIZE;
      }
      AccelDelay(mot, mot->accelStepCntr);
    } else if (mot->slowdown && stepsToGo<STEPPER_ACCEL_HIGHEST_POS) { /* slow down */
      if (mot->accelStepCntr>=0) {
        mot->accelStepCntr -= STEP_SIZE;
      }
      AccelDelay(mot, mot->accelStepCntr);
    }
  } /* speed up or slow down */
#endif
  return true; /* still work to do */
}

#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
static void SCTIMER_Handler0(void) {
  uint32_t flags;

  flags = SCTIMER_GetStatusFlags(SCT0);
  if (flags & SCT_CHANNEL_MASK_0) {
    SCTIMER_ClearStatusFlags(SCT0, SCT_CHANNEL_MASK_0); /* Clear interrupt flag */
    MATRIX_TimerCallback();
  }
}
#elif McuLib_CONFIG_CPU_IS_KINETIS
void PIT_HANDLER(void) {
  PIT_ClearStatusFlags(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerFlag);
  MATRIX_TimerCallback();
  __DSB();
}
#endif

#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
static void Timer_Init(void) {
  uint32_t eventNumberOutput = 0;
  sctimer_config_t sctimerInfo;
  uint32_t matchValue;
  status_t status;

  SCTIMER_GetDefaultConfig(&sctimerInfo);
  SCTIMER_Init(SCT0, &sctimerInfo);
  matchValue = USEC_TO_COUNT(200, CLOCK_GetFreq(kCLOCK_CoreSysClk));
  status = SCTIMER_CreateAndScheduleEvent(SCT0, kSCTIMER_MatchEventOnly, matchValue, 0 /* dummy I/O */, kSCTIMER_Counter_L /* dummy */, &eventNumberOutput);
  if (status==kStatus_Fail || eventNumberOutput!=0) {
    for(;;) {} /* should not happen! */
  }
  SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_L, eventNumberOutput);
  SCTIMER_SetCallback(SCT0, SCTIMER_Handler0, eventNumberOutput);
  SCTIMER_EnableInterrupts(SCT0, (1<<eventNumberOutput));
  NVIC_SetPriority(SCT0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1); /* less urgent than RS-485 Rx interrupt! */
  EnableIRQ(SCT0_IRQn); /* Enable at the NVIC */
}
#elif McuLib_CONFIG_CPU_IS_KINETIS
static void Timer_Init(void) {
  pit_config_t config;
  uint32_t delta = 0;

  PIT_GetDefaultConfig(&config);
  config.enableRunInDebug = false;
  PIT_Init(PIT_BASEADDR, &config);
  /* note: the LPC is running on 200us, but the K22 is a bit faster, so running slower */
#if STEPPER_CONFIG_IS_LED_RING
  /* \todo Timer is off about 25% (too fast?) */
  PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(12*(200U+100)+delta, PIT_SOURCE_CLOCK));
#else
  PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(200U+delta, PIT_SOURCE_CLOCK));
#endif
  PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
  NVIC_SetPriority(PIT_IRQ_ID, 1); /* \todo not 0, in order not to interrupt the DMA? */
  EnableIRQ(PIT_IRQ_ID);
}
#endif

/*!
 * \brief Move clock to absolute degree position
 */
void STEPPER_MoveClockDegreeAbs(STEPPER_Handle_t stepper, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown) {
  int32_t steps, currPos, targetPos;
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;

  if (degree<0) {
	  degree = 360+degree;
  }
  degree %= 360;
  targetPos = (STEPPER_CLOCK_360_STEPS*degree)/360;
  currPos = device->pos;
  currPos %= STEPPER_CLOCK_360_STEPS;
  if (currPos<0) { /* make it positive */
    currPos = STEPPER_CLOCK_360_STEPS+currPos;
  }
  if (mode==STEPPER_MOVE_MODE_CW) {
    steps = targetPos-currPos;
    if (steps<0) {
      steps = STEPPER_CLOCK_360_STEPS+steps;
    }
  } else if (mode==STEPPER_MOVE_MODE_CCW) {
    steps = targetPos-currPos;
    if (steps>0) {
      steps = -STEPPER_CLOCK_360_STEPS+steps;
    }
  } else { /* STEPPER_MOVE_MODE_SHORT */
    steps = targetPos-currPos;
    if (steps>STEPPER_CLOCK_360_STEPS/2) {
      steps = -(STEPPER_CLOCK_360_STEPS-steps);
    } else if (steps < -(STEPPER_CLOCK_360_STEPS/2)) {
      steps = -(-STEPPER_CLOCK_360_STEPS-steps);
    }
  }
  device->doSteps = steps;
  device->accelStepCntr = 0;
  device->delay = delay;
  device->speedup = speedUp;
  device->slowdown = slowDown;
}

void STEPPER_MoveMotorStepsRel(STEPPER_Handle_t stepper, int32_t steps, uint16_t delay) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;

  device->doSteps = steps;
  device->accelStepCntr = 0;
  device->delay = delay;
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveMotorDegreeRel(STEPPER_Handle_t stepper, int32_t degree, uint16_t delay) {
  int32_t steps;

  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  STEPPER_MoveMotorStepsRel(stepper, steps, delay);
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveClockDegreeRel(STEPPER_Handle_t stepper, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  int32_t steps;

  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  if (mode==STEPPER_MOVE_MODE_CCW) { /* invert direction */
    steps = -steps;
  }
  device->doSteps = steps;
  device->accelStepCntr = 0;
  device->delay = delay;
  device->delayCntr = delay;
  device->speedup = speedUp;
  device->slowdown = slowDown;
}

void *STEPPER_GetDevice(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  return device->device;
}

void STEPPER_Deinit(void) {
}

QueueHandle_t STEPPER_GetQueue(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  return device->queue;
}

void STEPPER_StrCatStatus(STEPPER_Handle_t stepper, unsigned char *buf, size_t bufSize) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;

  McuUtility_strcat(buf, bufSize, (unsigned char*)"pos:");
  McuUtility_strcatNum32sFormatted(buf, bufSize, device->pos, ' ', 5);
#if 0 && PL_CONFIG_USE_NVMC
  McuUtility_strcat(buf, bufSize, (unsigned char*)", offs:");
  McuUtility_strcatNum16sFormatted(buf, bufSize, NVMC_GetStepperZeroOffset(i, 0), ' ', 4);
#endif
  McuUtility_strcat(buf, bufSize, (unsigned char*)", delay:");
  McuUtility_strcatNum16sFormatted(buf, bufSize, device->delay, ' ', 2);
  McuUtility_strcat(buf, bufSize, (unsigned char*)", #qItem:");
  McuUtility_strcatNum16sFormatted(buf, bufSize, uxQueueMessagesWaiting(device->queue), ' ', 2);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[128];

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"Stepper clock settings\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"360 degree steps: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), STEPPER_CLOCK_360_STEPS);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  steps", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "stepper help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "stepper status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
#if 0
  } else if (McuUtility_strcmp((char*)cmd, "stepper reset")==0) {
    *handled = TRUE;
#if PL_CONFIG_USE_X12_STEPPER
    McuX12_017_ResetDriver(STEPPER_Clocks[0].mot[X12_017_M0].device);
#endif
    return ERR_OK;
#endif
#if 0
  } else if (McuUtility_strncmp((char*)cmd, "stepper step ", sizeof("stepper step ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper step ")-1;
    if (McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS) {
      if (McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS) {
        if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
#if PL_CONFIG_USE_X12_STEPPER
          McuX12_017_DoSteps(STEPPER_Clocks[clk].mot[m].device, STEPPER_Clocks[clk].mot[m].mot, steps);
#endif
          return ERR_OK;
        } else {
          return ERR_FAILED;
        }
      } else {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
#endif
#if 0
  } else if (McuUtility_strncmp((char*)cmd, "stepper goto ", sizeof("stepper goto ")-1)==0) {
    int32_t steps;

    *handled = TRUE;
    p = cmd + sizeof("stepper goto ")-1;
    if (McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS) {
      if (McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS) {
        if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
          STEPPER_Clocks[clk].mot[m].doSteps = steps;
          STEPPER_Clocks[clk].mot[m].accelStepCntr = 0;
        }
      } else {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
    STEPPER_START_TIMER();
    return ERR_OK;
#endif
  }
  return res;
}

int32_t STEPPER_GetPos(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  return device->pos;
}

void STEPPER_SetPos(STEPPER_Handle_t stepper, int32_t pos) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  device->pos = pos;
}

void STEPPER_NormalizePosition(STEPPER_Handle_t stepper) {
  STEPPER_Device_t *device = (STEPPER_Device_t*)stepper;
  device->pos %= STEPPER_CLOCK_360_STEPS;
}

void STEPPER_Init(void) {
  Timer_Init();
}

#endif /* PL_CONFIG_USE_STEPPER */
