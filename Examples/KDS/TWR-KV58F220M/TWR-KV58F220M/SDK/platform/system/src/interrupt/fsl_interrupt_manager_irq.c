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

#include "fsl_device_registers.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_INTMUX_COUNT
#include "fsl_intmux_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if INTMUX_INSTANCE_COUNT > 0U
/* INTMUX0_0_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX0_0_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX0_IDX,kIntmuxChannel0);
}

/* INTMUX0_1_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX0_1_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX0_IDX,kIntmuxChannel1);
}

/* INTMUX0_2_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX0_2_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX0_IDX,kIntmuxChannel2);
}

/* INTMUX0_3_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX0_3_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX0_IDX,kIntmuxChannel3);
}
#endif

#if INTMUX_INSTANCE_COUNT > 1U
/* INTMUX1_0_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX1_0_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX1_IDX,kIntmuxChannel0);
}

/* INTMUX1_1_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX1_1_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX1_IDX,kIntmuxChannel1);
}

/* INTMUX1_2_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX1_2_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX1_IDX,kIntmuxChannel2);
}

/* INTMUX1_3_IRQHandler that would cover the same name's APIs in startup code */
void INTMUX1_3_IRQHandler(void)
{
    INTMUX_IRQHandler(INTMUX1_IDX,kIntmuxChannel3);
}
#endif
#endif //end for FSL_FEATURE_SOC_INTMUX_COUNT

/*******************************************************************************
 * EOF
 ******************************************************************************/

