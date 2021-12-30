/*
 * Copyright 2018 - 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PRINCE_H_
#define _FSL_PRINCE_H_

#include "fsl_common.h"
#include "fsl_iap_ffr.h"
#include "fsl_puf.h"

/*!
 * @addtogroup prince
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief PRINCE driver version 2.3.2.
 *
 * Current version: 2.3.2
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version.
 * - Version 2.1.0
 *   - Update for the A1 rev. of LPC55Sxx serie.
 * - Version 2.2.0
 *   - Add runtime checking of the A0 and A1 rev. of LPC55Sxx serie to support
 *     both silicone revisions.
 * - Version 2.3.0
 *   - Add support for LPC55S1x and LPC55S2x series
 * - Version 2.3.0
 *   - Fix MISRA-2012 issues.
 * - Version 2.3.1
 *   - Add support for LPC55S0x series
 * - Version 2.3.2
 *   - Fix documentation of enumeration. Extend PRINCE example.
 */
#define FSL_PRINCE_DRIVER_VERSION (MAKE_VERSION(2, 3, 2))
/*@}*/

#if (defined(LPC55S04_SERIES) || defined(LPC55S06_SERIES))

#define FSL_PRINCE_DRIVER_LPC55S0x

#elif (defined(LPC55S14_SERIES) || defined(LPC55S16_SERIES))

#define FSL_PRINCE_DRIVER_LPC55S1x

#elif (defined(LPC55S26_SERIES) || defined(LPC55S28_SERIES))

#define FSL_PRINCE_DRIVER_LPC55S2x

#elif (defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES) || \
       defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES))

#define FSL_PRINCE_DRIVER_LPC55S6x

#else
#error "No valid CPU defined!"

#endif

#define FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB (8U)
#define FSL_PRINCE_DRIVER_MAX_FLASH_ADDR \
    ((uint32_t)FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES - (FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 2U * 1024U))

#if !defined(ALIGN_DOWN)
#define ALIGN_DOWN(x, a) ((x) & (uint32_t)(-((int32_t)(a))))
#endif

/*! @brief Secure status enumeration. */
typedef enum _skboot_status
{
    kStatus_SKBOOT_Success               = 0x5ac3c35au, /*!< PRINCE Success */
    kStatus_SKBOOT_Fail                  = 0xc35ac35au, /*!< PRINCE Fail */
    kStatus_SKBOOT_InvalidArgument       = 0xc35a5ac3u, /*!< PRINCE Invalid argument */
    kStatus_SKBOOT_KeyStoreMarkerInvalid = 0xc3c35a5au, /*!< PRINCE Invalid marker */
} skboot_status_t;

/*! @brief Secure boolean enumeration. */
typedef enum _secure_bool
{
    kSECURE_TRUE  = 0xc33cc33cU, /*!< PRINCE true */
    kSECURE_FALSE = 0x5aa55aa5U, /*!< PRINCE false */
} secure_bool_t;

/*! @brief Prince region. */
typedef enum _prince_region
{
    kPRINCE_Region0 = 0U, /*!< PRINCE region 0 */
    kPRINCE_Region1 = 1U, /*!< PRINCE region 1 */
    kPRINCE_Region2 = 2U, /*!< PRINCE region 2 */
} prince_region_t;

/*! @brief Prince lock. */
typedef enum _prince_lock
{
    kPRINCE_Region0Lock = 1U,   /*!< PRINCE region 0 lock */
    kPRINCE_Region1Lock = 2U,   /*!< PRINCE region 1 lock */
    kPRINCE_Region2Lock = 4U,   /*!< PRINCE region 2 lock */
    kPRINCE_MaskLock    = 256U, /*!< PRINCE mask register lock */
} prince_lock_t;

/*! @brief Prince flag. */
typedef enum _prince_flags
{
    kPRINCE_Flag_None       = 0U, /*!< PRINCE Flag None */
    kPRINCE_Flag_EraseCheck = 1U, /*!< PRINCE Flag Erase check */
    kPRINCE_Flag_WriteCheck = 2U, /*!< PRINCE Flag Write check */
} prince_flags_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable data encryption.
 *
 * This function enables PRINCE on-the-fly data encryption.
 *
 * @param base PRINCE peripheral address.
 */
static inline void PRINCE_EncryptEnable(PRINCE_Type *base)
{
    base->ENC_ENABLE = 1;
}

/*!
 * @brief Disable data encryption.
 *
 * This function disables PRINCE on-the-fly data encryption.
 *
 * @param base PRINCE peripheral address.
 */
static inline void PRINCE_EncryptDisable(PRINCE_Type *base)
{
    base->ENC_ENABLE = 0;
}

/*!
 * @brief Sets PRINCE data mask.
 *
 * This function sets the PRINCE mask that is used to mask decrypted data.
 *
 * @param base PRINCE peripheral address.
 * @param mask 64-bit data mask value.
 */
static inline void PRINCE_SetMask(PRINCE_Type *base, uint64_t mask)
{
    base->MASK_LSB = (uint32_t)(mask & 0xffffffffu);
    base->MASK_MSB = (uint32_t)(mask >> 32u);
}

/*!
 * @brief Locks access for specified region registers or data mask register.
 *
 * This function sets lock on specified region registers or mask register.
 *
 * @param base PRINCE peripheral address.
 * @param lock registers to lock. This is a logical OR of members of the
 *             enumeration ::prince_lock_t
 */
static inline void PRINCE_SetLock(PRINCE_Type *base, uint32_t lock)
{
    base->LOCK = lock & 0x1ffu;
}

/*!
 * @brief Generate new IV code.
 *
 * This function generates new IV code and stores it into the persistent memory.
 * Ensure about 800 bytes free space on the stack when calling this routine with the store parameter set to true!
 *
 * @param region PRINCE region index.
 * @param iv_code IV code pointer used for storing the newly generated 52 bytes long IV code.
 * @param store flag to allow storing the newly generated IV code into the persistent memory (FFR).
 * @param flash_context pointer to the flash driver context structure.
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise, kStatus_Fail is also returned if the key code for the particular
 *                         PRINCE region is not present in the keystore (though new IV code has been provided)
 */
status_t PRINCE_GenNewIV(prince_region_t region, uint8_t *iv_code, bool store, flash_config_t *flash_context);

/*!
 * @brief Load IV code.
 *
 * This function enables IV code loading into the PRINCE bus encryption engine.
 *
 * @param region PRINCE region index.
 * @param iv_code IV code pointer used for passing the IV code.
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise
 */
status_t PRINCE_LoadIV(prince_region_t region, uint8_t *iv_code);

/*!
 * @brief Allow encryption/decryption for specified address range.
 *
 * This function sets the encryption/decryption for specified address range.
 * The SR mask value for the selected Prince region is calculated from provided
 * start_address and length parameters. This calculated value is OR'ed with the
 * actual SR mask value and stored into the PRINCE SR_ENABLE register and also
 * into the persistent memory (FFR) to be used after the device reset. It is
 * possible to define several nonadjacent encrypted areas within one Prince
 * region when calling this function repeatedly. If the length parameter is set
 * to 0, the SR mask value is set to 0 and thus the encryption/decryption for
 * the whole selected Prince region is disabled.
 * Ensure about 800 bytes free space on the stack when calling this routine!
 *
 * @param region PRINCE region index.
 * @param start_address start address of the area to be encrypted/decrypted.
 * @param length length of the area to be encrypted/decrypted.
 * @param flash_context pointer to the flash driver context structure.
 * @param regenerate_iv flag to allow IV code regenerating, storing into
 *        the persistent memory (FFR) and loading into the PRINCE engine
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise
 */
status_t PRINCE_SetEncryptForAddressRange(
    prince_region_t region, uint32_t start_address, uint32_t length, flash_config_t *flash_context, bool regenerate_iv);

/*!
 * @brief Gets the PRINCE Sub-Region Enable register.
 *
 * This function gets PRINCE SR_ENABLE register.
 *
 * @param base PRINCE peripheral address.
 * @param region PRINCE region index.
 * @param sr_enable Sub-Region Enable register pointer.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_GetRegionSREnable(PRINCE_Type *base, prince_region_t region, uint32_t *sr_enable);

/*!
 * @brief Gets the PRINCE region base address register.
 *
 * This function gets PRINCE BASE_ADDR register.
 *
 * @param base PRINCE peripheral address.
 * @param region PRINCE region index.
 * @param region_base_addr Region base address pointer.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_GetRegionBaseAddress(PRINCE_Type *base, prince_region_t region, uint32_t *region_base_addr);

/*!
 * @brief Sets the PRINCE region IV.
 *
 * This function sets specified AES IV for the given region.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param iv 64-bit AES IV in little-endian byte order.
 */
status_t PRINCE_SetRegionIV(PRINCE_Type *base, prince_region_t region, const uint8_t iv[8]);

/*!
 * @brief Sets the PRINCE region base address.
 *
 * This function configures PRINCE region base address.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param region_base_addr Base Address for region.
 */
status_t PRINCE_SetRegionBaseAddress(PRINCE_Type *base, prince_region_t region, uint32_t region_base_addr);

/*!
 * @brief Sets the PRINCE Sub-Region Enable register.
 *
 * This function configures PRINCE SR_ENABLE register.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param sr_enable Sub-Region Enable register value.
 */
status_t PRINCE_SetRegionSREnable(PRINCE_Type *base, prince_region_t region, uint32_t sr_enable);

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length. It deals with the flash erase function
 * complenentary to the standard erase API of the IAP1 driver. This implementation
 * additionally checks if the whole encrypted PRINCE subregions are erased at once
 * to avoid secrets revealing. The checker implementation is limited to one contiguous
 * PRINCE-controlled memory area.
 *
 * @param config The pointer to the flash driver context structure.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address needs to be prince-sburegion-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be prince-sburegion-size-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @return #kStatus_FLASH_Success API was executed successfully.
 * @return #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @return #kStatus_FLASH_AlignmentError The parameter is not aligned with the specified baseline.
 * @return #kStatus_FLASH_AddressError The address is out of range.
 * @return #kStatus_FLASH_EraseKeyError The API erase key is invalid.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 * @return #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @return #kStatus_FLASH_EncryptedRegionsEraseNotDoneAtOnce Encrypted flash subregions are not erased at once.
 */
status_t PRINCE_FlashEraseWithChecker(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length. It deals with the
 * flash program function complenentary to the standard program API of the IAP1 driver.
 * This implementation additionally checks if the whole PRINCE subregions are
 * programmed at once to avoid secrets revealing. The checker implementation is limited
 * to one contiguous PRINCE-controlled memory area.
 *
 * @param config The pointer to the flash driver context structure.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              prince-sburegion-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be prince-sburegion-size-aligned.
 *
 * @return #kStatus_FLASH_Success API was executed successfully.
 * @return #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @return #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @return #kStatus_FLASH_AddressError Address is out of range.
 * @return #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 * @return #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @return #kStatus_FLASH_SizeError Encrypted flash subregions are not programmed at once.
 */
status_t PRINCE_FlashProgramWithChecker(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);

#if (defined(FSL_PRINCE_DRIVER_LPC55S0x)) || defined(FSL_PRINCE_DRIVER_LPC55S1x)
/*!
 * @brief Gets the PRINCE Error status register.
 *
 * @param base PRINCE peripheral address.
 *
 * @return PRINCE Error status register
 */
static inline uint32_t PRINCE_GetErrorStatus(PRINCE_Type *base)
{
    return base->ERR;
}

/*!
 * @brief Clears the PRINCE Error status register.
 *
 * @param base PRINCE peripheral address.
 */
static inline void PRINCE_ClearErrorStatus(PRINCE_Type *base)
{
    base->ERR = 0U;
}
#endif /* defined(FSL_PRINCE_DRIVER_LPC55S0x) || defined(FSL_PRINCE_DRIVER_LPC55S1x) */

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _FSL_PRINCE_H_ */
