/*
 * Copyright 2018-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_IAP_H_
#define FSL_IAP_H_

#include "fsl_common.h"

/*!
 * @addtogroup IAP_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_IAP_DRIVER_VERSION (MAKE_VERSION(2, 0, 7))
/*! @} */

/*!
 * @brief iap status codes.
 */
enum
{
    kStatus_IAP_Success        = kStatus_Success,                   /*!< Api is executed successfully */
    kStatus_IAP_InvalidCommand = MAKE_STATUS(kStatusGroup_IAP, 1U), /*!< Invalid command */
    kStatus_IAP_SrcAddrError   = MAKE_STATUS(kStatusGroup_IAP, 2U), /*!< Source address is not on word boundary */
    kStatus_IAP_DstAddrError =
        MAKE_STATUS(kStatusGroup_IAP, 3U), /*!< Destination address is not on a correct boundary */
    kStatus_IAP_SrcAddrNotMapped =
        MAKE_STATUS(kStatusGroup_IAP, 4U), /*!< Source address is not mapped in the memory map */
    kStatus_IAP_DstAddrNotMapped =
        MAKE_STATUS(kStatusGroup_IAP, 5U), /*!< Destination address is not mapped in the memory map */
    kStatus_IAP_CountError =
        MAKE_STATUS(kStatusGroup_IAP, 6U), /*!< Byte count is not multiple of 4 or is not a permitted value */
    kStatus_IAP_InvalidSector = MAKE_STATUS(
        kStatusGroup_IAP,
        7), /*!< Sector/page number is invalid or end sector/page number is greater than start sector/page number */
    kStatus_IAP_SectorNotblank = MAKE_STATUS(kStatusGroup_IAP, 8U), /*!< One or more sectors are not blank */
    kStatus_IAP_NotPrepared =
        MAKE_STATUS(kStatusGroup_IAP, 9U), /*!< Command to prepare sector for write operation has not been executed */
    kStatus_IAP_CompareError =
        MAKE_STATUS(kStatusGroup_IAP, 10U),                /*!< Destination and source memory contents do not match */
    kStatus_IAP_Busy = MAKE_STATUS(kStatusGroup_IAP, 11U), /*!< Flash programming hardware interface is busy */
    kStatus_IAP_ParamError =
        MAKE_STATUS(kStatusGroup_IAP, 12U), /*!< Insufficient number of parameters or invalid parameter */
    kStatus_IAP_AddrError     = MAKE_STATUS(kStatusGroup_IAP, 13U), /*!< Address is not on word boundary */
    kStatus_IAP_AddrNotMapped = MAKE_STATUS(kStatusGroup_IAP, 14U), /*!< Address is not mapped in the memory map */
    kStatus_IAP_NoPower       = MAKE_STATUS(kStatusGroup_IAP, 24U), /*!< Flash memory block is powered down */
    kStatus_IAP_NoClock = MAKE_STATUS(kStatusGroup_IAP, 27U), /*!< Flash memory block or controller is not clocked */
    kStatus_IAP_ReinvokeISPConfig = MAKE_STATUS(kStatusGroup_IAP, 0x1CU), /*!< Reinvoke configuration error */
};

/*!
 * @brief iap command codes.
 */
enum _iap_commands
{
    kIapCmd_IAP_ReadFactorySettings   = 40U, /*!< Read the factory settings */
    kIapCmd_IAP_PrepareSectorforWrite = 50U, /*!< Prepare Sector for write */
    kIapCmd_IAP_CopyRamToFlash        = 51U, /*!< Copy RAM to flash */
    kIapCmd_IAP_EraseSector           = 52U, /*!< Erase Sector */
    kIapCmd_IAP_BlankCheckSector      = 53U, /*!< Blank check sector */
    kIapCmd_IAP_ReadPartId            = 54U, /*!< Read part id */
    kIapCmd_IAP_Read_BootromVersion   = 55U, /*!< Read bootrom version */
    kIapCmd_IAP_Compare               = 56U, /*!< Compare */
    kIapCmd_IAP_ReinvokeISP           = 57U, /*!< Reinvoke ISP */
    kIapCmd_IAP_ReadUid               = 58U, /*!< Read Uid */
    kIapCmd_IAP_ErasePage             = 59U, /*!< Erase Page */
    kIapCmd_IAP_ReadSignature         = 70U, /*!< Read Signature */
    kIapCmd_IAP_ExtendedReadSignature = 73U, /*!< Extended Read Signature */
#if defined(FSL_FEATURE_IAP_HAS_FAIM_FUNCTION) && FSL_FEATURE_IAP_HAS_FAIM_FUNCTION
    kIapCmd_IAP_ReadFAIMPage  = 80U, /*!< Read FAIM page */
    kIapCmd_IAP_WriteFAIMPage = 81U, /*!< Write FAIM page */
#else
    kIapCmd_IAP_ReadEEPROMPage  = 80U, /*!< Read EEPROM page */
    kIapCmd_IAP_WriteEEPROMPage = 81U, /*!< Write EEPROM page */
#endif /*FSL_FEATURE_IAP_HAS_FAIM_FUNCTION  */
};

/*!
 * @brief Flash memory access time.
 */
enum _flash_access_time
{
    kFlash_IAP_OneSystemClockTime   = 0U, /*! 1 system clock flash access time */
    kFlash_IAP_TwoSystemClockTime   = 1U, /*! 2 system clock flash access time */
    kFlash_IAP_ThreeSystemClockTime = 2U, /*! 3 system clock flash access time */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Basic operations
 * @{
 */

/*!
 * @brief Read part identification number.
 *
 * This function is used to read the part identification number.
 *
 * @param partID Address to store the part identification number.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ReadPartID(uint32_t *partID);

/*!
 * @brief Read boot code version number.
 *
 * This function is used to read the boot code version number.
 *
 * @param bootCodeVersion Address to store the boot code version.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 *
 * note Boot code version is two 32-bit words. Word 0 is the major version, word 1 is the minor version.
 */
status_t IAP_ReadBootCodeVersion(uint32_t *bootCodeVersion);

/*!
 * @brief Reinvoke ISP.
 *
 * This function is used to invoke the boot loader in ISP mode. It maps boot vectors and configures the peripherals for
 * ISP.
 *
 * @param ispType ISP type selection.
 * @param status store the possible status.
 *
 * @retval kStatus_IAP_ReinvokeISPConfig reinvoke configuration error.
 *
 * note The error response will be returned when IAP is disabled or an invalid ISP type selection appears. The call
 * won't return unless an error occurs, so there can be no status code.
 */
void IAP_ReinvokeISP(uint8_t ispType, uint32_t *status);

/*!
 * @brief Read unique identification.
 *
 * This function is used to read the unique id.
 *
 * @param uniqueID store the uniqueID.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ReadUniqueID(uint32_t *uniqueID);

#if defined(FSL_FEATURE_IAP_HAS_READ_FACTORY_SETTINGS_FUNCTION) && FSL_FEATURE_IAP_HAS_READ_FACTORY_SETTINGS_FUNCTION
/*!
 * @brief Read factory settings.
 *
 * This function reads the factory settings for calibration registers.
 *
 * @param dstRegAddr Address of the targeted calibration register.
 * @param factoryValue Store the factory value
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_ParamError Param0 is not one of the supported calibration registers.
 */
status_t IAP_ReadFactorySettings(uint32_t dstRegAddr, uint32_t *factoryValue);
#endif /* FSL_FEATURE_IAP_HAS_READ_FACTORY_SETTINGS_FUNCTION */

/*! @} */

#if defined(FSL_FEATURE_IAP_HAS_FLASH_FUNCTION) && FSL_FEATURE_IAP_HAS_FLASH_FUNCTION
/*!
 * @name Flash operations
 * @{
 */

#if defined(FLASH_CTRL_FLASHCFG_FLASHTIM_MASK)
/*!
 * @brief Flash memory access time.
 *
 * This function is used to configure the access time to the flash memory.
 *
 * @param accessTime Flash memory access time FLASHTIM +1 is equal to the
 *                   number of system clocks used for flash access.
 */
void IAP_ConfigAccessFlashTime(uint32_t accessTime);
#endif

/*!
 * @brief Prepare sector for write operation.
 *
 * This function prepares sector(s) for write/erase operation. This function must be called before calling the
 * IAP_CopyRamToFlash() or IAP_EraseSector() or IAP_ErasePage() function. The end sector number must be greater than or
 * equal to the start sector number.
 *
 * @param startSector Start sector number.
 * @param endSector End sector number.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_InvalidSector Sector number is invalid or end sector number is greater than start sector number.
 * @retval kStatus_IAP_Busy Flash programming hardware interface is busy.
 */
status_t IAP_PrepareSectorForWrite(uint32_t startSector, uint32_t endSector);

/*!
 * @brief Copy RAM to flash.
 *
 * This function programs the flash memory. Corresponding sectors must be prepared via IAP_PrepareSectorForWrite before
 * calling this function. 
 *
 * @param dstAddr Destination flash address where data bytes are to be written, the address should be multiples 
 *      of FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES boundary.
 * @param srcAddr Source ram address from where data bytes are to be read.
 * @param numOfBytes Number of bytes to be written, it should be multiples of FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES, 
 *      and ranges from FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES to FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES.
 * @param systemCoreClock SystemCoreClock in Hz. It is converted to KHz before calling the rom IAP function. When the
 *      flash controller has a fixed reference clock, this parameter is bypassed.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_SrcAddrError Source address is not on word boundary.
 * @retval kStatus_IAP_DstAddrError Destination address is not on a correct boundary.
 * @retval kStatus_IAP_SrcAddrNotMapped Source address is not mapped in the memory map.
 * @retval kStatus_IAP_DstAddrNotMapped Destination address is not mapped in the memory map.
 * @retval kStatus_IAP_CountError Byte count is not multiple of 4 or is not a permitted value.
 * @retval kStatus_IAP_NotPrepared Command to prepare sector for write operation has not been executed.
 * @retval kStatus_IAP_Busy Flash programming hardware interface is busy.
 */
status_t IAP_CopyRamToFlash(uint32_t dstAddr, uint32_t *srcAddr, uint32_t numOfBytes, uint32_t systemCoreClock);

/*!
 * @brief Erase sector.
 *
 * This function erases sector(s). The end sector number must be greater than or equal to the start sector number.
 *
 * @param startSector Start sector number.
 * @param endSector End sector number.
 * @param systemCoreClock SystemCoreClock in Hz. It is converted to KHz before calling the rom IAP function. When the
 * flash controller has a fixed reference clock, this parameter is bypassed.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_InvalidSector Sector number is invalid or end sector number is greater than start sector number.
 * @retval kStatus_IAP_NotPrepared Command to prepare sector for write operation has not been executed.
 * @retval kStatus_IAP_Busy Flash programming hardware interface is busy.
 */
status_t IAP_EraseSector(uint32_t startSector, uint32_t endSector, uint32_t systemCoreClock);

/*!
 * @brief Erase page.
 *
 * This function erases page(s). The end page number must be greater than or equal to the start page number.
 *
 * @param startPage Start page number.
 * @param endPage End page number.
 * @param systemCoreClock SystemCoreClock in Hz. It is converted to KHz before calling the rom IAP function. When the
 * flash controller has a fixed reference clock, this parameter is bypassed.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_InvalidSector Page number is invalid or end page number is greater than start page number.
 * @retval kStatus_IAP_NotPrepared Command to prepare sector for write operation has not been executed.
 * @retval kStatus_IAP_Busy Flash programming hardware interface is busy.
 */
status_t IAP_ErasePage(uint32_t startPage, uint32_t endPage, uint32_t systemCoreClock);

/*!
 * @brief Blank check sector(s)
 *
 * Blank check single or multiples sectors of flash memory. The end sector number must be greater than or equal to the
 * start sector number. It can be used to verify the sector erasure after IAP_EraseSector call.
 *
 * @param startSector Start sector number.
 * @param endSector End sector number.
 * @retval kStatus_IAP_Success One or more sectors are in erased state.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_SectorNotblank One or more sectors are not blank.
 */
status_t IAP_BlankCheckSector(uint32_t startSector, uint32_t endSector);

/*!
 * @brief Compare memory contents of flash with ram.
 *
 * This function compares the contents of flash and ram. It can be used to verify the flash memory contents after
 * IAP_CopyRamToFlash call.
 *
 * @param dstAddr Destination flash address.
 * @param srcAddr Source ram address.
 * @param numOfBytes Number of bytes to be compared.
 *
 * @retval kStatus_IAP_Success Contents of flash and ram match.
 * @retval kStatus_IAP_NoPower Flash memory block is powered down.
 * @retval kStatus_IAP_NoClock Flash memory block or controller is not clocked.
 * @retval kStatus_IAP_AddrError Address is not on word boundary.
 * @retval kStatus_IAP_AddrNotMapped Address is not mapped in the memory map.
 * @retval kStatus_IAP_CountError Byte count is not multiple of 4 or is not a permitted value.
 * @retval kStatus_IAP_CompareError Destination and source memory contents do not match.
 */
status_t IAP_Compare(uint32_t dstAddr, uint32_t *srcAddr, uint32_t numOfBytes);

#if defined(FSL_FEATURE_IAP_HAS_FLASH_EXTENDED_SIGNATURE_READ) && FSL_FEATURE_IAP_HAS_FLASH_EXTENDED_SIGNATURE_READ
/*!
 * @brief Extended Read signature.
 *
 * This function calculates the signature value for one or more pages of on-chip flash memory.
 *
 * @param startPage Start page number.
 * @param endPage End page number.
 * @param numOfStates Number of wait states.
 * @param signature Address to store the signature value.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ExtendedFlashSignatureRead(uint32_t startPage,
                                        uint32_t endPage,
                                        uint32_t numOfStates,
                                        uint32_t *signature);
#endif /* FSL_FEATURE_IAP_HAS_FLASH_EXTENDED_SIGNATURE_READ */

#if defined(FSL_FEATURE_IAP_HAS_FLASH_SIGNATURE_READ) && FSL_FEATURE_IAP_HAS_FLASH_SIGNATURE_READ
/*!
 * @brief Read flash signature.
 *
 * This funtion is used to obtain a 32-bit signature value of the entire flash memory.
 *
 * @param signature Address to store the 32-bit generated signature value.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ReadFlashSignature(uint32_t *signature);
#endif /* FSL_FEATURE_IAP_HAS_FLASH_SIGNATURE_READ */

/*! @} */
#endif /* FSL_FEATURE_IAP_HAS_FLASH_FUNCTION */

#if (defined(FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION) && (FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION == 1))
/*!
 * @name EEPROM operations
 * @{
 */

/*!
 * @brief Read EEPROM page.
 *
 * This function is used to read given page of EEPROM into the memory provided.
 *
 * @param pageNumber EEPROM page number.
 * @param dstAddr Memory address to store the value read from EEPROM.
 * @param systemCoreClock Current core clock frequency in kHz.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_InvalidSector Sector number is invalid.
 * @retval kStatus_IAP_DstAddrNotMapped Destination address is not mapped in the memory map.
 *
 * note Value 0xFFFFFFFF of systemCoreClock will retain the timing and clock settings for EEPROM.
 */
status_t IAP_ReadEEPROMPage(uint32_t pageNumber, uint32_t *dstAddr, uint32_t systemCoreClock);

/*!
 * @brief Write EEPROM page.
 *
 * This function is used to write given data in the provided memory to a page of EEPROM.
 *
 * @param pageNumber EEPROM page number.
 * @param srcAddr Memory address holding data to be stored on to EEPROM page.
 * @param systemCoreClock Current core clock frequency in kHz.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_InvalidSector Sector number is invalid.
 * @retval kStatus_IAP_SrcAddrNotMapped Source address is not mapped in the memory map.
 *
 * note Value 0xFFFFFFFF of systemCoreClock will retain the timing and clock settings for EEPROM
 */
status_t IAP_WriteEEPROMPage(uint32_t pageNumber, uint32_t *srcAddr, uint32_t systemCoreClock);

/*! @} */
#endif /* FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION */

#if defined(FSL_FEATURE_IAP_HAS_FAIM_FUNCTION) && FSL_FEATURE_IAP_HAS_FAIM_FUNCTION
/*!
 * @name FAIM operations
 * @{
 */

/*!
 * @brief Read FAIM page.
 *
 * This function is used to read given page of FAIM into the memory provided.
 *
 * @param pageNumber FAIM page number.
 * @param dstAddr Memory address to store the value read from FAIM.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_DstAddrNotMapped Destination address is not mapped in the memory map.
 */
status_t IAP_ReadFAIMPage(uint32_t pageNumber, uint32_t *dstAddr);

/*!
 * @brief Write FAIM page.
 *
 * This function is used to write given data in the provided memory to a page of G.
 *
 * @param pageNumber FAIM page number.
 * @param srcAddr Memory address holding data to be stored on to FAIM page.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 * @retval kStatus_IAP_SrcAddrNotMapped Source address is not mapped in the memory map.
 */
status_t IAP_WriteFAIMPage(uint32_t pageNumber, uint32_t *srcAddr);
#endif /* FSL_FEATURE_IAP_HAS_FAIM_FUNCTION */

/*! @} */

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* FSL_IAP_H_ */
