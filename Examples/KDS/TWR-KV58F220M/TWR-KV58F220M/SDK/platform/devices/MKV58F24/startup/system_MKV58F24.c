/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KV5XP144M240RM Rev. 3, 02/2016
**     Version:             rev. 0.3, 2016-02-29
**     Build:               b160229
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2016 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 0.1 (2015-02-24)
**         Initial version.
**     - rev. 0.2 (2015-10-21)
**         UART0 - removed LON functionality.
**         FMC - corrected base address.
**     - rev. 0.3 (2016-02-29)
**         PORT - removed registers GICLR, GICHR.
**
** ###################################################################
*/

/*!
 * @file MKV58F24
 * @version 0.3
 * @date 2016-02-29
 * @brief Device specific configuration file for MKV58F24 (implementation file)
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
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

  /* Watchdog disable */

#if (DISABLE_WDOG)
  /* WDOG->UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
  /* WDOG->UNLOCK: WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
  /* WDOG->STCTRLH: ?=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,?=0,?=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) |
                 WDOG_STCTRLH_WAITEN_MASK |
                 WDOG_STCTRLH_STOPEN_MASK |
                 WDOG_STCTRLH_ALLOWUPDATE_MASK |
                 WDOG_STCTRLH_CLKSRC_MASK |
                 0x0100U;
#endif /* (DISABLE_WDOG) */

/* Enable instruction and data caches */
#if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT
  SCB_EnableICache();
#endif
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
  SCB_EnableDCache();
#endif

#ifdef CLOCK_SETUP
  /* Wake-up from VLLSx? */

  if((RCM->SRS0 & RCM_SRS0_WAKEUP_MASK) != 0x00U)
  {
    /* VLLSx recovery */
    if((PMC->REGSC & PMC_REGSC_ACKISO_MASK) != 0x00U)
    {
       PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release hold with ACKISO: Only has an effect if recovering from VLLSx.*/
    }
  }

  /* Power mode protection initialization */

#ifdef SYSTEM_SMC_PMPROT_VALUE
  SMC->PMPROT = SYSTEM_SMC_PMPROT_VALUE;
#endif

  /* High speed run mode enable */

#if ((SYSTEM_SMC_PMCTRL_VALUE & SMC_PMCTRL_RUNM_MASK) == (0x03U << SMC_PMCTRL_RUNM_SHIFT))
  SMC->PMCTRL = SYSTEM_SMC_PMCTRL_VALUE;                                       /* Enable HSRUN mode */
  while(SMC->PMSTAT != 0x80U) {                                                /* Wait until the system is in HSRUN mode */
  }
#endif /* ((SYSTEM_SMC_PMCTRL_VALUE & SMC_PMCTRL_RUNM_MASK) == (0x03U << SMC_PMCTRL_RUNM_SHIFT)) */

  /* System clock initialization */

  /* Internal reference clock trim initialization */
#if defined(SLOW_TRIM_ADDRESS)
  if ( *((uint8_t*)SLOW_TRIM_ADDRESS) != 0xFFU) {                              /* Skip if non-volatile flash memory is erased */
    MCG->C3 = *((uint8_t*)SLOW_TRIM_ADDRESS);
#endif /* defined(SLOW_TRIM_ADDRESS) */
#if defined(SLOW_FINE_TRIM_ADDRESS)
    MCG->C4 = (MCG->C4 & ~(MCG_C4_SCFTRIM_MASK)) | ((*((uint8_t*)SLOW_FINE_TRIM_ADDRESS)) & MCG_C4_SCFTRIM_MASK);
#endif /* SLOW_FINE_TRIM_ADDRESS */
#if defined(SLOW_TRIM_ADDRESS)
  }
#endif /* defined(SLOW_TRIM_ADDRESS) */
#if defined(FAST_TRIM_ADDRESS)
  if ( *((uint8_t*)FAST_TRIM_ADDRESS) != 0xFFU) {                              /* Skip if non-volatile flash memory is erased */
    MCG->C4 = (MCG->C4 & ~(MCG_C4_FCTRIM_MASK)) | ((*((uint8_t*)FAST_TRIM_ADDRESS)) & MCG_C4_FCTRIM_MASK);
#endif /* defined(FAST_TRIM_ADDRESS) */
#if defined(FAST_FINE_TRIM_ADDRESS)
    MCG->C2 = (MCG->C2 & ~(MCG_C2_FCFTRIM_MASK)) | ((*((uint8_t*)FAST_FINE_TRIM_ADDRESS)) & MCG_C2_FCFTRIM_MASK);
#endif /* defined(FAST_FINE_TRIM_ADDRESS) */
#if defined(FAST_TRIM_ADDRESS)
  }
#endif /* defined(FAST_TRIM_ADDRESS) */

  /* Set system prescalers and clock sources */
  SIM->CLKDIV1 = SYSTEM_SIM_CLKDIV1_VALUE;                                     /* Set system prescalers */
  SIM->SOPT1 = ((SIM->SOPT1) & (uint32_t)(~(SIM_SOPT1_OSC32KSEL_MASK))) | (SYSTEM_SIM_SOPT1_VALUE & (SIM_SOPT1_OSC32KSEL_MASK)); /* Set 32 kHz clock source (ERCLK32K) */

#if ((MCG_MODE == MCG_MODE_FEI) || (MCG_MODE == MCG_MODE_FBI) || (MCG_MODE == MCG_MODE_BLPI))

  /* FEI, FBI and BLPI MCG mode specific */

  /* External clock source pin routing when OSCERCLK or MCGPLLCLK is enabled */
  #if (((SYSTEM_OSC0_CR_VALUE & OSC0_CR_ERCLKEN_MASK) != 0U) || ((SYSTEM_MCG_C5_VALUE & (MCG_C5_PLLCLKEN_MASK | MCG_C5_PLLSTEN_MASK)) != 0U))
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if ((MCG->C2 & MCG_C2_EREFS_MASK) != 0U) {                                   /* Initialize not only EXTAL but also XTAL pin if oscillator is used */
    /* PORTA_PCR19: ISF=0,MUX=0 */
    PORTA->PCR[19] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
  #endif /* (((SYSTEM_OSC0_CR_VALUE & OSC0_CR_ERCLKEN_MASK) != 0U) || ((SYSTEM_MCG_C5_VALUE & (MCG_C5_PLLCLKEN_MASK | MCG_C5_PLLSTEN_MASK)) != 0U)) */

  /* Set MCG and OSC */
  MCG->SC = SYSTEM_MCG_SC_VALUE;                                               /* Set SC (fast clock internal reference divider) */
  MCG->C1 = SYSTEM_MCG_C1_VALUE;                                               /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
  /* Check that the source of the FLL reference clock is the requested one. */
  if ((SYSTEM_MCG_C1_VALUE & MCG_C1_IREFS_MASK) != 0x00U) {
    while((MCG->S & MCG_S_IREFST_MASK) == 0x00U) {
    }
  } else {
    while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) {
    }
  }
  MCG->C2 = (MCG->C2 & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (SYSTEM_MCG_C2_VALUE & (uint8_t)(~(MCG_C2_LP_MASK))); /* Set C2 (freq. range, ext. and int. reference selection etc. excluding trim bits; low power bit is set later) */
  MCG->C4 = (SYSTEM_MCG_C4_VALUE & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG->C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
  OSC0->CR = SYSTEM_OSC0_CR_VALUE;                                               /* Set OSC0_CR (OSCERCLK enable, oscillator capacitor load) */

#else /* MCG_MODE */

  /* FEE, FBE, PEE, PBE and BLPE MCG mode specific */

  /* External clock source pin routing */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if ((MCG->C2 & MCG_C2_EREFS_MASK) != 0U) {                                   /* Initialize not only EXTAL but also XTAL pin if oscillator is used */
    /* PORTA_PCR19: ISF=0,MUX=0 */
    PORTA->PCR[19] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }

  /* Set MCG and OSC */
  MCG->SC = SYSTEM_MCG_SC_VALUE;                                               /* Set SC (fast clock internal reference divider) */
  MCG->C2 = (MCG->C2 & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (SYSTEM_MCG_C2_VALUE & (uint8_t)(~(MCG_C2_LP_MASK))); /* Set C2 (freq. range, ext. and int. reference selection etc. excluding trim bits; low power bit is set later) */
  OSC0->CR = SYSTEM_OSC0_CR_VALUE;                                               /* Set OSC0_CR (OSCERCLK enable, oscillator capacitor load) */
#if (MCG_MODE == MCG_MODE_PEE)
  /* Prior entering PEE MCG mode the external reference clock has to be set */
  MCG->C1 = SYSTEM_MCG_C1_VALUE | MCG_C1_CLKS(0x02);                           /* Set C1 (FLL ext. reference divider, int. reference enable etc. but force external clock source selection) */
#else
  MCG->C1 = SYSTEM_MCG_C1_VALUE;                                               /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
#endif
  if ((SYSTEM_MCG_C2_VALUE & MCG_C2_EREFS_MASK) != 0U) {
    while((MCG->S & MCG_S_OSCINIT0_MASK) == 0x00U) {                           /* Check that the oscillator is running */
    }
  }
  /* Check that the source of the FLL reference clock is the requested one. */
  if ((SYSTEM_MCG_C1_VALUE & MCG_C1_IREFS_MASK) != 0x00U) {
    while((MCG->S & MCG_S_IREFST_MASK) == 0x00U) {
    }
  } else {
    while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) {
    }
  }
  MCG->C4 = ((SYSTEM_MCG_C4_VALUE)  & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG->C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
#endif /* MCG_MODE */

  /* Common for all MCG modes */

  /* Set PLL. PLL clock can be used to generate clock for some devices regardless of clock generator (MCGOUTCLK) mode */
  MCG->C5 = SYSTEM_MCG_C5_VALUE & (uint8_t)(~(MCG_C5_PLLCLKEN_MASK));          /* Set C5 (PLL settings, PLL reference divider etc. but do not enable PLL yet) */
  MCG->C6 = (SYSTEM_MCG_C6_VALUE) & (uint8_t)~(MCG_C6_PLLS_MASK);              /* Set C6 (VCO divider etc. but do not select PLL yet) */
  if ((SYSTEM_MCG_C5_VALUE & MCG_C5_PLLCLKEN_MASK) != 0U) {                    /* Omit second C5 access if not needed (allow compiler optimization) */
    MCG->C5 |= MCG_C5_PLLCLKEN_MASK;                                           /* Enable PLL */
  }
  /* Set OSCERCLK frequency */
  OSC0->DIV = SYSTEM_OSC0_OSC_DIV_VALUE;                                             /* Set OSC0_OSC_DIV (OSCERCLK divider) */
#if ((MCG_MODE == MCG_MODE_FEI) || (MCG_MODE == MCG_MODE_FEE))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x00U) {                                /* Wait until output of the FLL is selected */
  }
#elif ((MCG_MODE == MCG_MODE_FBI) || (MCG_MODE == MCG_MODE_BLPI))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x04U) {                                /* Wait until internal reference clock is selected as MCG output */
  }
#elif ((MCG_MODE == MCG_MODE_FBE) || (MCG_MODE == MCG_MODE_PBE) || (MCG_MODE == MCG_MODE_BLPE) || (MCG_MODE == MCG_MODE_PEE))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x08U) {                                /* Wait until external reference clock is selected as MCG output */
  }
#endif

  /* BLPI, BLPE, PEE and PBE MCG mode specific */

#if ((MCG_MODE == MCG_MODE_BLPI) || (MCG_MODE == MCG_MODE_BLPE))
  MCG->C2 |= (MCG_C2_LP_MASK);                                                 /* Disable FLL and PLL in bypass mode (enter BLPI or BLPE MCG mode) */
#elif ((MCG_MODE == MCG_MODE_PBE) || (MCG_MODE == MCG_MODE_PEE))
  MCG->C6 |= (MCG_C6_PLLS_MASK);                                               /* Select PLL (enter PBE MCG mode) */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U) {                                /* Wait until PLL is locked */
  }
  #if (MCG_MODE == MCG_MODE_PEE)
  MCG->C1 &= (uint8_t)~(MCG_C1_CLKS_MASK);                                     /* Swtich MCGOUTCLK from external clock source to PLL (enter PEE mode) */
  while((MCG->S & MCG_S_CLKST_MASK) != 0x0CU) {                                /* Wait until output of the PLL is selected */
  }
  #endif
#endif

/* PLL loss of lock interrupt request initialization */

#if ((SYSTEM_MCG_C6_VALUE & MCG_C6_LOLIE0_MASK) != 0U)
  NVIC_EnableIRQ(MCG_IRQn);                                                    /* Enable PLL loss of lock interrupt request */
#endif /* ((SYSTEM_MCG_C6_VALUE & MCG_C6_LOLIE0_MASK) != 0U) */

/* Very-low-power run mode enable */

#if ((SYSTEM_SMC_PMCTRL_VALUE & SMC_PMCTRL_RUNM_MASK) == (0x02U << SMC_PMCTRL_RUNM_SHIFT))
  SMC->PMCTRL = SYSTEM_SMC_PMCTRL_VALUE;                                       /* Enable VLPR mode */
  while(SMC->PMSTAT != 0x04U) {                                                /* Wait until the system is in VLPR mode */
  }
#endif /* ((SYSTEM_SMC_PMCTRL_VALUE & SMC_PMCTRL_RUNM_MASK) == (0x02U << SMC_PMCTRL_RUNM_SHIFT)) */
#endif

}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {


  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint16_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U) {
        /* External reference clock is selected */
        MCGOUTClock = CPU_XTAL_CLK_HZ;                                         /* System oscillator drives MCG clock */
        if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0U) {
          switch (MCG->C1 & MCG_C1_FRDIV_MASK) {
          case (uint8_t)MCG_C1_FRDIV(0x07):
            Divider = 1536;
            break;
          case (uint8_t)MCG_C1_FRDIV(0x06):
            Divider = 1280;
            break;
          default:
            Divider = (uint16_t)(32U << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
            break;
          }
        } else {/* ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0U) */
          Divider = (uint16_t)(1U << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        }
        MCGOUTClock = (MCGOUTClock / Divider);                                 /* Calculate the divided FLL reference clock */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640U;
          break;
        case 0x20u:
          MCGOUTClock *= 1280U;
          break;
        case 0x40u:
          MCGOUTClock *= 1920U;
          break;
        case 0x60u:
          MCGOUTClock *= 2560U;
          break;
        case 0x80u:
          MCGOUTClock *= 732U;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464U;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197U;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929U;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U)) */
      /* PLL is selected */
      Divider = (1U + (MCG->C5 & MCG_C5_PRDIV_MASK));
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = ((MCG->C6 & MCG_C6_VDIV_MASK) + 16U);
      MCGOUTClock = ((MCGOUTClock * Divider) >> 1U);                           /* Calculate the MCG output clock = VCO/2; VCO = (MCGOUTClock * Divider) */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U) {
    /* External reference clock is selected */
    MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
  SystemCoreClock = (MCGOUTClock / (1U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));

}
