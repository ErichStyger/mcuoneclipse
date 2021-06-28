/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuWait.h"
#include "leds.h"

void APP_Run(void) {
  PL_Init();
  for(;;) {
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_GREEN);
    LEDS_On(LEDS_RED);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(500);
  }
}
