/*
 * stepper.c
 *
 *  Created on: 08.08.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "stepper.h"
#include "McuULN2003.h"

static McuULN2003_Handle_t motorSec;
static McuULN2003_Handle_t motorMin;

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 1

typedef struct {
  int32_t targetPos;
  uint32_t delayMs;
  McuULN2003_Handle_t motor;
} StepperMover_t;

static int32_t targetPosSec = 0;
static int32_t targetPosMin = 0;

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  bool finished0, finished1;

  finished0 = McuULN2003_MoveCallback(motorSec, targetPosSec);
  finished1 = McuULN2003_MoveCallback(motorMin, targetPosMin);
  if (finished0 && finished1) {
    (void)xTimerStop(timerHndl, 0);
  }
}

void STEPPER_Deint(void) {
  motorSec = McuULN2003_DeinitMotor(motorSec);
  motorMin = McuULN2003_DeinitMotor(motorMin);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"curr pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorSec));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", goto pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), targetPosSec);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  sec", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"step mode: 1/");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetStepMode(motorSec));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  sec", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"curr pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorMin));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", goto pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), targetPosMin);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  min", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"step mode: 1/");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetStepMode(motorMin));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  min", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  step (m|s) <steps>", (unsigned char*)"perform a number of steps for minute or seconds\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  goto (m|s) <pos>", (unsigned char*)"go to a position for minute or seconds\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "stepper help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "stepper status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "stepper step ", sizeof("stepper step ")-1)==0) {
    McuULN2003_Handle_t motor = NULL;
    int32_t steps;

    p = cmd + sizeof("stepper step ")-1;
    if (*p=='m') {
      motor = motorMin;
    } else if (*p=='s') {
      motor = motorSec;
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
      McuULN2003_Step(motor, steps);
      McuULN2003_PowerOff(motor);
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "stepper goto ", sizeof("stepper goto ")-1)==0) {
    McuULN2003_Handle_t motor = NULL;
    int32_t *posP = NULL;
    int32_t pos;

    p = cmd + sizeof("stepper goto ")-1;
    if (*p=='m') {
      posP = &targetPosMin;
    } else if (*p=='s') {
      posP = &targetPosSec;
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &pos)==ERR_OK) {
      *posP = pos;
      (void)xTimerStart(timerHndl, 0);
    }
    *handled = TRUE;
  }
  return ERR_OK;
}

void STEPPER_Init(void) {
  McuULN2003_Config_t config;

  McuULN2003_GetDefaultConfig(&config);
  config.hw[0].gpio = GPIO;
  config.hw[0].port = 0U;
  config.hw[0].pin = 29U;

  config.hw[1].gpio = GPIO;
  config.hw[1].port = 0U;
  config.hw[1].pin = 28U;

  config.hw[2].gpio = GPIO;
  config.hw[2].port = 0U;
  config.hw[2].pin = 27U;

  config.hw[3].gpio = GPIO;
  config.hw[3].port = 0U;
  config.hw[3].pin = 26U;
  motorSec = McuULN2003_InitMotor(&config);

  config.hw[0].gpio = GPIO;
  config.hw[0].port = 0U;
  config.hw[0].pin = 23U;

  config.hw[1].gpio = GPIO;
  config.hw[1].port = 0U;
  config.hw[1].pin = 22U;

  config.hw[2].gpio = GPIO;
  config.hw[2].port = 0U;
  config.hw[2].pin = 21U;

  config.hw[3].gpio = GPIO;
  config.hw[3].port = 0U;
  config.hw[3].pin = 20U;
  motorMin = McuULN2003_InitMotor(&config);

  McuULN2003_PowerOff(motorMin);
  McuULN2003_PowerOff(motorSec);

  timerHndl = xTimerCreate("stepper", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void*)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
}
