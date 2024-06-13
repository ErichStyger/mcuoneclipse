/*
** ###################################################################
**     Processors:          MIMXRT685SFAWBR_cm33
**                          MIMXRT685SFFOB_cm33
**                          MIMXRT685SFVKB_cm33
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MIMXRT685 User manual Rev. 0.95 11 November 2019
**     Version:             rev. 2.0, 2019-11-12
**     Build:               b201016
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
**     - rev. 1.0 (2018-06-19)
**         Initial version.
**     - rev. 2.0 (2019-11-12)
**         Base on rev 0.95 RM (B0 Header)
**
** ###################################################################
*/

/*!
 * @file MIMXRT685S_cm33
 * @version 2.0
 * @date 2019-11-12
 * @brief Device specific configuration file for MIMXRT685S_cm33 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"


#define SYSTEM_IS_XIP_FLEXSPI()                                                                               \
    ((((uint32_t)SystemCoreClockUpdate >= 0x08000000U) && ((uint32_t)SystemCoreClockUpdate < 0x10000000U)) || \
     (((uint32_t)SystemCoreClockUpdate >= 0x18000000U) && ((uint32_t)SystemCoreClockUpdate < 0x20000000U)))

/* Get OSC clock from SYSOSC_BYPASS */
static uint32_t getOscClk(void)
{
  return (CLKCTL0->SYSOSCBYPASS == 0U) ? CLK_XTAL_OSC_CLK : ((CLKCTL0->SYSOSCBYPASS == 1U) ? CLK_EXT_CLKIN : 0U);
}

/* Get FFRO clock from FFROCTL0 setting */
static uint32_t getFFroFreq(void)
{
  uint32_t freq = 0U;

  switch (CLKCTL0->FFROCTL0 & CLKCTL0_FFROCTL0_TRIM_RANGE_MASK)
  {
    case CLKCTL0_FFROCTL0_TRIM_RANGE(0):
      freq = CLK_FRO_48MHZ;
      break;
    case CLKCTL0_FFROCTL0_TRIM_RANGE(3):
      freq = CLK_FRO_60MHZ;
      break;
    default:
      freq = 0U;
      break;
  }
  return freq;
}



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Secure mode */
  #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SCB_NS->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Non-secure mode */
  #endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

  SCB->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Secure mode (enable PowerQuad) */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SCB_NS->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Non-secure mode (enable PowerQuad) */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

  SCB->NSACR |= ((3UL << 0) | (3UL << 10));   /* enable CP0, CP1, CP10, CP11 Non-secure Access */

  SYSCTL0->DSPSTALL = SYSCTL0_DSPSTALL_DSPSTALL_MASK;

  if (SYSTEM_IS_XIP_FLEXSPI() && (CACHE64_POLSEL->POLSEL == 0U)) /* Enable cache to accelerate boot. */
  {
    /* set command to invalidate all ways and write GO bit to initiate command */
    CACHE64->CCR = CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_INVW0_MASK;
    CACHE64->CCR |= CACHE64_CTRL_CCR_GO_MASK;
    /* Wait until the command completes */
    while ((CACHE64->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0U)
    {
    }
    /* Enable cache, enable write buffer */
    CACHE64->CCR = (CACHE64_CTRL_CCR_ENWRBUF_MASK | CACHE64_CTRL_CCR_ENCACHE_MASK);

    /* Set whole FlexSPI0 space to write through. */
    CACHE64_POLSEL->REG0_TOP = 0x07FFFC00U;
    CACHE64_POLSEL->REG1_TOP = 0x0U;
    CACHE64_POLSEL->POLSEL = 0x1U;

    __ISB();
    __DSB();
  }

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  /* iMXRT6xx systemCoreClockUpdate */
  uint32_t freq = 0U;
  uint64_t freqTmp = 0U;

  switch ((CLKCTL0->MAINCLKSELB) & CLKCTL0_MAINCLKSELB_SEL_MASK)
  {
    case CLKCTL0_MAINCLKSELB_SEL(0): /* MAINCLKSELA clock */
      switch ((CLKCTL0->MAINCLKSELA) & CLKCTL0_MAINCLKSELA_SEL_MASK)
      {
        case CLKCTL0_MAINCLKSELA_SEL(0): /* FFRO clock (48/60m_irc) divider by 4 */
          freq = getFFroFreq() / 4U;
          break;
        case CLKCTL0_MAINCLKSELA_SEL(1): /* OSC clock (clk_in) */
          freq = getOscClk();
          break;
        case CLKCTL0_MAINCLKSELA_SEL(2): /* Low Power Oscillator Clock (1m_lposc) */
          freq = CLK_LPOSC_1MHZ;
          break;
        case CLKCTL0_MAINCLKSELA_SEL(3): /* FFRO clock */
          freq = getFFroFreq();
          break;
        default:
          freq = 0U;
          break;
      }
      break;
    case CLKCTL0_MAINCLKSELB_SEL(1): /* SFRO clock */
      freq = CLK_FRO_16MHZ;
      break;
    case CLKCTL0_MAINCLKSELB_SEL(2): /* Main System PLL clock */
      switch ((CLKCTL0->SYSPLL0CLKSEL) & CLKCTL0_SYSPLL0CLKSEL_SEL_MASK)
      {
        case CLKCTL0_SYSPLL0CLKSEL_SEL(0): /* SFRO clock */
          freq = CLK_FRO_16MHZ;
          break;
        case CLKCTL0_SYSPLL0CLKSEL_SEL(1): /* OSC clock (clk_in) */
          freq = getOscClk();
          break;
        case CLKCTL0_SYSPLL0CLKSEL_SEL(2): /* FFRO clock (48/60m_irc) divider by 2 */
          freq = getFFroFreq() / 2U;
          break;
        default:
          freq = 0U;
          break;
      }

      if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
      {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL0->SYSPLL0NUM))) / ((uint64_t)(CLKCTL0->SYSPLL0DENOM));
        freq *= ((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_MULT_MASK) >> CLKCTL0_SYSPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
        freq = (uint32_t)((uint64_t)freq * 18U /
               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD0_MASK) >> CLKCTL0_SYSPLL0PFD_PFD0_SHIFT));
      }
      freq = freq / ((CLKCTL0->MAINPLLCLKDIV & CLKCTL0_MAINPLLCLKDIV_DIV_MASK) + 1U);
      break;

    case CLKCTL0_MAINCLKSELB_SEL(3): /* RTC 32KHz clock */
        freq = CLK_RTC_32K_CLK;
        break;

    default:
        freq = 0U;
        break;
  }

  SystemCoreClock = freq / ((CLKCTL0->SYSCPUAHBCLKDIV & 0xffU) + 1U);

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
