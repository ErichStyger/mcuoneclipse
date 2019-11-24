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
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "leds.h"

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS   1

typedef struct STEPPER_Motor_t {
  McuX12_017_Handle_t device; /* X12.017 device */
  McuX12_017_Motor_e mot; /* motor id */
  MAG_MagSensor_e mag; /* magnet sensor for motor */
  int32_t doSteps; /* != 0: steps to do */
} STEPPER_Motor_t;

typedef struct STEPPER_Clock_t {
  STEPPER_Motor_t mot[STEPPER_NOF_CLOCK_MOTORS]; /* [0]: hh, inner motor, higher hand, [1]: outer motor, lower hand */
} STEPPER_Clock_t;

static STEPPER_Clock_t STEPPER_Clocks[STEPPER_NOF_CLOCKS] =
{ /* x -> horizontal, y -> vertical */
  [0]= {
      .mot[0] = {
          .device  = NULL,
          .mot=X12_017_M1,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
      .mot[1] = {
          .device = NULL,
          .mot=X12_017_M0,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
    },
  [1]= {
      .mot[0] = {
          .device = NULL,
          .mot=X12_017_M3,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
      .mot[1] = {
          .device = NULL,
          .mot=X12_017_M2,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
    },
  [2]= {
      .mot[0] = {
          .device = NULL,
          .mot=X12_017_M1,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
      .mot[1] = {
          .device = NULL,
          .mot=X12_017_M0,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
    },
  [3]= {
      .mot[0] = {
          .device = NULL,
          .mot=X12_017_M3,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
      .mot[1] = {
          .device = NULL,
          .mot=X12_017_M2,
          .mag = MAG_MAG0,
          .doSteps = 0,
          },
    },
};

bool STEPPER_JobIsFinished(void) {
  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
      if (STEPPER_Clocks[i].mot[j].doSteps!=0) { /* still steps to do? */
        return false; /* yes, not finished */
      }
    }
  }
  return true; /* finished */
}

static void vTimerCallback(TimerHandle_t pxTimer) {
  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
     for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
       if (STEPPER_Clocks[i].mot[j].doSteps > 0) {
         McuX12_017_SingleStep(STEPPER_Clocks[i].mot[j].device, STEPPER_Clocks[i].mot[j].mot, 1);
         STEPPER_Clocks[i].mot[j].doSteps--;
       } else if (STEPPER_Clocks[i].mot[j].doSteps < 0)  {
         McuX12_017_SingleStep(STEPPER_Clocks[i].mot[j].device, STEPPER_Clocks[i].mot[j].mot, -1);
         STEPPER_Clocks[i].mot[j].doSteps++;
       }
    }
  }
  /* check if we can stop timer */
  if (STEPPER_JobIsFinished()) {
    (void)xTimerStop(timerHndl, 0);
  }
}

void STEPPER_MoveAndWait(uint32_t waitMs) {
  (void)xTimerStart(timerHndl, 0);
  do {
    vTaskDelay(pdMS_TO_TICKS(waitMs));
  } while (!STEPPER_JobIsFinished());
}

/*!
 * \brief Move clock to absolute degree position
 */
void STEPPER_MoveClockDegreeAbs(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree, STEPPER_MoveMode_e mode) {
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
}

void STEPPER_MoveMotorStepsRel(STEPPER_Motor_t *motor, int32_t steps) {
  motor->doSteps = steps;
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveMotorDegreeRel(STEPPER_Motor_t *motor, int32_t degree) {
  int32_t steps;

  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  STEPPER_MoveMotorStepsRel(motor, steps);
}

/*!
 * \brief Move clock by relative degree
 */
void STEPPER_MoveClockHandDegreeRel(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree) {
  int32_t steps;
  STEPPER_Clock_t *clock;

  clock = &STEPPER_Clocks[clk];
  if (degree>=0) {
    steps = (STEPPER_CLOCK_360_STEPS*degree)/360;
  } else {
    steps = -(STEPPER_CLOCK_360_STEPS*-degree)/360;
  }
  clock->mot[motorIndex].doSteps = steps;
}


void STEPPER_Deinit(void) {
  McuX12_017_DeinitDevice(STEPPER_Clocks[0].mot[0].device);
  McuX12_017_DeinitDevice(STEPPER_Clocks[2].mot[0].device);
}

#if PL_CONFIG_USE_MAG_SENSOR
uint8_t STEPPER_ZeroHand(STEPPER_Motor_t *motors[], int16_t offsets[], size_t nofMotors) {
  bool done;
  int32_t timeout;
  uint8_t res = ERR_OK;

  /* if hand is on sensor: move hand out of the sensor area */
  for(int i=0; i<nofMotors; i++) {
    if (MAG_IsTriggered(motors[i]->mag)) { /* hand on sensor? */
      STEPPER_MoveMotorDegreeRel(motors[i], 90);
    }
  } /* for */
  STEPPER_MoveAndWait(10);

  /* move hand over sensor */
  timeout = 10000;
  for(;;) { /* breaks */
    done = true;
    for(int i=0; i<nofMotors; i++) { /* check if all motors are on sensor */
      if (!MAG_IsTriggered(motors[i]->mag)) {
        done = false; /* not yet */
        break;
      }
    }
    if (done || timeout<0) { /* all hands on sensor */
      break;
    }
    for(int i=0; i<nofMotors; i++) {
      if (!MAG_IsTriggered(motors[i]->mag)) {
        STEPPER_MoveMotorDegreeRel(motors[i], 1); /* make by 1 degree */
      }
    } /* for */
    STEPPER_MoveAndWait(20);
    timeout -= 20;
  }
  if (timeout<0) {
    res = ERR_UNDERFLOW;
  }
  /* here all hands are on the sensor: adjust with offset */

  /* step back in micro-steps just to leave the sensor */
  timeout = 10000;
  for(;;) { /* breaks */
    done = true;
    for(int i=0; i<nofMotors; i++) {
      if (MAG_IsTriggered(motors[i]->mag)) { /* check if all motors are not on sensor any more */
        done = false; /* still one on the sensor */
        break;
      }
    }
    if (done) { /* all hands off the sensor */
      break;
    }
    for(int i=0; i<nofMotors; i++) {
      if (MAG_IsTriggered(motors[i]->mag)) {
        STEPPER_MoveMotorStepsRel(motors[i], -1); /* step back */
      }
    } /* for */
    STEPPER_MoveAndWait(20);
    timeout -= 20;
  }
  if (timeout<0) {
    res = ERR_UNDERFLOW;
  }

  /* here all hands are on the sensor: adjust with offset */
  for(int i=0; i<nofMotors; i++) {
    STEPPER_MoveMotorStepsRel(motors[i], offsets[i]);
  } /* for */
  STEPPER_MoveAndWait(10);

  /* set zero position */
  for(int i=0; i<nofMotors; i++) {
    X12_017_SetPos(motors[i]->device, motors[i]->mot, 0);
  }
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
  if (STEPPER_ZeroHand(motors, offsets, STEPPER_NOF_CLOCKS*STEPPER_NOF_CLOCK_MOTORS)!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
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
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), NVMC_GetStepperZeroOffset(i, 0), ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"] MM[pos:");
    McuUtility_strcatNum32sFormatted(buf, sizeof(buf), X12_017_GetPos(STEPPER_Clocks[i].mot[1].device, STEPPER_Clocks[i].mot[1].mot), ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", offs:");
    McuUtility_strcatNum16sFormatted(buf, sizeof(buf), NVMC_GetStepperZeroOffset(i, 1), ' ', 5);
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
#if PL_CONFIG_USE_MAG_SENSOR
  McuShell_SendHelpStr((unsigned char*)"  zero all", (unsigned char*)"Move all motors to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  zero <c> <m>", (unsigned char*)"Move clock (0-3) and motor (0-1) to zero position using magnet sensor\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  offs <c> <m> <v>", (unsigned char*)"Set offset value for clock (0-3) and motor (0-1)\r\n", io->stdOut);
#endif
  McuShell_SendHelpStr((unsigned char*)"  step <c> <m> <steps>", (unsigned char*)"Perform a number of (blocking) steps for clock (0-3) and motor (0-1)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  goto <c> <m> <pos>", (unsigned char*)"Goto position (non-blocking) for clock (0-3) and motor (0-1)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  angle <c> <m> <deg> <md>", (unsigned char*)"Move clock (0-3) and motor (0-1) to angle (0..359) using mode (ccw, cw, short)\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  int32_t steps, clk, m;
  const unsigned char *p;
  uint8_t res = ERR_OK;

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
      res = STEPPER_ZeroHand(motors, &offset, 1);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed to find magnet/zero position\r\n", io->stdErr);
      }
    } else {
      return ERR_FAILED;
    }
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
  } else if (McuUtility_strncmp((char*)cmd, "stepper angle ", sizeof("stepper angle ")-1)==0) {
    int32_t angle;

    *handled = TRUE;
    p = cmd + sizeof("stepper angle ")-1;
    if (   McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS
        && McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS
        && McuUtility_xatoi(&p, &angle)==ERR_OK && angle>=0 && angle<=359
       )
    {
      STEPPER_MoveMode_e mode = STEPPER_MOVE_MODE_SHORT;

      if (McuUtility_strcmp((char*)p, (char*)" cw")==0) {
        mode = STEPPER_MOVE_MODE_CW;
      } else if (McuUtility_strcmp((char*)p, (char*)" ccw")==0) {
        mode = STEPPER_MOVE_MODE_CCW;
      } else if (McuUtility_strcmp((char*)p, (char*)" short")==0) {
        mode = STEPPER_MOVE_MODE_SHORT;
      } else {
        return ERR_FAILED;
      }
      STEPPER_MoveClockDegreeAbs(clk, m, angle, mode); /* lower right */
      (void)xTimerStart(timerHndl, 0);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "stepper goto ", sizeof("stepper goto ")-1)==0) {
    int32_t steps;

    *handled = TRUE;
    p = cmd + sizeof("stepper goto ")-1;
    if (McuUtility_xatoi(&p, &clk)==ERR_OK && clk>=0 && clk<STEPPER_NOF_CLOCKS) {
      if (McuUtility_xatoi(&p, &m)==ERR_OK && m>=0 && m<STEPPER_NOF_CLOCK_MOTORS) {
        if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
          STEPPER_Clocks[clk].mot[m].doSteps = steps;
          (void)xTimerStart(timerHndl, 0);
        }
      } else {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
    return ERR_OK;
  }
  return res;
}

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
  /* M0: outer shaft */
  STEPPER_Clocks[0].mot[1].device = device;
  STEPPER_Clocks[0].mot[1].mot = X12_017_M0;
  STEPPER_Clocks[0].mot[1].mag = MAG_MAG0;
  STEPPER_Clocks[0].mot[1].doSteps = 0;

  /* M3: inner shaft */
  STEPPER_Clocks[1].mot[0].device = device;
  STEPPER_Clocks[1].mot[0].mot = X12_017_M3;
  STEPPER_Clocks[1].mot[0].mag = MAG_MAG2;
  STEPPER_Clocks[1].mot[0].doSteps = 0;

  /* M2: outer shaft */
  STEPPER_Clocks[1].mot[1].device = device;
  STEPPER_Clocks[1].mot[1].mot = X12_017_M2;
  STEPPER_Clocks[1].mot[1].mag = MAG_MAG3;
  STEPPER_Clocks[1].mot[1].doSteps = 0;

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
  /* M1: inner shaft */
  STEPPER_Clocks[2].mot[0].device = device;
  STEPPER_Clocks[2].mot[0].mot = X12_017_M1;
  STEPPER_Clocks[2].mot[0].mag = MAG_MAG7;
  STEPPER_Clocks[2].mot[0].doSteps = 0;

  /* M0: outer shaft */
  STEPPER_Clocks[2].mot[1].device = device;
  STEPPER_Clocks[2].mot[1].mot = X12_017_M0;
  STEPPER_Clocks[2].mot[1].mag = MAG_MAG6;
  STEPPER_Clocks[2].mot[1].doSteps = 0;

  /* M3: inner shaft */
  STEPPER_Clocks[3].mot[0].device = device;
  STEPPER_Clocks[3].mot[0].mot = X12_017_M3;
  STEPPER_Clocks[3].mot[0].mag = MAG_MAG4;
  STEPPER_Clocks[3].mot[0].doSteps = 0;

  /* M2: outer shaft */
  STEPPER_Clocks[3].mot[1].device = device;
  STEPPER_Clocks[3].mot[1].mot = X12_017_M2;
  STEPPER_Clocks[3].mot[1].mag = MAG_MAG5;
  STEPPER_Clocks[3].mot[1].doSteps = 0;

  McuX12_017_ResetDriver(STEPPER_Clocks[0].mot[0].device); /* shared reset line with second device */

  timerHndl = xTimerCreate("stepper", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void*)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
}

#endif /* PL_CONFIG_USE_STEPPER */
