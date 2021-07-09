/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "leds.h"
#include "NeoPixel.h"

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon);

  /* McuLib modules */
  McuLib_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuWait_Init();
  McuArmTools_Init();

  /* application modules */
  LEDS_Init();
  NEO_Init();
}
