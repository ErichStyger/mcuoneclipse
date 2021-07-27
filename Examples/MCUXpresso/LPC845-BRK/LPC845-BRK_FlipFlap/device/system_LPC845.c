/*
** ###################################################################
**     Processors:          LPC845M301JBD48
**                          LPC845M301JBD64
**                          LPC845M301JHI33
**                          LPC845M301JHI48
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC84x User manual Rev.1.6  8 Dec 2017
**     Version:             rev. 1.2, 2017-06-08
**     Build:               b201015
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
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
  uint32_t wdt_osc = 0U;
  uint32_t fro_osc = 0U;

  /* Determine clock frequency according to clock register values */
  switch ((SYSCON->FROOSCCTRL     ) & 0x03U) {
    case 0U:  fro_osc = 18000000U; break;
    case 1U:  fro_osc = 24000000U; break;
    case 2U:  fro_osc = 30000000U; break;
    case 3U:  fro_osc = 30000000U; break;
    default:  fro_osc =        0U; break;
  }
  if (((SYSCON->FROOSCCTRL >> SYSCON_FROOSCCTRL_FRO_DIRECT_SHIFT) & 0x01U) == 0U) {
    fro_osc = fro_osc >> 1U;
  }

  switch ((SYSCON->WDTOSCCTRL >> SYSCON_WDTOSCCTRL_FREQSEL_SHIFT) & 0x0FU) {
    case 0U:  wdt_osc =       0U; break;
    case 1U:  wdt_osc =  600000U; break;
    case 2U:  wdt_osc = 1050000U; break;
    case 3U:  wdt_osc = 1400000U; break;
    case 4U:  wdt_osc = 1750000U; break;
    case 5U:  wdt_osc = 2100000U; break;
    case 6U:  wdt_osc = 2400000U; break;
    case 7U:  wdt_osc = 2700000U; break;
    case 8U:  wdt_osc = 3000000U; break;
    case 9U:  wdt_osc = 3250000U; break;
    case 10U: wdt_osc = 3500000U; break;
    case 11U: wdt_osc = 3750000U; break;
    case 12U: wdt_osc = 4000000U; break;
    case 13U: wdt_osc = 4200000U; break;
    case 14U: wdt_osc = 4400000U; break;
    case 15U: wdt_osc = 4600000U; break;
    default:  wdt_osc =       0U; break;
  }
  wdt_osc /= (((SYSCON->WDTOSCCTRL & SYSCON_WDTOSCCTRL_DIVSEL_MASK) + 1U) << 1U);

  switch (SYSCON->MAINCLKPLLSEL & 0x01U) {
    case 0U:                                           /* main_clk_pre_pll     */
      switch (SYSCON->MAINCLKSEL & SYSCON_MAINCLKSEL_SEL_MASK) {
        case 0U:                                       /* Free running oscillator (FRO) */
          SystemCoreClock = fro_osc;
          break;
        case 1U:                                       /* System oscillator */
          SystemCoreClock = CLK_OSC_IN;
          break;
        case 2U:                                       /* watchdog oscillator */
          SystemCoreClock = wdt_osc;
          break;
        case 3U:                                       /* Free running oscillator (FRO) / 2 */
          SystemCoreClock = (fro_osc >> 1U);
          break;
        default:
          SystemCoreClock = 0U;
          break;
      }
      break;
    case 1U:                                           /* System PLL Clock Out  */
      switch (SYSCON->SYSPLLCLKSEL & SYSCON_SYSPLLCLKSEL_SEL_MASK) {
        case 0U:                                       /* Free running oscillator (FRO) */
          SystemCoreClock = fro_osc        * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
          break;
        case 1U:                                       /* System oscillator */
          SystemCoreClock = CLK_OSC_IN * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
          break;
        case 2U:                                       /* watchdog oscillator */
          SystemCoreClock = wdt_osc        * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
          break;
        case 3U:                                       /* Free running oscillator (FRO) / 2 */
          SystemCoreClock = (fro_osc >> 1U) * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
          break;
        default:
          SystemCoreClock = 0U;
          break;
      }
      break;
    default:
      SystemCoreClock = 0U;
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
