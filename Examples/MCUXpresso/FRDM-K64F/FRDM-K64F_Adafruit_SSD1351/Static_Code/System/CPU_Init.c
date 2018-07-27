/** ###################################################################
**      Filename    : CPU_Init.c
**      Processor   : MK64FN1M0VLL12
**      Version     : 1.0
**      Abstract    :
**         This file implements the MCU initialization and CPU component runtime methods.
** 
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
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
** ###################################################################*/
/*!
** @file CPU_Init.c                                                  
** @version 01.00
** @brief
**         This file implements the MCU initialization and CPU component runtime methods.
*/         
/*!
**  @addtogroup CPU_Init_module CPU_Init module documentation
**  @{
*/         

/* MODULE CPU_Init.c */
#include "PE_Types.h"
#include "MK64F12.h"
#include "Init_Config.h"
#include "Peripherals_Init.h"
#include "CPU_Init.h"
#include "Vectors_Config.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CPU_FLASH_CONFIG_FIELD
/* Flash configuration field */
  #if defined(__CWCC__)
/* Pragma to place the flash configuration field on correct location defined in linker file. */
#pragma define_section cfmconfig ".cfmconfig" ".cfmconfig" ".cfmconfig" far_abs R

static __declspec(cfmconfig) uint8_t _cfm[0x10] = {CPU_FLASH_CONFIG_FIELD};
  #elif defined(__IAR_SYSTEMS_ICC__)    
/* Pragma to place the flash configuration field on correct location defined in linker file. */
#pragma language=extended
#pragma location = "FlashConfig"

__root const uint8_t Config[0x10] @ "FlashConfig" = {CPU_FLASH_CONFIG_FIELD};
  #elif defined(__GNUC__)
__attribute__ ((section (".cfmconfig"))) const uint8_t _cfm[0x10] = {CPU_FLASH_CONFIG_FIELD};
  #elif defined(__CC_ARM)
__attribute__ ((section (".cfmconfig"))) const uint8_t _cfm[0x10] __attribute__((used)) = {CPU_FLASH_CONFIG_FIELD};
  #else
    #error Unsupported compiler!
  #endif
#endif    

extern void Common_Init(void);         /* Forward declaration of generated common initialization in generated CPU module */
extern void Components_Init(void);     /* Forward declaration of generated LDD components initialization in generated CPU module */
extern void LDD_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration); 
  
/* Global variables */

volatile uint8_t SR_reg;               /* Current value of the FAULTMASK register */
volatile uint8_t SR_lock = 0x00U;      /* Lock */
LDD_TClockConfiguration ClockConfigurationID = CPU_CLOCK_CONFIG_0; /* Active clock configuration */

static const CPU_TClockGenMode ClockGenModeMatrix[8][8] = {
/* This matrix defines which mode is next in the MCG Mode state diagram in transitioning from the
   current mode to a target mode*/
  { CPU_MCG_MODE_FEI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FEE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE  }, /* FEI */
  { CPU_MCG_MODE_FEI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_BLPI, CPU_MCG_MODE_FEE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE  }, /* FBI */
  { CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_BLPI, CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI  }, /* BLPI */
  { CPU_MCG_MODE_FEI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FEE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE  }, /* FEE */
  { CPU_MCG_MODE_FEI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FBI,  CPU_MCG_MODE_FEE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_BLPE, CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE  }, /* FBE */
  { CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_BLPE, CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE  }, /* BLPE */
  { CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_FBE,  CPU_MCG_MODE_BLPE, CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PEE  }, /* PBE */
  { CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PBE,  CPU_MCG_MODE_PEE  }  /* PEE */
};

static const CPU_TClockConfigDescriptor CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_NUMBER] = {
  #if defined(CPU_CLOCK_CONFIG_0)
  /* Clock configuration 0 */
  {
    CPU_MCG_MODE_CONFIG_0,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_0,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_0,CPU_MCG_C2_CONFIG_0,CPU_MCG_C4_CONFIG_0,CPU_MCG_C5_CONFIG_0,CPU_MCG_C6_CONFIG_0,CPU_MCG_C7_CONFIG_0,CPU_MCG_SC_CONFIG_0,CPU_OSC_CR_CONFIG_0,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_0,CPU_SIM_SOPT2_CONFIG_0,CPU_SIM_CLKDIV1_CONFIG_0,
    },
    CPU_BUS_CLK_HZ_CONFIG_0            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_1)
  /* Clock configuration 1 */
  ,{
    CPU_MCG_MODE_CONFIG_1,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_1,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_1,CPU_MCG_C2_CONFIG_1,CPU_MCG_C4_CONFIG_1,CPU_MCG_C5_CONFIG_1,CPU_MCG_C6_CONFIG_1,CPU_MCG_C7_CONFIG_1,CPU_MCG_SC_CONFIG_1,CPU_OSC_CR_CONFIG_1,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_1,CPU_SIM_SOPT2_CONFIG_1,CPU_SIM_CLKDIV1_CONFIG_1,
    },
    CPU_BUS_CLK_HZ_CONFIG_1            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_2)
  /* Clock configuration 2 */
  ,{
    CPU_MCG_MODE_CONFIG_2,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_2,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_2,CPU_MCG_C2_CONFIG_2,CPU_MCG_C4_CONFIG_2,CPU_MCG_C5_CONFIG_2,CPU_MCG_C6_CONFIG_2,CPU_MCG_C7_CONFIG_2,CPU_MCG_SC_CONFIG_2,CPU_OSC_CR_CONFIG_2,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_2,CPU_SIM_SOPT2_CONFIG_2,CPU_SIM_CLKDIV1_CONFIG_2,
    },
    CPU_BUS_CLK_HZ_CONFIG_2            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_3)
  /* Clock configuration 3 */
  ,{
    CPU_MCG_MODE_CONFIG_3,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_3,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_3,CPU_MCG_C2_CONFIG_3,CPU_MCG_C4_CONFIG_3,CPU_MCG_C5_CONFIG_3,CPU_MCG_C6_CONFIG_3,CPU_MCG_C7_CONFIG_3,CPU_MCG_SC_CONFIG_3,CPU_OSC_CR_CONFIG_3,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_3,CPU_SIM_SOPT2_CONFIG_3,CPU_SIM_CLKDIV1_CONFIG_3,
    },
    CPU_BUS_CLK_HZ_CONFIG_3            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_4)
  /* Clock configuration 4 */
  ,{
    CPU_MCG_MODE_CONFIG_4,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_4,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_4,CPU_MCG_C2_CONFIG_4,CPU_MCG_C4_CONFIG_4,CPU_MCG_C5_CONFIG_4,CPU_MCG_C6_CONFIG_4,CPU_MCG_C7_CONFIG_4,CPU_MCG_SC_CONFIG_4,CPU_OSC_CR_CONFIG_4,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_4,CPU_SIM_SOPT2_CONFIG_4,CPU_SIM_CLKDIV1_CONFIG_4,
    },
    CPU_BUS_CLK_HZ_CONFIG_4            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_5)
  /* Clock configuration 5 */
  ,{
    CPU_MCG_MODE_CONFIG_5,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_5,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_5,CPU_MCG_C2_CONFIG_5,CPU_MCG_C4_CONFIG_5,CPU_MCG_C5_CONFIG_5,CPU_MCG_C6_CONFIG_5,CPU_MCG_C7_CONFIG_5,CPU_MCG_SC_CONFIG_5,CPU_OSC_CR_CONFIG_5,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_5,CPU_SIM_SOPT2_CONFIG_5,CPU_SIM_CLKDIV1_CONFIG_5,
    },
    CPU_BUS_CLK_HZ_CONFIG_5            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_6)
  /* Clock configuration 6 */
  ,{
    CPU_MCG_MODE_CONFIG_6,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_6,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_6,CPU_MCG_C2_CONFIG_6,CPU_MCG_C4_CONFIG_6,CPU_MCG_C5_CONFIG_6,CPU_MCG_C6_CONFIG_6,CPU_MCG_C7_CONFIG_6,CPU_MCG_SC_CONFIG_6,CPU_OSC_CR_CONFIG_6,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_6,CPU_SIM_SOPT2_CONFIG_6,CPU_SIM_CLKDIV1_CONFIG_6,
    },
    CPU_BUS_CLK_HZ_CONFIG_6            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_7)
  /* Clock configuration 7 */
  ,{
    CPU_MCG_MODE_CONFIG_7,             /* Clock generator mode */
    CPU_CLOCK_PMODE_CONFIG_7,          /* Very low power mode enable/disable */
    {                                  /* MCG registers */
      CPU_MCG_C1_CONFIG_7,CPU_MCG_C2_CONFIG_7,CPU_MCG_C4_CONFIG_7,CPU_MCG_C5_CONFIG_7,CPU_MCG_C6_CONFIG_7,CPU_MCG_C7_CONFIG_7,CPU_MCG_SC_CONFIG_7,CPU_OSC_CR_CONFIG_7,
    },
    {                                  /* SIM registers */
      CPU_SIM_SOPT1_CONFIG_7,CPU_SIM_SOPT2_CONFIG_7,CPU_SIM_CLKDIV1_CONFIG_7,
    },
    CPU_BUS_CLK_HZ_CONFIG_7            /* Bus frequency */
  }
  #endif
};

static const CPU_TClockGenRegs CPU_DefaultFEI = {
  CPU_DEFAULT_FEI_MCG_C1,CPU_DEFAULT_FEI_MCG_C2,CPU_DEFAULT_FEI_MCG_C4,CPU_DEFAULT_FEI_MCG_C5,CPU_DEFAULT_FEI_MCG_C6,CPU_DEFAULT_FEI_MCG_C7,CPU_DEFAULT_FEI_MCG_SC,CPU_DEFAULT_FEI_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBI = {
  CPU_DEFAULT_FBI_MCG_C1,CPU_DEFAULT_FBI_MCG_C2,CPU_DEFAULT_FBI_MCG_C4,CPU_DEFAULT_FBI_MCG_C5,CPU_DEFAULT_FBI_MCG_C6,CPU_DEFAULT_FBI_MCG_C7,CPU_DEFAULT_FBI_MCG_SC,CPU_DEFAULT_FBI_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultBLPI = {
  CPU_DEFAULT_BLPI_MCG_C1,CPU_DEFAULT_BLPI_MCG_C2,CPU_DEFAULT_BLPI_MCG_C4,CPU_DEFAULT_BLPI_MCG_C5,CPU_DEFAULT_BLPI_MCG_C6,CPU_DEFAULT_BLPI_MCG_C7,CPU_DEFAULT_BLPI_MCG_SC,CPU_DEFAULT_BLPI_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFEE = {
  CPU_DEFAULT_FEE_MCG_C1,CPU_DEFAULT_FEE_MCG_C2,CPU_DEFAULT_FEE_MCG_C4,CPU_DEFAULT_FEE_MCG_C5,CPU_DEFAULT_FEE_MCG_C6,CPU_DEFAULT_FEE_MCG_C7,CPU_DEFAULT_FEE_MCG_SC,CPU_DEFAULT_FEE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBE = {
  CPU_DEFAULT_FBE_MCG_C1,CPU_DEFAULT_FBE_MCG_C2,CPU_DEFAULT_FBE_MCG_C4,CPU_DEFAULT_FBE_MCG_C5,CPU_DEFAULT_FBE_MCG_C6,CPU_DEFAULT_FBE_MCG_C7,CPU_DEFAULT_FBE_MCG_SC,CPU_DEFAULT_FBE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultBLPE = {
  CPU_DEFAULT_BLPE_MCG_C1,CPU_DEFAULT_BLPE_MCG_C2,CPU_DEFAULT_BLPE_MCG_C4,CPU_DEFAULT_BLPE_MCG_C5,CPU_DEFAULT_BLPE_MCG_C6,CPU_DEFAULT_BLPE_MCG_C7,CPU_DEFAULT_BLPE_MCG_SC,CPU_DEFAULT_BLPE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultPBE = {
  CPU_DEFAULT_PBE_MCG_C1,CPU_DEFAULT_PBE_MCG_C2,CPU_DEFAULT_PBE_MCG_C4,CPU_DEFAULT_PBE_MCG_C5,CPU_DEFAULT_PBE_MCG_C6,CPU_DEFAULT_PBE_MCG_C7,CPU_DEFAULT_PBE_MCG_SC,CPU_DEFAULT_PBE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultPEE = {
  CPU_DEFAULT_PEE_MCG_C1,CPU_DEFAULT_PEE_MCG_C2,CPU_DEFAULT_PEE_MCG_C4,CPU_DEFAULT_PEE_MCG_C5,CPU_DEFAULT_PEE_MCG_C6,CPU_DEFAULT_PEE_MCG_C7,CPU_DEFAULT_PEE_MCG_SC,CPU_DEFAULT_PEE_OSC_CR
};

static const CPU_TClockGenRegs *const CPU_ClockGenModeRegs[CPU_MCG_MODES] = {
  &CPU_DefaultFEI,
  &CPU_DefaultFBI,
  &CPU_DefaultBLPI,
  &CPU_DefaultFEE,
  &CPU_DefaultFBE,
  &CPU_DefaultBLPE,
  &CPU_DefaultPBE,
  &CPU_DefaultPEE
};

/*
** ===================================================================
**     Method      :  Cpu_SetBASEPRI (component MK64FN1M0LL12)
**
**     Description :
**         This method sets the BASEPRI core register.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */
#if defined(_lint)
  #define CPU_SetBASEPRI(Level)  /* empty */
#elif defined(__CWCC__)
asm void CPU_SetBASEPRI(register uint32_t Level) {
  MSR BASEPRI,R0;
  MOV PC,LR
}
#elif defined(__GNUC__)
void CPU_SetBASEPRI(uint32_t Level) {
  __asm ("msr basepri, %[input]"::[input] "r" (Level):);
}
#elif defined(__CC_ARM)
__asm CPU_SetBASEPRI(uint32_t Level) {
  MSR BASEPRI,R0
  BX  LR
}
#endif
/*lint -restore Enable MISRA rule (2.1,1.1) checking. */

/*
** ===================================================================
**     Method      :  __init_hardware (component MK64FN1M0LL12)
**
**     Description :
**         This method is called from the __thumb_startup() function and 
**         provides necessary system initialization such as PLL, and 
**         external bus. Function of this name is used when GCC or ARM 
**         Keil compiler is used. IAR compiler uses function 
**         __low_level_init().
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#if !defined(PEX_ENTRYPOINT_FUNCTION)
  #if defined(__IAR_SYSTEMS_ICC__)
    #define PEX_ENTRYPOINT_FUNCTION __low_level_init
  #elif defined(__CWCC__) | defined(__GNUC__) | defined(__CC_ARM)
    #define PEX_ENTRYPOINT_FUNCTION __init_hardware
  #endif
#endif /* !defined(PEX_ENTRYPOINT_FUNCTION) */
#if !defined(PEX_ENTRYPOINT_FUNCTION_TYPE)
  #if defined(__IAR_SYSTEMS_ICC__)
    #define PEX_ENTRYPOINT_FUNCTION_TYPE int
  #elif defined(__CWCC__) | defined(__GNUC__) | defined(__CC_ARM)
    #define PEX_ENTRYPOINT_FUNCTION_TYPE void
  #endif
#endif /* !defined(PEX_ENTRYPOINT_FUNCTION_TYPE) */
#if !defined(PEX_ENTRYPOINT_FUNCTION_RETURN)
  #if defined(__IAR_SYSTEMS_ICC__)    
    #define PEX_ENTRYPOINT_FUNCTION_RETURN return 1;
  #endif
#endif
PEX_ENTRYPOINT_FUNCTION_TYPE PEX_ENTRYPOINT_FUNCTION()
{
  /* Interrupt vector placement initialization */
  #if PEX_VECTOR_TABLE
    #if defined(__IAR_SYSTEMS_ICC__)
  SCB_VTOR = (uint32_t)(&__vector_table); /* Set the interrupt vector table position */
    #elif defined(__CWCC__) | defined(__GNUC__) | defined(__CC_ARM)
  SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
    #endif
  #endif
  /* Disable the WDOG module */
  #if STARTUP_WDOG
  WDOG_UNLOCK = (uint16_t)STARTUP_WDOG_KEY_1; /* Key 1 */
  WDOG_UNLOCK = (uint16_t)STARTUP_WDOG_KEY_2; /* Key 2 */
  WDOG_STCTRLH = (uint16_t)STARTUP_WDOG_STCTRLH_VALUE; /* Disable WDOG */
  #endif /* STARTUP_WDOG */
  
  /* System clock initialization */
#if defined(CPU_MCG_MODE_CONFIG_0) && (CPU_MCG_MODE_CONFIG_0 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_1) && (CPU_MCG_MODE_CONFIG_1 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_2) && (CPU_MCG_MODE_CONFIG_2 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_3) && (CPU_MCG_MODE_CONFIG_3 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_4) && (CPU_MCG_MODE_CONFIG_4 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_5) && (CPU_MCG_MODE_CONFIG_5 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_6) && (CPU_MCG_MODE_CONFIG_6 & CPU_CLOCK_IRC48M_MASK) || \
    defined(CPU_MCG_MODE_CONFIG_7) && (CPU_MCG_MODE_CONFIG_7 & CPU_CLOCK_IRC48M_MASK)
  /* Enable IRC48MHz clock */
  SIM_SCGC4 |= (uint32_t)SIM_SCGC4_USBOTG_MASK;
  USB0_CLK_RECOVER_IRC_EN |= (uint32_t)USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK;
  SIM_SCGC4 |= SIM_SCGC4_USBOTG_MASK;
  SIM_SCGC4 &= (uint32_t)~(uint32_t)(SIM_SCGC4_USBOTG_MASK);
#endif 
#if STARTUP_RTCOSC
  /* SIM_SCGC6: RTC=1 */
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
  if ((RTC_CR & RTC_CR_OSCE_MASK) == 0u) { /* Only if the OSCILLATOR is not already enabled */
    RTC_CR = (uint32_t)((RTC_CR & (uint32_t)~(uint32_t)(RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK)) | (uint32_t)STARTUP_RTC_CR_SC_VALUE);
    RTC_CR |= (uint32_t)RTC_CR_OSCE_MASK;
    RTC_CR &= (uint32_t)~(uint32_t)RTC_CR_CLKO_MASK;
  }
#endif
    
  /* Internal reference clock trim initialization */
  #if (defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) || defined(STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS))
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS)
  if ( *((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) != 0xFFU) { /* Skip if non-volatile flash memory is erased */
    MCG_C3 = *((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS);
    #endif /* defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) */
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)
      #if defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)
        #if (STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS == STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)
    MCG_C4 = (MCG_C4 & ~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)) |
             ((*((uint8_t*) STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)) & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK));
        #else /* (STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS == STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS) */
    MCG_C4 = (MCG_C4 & ~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)) | 
             ((*((uint8_t*) STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)) & MCG_C4_FCTRIM_MASK) | 
             ((*((uint8_t*) STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)) & MCG_C4_SCFTRIM_MASK);
        #endif /* (STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS == STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS) */
        #if defined(STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS)
    MCG_C2 = (MCG_C2 & ~(MCG_C2_FCFTRIM_MASK)) | ((*((uint8_t*)STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)) & MCG_C2_FCFTRIM_MASK);
        #endif /* defined(STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS) */
      #else /* defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) */
    MCG_C4 = (MCG_C4 & ~(MCG_C4_SCFTRIM_MASK)) | ((*((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)) & MCG_C4_SCFTRIM_MASK);
      #endif /* defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) */
    #endif /* STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS */
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS)
  }
    #endif /* defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) */
  #elif (defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) || defined(STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS))
    #if defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)
  if ( *((uint8_t*)STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) != 0xFFU) { /* Skip if non-volatile flash memory is erased */
    MCG_C4 = (MCG_C4 & ~(MCG_C4_FCTRIM_MASK)) | ((*((uint8_t*)STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)) & MCG_C4_FCTRIM_MASK);
    #endif /* defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) */
    #if defined(STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS)
    MCG_C2 = (MCG_C2 & ~(MCG_C2_FCFTRIM_MASK)) | ((*((uint8_t*)STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS)) & MCG_C2_FCFTRIM_MASK);
    #endif /* defined(STARTUP_CLOCK_INTERNAL_FAST_FINE_TRIM_ADDRESS) */
    #if defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS)
  }
    #endif /* defined(STARTUP_CLOCK_INTERNAL_FAST_TRIM_ADDRESS) */
  #endif /* STARTUP_CLOCK_INTERNAL_FAST_TRIM */
  /* Low power modes protection */
  
  /* Disable very low power mode protection */
  SMC_PMPROT = (CPU_LOW_POWER_ALLOW_VLP? SMC_PMPROT_AVLP_MASK : 0) |
               (CPU_LOW_POWER_ALLOW_LLS? SMC_PMPROT_ALLS_MASK : 0) |
               (CPU_LOW_POWER_ALLOW_VLLS? SMC_PMPROT_AVLLS_MASK : 0);
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=4,OUTDIV4=4,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
                SIM_CLKDIV1_OUTDIV2(0x01) |
                SIM_CLKDIV1_OUTDIV3(0x04) |
                SIM_CLKDIV1_OUTDIV4(0x04); /* Set the system prescalers to safe value */
  CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_0);
  SIM_CLKDIV1 = (uint32_t)CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_0].SysRegs.SIM_CLKDIV1_value; /* Update system prescalers */
  SIM_SOPT1 = (uint32_t)((SIM_SOPT1 & (uint32_t)~(uint32_t)SIM_SOPT1_OSC32KSEL_MASK) | (uint32_t)CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_0].SysRegs.SIM_SOPT1_value); /* Update 32 kHz oscillator clock source (ERCLK32K) */
  SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)SIM_SOPT2_PLLFLLSEL_MASK) | (uint32_t)CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_0].SysRegs.SIM_SOPT2_value); /* Update PLL/FLL clock select */
  #if defined(PEX_ENTRYPOINT_FUNCTION_RETURN)
  PEX_ENTRYPOINT_FUNCTION_RETURN
  #endif  
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component MK64FN1M0LL12)
**
**     Description :
**         Initializes components and provides common register 
**         initialization. The method is called automatically as a part 
**         of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* RTOS initialization */

  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  
  
  /* NMI, reset and debug pins port clock gate enable */
  
  #if CPU_NMI_PIN | CPU_RESET_PIN | CPU_SWD_DIO_PIN | CPU_SWD_CLK_PIN
  SIM_SCGC5 |= (uint32_t)SIM_SCGC5_PORTA_MASK; /* NMI and reset pin clock gate enable */
  #endif /* CPU_NMI_PIN | CPU_RESET_PIN */

  /* Non-maskable interrupt pin initialization */
  
  #if CPU_NMI_PIN
  /* Non-maskable interrupt pin routing */
  /* PORTA_PCR4: ISF=0,MUX=7 */
  PORTA_PCR4 = (uint32_t)((PORTA_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  #endif /* CPU_NMI_PIN */

  /* JTAG TDI pin initialization */
  
  #if CPU_JTAG_TDI_PIN
  /* JTAG TDI pin routing */
  #endif /* CPU_JTAG_TDI_PIN */

  /* JTAG TDO pin initialization */
  
  #if CPU_JTAG_TDO_PIN
  /* JTAG TDO pin routing */
  #endif /* CPU_JTAG_TDO_PIN */

  /* JTAG TDO pin initialization */
  
  #if CPU_JTAG_TCK_PIN
  /* JTAG TCK pin routing */
  #endif /* CPU_JTAG_TCK_PIN */
	
	/* JTAG TMS pin initialization */
  
  #if CPU_JTAG_TMS_PIN
  /* JTAG TMS pin routing */
  #endif /* CPU_JTAG_TMS_PIN */

	/* JTAG TRST pin initialization */
  
  #if CPU_JTAG_TRST_PIN
  /* JTAG nTRST pin routing */
  #endif /* CPU_JTAG_TRST_PIN */


  /* Common initialization */
  
  #if CPU_COMMON_INIT
  Common_Init();
  #endif /* CPU_COMMON_INIT */
  
  /* Peripheral initialization components initialization */

  #if CPU_PERIPHERALS_INIT
  Peripherals_Init();
  #endif /* CPU_PERIPHERALS_INIT */

  /* OnReset event */
  
  #ifdef CPU_ON_RESET_EVENT_NAME
  CPU_ON_RESET_EVENT_NAME((uint16_t)(((uint16_t)RCM_SRS1) << 8U) | (uint16_t)RCM_SRS0); /* Invoke an user event */
  #endif /* CPU_ON_RESET_EVENT_NAME */
  
  /* Rest of components initialization */
  
  #if CPU_COMPONENTS_INIT
  Components_Init();
  #endif /* CPU_COMPONENTS_INIT */

  /* Interrupts priority level initialization */
  
   #if (CPU_INT_PRIORITY == 0)
   __DI();
  #else /* (CPU_INT_PRIORITY == 0) */
    #if defined(__IAR_SYSTEMS_ICC__)
    __set_BASEPRI(CPU_INT_PRIORITY);
    #elif defined(__CWCC__)
    CPU_SetBASEPRI(CPU_INT_PRIORITY);
    #elif defined(__GNUC__)
    CPU_SetBASEPRI(CPU_INT_PRIORITY);
    #elif defined(__CC_ARM)
    CPU_SetBASEPRI(CPU_INT_PRIORITY);
  	#else /* defined(compiler ID) */
  	  #error Unsupported compiler
  	#endif /* defined(compiler ID) */
  #endif
}

CPU_TClockGenMode CPU_GetClockGenMode(void)
{
  switch (MCG_C1  & MCG_C1_CLKS_MASK) {
    case  0x00U:
      /* Output of FLL or PLL is selected */
      if ((MCG_C6 & MCG_C6_PLLS_MASK) == 0x00U) {
        /* Output of FLL is selected */
        if ((MCG_C1 & MCG_C1_IREFS_MASK) == 0x00U) {
          /* External reference clock is selected */
          return CPU_MCG_MODE_FEE;
        } else {
          /* Internal reference clock is selected */
          return CPU_MCG_MODE_FEI;
        }
      } else {
        /* Output of FLL is selected */
	      return CPU_MCG_MODE_PEE;
	    }  
    case 0x40U:
      /* Internal reference clock is selected */
      if ((MCG_C2 & MCG_C2_LP_MASK) == 0x00U) {
        /* Low power mode is disabled */
        return CPU_MCG_MODE_FBI;
      } else {
        /* Low power mode is enabled */
        return CPU_MCG_MODE_BLPI;
      }
    case 0x80U:
      /* External reference clock is selected */
      if ((MCG_C6 & MCG_C6_PLLS_MASK) == 0x00U) {
        /* FLL or PLL is selected */
        if ((MCG_C2 & MCG_C2_LP_MASK) == 0x00U) {
          /* FLL is selected */
          return CPU_MCG_MODE_FBE;
        } else {
          /* Low power mode is enabled */
          return CPU_MCG_MODE_BLPE;
        }
      } else {
        /* PLL is selected */
        return CPU_MCG_MODE_PBE;
      }
    default:
      return (CPU_TClockGenMode)0x00U;
  }
}

void CPU_SetClockConfigGenMode(LDD_TClockConfiguration ConfigID)
{
  CPU_TClockGenMode NextMode, TargetMCGMode;
  CPU_TClockGenRegs NextModeRegs;
  CPU_TClockGenMode TargetMode = CPU_ClockConfigDescriptors[ConfigID].Mode;
  
  /* External clock source pin routing */
  if ((TargetMode & (CPU_CLOCK_EXTERNAL_CLOCK_MASK | CPU_CLOCK_EXTERNAL_CRYSTAL_MASK)) != 0) { /* Is external clock source used in targeted clock configuration? */
    /* If yes, initialize the EXTAL pin routing */
    SIM_SCGC5 |= (uint32_t)SIM_SCGC5_PORTA_MASK; /* Enable EXTAL/XTAL pins clock gate */
    /* PORTA_PCR18: ISF=0,MUX=0 */
    PORTA_PCR18 &= (uint32_t)~(uint32_t)(
                    PORT_PCR_ISF_MASK |
                    PORT_PCR_MUX(0x07)
                   );
    if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) { /* Is external crystal/resonator used in targeted clock configuration? */
      /* If yes, initialize also XTAL pin routing */
      /* PORTA_PCR19: ISF=0,MUX=0 */
      PORTA_PCR19 &= (uint32_t)~(uint32_t)(
                      PORT_PCR_ISF_MASK |
                      PORT_PCR_MUX(0x07)
                     );
    }
  }
  
  if ((MCG_SC & MCG_SC_FCRDIV_MASK) != CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_SC_value) { /* Check if it is necessary to update Fast Clock Internal Reference Divider */ 
    if ((MCG_C2 & MCG_C2_IRCS_MASK) == 0x00U) {
      MCG_SC = (MCG_SC & (uint8_t)(~(MCG_SC_FCRDIV_MASK))) | CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_SC_value;
    } else {
      if ((MCG_C1 & (MCG_C1_IREFS_MASK || MCG_C1_IRCLKEN_MASK)) != 0x00U) { /* Is internal reference clock active? */      
        MCG_C2 &= (uint8_t)(~(MCG_C2_IRCS_MASK)); /* Disable the fast internal clock */
        while((MCG_S & MCG_S_IRCST_MASK) != 0x00U) { /* Check that the source internal reference clock is slow clock. */
        }
        MCG_SC = (MCG_SC & (uint8_t)(~(MCG_SC_FCRDIV_MASK))) | CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_SC_value;    
        MCG_C2 |= MCG_C2_IRCS_MASK;    /* Re-enable the fast internal clock */
        while((MCG_S & MCG_S_IRCST_MASK) == 0x00U) { /* Check that the source internal reference clock is fast clock. */
        }
      } else {
        MCG_C2 &= (uint8_t)(~(MCG_C2_IRCS_MASK)); /* Disable the fast internal clock */
        MCG_SC = (MCG_SC & (uint8_t)(~(MCG_SC_FCRDIV_MASK))) | CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_SC_value;    
        MCG_C2 |= MCG_C2_IRCS_MASK;    /* Re-enable the fast internal clock */
      }
    }
  }      
  NextMode = CPU_GetClockGenMode(); /* Identify the currently active MCG mode */
  TargetMCGMode = TargetMode & CPU_MCG_MODE_INDEX_MASK;
  do {
    NextMode = ClockGenModeMatrix[NextMode & CPU_MCG_MODE_INDEX_MASK][TargetMode & CPU_MCG_MODE_INDEX_MASK];
    if (((NextMode == CPU_MCG_MODE_PBE) && (TargetMCGMode == CPU_MCG_MODE_PEE)) || ((NextMode == CPU_MCG_MODE_FBE) && (TargetMCGMode == CPU_MCG_MODE_FEE)) || (NextMode == TargetMCGMode)) {
      NextModeRegs = CPU_ClockConfigDescriptors[ConfigID].GenRegs;
    } else {
      NextModeRegs = *CPU_ClockGenModeRegs[NextMode & CPU_MCG_MODE_INDEX_MASK];
    }
    switch (NextMode) {
      case CPU_MCG_MODE_FEI:
      case CPU_MCG_MODE_FBI:
        MCG_C1 = NextModeRegs.MCG_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        while((MCG_S & MCG_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
        }
        MCG_C2 = ((NextModeRegs.MCG_C2_value) & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (MCG_C2 & MCG_C2_FCFTRIM_MASK); /* Set C2 (freq. range, ext. and int. reference selection etc.; trim values not changed) */
        MCG_C4 = ((NextModeRegs.MCG_C4_value) & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG_C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
        MCG_C7 = NextModeRegs.MCG_C7_value; /* Select MCG OSC clock source */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
        MCG_C5 = NextModeRegs.MCG_C5_value; /* Set C5 (PLL settings, PLL reference divider etc.) */
        MCG_C6 = NextModeRegs.MCG_C6_value; /* Set C6 (PLL select, VCO divider etc.) */
        if (TargetMode & CPU_CLOCK_PLL_MASK) {
          MCG_C5 |= MCG_C5_PLLCLKEN0_MASK;
        }
        break;
      case CPU_MCG_MODE_BLPI:
        MCG_C1 = NextModeRegs.MCG_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        while((MCG_S & MCG_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
        }
        MCG_C2 = ((NextModeRegs.MCG_C2_value) & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (MCG_C2 & MCG_C2_FCFTRIM_MASK); /* Set C2 (freq. range, ext. and int. reference selection etc.; trim values not changed) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
        if (TargetMode & CPU_CLOCK_FAST_MASK) {
          while((MCG_S & MCG_S_IRCST_MASK) == 0x00U) { /* Check that the fast external reference clock is selected. */
      	  }
      	}      	
        break;
      case CPU_MCG_MODE_FEE:
      case CPU_MCG_MODE_FBE:
        MCG_C2 = ((NextModeRegs.MCG_C2_value) & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (MCG_C2 & MCG_C2_FCFTRIM_MASK); /* Set C2 (freq. range, ext. and int. reference selection etc.; trim values not changed) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */      	
        MCG_C7 = NextModeRegs.MCG_C7_value; /* Select MCG OSC clock source */
        if (NextMode == CPU_MCG_MODE_FBE) {
          MCG_C1 = NextModeRegs.MCG_C1_value | MCG_C1_CLKS(0x02); /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        } else {
          MCG_C1 = NextModeRegs.MCG_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        }
        if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) {
          while((MCG_S & MCG_S_OSCINIT0_MASK) == 0x00U) { /* Check that the oscillator is running */
          }
        }
        while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
        }
        MCG_C4 = ((NextModeRegs.MCG_C4_value) & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG_C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
        MCG_C5 = NextModeRegs.MCG_C5_value; /* Set C5 (PLL settings, PLL reference divider etc.) */
        if (TargetMode & CPU_CLOCK_PLL_MASK) {
          MCG_C5 |= MCG_C5_PLLCLKEN0_MASK;
        }
        MCG_C6 = NextModeRegs.MCG_C6_value; /* Set C6 (PLL select, VCO divider etc.) */
        break;
      case CPU_MCG_MODE_BLPE:
        MCG_C1 = NextModeRegs.MCG_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        MCG_C2 = ((NextModeRegs.MCG_C2_value) & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (MCG_C2 & MCG_C2_FCFTRIM_MASK); /* Set C2 (freq. range, ext. and int. reference selection etc.; trim values not changed) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */      	
        MCG_C7 = NextModeRegs.MCG_C7_value; /* Select MCG OSC clock source */
        if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) {
          while((MCG_S & MCG_S_OSCINIT0_MASK) == 0x00U) { /* Check that the oscillator is running */
          }
        }
        break;
      case CPU_MCG_MODE_PEE:
      case CPU_MCG_MODE_PBE:
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
        MCG_C7 = NextModeRegs.MCG_C7_value; /* Select MCG OSC clock source */
        if (NextMode == CPU_MCG_MODE_PBE) {
          MCG_C1 = NextModeRegs.MCG_C1_value | MCG_C1_CLKS(0x02); /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        } else {
          MCG_C1 = NextModeRegs.MCG_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        }
        MCG_C2 = ((NextModeRegs.MCG_C2_value) & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (MCG_C2 & MCG_C2_FCFTRIM_MASK); /* Set C2 (freq. range, ext. and int. reference selection etc.; trim values not changed) */
        if ((TargetMode & CPU_MCG_MODE_INDEX_MASK) == CPU_MCG_MODE_PEE) {
          MCG_C5 = CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_C5_value; /* Set C5 (PLL settings, PLL reference divider etc.) */
          MCG_C6 = CPU_ClockConfigDescriptors[ConfigID].GenRegs.MCG_C6_value; /* Set C6 (PLL select, VCO divider etc.) */
        } else {
          MCG_C5 = NextModeRegs.MCG_C5_value; /* Set C5 (PLL settings, PLL reference divider etc.) */
          MCG_C6 = NextModeRegs.MCG_C6_value; /* Set C6 (PLL select, VCO divider etc.) */
        }
        while((MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until PLL is locked*/
        }
        break;
      default:
        break;            
    }
    switch (NextMode) {
      case CPU_MCG_MODE_FEI:
      case CPU_MCG_MODE_FEE:
        while((MCG_S & 0x0CU) != 0x00U) { /* Wait until output of the FLL is selected */
        }
        break;
      case CPU_MCG_MODE_FBI:
      case CPU_MCG_MODE_BLPI:
        while((MCG_S & 0x0CU) != 0x04U) { /* Wait until internal reference clock is selected as MCG output */
        }
        break;
      case CPU_MCG_MODE_FBE:
      case CPU_MCG_MODE_BLPE:
      case CPU_MCG_MODE_PBE:
        while((MCG_S & 0x0CU) != 0x08U) { /* Wait until external reference clock is selected as MCG output */
        }
        break;
      case CPU_MCG_MODE_PEE:
        while((MCG_S & 0x0CU) != 0x0CU) { /* Wait until output of the PLL is selected */
        }
        break;
    }
  } while (NextMode != (TargetMode & CPU_MCG_MODE_INDEX_MASK)); /* Loop until the target MCG mode is set */
}

/*
** ===================================================================
**     Method      :  Cpu_SetClockConfiguration (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Calling of this method will cause the clock configuration
**         change and reconfiguration of all components according to
**         the requested clock configuration setting.
**     @param
**         ModeID          - Clock configuration identifier
**     @return
**                         - ERR_OK - OK.
**                           ERR_RANGE - Mode parameter out of range
*/
/* ===================================================================*/
#if CPU_SET_CLOCK_CONFIGURATION
LDD_TError CPU_SetClockConfiguration(LDD_TClockConfiguration ModeID)
{
  if (ModeID > (CPU_CLOCK_CONFIG_NUMBER - 1U)) {
    return ERR_RANGE;
  }
  
  if (SMC_PMSTAT == 0x04U) {           /* Test if in VLPR mode */
    /* SMC_PMCTRL: LPWUI=0,RUNM=0,??=0,STOPA=0,STOPM=0 */
    SMC_PMCTRL = (SMC_PMCTRL_RUNM(0x00) | SMC_PMCTRL_STOPM(0x00)); /* Disable very low power mode */
    while((PMC_REGSC & PMC_REGSC_REGONS_MASK) == 0x00U) { /* Wait until the regulator is in run regulation */
    }
    while(SMC_PMSTAT == 0x04U) {       /* Wait until the system is back in RUN mode */
    }
  }
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=4,OUTDIV4=4,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
                SIM_CLKDIV1_OUTDIV2(0x01) |
                SIM_CLKDIV1_OUTDIV3(0x04) |
                SIM_CLKDIV1_OUTDIV4(0x04); /* Set the system prescalers to safe value */
  switch (ModeID) {
  #if defined(CPU_CLOCK_CONFIG_0)
    case CPU_CLOCK_CONFIG_0:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_0);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_0) */
  #if defined(CPU_CLOCK_CONFIG_1)
    case CPU_CLOCK_CONFIG_1:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_1);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_1) */
  #if defined(CPU_CLOCK_CONFIG_2)
    case CPU_CLOCK_CONFIG_2:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_2);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_2) */
  #if defined(CPU_CLOCK_CONFIG_3)
    case CPU_CLOCK_CONFIG_3:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_3);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_3) */
  #if defined(CPU_CLOCK_CONFIG_4)
    case CPU_CLOCK_CONFIG_4:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_4);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_4) */
  #if defined(CPU_CLOCK_CONFIG_5)
    case CPU_CLOCK_CONFIG_5:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_5);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_5) */
  #if defined(CPU_CLOCK_CONFIG_6)
    case CPU_CLOCK_CONFIG_6:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_6);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_6) */
  #if defined(CPU_CLOCK_CONFIG_7)
    case CPU_CLOCK_CONFIG_7:
      CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_7);
      break;
  #endif /* defined(CPU_CLOCK_CONFIG_7) */
    default:
      break;
  }
  SIM_CLKDIV1 = (uint32_t)CPU_ClockConfigDescriptors[ModeID].SysRegs.SIM_CLKDIV1_value; /* Update system prescalers */
  SIM_SOPT1 = (uint32_t)((SIM_SOPT1 & (uint32_t)~(uint32_t)SIM_SOPT1_OSC32KSEL_MASK) | (uint32_t)CPU_ClockConfigDescriptors[ModeID].SysRegs.SIM_SOPT1_value); /* Update 32 kHz oscillator clock source (ERCLK32K) */
  SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)SIM_SOPT2_PLLFLLSEL_MASK) | (uint32_t)CPU_ClockConfigDescriptors[ModeID].SysRegs.SIM_SOPT2_value); /* Update PLL/FLL clock select */
  LDD_SetClockConfiguration(ModeID);   /* Call all LDD components to update the clock configuration */
  ClockConfigurationID = ModeID;       /* Store clock configuration identifier */
  if ((CPU_ClockConfigDescriptors[ClockConfigurationID].PowerMode & CPU_CLOCK_VLP_AUTO_ENABLE_MASK) != 0U) {
    /* SMC_PMCTRL: LPWUI=0,RUNM=2,??=0,STOPA=0,STOPM=0 */
    SMC_PMCTRL = (SMC_PMCTRL_RUNM(0x02) | SMC_PMCTRL_STOPM(0x00)); /* Enable very low power mode */
    if ((CPU_ClockConfigDescriptors[ClockConfigurationID].PowerMode & CPU_CLOCK_VLP_WAKEUP_MASK) != 0U) {
      /* SMC_PMCTRL: LPWUI=1 */
      SMC_PMCTRL |= SMC_PMCTRL_LPWUI_MASK; /* Enable exits to Normal RUN mode on an interrupt */
    }
    while(SMC_PMSTAT != 0x04U) {       /* Wait until in the Very Low Power run mode */
    }
  }
  return ERR_OK;
}
#endif /* CPU_SET_CLOCK_CONFIGURATION */

/*
** ===================================================================
**     Method      :  Cpu_GetClockConfiguration (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Returns the active clock configuration identifier. The
**         method is automatically enabled if more than one clock
**         configuration is enabled in the component.
**     @return
**                         - Active clock configuration identifier
*/
/* ===================================================================*/
#if CPU_GET_CLOCK_CONFIGURATION
LDD_TClockConfiguration CPU_GetClockConfiguration(void)
{
#if CPU_CLOCK_CONFIG_NUMBER > 1
  return ClockConfigurationID;         /* Return the actual clock configuration identifier */
#else
  return CPU_CLOCK_CONFIG_0;           /* Return the actual clock configuration identifier */
#endif
}
#endif /* CPU_GET_CLOCK_CONFIGURATION */

/*
** ===================================================================
**     Method      :  Cpu_SetOperationMode (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method requests to change the component's operation
**         mode (RUN, WAIT, SLEEP, STOP). The target operation mode
**         will be entered immediately. 
**         See [Operation mode settings] for further details of the
**         operation modes mapping to low power modes of the cpu.
**     @param
**         OperationMode   - Requested driver
**                           operation mode
**     @param
**         ModeChangeCallback - Callback to
**                           notify the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @param
**         ModeChangeCallbackParamPtr 
**                           - Pointer to callback parameter to notify
**                           the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_PARAM_MODE - Invalid operation mode
*/
/* ===================================================================*/
#if CPU_SET_OPERATION_MODE
LDD_TError CPU_SetOperationMode(LDD_TDriverOperationMode OperationMode, LDD_TCallback ModeChangeCallback, LDD_TCallbackParam *ModeChangeCallbackParamPtr)
{
  (void) ModeChangeCallback;           /* Parameter is not used, suppress unused argument warning */
  (void) ModeChangeCallbackParamPtr;   /* Parameter is not used, suppress unused argument warning */
  
    switch (OperationMode) {
    case DOM_RUN:
      /* SCB_SCR: SLEEPDEEP=0,SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(
                  SCB_SCR_SLEEPDEEP_MASK |
                  SCB_SCR_SLEEPONEXIT_MASK
                 );                    /* Set RUN or VLPR mode */
      if ((CPU_ClockConfigDescriptors[ClockConfigurationID].Mode & CPU_MCG_MODE_INDEX_MASK) == CPU_MCG_MODE_PEE) {
        if ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3)) { /* If in PBE mode, switch to PEE. PEE to PBE transition was caused by wakeup from low power mode. */
          /* MCG_C1: CLKS=0,IREFS=0 */
          MCG_C1 &= (uint8_t)~(uint8_t)((MCG_C1_CLKS(0x03) | MCG_C1_IREFS_MASK)); /* Switch back to the PEE mode */
          while( (MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait for PLL lock */
          }
        }
      }
      break;
    case DOM_WAIT:
      /* SCB_SCR: SLEEPDEEP=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPDEEP_MASK); /* WAIT or VLPW mode can be entered after WFI instruction call */
  #if CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT
      /* SCB_SCR: SLEEPONEXIT=1 */
      SCB_SCR |= SCB_SCR_SLEEPONEXIT_MASK; /* Enter wait state on ISR exit */
  #else /* CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT */
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK); /* Do not enter wait state on ISR exit */
  #endif /* CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT */
      PE_WFI();                        /* Enter WAIT or VLPW state */
      break;
    case DOM_SLEEP:
      /* SCB_SCR: SLEEPDEEP=1 */
      SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; /* STOP VLPS or VLLSx mode can be entered after WFI instruction call */
      /* SMC_PMCTRL: STOPM=0 */
      SMC_PMCTRL &= (uint8_t)~(uint8_t)(SMC_PMCTRL_STOPM(0x07)); /* Set normal STOP mode */
      (void)(SMC_PMCTRL == 0U);        /* Dummy read of SMC_PMCTRL to ensure the register is written before entering low power mode */
  #if CPU_LOW_POWER_SLEEP_SLEEP_ON_EXIT
      /* SCB_SCR: SLEEPONEXIT=1 */
      SCB_SCR |= SCB_SCR_SLEEPONEXIT_MASK; /* Enter stop state on ISR exit */
  #else /* CPU_LOW_POWER_SLEEP_SLEEP_ON_EXIT */
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK); /* Do not enter stop state on ISR exit */
  #endif /* CPU_LOW_POWER_SLEEP_SLEEP_ON_EXIT */
      PE_WFI();                        /* Enter STOP state */
      break;
    case DOM_STOP:
  #if CPU_LOW_POWER_STOP
      /* Clear LLWU flags */
      /* LLWU_F1: WUF7=1,WUF6=1,WUF5=1,WUF4=1,WUF3=1,WUF2=1,WUF1=1,WUF0=1 */
      LLWU_F1 = LLWU_F1_WUF7_MASK |
                LLWU_F1_WUF6_MASK |
                LLWU_F1_WUF5_MASK |
                LLWU_F1_WUF4_MASK |
                LLWU_F1_WUF3_MASK |
                LLWU_F1_WUF2_MASK |
                LLWU_F1_WUF1_MASK |
                LLWU_F1_WUF0_MASK;
      /* LLWU_F2: WUF15=1,WUF14=1,WUF13=1,WUF12=1,WUF11=1,WUF10=1,WUF9=1,WUF8=1 */
      LLWU_F2 = LLWU_F2_WUF15_MASK |
                LLWU_F2_WUF14_MASK |
                LLWU_F2_WUF13_MASK |
                LLWU_F2_WUF12_MASK |
                LLWU_F2_WUF11_MASK |
                LLWU_F2_WUF10_MASK |
                LLWU_F2_WUF9_MASK |
                LLWU_F2_WUF8_MASK;
      /* LLWU_F3: MWUF7=1,MWUF6=1,MWUF5=1,MWUF4=1,MWUF3=1,MWUF2=1,MWUF1=1,MWUF0=1 */
      LLWU_F3 = LLWU_F3_MWUF7_MASK |
                LLWU_F3_MWUF6_MASK |
                LLWU_F3_MWUF5_MASK |
                LLWU_F3_MWUF4_MASK |
                LLWU_F3_MWUF3_MASK |
                LLWU_F3_MWUF2_MASK |
                LLWU_F3_MWUF1_MASK |
                LLWU_F3_MWUF0_MASK;
      /* LLWU_FILT1: FILTF=1 */
      LLWU_FILT1 |= LLWU_FILT1_FILTF_MASK;
      /* LLWU_FILT2: FILTF=1 */
      LLWU_FILT2 |= LLWU_FILT2_FILTF_MASK;
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK); /* Do not enter stop state on ISR exit */
      /* SCB_SCR: SLEEPDEEP=1 */
      SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; /* STOP VLPS or VLLSx mode can be entered after WFI instruction call */
    #if (CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_LLS)
      /* SMC_PMCTRL: STOPM=3 */
      SMC_PMCTRL = (uint8_t)((SMC_PMCTRL & (uint8_t)~(uint8_t)(
                    SMC_PMCTRL_STOPM(0x04)
                   )) | (uint8_t)(
                    SMC_PMCTRL_STOPM(0x03)
                   ));                 /* Set Very-low-leakage mode */
    #else  
      /* SMC_PMCTRL: STOPM=4 */
      SMC_PMCTRL = (uint8_t)((SMC_PMCTRL & (uint8_t)~(uint8_t)(
                    SMC_PMCTRL_STOPM(0x03)
                   )) | (uint8_t)(
                    SMC_PMCTRL_STOPM(0x04)
                   ));                 /* Set Very-low-leakage mode */
      #if (CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS0)
        #if (CPU_LOW_POWER_STOP_POR_DETECT)
      /* SMC_VLLSCTRL: ??=0,??=0,PORPO=0,??=0,??=0,VLLSM=0 */
      SMC_VLLSCTRL = SMC_VLLSCTRL_VLLSM(0x00); /* Set VLLS0 mode with POR detect enabled */
        #else /* CPU_LOW_POWER_STOP_POR_DETECT */
      /* SMC_VLLSCTRL: ??=0,??=0,PORPO=1,??=0,??=0,VLLSM=0 */
      SMC_VLLSCTRL = (SMC_VLLSCTRL_PORPO_MASK | SMC_VLLSCTRL_VLLSM(0x00)); /* Set VLLS0 mode with POR detect disabled */
        #endif /* CPU_LOW_POWER_STOP_POR_DETECT */
      #elif (CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS3)
      /* SMC_VLLSCTRL: ??=0,??=0,PORPO=0,??=0,??=0,VLLSM=3 */
      SMC_VLLSCTRL = SMC_VLLSCTRL_VLLSM(0x03); /* Set VLLS3 mode */
      #elif (CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS2)
      /* SMC_VLLSCTRL: ??=0,??=0,PORPO=0,??=0,??=0,VLLSM=2 */
      SMC_VLLSCTRL = SMC_VLLSCTRL_VLLSM(0x02); /* Set VLLS2 mode */
      #elif (CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS1)
      /* SMC_VLLSCTRL: ??=0,??=0,PORPO=0,??=0,??=0,VLLSM=1 */
      SMC_VLLSCTRL = SMC_VLLSCTRL_VLLSM(0x01); /* Set VLLS1 mode */
      #else /* CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS3 */
            #error Unsupported STOP low power mode
      #endif /* CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_VLLS3 */
    #endif /* CPU_LOW_POWER_STOP == CPU_LOW_POWER_STOP_LLS */
      (void)(SMC_PMCTRL == 0U);        /* Dummy read of SMC_PMCTRL to ensure the register is written before entering low power mode */
      PE_WFI();                        /* Enter STOP state */
  #endif /* CPU_LOW_POWER_STOP */
      break;
    default:
      return ERR_PARAM_MODE;
  }
  return ERR_OK;
}
#endif /* CPU_SET_OPERATION_MODE */

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Enables all maskable interrupts.
*/
/* ===================================================================*/
#if CPU_ENABLE_INT
void CPU_EnableInt(void)
{
 __EI();
}
#endif /* CPU_ENABLE_INT */

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Disables all maskable interrupts.
*/
/* ===================================================================*/
#if CPU_DISABLE_INT
void CPU_DisableInt(void)
{
 __DI();
}
#endif /* CPU_DISABLE_INT */

/*
** ===================================================================
**     Method      :  Cpu_MCGAutoTrim (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method uses MCG auto trim feature to trim internal
**         reference clock. This method can be used only in a clock
**         configuration which derives its bus clock from external
**         reference clock ([MCG mode] must be one of the following
**         modes - FEE, FBE, BLPE, PEE, PBE) and if value of [Bus clock]
**         is in the range <8; 16>MHz.
**         The slow internal reference clock is trimmed to the value
**         selected by [Slow internal reference clock [kHz]] property. 
**         The fast internal reference clock will be trimmed to value
**         4MHz.
**     @param
**         ClockSelect     - Selects which internal
**                           reference clock will be trimmed.
**                           0 ... slow (32kHz) internal reference clock
**                           will be trimmed
**                           > 0 ... fast (4MHz) internal reference
**                           clock will be trimmed
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_SPEED - The method does not work in the
**                           active clock configuration.
**                           ERR_FAILED - Autotrim process failed.
*/
/* ===================================================================*/
#if CPU_MCG_AUTO_TRIM
LDD_TError CPU_MCGAutoTrim(uint8_t ClockSelect)
{
  uint16_t CompareValue;               /* Autotrim compare value expected count */
  uint16_t BusClockMHz = (uint16_t)((uint32_t)(CPU_ClockConfigDescriptors[ClockConfigurationID].BusClock) /1000000UL); /* Bus clock in MHz */

  /* Calculate compare value */
  if (((CPU_ClockConfigDescriptors[ClockConfigurationID].Mode & (CPU_CLOCK_EXTERNAL_CLOCK_MASK | CPU_CLOCK_EXTERNAL_CRYSTAL_MASK)) != 0) && (BusClockMHz >= 8U) && (BusClockMHz <= 16U)) {
    if (ClockSelect == 0x00U) {
      CompareValue = (uint16_t)(21000 * BusClockMHz / CPU_INT_SLOW_CLK_HZ); /* Slow internal reference clock */
    } else {
      CompareValue = (uint16_t)(672U * BusClockMHz); /* Fast internal reference clock */
    }
  } else {
    return ERR_SPEED;                  /* MCU has to be clocked from external clock and has to have bus clock in allowed range */
  }
  MCG_ATCVH = (uint8_t)(CompareValue >> 8U); /* Set compare value high half */
  MCG_ATCVL = (uint8_t)(CompareValue & 255U); /* Set compare value low half */
  if (ClockSelect == 0x00U) {
    /* MCG_SC: ATME=1,ATMS=0,LOCS0=0 */
    MCG_SC = (uint8_t)((MCG_SC & (uint8_t)~(uint8_t)(
              MCG_SC_ATMS_MASK |
              MCG_SC_LOCS0_MASK
             )) | (uint8_t)(
              MCG_SC_ATME_MASK
             ));                       /* Start trimming of the slow internal reference clock */
  } else {
    /* MCG_SC: ATME=1,ATMS=1,LOCS0=0 */
    MCG_SC = (uint8_t)((MCG_SC & (uint8_t)~(uint8_t)(
              MCG_SC_LOCS0_MASK
             )) | (uint8_t)(
              MCG_SC_ATME_MASK |
              MCG_SC_ATMS_MASK
             ));                       /* Start trimming of the fast internal reference clock */
  }
  while ((MCG_SC & MCG_SC_ATME_MASK) != 0x00U) { /* Wait until autotrim completes */
  }
  if ((MCG_SC & MCG_SC_ATMF_MASK) == 0x00U) {
    return ERR_OK;                     /* Trim operation completed successfully */
  } else {
    return ERR_FAILED;                 /* Trim operation failed */
  }
}
#endif /* CPU_MCG_AUTO_TRIM */

/*
** ===================================================================
**     Method      :  Cpu_VLPModeEnable (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method enables Very Low Power (VLP) mode in the active
**         clock configuration. To enable the VLP mode the active clock
**         configuration has to have the [Very low power mode] property
**         enabled. The method waits until the entry to the VLP mode is
**         confirmed by a power management module status register.
**         This method can be enabled only when one of the clock
**         configurations modes have the [Very low power mode] property
**         enabled.
**     @return
**                         - Error code 
**                           ERR_OK - OK
**                           ERR_SPEED - the Very Low Power mode is not
**                           supported in the active clock configuration.
*/
/* ===================================================================*/
#if CPU_VLP_MODE_ENABLE
LDD_TError CPU_VLPModeEnable(void)
{
  if ((CPU_ClockConfigDescriptors[ClockConfigurationID].PowerMode & CPU_CLOCK_VLP_ENABLE_MASK) == 0U) {
    return ERR_SPEED;                  /* Very low power mode not enabled in the active clock configuration. */
  }
  if (SMC_PMSTAT == 0x04U) {           /* If the system is already in VLP mode, return */
    return ERR_OK;
  }
  /* SMC_PMCTRL: LPWUI=0,RUNM=2,??=0,STOPA=0,STOPM=0 */
  SMC_PMCTRL = (SMC_PMCTRL_RUNM(0x02) | SMC_PMCTRL_STOPM(0x00)); /* Enable very low power mode */
  if ((CPU_ClockConfigDescriptors[ClockConfigurationID].PowerMode & CPU_CLOCK_VLP_WAKEUP_MASK) == 0U) {
    /* SMC_PMCTRL: LPWUI=1 */
    SMC_PMCTRL |= SMC_PMCTRL_LPWUI_MASK; /* Enable exits to Normal RUN mode on an interrupt */
  }
  while(SMC_PMSTAT != 0x04U) {         /* Wait until in the Very Low Power run mode */
  }
  return ERR_OK;
}
#endif /* CPU_VLP_MODE_ENABLE */

/*
** ===================================================================
**     Method      :  Cpu_VLPModeDisable (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method disables the Very Low Power (VLP) mode in the
**         active clock configuration. The method waits until the exit
**         of the VLP mode is confirmed by a power management module
**         status register.
**         This method can be enabled only when one of the clock
**         configurations have the [Very low power mode] property
**         enabled.
**     @return
**                         - Error code 
**                           ERR_OK - OK
**                           ERR_SPEED - the Very Low Power mode is not
**                           supported in the active clock configuration.
*/
/* ===================================================================*/
#if CPU_VLP_MODE_DISABLE
LDD_TError CPU_VLPModeDisable(void)
{
  if ((CPU_ClockConfigDescriptors[ClockConfigurationID].PowerMode & CPU_CLOCK_VLP_ENABLE_MASK) == 0U) {
    return ERR_SPEED;                  /* Very low power mode not enabled in the active clock configuration. */
  }
  if (SMC_PMSTAT == 0x04U) {           /* Test if in VLPR mode */
    /* SMC_PMCTRL: LPWUI=0,RUNM=0,??=0,STOPA=0,STOPM=0 */
    SMC_PMCTRL = (SMC_PMCTRL_RUNM(0x00) | SMC_PMCTRL_STOPM(0x00)); /* Disable very low power mode */
    while((PMC_REGSC & PMC_REGSC_REGONS_MASK) == 0x00U) { /* Wait until the regulator is in run regulation */
    }
    while(SMC_PMSTAT == 0x04U) {       /* Wait until the system is back in RUN mode */
    }
  }
  return ERR_OK;
}
#endif /* CPU_VLP_MODE_DISABLE */

/*
** ===================================================================
**     Method      :  Cpu_SystemReset (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method initiates a system reset request to reset the
**         CPU.
*/
/* ===================================================================*/
#if CPU_SYSTEM_RESET
void CPU_SystemReset(void)
{
  /* SCB_AIRCR: VECTKEY=0x05FA,SYSRESETREQ=1 */
  SCB_AIRCR = (uint32_t)((SCB_AIRCR & (uint32_t)~(uint32_t)(
               SCB_AIRCR_VECTKEY(0xFA05)
              )) | (uint32_t)(
               SCB_AIRCR_VECTKEY(0x05FA) |
               SCB_AIRCR_SYSRESETREQ_MASK
              ));                      /* Request system reset */
  while(1) {                           /* Wait until reset */
  }
}
#endif /* CPU_SYSTEM_RESET */


#ifdef __cplusplus
}
#endif

/* END CPU_Init.c */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file is a part of Processor Expert static initialization
**     library for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
