/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "bootloader/bl_context.h"
#include "memory/memory.h"
#if !defined(BOOTLOADER_HOST)
#include "fsl_device_registers.h"
#endif // BOOTLOADER_HOST
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
#if defined(__CORE_CM4_H_GENERIC)

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

#else
#error "This function only applies to cm4 family"
#endif // __CORE_CM4_H_GENERIC

    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
