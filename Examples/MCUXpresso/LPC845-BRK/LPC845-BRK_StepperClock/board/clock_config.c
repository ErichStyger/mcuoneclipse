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
product: Clocks v8.0
processor: LPC845
package_id: LPC845M301JBD48
mcu_data: ksdk2_0
processor_version: 10.0.0
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
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: FROHF_clock.outFreq, value: 30 MHz}
- {id: LowPower_clock.outFreq, value: 10 kHz}
- {id: SYSPLL_clock.outFreq, value: 15 MHz}
- {id: System_clock.outFreq, value: 15 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                   /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                      /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);                    /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcLpwrBootValue);                    /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);                  /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);                     /*!<select external clock source to sys_osc */
    clock_sys_pll_t config;
    config.src = kCLOCK_SysPllSrcFRO;                   /*!< select FRO for SYSPLL */
    config.targetFreq = 15000000U;                     /*!< set pll target freq */
    CLOCK_InitSystemPll(&config);                           /*!< set parameters */
    CLOCK_Select(kFRG0_Clk_From_Fro);                     /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(15000000U);                     /*!< select frg0 freq */
    CLOCK_Select(kFRG1_Clk_From_Fro);                     /*!< select fro for frg1 */
    CLOCK_SetFRG1ClkFreq(15000000U);                     /*!< select frg1 freq */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);            /*!< select fro for main clock */
    CLOCK_Select(kCLKOUT_From_Fro);                         /*!< select FRO for CLKOUT */
    CLOCK_Select(kSCT_Clk_From_Fro);                        /*!< select FRO for SCT */
    CLOCK_Select(kADC_Clk_From_Fro);                       /*!< select FRO for ADC */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

