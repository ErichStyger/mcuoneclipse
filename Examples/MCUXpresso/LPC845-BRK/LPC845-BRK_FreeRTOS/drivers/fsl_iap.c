/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_iap.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iap"
#endif

#define HZ_TO_KHZ_DIV 1000U

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief IAP_ENTRY API function type */
typedef void (*IAP_ENTRY_T)(uint32_t cmd[], uint32_t stat[]);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Translate the IAP return status.
 *
 * @param status IAP status return from the IAP function.
 *
 * @return sdk status code.
 */
static inline status_t translate_iap_status(uint32_t status);

/*!
 * @brief IAP_ENTRY API function type.
 *
 * Wrapper for rom iap call.
 *
 * @param cmd_param IAP command and relevant parameter array.
 * @param status_result IAP status result array.
 */
static inline void iap_entry(uint32_t *cmd_param, uint32_t *status_result);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static inline status_t translate_iap_status(uint32_t status)
{
    status_t ret = (status_t)status;

    /* Translate IAP return code to sdk status code */
    if (status != (uint32_t)kStatus_Success)
    {
        ret = MAKE_STATUS((int32_t)kStatusGroup_IAP, (int32_t)status);
    }

    return ret;
}

static inline void iap_entry(uint32_t *cmd_param, uint32_t *status_result)
{
    __disable_irq();
    ((IAP_ENTRY_T)FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION)(cmd_param, status_result);
    __enable_irq();
}

/*!
 * @brief Read part identification number.
 *
 * This function is used to read the part identification number.
 *
 * @param partID Address to store the part identification number.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ReadPartID(uint32_t *partID)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadPartId;
    iap_entry(command, result);
    *partID = result[1];

    return translate_iap_status(result[0]);
}

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
status_t IAP_ReadBootCodeVersion(uint32_t *bootCodeVersion)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_Read_BootromVersion;
    iap_entry(command, result);
    bootCodeVersion[0] = result[1];
    bootCodeVersion[1] = result[2];

    return translate_iap_status(result[0]);
}

/*!
 * @brief Reinvoke ISP.
 *
 * This function is used to invoke the boot loader in ISP mode. It maps boot vectors and configures the peripherals for
 * ISP.
 *
 * @param ispTyoe ISP type selection.
 * @param status store the possible status.
 *
 * @retval kStatus_IAP_ReinvokeISPConfig reinvoke configuration error.
 *
 * note The error response will be returned when IAP is disabled or an invalid ISP type selection appears. The call
 * won't return unless an error occurs, so there can be no status code.
 */
void IAP_ReinvokeISP(uint8_t ispType, uint32_t *status)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};
    uint8_t ispParameterArray[8];

    command[0] = (uint32_t)kIapCmd_IAP_ReinvokeISP;
    (void)memset(ispParameterArray, 0, sizeof(uint8_t) * 8U);
    ispParameterArray[1] = ispType;
    ispParameterArray[7] = ispParameterArray[0] ^ ispParameterArray[1] ^ ispParameterArray[2] ^ ispParameterArray[3] ^
                           ispParameterArray[4] ^ ispParameterArray[5] ^ ispParameterArray[6];
    command[1] = (uint32_t)ispParameterArray;
    iap_entry(command, result);
    *status = (uint32_t)translate_iap_status(result[0]);
}

/*!
 * @brief Read unique identification.
 *
 * This function is used to read the unique id.
 *
 * @param uniqueID store the uniqueID.
 *
 * @retval kStatus_IAP_Success Api has been executed successfully.
 */
status_t IAP_ReadUniqueID(uint32_t *uniqueID)
{
#if defined(FSL_FEATURE_IAP_READ_UNIQUE_ID_NOWORK) && FSL_FEATURE_IAP_READ_UNIQUE_ID_NOWORK
    uint32_t *result = (uint32_t *)0x01000100;
    uint8_t i        = 0;

    for (i = 0; i < 4; i++)
        uniqueID[i] = result[i];
    return kStatus_IAP_Success;
#else
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadUid;
    iap_entry(command, result);
    uniqueID[0] = result[1];
    uniqueID[1] = result[2];
    uniqueID[2] = result[3];
    uniqueID[3] = result[4];

    return translate_iap_status(result[0]);
#endif
}

#if defined(FLASH_CTRL_FLASHCFG_FLASHTIM_MASK)
/*!
 * @brief Flash memory access time.
 *
 * This function is used to configure the access time to the flash memory.
 *
 * @param accessTime Flash memory access time FLASHTIM +1 is equal to the
 *                   number of system clocks used for flash access.
 */
void IAP_ConfigAccessFlashTime(uint32_t accessTime)
{
    uint32_t temp;
    temp = FLASH_CTRL->FLASHCFG;
    temp &= ~FLASH_CTRL_FLASHCFG_FLASHTIM_MASK;
    FLASH_CTRL->FLASHCFG = temp | FLASH_CTRL_FLASHCFG_FLASHTIM(accessTime);
}
#endif

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
status_t IAP_ReadFactorySettings(uint32_t dstRegAddr, uint32_t *factoryValue)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadFactorySettings;
    command[1] = dstRegAddr;
    iap_entry(command, result);
    *factoryValue = result[1];

    return translate_iap_status(result[0]);
}
#endif /* FSL_FEATURE_IAP_HAS_READ_FACTORY_SETTINGS_FUNCTION */

#if defined(FSL_FEATURE_IAP_HAS_FLASH_FUNCTION) && FSL_FEATURE_IAP_HAS_FLASH_FUNCTION
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
status_t IAP_PrepareSectorForWrite(uint32_t startSector, uint32_t endSector)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_PrepareSectorforWrite;
    command[1] = startSector;
    command[2] = endSector;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

/*!
 * @brief Copy RAM to flash.
 *
 * This function programs the flash memory. Corresponding sectors must be prepared via IAP_PrepareSectorForWrite before
 * calling this function. The addresses should be a 256 byte boundary and the number of bytes should be 256 | 512 |
 * 1024 | 4096.
 *
 * @param dstAddr Destination flash address where data bytes are to be written.
 * @param srcAddr Source ram address from where data bytes are to be read.
 * @param numOfBytes Number of bytes to be written.
 * @param systemCoreClock SystemCoreClock in Hz. It is converted to KHz before calling the rom IAP function. When the
 * flash controller has a fixed reference clock, this parameter is bypassed.
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
status_t IAP_CopyRamToFlash(uint32_t dstAddr, uint32_t *srcAddr, uint32_t numOfBytes, uint32_t systemCoreClock)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_CopyRamToFlash;
    command[1] = dstAddr;
    command[2] = (uint32_t)srcAddr;
    command[3] = numOfBytes;
#if !(defined(FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK) && FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK)
    command[4] = systemCoreClock / HZ_TO_KHZ_DIV;
#endif /* FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK */
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_EraseSector(uint32_t startSector, uint32_t endSector, uint32_t systemCoreClock)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_EraseSector;
    command[1] = startSector;
    command[2] = endSector;
#if !(defined(FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK) && FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK)
    command[3] = systemCoreClock / HZ_TO_KHZ_DIV;
#endif /* FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK */
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_ErasePage(uint32_t startPage, uint32_t endPage, uint32_t systemCoreClock)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ErasePage;
    command[1] = startPage;
    command[2] = endPage;
#if !(defined(FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK) && FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK)
    command[3] = systemCoreClock / HZ_TO_KHZ_DIV;
#endif /* FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK */
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_BlankCheckSector(uint32_t startSector, uint32_t endSector)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_BlankCheckSector;
    command[1] = startSector;
    command[2] = endSector;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_Compare(uint32_t dstAddr, uint32_t *srcAddr, uint32_t numOfBytes)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_Compare;
    command[1] = dstAddr;
    command[2] = (uint32_t)srcAddr;
    command[3] = numOfBytes;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_ExtendedFlashSignatureRead(uint32_t startPage, uint32_t endPage, uint32_t numOfStates, uint32_t *signature)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ExtendedReadSignature;
    command[1] = startPage;
    command[2] = endPage;
    command[3] = numOfStates;
    command[4] = 0;
    iap_entry(command, result);
    signature[0] = result[4];
    signature[1] = result[3];
    signature[2] = result[2];
    signature[3] = result[1];

    return translate_iap_status(result[0]);
}
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
status_t IAP_ReadFlashSignature(uint32_t *signature)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadSignature;
    iap_entry(command, result);
    *signature = result[1];

    return translate_iap_status(result[0]);
}
#endif /* FSL_FEATURE_IAP_HAS_FLASH_SIGNATURE_READ */
#endif /* FSL_FEATURE_IAP_HAS_FLASH_FUNCTION */

#if (defined(FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION) && (FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION == 1))
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
status_t IAP_ReadEEPROMPage(uint32_t pageNumber, uint32_t *dstAddr, uint32_t systemCoreClock)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadEEPROMPage;
    command[1] = pageNumber;
    command[2] = (uint32_t)dstAddr;
    command[3] = systemCoreClock / HZ_TO_KHZ_DIV;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_WriteEEPROMPage(uint32_t pageNumber, uint32_t *srcAddr, uint32_t systemCoreClock)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_WriteEEPROMPage;
    command[1] = pageNumber;
    command[2] = (uint32_t)srcAddr;
    command[3] = systemCoreClock / HZ_TO_KHZ_DIV;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}
#endif /* FSL_FEATURE_IAP_HAS_EEPROM_FUNCTION */

#if defined(FSL_FEATURE_IAP_HAS_FAIM_FUNCTION) && FSL_FEATURE_IAP_HAS_FAIM_FUNCTION
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
status_t IAP_ReadFAIMPage(uint32_t pageNumber, uint32_t *dstAddr)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_ReadFAIMPage;
    command[1] = pageNumber;
    command[2] = (uint32_t)dstAddr;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}

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
status_t IAP_WriteFAIMPage(uint32_t pageNumber, uint32_t *srcAddr)
{
    uint32_t command[5] = {0x00U};
    uint32_t result[5]  = {0x00U};

    command[0] = (uint32_t)kIapCmd_IAP_WriteFAIMPage;
    command[1] = pageNumber;
    command[2] = (uint32_t)srcAddr;
    iap_entry(command, result);

    return translate_iap_status(result[0]);
}
#endif /* FSL_FEATURE_IAP_HAS_FAIM_FUNCTION */
