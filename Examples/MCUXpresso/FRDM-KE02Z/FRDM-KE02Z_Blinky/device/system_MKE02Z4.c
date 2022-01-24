/*
** ###################################################################
**     Processors:          MKE02Z16VFM4
**                          MKE02Z16VLC4
**                          MKE02Z16VLD4
**                          MKE02Z32VFM4
**                          MKE02Z32VLC4
**                          MKE02Z32VLD4
**                          MKE02Z32VLH4
**                          MKE02Z32VQH4
**                          MKE02Z64VFM4
**                          MKE02Z64VLC4
**                          MKE02Z64VLD4
**                          MKE02Z64VLH4
**                          MKE02Z64VQH4
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MKE02P64M40SF0RM Rev 4
**     Version:             rev. 1.0, 2017-05-19
**     Build:               b201123
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
**     - rev. 1.0 (2017-05-19)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MKE02Z4
 * @version 1.0
 * @date 2017-05-19
 * @brief Device specific configuration file for MKE02Z4 (implementation file)
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

#if (DISABLE_WDOG)
  WDOG->CNT = WDOG_UPDATE_KEY1;
  WDOG->CNT = WDOG_UPDATE_KEY2;
  WDOG->TOVAL = 0xFFFFU;
  WDOG->CS1 = (uint8_t) ((WDOG->CS1) & ~WDOG_CS1_EN_MASK) | WDOG_CS1_UPDATE_MASK;
  WDOG->CS2 |= 0U;
#endif /* (DISABLE_WDOG) */

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  uint32_t ICSOUTClock; /* Variable to store output clock frequency of the ICS module */
  uint16_t Divider;
  uint16_t Temp;

  Divider = (uint16_t)(0x01U) << (((uint16_t)ICS->C2 & ICS_C2_BDIV_MASK) >> ICS_C2_BDIV_SHIFT);

  switch ((ICS->C1 & ICS_C1_CLKS_MASK) >> ICS_C1_CLKS_SHIFT) {
    case 0x0:
      /* FLL */
      if((ICS->C1 & ICS_C1_IREFS_MASK) != 0x0U)
      {
          ICSOUTClock = CPU_INT_IRC_CLK_HZ * 1024UL;
      }
      else
      {
          /* Reference Divider */
          Temp = ((uint16_t)ICS->C1 & ICS_C1_RDIV_MASK) >> ICS_C1_RDIV_SHIFT;
          Temp = (Temp + 1U) * (((OSC->CR & OSC_CR_RANGE_MASK) != 0x0U) ? 32U : 1U);

          ICSOUTClock = CPU_XTAL_CLK_HZ / Temp * 1024UL;
      }
      break;

    case 0x1:
      /* Internal IRC */
      ICSOUTClock = CPU_INT_IRC_CLK_HZ;
      break;

    case 0x2:
      /* External OSC */
      ICSOUTClock = CPU_XTAL_CLK_HZ;
      break;

    default:
      ICSOUTClock = 0U;
      break;
  }
  SystemCoreClock = (ICSOUTClock / Divider);

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
