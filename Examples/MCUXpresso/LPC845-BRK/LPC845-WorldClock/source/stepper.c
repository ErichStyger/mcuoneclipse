/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_STEPPER
#include "stepper.h"
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#else
  #include "McuULN2003.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "leds.h"
#include "Shell.h"

#include "fsl_ctimer.h"
#include "fsl_sctimer.h"

#define STEPPER_HAND_ZERO_DELAY   (6)

#define STEPPER_CMD_QUEUE_LENGTH    (8) /* number of items in stepper command queue */
static bool STEPPER_ExecuteQueue = false; /* only a flag: if the execute command comes from RS-485, it will be executed as part of the shell loop */

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

typedef struct STEPPER_Motor_t {
  McuX12_017_Handle_t device; /* X12.017 device */
  McuX12_017_Motor_e mot; /* motor id */
  MAG_MagSensor_e mag; /* magnet sensor for motor */
  int32_t doSteps; /* != 0: steps to do */
  int16_t delay; /* shortest delay: 0 */
  int16_t delayCntr; /* in the range of delay..0, step will be done at counter of 0 */
  /* acceleration and de-acceleration */
  //const uint16_t (*accelTable)[2]; /* acceleration table */
  //uint16_t nofAccelTableEntries; /* number of entries in acceTable */
  int32_t accelStepCntr; /* current counter of steps since start */
  bool speedup, slowdown;
  /* queue */
  QueueHandle_t queue; /* queue for the motor */
} STEPPER_Motor_t;

typedef struct STEPPER_Clock_t {
  STEPPER_Motor_t mot[STEPPER_NOF_CLOCK_MOTORS]; /* [0]: hh, inner motor, higher hand, [1]: outer motor, lower hand */
} STEPPER_Clock_t;

static STEPPER_Clock_t STEPPER_Clocks[STEPPER_NOF_CLOCKS];

bool STEPPER_IsIdle(void) {
  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
      if (STEPPER_Clocks[i].mot[j].doSteps!=0) { /* still steps to do? */
        return false; /* yes, not finished */
      }
    }
  }
  return true; /* finished */
}

#define STEPPER_StartTimer()        SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
#define STEPPER_StopTimer()         SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_L);
#define STEPPER_ACCEL_HIGHEST_POS   (300)

static void AccelDelay(STEPPER_Motor_t *mot, int32_t steps) {
  if (steps<=STEPPER_ACCEL_HIGHEST_POS) {
    if (steps<=50) {
      mot->delayCntr += 10;
    } else if (steps<=100) {
      mot->delayCntr += 7;
    } else if (steps<=150) {
      mot->delayCntr += 5;
    } else if (steps<=250) {
      mot->delayCntr += 3;
    } else if (steps<=STEPPER_ACCEL_HIGHEST_POS) {
      mot->delayCntr += 1;
    }
  }
}

static bool STEPPER_TimerClockCallback(STEPPER_Motor_t *mot) {
  if (mot->delayCntr==0) { /* delay expired */
    if (mot->doSteps!=0) { /* a step to do */
      if (mot->doSteps > 0) {
        McuX12_017_SingleStep(mot->device, mot->mot, 1);
        mot->doSteps--;
      } else if (mot->doSteps < 0)  {
        McuX12_017_SingleStep(mot->device, mot->mot, -1);
        mot->doSteps++;
      }
      mot->delayCntr = mot->delay; /* reload delay counter */
      if (mot->speedup || mot->slowdown) {
        int32_t stepsToGo;;

        stepsToGo = mot->doSteps;
        if (stepsToGo<0) { /* make it positive */
          stepsToGo = -stepsToGo;
        }
        if (mot->speedup && stepsToGo>STEPPER_ACCEL_HIGHEST_POS) { /* accelerate */
          if (mot->accelStepCntr<=STEPPER_ACCEL_HIGHEST_POS) {
            mot->accelStepCntr++;
          }
          AccelDelay(mot, mot->accelStepCntr);
        } else if (mot->slowdown && stepsToGo<STEPPER_ACCEL_HIGHEST_POS) { /* slow down */
          if (mot->accelStepCntr>=0) {
            mot->accelStepCntr--;
          }
          mot->accelStepCntr--;
          AccelDelay(mot, mot->accelStepCntr);
        }
      }
    } else {
      return false; /* no work to do */
    }
  } else {
    mot->delayCntr--; /* decrement delay counter */
  }
  return true; /* still work to do */
}

static void STEPPER_TimerCallback(void) {
  bool workToDo = false;

  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
     for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) { /* go through all motors */
       workToDo |= STEPPER_TimerClockCallback(&STEPPER_Clocks[i].mot[j]);
    } /* for */
  }
  /* check if we can stop timer */
  if (!workToDo) {
    STEPPER_StopTimer();
  }
}

static void SCTIMER_Handler0(void) {
  uint32_t flags;

  flags = SCTIMER_GetStatusFlags(SCT0);
  if (flags & SCT_CHANNEL_MASK_0) {
    SCTIMER_ClearStatusFlags(SCT0, SCT_CHANNEL_MASK_0); /* Clear interrupt flag */
    STEPPER_TimerCallback();
  }
}

static void SCTMR_Init(void) {
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

void STEPPER_MoveAndWait(uint32_t waitMs) {
  STEPPER_StartTimer();
  do {
    vTaskDelay(pdMS_TO_TICKS(waitMs));
#if PL_CONFIG_USE_WDT
    WDT_Report(WDT_REPORT_ID_CURR_TASK, waitMs);
#endif
  } while (!STEPPER_IsIdle());
}

/*!
 * \brief Move clock to absolute degree position
 */
void STEPPER_MoveClockDegreeAbs(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown) {
  int32_t steps, currPos, targetPos;
  STEPPER_Clock_t *clock;

  clock = &STEPPER_Clocks[clk];
  if (degree<0) {
	  degree = 360+degree;
  }
  degree %= 360;
  targetPos = (STEPPER_CLOCK_360_STEPS*degree)/360;
  currPos = X12_017_GetPos(clock->mot[motorIndex].device, clock->mot[motorIndex].mot)%STEPPER_CLOCK_360_STEPS;
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
  clock->mot[motorIndex].doSteps = steps;
  clock->mot[motorIndex].accelStepCntr = 0;
  clock->mot[motorIndex].delay = delay;
  clock->mot[motorIndex].speedup = speedUp;
  clock->mot[motorIndex].slowdown = slowDown;
}

void STEPPER_MoveMotorStepsRel(STEPPER_Motor_t *motor, int32_t steps, uint16_t delay) {
  motor->doSteps = steps;
  motor->accelStepCntr = 0;
  motor->delay = delay;
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveMotorDegreeRel(STEPPER_Motor_t *motor, int32_t degree, uint16_t delay) {
  int32_t steps;

  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  STEPPER_MoveMotorStepsRel(motor, steps, delay);
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveClockDegreeRel(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown) {
  int32_t steps;
  STEPPER_Clock_t *clock;

  clock = &STEPPER_Clocks[clk];
  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  clock->mot[motorIndex].doSteps = steps;
  clock->mot[motorIndex].accelStepCntr = 0;
  clock->mot[motorIndex].delay = delay;
  clock->mot[motorIndex].speedup = speedUp;
  clock->mot[motorIndex].slowdown = slowDown;
}

void STEPPER_Deinit(void) {
  McuX12_017_DeinitDevice(STEPPER_Clocks[0].mot[0].device);
  McuX12_017_DeinitDevice(STEPPER_Clocks[2].mot[0].device);
}

#if PL_CONFIG_USE_MAG_SENSOR
uint8_t STEPPER_MoveHandOnSensor(STEPPER_Motor_t *motors[], size_t nofMotors, bool onSensor, int32_t stepSize, int32_t timeoutms, uint32_t waitms, uint16_t delay) {
  uint8_t res = ERR_OK;
  bool done;

  /* move hand over sensor */
  for(;;) { /* breaks */
    done = true;
    for(int i=0; i<nofMotors; i++) { /* check if all motors are on sensor */
      if (MAG_IsTriggered(motors[i]->mag)!=onSensor) {
        done = false; /* not yet */
        break;
      }
    }
    if (done || timeoutms<0) { /* all hands on sensor */
      break;
    }
    for(int i=0; i<nofMotors; i++) {
      if (MAG_IsTriggered(motors[i]->mag)!=onSensor) {
        STEPPER_MoveMotorStepsRel(motors[i], stepSize, delay); /* make by 1 degree */
      }
    } /* for */
    STEPPER_MoveAndWait(waitms);
    timeoutms -= waitms;
  }
  if (timeoutms<0) {
    res = ERR_UNDERFLOW;
  }
  return res;
}
#endif

#if PL_CONFIG_USE_MAG_SENSOR
void STEPPER_MoveByOffset(STEPPER_Motor_t *motors[], int16_t offsets[], size_t nofMotors, uint16_t delay) {
  /* here all hands are on the sensor: adjust with offset */
   for(int i=0; i<nofMotors; i++) {
     STEPPER_MoveMotorStepsRel(motors[i], offsets[i], delay);
   } /* for */
   STEPPER_MoveAndWait(10);
}

void STEPPER_SetZeroPosition(STEPPER_Motor_t *motors[], size_t nofMotors) {
  /* set zero position */
  for(int i=0; i<nofMotors; i++) {
    X12_017_SetPos(motors[i]->device, motors[i]->mot, 0);
  }
}

uint8_t STEPPER_ZeroHand(STEPPER_Motor_t *motors[], int16_t offsets[], size_t nofMotors, uint16_t delay) {
  uint8_t res = ERR_OK;

  /* if hand is on sensor: move hand out of the sensor area */
  for(int i=0; i<nofMotors; i++) {
    if (MAG_IsTriggered(motors[i]->mag)) { /* hand on sensor? */
      STEPPER_MoveMotorDegreeRel(motors[i], 90, delay);
    }
  } /* for */
  STEPPER_MoveAndWait(10);

  /* move forward in larger steps to find sensor */
  if (STEPPER_MoveHandOnSensor(motors, nofMotors, true, 10, 10000, 10, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step back in micro-steps just to leave the sensor */
  if (STEPPER_MoveHandOnSensor(motors, nofMotors, false, -1, 10000, 10, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step forward in micro-steps just to enter the sensor again */
  if (STEPPER_MoveHandOnSensor(motors, nofMotors, true, 1, 10000, 2, delay)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* here all hands are on the sensor: adjust with offset */
  STEPPER_MoveByOffset(motors, offsets, nofMotors, delay);
  /* set zero position */
  STEPPER_SetZeroPosition(motors, nofMotors);
  return res;
}

uint8_t STEPPER_ZeroAllHands(void) {
  uint8_t res = ERR_OK;
  STEPPER_Motor_t *motors[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  int16_t offsets[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];

  /* fill in motor array information */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      motors[c*STEPPER_NOF_CLOCK_MOTORS + m] = &STEPPER_Clocks[c].mot[m];
      offsets[c*STEPPER_NOF_CLOCK_MOTORS + m] = NVMC_GetStepperZeroOffset(c, m);
    }
  }
  /* zero all of them */
  if (STEPPER_ZeroHand(motors, offsets, STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
}

uint8_t STEPPER_SetOffsetFrom12(void) {
  /* all hands shall be at 12-o-clock position */
  uint8_t res = ERR_OK;
  STEPPER_Motor_t *motors[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];
  int16_t offsets[STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS];

  /* first zero position at current position and set delay */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      X12_017_SetPos(STEPPER_Clocks[c].mot[m].device, STEPPER_Clocks[c].mot[m].mot, 0);
      STEPPER_Clocks[c].mot[m].delay = 8;
    }
  }

  /* fill in motor array information */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      motors[c*STEPPER_NOF_CLOCK_MOTORS + m] = &STEPPER_Clocks[c].mot[m];
    }
  }
  /* move forward in larger steps to find sensor */
  if (STEPPER_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), true, -10, 10000, 5, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step back in micro-steps just to leave the sensor */
  if (STEPPER_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), false, 1, 10000, 2, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
  }

  /* step forward in micro-steps just to enter the sensor again */
  if (STEPPER_MoveHandOnSensor(motors, sizeof(motors)/sizeof(motors[0]), true, -1, 10000, 2, STEPPER_HAND_ZERO_DELAY)!=ERR_OK) {
    res = ERR_FAILED;
    return res;
  }

  /* store new offsets */
  NVMC_Data_t data;

  data = *NVMC_GetDataPtr(); /* struct copy */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      data.zeroOffsets[c][m] = -X12_017_GetPos(STEPPER_Clocks[c].mot[m].device, STEPPER_Clocks[c].mot[m].mot);
    }
  }
  res = NVMC_WriteConfig(&data);
  if (res!=ERR_OK) {
    return res;
  }
  /* fill in motor array information */
  for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
    for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
      offsets[c*STEPPER_NOF_CLOCK_MOTORS + m] = NVMC_GetStepperZeroOffset(c, m);
    }
  }
  STEPPER_MoveByOffset(motors, offsets, sizeof(motors)/sizeof(motors[0]), STEPPER_HAND_ZERO_DELAY);
  return res;
}

uint8_t STEPPER_Test(int8_t clock) {
  /* Test the clock stepper motors. Pass -1 to run the test for all motors/clocks */
  for (int m=0; m<STEPPER_NOF_CLOCK_MOTORS; m++) {
    /* clockwise */
    for(int i=0; i<4; i++) {
      if (clock==-1) { /* all */
        for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
          STEPPER_MoveClockDegreeRel(c, m, 90, STEPPER_MOVE_MODE_CW, 4, true, true);
        }
      } else {
        STEPPER_MoveClockDegreeRel(clock, m, 90, STEPPER_MOVE_MODE_CW, 4, true, true);
      }
      STEPPER_MoveAndWait(1000);
    }
    /* counter-clockwise */
    for(int i=0; i<4; i++) {
      if (clock==-1) { /* all */
        for(int c=0; c<STEPPER_NOF_CLOCKS; c++) {
          STEPPER_MoveClockDegreeRel(c, m, -90, STEPPER_MOVE_MODE_CCW, 4, true, true);
        }
      } else {
        STEPPER_MoveClockDegreeRel(clock, m, -90, STEPPER_MOVE_MODE_CCW, 4, true, true);
      }
      STEPPER_MoveAndWait(1000);
    }
  }
  return ERR_OK;
}

#endif

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[128];
  unsigned char statStr[16];

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"Stepper clock settings\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"360 degree steps: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), STEPPER_CLOCK_360_STEPS);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  steps", buf, io->stdOut);

  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    buf[0] = '\0';
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"HH[pos:");
    McuUtility_strcatNum32sFormatted(buf, sizeof(buf), X12_017_GetPos(STEPPER_Clocks[i].mot[0].device, STEPPER_Clocks[i].mot[0].mot), ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", offs:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), NVMC_GetStepperZeroOffset(i, 0), ' ', 4);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", delay:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), STEPPER_Clocks[i].mot[0].delay, ' ', 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", #qItem:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), uxQueueMessagesWaiting(STEPPER_Clocks[i].mot[0].queue), ' ', 2);

    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"] MM[pos:");
    McuUtility_strcatNum32sFormatted(buf, sizeof(buf), X12_017_GetPos(STEPPER_Clocks[i].mot[1].device, STEPPER_Clocks[i].mot[1].mot), ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", offs:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), NVMC_GetStepperZeroOffset(i, 1), ' ', 4);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", delay:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), STEPPER_Clocks[i].mot[1].delay, ' ', 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", #qItem:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), uxQueueMessagesWaiting(STEPPER_Clocks[i].mot[1].queue), ' ', 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"]\r\n");

    McuUtility_strcpy(statStr, sizeof(statStr), (unsigned char*)"  clk[");
    McuUtility_strcatNum32s(statStr, sizeof(statStr), i);
    McuUtility_strcat(statStr, sizeof(statStr), (unsigned char*)"]");
    McuShell_SendStatusStr(statStr, buf, io->stdOut);
  }

  McuX12_017_GetDeviceStatusString(STEPPER_Clocks[0].mot[X12_017_M0].device, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuUtility_strcpy(statStr, sizeof(statStr), (unsigned char*)"  X12.017[0]");
  McuShell_SendStatusStr(statStr, buf, io->stdOut);

  McuX12_017_GetDeviceStatusString(STEPPER_Clocks[2].mot[X12_017_M0].device, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuUtility_strcpy(statStr, sizeof(statStr), (unsigned char*)"  X12.017[1]");
  McuShell_SendStatusStr(statStr, buf, io->stdOut);

  if (STEPPER_ExecuteQueue) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"execute: yes");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"execute: no");
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  queue", buf, io->stdOut);
#if 0
  int32_t pos;
  buf[0] = '\0';
  pos = STEPPER_MotorGetPos(motorHour);
  pos %= STEPPER_CLOCK_360_STEPS_HH;
  val = pos/(STEPPER_CLOCK_360_STEPS_HH/12);
  McuUtility_strcatNum32sFormatted(buf, sizeof(buf), val, '0', 2);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)":");
  pos = STEPPER_MotorGetPos(motorMinute);
  pos %= STEPPER_CLOCK_360_STEPS_MM;
  val = pos/(STEPPER_CLOCK_360_STEPS_MM/60);
  McuUtility_strcatNum32sFormatted(buf, sizeof(buf), val, '0', 2);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  time", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Performs a X12.017 driver reset\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test <c>", (unsigned char*)"Test stepper motors of clock (0-3), or -1 for all\r\n", io->stdOut);
#if PL_CONFIG_USE_MAG_SENSOR
  McuShell_SendHelpStr((unsigned char*)"  zero all", (unsigned char*)"Move all motors to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  zero <c> <m>", (unsigned char*)"Move clock (0-3) and motor (0-1) to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  offs <c> <m> <v>", (unsigned char*)"Set offset value for clock (0-3) and motor (0-1)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  offs 12", (unsigned char*)"Calculate offset from 12-o-clock\r\n", io->stdOut);
#endif
  McuShell_SendHelpStr((unsigned char*)"  delay <m0>...<m7>", (unsigned char*)"Set delay for motors (0..7)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  step <c> <m> <steps>", (unsigned char*)"Perform a number of (blocking) steps for clock (0-3) and motor (0-1)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  goto <c> <m> <pos>", (unsigned char*)"Goto position (non-blocking) for clock (0-3) and motor (0-1)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  m <c> <m> <a> <d> <md>", (unsigned char*)"Move the clock and motor to the angle with delay using mode (cc, cw, sh), uppercase mode letter is without accel control\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  r <c> <m> <a> <d> <md>", (unsigned char*)"Relative angle move of clock and motor and delay using mode (cc, cw, sh), uppercase mode letter is without accel control\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  q <c> <m> <cmd>", (unsigned char*)"Queue a command for clock and motor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  exq", (unsigned char*)"Execute command in queue\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  idle", (unsigned char*)"Check if steppers are idle\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t ParseStepperCommand(const unsigned char *cmd, STEPPER_Clock_e *c, STEPPER_Hand_e *m, int32_t *v, uint8_t *d, STEPPER_MoveMode_e *mode, bool *speedUp, bool *slowDown) {
  /* parse a string like <c> <m> <v> <d> <md> */
  int32_t clk, mot, val, delay;

  if (   McuUtility_xatoi(&cmd, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS
      && McuUtility_xatoi(&cmd, &mot)==ERR_OK && mot>=0 && mot<STEPPER_NOF_CLOCK_MOTORS
      && McuUtility_xatoi(&cmd, &val)==ERR_OK
      && McuUtility_xatoi(&cmd, &delay)==ERR_OK && delay>=0
     )
  {
    if (*cmd==' ') {
      cmd++;
    }
    if (*cmd=='\0') { /* mode is optional, set it to defaults */
      *mode = STEPPER_MOVE_MODE_SHORT;
      *speedUp = *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cw")==0) {
      *mode = STEPPER_MOVE_MODE_CW;
      *speedUp = *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Cw")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = false; *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cW")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = true; *slowDown = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"CW")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = *slowDown = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cc")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Cc")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = false; *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"cC")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = true; *slowDown = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"CC")==0) {
      *mode = STEPPER_MOVE_MODE_CCW;
      *speedUp = *slowDown = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"sh")==0) {
      *mode = STEPPER_MOVE_MODE_SHORT;
      *speedUp = *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"Sh")==0) {
      *mode = STEPPER_MOVE_MODE_SHORT;
      *speedUp = false; *slowDown = true;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"sH")==0) {
      *mode = STEPPER_MOVE_MODE_SHORT;
      *speedUp = true; *slowDown = false;
    } else if (McuUtility_strcmp((char*)cmd, (char*)"SH")==0) {
      *mode = STEPPER_MOVE_MODE_SHORT;
      *speedUp = *slowDown = false;
    } else {
      return ERR_FAILED;
    }
    *c = clk;
    *m = mot;
    *v = val;
    *d = delay;
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  int32_t steps, clk, m;
  const unsigned char *p;
  uint8_t res = ERR_OK;
  STEPPER_Clock_e clock;
  STEPPER_Hand_e motor;
  int32_t value;
  uint8_t delay;
  STEPPER_MoveMode_e mode;
  bool speedUp, slowDown;


  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "stepper help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "stepper status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "stepper reset")==0) {
    *handled = TRUE;
    McuX12_017_ResetDriver(STEPPER_Clocks[0].mot[X12_017_M0].device);
    return ERR_OK;
#if PL_CONFIG_USE_MAG_SENSOR
  } else if (McuUtility_strcmp((char*)cmd, "stepper zero all")==0) {
    *handled = TRUE;
    return STEPPER_ZeroAllHands();
  } else if (McuUtility_strncmp((char*)cmd, "stepper zero ", sizeof("stepper zero ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper zero ")-1;
    if (   McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS
        && McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS
       )
    {
      STEPPER_Motor_t *motors[1];
      int16_t offset;

      motors[0] = &STEPPER_Clocks[clk].mot[m];
      offset = NVMC_GetStepperZeroOffset(clk, m);
      res = STEPPER_ZeroHand(motors, &offset, 1, STEPPER_HAND_ZERO_DELAY);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed to find magnet/zero position\r\n", io->stdErr);
      }
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strcmp((char*)cmd, "stepper offs 12")==0) {
    *handled = TRUE;
    return STEPPER_SetOffsetFrom12();
  } else if (McuUtility_strncmp((char*)cmd, "stepper test ", sizeof("stepper test ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper test ")-1;
    if (McuUtility_xatoi(&p, &clk)==ERR_OK && ((clk>=0 && clk<STEPPER_NOF_CLOCKS) || clk==-1)) {
      return STEPPER_Test(clk);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "stepper offs ", sizeof("stepper offs ")-1)==0) {
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("stepper offs ")-1;
    if (   McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS
        && McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS
        && McuUtility_xatoi(&p, &val)==ERR_OK
       )
    {
  #if PL_CONFIG_USE_NVMC
      NVMC_Data_t data;

      if (NVMC_IsErased()) {
        McuShell_SendStr((unsigned char*)"FLASH is erased, initialize it first!\r\n", io->stdErr);
        return ERR_FAILED;
      }
      data = *NVMC_GetDataPtr(); /* struct copy */
      data.zeroOffsets[clk][m] = val;
      return NVMC_WriteConfig(&data);
  #endif
    } else {
      return ERR_FAILED;
    }
#endif
  } else if (McuUtility_strncmp((char*)cmd, "stepper step ", sizeof("stepper step ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper step ")-1;
    if (McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS) {
      if (McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS) {
        if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
          McuX12_017_DoSteps(STEPPER_Clocks[clk].mot[m].device, STEPPER_Clocks[clk].mot[m].mot, steps);
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
  } else if (McuUtility_strncmp((char*)cmd, "stepper m ", sizeof("stepper m ")-1)==0) { /* "stepper m <c> <m> <a> <d> <md> " */
    *handled = TRUE;
    res = ParseStepperCommand(cmd+sizeof("stepper m ")-1, &clock, &motor, &value, &delay, &mode, &speedUp, &slowDown);
    if (res==ERR_OK) {
      STEPPER_MoveClockDegreeAbs(clock, motor, value, mode, delay, speedUp, slowDown);
      STEPPER_StartTimer();
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "stepper r ", sizeof("stepper r ")-1)==0) { /* "stepper r <c> <m> <s> <d> <md> " */
    *handled = TRUE;
    res = ParseStepperCommand(cmd+sizeof("stepper r ")-1, &clock, &motor, &value, &delay, &mode, &speedUp, &slowDown);
    if (res==ERR_OK) {
      STEPPER_MoveClockDegreeRel(clock, motor, value, mode, delay, speedUp, slowDown);
      STEPPER_StartTimer();
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "stepper delay ", sizeof("stepper delay ")-1)==0) {
    int32_t i;
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("stepper delay ")-1;
    i = 0;
    while(*p!='\0') {
      if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0)
      {
        STEPPER_Clocks[i/2].mot[i%2].delay = val;
        i++;
      } else {
        res = ERR_FAILED;
        break; /* get out here */
      }
    } /* while */
    return res;
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
    STEPPER_StartTimer();
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "stepper q ", sizeof("stepper q ")-1)==0) {
    *handled = TRUE;
    unsigned char *ptr, *data;

    p = cmd + sizeof("stepper q ")-1;
    if (   McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS
        && McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS
       )
    {
      data = (unsigned char*)p;
      while(*data==' ') {
        data++;
      }
      ptr = pvPortMalloc(McuUtility_strlen((char*)data));
      if (ptr==NULL) {
        return ERR_FAILED;
      }
      strcpy((char*)ptr, (char*)data); /* copy command */
      if (xQueueSendToBack(STEPPER_Clocks[clk].mot[m].queue, &ptr, pdMS_TO_TICKS(100))!=pdTRUE) {
        return ERR_FAILED;
      }
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strcmp((char*)cmd, "stepper exq")==0) {
    STEPPER_ExecuteQueue = true;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "stepper idle")==0) {
    *handled = TRUE;
    if (STEPPER_IsIdle()) {
      McuShell_SendStr((unsigned char*)"idle\r\n", io->stdOut);
    } else {
      McuShell_SendStr((unsigned char*)"busy\r\n", io->stdOut);
    }
    return ERR_OK;
  }
  return res;
}

uint8_t STEPPER_CheckAndExecuteQueue(const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint8_t *cmd;
  bool noCommandsInQueue = true;

  if (STEPPER_ExecuteQueue) {
    for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
      for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
        if (STEPPER_Clocks[i].mot[j].doSteps==0) { /* no steps to do? */
          if (xQueueReceive(STEPPER_Clocks[i].mot[j].queue, &cmd, 0)==pdPASS) { /* check queue */
            noCommandsInQueue = false;
            res = SHELL_ParseCommand(cmd, io, true); /* parse and execute it */
            vPortFree(cmd); /* free memory for command */
          }
        }
      }
    }
    if (noCommandsInQueue && STEPPER_IsIdle()) { /* nothing pending in queues */
      STEPPER_ExecuteQueue = false;
    }
  }
  return res;
}

#if 0
void STEPPER_SetAccelTable(STEPPER_Motor_t *motor, const uint16_t (*table)[2], size_t nofTableEntries) {
  motor->accelTable = table;
  motor->nofAccelTableEntries = nofTableEntries;
}
#endif

void STEPPER_Init(void) {
  McuX12_017_Config_t config;
  McuX12_017_Handle_t device;

  McuX12_017_GetDefaultConfig(&config);

  /* initialize first X12.017 */
  /* DRV_RESET: PIO0_14 */
  config.hasReset = true;
  config.hw_reset.gpio = GPIO;
  config.hw_reset.port = 0U;
  config.hw_reset.pin  = 14U;

  /* M0_DIR: PIO1_9 */
  config.motor[X12_017_M0].hw_dir.gpio = GPIO;
  config.motor[X12_017_M0].hw_dir.port = 1U;
  config.motor[X12_017_M0].hw_dir.pin  = 9U;

  /* M0_STEP: PIO0_12 */
  config.motor[X12_017_M0].hw_step.gpio = GPIO;
  config.motor[X12_017_M0].hw_step.port = 0U;
  config.motor[X12_017_M0].hw_step.pin  = 12U;

  /* M1_DIR: PIO0_13 */
  config.motor[X12_017_M1].hw_dir.gpio = GPIO;
  config.motor[X12_017_M1].hw_dir.port = 0U;
  config.motor[X12_017_M1].hw_dir.pin  = 13U;

  /* M1_STEP: PIO1_8 */
  config.motor[X12_017_M1].hw_step.gpio = GPIO;
  config.motor[X12_017_M1].hw_step.port = 1U;
  config.motor[X12_017_M1].hw_step.pin  = 8U;

  /* M2_DIR: PIO0_4 */
  config.motor[X12_017_M2].hw_dir.gpio = GPIO;
  config.motor[X12_017_M2].hw_dir.port = 0U;
  config.motor[X12_017_M2].hw_dir.pin  = 4U;

  /* M2_STEP: PIO0_28 */
  config.motor[X12_017_M2].isInverted = true;
  config.motor[X12_017_M2].hw_step.gpio = GPIO;
  config.motor[X12_017_M2].hw_step.port = 0U;
  config.motor[X12_017_M2].hw_step.pin  = 28U;

#if PL_CONFIG_BOARD_VERSION==1 /* PIO0_11 needs external pull-up! */
  /* M3_DIR: PIO0_11 */
  config.motor[X12_017_M3].isInverted = true;
  config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  config.motor[X12_017_M3].hw_dir.port = 0U;
  config.motor[X12_017_M3].hw_dir.pin  = 11U;
#else
  /* M3_DIR: PIO0_27 */
  config.motor[X12_017_M3].isInverted = true;
  config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  config.motor[X12_017_M3].hw_dir.port = 0U;
  config.motor[X12_017_M3].hw_dir.pin  = 27U;
#endif

#if PL_CONFIG_BOARD_VERSION==1
  /* M3_STEP: PIO1_0 */
  config.motor[X12_017_M3].hw_step.gpio = GPIO;
  config.motor[X12_017_M3].hw_step.port = 1U;
  config.motor[X12_017_M3].hw_step.pin  = 0U;
#else
  /* M3_STEP: PIO0_26 */
  config.motor[X12_017_M3].hw_step.gpio = GPIO;
  config.motor[X12_017_M3].hw_step.port = 0U;
  config.motor[X12_017_M3].hw_step.pin  = 26U;
#endif
  device = McuX12_017_InitDevice(&config);

  /* create clock descriptor */
  /* M1: inner shaft */
  STEPPER_Clocks[0].mot[0].device = device;
  STEPPER_Clocks[0].mot[0].mot = X12_017_M1;
  STEPPER_Clocks[0].mot[0].mag = MAG_MAG1;
  STEPPER_Clocks[0].mot[0].doSteps = 0;
  STEPPER_Clocks[0].mot[0].accelStepCntr = 0;
  /* M0: outer shaft */
  STEPPER_Clocks[0].mot[1].device = device;
  STEPPER_Clocks[0].mot[1].mot = X12_017_M0;
  STEPPER_Clocks[0].mot[1].mag = MAG_MAG0;
  STEPPER_Clocks[0].mot[1].doSteps = 0;
  STEPPER_Clocks[0].mot[1].accelStepCntr = 0;

  /* M3: inner shaft */
  STEPPER_Clocks[1].mot[0].device = device;
  STEPPER_Clocks[1].mot[0].mot = X12_017_M3;
  STEPPER_Clocks[1].mot[0].mag = MAG_MAG2;
  STEPPER_Clocks[1].mot[0].doSteps = 0;
  STEPPER_Clocks[1].mot[0].accelStepCntr = 0;

  /* M2: outer shaft */
  STEPPER_Clocks[1].mot[1].device = device;
  STEPPER_Clocks[1].mot[1].mot = X12_017_M2;
  STEPPER_Clocks[1].mot[1].mag = MAG_MAG3;
  STEPPER_Clocks[1].mot[1].doSteps = 0;
  STEPPER_Clocks[1].mot[1].accelStepCntr = 0;

  /* initialize second X12.017 */
  config.hasReset = false; /* second device shares the reset line from the first */
  /* M4_DIR: PIO0_0 */
  config.motor[X12_017_M0].hw_dir.gpio = GPIO;
  config.motor[X12_017_M0].hw_dir.port = 0U;
  config.motor[X12_017_M0].hw_dir.pin  = 0U;

  /* M4_STEP: PIO1_7 */
  config.motor[X12_017_M0].hw_step.gpio = GPIO;
  config.motor[X12_017_M0].hw_step.port = 1U;
  config.motor[X12_017_M0].hw_step.pin  = 7U;

  /* M5_DIR: PIO0_6 */
  config.motor[X12_017_M1].hw_dir.gpio = GPIO;
  config.motor[X12_017_M1].hw_dir.port = 0U;
  config.motor[X12_017_M1].hw_dir.pin  = 6U;

  /* M5_STEP: PIO0_7 */
  config.motor[X12_017_M1].hw_step.gpio = GPIO;
  config.motor[X12_017_M1].hw_step.port = 0U;
  config.motor[X12_017_M1].hw_step.pin  = 7U;

  /* M6_DIR: PIO0_8 */
  config.motor[X12_017_M2].isInverted = true;
  config.motor[X12_017_M2].hw_dir.gpio = GPIO;
  config.motor[X12_017_M2].hw_dir.port = 0U;
  config.motor[X12_017_M2].hw_dir.pin  = 8U;

  /* M6_STEP: PIO0_9 */
  config.motor[X12_017_M2].hw_step.gpio = GPIO;
  config.motor[X12_017_M2].hw_step.port = 0U;
  config.motor[X12_017_M2].hw_step.pin  = 9U;

  /* M7_DIR: PIO1_5 */
  config.motor[X12_017_M3].isInverted = true;
  config.motor[X12_017_M3].hw_dir.gpio = GPIO;
  config.motor[X12_017_M3].hw_dir.port = 1U;
  config.motor[X12_017_M3].hw_dir.pin  = 5U;

  /* M7_STEP: PIO1_6 */
  config.motor[X12_017_M3].hw_step.gpio = GPIO;
  config.motor[X12_017_M3].hw_step.port = 1U;
  config.motor[X12_017_M3].hw_step.pin  = 6U;

  device = McuX12_017_InitDevice(&config);

  /* create clock descriptor */
  /* M3: inner shaft */
  STEPPER_Clocks[2].mot[0].device = device;
  STEPPER_Clocks[2].mot[0].mot = X12_017_M3;
  STEPPER_Clocks[2].mot[0].mag = MAG_MAG4;
  STEPPER_Clocks[2].mot[0].doSteps = 0;
  STEPPER_Clocks[2].mot[0].accelStepCntr = 0;

  /* M2: outer shaft */
  STEPPER_Clocks[2].mot[1].device = device;
  STEPPER_Clocks[2].mot[1].mot = X12_017_M2;
  STEPPER_Clocks[2].mot[1].mag = MAG_MAG5;
  STEPPER_Clocks[2].mot[1].doSteps = 0;
  STEPPER_Clocks[2].mot[1].accelStepCntr = 0;

  /* M1: inner shaft */
  STEPPER_Clocks[3].mot[0].device = device;
  STEPPER_Clocks[3].mot[0].mot = X12_017_M1;
  STEPPER_Clocks[3].mot[0].mag = MAG_MAG7;
  STEPPER_Clocks[3].mot[0].doSteps = 0;
  STEPPER_Clocks[3].mot[0].accelStepCntr = 0;

  /* M0: outer shaft */
  STEPPER_Clocks[3].mot[1].device = device;
  STEPPER_Clocks[3].mot[1].mot = X12_017_M0;
  STEPPER_Clocks[3].mot[1].mag = MAG_MAG6;
  STEPPER_Clocks[3].mot[1].doSteps = 0;
  STEPPER_Clocks[3].mot[1].accelStepCntr = 0;

  /* set default acceleration table for all motors */
  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    //STEPPER_SetAccelTable(
    //    &STEPPER_Clocks[i].mot[0],
    //    STEPPER_DefaultAccelTable,
    //    sizeof(STEPPER_DefaultAccelTable)/sizeof(STEPPER_DefaultAccelTable[0]));
    STEPPER_Clocks[i].mot[0].delay = 0;
    STEPPER_Clocks[i].mot[0].delayCntr = 0;
    //STEPPER_SetAccelTable(
    //    &STEPPER_Clocks[i].mot[1],
    //    STEPPER_DefaultAccelTable,
    //    sizeof(STEPPER_DefaultAccelTable)/sizeof(STEPPER_DefaultAccelTable[0]));
    STEPPER_Clocks[i].mot[1].delay = 0;
    STEPPER_Clocks[i].mot[1].delayCntr = 0;

    STEPPER_Clocks[i].mot[0].queue = xQueueCreate(STEPPER_CMD_QUEUE_LENGTH, sizeof(uint8_t*));
    if (STEPPER_Clocks[i].mot[0].queue==NULL) {
      for(;;){} /* out of memory? */
    }
    STEPPER_Clocks[i].mot[1].queue = xQueueCreate(STEPPER_CMD_QUEUE_LENGTH, sizeof(uint8_t*));
    if (STEPPER_Clocks[i].mot[1].queue==NULL) {
      for(;;){} /* out of memory? */
    }
  } /* for */
  McuX12_017_ResetDriver(STEPPER_Clocks[0].mot[0].device); /* shared reset line with second device */
  SCTMR_Init();
}

#endif /* PL_CONFIG_USE_STEPPER */
