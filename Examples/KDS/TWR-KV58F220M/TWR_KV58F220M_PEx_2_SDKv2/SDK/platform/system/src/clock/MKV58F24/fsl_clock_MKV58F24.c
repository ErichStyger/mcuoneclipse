/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_mcg_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_osc_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_mcg_hal_modes.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

uint32_t g_enet1588ClkInFreq[ENET_EXT_CLK_COUNT];  /* ENET_1588_CLKIN  */
uint32_t g_ftmClkFreq[FTM_EXT_CLK_COUNT];          /* FTM_CLK0         */

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetSimConfigration
 * Description   : This funtion sets the SIM registers for clock transitiom.
 *
 *END**************************************************************************/
void CLOCK_SYS_SetSimConfigration(sim_config_t const *simConfig)
{
    CLOCK_HAL_SetOutDiv(SIM,
                        simConfig->outdiv1,
                        simConfig->outdiv2,
                        simConfig->outdiv3,
                        simConfig->outdiv4);

    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, simConfig->er32kSrc);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetDmaFreq
 * Description   : Gets the clock frequency for DMA module
 * This function gets the clock frequency for DMA module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetDmaFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kSystemClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetDmamuxFreq
 * Description   : Gets the clock frequency for DMAMUX module
 * This function gets the clock frequency for DMAMUX module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetDmamuxFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPortFreq
 * Description   : Gets the clock frequency for PORT module
 * This function gets the clock frequency for PORT module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPortFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kLpoClock, &freq);
    return freq;
}
/* PORT instance table. */
static const sim_clock_gate_name_t portGateTable[] =
{
    kSimClockGatePortA,
    kSimClockGatePortB,
    kSimClockGatePortC,
    kSimClockGatePortD,
    kSimClockGatePortE
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnablePortClock
 * Description   : Enable the clock for PORT module
 * This function enables the clock for PORT module
 *
 *END**************************************************************************/
void CLOCK_SYS_EnablePortClock(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    SIM_HAL_EnableClock(SIM, portGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisablePortClock
 * Description   : Disable the clock for PORT module
 * This function disables the clock for PORT module
 *
 *END**************************************************************************/
void CLOCK_SYS_DisablePortClock(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    SIM_HAL_DisableClock(SIM, portGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPortGateCmd
 * Description   : Get the the clock gate state for PORT module
 * This function will get the clock gate state for PORT module.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetPortGateCmd(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, portGateTable[instance]);
}

/* HSADC instance table. */
static const sim_clock_gate_name_t hsadcGateTable[] =
{
    kSimClockGateHsadc0,
    kSimClockGateHsadc1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableHSAdcClock
 * Description   : Enable the clock for HSADC module
 * This function enables the clock for HSADC module
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableHSAdcClock(uint32_t instance)
{
    assert(instance < sizeof(hsadcGateTable)/sizeof(hsadcGateTable[0]));

    SIM_HAL_EnableClock(SIM, hsadcGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableHSAdcClock
 * Description   : Disable the clock for HSADC module
 * This function disables the clock for HSADC module
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableHSAdcClock(uint32_t instance)
{
    assert(instance < sizeof(hsadcGateTable)/sizeof(hsadcGateTable[0]));

    SIM_HAL_DisableClock(SIM, hsadcGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetConfiguration
 * Description   : This funtion sets the system to target configuration, it
 * only sets the clock modules registers for clock mode change, but not send
 * notifications to drivers.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const* config)
{
    assert(NULL != config);

    /* Set outdiv for safe output clock frequency. */
    CLOCK_HAL_SetOutDiv(SIM, 0U, 1U, 7U, 7U);

    /* Set MCG mode. */
    CLOCK_SYS_SetMcgMode(&config->mcgConfig);

    /* Set SIM setting. */
    CLOCK_SYS_SetSimConfigration(&config->simConfig);

    /* Set OSCERCLK setting. */
    CLOCK_SYS_SetOscerConfigration(0, &config->oscerConfig);
    SystemCoreClock = CLOCK_SYS_GetCoreClockFreq();

    return kClockManagerSuccess;
}

clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                 uint32_t *frequency)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    switch (clockName)
    {
        case kCoreClock:
        case kSystemClock:
            *frequency = CLOCK_SYS_GetCoreClockFreq();
            break;
        case kPlatformClock:
            *frequency = CLOCK_SYS_GetSystemClockFreq();
            break;
        case kBusClock:
            *frequency = CLOCK_SYS_GetBusClockFreq();
            break;
        case kFlexBusClock:
            *frequency = CLOCK_SYS_GetFlexbusFreq();
            break;
        case kFlashClock:
            *frequency = CLOCK_SYS_GetFlashClockFreq();
            break;
        case kFastPeripheralClock:
            *frequency = CLOCK_SYS_GetFastPeripheralClockFreq();
        break;    
        case kOsc0ErClock:
            *frequency = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kOsc0ErClockUndiv:
            *frequency = CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq();
            break;
        case kMcgFfClock:
            *frequency = CLOCK_SYS_GetFixedFreqClockFreq();
            break;
        case kMcgFllClock:
            *frequency = CLOCK_HAL_GetFllClk(MCG);
            break;
        case kMcgPll0Clock:
            *frequency = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kMcgOutClock:
            *frequency = CLOCK_HAL_GetOutClk(MCG);
            break;
        case kMcgIrClock:
            *frequency = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
#if FSL_FEATURE_MCG_HAS_IRC_48M            
        case kIrc48mClock:
            *frequency = CPU_INTERNAL_IRC_48M; 
            break;
#endif            
        case kLpoClock:
            *frequency = CLOCK_SYS_GetLpoClockFreq();
            break;
        case kSystickClock:
            *frequency = CLOCK_SYS_GetSystickFreq();
            break;
        default:
            *frequency = 0U;
            returnCode = kClockManagerNoSuchClockName;
            break;
    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlexbusFreq
 * Description   : Gets the clock frequency for FLEXBUS module
 * This function gets the clock frequency for FLEXBUS module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlexbusFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv3(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlashClockFreq
 * Description   : Gets the flash clock frequency.
 * This function gets the flash clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlashClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv4(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCoreClockFreq
 * Description   : Gets the core clock frequency.
 * This function gets the core clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetCoreClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv1(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSystemClockFreq
 * Description   : Gets the systen clock frequency.
 * This function gets the systen clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSystemClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv1(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFastPeripheralClockFreq
 * Description   : Gets the fast peripheral clock frequency.
 * This function gets the fast peripheral clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFastPeripheralClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv2(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPllFllClockFreq
 * Description   : Gets the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPllFllClockFreq(void)
{
    uint32_t freq;
    clock_pllfll_sel_t src;

    src = CLOCK_HAL_GetPllfllSel(SIM);

    switch (src)
    {
        case kClockPllFllSelFll:
            freq = CLOCK_HAL_GetFllClk(MCG);
            break;
        case kClockPllFllSelPll:
            freq = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetBusClockFreq
 * Description   : Gets the bus clock frequency.
 * This function gets the bus clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetBusClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv4(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetExternalRefClockFreq
 * Description   : Gets the ERCLK32K clock frequency.
 * This function gets the external reference (ERCLK32K) clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetExternalRefClock32kFreq(void)
{
    clock_er32k_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetExternalRefClock32kSrc(SIM);

    switch (src)
    {
        case kClockEr32kSrcOsc0:      /* OSC 32k clock  */
            freq = (32768U == g_xtal0ClkFreq) ? 32768U : 0U;
            break;
        case kClockEr32kSrcLpo:         /* LPO clock      */
            freq = CLOCK_SYS_GetLpoClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetOsc0ExternalRefClockFreq
 * Description   : Gets OSC0ERCLK.
 * This function gets the OSC0 external reference frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockFreq(void)
{
    return CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq()
        >> OSC_HAL_GetExternalRefClkDiv(g_oscBase[0]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq
 * Description   : Gets OSC0ERCLKUDIV.
 * This function gets the OSC0 external reference undivided frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq(void)
{
    if (OSC_HAL_GetExternalRefClkCmd(g_oscBase[0]))
    {
        return g_xtal0ClkFreq;
    }
    else
    {
        return 0U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetHsadcAltFreq
 * Description   : Gets the HSADC alternate clock frequency.
 * This function gets the HSADC alternate clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetHsadcAltFreq(uint32_t instance)
{
    return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLptmrFreq
 * Description   : Gets LPTMRx prescaler/glitch filter clock frequency.
 * This function gets the LPTMRx prescaler/glitch filter clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetLptmrFreq(uint32_t instance, clock_lptmr_src_t lptmrSrc)
{
    uint32_t freq;

    switch (lptmrSrc)
    {
        case kClockLptmrSrcMcgIrClk:        /* MCG out clock  */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kClockLptmrSrcLpoClk:             /* LPO clock     */
            freq = CLOCK_SYS_GetLpoClockFreq();
            break;
        case kClockLptmrSrcEr32kClk:        /* ERCLK32K clock */
            freq = CLOCK_SYS_GetExternalRefClock32kFreq();
            break;
        case kClockLptmrSrcOsc0erClkUndiv:        /* OSCERCLK_UNDIV clock */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEwmFreq
 * Description   : Gets the clock frequency for Ewm module
 * This function gets the clock frequency for Ewm module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEwmFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kLpoClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFtfFreq
 * Description   : Gets the clock frequency for FTF module. (Flash Memory)
 * This function gets the clock frequency for FTF module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFtfFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFlashClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCrcFreq
 * Description   : Gets the clock frequency for CRC module
 * This function gets the clock frequency for CRC module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetCrcFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kSystemClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetAdcFreq
 * Description   : Gets the clock frequency for ADC module
 * This function gets the clock frequency for ADC module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetAdcFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kMcgIrClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCmpFreq
 * Description   : Gets the clock frequency for CMP module
 * This function gets the clock frequency for CMP module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetCmpFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPdbFreq
 * Description   : Gets the clock frequency for PDB module
 * This function gets the clock frequency for PDB module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPdbFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPwmFreq
 * Description   : Gets the clock frequency for eFlexPWM module
 * This function gets the clock frequency for eFlexPWM module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPwmFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFtmExternalFreq
 * Description   : Gets FTM external clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFtmExternalFreq(uint32_t instance)
{
    sim_ftm_clk_sel_t sel = SIM_HAL_GetFtmExternalClkPinMode(SIM, instance);

    if (kSimFtmClkSel0 == sel)
    {
        return g_ftmClkFreq[0];
    }
    else
    {
        return g_ftmClkFreq[1];
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPitFreq
 * Description   : Gets the clock frequency for Pit module. 
 * This function gets the clock frequency for Pit module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPitFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSpiFreq
 * Description   : Gets the clock frequency for SPI module. 
 * This function gets the clock frequency for SPI module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSpiFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetI2cFreq
 * Description   : Gets the clock frequency for I2C module. 
 * This function gets the clock frequency for I2C module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetI2cFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetUartFreq
 * Description   : Gets the clock frequency for UART module. 
 * This function gets the clock frequency for UART module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetUartFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEnetRmiiFreq
 * Description   : Gets the clock frequency for ENET module RMII clock.
 * This function gets the clock frequency for ENET module RMII clock.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEnetRmiiFreq(uint32_t instance)
{
    /* get the sim clock source setting*/
    if (CLOCK_HAL_GetRmiiSrc(SIM, instance) == kClockRmiiSrcExtalClk)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();   /* OSCERCLK */
    }
    else
    {
        return g_enet1588ClkInFreq[0];      /* ENET_1588_CLKIN */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEnetTimeStampFreq
 * Description   : Gets the clock frequency for ENET module TIME clock.
 * This function gets the clock frequency for ENET module TIME clock.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEnetTimeStampFreq(uint32_t instance)
{
    uint32_t freq;
    clock_time_src_t src;

    src = CLOCK_HAL_GetTimeSrc(SIM, instance);

    switch(src)
    {
        case kClockTimeSrcCoreSysClk: /* Core/System clock. */
            freq = CLOCK_SYS_GetCoreClockFreq();
            break;
        case kClockTimeSrcPllFllSel:  /* FLL/PLL/IRC48M. */
            freq = CLOCK_SYS_GetPllFllClockFreq();
            break;
        case kClockTimeSrcOsc0erClk:   /* OSCERCLK. */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockTimeSrcExt:        /* ENET 1588 clock in. */
            freq = g_enet1588ClkInFreq[0];
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetGpioFreq
 * Description   : Gets the clock frequency for GPIO module. 
 * This function gets the clock frequency for GPIO module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetGpioFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kSystemClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEncFreq
 * Description   : Gets the clock frequency for ENC module. 
 * This function gets the clock frequency for ENC module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEncFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetWdogFreq
 * Description   : Gets watch dog clock frequency.
 * This function gets the watch dog clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetWdogFreq(uint32_t instance, clock_wdog_src_t wdogSrc)
{
    if (kClockWdogSrcLpoClk == wdogSrc)
    {
        return CLOCK_SYS_GetLpoClockFreq();
    }
    else
    {
        return CLOCK_SYS_GetBusClockFreq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetXbarFreq
 * Description   : Gets the clock frequency for XBAR module. 
 * This function gets the clock frequency for XBAR module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetXbarFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetAoiFreq
 * Description   : Gets the clock frequency for AOI module. 
 * This function gets the clock frequency for AOI module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetAoiFreq(uint32_t instance)
{
    uint32_t freq = 0;
    CLOCK_SYS_GetFreq(kBusClock, &freq);
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlexcanFreq
 * Description   : Gets FLEXCAN clock frequency.
 * This function gets the FLEXCAN clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlexcanFreq(uint8_t instance, clock_flexcan_src_t flexcanSrc)
{
    uint32_t freq = 0;
    if (kClockFlexcanSrcOsc0erClk == flexcanSrc)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
    }
    else
    { 
        CLOCK_SYS_GetFreq(kFastPeripheralClock, &freq);
        return freq;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
