/*
 * stepper.c
 *
 *  Created on: 08.08.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "stepper.h"
#include "McuULN2003.h"

static McuULN2003_Handle_t motorSec, motorMin;

void STEPPER_Deint(void) {
  motorSec = McuULN2003_DeinitMotor(motorSec);
  motorMin = McuULN2003_DeinitMotor(motorMin);
}

void STEPPER_Init(void) {
  McuULN2003_Config_t config;

  McuULN2003_GetDefaultConfig(&config);
  config.hw[0].gpio = GPIO;
  config.hw[0].port = 0U;
  config.hw[0].pin = 8U;

  config.hw[1].gpio = GPIO;
  config.hw[1].port = 0U;
  config.hw[1].pin = 9U;

  config.hw[2].gpio = GPIO;
  config.hw[2].port = 0U;
  config.hw[2].pin = 31U;

  config.hw[3].gpio = GPIO;
  config.hw[3].port = 0U;
  config.hw[3].pin = 30U;
  motorSec = McuULN2003_InitMotor(&config);

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
  motorMin = McuULN2003_InitMotor(&config);
}
