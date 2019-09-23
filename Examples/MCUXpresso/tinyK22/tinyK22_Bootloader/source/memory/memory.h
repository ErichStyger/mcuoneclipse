/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _memory_h
#define _memory_h

#include <stdint.h>
#include "bootloader_common.h"

//! @addtogroup memif
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Bit mask for device ID.
#define DEVICE_ID_MASK 0xff
//! @brief Bit position of device ID.
#define DEVICE_ID_SHIFT 0
//! @brief Bit mask for group ID.
#define GROUP_ID_MASK 0xf00
//! @brief Bit position of group ID.
#define GROUP_ID_SHIFT 8

/*! @brief Construct a memory ID from a given group ID and device ID. */
#define MAKE_MEMORYID(group, device) \
    ((((group) << GROUP_ID_SHIFT) & GROUP_ID_MASK) | (((device) << DEVICE_ID_SHIFT) & DEVICE_ID_MASK))
/*! @brief Get group ID from a given memory ID. */
#define GROUPID(memoryId) (((memoryId)&GROUP_ID_MASK) >> GROUP_ID_SHIFT)

/*! @brief Get device ID from a given memory ID. */
#define DEVICEID(memoryId) (((memoryId)&DEVICE_ID_MASK) >> DEVICE_ID_SHIFT)

/*! @brief Memory group definition. */
enum _bl_memory_groups
{
    kGroup_Internal = 0, //!<  Kinetis internal 4G memory region.
    kGroup_External = 1, //!<  Kinetis external memory region.
    kGroup_AES_OTP = 2,
};

/*! @brief Memory device ID definition. */
enum _bl_memory_id
{
    /*  Memory ID bitfiled definition.
        | 11 | 10 | 9 |    8    |  7   |  6   |  5   |  4  |  3   |  2   |  1  |  0  |
        |  Reserved   | INT/EXT | Type                     | Sub-Type                |
        |             | 0: INT  | INT:                     |                         |
        |             | 1: EXT  | 0: NorFlash0             | 0: Internal Flash(FTFX) |
        |             |         |                          | 1: QSPI                 |
        |             |         |                          | 4: IFR                  |
        |             |         |                          | 8: SEMC                 |
        |             |         |                          | 9: FlexSPI              |
        |             |         |                          | A: SPIFI                |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 1: ExecuteOnlyRegion     | 0: Internal Flash(FTFX) |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | others: Unused           |                         |
        |             |         |                          |                         |
        |             |         | EXT:                     |                         |
        |             |         | 0: NandFlash             | 0: SEMC                 |
        |             |         |                          | 1: FlexSPI              |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 1: NorFlash/EEPROM       | 0: LPSPI                |
        |             |         |                          | 1: LPI2C                |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 2: SD/SDHC/SDXC/MMC/eMMC | 0: uSDHC SD             |
        |             |         |                          | 1: uSDHC MMC            |
        |             |         |                          | others: Unused          |
        |             |         | others: Unused           |                         |

        INT : Internal 4G memory, including internal memory modules, and XIP external memory modules.
        EXT : Non-XIP external memory modules.
    */
    kMemoryInternal = MAKE_MEMORYID(kGroup_Internal, 0),  // Internal memory (include all on chip memory)
    kMemoryQuadSpi0 = MAKE_MEMORYID(kGroup_Internal, 1),  // Qsuad SPI memory 0
    kMemoryIFR0_Fuse = MAKE_MEMORYID(kGroup_Internal, 4), // Nonvolatile information register 0. Only used by SB loader.
    kMemorySemcNor = MAKE_MEMORYID(kGroup_Internal, 8),   // SEMC Nor memory
    kMemoryFlexSpiNor = MAKE_MEMORYID(kGroup_Internal, 9),          // Flex SPI Nor memory
    kMemorySpifiNor = MAKE_MEMORYID(kGroup_Internal, 0xA),          // SPIFI Nor memory
    kMemoryFlashExecuteOnly = MAKE_MEMORYID(kGroup_Internal, 0x10), // Execute-only region on internal Flash

    kMemorySemcNand = MAKE_MEMORYID(kGroup_External, 0),        // SEMC NAND memory
    kMemorySpiNand = MAKE_MEMORYID(kGroup_External, 1),         // SPI NAND memory
    kMemorySpiNorEeprom = MAKE_MEMORYID(kGroup_External, 0x10), // SPI NOR/EEPROM memory
    kMemoryI2cNorEeprom = MAKE_MEMORYID(kGroup_External, 0x11), // I2C NOR/EEPROM memory
    kMemorySDCard = MAKE_MEMORYID(kGroup_External, 0x20),       // eSD, SD, SDHC, SDXC memory Card
    kMemoryMMCCard = MAKE_MEMORYID(kGroup_External, 0x21),      // MMC, eMMC memory Card
    //
};

//! @brief Memory interface status codes.
enum _memory_interface_status
{
    kStatusMemoryRangeInvalid = MAKE_STATUS(kStatusGroup_MemoryInterface, 0),
    kStatusMemoryReadFailed = MAKE_STATUS(kStatusGroup_MemoryInterface, 1),
    kStatusMemoryWriteFailed = MAKE_STATUS(kStatusGroup_MemoryInterface, 2),
    kStatusMemoryCumulativeWrite = MAKE_STATUS(kStatusGroup_MemoryInterface, 3),
    kStatusMemoryAppOverlapWithExecuteOnlyRegion = MAKE_STATUS(kStatusGroup_MemoryInterface, 4),
    kStatusMemoryNotConfigured = MAKE_STATUS(kStatusGroup_MemoryInterface, 5),
    kStatusMemoryAlignmentError = MAKE_STATUS(kStatusGroup_MemoryInterface, 6),
    kStatusMemoryVerifyFailed = MAKE_STATUS(kStatusGroup_MemoryInterface, 7),
    kStatusMemoryWriteProtected = MAKE_STATUS(kStatusGroup_MemoryInterface, 8),
    kStatusMemoryAddressError = MAKE_STATUS(kStatusGroup_MemoryInterface, 9),
    kStatusMemoryBlankCheckFailed = MAKE_STATUS(kStatusGroup_MemoryInterface, 10),
    kStatusMemoryBlankPageReadDisallowed = MAKE_STATUS(kStatusGroup_MemoryInterface, 11),
    kStatusMemoryProtectedPageReadDisallowed = MAKE_STATUS(kStatusGroup_MemoryInterface, 12),
    kStatusMemoryUnsupportedCommand = MAKE_STATUS(kStatusGroup_MemoryInterface, 13),
};

// !@brief Memory property enum codes
enum
{
    /* Memory property bitfield definition.
     * Bit[0]: 0 -- NotExecutable( None-XIP)
     *         1 -- Executable(XIP)
     * Bit[1] : Reserved.(Reserved for Int/Ext. 0 Internal, 1 External)
     * Bit[3:2] : Reserved.
     * Bit[7:4] : 0000 -- FLASH.
     *            0001 -- RAM.
     *            0010 -- Device.
     *            0100 -- Reserved.
     *            1000 -- Reserved.
     * Bit[15-8] : Reserved.
     * Bit[16] : Reserved.(Reserved for Bufferable. 0 Not bufferable, 1 Bufferable)
     * Bit[17] : Reserved.(Reserved for Cacheable. 0 Not cacheable, 1 Cacheable)
     * Bit[18] : Reserved.(Reserved for Shareable. 0 Not shareable, 1 Shareable)
     * Bit[31-19] : Reserved.
     */
    kMemoryNotExecutable = 0,  //!< The memory doesn't support executing in place.
    kMemoryIsExecutable = 1,   //!< The memory supports executing in place.
    kMemoryType_FLASH = 0x00,  //!< The memory is FLASH device
    kMemoryType_RAM = 0x10,    //!< The memory is RAM device
    kMemoryType_Device = 0x20, //!< The memory is device register
};

//! @brief Interface to memory operations.
//!
//! This is the main abstract interface to all memory operations.
typedef struct _memory_interface
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer, uint32_t memoryId);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer, uint32_t memoryId);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*finalize)(void);
    status_t (*erase)(uint32_t address, uint32_t length, uint32_t memoryId);
} memory_interface_t;

//! @brief Interface to memory operations for one region of memory.
typedef struct _memory_region_interface
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*erase)(uint32_t address, uint32_t length);
} memory_region_interface_t;

//! @brief Structure of a memory map entry.
typedef struct _memory_map_entry
{
    uint32_t startAddress;
    uint32_t endAddress;
    uint32_t memoryProperty;
    const memory_region_interface_t *memoryInterface;
} memory_map_entry_t;

#if BL_FEATURE_EXPAND_MEMORY

typedef struct _external_memory_region_interface
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer);
    status_t (*erase)(uint32_t address, uint32_t length);
    status_t (*config)(uint32_t *buffer);
    status_t (*flush)(void);
    status_t (*finalize)(void);
} external_memory_region_interface_t;

typedef struct _external_memory_map_entry
{
    uint32_t memoryId;
    uint32_t status;
    uint32_t basicUnitCount;
    uint32_t basicUnitSize;
    const external_memory_region_interface_t *memoryInterface;
} external_memory_map_entry_t;
#endif // BL_FEATURE_EXPAND_MEMORY

//! @brief Memory Map index constants
enum _memorymap_constants
{
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
    kIndexFlashArray = 0,
    kIndexSRAM = 1,
#if BL_FEATURE_SUPPORT_DFLASH
    kIndexDFlashArray = 2,
#endif    
#if CPU_IS_ARM_CORTEX_M7
    kIndexDTCM = 2,
    kIndexOCRAM = 3,
#endif // CPU_IS_ARM_CORTEX_M7
#if defined(K28F15_SERIES)
    kIndexOCRAM = 4,
#endif
#else
    kIndexSRAM = 0,
#if CPU_IS_ARM_CORTEX_M7
    kIndexDTCM = 1,
    kIndexOCRAM = 2,
#endif // CPU_IS_ARM_CORTEX_M7
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if BL_FEATURE_FLEXSPI_NOR_MODULE
    kIndexFlexSpiNor = 3,
    kIndexFlexSpiNorAlias = 4,
#endif // #if BL_FEATURE_FLEXSPI_NOR_MODULE
#if BL_FEATURE_SPIFI_NOR_MODULE
    kIndexSpifiNor = 5,
#endif // #if BL_FEATURE_SPIFI_NOR_MODULE
#if BL_FEATURE_SEMC_NOR_MODULE
    kIndexSemcNor = 4,
#endif // #if BL_FEATURE_SEMC_NOR_MODULE
#if BL_FEATURE_QSPI_MODULE
    kIndexQspiMemory = 2,
    kIndexQspiAliasArea = 3,
#endif // BL_FEATURE_QSPI_MODULE
    kSRAMSeparatrix = (uint32_t)0x20000000 //!< This value is the start address of SRAM_U
};

#if BL_FEATURE_EXPAND_MEMORY
enum _external_memorymap_constants
{
    kIndexStart = 0,
    // Never add index for external memory map.
    // Because external memories don't have fixed indexes,
    // and are changed by bootloader configuration.
    // Please call find_external_map_index() to get the correct index.
};
#endif // BL_FEATURE_EXPAND_MEMORY

//! @brief flash memory erase all options.
typedef enum _flash_erase_all_option
{
    kFlashEraseAllOption_Blocks = 0,
    kFlashEraseAllOption_ExecuteOnlySegments = 1
} flash_erase_all_option_t;

//! @brief Flash index constants.
enum _flash_index_constants
{
    kFlashIndex_Main = 0,
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)    
    kFlashIndex_Secondary = 1,
#if BL_FEATURE_SUPPORT_DFLASH    
    kFalshIndex_DFlash = 2
#endif // BL_FEATURE_SUPPORT_DFLASH
#else
#if BL_FEATURE_SUPPORT_DFLASH   
    kFalshIndex_DFlash = 1 
#endif // BL_FEATURE_SUPPORT_DFLASH      
#endif //  defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)    
};

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory map for the system.
extern memory_map_entry_t g_memoryMap[];

//! @brief External memory map for the system.
#if BL_FEATURE_EXPAND_MEMORY
extern external_memory_map_entry_t g_externalMemoryMap[];
#endif // BL_FEATURE_EXPAND_MEMORY

//! @name Memory interfaces
//@{

//! @brief Abstract memory interface.
//!
//! This interface utilizes the memory map to perform different memory operations
//! depending on the region of memory being accessed.
extern const memory_interface_t g_memoryInterface;

#if !BL_DEVICE_IS_LPC_SERIES
//! @brief Kinetis Main Flash memory interface.
extern const memory_region_interface_t g_flashMemoryInterface;
#else
//! @brief LPC Main Flash memory interface.
extern const memory_region_interface_t g_flashiapMemoryInterface;
#endif

#if BL_FEATURE_SUPPORT_DFLASH
extern const memory_region_interface_t g_dFlashMemoryInterface;
#endif

#if BL_HAS_SECONDARY_INTERNAL_FLASH
//! @brief Secondary Flash memory interface.
extern const memory_region_interface_t g_secondaryFlashMemoryInterface;
#endif

//! @brief Memory interface for memory with Normal type.
//!
//! Use of multiword loads and stores is allowed with this memory type.
extern const memory_region_interface_t g_normalMemoryInterface;

#if CPU_IS_ARM_CORTEX_M7
//! @brief Memory interface for memory with Normal type.
//!
//! Use of multiword loads and stores is allowed with this memory type.
extern const memory_region_interface_t g_normalDTCMInterface;
#endif // CPU_IS_ARM_CORTEX_M7

#if defined(CPU_IS_CORTEX_M7) || defined(K28F15_SERIES)
//! @brief Memory interface for memory with Normal type.
//!
//! Use of multiword loads and stores is allowed with this memory type.
extern const memory_region_interface_t g_normalOCRAMInterface;
#endif // defined(CPU_IS_CORTEX_M7) || defined(K28F15_SERIES)

//! @brief Memory interface for memory with Device or Strongly-ordered type.
//!
//! This memory type does not support multiword loads and stores.
extern const memory_region_interface_t g_deviceMemoryInterface;

#if defined BL_FEATURE_QSPI_MODULE
extern const memory_region_interface_t g_qspiMemoryInterface;
#if BL_FEATURE_QSPI_ALIAS_AREA
extern const memory_region_interface_t g_qspiAliasAreaInterface;
#endif // BL_FEATURE_QSPI_ALIAS_AREA
#endif // BL_FEATURE_QSPI_MODULE

#if BL_FEATURE_FLEXSPI_NOR_MODULE
extern const memory_region_interface_t g_flexspiMemoryInterface;
#if BL_FEATURE_FLEXSPI_ALIAS_AREA
extern const memory_region_interface_t g_flexspiAliasAreaInterface;
#endif // #if BL_FEATURE_FLEXSPI_ALIAS_AREA
#endif // #if BL_FEATURE_FLEXSPI_NOR_MODULE

#if BL_FEATURE_SPIFI_NOR_MODULE
extern const memory_region_interface_t g_spifiMemoryInterface;
#endif // #if BL_FEATURE_SPIFI_NOR_MODULE

#if BL_FEATURE_SEMC_NOR_MODULE
extern const memory_region_interface_t g_semcNorMemoryInterface;
#endif // #if BL_FEATURE_SEMC_NOR_MODULE

#if BL_FEATURE_EXPAND_MEMORY
#if BL_FEATURE_SPINAND_MODULE
extern const external_memory_region_interface_t g_spiNandMemoryInterface;
#endif // BL_FEATURE_SPINAND_MODULE
#if BL_FEATURE_SEMC_NAND_MODULE
extern const external_memory_region_interface_t g_semcNandMemoryInterface;
#endif
#if BL_FEATURE_SPI_NOR_EEPROM_MODULE
extern const external_memory_region_interface_t g_spiNorEepromMemoryInterface;
#endif // BL_FEATURE_SPI_NOR_EEPROM_MODULE
#if BL_FEATURE_SD_MODULE
extern const external_memory_region_interface_t g_sdMemoryInterface;
#endif
#if BL_FEATURE_MMC_MODULE
extern const external_memory_region_interface_t g_mmcMemoryInterface;
#endif
#endif // BL_FEATURE_EXPAND_MEMORY

//@}

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @name Generic memory interface implementation
//@{

//! @brief Initialize memory interface.
status_t mem_init(void);

//! @brief Read memory.
status_t mem_read(uint32_t address, uint32_t length, uint8_t *buffer, uint32_t memoryId);

//! @brief Write memory.
status_t mem_write(uint32_t address, uint32_t length, const uint8_t *buffer, uint32_t memoryId);

//! @brief Fill memory with a word pattern.
status_t mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

//! @brief Erase memory.
status_t mem_erase(uint32_t address, uint32_t length, uint32_t memoryId);

//! @brief Flush memory.
status_t mem_flush(void);

//! @brief Reset state machine of memory interface.
status_t mem_finalize(void);

//! @brief Find a map entry that matches address and length.
status_t find_map_entry(uint32_t address, uint32_t length, const memory_map_entry_t **map);

#if BL_FEATURE_EXPAND_MEMORY
//! @brief Find an external map entry that matches address and length.
status_t find_external_map_entry(uint32_t address,
                                 uint32_t length,
                                 uint32_t memory_id,
                                 const external_memory_map_entry_t **map);

//! @brief Find an external map index that matches the given memory id.
status_t find_external_map_index(uint32_t memoryId, uint32_t *index);
#endif // BL_FEATURE_EXPAND_MEMORY

//!@brief Check is the specified memory region is erased.
bool mem_is_erased(uint32_t address, uint32_t length);

//@}

//! @name Memory utilities
//@{

//! @brief Determine if all or part of block is in a reserved region.
bool mem_is_block_reserved(uint32_t address, uint32_t length);

//@}

//! @name Flash erase operations
//@{

//! @brief Erase Flash memory.
status_t flash_mem_erase(uint32_t address, uint32_t length);

#if BL_FEATURE_FAC_ERASE
//! @brief Erase all Flash memory or all Flash execute-only segments.
//!
//! It is only valid for non-flash resident bootloader when option is erasing execute-only segments.
status_t flash_mem_erase_all(flash_erase_all_option_t eraseOption);
#else
//! @brief Erase all Flash memory.
//!
//! If building for flash resident bootloader, we have to decompose the the flash erase all
//! operation into two region erases. This allows the user to still do an erase all, but not
//! wipe out the bootloader itself.
status_t flash_mem_erase_all(void);
#endif

//! @brief Erase all Flash memory (unsecure).
status_t flash_mem_erase_all_unsecure(void);

#if BL_FEATURE_SUPPORT_DFLASH 
//! @brief Erase all FlexNVM Flash memory.
status_t flexNVM_mem_erase_all(void);

//! @brief Erase all Flash memory (unsecure).
status_t flexNVM_mem_erase_all_unsecure(void);
#endif // #if BL_FEATURE_SUPPORT_DFLASH 

//@}

//! @name QSPI erase operation
//@{

//! @brief Erase all QSPI memory
status_t qspi_mem_erase_all(void);

//! @brief Configure QSPI memory
status_t configure_qspi(const uint32_t address);
//@}

//! @name FlexSPI NOR erase operation
//@{

//! @brief Config FlexSPI NOR memory
status_t flexspi_nor_mem_config(uint32_t *config);

//! @brief Erase all FlexSPI NOR memory
status_t flexspi_nor_mem_erase_all(void);

//! @brief Get Property from flexspi0 NOR Flash driver
status_t flexspi_nor_get_property(uint32_t whichProperty, uint32_t *value);

//! @brief Get the status of flexspi configuration
bool is_flexspi_nor_configured(void);

//@}

//! @name SPI NAND erase operation
//@{

//! @brief Erase all SPI NAND memory
status_t spinand_mem_erase_all(void);

//! @brief Get Property from spi NAND flash driver.
status_t spinand_get_property(uint32_t whichProperty, uint32_t *value);

//@}

//! @name SEMC NOR
//@{

//! @brief Configure SEMC NOR memory.
status_t semc_nor_mem_config(uint32_t *config);

//! @brief Erase all SEMC NOR memory
status_t semc_nor_mem_erase_all(void);

//! @brief Get Property from semc nor driver
status_t semc_nor_get_property(uint32_t whichProperty, uint32_t *value);

//! @brief Get the status of semc nor configuration
bool is_semc_nor_configured(void);

//@}

//! @name SEMC NAND erase operation
//@{

//! @brief Erase all SEMC NAND memory
status_t semc_nand_mem_erase_all(void);

//! @brief Get Property from semc nand driver
status_t semc_nand_get_property(uint32_t whichProperty, uint32_t *value);

//@}

//! @name SPI NOR/EEPROM
//@{

//! @brief  Erase all Serial NOR/EEPROM memory
status_t spi_nor_eeprom_mem_erase_all(void);

//! @brief Get Property from spi NOR/EEPROM flash driver.
status_t spi_nor_eeprom_get_property(uint32_t whichProperty, uint32_t *value);

//@}

//! @name SD CARD
//@{
//! @brief Erase all SD memory
status_t sd_mem_erase_all(void);
//! @brief Get Property from SD card driver.
status_t sd_get_property(uint32_t whichProperty, uint32_t *value);

//@}

//! @name MMC CARD
//@{
//! @brief Erase all MMC memory
status_t mmc_mem_erase_all(void);
//! @brief Get Property from MMC card driver.
status_t mmc_get_property(uint32_t whichProperty, uint32_t *value);

//@}

//! @name SPIFI NOR erase operation
//@{

//! @brief Config SPIFI NOR memory
status_t spifi_nor_mem_config(uint32_t *config);

//! @brief Erase all SPIFI NOR memory
status_t spifi_nor_mem_erase_all(void);

//! @brief Get Property from spifi driver
status_t spifi_nor_get_property(uint32_t whichProperty, uint32_t *value);

//@}

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // _memory_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
