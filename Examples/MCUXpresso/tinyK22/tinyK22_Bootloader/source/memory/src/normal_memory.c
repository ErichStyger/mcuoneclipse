/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright (c) 2016-2018, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "normal_memory.h"
#include "pattern_fill.h"
#include "sram_init.h"
#include "fsl_device_registers.h"

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
#endif // CPU_IS_ARM_CORTEX_M7

#if defined(CPU_IS_ARM_CORTEX_M7) || defined(K28F15_SERIES)
//! @brief Interface to simulator memory operations.
const memory_region_interface_t g_normalOCRAMInterface = {.init = &normal_mem_init,
                                                          .read = &normal_mem_read,
                                                          .write = &normal_mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
                                                          .fill = &normal_mem_fill,
#endif // !BL_FEATURE_MIN_PROFILE
                                                          .flush = NULL,
                                                          .erase = NULL };
#endif // defined(CPU_IS_ARM_CORTEX_M7) || defined(K28F15_SERIES)

enum
{
    kSRAM_Boundary = 0x20000000u //!< SRAM boundary address
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! See normal_memory.h for documentation on this function.
__WEAK status_t normal_mem_init(void)
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
