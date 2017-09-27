/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#include "bootloader_common.h"
#include "fsl_device_registers.h"

#if defined(DEBUG)

typedef struct _stack_frame
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
} stack_frame_t;

volatile stack_frame_t *s_stack_frame;

#endif
////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief HardFault_Handler
void HardFault_Handler(void)
{
#if defined(DEBUG)
    s_stack_frame = (stack_frame_t *)__get_MSP();
    __ASM("BKPT #0");
    (void)s_stack_frame;
#endif

    // Reset MCU
    NVIC_SystemReset();
}

/* Functions below only apply to mcus belonging to ARM-Cortex M4 family */
#if defined(__CORE_CM4_H_GENERIC)
//! @brief MPU Fault Handler
void MemManage_Handler(void)
{
#if defined(DEBUG)
    __ASM("BKPT #0");
#endif // DEBUG

    // Reset MCU
    NVIC_SystemReset();
}

//! @brief Bus Fault Handler
void BusFault_Handler(void)
{
#if defined(DEBUG)
    __ASM("BKPT #0");
#endif // DEBUG

    // Reset MCU
    NVIC_SystemReset();
}

//! @brief Usage Fault Handler
void UsageFault_Handler(void)
{
#if defined(DEBUG)
    __ASM("BKPT #0");
#endif // DEBUG

    // Reset MCU
    NVIC_SystemReset();
}

#endif // __CORE_C4_H_GENERIC

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
