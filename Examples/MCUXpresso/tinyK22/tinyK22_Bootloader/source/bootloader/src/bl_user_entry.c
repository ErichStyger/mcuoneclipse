/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "bootloader_common.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bl_user_entry.h for documentation of this function.
void bootloader_user_entry(void *arg)
{
#if BL_TARGET_ROM

    // For ROM targets, we set the RCM_FM bits to force the ROM to run out of
    // reset, then perform a reset. This provides a guaranteed clean system.
#if defined(K32W042S1M2_M4_SERIES)
    // fixme SMC0 or SCM1?
    SMC0->FM = 0x3;
#else
    RCM->FM |= RCM_FM_FORCEROM(0x3);
#endif // defined(K32W042S1M2_M4_SERIES
    NVIC_SystemReset();

#elif BL_TARGET_FLASH

    // For flash-resident configurations, just call the reset handler as the entry point.
    Reset_Handler();

#elif !BL_TARGET_RAM
#error "Undefined target type"
#endif // BL_TARGET_ROM
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
