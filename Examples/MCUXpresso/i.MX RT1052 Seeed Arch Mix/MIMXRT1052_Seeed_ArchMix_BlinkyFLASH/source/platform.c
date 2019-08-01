/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuRTT.h"
/* SDK */
#include "fsl_gpio.h"
/* application modules: */
#include "leds.h"
#include "buttons.h"

void PL_Init(void) {
  /* McuLib modules: */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();

  /* application modules: */
  LEDS_Init();
  BTN_Init();
}
