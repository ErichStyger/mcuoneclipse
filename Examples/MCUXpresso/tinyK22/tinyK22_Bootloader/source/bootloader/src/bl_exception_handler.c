/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
//! @brief SYSMPU Fault Handler
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
