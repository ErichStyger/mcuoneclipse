/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
/* library modules */
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"

/* application modulMcues */
#include "leds.h"

void PL_Init(void) {
  /* clocking */
  CLOCK_EnableClock(kCLOCK_PortA); /* used by leds */
  CLOCK_EnableClock(kCLOCK_PortB); /* used by sd card detect and I2C */
  CLOCK_EnableClock(kCLOCK_PortD); /* used by leds */

  /* library modules */
  McuLib_Init();
  #if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
  #endif
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();

  /* application modules */
  LEDS_Init();
}
