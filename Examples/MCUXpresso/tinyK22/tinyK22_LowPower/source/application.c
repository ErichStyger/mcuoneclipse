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
#include <stdio.h>

void APP_Run(void) {
  PL_Init(); /* initialize platform */
  printf("SystemCoreClock: %lu\n", SystemCoreClock);
  for(;;) {
    McuLED_On(tinyLED);
    McuWait_Waitms(100);
    McuLED_Off(tinyLED);
#if LP_MODE==LP_MODE_RUN
    LP_EnterLowPower(kAPP_PowerModeRun);
    McuWait_Waitms(1000); /* no wakeup, burn cycles here */
#elif LP_MODE==LP_MODE_WAIT
    LP_EnterLowPower(kAPP_PowerModeWait);
    /* PIT configured for 1 sec will wake us up */
#elif LP_MODE==LP_MODE_STOP
    LP_EnterLowPower(kAPP_PowerModeStop);
    /* PIT configured for 1 sec will wake us up */
#elif LP_MODE==LP_MODE_VLPR

#endif
  }
}
