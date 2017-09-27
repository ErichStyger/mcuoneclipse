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

#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for DMAMUX.
 *
 * @param base DMAMUX peripheral base address.
 */
static uint32_t DMAMUX_GetInstance(DMAMUX_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map DMAMUX instance number to base pointer. */
static DMAMUX_Type *const s_dmamuxBases[] = DMAMUX_BASE_PTRS;

/*! @brief Array to map DMAMUX instance number to clock name. */
static const clock_ip_name_t s_dmamuxClockName[] = DMAMUX_CLOCKS;

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DMAMUX_GetInstance(DMAMUX_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < FSL_FEATURE_SOC_DMAMUX_COUNT; instance++)
    {
        if (s_dmamuxBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < FSL_FEATURE_SOC_DMAMUX_COUNT);

    return instance;
}

void DMAMUX_Init(DMAMUX_Type *base)
{
    CLOCK_EnableClock(s_dmamuxClockName[DMAMUX_GetInstance(base)]);
}

void DMAMUX_Deinit(DMAMUX_Type *base)
{
    CLOCK_DisableClock(s_dmamuxClockName[DMAMUX_GetInstance(base)]);
}
