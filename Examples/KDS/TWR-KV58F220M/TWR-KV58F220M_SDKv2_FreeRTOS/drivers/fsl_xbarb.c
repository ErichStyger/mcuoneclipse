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

#include "fsl_xbarb.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the XBARB instance from peripheral base address.
 *
 * @param base XBARB peripheral base address.
 * @return XBARB instance.
 */
static uint32_t XBARB_GetInstance(XBARB_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of XBARB peripheral base address. */
static XBARB_Type *const s_xbarbBases[] = XBARB_BASE_PTRS;

/* Array of XBARB clock name. */
static const clock_ip_name_t s_xbarbClock[] = XBARB_CLOCKS;

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t XBARB_GetInstance(XBARB_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < FSL_FEATURE_SOC_XBARB_COUNT; instance++)
    {
        if (s_xbarbBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < FSL_FEATURE_SOC_XBARB_COUNT);

    return instance;
}

void XBARB_Init(XBARB_Type *base)
{
    /* Enable XBARB module clock. */
    CLOCK_EnableClock(s_xbarbClock[XBARB_GetInstance(base)]);
}

void XBARB_Deinit(XBARB_Type *base)
{
    /* Disable XBARB module clock. */
    CLOCK_DisableClock(s_xbarbClock[XBARB_GetInstance(base)]);
}

void XBARB_SetSignalsConnection(XBARB_Type *base, xbar_input_signal_t input, xbar_output_signal_t output)
{
    XBARB_WR_SELx_SELx(base, (((uint16_t)input) & 0xFFU), (((uint16_t)output) & 0xFFU));
}
