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

#include "fsl_trgmux.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t TRGMUX_SetTriggerSource(TRGMUX_Type *base,
                                 trgmux_device_t index,
                                 trgmux_trigger_input_t input,
                                 trgmux_source_t trigger_src)
{
    uint32_t value;

    value = base->TRGCFG[index];
    if (value & TRGMUX_TRGCFG_LK_MASK)
    {
        return kStatus_TRGMUX_Locked;
    }
    else
    {
        /* Since all SEL bitfileds in TRGCFG register have the same length, SEL0's mask is used to access other SEL
         * bitfileds. */
        value = (value & ~((uint32_t)(TRGMUX_TRGCFG_SEL0_MASK << input))) |
                ((uint32_t)(((uint32_t)(trigger_src & TRGMUX_TRGCFG_SEL0_MASK)) << input));
        base->TRGCFG[index] = value;
        return kStatus_Success;
    }
}
