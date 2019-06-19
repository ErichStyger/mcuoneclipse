/** ###################################################################
**      Filename    : CPU_Init.c
**      Processor   : MKE06Z128VLK4
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
#include "MKE06Z4.h"
#include "Init_Config.h"
#include "Peripherals_Init.h"
#include "CPU_Init.h"
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

#if CPU_COMMON_INIT
extern void Common_Init(void);         /* Forward declaration of generated common initialization in generated CPU module */
#endif /* CPU_COMMON_INIT */
#if CPU_COMPONENTS_INIT
extern void Components_Init(void);     /* Forward declaration of generated LDD components initialization in generated CPU module */
#endif /* CPU_COMPONENTS_INIT */
#if CPU_SET_CLOCK_CONFIGURATION
extern void LDD_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration); 
#endif /* CPU_SET_CLOCK_CONFIGURATION */
  
/* Global variables */

volatile uint8_t SR_reg;               /* Current value of the FAULTMASK register */
volatile uint8_t SR_lock = 0x00U;      /* Lock */
LDD_TClockConfiguration ClockConfigurationID = CPU_CLOCK_CONFIG_0; /* Active clock configuration */

static const CPU_TClockGenMode ClockGenModeMatrix[6][6] = {
/* This matrix defines which mode is next in the ICS Mode state diagram in transitioning from the
   current mode to a target mode*/
  { CPU_ICS_MODE_FEI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FEE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE  }, /* FEI */
  { CPU_ICS_MODE_FEI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBILP, CPU_ICS_MODE_FEE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE  }, /* FBI */
  { CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBILP, CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI  }, /* FBILP */
  { CPU_ICS_MODE_FEI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FEE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE  }, /* FEE */
  { CPU_ICS_MODE_FEI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FBI,  CPU_ICS_MODE_FEE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBELP}, /* FBE */
  { CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBE,  CPU_ICS_MODE_FBELP}  /* FBELP */
};

static const CPU_TClockConfigDescriptor CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_NUMBER] = {
  #if defined(CPU_CLOCK_CONFIG_0)
  /* Clock configuration 0 */
  {
    CPU_ICS_MODE_CONFIG_0,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_0,CPU_ICS_C2_CONFIG_0,CPU_ICS_C4_CONFIG_0,CPU_ICS_S_CONFIG_0,CPU_OSC_CR_CONFIG_0
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_0,
    },
    CPU_BUS_CLK_HZ_CONFIG_0            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_1)
  /* Clock configuration 1 */
  ,{
    CPU_ICS_MODE_CONFIG_1,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_1,CPU_ICS_C2_CONFIG_1,CPU_ICS_C4_CONFIG_1,CPU_ICS_S_CONFIG_1,CPU_OSC_CR_CONFIG_1
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_1,
    },
    CPU_BUS_CLK_HZ_CONFIG_1            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_2)
  /* Clock configuration 2 */
  ,{
    CPU_ICS_MODE_CONFIG_2,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_2,CPU_ICS_C2_CONFIG_2,CPU_ICS_C4_CONFIG_2,CPU_ICS_S_CONFIG_2,CPU_OSC_CR_CONFIG_2
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_2,
    },
    CPU_BUS_CLK_HZ_CONFIG_2            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_3)
  /* Clock configuration 3 */
  ,{
    CPU_ICS_MODE_CONFIG_3,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_3,CPU_ICS_C2_CONFIG_3,CPU_ICS_C4_CONFIG_3,CPU_ICS_S_CONFIG_3,CPU_OSC_CR_CONFIG_3
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_3,
    },
    CPU_BUS_CLK_HZ_CONFIG_3            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_4)
  /* Clock configuration 4 */
  ,{
    CPU_ICS_MODE_CONFIG_4,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_4,CPU_ICS_C2_CONFIG_4,CPU_ICS_C4_CONFIG_4,CPU_ICS_S_CONFIG_4,CPU_OSC_CR_CONFIG_4
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_4,
    },
    CPU_BUS_CLK_HZ_CONFIG_4            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_5)
  /* Clock configuration 5 */
  ,{
    CPU_ICS_MODE_CONFIG_5,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_5,CPU_ICS_C2_CONFIG_5,CPU_ICS_C4_CONFIG_5,CPU_ICS_S_CONFIG_5,CPU_OSC_CR_CONFIG_5
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_5,
    },
    CPU_BUS_CLK_HZ_CONFIG_5            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_6)
  /* Clock configuration 6 */
  ,{
    CPU_ICS_MODE_CONFIG_6,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_6,CPU_ICS_C2_CONFIG_6,CPU_ICS_C4_CONFIG_6,CPU_ICS_S_CONFIG_6,CPU_OSC_CR_CONFIG_6
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_6,
    },
    CPU_BUS_CLK_HZ_CONFIG_6            /* Bus frequency */
  }
  #endif
  #if defined(CPU_CLOCK_CONFIG_7)
  /* Clock configuration 7 */
  ,{
    CPU_ICS_MODE_CONFIG_7,             /* Clock generator mode */
    {                                  /* ICS registers */
      CPU_ICS_C1_CONFIG_7,CPU_ICS_C2_CONFIG_7,CPU_ICS_C4_CONFIG_7,CPU_ICS_S_CONFIG_7,CPU_OSC_CR_CONFIG_7
    },
    {                                  /* SIM registers */
      CPU_SIM_CLKDIV_CONFIG_7,
    },
    CPU_BUS_CLK_HZ_CONFIG_7            /* Bus frequency */
  }
  #endif
};

static const CPU_TClockGenRegs CPU_DefaultFEI = {
  CPU_DEFAULT_FEI_ICS_C1,CPU_DEFAULT_FEI_ICS_C2,CPU_DEFAULT_FEI_ICS_C4,CPU_DEFAULT_FEI_ICS_S,CPU_DEFAULT_FEI_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBI = {
  CPU_DEFAULT_FBI_ICS_C1,CPU_DEFAULT_FBI_ICS_C2,CPU_DEFAULT_FBI_ICS_C4,CPU_DEFAULT_FBI_ICS_S,CPU_DEFAULT_FBI_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBILP = {
  CPU_DEFAULT_FBILP_ICS_C1,CPU_DEFAULT_FBILP_ICS_C2,CPU_DEFAULT_FBILP_ICS_C4,CPU_DEFAULT_FBILP_ICS_S,CPU_DEFAULT_FBILP_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFEE = {
  CPU_DEFAULT_FEE_ICS_C1,CPU_DEFAULT_FEE_ICS_C2,CPU_DEFAULT_FEE_ICS_C4,CPU_DEFAULT_FEE_ICS_S,CPU_DEFAULT_FEE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBE = {
  CPU_DEFAULT_FBE_ICS_C1,CPU_DEFAULT_FBE_ICS_C2,CPU_DEFAULT_FBE_ICS_C4,CPU_DEFAULT_FBE_ICS_S,CPU_DEFAULT_FBE_OSC_CR
};
static const CPU_TClockGenRegs CPU_DefaultFBELP = {
  CPU_DEFAULT_FBELP_ICS_C1,CPU_DEFAULT_FBELP_ICS_C2,CPU_DEFAULT_FBELP_ICS_C4,CPU_DEFAULT_FBELP_ICS_S,CPU_DEFAULT_FBELP_OSC_CR
};

static const CPU_TClockGenRegs *const CPU_ClockGenModeRegs[CPU_ICS_MODES] = {
  &CPU_DefaultFEI,
  &CPU_DefaultFBI,
  &CPU_DefaultFBILP,
  &CPU_DefaultFEE,
  &CPU_DefaultFBE,
  &CPU_DefaultFBELP
};


/*
** ===================================================================
**     Method      :  __init_hardware (component MKE06Z128LK4)
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
#if defined(__IAR_SYSTEMS_ICC__)
int __low_level_init()
#elif defined(__CWCC__) | defined(__GNUC__) | defined(__CC_ARM)
void __init_hardware()
#endif
{
  /* Interrupt vector placement initialization */
  #if defined(__IAR_SYSTEMS_ICC__)
  SCB_VTOR = (uint32_t)(&__vector_table); /* Set the interrupt vector table position */
  #elif defined(__CWCC__) | defined(__GNUC__) | defined(__CC_ARM)
  SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
  #endif
  /* Disable the WDOG module */
  #if STARTUP_WDOG
  WDOG_TOVAL = (uint8_t)STARTUP_WDOG_TOVAL_VALUE; /* Disable WDOG */
  WDOG_CS2 = (uint8_t)STARTUP_WDOG_CS2_VALUE; /* Disable WDOG */
  WDOG_CS1 = (uint8_t)STARTUP_WDOG_CS1_VALUE; /* Disable WDOG */
  #endif /* STARTUP_WDOG */
    
  /* Internal reference clock trim initialization */
  #if (defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) || defined(STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS))
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS)
  if ( *((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) != 0xFFU) { /* Skip if non-volatile flash memory is erased */
    ICS_C3 = *((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS);
    #endif /* defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) */
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)
    ICS_C4 = (ICS_C4 & ~(ICS_C4_SCFTRIM_MASK)) | ((*((uint8_t*)STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS)) & ICS_C4_SCFTRIM_MASK);
    #endif /* STARTUP_CLOCK_INTERNAL_SLOW_FINE_TRIM_ADDRESS */
    #if defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS)
  }
    #endif /* defined(STARTUP_CLOCK_INTERNAL_SLOW_TRIM_ADDRESS) */
  #endif /* STARTUP_CLOCK_INTERNAL_FAST_TRIM */
  /* SIM_CLKDIV: ??=0,??=0,OUTDIV1=0,??=0,??=0,??=0,OUTDIV2=1,??=0,??=0,??=0,OUTDIV3=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV = (SIM_CLKDIV_OUTDIV1(0x00) | SIM_CLKDIV_OUTDIV2_MASK); /* Set the system prescalers to safe value */
  CPU_SetClockConfigGenMode(CPU_CLOCK_CONFIG_0);
  SIM_CLKDIV = (uint32_t)CPU_ClockConfigDescriptors[CPU_CLOCK_CONFIG_0].SysRegs.SIM_CLKDIV_value; /* Update system prescalers */
  #if defined(__IAR_SYSTEMS_ICC__)    
  return 1;
  #endif
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component MKE06Z128LK4)
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
  
  /* Debug pins port clock gate enable */
  
  #if CPU_SWD_DIO_PIN | CPU_SWD_CLK_PIN
  SIM_SCGC |= (uint32_t)SIM_SCGC_SWD_MASK; /* SWD pins clock gate enable */
  #endif /* CPU_SWD_DIO_PIN | CPU_SWD_CLK_PIN */

  /* NMI pin initialization */
    
  #if CPU_NMI_PIN
  SIM_SOPT0 |= (uint32_t)SIM_SOPT0_NMIE_MASK; /* Enable NMI pin */
  #else
  SIM_SOPT0 &= (uint32_t)~(uint32_t)SIM_SOPT0_NMIE_MASK; /* Disable NMI pin */
  #endif /* CPU_NMI_PIN */

  /* Reset pin initialization */
    
  #if CPU_RESET_PIN
  SIM_SOPT0 |= (uint32_t)SIM_SOPT0_RSTPE_MASK; /* Enable Reset pin */
  #else
  SIM_SOPT0 &= (uint32_t)~(uint32_t)SIM_SOPT0_RSTPE_MASK; /* Disable Reset pin */
  #endif /* CPU_RESET_PIN */

  /* SWD pins initialization */
    
  #if CPU_SWD_DIO_PIN | CPU_SWD_CLK_PIN
  SIM_SOPT0 |= (uint32_t)SIM_SOPT0_SWDE_MASK; /* Enable SWD pins */
  #else
  SIM_SOPT0 &= (uint32_t)~(uint32_t)SIM_SOPT0_SWDE_MASK; /* Disable SWD pins */
  #endif /* CPU_SWD_DIO_PIN | CPU_SWD_CLK_PIN */
  
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
  CPU_ON_RESET_EVENT_NAME((uint16_t)SIM_SRSID); /* Invoke an user event */
  #endif /* CPU_ON_RESET_EVENT_NAME */
  
  /* Rest of components initialization */
  
  #if CPU_COMPONENTS_INIT
  Components_Init();
  #endif /* CPU_COMPONENTS_INIT */

  /* Interrupts priority level initialization */
  
  #if CPU_INT_PRIORITY == 0
  __DI();                              /* Disable interrupts */
  #elif CPU_INT_PRIORITY == 1
  __EI();                              /* Enable interrupts */
  #else
    #error Unsupported interrupt priority level
  #endif 
}

CPU_TClockGenMode CPU_GetClockGenMode(void)
{
  switch (ICS_C1  & ICS_C1_CLKS_MASK) {
    case  0x00U:
      /* Output of FLL is selected */
      if ((ICS_C1 & ICS_C1_IREFS_MASK) == 0x00U) {
        /* External reference clock is selected */
        return CPU_ICS_MODE_FEE;
      } else {
        /* Internal reference clock is selected */
        return CPU_ICS_MODE_FEI;
      }
    case 0x40U:
      /* Internal reference clock is selected */
      if ((ICS_C2 & ICS_C2_LP_MASK) == 0x00U) {
        /* Low power mode is disabled */
        return CPU_ICS_MODE_FBI;
      } else {
        /* Low power mode is enabled */
        return CPU_ICS_MODE_FBILP;
      }
    case 0x80U:
      /* External reference clock is selected */
      if ((ICS_C2 & ICS_C2_LP_MASK) == 0x00U) {
        /* FLL is selected */
        return CPU_ICS_MODE_FBE;
      } else {
        /* Low power mode is enabled */
        return CPU_ICS_MODE_FBELP;
      }
    default:
      return (CPU_TClockGenMode)0x00U;
  }
}

void CPU_SetClockConfigGenMode(LDD_TClockConfiguration ConfigID)
{
  CPU_TClockGenMode NextMode;
  CPU_TClockGenRegs NextModeRegs;
  CPU_TClockGenMode TargetMode = CPU_ClockConfigDescriptors[ConfigID].Mode;
  
  /* External clock source pin routing */
  if ((TargetMode & (CPU_CLOCK_EXTERNAL_CLOCK_MASK | CPU_CLOCK_EXTERNAL_CRYSTAL_MASK)) != 0) { /* Is external clock source used in targeted clock configuration? */
    if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) { /* Is external crystal/resonator used in targeted clock configuration? */
      /* If yes, initialize also XTAL pin routing */
    }
  }
   
  NextMode = CPU_GetClockGenMode(); /* Identify the currently active ICS mode */
  do {
    NextMode = ClockGenModeMatrix[NextMode & CPU_ICS_MODE_INDEX_MASK][TargetMode & CPU_ICS_MODE_INDEX_MASK];
    if (NextMode == (TargetMode & CPU_ICS_MODE_INDEX_MASK)) {
      NextModeRegs = CPU_ClockConfigDescriptors[ConfigID].GenRegs;
    } else {
      NextModeRegs = *CPU_ClockGenModeRegs[NextMode & CPU_ICS_MODE_INDEX_MASK];
    }
    switch (NextMode & CPU_ICS_MODE_INDEX_MASK) {
      case CPU_ICS_MODE_FEI:
      case CPU_ICS_MODE_FBI:
        ICS_C1 = NextModeRegs.ICS_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        while((ICS_S & ICS_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
        }
        ICS_C2 = NextModeRegs.ICS_C2_value; /* Set C2 (ICS output divider, low power select) */
        ICS_C4 = ((NextModeRegs.ICS_C4_value) & (uint8_t)(~(ICS_C4_SCFTRIM_MASK))) | (ICS_C4 & (ICS_C4_SCFTRIM_MASK)); /* Set C4 (clock monitor, loss of clock interrupt, trim values not changed) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, freq. range, OCS output select) */      	
        break;
      case CPU_ICS_MODE_FBILP:
        ICS_C1 = NextModeRegs.ICS_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        while((ICS_S & ICS_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
        }
        ICS_C2 = NextModeRegs.ICS_C2_value; /* Set C2 (ICS output divider, low power select) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, freq. range, OCS output select) */
        break;
      case CPU_ICS_MODE_FEE:
      case CPU_ICS_MODE_FBE:
        ICS_C2 = NextModeRegs.ICS_C2_value; /* Set C2 (ICS output divider, low power select) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, freq. range, OCS output select) */      	
        ICS_C1 = NextModeRegs.ICS_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) {
          while((OSC_CR & OSC_CR_OSCINIT_MASK) == 0x00U) { /* Check that the oscillator is running */
          }
        }
        while((ICS_S & ICS_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
        }
        ICS_C4 = ((NextModeRegs.ICS_C4_value) & (uint8_t)(~(ICS_C4_SCFTRIM_MASK))) | (ICS_C4 & (ICS_C4_SCFTRIM_MASK)); /* Set C4 (clock monitor, loss of clock interrupt, trim values not changed) */
        break;
      case CPU_ICS_MODE_FBELP:
        ICS_C1 = NextModeRegs.ICS_C1_value; /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
        ICS_C2 = NextModeRegs.ICS_C2_value; /* Set C2 (ICS output divider, low power select) */
        OSC_CR = NextModeRegs.OSC_CR_value; /* Set OSC_CR (OSCERCLK enable, freq. range, OCS output select) */      	
        if ((TargetMode & CPU_CLOCK_EXTERNAL_CRYSTAL_MASK) != 0) {
          while((OSC_CR & OSC_CR_OSCINIT_MASK) == 0x00U) { /* Check that the oscillator is running */
          }
        }
        break;
      default:
        break;            
    }
    switch (NextMode) {
      case CPU_ICS_MODE_FEI:
      case CPU_ICS_MODE_FEE:
        while((ICS_S & 0x0CU) != 0x00U) { /* Wait until output of the FLL is selected */
        }
        break;
      case CPU_ICS_MODE_FBI:
      case CPU_ICS_MODE_FBILP:
        while((ICS_S & 0x0CU) != 0x04U) { /* Wait until internal reference clock is selected as ICS output */
        }
        break;
      case CPU_ICS_MODE_FBE:
      case CPU_ICS_MODE_FBELP:
        while((ICS_S & 0x0CU) != 0x08U) { /* Wait until external reference clock is selected as ICS output */
        }
        break;
    }
  } while (NextMode != (TargetMode & CPU_ICS_MODE_INDEX_MASK)); /* Loop until the target ICS mode is set */
}

/*
** ===================================================================
**     Method      :  Cpu_SetClockConfiguration (component MKE06Z128LK4)
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
  
  /* SIM_CLKDIV: ??=0,??=0,OUTDIV1=0,??=0,??=0,??=0,OUTDIV2=1,??=0,??=0,??=0,OUTDIV3=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV = (SIM_CLKDIV_OUTDIV1(0x00) | SIM_CLKDIV_OUTDIV2_MASK); /* Set the system prescalers to safe value */
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
  SIM_CLKDIV = (uint32_t)CPU_ClockConfigDescriptors[ModeID].SysRegs.SIM_CLKDIV_value; /* Update system prescalers */
  LDD_SetClockConfiguration(ModeID);   /* Call all LDD components to update the clock configuration */
  ClockConfigurationID = ModeID;       /* Store clock configuration identifier */
  return ERR_OK;
}
#endif /* CPU_SET_CLOCK_CONFIGURATION */

/*
** ===================================================================
**     Method      :  Cpu_GetClockConfiguration (component MKE06Z128LK4)
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
**     Method      :  Cpu_SetOperationMode (component MKE06Z128LK4)
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
                 );                    /* Set RUN mode */
      break;
    case DOM_WAIT:
      /* SCB_SCR: SLEEPDEEP=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPDEEP_MASK); /* WAIT= mode can be entered after WFI instruction call */
  #if CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT
      /* SCB_SCR: SLEEPONEXIT=1 */
      SCB_SCR |= SCB_SCR_SLEEPONEXIT_MASK; /* Enter wait state on ISR exit */
  #else /* CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT */
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK); /* Do not enter wait state on ISR exit */
  #endif /* CPU_LOW_POWER_WAIT_SLEEP_ON_EXIT */
      PE_WFI();                        /* Enter WAIT state */
      break;
    case DOM_SLEEP:
      /* SCB_SCR: SLEEPDEEP=1 */
      SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; /* STOP mode can be entered after WFI instruction call */
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
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK); /* Do not enter stop state on ISR exit */
      /* SCB_SCR: SLEEPDEEP=1 */
      SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; /* STOP mode can be entered after WFI instruction call */
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
**     Method      :  Cpu_EnableInt (component MKE06Z128LK4)
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
**     Method      :  Cpu_DisableInt (component MKE06Z128LK4)
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
**     Method      :  Cpu_SystemReset (component MKE06Z128LK4)
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