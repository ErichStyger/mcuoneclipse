/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_common.h"
#include "fsl_smc.h"
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
 * Code
******************************************************************************/

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*
 * How to setup clock using clock driver functions:
 *
 * 1. CLOCK_SetSimSafeDivs, to make sure core clock, bus clock, flexbus clock
 *    and flash clock are in allowed range during clock mode switch.
 *
 * 2. Call CLOCK_Osc0Init to setup OSC clock, if it is used in target mode.
 *
 * 3. Set MCG configuration, MCG includes three parts: FLL clock, PLL clock and
 *    internal reference clock(MCGIRCLK). Follow the steps to setup:
 *
 *    1). Call CLOCK_BootToXxxMode to set MCG to target mode.
 *
 *    2). If target mode is FBI/BLPI/PBI mode, the MCGIRCLK has been configured
 *        correctly. For other modes, need to call CLOCK_SetInternalRefClkConfig
 *        explicitly to setup MCGIRCLK.
 *
 *    3). Don't need to configure FLL explicitly, because if target mode is FLL
 *        mode, then FLL has been configured by the function CLOCK_BootToXxxMode,
 *        if the target mode is not FLL mode, the FLL is disabled.
 *
 *    4). If target mode is PEE/PBE/PEI/PBI mode, then the related PLL has been
 *        setup by CLOCK_BootToXxxMode. In FBE/FBI/FEE/FBE mode, the PLL could
 *        be enabled independently, call CLOCK_EnablePll0 explicitly in this case.
 *
 * 4. Call CLOCK_SetSimConfig to set the clock configuration in SIM.
 */

static void CLOCK_SYS_FllStableDelay(void)
{
    uint32_t i = 30000U;
    while (i--)
    {
        __NOP();
    }
}

void BOARD_BootClockVLPR(void)
{
    const sim_clock_config_t simConfig = {
        .er32kSrc = 0U, .clkdiv1 = 0x00040000U,
    };

    /* ERR010224 */
    RSIM->RF_OSC_CTRL |= RSIM_RF_OSC_CTRL_RADIO_EXT_OSC_OVRD_EN_MASK;   /* Prevent XTAL_OUT_EN from generating XTAL_OUT request */

    CLOCK_SetSimSafeDivs();

    CLOCK_BootToBlpiMode(0U, kMCG_IrcFast, kMCG_IrclkEnable);

    CLOCK_SetSimConfig(&simConfig);

    SystemCoreClock = 4000000U;

    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeVlpr(SMC);
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateVlpr)
    {
    }
}

void BOARD_BootClockRUN(void)
{
    const sim_clock_config_t simConfig = {
        .er32kSrc = 0U, .clkdiv1 = 0x00010000U,
    };

    BOARD_RfOscInit();

    CLOCK_SetSimSafeDivs();

    BOARD_InitOsc0();
    CLOCK_BootToFeeMode(kMCG_OscselOsc, 5U, kMCG_Dmx32Default, kMCG_DrsMid, CLOCK_SYS_FllStableDelay);

    CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcSlow, 0U);
    
    CLOCK_SetSimConfig(&simConfig);

    SystemCoreClock = 40000000U;
}

void BOARD_RfOscInit(void)
{
    uint32_t temp, tempTrim;
    uint8_t revId;

    /* Obtain REV ID from SIM */
    temp = SIM->SDID;
    revId = (uint8_t)((temp & SIM_SDID_REVID_MASK) >> SIM_SDID_REVID_SHIFT);

    if(0 == revId)
    {
        tempTrim = RSIM->ANA_TRIM;
        RSIM->ANA_TRIM |= RSIM_ANA_TRIM_BB_LDO_XO_TRIM_MASK;            /* Set max trim for BB LDO for XO */
    }/* Workaround for Rev 1.0 XTAL startup and ADC analog diagnostics circuitry */

    /* Turn on clocks for the XCVR */
    /* Enable RF OSC in RSIM and wait for ready */
    temp = RSIM->CONTROL;
    temp &= ~RSIM_CONTROL_RF_OSC_EN_MASK;
    RSIM->CONTROL = temp | RSIM_CONTROL_RF_OSC_EN(1);

    /* ERR010224 */
    RSIM->RF_OSC_CTRL |= RSIM_RF_OSC_CTRL_RADIO_EXT_OSC_OVRD_EN_MASK;   /* Prevent XTAL_OUT_EN from generating XTAL_OUT request */

    while((RSIM->CONTROL & RSIM_CONTROL_RF_OSC_READY_MASK) == 0);       /* Wait for RF_OSC_READY */

    if(0 == revId)
    {
        SIM->SCGC5 |= SIM_SCGC5_PHYDIG_MASK;
        XCVR_TSM->OVRD0 |= XCVR_TSM_OVRD0_BB_LDO_ADCDAC_EN_OVRD_EN_MASK | XCVR_TSM_OVRD0_BB_LDO_ADCDAC_EN_OVRD_MASK; /* Force ADC DAC LDO on to prevent BGAP failure */

        RSIM->ANA_TRIM = tempTrim;                                      /* Reset LDO trim settings */
    }/* Workaround for Rev 1.0 XTAL startup and ADC analog diagnostics circuitry */
}

void BOARD_InitOsc0(void)
{
    const osc_config_t oscConfig = {
        .freq = BOARD_XTAL0_CLK_HZ, .workMode = kOSC_ModeExt,
    };

    CLOCK_InitOsc0(&oscConfig);

    /* Passing the XTAL0 frequency to clock driver. */
    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);
}
