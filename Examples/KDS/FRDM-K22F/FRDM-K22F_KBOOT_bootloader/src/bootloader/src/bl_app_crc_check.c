/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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

#include "utilities/fsl_assert.h"
#include <string.h>
#include "bootloader_common.h"
#include "property/property.h"
#include "memory/memory.h"
#include "bootloader/bl_context.h"
#include "crc/crc32.h"
#include "bootloader/bl_app_crc_check.h"
#include "utilities/vector_table_info.h"
#include "target_config.h"

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
#if BL_FEATURE_CRC_ASSERT
//! @brief Toggle a pin to the inverse of default logic state to indicate crc check failure.
static void assert_pin_to_indicate_crc_check_failure(void)
{
    // Initialize pin for GPIO
    PORT_BWR_PCR_MUX(CRC_CHECK_FAILURE_PIN_PORT, CRC_CHECK_FAILURE_PIN_NUMBER, CRC_CHECK_FAILURE_PIN_GPIO_MODE);
    // Set pin as output
    GPIO_SET_PDDR(CRC_CHECK_FAILURE_PIN_GPIO, 1 << CRC_CHECK_FAILURE_PIN_NUMBER);
    // Toggle pin (the inverse of default logic state) for crc check failure
    GPIO_WR_PTOR(CRC_CHECK_FAILURE_PIN_GPIO, 1 << CRC_CHECK_FAILURE_PIN_NUMBER);
}

// See bl_app_crc_check.h for documentation on this function.
void restore_crc_check_failure_pin(void)
{
    // Restore crc check failure pin to default state
    if (PORT_BRD_PCR_MUX(CRC_CHECK_FAILURE_PIN_PORT, CRC_CHECK_FAILURE_PIN_NUMBER) == CRC_CHECK_FAILURE_PIN_GPIO_MODE)
    {
        // Restore pin as input
        GPIO_CLR_PDDR(CRC_CHECK_FAILURE_PIN_GPIO, 1 << CRC_CHECK_FAILURE_PIN_NUMBER);
        // Restore pin as default muxing slot mode
        PORT_BWR_PCR_MUX(CRC_CHECK_FAILURE_PIN_PORT, CRC_CHECK_FAILURE_PIN_NUMBER, CRC_CHECK_FAILURE_PIN_DEFAULT_MODE);
    }
}
#endif
// See bl_app_crc_check.h for documentation on this function.
void init_crc_check_status(property_store_t *propertyStore)
{
    // Crc check is available if BCA exists and crc parameters are set (not all 0xff bytes)
    if (!((propertyStore->configurationData.crcStartAddress == 0xffffffff) &&
          (propertyStore->configurationData.crcByteCount == 0xffffffff) &&
          (propertyStore->configurationData.crcExpectedValue == 0xffffffff)))
    {
        propertyStore->crcCheckStatus = kStatus_AppCrcCheckInactive;
    }
    else
    {
        propertyStore->crcCheckStatus = kStatus_AppCrcCheckInvalid;
    }
}

//! @brief Calculate crc on a range of flash, specified in the bootloader configuration area.
uint32_t calculate_application_crc32(crc_checksum_header_t *header, uint32_t crcHeaderStart)
{
    uint32_t crc32;

    // Initialize the CRC32 information
    crc32_data_t crcInfo;
    crc32_init(&crcInfo);

    // Run CRC, Considering skip crcExpectedValue address
    uint32_t bypassStartAddress = crcHeaderStart + ((uint32_t)&header->crcExpectedValue - (uint32_t)&header->tag);
    uint32_t bypassEndAddress = bypassStartAddress + sizeof(header->crcExpectedValue);

    if ((header->crcStartAddress >= bypassEndAddress) ||
        (header->crcStartAddress + header->crcByteCount <= bypassStartAddress))
    {
        crc32_update(&crcInfo, (uint8_t *)header->crcStartAddress, header->crcByteCount);
    }
    else
    {
        // Assume that crcExpectedValue address (4 byte) resides in crc addresses completely
        crc32_update(&crcInfo, (uint8_t *)header->crcStartAddress, bypassStartAddress - header->crcStartAddress);
        crc32_update(&crcInfo, (uint8_t *)bypassEndAddress,
                     header->crcStartAddress + header->crcByteCount - bypassEndAddress);
    }

    // Finalize the CRC calculations
    crc32_finalize(&crcInfo, &crc32);

    return crc32;
}

//! @brief Check if crc check addresses reside in the range of valid memory space (Pflash or QSPIflash)
static bool is_crc_check_address_valid(bootloader_configuration_data_t *config)
{
    bool isAddressValid;

    // Check if crc byte count is not equal to zero and crc end address does't exceed 4G address space
    isAddressValid = (config->crcByteCount != 0) && (config->crcStartAddress <= 0xffffffff - config->crcByteCount + 1);

    // Check if addresses reside in internal flash
    const memory_map_entry_t *map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexFlashArray];
    if (isAddressValid)
    {
        isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                          (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
#if BL_FEATURE_QSPI_MODULE
        // Check if addresses reside in external QSPI flash
        if ((!isAddressValid) && is_qspi_present())
        {
            map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexQspiMemory];

            isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                              (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
        }
#endif // BL_FEATURE_QSPI_MODULE
    }

    return isAddressValid;
}

// See bl_app_crc_check.h for documentation on this function.
bool is_application_crc_check_pass(void)
{
    bool isCrcCheckPassed = true;

    property_store_t *propertyStore = g_bootloaderContext.propertyInterface->store;
    if (kStatus_AppCrcCheckInvalid != propertyStore->crcCheckStatus)
    {
        isCrcCheckPassed = false;

        // Check if crc check addresses reside in the range of valid memory space (Pflash or QSPIflash)
        if (is_crc_check_address_valid(&propertyStore->configurationData))
        {
            uint32_t calculated_crc = calculate_application_crc32(
                (crc_checksum_header_t *)&propertyStore->configurationData, kBootloaderConfigAreaAddress);

            if (calculated_crc != propertyStore->configurationData.crcExpectedValue)
            {
                propertyStore->crcCheckStatus = kStatus_AppCrcCheckFailed;
            }
            else
            {
                isCrcCheckPassed = true;
                propertyStore->crcCheckStatus = kStatus_AppCrcCheckPassed;
            }
        }
        else
        {
            propertyStore->crcCheckStatus = kStatus_AppCrcCheckOutOfRange;
        }
#if BL_FEATURE_CRC_ASSERT
        if (!isCrcCheckPassed)
        {
            assert_pin_to_indicate_crc_check_failure();
        }
#endif
    }

    return isCrcCheckPassed;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
