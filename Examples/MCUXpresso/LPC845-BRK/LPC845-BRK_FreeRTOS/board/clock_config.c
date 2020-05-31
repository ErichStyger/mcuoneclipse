/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * How to set up clock using clock driver functions:
 *
 * 1. Setup clock sources.
 *
 * 2. Set up all dividers.
 *
 * 3. Set up all selectors to provide selected clocks.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v5.0
processor: LPC845
package_id: LPC845M301JBD48
mcu_data: ksdk2_0
processor_version: 5.0.0
board: LPC845BREAKOUT
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "fsl_power.h"
#include "fsl_clock.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockFRO18M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO18M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO18M
called_from_default_init: true
outputs:
- {id: FROHF_clock.outFreq, value: 18 MHz}
- {id: System_clock.outFreq, value: 18 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
- {id: SYSCON.SCTCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON_PDRUNCFG0_PDEN_PLL_CFG, value: Power_down}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 18 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
void BOARD_BootClockFRO18M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut18M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO18M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO24M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO24M
outputs:
- {id: FROHF_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 24 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
- {id: SYSCON.SCTCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON_PDRUNCFG0_PDEN_PLL_CFG, value: Power_down}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 24 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
void BOARD_BootClockFRO24M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut24M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO24M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO30M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO30M
outputs:
- {id: FROHF_clock.outFreq, value: 30 MHz}
- {id: System_clock.outFreq, value: 30 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
- {id: SYSCON.SCTCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON_PDRUNCFG0_PDEN_PLL_CFG, value: Power_down}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
void BOARD_BootClockFRO30M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO30M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPll24M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockPll24M
outputs:
- {id: FROHF_clock.outFreq, value: 24 MHz}
- {id: SYSPLL_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 24 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
- {id: SYSCON.MAINCLKPLLSEL.sel, value: SYSCON.PLL}
- {id: SYSCON.SCTCLKSEL.sel, value: NO_CLOCK}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 24 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockPll24M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockPll24M configuration
 ******************************************************************************/
void BOARD_BootClockPll24M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut24M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    clock_sys_pll_t config;
    config.src        = kCLOCK_SysPllSrcFRO;      /*!< select FRO for SYSPLL */
    config.targetFreq = 24000000U;                /*!< set pll target freq */
    CLOCK_InitSystemPll(&config);                 /*!< set parameters */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); /*!< select syspll for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKPLL24M_CORE_CLOCK;
}
