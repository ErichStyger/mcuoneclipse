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
#if 0
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
#endif

  McuULN2003_Disable(motorSec);
//  McuULN2003_Disable(motorMin);
  for(int i=0; i<200; i++) {
    McuULN2003_IncStep(motorSec);
  }
  McuULN2003_Disable(motorSec);
}
