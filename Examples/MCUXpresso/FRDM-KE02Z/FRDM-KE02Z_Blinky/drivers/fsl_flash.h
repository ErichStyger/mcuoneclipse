/*
 * Copyright 2017 - 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FLASH_H_
#define _FSL_FLASH_H_

#if (defined(BL_TARGET_FLASH) || defined(BL_TARGET_ROM) || defined(BL_TARGET_RAM))
#include <assert.h>
#include <string.h>
#include "fsl_device_registers.h"
#include "bootloader_common.h"
#else
#include "fsl_common.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup flash_driver
 * @{
 */

/*!
 * @name Flash version
 * @{
 */
/*! @brief Constructs the version number for drivers. */
#if !defined(MAKE_VERSION)
#define MAKE_VERSION(major, minor, bugfix) (((major) << 16) | ((minor) << 8) | (bugfix))
#endif

/*! @brief Flash driver version for SDK*/
#define FSL_FLASH_DRIVER_VERSION (MAKE_VERSION(2, 1, 2)) /*!< Version 2.1.2. */

/*! @brief Flash driver version for ROM*/
enum _flash_driver_version_constants
{
    kFLASH_DriverVersionName   = 'F', /*!< Flash driver version name.*/
    kFLASH_DriverVersionMajor  = 2,   /*!< Major flash driver version.*/
    kFLASH_DriverVersionMinor  = 1,   /*!< Minor flash driver version.*/
    kFLASH_DriverVersionBugfix = 1    /*!< Bugfix for flash driver version.*/
};
/*@}*/

/*!
 * @name Flash configuration
 * @{
 */
/*! @brief Indicates whether to support EEPROM in the Flash driver */
#if (defined(FSL_FEATURE_FLASH_HAS_EEPROM) && FSL_FEATURE_FLASH_HAS_EEPROM)
#define FLASH_SSD_CONFIG_ENABLE_EEPROM_SUPPORT 1 /*!< Enables the EEPROM support. */
#else
#define FLASH_SSD_CONFIG_ENABLE_EEPROM_SUPPORT 0 /*!< Disables the EEPROM support. */
#endif

/*! @brief Indicates whether the EEPROM is enabled in the Flash driver */
#define FLASH_SSD_IS_EEPROM_ENABLED FLASH_SSD_CONFIG_ENABLE_EEPROM_SUPPORT

/*! @brief Indicates whether to support Secondary flash in the Flash driver */
#if !defined(FLASH_SSD_CONFIG_ENABLE_SECONDARY_FLASH_SUPPORT)
#define FLASH_SSD_CONFIG_ENABLE_SECONDARY_FLASH_SUPPORT 1 /*!< Enables the secondary flash support by default. */
#endif

/*! @brief Indicates whether the secondary flash is supported in the Flash driver */
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)
#define FLASH_SSD_IS_SECONDARY_FLASH_ENABLED (FLASH_SSD_CONFIG_ENABLE_SECONDARY_FLASH_SUPPORT)
#else
#define FLASH_SSD_IS_SECONDARY_FLASH_ENABLED (0)
#endif

/*! @brief Flash driver location. */
#if !defined(FLASH_DRIVER_IS_FLASH_RESIDENT)
#if (!defined(BL_TARGET_ROM) && !defined(BL_TARGET_RAM))
#define FLASH_DRIVER_IS_FLASH_RESIDENT 1 /*!< Used for the flash resident application. */
#else
#define FLASH_DRIVER_IS_FLASH_RESIDENT 0 /*!< Used for the non-flash resident application. */
#endif
#endif

/*! @brief Flash Driver Export option */
#if !defined(FLASH_DRIVER_IS_EXPORTED)
#if (defined(BL_TARGET_ROM) || defined(BL_TARGET_FLASH))
#define FLASH_DRIVER_IS_EXPORTED 1 /*!< Used for the ROM bootloader. */
#else
#define FLASH_DRIVER_IS_EXPORTED 0 /*!< Used for the MCUXpresso SDK application. */
#endif
#endif

/*! @brief Enable flash stalling controller */
#define FLASH_ENABLE_STALLING_FLASH_CONTROLLER 1
/*@}*/

/*!
 * @name Flash status
 * @{
 */
/*! @brief Flash driver status group. */
#if defined(kStatusGroup_FlashDriver)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FlashDriver
#elif defined(kStatusGroup_FLASH)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FLASH
#else
#define kStatusGroupGeneric     0
#define kStatusGroupFlashDriver 1
#endif

/*! @brief Constructs a status code value from a group and a code number. */
#if !defined(MAKE_STATUS)
#define MAKE_STATUS(group, code) ((((group)*100) + (code)))
#endif

/*!
 * @brief Flash driver status codes.
 */
enum
{
    kStatus_FLASH_Success         = MAKE_STATUS(kStatusGroupGeneric, 0),     /*!< API is executed successfully*/
    kStatus_FLASH_InvalidArgument = MAKE_STATUS(kStatusGroupGeneric, 4),     /*!< Invalid argument*/
    kStatus_FLASH_SizeError       = MAKE_STATUS(kStatusGroupFlashDriver, 0), /*!< Error size*/
    kStatus_FLASH_AlignmentError =
        MAKE_STATUS(kStatusGroupFlashDriver, 1), /*!< Parameter is not aligned with the specified baseline*/
    kStatus_FLASH_AddressError = MAKE_STATUS(kStatusGroupFlashDriver, 2), /*!< Address is out of range */
    kStatus_FLASH_AccessError =
        MAKE_STATUS(kStatusGroupFlashDriver, 3), /*!< Invalid instruction codes and out-of bound addresses */
    kStatus_FLASH_ProtectionViolation = MAKE_STATUS(
        kStatusGroupFlashDriver, 4), /*!< The program/erase operation is requested to execute on protected areas */
    kStatus_FLASH_CommandFailure =
        MAKE_STATUS(kStatusGroupFlashDriver, 5), /*!< Run-time error during command execution. */
    kStatus_FLASH_UnknownProperty = MAKE_STATUS(kStatusGroupFlashDriver, 6), /*!< Unknown property.*/
    kStatus_FLASH_EraseKeyError   = MAKE_STATUS(kStatusGroupFlashDriver, 7), /*!< API erase key is invalid.*/
    kStatus_FLASH_RegionExecuteOnly =
        MAKE_STATUS(kStatusGroupFlashDriver, 8), /*!< The current region is execute-only.*/
    kStatus_FLASH_ExecuteInRamFunctionNotReady =
        MAKE_STATUS(kStatusGroupFlashDriver, 9), /*!< Execute-in-RAM function is not available.*/
    kStatus_FLASH_PartitionStatusUpdateFailure =
        MAKE_STATUS(kStatusGroupFlashDriver, 10), /*!< Failed to update partition status.*/
    kStatus_FLASH_SetFlexramAsEepromError =
        MAKE_STATUS(kStatusGroupFlashDriver, 11), /*!< Failed to set FlexRAM as EEPROM.*/
    kStatus_FLASH_RecoverFlexramAsRamError =
        MAKE_STATUS(kStatusGroupFlashDriver, 12), /*!< Failed to recover FlexRAM as RAM.*/
    kStatus_FLASH_SetFlexramAsRamError = MAKE_STATUS(kStatusGroupFlashDriver, 13), /*!< Failed to set FlexRAM as RAM.*/
    kStatus_FLASH_RecoverFlexramAsEepromError =
        MAKE_STATUS(kStatusGroupFlashDriver, 14), /*!< Failed to recover FlexRAM as EEPROM.*/
    kStatus_FLASH_CommandNotSupported = MAKE_STATUS(kStatusGroupFlashDriver, 15), /*!< Flash API is not supported.*/
    kStatus_FLASH_SwapSystemNotInUninitialized =
        MAKE_STATUS(kStatusGroupFlashDriver, 16), /*!< Swap system is not in an uninitialzed state.*/
    kStatus_FLASH_SwapIndicatorAddressError =
        MAKE_STATUS(kStatusGroupFlashDriver, 17), /*!< The swap indicator address is invalid.*/
    kStatus_FLASH_ReadOnlyProperty = MAKE_STATUS(kStatusGroupFlashDriver, 18), /*!< The flash property is read-only.*/
    kStatus_FLASH_InvalidPropertyValue =
        MAKE_STATUS(kStatusGroupFlashDriver, 19), /*!< The flash property value is out of range.*/
    kStatus_FLASH_InvalidSpeculationOption =
        MAKE_STATUS(kStatusGroupFlashDriver, 20), /*!< The option of flash prefetch speculation is invalid.*/

    kStatus_FLASH_ClockDivider = MAKE_STATUS(kStatusGroupFlashDriver, 21), /*!<Flash clock prescaler is wrong*/
    kStatus_FLASH_EepromDoubleBitFault =
        MAKE_STATUS(kStatusGroupFlashDriver, 22), /*!< A double bit fault was detected in the stored parity.*/
    kStatus_FLASH_EepromSingleBitFault =
        MAKE_STATUS(kStatusGroupFlashDriver, 23), /*!< A single bit fault was detected in the stored parity.*/

};

/*@}*/

/*!
 * @name Flash API key
 * @{
 */
/*! @brief Constructs the four character code for the Flash driver API key. */
#if !defined(FOUR_CHAR_CODE)
#define FOUR_CHAR_CODE(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | ((a)))
#endif

/*!
 * @brief Enumeration for Flash driver API keys.
 *
 * @note The resulting value is built with a byte order such that the string
 * being readable in expected order when viewed in a hex editor, if the value
 * is treated as a 32-bit little endian value.
 */
enum _flash_driver_api_keys
{
    kFLASH_ApiEraseKey = FOUR_CHAR_CODE('k', 'f', 'e', 'k') /*!< Key value used to validate all flash erase APIs.*/
};
/*@}*/

/*!
 * @brief Enumeration for supported flash user margin levels.
 */
typedef enum _flash_user_margin_value
{
    kFLASH_ReadMarginValueNormal = 0x0000U, /*!< Use the 'normal' read level for 1s.*/
    kFLASH_UserMarginValue1      = 0x0001U, /*!< Apply the 'User' margin to the normal read-1 level.*/
    kFLASH_UserMarginValue0      = 0x0002U, /*!< Apply the 'User' margin to the normal read-0 level.*/
} flash_user_margin_value_t;

/*!
 * @brief Enumeration for supported factory margin levels.
 */
typedef enum _flash_factory_margin_value
{
    kFLASH_FactoryMarginValue1 = 0x0003U, /*!< Apply the 'Factory' margin to the normal read-1 level.*/
    kFLASH_FactoryMarginValue0 = 0x0004U, /*!< Apply the 'Factory' margin to the normal read-0 level.*/
} flash_factory_margin_value_t;

/*!
 * @brief Enumeration for supported flash margin levels.
 */
typedef enum _flash_margin_value
{
    kFLASH_MarginValueNormal,  /*!< Use the 'normal' read level for 1s.*/
    kFLASH_MarginValueUser,    /*!< Apply the 'User' margin to the normal read-1 level.*/
    kFLASH_MarginValueFactory, /*!< Apply the 'Factory' margin to the normal read-1 level.*/
    kFLASH_MarginValueInvalid, /*!< Not real margin level, Used to determine the range of valid margin level. */
} flash_margin_value_t;

/*!
 * @brief Enumeration for the three possible flash security states.
 */
typedef enum _flash_security_state
{
    kFLASH_SecurityStateNotSecure,       /*!< Flash is not secure.*/
    kFLASH_SecurityStateBackdoorEnabled, /*!< Flash backdoor is enabled.*/
    kFLASH_SecurityStateBackdoorDisabled /*!< Flash backdoor is disabled.*/
} flash_security_state_t;

/*!
 * @brief Enumeration for the three possible flash protection levels.
 */
typedef enum _flash_protection_state
{
    kFLASH_ProtectionStateUnprotected, /*!< Flash region is not protected.*/
    kFLASH_ProtectionStateProtected,   /*!< Flash region is protected.*/
    kFLASH_ProtectionStateMixed        /*!< Flash is mixed with protected and unprotected region.*/
} flash_protection_state_t;

/*!
 * @brief Enumeration for various flash properties.
 */
typedef enum _flash_property_tag
{
    kFLASH_PropertyPflashSectorSize    = 0x00U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflashTotalSize     = 0x01U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflashBlockSize     = 0x02U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflashBlockCount    = 0x03U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflashBlockBaseAddr = 0x04U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflashFacSupport    = 0x05U, /*!< Pflash fac support property.*/

    kFLASH_PropertyEepromTotalSize           = 0x15U, /*!< EEPROM total size property.*/
    kFLASH_PropertyFlashMemoryIndex          = 0x20U, /*!< Flash memory index property.*/
    kFLASH_PropertyFlashCacheControllerIndex = 0x21U, /*!< Flash cache controller index property.*/

    kFLASH_PropertyEepromBlockBaseAddr = 0x22U, /*!< EEPROM block base address property.*/
    kFLASH_PropertyEepromSectorSize    = 0x23U, /*!< EEPROM sector size property.*/
    kFLASH_PropertyEepromBlockSize     = 0x24U, /*!< EEPROM block size property.*/
    kFLASH_PropertyEepromBlockCount    = 0x25U, /*!< EEPROM block count property.*/
    kFLASH_PropertyFlashClockFrequency = 0x26U, /*!< Flash peripheral clock property.*/
} flash_property_tag_t;

/*!
 * @brief Constants for execute-in-RAM flash function.
 * _flash_execute_in_ram_function_constants
 */
enum
{
    kFLASH_ExecuteInRamFunctionMaxSizeInWords = 16U, /*!< The maximum size of execute-in-RAM function.*/
    kFLASH_ExecuteInRamFunctionTotalNum       = 2U   /*!< Total number of execute-in-RAM functions.*/
};

/*!
 * @brief PFlash protection status - full
 */
typedef struct _pflash_protection_status
{
    uint8_t fprotvalue; /*!< FPROT[7:0] .*/
} pflash_protection_status_t;

/*!
 * @brief Enumeration for the flash memory index.
 */
typedef enum _flash_memory_index
{
    kFLASH_MemoryIndexPrimaryFlash   = 0x00U, /*!< Current flash memory is primary flash.*/
    kFLASH_MemoryIndexSecondaryFlash = 0x01U, /*!< Current flash memory is secondary flash.*/
} flash_memory_index_t;

/*!
 * @brief Enumeration for the flash cache controller index.
 */
typedef enum _flash_cache_controller_index
{
    kFLASH_CacheControllerIndexForCore0 = 0x00U, /*!< Current flash cache controller is for core 0.*/
    kFLASH_CacheControllerIndexForCore1 = 0x01U, /*!< Current flash cache controller is for core 1.*/
} flash_cache_controller_index_t;

/*! @brief A callback type used for the Pflash block*/
typedef void (*flash_callback_t)(void);

/*!
 * @brief Enumeration for the two possible options of flash prefetch speculation.
 */
typedef enum _flash_prefetch_speculation_option
{
    kFLASH_prefetchSpeculationOptionEnable  = 0x00U,
    kFLASH_prefetchSpeculationOptionDisable = 0x01U
} flash_prefetch_speculation_option_t;

/*!
 * @brief Flash prefetch speculation status.
 */
typedef struct _flash_prefetch_speculation_status
{
    flash_prefetch_speculation_option_t instructionOption; /*!< Instruction speculation.*/
    flash_prefetch_speculation_option_t dataOption;        /*!< Data speculation.*/
} flash_prefetch_speculation_status_t;

/*!
 * @brief Flash cache clear process code.
 */
typedef enum _flash_cache_clear_process
{
    kFLASH_CacheClearProcessPre  = 0x00U, /*!< Pre flash cache clear process.*/
    kFLASH_CacheClearProcessPost = 0x01U, /*!< Post flash cache clear process.*/
} flash_cache_clear_process_t;

/*!
 * @brief Active flash protection information for the current operation.
 */
typedef struct _flash_protection_config
{
    uint32_t lowRegionStart;  /*!< Start address of flash protection low region.*/
    uint32_t lowRegionEnd;    /*!< End address of flash protection low region.*/
    uint32_t highRegionStart; /*!< Start address of flash protection high region.*/
    uint32_t highRegionEnd;   /*!< End address of flash protection high region.*/
} flash_protection_config_t;

/*!
 * @brief Active flash information for the current operation.
 */
typedef struct _flash_operation_config
{
    uint32_t convertedAddress;          /*!< A converted address for the current flash type.*/
    uint32_t activeSectorSize;          /*!< A sector size of the current flash type.*/
    uint32_t activeBlockSize;           /*!< A block size of the current flash type.*/
    uint32_t blockWriteUnitSize;        /*!< The write unit size.*/
    uint32_t sectorCmdAddressAligment;  /*!< An erase sector command address alignment.*/
    uint32_t sectionCmdAddressAligment; /*!< A program/verify section command address alignment.*/

    uint32_t programCmdAddressAligment; /*!< A program flash command address alignment.*/
} flash_operation_config_t;

/*!
 * @brief Flash execute-in-RAM command.
 */
typedef union
{
    uint32_t commadAddr;
    void (*callFlashCommand)(volatile uint8_t *FTMRx_fstat);
} function_run_command_t;

typedef union
{
    uint32_t bitOperationAddr;
    void (*callCommonBitOperationCommand)(volatile uint32_t *base,
                                          uint32_t bitMask,
                                          uint32_t bitShift,
                                          uint32_t bitValue);
} function_common_bit_operation_t;
/*!
 * @brief Flash execute-in-RAM function information.
 */
typedef struct _flash_execute_in_ram_function_config
{
    uint32_t activeFunctionCount;                           /*!< Number of available execute-in-RAM functions.*/
    function_run_command_t runCmdFuncAddr;                  /*!< Execute-in-RAM function: flash_run_command. */
    function_common_bit_operation_t CommonBitOperationAddr; /*! Execute-in-RAM function: flash_common_bit_operation. */
} flash_execute_in_ram_function_config_t;

/*! @brief Flash driver state information.
 *
 * An instance of this structure is allocated by the user of the flash driver and
 * passed into each of the driver APIs.
 */
typedef struct _flash_config
{
    uint32_t PFlashBlockBase;          /*!< A base address of the first PFlash block */
    uint32_t PFlashTotalSize;          /*!< The size of the combined PFlash block. */
    uint8_t PFlashBlockCount;          /*!< A number of PFlash blocks. */
    uint8_t FlashMemoryIndex;          /*!< 0 - primary flash; 1 - secondary flash*/
    uint8_t FlashCacheControllerIndex; /*!< 0 - Controller for core 0; 1 - Controller for core 1 */
    uint8_t Reserved0;                 /*!< Reserved field 0 */
    uint32_t PFlashSectorSize;         /*!< The size in bytes of a sector of PFlash. */
    flash_callback_t PFlashCallback;   /*!< The callback function for the flash API. */

    uint32_t *flashExecuteInRamFunctionInfo; /*!< An information structure of the flash execute-in-RAM function. */

    uint32_t EEpromTotalSize; /*!< For the FlexNVM device, this is the size in bytes of the EEPROM area which was
                                 partitioned from FlexRAM */
    /*!< For the non-FlexNVM device, this field is unused */

    uint32_t EEpromBlockBase; /*!< This is the base address of the Eeprom */
    /*!< For the non-Eeprom device, this field is unused */
    uint8_t EEpromBlockCount; /*!< A number of EEPROM blocks. */
    /*!< For the non-Eeprom device, this field is unused */
    uint8_t EEpromSectorSize; /*!< The size in bytes of a sector of EEPROM. */
    /*!< For the non-Eeprom device, this field is unused */
    uint8_t Reserved1[2];       /*!< Reserved field 1 */
    uint32_t PFlashClockFreq;   /*!< The flash peripheral clock frequency */
    uint32_t PFlashMarginLevel; /*!< The margin level*/
    flash_execute_in_ram_function_config_t executeInRamFunction;
} flash_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_ClockDivider Flash clock prescaler is wrong.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 */
status_t FLASH_Init(flash_config_t *config);

/*!
 * @brief Sets the desired flash callback function.
 *
 * @param config Pointer to the storage for the driver runtime state.
 * @param callback A callback function to be stored in the driver.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_SetCallback(flash_config_t *config, flash_callback_t callback);

#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && FLASH_DRIVER_IS_FLASH_RESIDENT
/*!
 * @brief Prepares flash execute-in-RAM functions.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_PrepareExecuteInRamFunctions(flash_config_t *config);
#endif /* FLASH_DRIVER_IS_FLASH_RESIDENT */

/*@}*/

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erases entire flash
 *
 * @param config Pointer to the storage for the driver runtime state.
 * @param key A value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_EraseKeyError API erase key is invalid.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FLASH_EepromSingleBitFault EEPROM single bit fault error code.
 * @retval #kStatus_FLASH_EepromDoubleBitFault EEPROM double bit fault error code.
 */
status_t FLASH_EraseAll(flash_config_t *config, uint32_t key);

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be word-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError The address is out of range.
 * @retval #kStatus_FLASH_EraseKeyError The API erase key is invalid.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);

#if defined(FLASH_SSD_IS_EEPROM_ENABLED) && FLASH_SSD_IS_EEPROM_ENABLED
/*!
 * @brief Erases the eeprom sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of eeprom sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired eeprom memory to be erased.
 *              The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be word-aligned.
 * @param key The value used to validate all eeprom erase APIs.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError The address is out of range.
 * @retval #kStatus_FLASH_EraseKeyError The API erase key is invalid.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_EraseEEprom(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
#endif /* FLASH_SSD_IS_EEPROM_ENABLED */

#if defined(FSL_FEATURE_FLASH_HAS_UNSECURE_FLASH_CMD) && FSL_FEATURE_FLASH_HAS_UNSECURE_FLASH_CMD
/*!
 * @brief Erases the entire flash, including protected sectors.
 *
 * @param config Pointer to the storage for the driver runtime state.
 * @param key A value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_EraseKeyError API erase key is invalid.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FLASH_EepromSingleBitFault EEPROM single bit fault error code.
 * @retval #kStatus_FLASH_EepromDoubleBitFault EEPROM double bit fault error code.
 */
status_t FLASH_EraseAllUnsecure(flash_config_t *config, uint32_t key);
#endif /* FSL_FEATURE_FLASH_HAS_UNSECURE_FLASH_CMD */

/*@}*/

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint32_t *src, uint32_t lengthInBytes);

/*!
 * @brief Programs Program Once Field through parameters.
 *
 * This function programs the Program Once Field with the desired data for a given
 * flash area as determined by the index and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param index The index indicating which area of the Program Once Field to be programmed.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the Program Once Field.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ProgramOnce(flash_config_t *config, uint32_t index, uint32_t *src, uint32_t lengthInBytes);

#if defined(FLASH_SSD_IS_EEPROM_ENABLED) && FLASH_SSD_IS_EEPROM_ENABLED
/*!
 * @brief Programs the EEPROM with data at locations passed in through parameters.
 *
 * This function programs the emulated EEPROM with the desired data for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_EepromSingleBitFault EEPROM single bit fault error code.
 * @retval #kStatus_FLASH_EepromDoubleBitFault EEPROM double bit fault error code.
 */
status_t FLASH_EepromWrite(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
#endif /* FLASH_SSD_IS_EEPROM_ENABLED */

/*@}*/

/*!
 * @name Reading
 * @{
 */

/*!
 * @brief Reads the Program Once Field through parameters.
 *
 * This function reads the read once feild with given index and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param index The index indicating the area of program once field to be read.
 * @param dst A pointer to the destination buffer of data that is used to store
 *        data to be read.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ReadOnce(flash_config_t *config, uint32_t index, uint32_t *dst, uint32_t lengthInBytes);

/*@}*/

/*!
 * @name Security
 * @{
 */

/*!
 * @brief Returns the security state via the pointer passed into the function.
 *
 * This function retrieves the current flash security status, including the
 * security enabling state and the backdoor key enabling state.
 *
 * @param config A pointer to storage for the driver runtime state.
 * @param state A pointer to the value returned for the current security status code:
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_GetSecurityState(flash_config_t *config, flash_security_state_t *state);

/*!
 * @brief Allows users to bypass security with a backdoor key.
 *
 * If the MCU is in secured state, this function unsecures the MCU by
 * comparing the provided backdoor key with ones in the flash configuration
 * field.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param backdoorKey A pointer to the user buffer containing the backdoor key.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_SecurityBypass(flash_config_t *config, const uint8_t *backdoorKey);

/*@}*/

/*!
 * @name Verification
 * @{
 */

/*!
 * @brief Verifies erasure of the entire flash at a specified margin level.
 *
 * This function checks whether the flash is erased to the
 * specified read margin level.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param margin Read margin choice.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @retval #kStatus_FLASH_EepromSingleBitFault EEPROM single bit fault error code.
 * @retval #kStatus_FLASH_EepromDoubleBitFault EEPROM double bit fault error code.
 */
status_t FLASH_VerifyEraseAll(flash_config_t *config, flash_margin_value_t margin);

/*!
 * @brief Verifies an erasure of the desired flash area at a specified margin level.
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 * to the specified read margin level.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param margin Read margin choice.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, flash_margin_value_t margin);

/*@}*/

/*!
 * @name Protection
 * @{
 */

/*!
 * @brief Returns the protection state of the desired flash area via the pointer passed into the function.
 *
 * This function retrieves the current flash protect status for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be checked. Must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *        to be checked.  Must be word-aligned.
 * @param protection_state A pointer to the value returned for the current
 *        protection status code for the desired flash area.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError The address is out of range.
 */
status_t FLASH_IsProtected(flash_config_t *config,
                           uint32_t start,
                           uint32_t lengthInBytes,
                           flash_protection_state_t *protection_state);

/*@}*/

/*!
 * @name Properties
 * @{
 */

/*!
 * @brief Returns the desired flash property.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_UnknownProperty An unknown property tag.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

/*!
 * @brief Sets the desired flash property.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A to set for the desired flash property.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_UnknownProperty An unknown property tag.
 * @retval #kStatus_FLASH_InvalidPropertyValue An invalid property value.
 * @retval #kStatus_FLASH_ReadOnlyProperty An read-only property tag.
 */
status_t FLASH_SetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t value);

/*@}*/

/*!
 * @name Flash Protection Utilities
 * @{
 */

/*!
 * @brief Sets the PFlash Protection to the intended protection status.
 *
 * @param config A pointer to storage for the driver runtime state.
 * @param protectStatus The expected protect status to set to the PFlash protection register.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 */
status_t FLASH_PflashSetProtection(flash_config_t *config, pflash_protection_status_t *protectStatus);

/*!
 * @brief Gets the PFlash protection status.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param protectStatus  Protect status returned by the PFlash IP.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_PflashGetProtection(flash_config_t *config, pflash_protection_status_t *protectStatus);

#if defined(FLASH_SSD_IS_EEPROM_ENABLED) && FLASH_SSD_IS_EEPROM_ENABLED
/*!
 * @brief Sets the EEPROM protection to the intended protection status.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param protectStatus The expected protect status to set to the EEPROM protection register.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 */
status_t FLASH_EepromSetProtection(flash_config_t *config, uint8_t protectStatus);
#endif /* FLASH_SSD_IS_EEPROM_ENABLED */

#if defined(FLASH_SSD_IS_EEPROM_ENABLED) && FLASH_SSD_IS_EEPROM_ENABLED
/*!
 * @brief Gets the EEPROM protection status.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param protectStatus  EEPROM Protect status returned by the EEPROM IP.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 */
status_t FLASH_EepromGetProtection(flash_config_t *config, uint8_t *protectStatus);
#endif /* FLASH_SSD_IS_EEPROM_ENABLED */

/*@}*/

/*!
 * @name Flash Speculation Utilities
 * @{
 */

/*!
 * @brief Sets the PFlash prefetch speculation to the intended speculation status.
 *
 * @param speculationStatus The expected protect status to set to the PFlash protection register. Each bit is
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidSpeculationOption An invalid speculation option argument is provided.
 */
status_t FLASH_PflashSetPrefetchSpeculation(flash_prefetch_speculation_status_t *speculationStatus);

/*!
 * @brief Gets the PFlash prefetch speculation status.
 *
 * @param speculationStatus  Speculation status returned by the PFlash IP.
 * @retval #kStatus_FLASH_Success API was executed successfully.
 */
status_t FLASH_PflashGetPrefetchSpeculation(flash_prefetch_speculation_status_t *speculationStatus);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_FLASH_H_ */
