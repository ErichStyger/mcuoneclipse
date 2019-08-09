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

void STEPPER_Deint(void) {
  motorSec = McuULN2003_DeinitMotor(motorSec);
  motorMin = McuULN2003_DeinitMotor(motorMin);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorSec));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  seconds", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorMin));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  minutes", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  step (m|s) <no>", (unsigned char*)"perform a number of steps for minute or seconds\r\n", io->stdOut);
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
}
