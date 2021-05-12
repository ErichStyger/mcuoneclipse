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
#include "clock_config.h"

static void GearShiftSlow(bool slow) {
  #define SIM_PLLFLLSEL_MCGFLLCLK_CLK                       0U  /*!< PLLFLL select: MCGFLLCLK clock */
  #define SIM_OSC32KSEL_OSC32KCLK_CLK                       0U  /*!< OSC32KSEL select: OSC32KCLK clock */
  static const sim_clock_config_t simConfig_BOARD_BootClockRUN =
      {
          .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
          .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK,  /* OSC32KSEL select: OSC32KCLK clock */
          .clkdiv1 = 0x44440000U,                   /* SIM_CLKDIV1 - OUTDIV1: /5, OUTDIV2: /5, OUTDIV3: /5, OUTDIV4: /5 */
          /* divide by 5 (5-1) 20 MHz */
      };
  static const sim_clock_config_t simConfig_BOARD_BootClockRUN_slow =
      {
          .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
          .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK,  /* OSC32KSEL select: OSC32KCLK clock */
          .clkdiv1 = 0x99990000U,                   /* SIM_CLKDIV1 - OUTDIV1: /10, OUTDIV2: /10, OUTDIV3: /10, OUTDIV4: /10 */
          /* divide by 10 (10-1) 10 MHz */
      };
  if (slow) {
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockRUN_slow);
  } else {
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockRUN);
  }
  SystemCoreClock = CLOCK_GetCoreSysClkFreq();
}

void APP_Run(void) {
  PL_Init(); /* initialize platform */
  for(int i=0; i<3; i++) {
    McuLED_On(blueLED);
    McuWait_Waitms(500);
    McuLED_Off(blueLED);
    McuWait_Waitms(500);
  }
//  printf("SystemCoreClock: %lu\n", SystemCoreClock);
  GearShiftSlow(true);
  for(;;) {
    McuLED_On(blueLED);
    McuWait_Waitms(100);
    McuLED_Off(blueLED);
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
