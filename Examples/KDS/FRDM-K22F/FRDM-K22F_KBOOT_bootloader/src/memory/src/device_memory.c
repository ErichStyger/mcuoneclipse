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
#include "device_memory.h"
#include "pattern_fill.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static void device_copy(uint32_t address, uint32_t length, uint32_t buffer);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Interface to simulator memory operations.
const memory_region_interface_t g_deviceMemoryInterface = {.read = &device_mem_read,
                                                           .write = &device_mem_write,
#if !BL_FEATURE_MIN_PROFILE || BL_FEATURE_FILL_MEMORY
                                                           .fill = &device_mem_fill,
#endif // !BL_FEATURE_MIN_PROFILE
                                                           .flush = NULL,
                                                           .erase = NULL };

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Device-safe memory copy.
//!
//! Performs a memory copy using aligned accesses of no more than one word
//! at a time.
void device_copy(uint32_t address, uint32_t length, uint32_t buffer)
{
    // This loop lets us reuse the byte and halfword copy code.
    while (length)
    {
        // Handle leading/trailing byte.
        if ((address & 1) || (length == 1))
        {
            *(uint8_t *)address = *(const uint8_t *)buffer;
            ++address;
            ++buffer;
            --length;
            continue;
        }

        // Handle leading/trailing halfword.
        if ((address & 2) || (length < sizeof(uint32_t)))
        {
            *(uint16_t *)address = *(const uint16_t *)buffer;
            address += sizeof(uint16_t);
            buffer += sizeof(uint16_t);
            length -= sizeof(uint16_t);
        }

        // Copy as many whole words as remain.
        uint32_t words = length >> 2;
        if (words)
        {
            uint32_t wordsLength = words << 2;
            uint32_t end = address + wordsLength;
            while (address < end)
            {
                *(uint32_t *)address = *(uint32_t *)buffer;
                address += sizeof(uint32_t);
                buffer += sizeof(uint32_t);
            }

            length -= wordsLength;
        }
    }
}

status_t device_mem_read(uint32_t address, uint32_t length, uint8_t *buffer)
{
    device_copy((uint32_t)buffer, length, address);
    return kStatus_Success;
}

status_t device_mem_write(uint32_t address, uint32_t length, const uint8_t *buffer)
{
    device_copy(address, length, (uint32_t)buffer);
    return kStatus_Success;
}

status_t device_mem_fill(uint32_t address, uint32_t length, uint32_t pattern)
{
    status_t status = kStatus_Success;
    status = pattern_fill(address, pattern, length, true);
    return status;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
