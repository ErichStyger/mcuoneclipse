/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __BOOTLOADER_CORE_H__
#define __BOOTLOADER_CORE_H__

#include "fsl_device_registers.h"

// These functions are missing from the latest CMSIS core header files.
#if __CORTEX_M == 0x00

/** \brief  Clear Enabled IRQs

    The function clears all device IRQs
 */
__STATIC_INLINE void NVIC_ClearEnabledIRQs(void)
{
    NVIC->ICER[0] = 0xFFFFFFFF;
}

/** \brief  Clear All Pending Interrupts

    The function clears the pending bits of all external interrupts.

 */
__STATIC_INLINE void NVIC_ClearAllPendingIRQs(void)
{
    NVIC->ICPR[0] = 0xFFFFFFFF;
}

#elif __CORTEX_M == 0x04 || __CORTEX_M == 0x07

/** \brief  Clear Enabled IRQs

    The function clears all device IRQs
 */
__STATIC_INLINE void NVIC_ClearEnabledIRQs(void)
{
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICER[1] = 0xFFFFFFFF;
    NVIC->ICER[2] = 0xFFFFFFFF;
    NVIC->ICER[3] = 0xFFFFFFFF;
    NVIC->ICER[4] = 0xFFFFFFFF;
    NVIC->ICER[5] = 0xFFFFFFFF;
    NVIC->ICER[6] = 0xFFFFFFFF;
    NVIC->ICER[7] = 0xFFFFFFFF;
}

/** \brief  Clear All Pending Interrupts

    The function clears the pending bits of all external interrupts.

 */
__STATIC_INLINE void NVIC_ClearAllPendingIRQs(void)
{
    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICPR[1] = 0xFFFFFFFF;
    NVIC->ICPR[2] = 0xFFFFFFFF;
    NVIC->ICPR[3] = 0xFFFFFFFF;
    NVIC->ICPR[4] = 0xFFFFFFFF;
    NVIC->ICPR[5] = 0xFFFFFFFF;
    NVIC->ICPR[6] = 0xFFFFFFFF;
    NVIC->ICPR[7] = 0xFFFFFFFF;
}
#else
#error CORTEX_M version not defined
#endif

#endif // __BOOTLOADER_CORE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
