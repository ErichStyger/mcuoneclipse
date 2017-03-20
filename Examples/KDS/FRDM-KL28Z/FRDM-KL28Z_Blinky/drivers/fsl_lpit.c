/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_lpit.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

void LPIT_Init(LPIT_Type *base, const lpit_config_t *config)
{
    assert(config);

    /* Enable the clock */
    CLOCK_EnableClock(kCLOCK_Lpit0);

    /* Reset the timer channels and registers except the MCR register */
    LPIT_Reset(base);

    /* Setup timer operation in debug and doze modes and enable the module */
    base->MCR =
        (LPIT_MCR_DBG_EN(config->enableRunInDebug) | LPIT_MCR_DOZE_EN(config->enableRunInDoze) | LPIT_MCR_M_CEN_MASK);
}

void LPIT_Deinit(LPIT_Type *base)
{
    /* Disable the module */
    base->MCR &= ~LPIT_MCR_M_CEN_MASK;
    /* Disable the clock */
    CLOCK_DisableClock(kCLOCK_Lpit0);
}

void LPIT_GetDefaultConfig(lpit_config_t *config)
{
    assert(config);

    /* Timers are stopped in debug mode */
    config->enableRunInDebug = false;
    /* Timers are stopped in doze mode */
    config->enableRunInDoze = false;
}

status_t LPIT_SetupChannel(LPIT_Type *base, lpit_chnl_t channel, const lpit_chnl_params_t *chnlSetup)
{
    uint32_t reg = 0;

    /* Cannot assert the chain bit for channel 0 */
    if ((channel == kLPIT_Chnl_0) && (chnlSetup->chainChannel == true))
    {
        return kStatus_Fail;
    }

    /* Setup the channel counters operation mode, trigger operation, chain mode */
    reg = (LPIT_TCTRL_MODE(chnlSetup->timerMode) | LPIT_TCTRL_TRG_SRC(chnlSetup->triggerSource) |
           LPIT_TCTRL_TRG_SEL(chnlSetup->triggerSelect) | LPIT_TCTRL_TROT(chnlSetup->enableReloadOnTrigger) |
           LPIT_TCTRL_TSOI(chnlSetup->enableStopOnTimeout) | LPIT_TCTRL_TSOT(chnlSetup->enableStartOnTrigger) |
           LPIT_TCTRL_CHAIN(chnlSetup->chainChannel));

    base->CHANNEL[channel].TCTRL = reg;

    return kStatus_Success;
}
