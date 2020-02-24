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
#include "LowPower.h"

void APP_Run(void) {
  PL_Init();
  for(;;) {
    McuLED_On(tinyLED);
    McuWait_Waitms(1000);
    McuLED_Off(tinyLED);
    LP_EnterLowPower();
#if LP_MODE==LP_MODE_RUN
    McuWait_Waitms(10000); /* no wakeup, burn cycles here */
#elif LP_MODE==LP_MODE_WAIT
    /* PIT configured for 10 sec will wake us up */
#elif LP_MODE==LP_MODE_STOP
    /* PIT configured for 10 sec will wake us up */
#endif
  }
}
