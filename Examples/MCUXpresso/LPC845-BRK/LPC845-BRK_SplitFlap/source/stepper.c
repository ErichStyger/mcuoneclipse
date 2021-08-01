/*
 * Copyright (c) 2021, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_STEPPER
#include "stepper.h"
#include "McuULN2003.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "magnets.h"

#if STEPPER_CONFIG_NOF_STEPPER>=1
/* motor 0 */
#define STEPPER_MOTOR0_IN1_GPIO       GPIO
#define STEPPER_MOTOR0_IN1_PORT       0U
#define STEPPER_MOTOR0_IN1_PIN        20U
#define STEPPER_MOTOR0_IN1_IOCON      IOCON_INDEX_PIO0_20
#define STEPPER_MOTOR0_IN2_GPIO       GPIO
#define STEPPER_MOTOR0_IN2_PORT       0U
#define STEPPER_MOTOR0_IN2_PIN        21U
#define STEPPER_MOTOR0_IN2_IOCON      IOCON_INDEX_PIO0_21
#define STEPPER_MOTOR0_IN3_GPIO       GPIO
#define STEPPER_MOTOR0_IN3_PORT       0U
#define STEPPER_MOTOR0_IN3_PIN        22U
#define STEPPER_MOTOR0_IN3_IOCON      IOCON_INDEX_PIO0_22
#define STEPPER_MOTOR0_IN4_GPIO       GPIO
#define STEPPER_MOTOR0_IN4_PORT       0U
#define STEPPER_MOTOR0_IN4_PIN        23U
#define STEPPER_MOTOR0_IN4_IOCON      IOCON_INDEX_PIO0_23
#endif

#if STEPPER_CONFIG_NOF_STEPPER>=2
/* motor 1 */
#define STEPPER_MOTOR1_IN1_GPIO       GPIO
#define STEPPER_MOTOR1_IN1_PORT       0U
#define STEPPER_MOTOR1_IN1_PIN        26U
#define STEPPER_MOTOR1_IN1_IOCON      IOCON_INDEX_PIO0_26
#define STEPPER_MOTOR1_IN2_GPIO       GPIO
#define STEPPER_MOTOR1_IN2_PORT       0U
#define STEPPER_MOTOR1_IN2_PIN        27U
#define STEPPER_MOTOR1_IN2_IOCON      IOCON_INDEX_PIO0_27
#define STEPPER_MOTOR1_IN3_GPIO       GPIO
#define STEPPER_MOTOR1_IN3_PORT       0U
#define STEPPER_MOTOR1_IN3_PIN        28U
#define STEPPER_MOTOR1_IN3_IOCON      IOCON_INDEX_PIO0_28
#define STEPPER_MOTOR1_IN4_GPIO       GPIO
#define STEPPER_MOTOR1_IN4_PORT       0U
#define STEPPER_MOTOR1_IN4_PIN        29U
#define STEPPER_MOTOR1_IN4_IOCON      IOCON_INDEX_PIO0_29
#endif

#if STEPPER_CONFIG_NOF_STEPPER>=3
/* motor 2 */
#define STEPPER_MOTOR2_IN1_GPIO       GPIO
#define STEPPER_MOTOR2_IN1_PORT       0U
#define STEPPER_MOTOR2_IN1_PIN        14U
#define STEPPER_MOTOR2_IN1_IOCON      IOCON_INDEX_PIO0_14
#define STEPPER_MOTOR2_IN2_GPIO       GPIO
#define STEPPER_MOTOR2_IN2_PORT       0U
#define STEPPER_MOTOR2_IN2_PIN        13U
#define STEPPER_MOTOR2_IN2_IOCON      IOCON_INDEX_PIO0_13
#define STEPPER_MOTOR2_IN3_GPIO       GPIO
#define STEPPER_MOTOR2_IN3_PORT       0U
#define STEPPER_MOTOR2_IN3_PIN        9U
#define STEPPER_MOTOR2_IN3_IOCON      IOCON_INDEX_PIO0_9
#define STEPPER_MOTOR2_IN4_GPIO       GPIO
#define STEPPER_MOTOR2_IN4_PORT       0U
#define STEPPER_MOTOR2_IN4_PIN        8U
#define STEPPER_MOTOR2_IN4_IOCON      IOCON_INDEX_PIO0_8
#endif

#if STEPPER_CONFIG_NOF_STEPPER>=4
/* motor 3 */
#define STEPPER_MOTOR3_IN1_GPIO       GPIO
#define STEPPER_MOTOR3_IN1_PORT       0U
#define STEPPER_MOTOR3_IN1_PIN        0U
#define STEPPER_MOTOR3_IN1_IOCON      IOCON_INDEX_PIO0_0
#define STEPPER_MOTOR3_IN2_GPIO       GPIO
#define STEPPER_MOTOR3_IN2_PORT       0U
#define STEPPER_MOTOR3_IN2_PIN        1U
#define STEPPER_MOTOR3_IN2_IOCON      IOCON_INDEX_PIO0_1
#define STEPPER_MOTOR3_IN3_GPIO       GPIO
#define STEPPER_MOTOR3_IN3_PORT       0U
#define STEPPER_MOTOR3_IN3_PIN        6U
#define STEPPER_MOTOR3_IN3_IOCON      IOCON_INDEX_PIO0_6
#define STEPPER_MOTOR3_IN4_GPIO       GPIO
#define STEPPER_MOTOR3_IN4_PORT       0U
#define STEPPER_MOTOR3_IN4_PIN        15U
#define STEPPER_MOTOR3_IN4_IOCON      IOCON_INDEX_PIO0_15
#endif

static const char STEPPER_flapChars[STEPPER_NOF_FLAPS] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?."; /* chars on the flaps */
static McuULN2003_Handle_t motorHandles[STEPPER_CONFIG_NOF_STEPPER]; /* list of motor handles */
static int32_t motorMoveSteps[STEPPER_CONFIG_NOF_STEPPER]; /* number of steps to be performed, processed by timer */
#if PL_CONFIG_USE_HALL_SENSOR
static const int32_t motorZeroOffsets[STEPPER_CONFIG_NOF_STEPPER] = { /* offset from the zero position */
  #if STEPPER_CONFIG_NOF_STEPPER>=1
    12,
  #endif
  #if STEPPER_CONFIG_NOF_STEPPER>=2
    12,
  #endif
  #if STEPPER_CONFIG_NOF_STEPPER>=3
    12,
  #endif
  #if STEPPER_CONFIG_NOF_STEPPER>=4
    12,
  #endif
};
#endif

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS   1

typedef struct StepperMover_t {
  int32_t targetPos;
  uint32_t delayMs;
  McuULN2003_Handle_t motor;
} StepperMover_t;

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  bool finished = true; /* gets reset if not finished */
  bool finishedStep;

  for(int i=0; i<STEPPER_CONFIG_NOF_STEPPER; i++) {
    if (motorMoveSteps[i]>0) {
      finishedStep =  McuULN2003_StepCallback(motorHandles[i], true);
      if (finishedStep) {
        motorMoveSteps[i]--;
      }
    }
    if (motorMoveSteps[i]>0) { /* not finished yet? */
      finished = false;
    }
  } /* for */
  if (finished) { /* all finished moving */
    (void)xTimerStop(timerHndl, 0);
    /* normalize positions */
    for(int i=0; i<STEPPER_CONFIG_NOF_STEPPER; i++) {
      McuULN2003_Handle_t motor = motorHandles[i];
      McuULN2003_SetPos(motor, McuULN2003_GetPos(motor)%STEPPER_360_STEPS);
      McuULN2003_PowerOff(motor);
    }
  }
}

static void STEPPER_SetTargetPos(uint8_t motorIdx, int32_t targetPos) {
  int32_t currPos;

  targetPos %= STEPPER_360_STEPS;
  currPos = STEPPER_GetPos(motorIdx);
  currPos %= STEPPER_360_STEPS;
  McuULN2003_SetPos(motorHandles[motorIdx], currPos);
  if (targetPos>=currPos) {
    motorMoveSteps[motorIdx] = targetPos-currPos;
  } else {
    motorMoveSteps[motorIdx] = STEPPER_360_STEPS-(currPos-targetPos);
  }
}

int32_t STEPPER_GetPos(uint8_t motorIndex) {
  return McuULN2003_GetPos(motorHandles[motorIndex]);
}

void STEPPER_Deint(void) {
  for(int i=0; i<STEPPER_CONFIG_NOF_STEPPER; i++) {
    motorHandles[i] = McuULN2003_DeinitMotor(motorHandles[i]);
  }
}

uint8_t STEPPER_ZeroPosition(uint8_t motorIndex) {
  uint8_t res = ERR_FAILED;

#if PL_CONFIG_USE_HALL_SENSOR
  while(MAG_Triggered(motorIndex)) {
    McuULN2003_IncStep(motorHandles[motorIndex]);
  }
  McuULN2003_Step(motorHandles[motorIndex], STEPPER_360_STEPS/3);
  for(int i=0; i<STEPPER_360_STEPS+(STEPPER_360_STEPS/50); i++) {
    McuULN2003_IncStep(motorHandles[motorIndex]);
    if (MAG_Triggered(motorIndex)) {
      McuULN2003_Step(motorHandles[motorIndex], motorZeroOffsets[motorIndex]);
      McuULN2003_SetPos(motorHandles[motorIndex], 0);
      res = ERR_OK;
      break;
    }
  }
  McuULN2003_PowerOff(motorHandles[motorIndex]);
#endif
  return res;
}

static uint8_t STEPPER_ShowChar(uint8_t motorIndex, unsigned char ch) {
  size_t index = 0;
  int32_t currPos, targetPos, steps = 0;

  for(index=0;index<sizeof(STEPPER_flapChars);index++) {
    if (STEPPER_flapChars[index]==ch) {
      break;
    }
  }
  if (STEPPER_flapChars[index]!=ch) {
    return ERR_FAILED; /* not found? */
  }
  targetPos = (index*STEPPER_360_STEPS)/STEPPER_NOF_FLAPS;
  currPos = McuULN2003_GetPos(motorHandles[motorIndex])%STEPPER_360_STEPS;
  if (targetPos>=currPos) {
    steps = targetPos - currPos;
  } else {
    steps = STEPPER_360_STEPS-(currPos-targetPos);
  }
  if (steps!=0) {
    McuULN2003_Step(motorHandles[motorIndex], steps);
    McuULN2003_PowerOff(motorHandles[motorIndex]);
  }
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];
  unsigned char statusBuf[16];

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"");
  McuUtility_strcatNum32s(buf, sizeof(buf), STEPPER_360_STEPS);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
  McuShell_SendStatusStr((unsigned char*)"  360 degree", buf, io->stdOut);

  for(int motorIndex=0; motorIndex<STEPPER_CONFIG_NOF_STEPPER; motorIndex++) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"curr: ");
    McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorHandles[motorIndex]));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", move: ");
    McuUtility_strcatNum32s(buf, sizeof(buf), motorMoveSteps[motorIndex]);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", step: 1/");
    McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetStepMode(motorHandles[motorIndex]));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuUtility_strcpy(statusBuf, sizeof(statusBuf), (unsigned char*)"  motor ");
    McuUtility_strcatNum8u(statusBuf, sizeof(statusBuf), motorIndex);
    McuShell_SendStatusStr(statusBuf, buf, io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset <m>", (unsigned char*)"Set stepper position info to zero\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  step <m> <steps>", (unsigned char*)"perform a number of incremental steps for motor (0, ...)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  goto <m> <pos>", (unsigned char*)"background goto position motor (0, ...)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  char <m> <ch>", (unsigned char*)"show character on motor (0, ...)\r\n", io->stdOut);
#if PL_CONFIG_USE_HALL_SENSOR
  McuShell_SendHelpStr((unsigned char*)"  zero <m>", (unsigned char*)"Move hour or minute to zero position\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint8_t res = ERR_OK;
  int32_t motorIdx;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "stepper help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "stepper status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "stepper reset ", sizeof("stepper reset ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper reset ")-1;
    if (McuUtility_xatoi(&p, &motorIdx)==ERR_OK) {
      if (motorIdx>=STEPPER_CONFIG_NOF_STEPPER) {
        return ERR_FAILED;
      }
      McuULN2003_SetPos(motorHandles[motorIdx], 0);
    } else {
      return ERR_FAILED;
    }
    return ERR_OK;
#if PL_CONFIG_USE_HALL_SENSOR
  } else if (McuUtility_strncmp((char*)cmd, "stepper zero ", sizeof("stepper zero ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper zero ")-1;
    if (McuUtility_xatoi(&p, &motorIdx)==ERR_OK) {
      if (motorIdx>=STEPPER_CONFIG_NOF_STEPPER) {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
    res = STEPPER_ZeroPosition(motorIdx);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"failed to find zero position\r\n", io->stdErr);
    }
#endif
  } else if (McuUtility_strncmp((char*)cmd, "stepper char ", sizeof("stepper char ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("stepper char ")-1;
    if (McuUtility_xatoi(&p, &motorIdx)==ERR_OK) {
      if (motorIdx>=STEPPER_CONFIG_NOF_STEPPER) {
        return ERR_FAILED;
      }
      if (*p==' ') {
        p++; /* skip space */
      }
      return STEPPER_ShowChar(motorIdx, *p);
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "stepper step ", sizeof("stepper step ")-1)==0) {
    int32_t steps;

    p = cmd + sizeof("stepper step ")-1;
    if (McuUtility_xatoi(&p, &motorIdx)==ERR_OK) {
      if (motorIdx>=STEPPER_CONFIG_NOF_STEPPER) {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
      McuULN2003_Step(motorHandles[motorIdx], steps);
      McuULN2003_PowerOff(motorHandles[motorIdx]);
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "stepper goto ", sizeof("stepper goto ")-1)==0) {
    int32_t pos;

    *handled = TRUE;
    p = cmd + sizeof("stepper goto ")-1;
    if (McuUtility_xatoi(&p, &motorIdx)==ERR_OK) {
      if (motorIdx>=STEPPER_CONFIG_NOF_STEPPER) {
        return ERR_FAILED;
      }
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &pos)==ERR_OK && pos>=0) {
      STEPPER_SetTargetPos(motorIdx, pos);
      (void)xTimerStart(timerHndl, 0);
    } else {
      return ERR_FAILED;
    }
    return ERR_OK;
  }
  return res;
}

void STEPPER_Init(void) {
  McuULN2003_Config_t config;

  McuULN2003_GetDefaultConfig(&config);
#if STEPPER_CONFIG_NOF_STEPPER >= 1
  config.hw[0].gpio = STEPPER_MOTOR0_IN1_GPIO;
  config.hw[0].port = STEPPER_MOTOR0_IN1_PORT;
  config.hw[0].pin = STEPPER_MOTOR0_IN1_PIN;
  config.hw[0].iocon = STEPPER_MOTOR0_IN1_IOCON;

  config.hw[1].gpio = STEPPER_MOTOR0_IN2_GPIO;
  config.hw[1].port = STEPPER_MOTOR0_IN2_PORT;
  config.hw[1].pin = STEPPER_MOTOR0_IN2_PIN;
  config.hw[1].iocon = STEPPER_MOTOR0_IN2_IOCON;

  config.hw[2].gpio = STEPPER_MOTOR0_IN3_GPIO;
  config.hw[2].port = STEPPER_MOTOR0_IN3_PORT;
  config.hw[2].pin = STEPPER_MOTOR0_IN3_PIN;
  config.hw[2].iocon = STEPPER_MOTOR0_IN3_IOCON;

  config.hw[3].gpio = STEPPER_MOTOR0_IN4_GPIO;
  config.hw[3].port = STEPPER_MOTOR0_IN4_PORT;
  config.hw[3].pin = STEPPER_MOTOR0_IN4_PIN;
  config.hw[3].iocon = STEPPER_MOTOR0_IN4_IOCON;
  config.inverted = true;
  motorHandles[0] = McuULN2003_InitMotor(&config);
  McuULN2003_PowerOff(motorHandles[0]);
#endif

#if STEPPER_CONFIG_NOF_STEPPER >= 2
  config.hw[0].gpio = STEPPER_MOTOR1_IN1_GPIO;
  config.hw[0].port = STEPPER_MOTOR1_IN1_PORT;
  config.hw[0].pin = STEPPER_MOTOR1_IN1_PIN;
  config.hw[0].iocon = STEPPER_MOTOR1_IN1_IOCON;

  config.hw[1].gpio = STEPPER_MOTOR1_IN2_GPIO;
  config.hw[1].port = STEPPER_MOTOR1_IN2_PORT;
  config.hw[1].pin = STEPPER_MOTOR1_IN2_PIN;
  config.hw[1].iocon = STEPPER_MOTOR1_IN2_IOCON;

  config.hw[2].gpio = STEPPER_MOTOR1_IN3_GPIO;
  config.hw[2].port = STEPPER_MOTOR1_IN3_PORT;
  config.hw[2].pin = STEPPER_MOTOR1_IN3_PIN;
  config.hw[2].iocon = STEPPER_MOTOR1_IN3_IOCON;

  config.hw[3].gpio = STEPPER_MOTOR1_IN4_GPIO;
  config.hw[3].port = STEPPER_MOTOR1_IN4_PORT;
  config.hw[3].pin = STEPPER_MOTOR1_IN4_PIN;
  config.hw[3].iocon = STEPPER_MOTOR1_IN4_IOCON;
  config.inverted = true;
  motorHandles[1] = McuULN2003_InitMotor(&config);
  McuULN2003_PowerOff(motorHandles[1]);
#endif

#if STEPPER_CONFIG_NOF_STEPPER >= 3
  config.hw[0].gpio = STEPPER_MOTOR2_IN1_GPIO;
  config.hw[0].port = STEPPER_MOTOR2_IN1_PORT;
  config.hw[0].pin = STEPPER_MOTOR2_IN1_PIN;
  config.hw[0].iocon = STEPPER_MOTOR2_IN1_IOCON;

  config.hw[1].gpio = STEPPER_MOTOR2_IN2_GPIO;
  config.hw[1].port = STEPPER_MOTOR2_IN2_PORT;
  config.hw[1].pin = STEPPER_MOTOR2_IN2_PIN;
  config.hw[1].iocon = STEPPER_MOTOR2_IN2_IOCON;

  config.hw[2].gpio = STEPPER_MOTOR2_IN3_GPIO;
  config.hw[2].port = STEPPER_MOTOR2_IN3_PORT;
  config.hw[2].pin = STEPPER_MOTOR2_IN3_PIN;
  config.hw[2].iocon = STEPPER_MOTOR2_IN3_IOCON;

  config.hw[3].gpio = STEPPER_MOTOR2_IN4_GPIO;
  config.hw[3].port = STEPPER_MOTOR2_IN4_PORT;
  config.hw[3].pin = STEPPER_MOTOR2_IN4_PIN;
  config.hw[3].iocon = STEPPER_MOTOR2_IN4_IOCON;
  config.inverted = true;
  motorHandles[2] = McuULN2003_InitMotor(&config);
  McuULN2003_PowerOff(motorHandles[2]);
#endif

#if STEPPER_CONFIG_NOF_STEPPER >= 4
  config.hw[0].gpio = STEPPER_MOTOR3_IN1_GPIO;
  config.hw[0].port = STEPPER_MOTOR3_IN1_PORT;
  config.hw[0].pin = STEPPER_MOTOR3_IN1_PIN;
  config.hw[0].iocon = STEPPER_MOTOR3_IN1_IOCON;

  config.hw[1].gpio = STEPPER_MOTOR3_IN2_GPIO;
  config.hw[1].port = STEPPER_MOTOR3_IN2_PORT;
  config.hw[1].pin = STEPPER_MOTOR3_IN2_PIN;
  config.hw[1].iocon = STEPPER_MOTOR3_IN2_IOCON;

  config.hw[2].gpio = STEPPER_MOTOR3_IN3_GPIO;
  config.hw[2].port = STEPPER_MOTOR3_IN3_PORT;
  config.hw[2].pin = STEPPER_MOTOR3_IN3_PIN;
  config.hw[2].iocon = STEPPER_MOTOR3_IN3_IOCON;

  config.hw[3].gpio = STEPPER_MOTOR3_IN4_GPIO;
  config.hw[3].port = STEPPER_MOTOR3_IN4_PORT;
  config.hw[3].pin = STEPPER_MOTOR3_IN4_PIN;
  config.hw[3].iocon = STEPPER_MOTOR3_IN4_IOCON;
  config.inverted = true;
  motorHandles[3] = McuULN2003_InitMotor(&config);
  McuULN2003_PowerOff(motorHandles[3]);
#endif

  timerHndl = xTimerCreate("stepper", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void*)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
}
#endif /* PL_CONFIG_USE_STEPPER */
