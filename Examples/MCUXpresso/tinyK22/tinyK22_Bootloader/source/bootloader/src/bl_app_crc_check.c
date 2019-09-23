/*
 * Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
    CRC_CHECK_FAILURE_PIN_PORT->PCR[CRC_CHECK_FAILURE_PIN_NUMBER] = PORT_PCR_MUX(CRC_CHECK_FAILURE_PIN_GPIO_MODE);
    // Set pin as output
    CRC_CHECK_FAILURE_PIN_GPIO->PDDR |= ( 1 << CRC_CHECK_FAILURE_PIN_NUMBER);
    // Toggle pin (the inverse of default logic state) for crc check failure
    CRC_CHECK_FAILURE_PIN_GPIO->PTOR = 1 << CRC_CHECK_FAILURE_PIN_NUMBER;
}

// See bl_app_crc_check.h for documentation on this function.
void restore_crc_check_failure_pin(void)
{
    // Restore crc check failure pin to default state
    if ((CRC_CHECK_FAILURE_PIN_PORT->PCR[CRC_CHECK_FAILURE_PIN_NUMBER] & PORT_PCR_MUX_MASK) == PORT_PCR_MUX(CRC_CHECK_FAILURE_PIN_GPIO_MODE))
    {
        // Restore pin as input
        CRC_CHECK_FAILURE_PIN_GPIO->PDDR &= ~(1 << CRC_CHECK_FAILURE_PIN_NUMBER);
        // Restore pin as default muxing slot mode
        CRC_CHECK_FAILURE_PIN_PORT->PCR[CRC_CHECK_FAILURE_PIN_NUMBER] = PORT_PCR_MUX(CRC_CHECK_FAILURE_PIN_DEFAULT_MODE);
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
    if (!isAddressValid)
    {
        return isAddressValid;
    }

    const memory_map_entry_t *map;
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
    // Check if addresses reside in internal flash
    map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexFlashArray];
    isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                      (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
#else
    isAddressValid = false;
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH

#if BL_FEATURE_QSPI_MODULE
    // Check if addresses reside in external QSPI flash
    if ((!isAddressValid) && is_qspi_present())
    {
        map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexQspiMemory];

        isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                          (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
    }
#endif // BL_FEATURE_QSPI_MODULE
#if BL_FEATURE_FLEXSPI_NOR_MODULE
    // Check if addresses reside in external FlexSPI NOR flash
    if ((!isAddressValid) && is_flexspi_nor_present())
    {
        map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexFlexSpiNor];

        isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                          (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
#if BL_FEATURE_FLEXSPI_ALIAS_AREA
        if (!isAddressValid)
        {
            map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexFlexSpiNorAlias];

            isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                              (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
        }
#endif // #if BL_FEATURE_FLEXSPI_ALIAS_AREA
    }
#endif // #if BL_FEATURE_FLEXSPI_NOR_MODULE
#if BL_FEATURE_SEMC_NOR_MODULE
    // Check if addresses reside in external SEMC NOR flash
    if ((!isAddressValid) && is_semc_nor_present())
    {
        map = (const memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexSemcNor];

        isAddressValid = ((config->crcStartAddress >= map->startAddress) &&
                          (config->crcStartAddress + config->crcByteCount - 1 <= map->endAddress));
    }
#endif // #if BL_FEATURE_SEMC_NOR_MODULE
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
