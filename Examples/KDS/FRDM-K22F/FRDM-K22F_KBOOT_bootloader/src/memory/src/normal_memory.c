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

#include <string.h>
#include "normal_memory.h"
#include "pattern_fill.h"
#include "sram_init.h"
#if !defined(BOOTLOADER_HOST)
#include "fsl_device_registers.h"
#endif // BOOTLOADER_HOST

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Interface to simulator memory operations.
const memory_region_interface_t g_normalMemoryInterface = {.init = &normal_mem_init,
                                                           .read = &normal_mem_read,
                                                           .write = &normal_mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
                                                           .fill = &normal_mem_fill,
#endif // !BL_FEATURE_MIN_PROFILE
                                                           .flush = NULL,
                                                           .erase = NULL };

#if CPU_IS_ARM_CORTEX_M7
//! @brief Interface to simulator memory operations.
const memory_region_interface_t g_normalDTCMInterface = {.init = &normal_mem_init,
                                                         .read = &normal_mem_read,
                                                         .write = &normal_mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
                                                         .fill = &normal_mem_fill,
#endif // !BL_FEATURE_MIN_PROFILE
                                                         .flush = NULL,
                                                         .erase = NULL };

//! @brief Interface to simulator memory operations.
const memory_region_interface_t g_normalOCRAMInterface = {.init = &normal_mem_init,
                                                          .read = &normal_mem_read,
                                                          .write = &normal_mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
                                                          .fill = &normal_mem_fill,
#endif // !BL_FEATURE_MIN_PROFILE
                                                          .flush = NULL,
                                                          .erase = NULL };
#endif

enum
{
    kSRAM_Boundary = 0x20000000u //!< SRAM boundary address
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! See normal_memory.h for documentation on this function.
status_t normal_mem_init(void)
{
    return sram_init();
}

status_t normal_mem_read(uint32_t address, uint32_t length, uint8_t *buffer)
{
    memcpy((void *)buffer, (void *)address, length);
    return kStatus_Success;
}

status_t normal_mem_write(uint32_t address, uint32_t length, const uint8_t *buffer)
{
#if defined(__CORE_CM4_H_GENERIC)
    // If address is non-longword aligned and the area to be written is across RAM_L and RAM_U,
    // need to write the RAM_L first and then write RAM_U to avoid unaligned access across RAM boundary
    if ((address & 0x03) && ((address < kSRAM_Boundary) && ((address + length - 1) >= kSRAM_Boundary)))
    {
        uint32_t firstCopyCount = kSRAM_Boundary - address;
        uint32_t secondCopyCount = length - firstCopyCount;

        memcpy((void *)address, (void *)buffer, firstCopyCount);
        memcpy((void *)kSRAM_Boundary, (void *)(buffer + firstCopyCount), secondCopyCount);
    }
    else
#endif // #if defined (__CORE_CM4_H_GENERIC)
    {
        memcpy((void *)address, (void *)buffer, length);
    }
    return kStatus_Success;
}

status_t normal_mem_fill(uint32_t address, uint32_t length, uint32_t pattern)
{
    status_t status = kStatus_Success;
// Allow multiword stores in the pattern fill.
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
    status = pattern_fill(address, pattern, length, true);
#endif // !BL_FEATURE_MIN_PROFILE
    return status;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
