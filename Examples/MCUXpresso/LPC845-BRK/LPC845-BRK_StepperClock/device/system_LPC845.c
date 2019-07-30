/*
** ###################################################################
**     Processors:          LPC845M301JBD48
**                          LPC845M301JBD64
**                          LPC845M301JHI33
**                          LPC845M301JHI48
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC84x User manual Rev.1.6  8 Dec 2017
**     Version:             rev. 1.2, 2017-06-08
**     Build:               b180802
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2018 NXP
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-08-12)
**         Initial version.
**     - rev. 1.1 (2016-11-25)
**         Update CANFD and Classic CAN register.
**         Add MAC TIMERSTAMP registers.
**     - rev. 1.2 (2017-06-08)
**         Remove RTC_CTRL_RTC_OSC_BYPASS.
**         SYSCON_ARMTRCLKDIV rename to SYSCON_ARMTRACECLKDIV.
**         Remove RESET and HALT from SYSCON_AHBCLKDIV.
**
** ###################################################################
*/

/*!
 * @file LPC845
 * @version 1.2
 * @date 2017-06-08
 * @brief Device specific configuration file for LPC845 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"





/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
    extern void *__Vectors;
    SCB->VTOR = (uint32_t) &__Vectors;
#endif
    SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  uint32_t wdt_osc = 0;
  uint32_t fro_osc = 0;

  /* Determine clock frequency according to clock register values */
  switch ((SYSCON->FROOSCCTRL     ) & 0x03) {
    case 0:  fro_osc = 18000000; break;
    case 1:  fro_osc = 24000000; break;
    case 2:  fro_osc = 30000000; break;
    case 3:  fro_osc = 30000000; break;
  }
  if (((SYSCON->FROOSCCTRL >> 17) & 0x01) == 0) {
    fro_osc = fro_osc >> 1;
  }

  switch ((SYSCON->WDTOSCCTRL >> 5) & 0x0F) {
    case 0:  wdt_osc =       0; break;
    case 1:  wdt_osc =  600000; break;
    case 2:  wdt_osc = 1050000; break;
    case 3:  wdt_osc = 1400000; break;
    case 4:  wdt_osc = 1750000; break;
    case 5:  wdt_osc = 2100000; break;
    case 6:  wdt_osc = 2400000; break;
    case 7:  wdt_osc = 2700000; break;
    case 8:  wdt_osc = 3000000; break;
    case 9:  wdt_osc = 3250000; break;
    case 10: wdt_osc = 3500000; break;
    case 11: wdt_osc = 3750000; break;
    case 12: wdt_osc = 4000000; break;
    case 13: wdt_osc = 4200000; break;
    case 14: wdt_osc = 4400000; break;
    case 15: wdt_osc = 4600000; break;
  }
  wdt_osc /= (((SYSCON->WDTOSCCTRL & 0x1F) + 1) << 1);

  switch (SYSCON->MAINCLKPLLSEL & 0x03) {
    case 0:                                           /* main_clk_pre_pll     */
      switch (SYSCON->MAINCLKSEL & 0x03) {
        case 0:                                       /* Free running oscillator (FRO) */
          SystemCoreClock = fro_osc;
          break;
        case 1:                                       /* System oscillator */
          SystemCoreClock = CLK_OSC_IN;
          break;
        case 2:                                       /* watchdog oscillator */
          SystemCoreClock = wdt_osc;
          break;
        case 3:                                       /* Free running oscillator (FRO) / 2 */
          SystemCoreClock = (fro_osc >> 1);
          break;
      }
      break;
    case 1:                                           /* System PLL Clock Out  */
      switch (SYSCON->SYSPLLCLKSEL & 0x03) {
        case 0:                                       /* Free running oscillator (FRO) */
          SystemCoreClock = fro_osc        * ((SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
        case 1:                                       /* System oscillator */
          SystemCoreClock = CLK_OSC_IN * ((SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
        case 2:                                       /* watchdog oscillator */
          SystemCoreClock = wdt_osc        * ((SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
        case 3:                                       /* Free running oscillator (FRO) / 2 */
          SystemCoreClock = (fro_osc >> 1) * ((SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
      }
      break;
  }

  SystemCoreClock /= SYSCON->SYSAHBCLKDIV;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
