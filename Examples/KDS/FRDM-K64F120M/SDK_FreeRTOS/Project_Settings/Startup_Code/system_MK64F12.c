/*
** ###################################################################
**     Processors:          MK64F12
**
**     Reference manual:    K64P144M120SF5RM, Rev.2, January 2014
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
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
**     http: www.freescale.com
**     mail: support@freescale.com
**
** ###################################################################
*/

/*!
 * @file MK64F12
 * @brief Device specific configuration file for MK64F12 (implementation file)
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

#if (DISABLE_WDOG)
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
  /* WDOG->UNLOCK: WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
  /* WDOG->STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,??=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) |
                 WDOG_STCTRLH_WAITEN_MASK |
                 WDOG_STCTRLH_STOPEN_MASK |
                 WDOG_STCTRLH_ALLOWUPDATE_MASK |
                 WDOG_STCTRLH_CLKSRC_MASK |
                 0x0100U;
#endif /* (DISABLE_WDOG) */
#if (CLOCK_SETUP == 0)
  /* SMC_PMPROT: ??=0,??=0,AVLP=0,??=0,ALLS=0,??=0,AVLLS=0,??=0 */
  SMC_PMPROT = 0x00U;                  /* Setup Power mode protection register */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
                SIM_CLKDIV1_OUTDIV2(0x00) |
                SIM_CLKDIV1_OUTDIV3(0x01) |
                SIM_CLKDIV1_OUTDIV4(0x01); /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL&=~1 */
  SIM_SOPT2 &= (uint32_t)~(uint32_t)(SIM_SOPT2_PLLFLLSEL(0x01)); /* Select FLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=3 */
  SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x03); /* LPO 1kHz oscillator drives 32 kHz clock for various peripherals */
    /* Switch to FEI Mode */
    /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
    MCG_C1 = MCG_C1_CLKS(0x00) |
             MCG_C1_FRDIV(0x00) |
             MCG_C1_IREFS_MASK |
             MCG_C1_IRCLKEN_MASK;
    /* MCG_C2: LOCRE0=0,RANGE=0,HGO=0,EREFS=0,LP=0,IRCS=0 */
    MCG_C2 &= (uint8_t)~(uint8_t)(
               MCG_C2_LOCRE0_MASK |
               MCG_C2_RANGE(0x03) |
               MCG_C2_HGO_MASK |
               MCG_C2_EREFS_MASK |
               MCG_C2_LP_MASK |
               MCG_C2_IRCS_MASK
              );
    /* MCG_C4: DMX32=0,DRST_DRS=0 */
    MCG_C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));
    /* OSC_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
    OSC_CR = OSC_CR_ERCLKEN_MASK;
    /* MCG_C7: OSCSEL=0 */
    MCG_C7 &= (uint8_t)~(uint8_t)(MCG_C7_OSCSEL(0x03));
    /* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
    MCG_C5 = MCG_C5_PRDIV0(0x00);
    /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
    MCG_C6 = MCG_C6_VDIV0(0x00);
    while((MCG_S & MCG_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
    }
    while((MCG_S & 0x0CU) != 0x00U) {  /* Wait until output of the FLL is selected */
    }
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
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u) {
        /* External reference clock is selected */
        switch (MCG->C7 & MCG_C7_OSCSEL_MASK) {
        case 0x00u:
          MCGOUTClock = CPU_XTAL_CLK_HZ;                                       /* System oscillator drives MCG clock */
          break;
        case 0x01u:
          MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                    /* RTC 32 kHz oscillator drives MCG clock */
          break;
        case 0x02u:
        default:
          MCGOUTClock = CPU_INT_IRC_CLK_HZ;                                              /* IRC 48MHz oscillator drives MCG clock */
        }
        if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0u) {
          switch (MCG->C1 & MCG_C1_FRDIV_MASK) {
          case MCG_C1_FRDIV(0x07):
            Divider = 1536;
            break;
          case MCG_C1_FRDIV(0x06):
            Divider = 1280;
            break;
          default:
            Divider = (uint16_t)(32u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
          }
        } else {/* ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0u) */
          Divider = (uint16_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        }
        MCGOUTClock = (MCGOUTClock / Divider);  /* Calculate the divided FLL reference clock */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640u;
          break;
        case 0x20u:
          MCGOUTClock *= 1280u;
          break;
        case 0x40u:
          MCGOUTClock *= 1920u;
          break;
        case 0x60u:
          MCGOUTClock *= 2560u;
          break;
        case 0x80u:
          MCGOUTClock *= 732u;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464u;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197u;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929u;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
      /* PLL is selected */
      Divider = (1u + (MCG->C5 & MCG_C5_PRDIV0_MASK));
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = ((MCG->C6 & MCG_C6_VDIV0_MASK) + 24u);
      MCGOUTClock *= Divider;                       /* Calculate the MCG output clock */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    switch (MCG->C7 & MCG_C7_OSCSEL_MASK) {
    case 0x00u:
      MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
      break;
    case 0x01u:
      MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                        /* RTC 32 kHz oscillator drives MCG clock */
      break;
    case 0x02u:
    default:
      MCGOUTClock = CPU_INT_IRC_CLK_HZ;                                              /* IRC 48MHz oscillator drives MCG clock */
    }
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
  SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
