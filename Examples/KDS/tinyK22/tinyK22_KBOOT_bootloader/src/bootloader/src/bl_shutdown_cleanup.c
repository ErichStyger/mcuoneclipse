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
#if !defined(BOOTLOADER_HOST)
#include "fsl_device_registers.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "utilities/vector_table_info.h"
#include "flash/fsl_flash.h"
#include "microseconds/microseconds.h"
#include "bootloader_common.h"

#endif // BOOTLOADER_HOST

#include "bootloader/bl_shutdown_cleanup.h"
#include "bootloader/bl_context.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
extern void init_interrupts(void);
void flash_cache_clear(flash_config_t *config);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bl_shutdown_cleanup.h for documentation of this function.
void shutdown_cleanup(shutdown_type_t shutdown)
{
#if !defined(BOOTLOADER_HOST)
    if (shutdown != kShutdownType_Reset)
    {
        // Clear (flush) the flash cache.
        flash_cache_clear(NULL);
    }

    if (shutdown != kShutdownType_Cleanup)
    {
        // Shutdown all peripherals because they could be active
        uint32_t i;
        for (i = 0; g_peripherals[i].typeMask != 0; i++)
        {
            if (g_peripherals[i].controlInterface->shutdown)
            {
                g_peripherals[i].controlInterface->shutdown(&g_peripherals[i]);
            }
        }
    }

    // If we are permanently exiting the bootloader, there are a few extra things to do.
    if (shutdown == kShutdownType_Shutdown)
    {
        // Turn off global interrupt
        lock_acquire();

        // Shutdown microseconds driver.
        microseconds_shutdown();

#if defined(RCM_FM)
        // Disable force ROM.
        RCM_BWR_FM_FORCEROM(RCM, 0);

        // Clear status register (bits are w1c).
        RCM_BWR_MR_BOOTROM(RCM, 3);
#endif // defined(RCM_FM)

        init_interrupts();

        // Set the VTOR to default.
        SCB->VTOR = kDefaultVectorTableAddress;

        // Restore clock to default before leaving bootloader.
        configure_clocks(kClockOption_ExitBootloader);

        // De-initialize hardware such as disabling port clock gate
        deinit_hardware();

        // Restore global interrupt.
        __enable_irq();

#if BL_FEATURE_BYPASS_WATCHDOG
        // De-initialize watchdog
        bootloader_watchdog_deinit();
#endif // BL_FEATURE_BYPASS_WATCHDOG
    }

    // Memory barriers for good measure.
    __ISB();
    __DSB();
#endif
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
