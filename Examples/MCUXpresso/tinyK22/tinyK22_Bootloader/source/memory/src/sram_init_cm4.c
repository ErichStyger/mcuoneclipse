/*
 * Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_common.h"
#include "bootloader/bl_context.h"
#include "memory/memory.h"
#include "fsl_device_registers.h"
#include "sram_init.h"
#include "utilities/fsl_assert.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
//! @brief Determine if a number is power of 2.
static inline bool is_power_of_2(uint32_t number)
{
    return !(number && (number & (number - 1)));
}

//! @brief Initialize address ranges of SRAM for chips belongs to cm4 family
status_t sram_init(void)
{
    memory_map_entry_t *map = NULL;
#if defined(__CORE_CM4_H_GENERIC)

#if defined(K32W042S1M2_M4_SERIES)
    // Nothing to do, ranges hard-coded in memory map.
#else

    uint32_t ram_size = 0;
    uint32_t tmp;
#if defined(FSL_FEATURE_SIM_OPT_HAS_RAMSIZE)
    tmp = (SIM->SOPT1 & SIM_SOPT1_RAMSIZE_MASK) >> SIM_SOPT1_RAMSIZE_SHIFT;
#elif defined(FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE)
    tmp = (SIM->SDID & SIM_SDID_RAMSIZE) >> SIM_SDID_RAMSIZE_SHIFT;
#else
#error "No valid RAMSIZE defined!"
#endif
    switch (tmp)
    {
        case kRamSize16kIndex:
            ram_size = 16 * 1024UL;
            break;
        case kRamSize24kIndex:
            ram_size = 24 * 1024UL;
            break;
        case kRamSize32kIndex:
            ram_size = 32 * 1024UL;
            break;
        case kRamSize48kIndex:
            ram_size = 48 * 1024UL;
            break;
        case kRamSize64kIndex:
            ram_size = 64 * 1024UL;
            break;
        case kRamSize96kIndex:
            ram_size = 96 * 1024UL;
            break;
        case kRamSize128kIndex:
            ram_size = 128 * 1024UL;
            break;
        case kRamSize256kIndex:
            ram_size = 256 * 1024UL;
            break;
        case kRamSize512kIndex:
            ram_size = 512 * 1024UL;
            break;
        case kRamSize1024kIndex:
            ram_size = 1024 * 1024UL;
#if defined(K28F15_SERIES)
            // Update ram_size, minus OCRAM size.
            map = (memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexOCRAM];
            ram_size -= (map->endAddress - map->startAddress + 1);
#endif // #if defined(K28F15_SERIES)
            break;
        default:
            ram_size = 0;
            break;
    }

    assert(ram_size > 0);

    uint32_t sram_lower_part = kSram_LowerPart;
    uint32_t sram_upper_part = kSram_UpperPart;

    if (ram_size)
    {
        // For target in which RAM size is not power of 2, for example, 24KB, 48KB, 96KB, 192KB, etc
        // SRAM_LOWER is 1 / 3 of Total SRAM.
        if (!is_power_of_2(ram_size))
        {
            sram_lower_part = 1;
            sram_upper_part = 2;
        }

        // Update  address range of SRAM
        memory_map_entry_t *map = (memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexSRAM];

        uint32_t tmp = ram_size / (sram_lower_part + sram_upper_part);

        map->startAddress = kSRAMSeparatrix - tmp * sram_lower_part;   // start of SRAM
        map->endAddress = kSRAMSeparatrix + tmp * sram_upper_part - 1; // end of SRAM
    }

#endif // K32W042S1M2_M4_SERIES

#else
#error "This function only applies to cm4 family"
#endif // __CORE_CM4_H_GENERIC

    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
