/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _property_h
#define _property_h

#include <stdint.h>
#include "bootloader_common.h"
#include "packet/command_packet.h"
#include "fsl_device_registers.h"
#include "utilities/vector_table_info.h"

//! @addtogroup property
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @name Command Availability
//@{

//! Sets a bit in the available commands property value to indicate a command with
//! the given tag is available.
#define HAS_CMD(tag) (1 << ((tag)-kFirstCommandTag))

//! Checks whether a command with the specified tag is present in the provided command
//! availability mask.
#define IS_CMD_AVAILABLE(mask, tag) (((mask)&HAS_CMD(tag)) != 0)

enum _available_commands
{
    kAvailableCommands = (
#if !BL_FEATURE_MIN_PROFILE
        HAS_CMD(kCommandTag_FlashEraseAll) | HAS_CMD(kCommandTag_FlashEraseRegion) | HAS_CMD(kCommandTag_WriteMemory)
#if BL_FEATURE_FLASH_SECURITY
        |
        HAS_CMD(kCommandTag_FlashSecurityDisable)
#endif // BL_FEATURE_ERASEALL_UNSECURE
        |
        HAS_CMD(kCommandTag_GetProperty) | HAS_CMD(kCommandTag_Execute) | HAS_CMD(kCommandTag_Reset) |
        HAS_CMD(kCommandTag_SetProperty) | HAS_CMD(kCommandTag_ReadMemory) | HAS_CMD(kCommandTag_FillMemory) |
        HAS_CMD(kCommandTag_ReceiveSbFile) | HAS_CMD(kCommandTag_Call)
#if BL_FEATURE_ERASEALL_UNSECURE
        |
        HAS_CMD(kCommandTag_FlashEraseAllUnsecure)
#endif // BL_FEATURE_ERASEALL_UNSECURE
#if (((!BL_FEATURE_HAS_NO_INTERNAL_FLASH) || BL_FEATURE_OCOTP_MODULE) && (!BL_DEVICE_IS_LPC_SERIES))|| \
    ((BL_DEVICE_IS_LPC_SERIES) && defined(OTP_API))
        |
        HAS_CMD(kCommandTag_FlashReadOnce) | HAS_CMD(kCommandTag_FlashProgramOnce)
#endif // (((!BL_FEATURE_HAS_NO_INTERNAL_FLASH) || BL_FEATURE_OCOTP_MODULE) && (!BL_DEVICE_IS_LPC_SERIES))|| ((BL_DEVICE_IS_LPC_SERIES) && defined(OTP_API))
#if !BL_FEATURE_HAS_NO_READ_SOURCE
        |
        HAS_CMD(kCommandTag_FlashReadResource)
#endif // !BL_FEATURE_HAS_NO_READ_SOURCE
#if BL_FEATURE_QSPI_MODULE || BL_FEATURE_FLEXSPI_NOR_MODULE || BL_FEATURE_SEMC_NOR_MODULE || \
    BL_FEATURE_EXPAND_MEMORY || BL_FEATURE_SPI_NOR_EEPROM_MODULE || BL_FEATURE_SPIFI_NOR_MODULE
        |
        HAS_CMD(kCommandTag_ConfigureMemory)
#endif // BL_FEATURE_QSPI_MODULE || BL_FEATURE_FLEXSPI_NOR_MODULE || BL_FEATURE_SEMC_NOR_MODULE || BL_FEATURE_EXPAND_MEMORY || BL_FEATURE_SPI_NOR_EEPROM_MODULE || BL_FEATURE_SPIFI_NOR_MODULE
#if BL_FEATURE_RELIABLE_UPDATE
        |
        HAS_CMD(kCommandTag_ReliableUpdate)
#endif // BL_FEATURE_RELIABLE_UPDATE
#if BL_FEATURE_GEN_KEYBLOB
        |
        HAS_CMD(kCommandTag_GenerateKeyBlob)
#endif // BL_FEATURE_GEN_KEYBLOB
#if BL_FEATURE_KEY_PROVISIONING
        |
        HAS_CMD(kCommandTag_KeyProvisioning)
#endif
#else // BL_FEATURE_MIN_PROFILE
        HAS_CMD(kCommandTag_FlashEraseAll) | HAS_CMD(kCommandTag_FlashEraseRegion) | HAS_CMD(kCommandTag_WriteMemory)
#if BL_FEATURE_FLASH_SECURITY
        |
        HAS_CMD(kCommandTag_FlashSecurityDisable)
#endif // BL_FEATURE_FLASH_SECURITY
        |
        HAS_CMD(kCommandTag_GetProperty) | HAS_CMD(kCommandTag_Execute) | HAS_CMD(kCommandTag_Reset) |
        HAS_CMD(kCommandTag_SetProperty)
#if BL_FEATURE_READ_MEMORY
        |
        HAS_CMD(kCommandTag_ReadMemory)
#endif // BL_FEATURE_READ_MEMORY
#if BL_FEATURE_FILL_MEMORY
        |
        HAS_CMD(kCommandTag_FillMemory)
#endif // BL_FEATURE_FILL_MEMORY
#if BL_FEATURE_ERASEALL_UNSECURE
        |
        HAS_CMD(kCommandTag_FlashEraseAllUnsecure)
#endif // BL_FEATURE_ERASEALL_UNSECURE
#endif // BL_FEATURE_MIN_PROFILE
            )
};

//@}

//! @brief Property store status codes.
enum _property_errors
{
    kStatus_UnknownProperty = MAKE_STATUS(kStatusGroup_PropertyStore, 0),
    kStatus_ReadOnlyProperty = MAKE_STATUS(kStatusGroup_PropertyStore, 1),    //!< Property is read-only.
    kStatus_InvalidPropertyValue = MAKE_STATUS(kStatusGroup_PropertyStore, 2) //!< Property value is out of range.
};

//! @brief Property tags.
//! @note Do not change any tag values. Add tags at the end.
enum _property_tag
{
    kPropertyTag_ListProperties = 0x00,
    kPropertyTag_BootloaderVersion = 0x01,
    kPropertyTag_AvailablePeripherals = 0x02,
    kPropertyTag_FlashStartAddress = 0x03,
    kPropertyTag_FlashSizeInBytes = 0x04,
    kPropertyTag_FlashSectorSize = 0x05,
    kPropertyTag_FlashBlockCount = 0x06,
    kPropertyTag_AvailableCommands = 0x07,
    kPropertyTag_CrcCheckStatus = 0x08,
    kPropertyTag_Reserved9 = 0x09,
    kPropertyTag_VerifyWrites = 0x0a,
    kPropertyTag_MaxPacketSize = 0x0b,
    kPropertyTag_ReservedRegions = 0x0c,
    kPropertyTag_Reserved13 = 0x0d,
    kPropertyTag_RAMStartAddress = 0x0e,
    kPropertyTag_RAMSizeInBytes = 0x0f,
    kPropertyTag_SystemDeviceId = 0x10,
    kPropertyTag_FlashSecurityState = 0x11,
    kPropertyTag_UniqueDeviceId = 0x12,
    kPropertyTag_FacSupport = 0x13,
    kPropertyTag_FlashAccessSegmentSize = 0x14,
    kPropertyTag_FlashAccessSegmentCount = 0x15,
    kPropertyTag_FlashReadMargin = 0x16,
    kPropertyTag_QspiInitStatus = 0x17,
    kPropertyTag_TargetVersion = 0x18,
    kPropertyTag_ExternalMemoryAttributes = 0x19,
    kPropertyTag_ReliableUpdateStatus = 0x1a,
    kPropertyTag_FlashPageSize = 0x1b,
    kPropertyTag_InvalidProperty = 0xFF,
};

//! @brief Property constants.
enum _property_constants
{
    kProperty_ReservedRegionsCount = 2,
    kProperty_FlashReservedRegionIndex = 0,
    kProperty_RamReservedRegionIndex = 1,

    kProperty_FlashVersionIdSizeInBytes = 8,
};

//! @brief Bit positions for clock flags in configuration data.
enum _clock_flags
{
    kClockFlag_HighSpeed = (1 << 0)
};

//! @brief Bit positions for boot flags in configuration data
enum _boot_flags
{
    kBootFlag_DirectBoot = (1 << 0)
};

//! @brief Flash constants.
enum _flash_constants
{
    //! @brief The bootloader configuration data location .
    //!
    //! A User Application should populate a BootloaderConfigurationData
    //! struct at 0x3c0 from the beginning of the application image which must
    //! be the User Application vector table for the flash-resident bootloader
    //! collaboration.
    kBootloaderConfigAreaAddress = (uint32_t)(APP_VECTOR_TABLE) + 0x3c0,
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)
#if BL_FEATURE_SUPPORT_DFLASH
    kFLASHCount = 3,
#else 
    kFLASHCount = 2,
#endif // BL_FEATURE_SUPPORT_DFLASH 
#else   
#if BL_FEATURE_SUPPORT_DFLASH
    kFLASHCount = 2,
#else    
    kFLASHCount = 1,
#endif // BL_FEATURE_SUPPORT_DFLASH   
#endif    
};

//!@brief Unique ID constants
enum _uid_constrants
{
    kUid_MaxSizeInbytes = 16,
};

//! @brief Format of bootloader configuration data on Flash.
typedef struct BootloaderConfigurationData
{
    uint32_t tag; //!< [00:03] Tag value used to validate the bootloader configuration data. Must be set to 'kcfg'.
    uint32_t crcStartAddress;              //!< [04:07]
    uint32_t crcByteCount;                 //!< [08:0b]
    uint32_t crcExpectedValue;             //!< [0c:0f]
    uint8_t enabledPeripherals;            //!< [10:10]
    uint8_t i2cSlaveAddress;               //!< [11:11]
    uint16_t peripheralDetectionTimeoutMs; //!< [12:13] Timeout in milliseconds for peripheral detection before jumping
    //! to application code
    uint16_t usbVid;                    //!< [14:15]
    uint16_t usbPid;                    //!< [16:17]
    uint32_t usbStringsPointer;         //!< [18:1b]
    uint8_t clockFlags;                 //!< [1c:1c] High Speed and other clock options
    uint8_t clockDivider;               //!< [1d:1d] One's complement of clock divider, zero divider is divide by 1
    uint8_t bootFlags;                  //!< [1e:1e] One's complemnt of direct boot flag, 0xFE represents direct boot
    uint8_t pad0;                       //!< [1f:1f] Reserved, set to 0xFF
    uint32_t mmcauConfigPointer;        //!< [20:23] Holds a pointer value to the MMCAU configuration
    uint32_t keyBlobPointer;            //!< [24:27] Holds a pointer value to the key blob array used to configure OTFAD
    uint8_t qspiPort;                   //!< [28:28] qspi port: 0xFF-PORTE, 0xFE-PORTC
    uint8_t canConfig1;                 //!< [29:29] ClkSel[1], PropSeg[3], SpeedIndex[4]
    uint16_t canConfig2;                //!< [2a:2b] Pdiv[8], Pseg1[3], Pseg2[3],  rjw[2]
    uint16_t canTxId;                   //!< [2c:2d] txId
    uint16_t canRxId;                   //!< [2e:2f] rxId
    uint32_t qspi_config_block_pointer; //!< [30:33] QSPI config block pointer.
} bootloader_configuration_data_t;

//! @brief Structure of a reserved regions entry.
typedef struct ReservedRegion
{
    uint32_t startAddress;
    uint32_t endAddress;
} reserved_region_t;

//! @brief Structure of a unique device id.
typedef struct UniqueDeviceId
{
    uint32_t uid[kUid_MaxSizeInbytes / sizeof(uint32_t)];
} unique_device_id_t;

//! @brief External Memory Properties tag
enum _external_memory_property_tags
{
    kExternalMemoryPropertyTag_InitStatus = 0,         //!< Init status tag
    kExternalMemoryPropertyTag_StartAddress = 1,       //!< Start address tag
    kExternalMemoryPropertyTag_MemorySizeInKbytes = 2, //!< Memory size tag
    kExternalMemoryPropertyTag_PageSize = 3,           //!< Pag size tag
    kExternalMemoryPropertyTag_SectorSize = 4,         //!< Sector size tag
    kExternalMemoryPropertyTag_BlockSize = 5,          //!< Block size tag

    kExternalMemoryPropertyTag_Start = kExternalMemoryPropertyTag_StartAddress,
    kExternalMemoryPropertyTag_End = kExternalMemoryPropertyTag_BlockSize,
};

//! @brief Exernal Memory attribute store
typedef struct
{
    uint32_t availableAttributesFlag; //!< Available Atrributes, bit map
    uint32_t startAddress;            //!< start Address of external memory
    uint32_t flashSizeInKB;           //!< flash size of external memory
    uint32_t pageSize;                //!< page size of external memory
    uint32_t sectorSize;              //!< sector size of external memory
    uint32_t blockSize;               //!< block size of external memory
} external_memory_property_store_t;

enum _ram_constants
{
#if CPU_IS_ARM_CORTEX_M7
    kRAMCount = 3,
#elif defined(K28F15_SERIES)
    kRAMCount = 2,
#elif BL_FEATURE_MULTI_SRAM_SECTIONS
    kRAMCount = kRAMSections,
#else
    kRAMCount = 1,
#endif

    kPropertyIndex_SRAM = 0,
#if defined(K28F15_SERIES)
    kPropertyIndex_OCRAM = 1,
#elif CPU_IS_ARM_CORTEX_M7

    kPropertyIndex_DTCM = 1,
    kPropertyIndex_OCRAM = 2,
#endif
};

//! @brief Structure of property store.
typedef struct PropertyStore
{
    standard_version_t bootloaderVersion;     //!< Current bootloader version.
    standard_version_t serialProtocolVersion; //!< Serial protocol version number.
    standard_version_t targetVersion;         //!< Target version number.
    uint32_t availablePeripherals;            //!< The set of peripherals supported available on this chip. See enum
                                              //!_peripheral_types in bl_peripheral.h.
    uint32_t flashStartAddress[kFLASHCount];  //!< Start address of program flash.
    uint32_t flashSizeInBytes[kFLASHCount];   //!< Size in bytes of program flash.
    uint32_t flashPageSize[kFLASHCount];      //!< The size in bytes of one page of program flash. This is the minimum
                                              //!program size of LPC device.
    uint32_t flashSectorSize[kFLASHCount];    //!< The size in bytes of one sector of program flash. This is the minimum
    //! erase size.
    uint32_t flashBlockSize[kFLASHCount];  //!< The size in bytes of one block of program flash.
    uint32_t flashBlockCount[kFLASHCount]; //!< Number of blocks in the flash array.
    uint32_t ramStartAddress[kRAMCount];   //!< Start address of RAM
    uint32_t ramSizeInBytes[kRAMCount];    //!< Size in bytes of RAM
    uint32_t crcCheckStatus;               //!< Status code from the last CRC check operation.
    uint32_t verifyWrites; //!< Boolean controlling whether the bootloader will verify writes to flash. Non-zero enables
    //! verificaton. Writable by host.
    uint32_t availableCommands;                    //!< Bit mask of the available commands.
    unique_device_id_t UniqueDeviceId;             //!< Unique identification for the device.
    uint32_t flashFacSupport[kFLASHCount];         //!< Boolean indicating whether the FAC feature is supported
    uint32_t flashAccessSegmentSize[kFLASHCount];  //!< The size in bytes of one segment of flash
    uint32_t flashAccessSegmentCount[kFLASHCount]; //!< The count of flash access segment within flash module
    uint32_t flashReadMargin;                      //!< The margin level setting for flash erase and program Verify CMDs
    uint32_t qspiInitStatus;                       //!< Result of QSPI+OTFAD init during bootloader startup
    reserved_region_t reservedRegions[kProperty_ReservedRegionsCount]; //!< Flash and Ram reserved regions.
    bootloader_configuration_data_t
        configurationData; //!< Configuration data from flash address 0x3c0-0x3ff in sector 0 (64 bytes max)
    external_memory_property_store_t externalMemoryPropertyStore; //!< Property store for external memory
    uint32_t reliableUpdateStatus;                                //!< Status of reliable update
} property_store_t;

enum _property_store_tags
{
    //! @brief Tag value used to validate the bootloader configuration data.
    kPropertyStoreTag = FOUR_CHAR_CODE('k', 'c', 'f', 'g')
};

//! @brief External Memory properties interface
typedef struct ExternalMemoryPropertyInterface
{
    uint32_t memoryId;
    status_t (*get)(uint32_t tag, uint32_t *value);
} external_memory_property_interface_t;

//! @brief Interface to property operations.
typedef struct PropertyInterface
{
    status_t (*load_user_config)(void); //!< Load the user configuration data
    status_t (*init)(void);             //!< Initialize
    status_t (*get)(uint8_t tag, uint32_t id, const void **value, uint32_t *valueSize); //!< Get property
    status_t (*set_uint32)(uint8_t tag, uint32_t value);                                //!< Set uint32_t property
    property_store_t *store;                                                            //!< The property store
} property_interface_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @brief Property interface.
extern const property_interface_t g_propertyInterface;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C" {
#endif

//! @name Property Store
//@{

//! @brief Early initialization function to get user configuration data
status_t bootloader_property_load_user_config(void);

//! @brief Initialize the property store.
status_t bootloader_property_init(void);

//! @brief Get a property.
//!
//! Example calling sequence for uint32_t property:
//! @code
//! void * value;
//! uint32_t valueSize;
//! status_t status = bootloader_property_get(sometag, &value, &valueSize);
//! uint32_t result = *(uint32_t *)value;
//! @endcode
//!
//! @param tag Tag of the requested property
//! @param memoryId Id for specified external memory, for example: 1 represent QuadSPI 0
//! @param value Pointer to where to write a pointer to the result, may be NULL
//! @param valueSize Size in bytes of the property value, may be NULL
//!
//! @retval kStatus_Success
//! @retval kStatus_UnknownProperty
status_t bootloader_property_get(uint8_t tag, uint32_t memoryId, const void **value, uint32_t *valueSize);

//! @brief Set a property.
//!
//! Only uint32_t properties can be set with this function.
//!
//! @param tag Tag of the property to set
//! @param value New property value
//!
//! @retval kStatus_Success
//! @retval kStatus_UnknownProperty
//! @retval kStatus_ReadOnlyProperty
status_t bootloader_property_set_uint32(uint8_t tag, uint32_t value);

//@}

#if __cplusplus
}
#endif

//! @}

#endif // _property_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
