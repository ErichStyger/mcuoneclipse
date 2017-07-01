/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
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
#include "drivers/flash/fsl_flash.h"
#include "fsl_device_registers.h"
#include "flash_memory.h"
#endif // BOOTLOADER_HOST
#include "utilities/fsl_assert.h"

//! @addtogroup memif
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

// Forward function declarations.
bool mem_is_block_reserved(uint32_t address, uint32_t length);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief This variable is used to do flush operation, it is bind to write operation.
static const memory_region_interface_t *s_flushMemoryInterface = NULL;

//! @brief Interface to generic memory operations.
const memory_interface_t g_memoryInterface = {
    mem_init,  mem_read,  mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
    mem_fill,
#else
    NULL,
#endif // !BL_FEATURE_MIN_PROFILE
    mem_flush, mem_erase,
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See memory.h for documentation on this function.
status_t mem_read(uint32_t address, uint32_t length, uint8_t *buffer)
{
    if (length == 0)
    {
        return kStatus_Success;
    }

    const memory_map_entry_t *mapEntry;
    status_t status = find_map_entry(address, length, &mapEntry);
    if (status == kStatus_Success)
    {
        status = mapEntry->memoryInterface->read(address, length, buffer);
    }
    return status;
}

// See memory.h for documentation on this function.
status_t mem_write(uint32_t address, uint32_t length, const uint8_t *buffer)
{
    if (length == 0)
    {
        return kStatus_Success;
    }

    if (mem_is_block_reserved(address, length))
    {
        return kStatusMemoryRangeInvalid;
    }

    const memory_map_entry_t *mapEntry;
    status_t status = find_map_entry(address, length, &mapEntry);
    if (status == kStatus_Success)
    {
        status = mapEntry->memoryInterface->write(address, length, buffer);

        if (status == kStatus_Success)
        {
            s_flushMemoryInterface = mapEntry->memoryInterface;
        }
        else
        {
            s_flushMemoryInterface = NULL;
        }
    }
    return status;
}

status_t mem_erase(uint32_t address, uint32_t length)
{
    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    const memory_map_entry_t *mapEntry;
    status = find_map_entry(address, length, &mapEntry);
    if (status == kStatus_Success)
    {
        // In this case, it means that bootloader tries to erase a range of memory
        // which doesn't support erase operaton
        if (mapEntry->memoryInterface->erase == NULL)
        {
            return kStatus_FLASH_AddressError;
        }

        if (mem_is_block_reserved(address, length))
        {
            return kStatusMemoryRangeInvalid;
        }

        status = mapEntry->memoryInterface->erase(address, length);
    }
    else if (length == 0)
    {
        // if length = 0, return kStatus_Success regardless of memory address
        return kStatus_Success;
    }
#endif // BOOTLOADER_HOST

    return status;
}

// See memory.h for documentation on this function.
status_t mem_fill(uint32_t address, uint32_t length, uint32_t pattern)
{
    if (length == 0)
    {
        return kStatus_Success;
    }

    if (mem_is_block_reserved(address, length))
    {
        return kStatusMemoryRangeInvalid;
    }

    const memory_map_entry_t *mapEntry;
    status_t status = find_map_entry(address, length, &mapEntry);
    if (status == kStatus_Success)
    {
        status = mapEntry->memoryInterface->fill(address, length, pattern);
    }
    return status;
}

//! @brief Flush buffered data into target memory
//! @note  1. This function should be called immediately after one write-memory command(either
//!        received in command packet or in sb file), only in this way, given data can be programmed
//!        at given address as expected.
//!
//!        2. So far, flush() is only implemented in qspi memory interface, for other memory
//!        interfaces, it is not available and mem_flush() just returns kStatus_Success if it is
//!        called.
//!
//!        3. This function is designed to flush buffered data into target memory, please call it
//!        only if it is required to do so. For example, write 128 bytes to qspi flash, while the
//!        page size is 256 bytes, that means data might not be written to qspi memory immediately,
//!        since the internal buffer of qspi memory interface is not full, if no data are expected
//!        to write to left area of the same page, this function can be used to force to write
//!        immediately, otherwise, keep in mind that any calls should be avoided. If users voilate
//!        this rules, it would make the left area of the same page cannot be programmed.
//!
//! @return An error code or kStatus_Success
status_t mem_flush(void)
{
    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    if (s_flushMemoryInterface && s_flushMemoryInterface->flush)
    {
        status = s_flushMemoryInterface->flush();
        s_flushMemoryInterface = NULL; // Clear this variable after performing flush operation
    }
#endif // BOOTLOADER_HOST

    return status;
}

//! @brief Find a map entry that matches address and length.
//!
//! @param address Start address for the memory operation.
//! @param length Number of bytes on which the operation will act.
//! @param map The matching map entry is returned through this pointer if the return status
//!     is #kStatus_Success.
//!
//! @retval #kStatus_Success A valid map entry was found and returned through @a map.
//! @retval #kStatusMemoryRangeInvalid The requested address range does not match an entry, or
//!     the length extends past the matching entry's end address.
status_t find_map_entry(uint32_t address, uint32_t length, const memory_map_entry_t **map)
{
    status_t status = kStatusMemoryRangeInvalid;

    // Set starting entry.
    assert(map);
    if (map)
    {
        *map = &g_bootloaderContext.memoryMap[0];
    }

    // Scan memory map array looking for a match.
    while ((length > 0) && map && *map)
    {
        if (((*map)->startAddress == 0) && ((*map)->endAddress == 0) && ((*map)->memoryInterface == NULL))
        {
            break;
        }
        // Check if the start address is within this entry's address range.
        if ((address >= (*map)->startAddress) && (address <= (*map)->endAddress))
        {
            // Check that the length fits in this entry's address range.
            if ((address + length - 1) <= (*map)->endAddress)
            {
                status = kStatus_Success;
            }
            break;
        }
        ++(*map);
    }

    return status;
}

// See memory.h for documentation on this function.
bool mem_is_block_reserved(uint32_t address, uint32_t length)
{
    uint32_t end = address + length - 1;
    uint32_t start = 0;
    for (uint32_t i = 0; i < kProperty_ReservedRegionsCount; ++i)
    {
        reserved_region_t *region = &g_bootloaderContext.propertyInterface->store->reservedRegions[i];

        start = (&g_bootloaderContext.memoryMap[i])->startAddress;
        if ((region->startAddress == start) && (region->endAddress == start))
        {
            // Special case, empty region
            continue;
        }

        if ((address <= region->endAddress) && (end >= region->startAddress))
        {
            return true;
        }
    }
    return false;
}

// See memory.h for documentation on this function.
status_t mem_init(void)
{
    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)

    const memory_map_entry_t *map = &g_bootloaderContext.memoryMap[0];

    while (map->memoryInterface)
    {
        if (map->memoryInterface->init)
        {
            map->memoryInterface->init();
        }
        ++map;
    }

#endif // BOOTLOADER_HOST

    return status;
}

// See memory.h for documentation on this function.
bool mem_is_erased(uint32_t address, uint32_t length)
{
    const uint8_t *start = (const uint8_t *)address;
    bool isMemoryErased = true;

    while (length)
    {
        if (*start != 0xFF)
        {
            isMemoryErased = false;
            break;
        }
        else
        {
            length--;
            start++;
        }
    }

    return isMemoryErased;
}

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
