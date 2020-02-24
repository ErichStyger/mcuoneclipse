/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuLED.h"
#include "leds.h"
#include "fsl_pit.h"

void APP_Run(void) {
  PL_Init();
  for(;;) {
    McuLED_On(tinyLED);
    McuWait_Waitms(1000);
    McuLED_Off(tinyLED);
    McuWait_Waitms(10*1000);
  }
}
