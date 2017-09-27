/*
* Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#include "fsl_mcglite_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_clock_manager.h"

/*
* README:
* This file should provide these APIs:
* 1. APIs to get the frequency of output clocks in Reference Manual ->
* Chapter Clock Distribution -> Figure Clocking diagram.
* 2. APIs for IP modules listed in Reference Manual -> Chapter Clock Distribution
* -> Module clocks.
*/

/*******************************************************************************
* Definitions
******************************************************************************/
uint32_t g_tpmClkFreq[TPM_EXT_CLK_COUNT];          /* TPM_CLK          */

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
                        0U,
                        0U,
                        simConfig->outdiv4);

    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, simConfig->er32kSrc);
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
    CLOCK_HAL_SetOutDiv(SIM, 1U, 0U, 0U, 7U);

    /* Set MCG mode. */
    CLOCK_SYS_SetMcgliteMode(&config->mcgliteConfig);

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
    case kFlashClock:
        *frequency = CLOCK_SYS_GetFlashClockFreq();
        break;
    case kOsc32kClock:
        *frequency = CLOCK_SYS_GetExternalRefClock32kFreq();
        break;
    case kOsc0ErClock:
        *frequency = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
        break;
    case kIrc48mClock:
        *frequency = kMcgliteConst48M;
        break;
    case kRtcoutClock:
        *frequency = CLOCK_SYS_GetRtcOutFreq();
        break;
    case kMcgOutClock:
        *frequency = CLOCK_HAL_GetOutClk(MCG);
        break;
    case kMcgIrClock:
        *frequency = CLOCK_HAL_GetInternalRefClk(MCG);
        break;
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
* Function Name : CLOCK_SYS_GetBusClockFreq
* Description   : Gets the bus clock frequency.
* This function gets the bus clock frequency.
*
*END**************************************************************************/
uint32_t CLOCK_SYS_GetBusClockFreq(void)
{
    return CLOCK_SYS_GetSystemClockFreq() / (CLOCK_HAL_GetOutDiv4(SIM) + 1);
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
    return CLOCK_SYS_GetSystemClockFreq() / (CLOCK_HAL_GetOutDiv4(SIM) + 1);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetRtcOutFreq
* Description   : Gets the RTC_CLKOUT frequency.
* This function gets RTC_CLKOUT  clock frequency.
*
*END**************************************************************************/
uint32_t CLOCK_SYS_GetRtcOutFreq(void)
{
    if (kClockRtcoutSrc1Hz == CLOCK_SYS_GetRtcOutSrc())
    {
        return 1U;
    }
    else
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetRtcFreq
 * Description   : Gets rtc clock frequency.
 * This function gets rtc clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetRtcFreq(uint32_t instance)
{
    return CLOCK_SYS_GetExternalRefClock32kFreq();
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
    case kClockEr32kSrcRtc:      /* RTC 32k clock  */
        freq = g_xtalRtcClkFreq;
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
* Function Name : CLOCK_SYS_GetTpmFreq
* Description	 : Gets the clock frequency for TPM module.
* This function gets the clock frequency for TPM moudle.
*
*END**************************************************************************/
uint32_t CLOCK_SYS_GetTpmFreq(uint32_t instance)
{

    clock_tpm_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetTpmSrc(SIM, instance);

    switch (src)
    {
    case kClockTpmSrcIrc48M:	  /* IRC48M */
	freq = kMcgliteConst48M;
	break;
    case kClockTpmSrcOsc0erClk: 	 	/* OSCER clock */
	freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
	break;
    case kClockTpmSrcMcgIrClk: 		/* MCGIR clock */
	freq = CLOCK_HAL_GetInternalRefClk(MCG);
	break;
    default:
	freq = 0U;
	break;
    }

    return freq;

}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetLpuartFreq
* Description	 : Gets the clock frequency for LPUART module.
* This function gets the clock frequency for LPUART moudle.
*
*END**************************************************************************/
uint32_t CLOCK_SYS_GetLpuartFreq(uint32_t instance)
{

    clock_lpuart_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetLpuartSrc(SIM, instance);

    switch (src)
    {
    case kClockLpuartSrcIrc48M:	  /* IRC48M */
	freq = kMcgliteConst48M;
	break;
    case kClockLpuartSrcOsc0erClk:		/* OSCER clock */
	freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
	break;
    case kClockLpuartSrcMcgIrClk:		/* MCGIR clock */
	freq = CLOCK_HAL_GetInternalRefClk(MCG);
	break;
    default:
	freq = 0U;
	break;
    }

    return freq;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLptmrFreq
 * Description   : Gets LPTMRx pre-scaler/glitch filter clock frequency.
 * This function gets the LPTMRx pre-scaler/glitch filter clock frequency.
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
        case kClockLptmrSrcOsc0erClk:        /* OSCERCLK clock */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetTpmExternalFreq
* Description	 : Gets Tpm external clock frequency.
*
*END**************************************************************************/
uint32_t CLOCK_SYS_GetTpmExternalFreq(uint32_t instance)
{
    sim_tpm_clk_sel_t sel = SIM_HAL_GetTpmExternalClkPinSelMode(SIM, instance);

    if (kSimTpmClkSel0 == sel)
    {
        return g_tpmClkFreq[0];
    }
    else
    {
        return g_tpmClkFreq[1];
    }
}


/* PORT instance table. */
static const sim_clock_gate_name_t portGateTable[] =
{
    kSimClockGatePortA,
    kSimClockGatePortB,
};

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_EnablePortClock
* Description   : Enable the clock for PORT module
* This function enables the clock for PORT moudle
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
* This function disables the clock for PORT moudle
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
* This function will get the clock gate state for PORT moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetPortGateCmd(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, portGateTable[instance]);
}

/* ADC instance table. */
static const sim_clock_gate_name_t adcGateTable[] =
{
    kSimClockGateAdc0,
};

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_EnableAdcClock
* Description   : Enable the clock for ADC module
* This function enables the clock for ADC moudle
*
*END**************************************************************************/
void CLOCK_SYS_EnableAdcClock(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    SIM_HAL_EnableClock(SIM, adcGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_DisableAdcClock
* Description   : Disable the clock for ADC module
* This function disables the clock for ADC moudle
*
*END**************************************************************************/
void CLOCK_SYS_DisableAdcClock(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    SIM_HAL_DisableClock(SIM, adcGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetAdcGateCmd
* Description   : Get the the clock gate state for ADC module
* This function will get the clock gate state for ADC moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetAdcGateCmd(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, adcGateTable[instance]);
}

/* SPI instance table. */
static const sim_clock_gate_name_t spiGateTable[] =
{
    kSimClockGateSpi0,
};

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_EnableSpiClock
* Description   : Enable the clock for SPI module
* This function enables the clock for SPI moudle
*
*END**************************************************************************/
void CLOCK_SYS_EnableSpiClock(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    SIM_HAL_EnableClock(SIM, spiGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_DisableSpiClock
* Description   : Disable the clock for SPI module
* This function disables the clock for SPI moudle
*
*END**************************************************************************/
void CLOCK_SYS_DisableSpiClock(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    SIM_HAL_DisableClock(SIM, spiGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetSpiGateCmd
* Description   : Get the the clock gate state for SPI module
* This function will get the clock gate state for SPI moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetSpiGateCmd(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, spiGateTable[instance]);
}

/* I2C instance table. */
static sim_clock_gate_name_t i2cGateTable[] =
{
    kSimClockGateI2c0,
};

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_EnableI2cClock
* Description   : Enable the clock for I2C module
* This function enables the clock for I2C moudle
*
*END**************************************************************************/
void CLOCK_SYS_EnableI2cClock(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    SIM_HAL_EnableClock(SIM, i2cGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_DisableI2cClock
* Description   : Disable the clock for I2C module
* This function disables the clock for I2C moudle
*
*END**************************************************************************/
void CLOCK_SYS_DisableI2cClock(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    SIM_HAL_DisableClock(SIM, i2cGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetI2cGateCmd
* Description   : Get the the clock gate state for I2C module
* This function will get the clock gate state for I2C moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetI2cGateCmd(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, i2cGateTable[instance]);
}

/* Lpuart instance table. */
static const sim_clock_gate_name_t lpuartGateTable[] =
{
    kSimClockGateLpuart0
};

/*FUNCTION**********************************************************************
*
* Function Name : SIM_HAL_EnableUartClock
* Description   : Enable the clock for UART module
* This function enables the clock for UART moudle
*
*END**************************************************************************/
void CLOCK_SYS_EnableLpuartClock(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    SIM_HAL_EnableClock(SIM, lpuartGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : SIM_HAL_DisableUartClock
* Description   : Disable the clock for UART module
* This function enables the clock for UART moudle
*
*END**************************************************************************/
void CLOCK_SYS_DisableLpuartClock(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    SIM_HAL_DisableClock(SIM, lpuartGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : SIM_HAL_GetUartGateCmd
* Description   : Get the the clock gate state for UART module
* This function will get the clock gate state for UART moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetLpuartGateCmd(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, lpuartGateTable[instance]);
}

/* TPM instance table. */
static const sim_clock_gate_name_t tpmGateTable[] =
{
    kSimClockGateTpm0,
    kSimClockGateTpm1,
};

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_EnableTpmClock
* Description	 : Enable the clock for TPM module
* This function enables the clock for TPM moudle
*
*END**************************************************************************/
void CLOCK_SYS_EnableTpmClock(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    SIM_HAL_EnableClock(SIM, tpmGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_DisableTpmClock
* Description	 : Disable the clock for TPM module
* This function disables the clock for TPM moudle
*
*END**************************************************************************/
void CLOCK_SYS_DisableTpmClock(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    SIM_HAL_DisableClock(SIM, tpmGateTable[instance]);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_SYS_GetTpmGateCmd
* Description	 : Get the the clock gate state for TPM module
* This function will get the clock gate state for TPM moudle.
*
*END**************************************************************************/
bool CLOCK_SYS_GetTpmGateCmd(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, tpmGateTable[instance]);
}

/*******************************************************************************
* EOF
******************************************************************************/
