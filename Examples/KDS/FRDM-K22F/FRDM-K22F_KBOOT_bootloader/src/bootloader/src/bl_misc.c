/*
 * Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
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
#include "bootloader/bootloader.h"
#include "memory/memory.h"
#include "sbloader/sbloader.h"
#include "property/property.h"
#include "utilities/fsl_assert.h"
#if BL_FEATURE_QSPI_MODULE
#include "qspi/qspi.h"
#endif
#if BL_FEATURE_OTFAD_MODULE
#include "otfad/fsl_otfad_driver.h"
#endif
#include <string.h>
#include <stdint.h>
#include "fsl_device_registers.h"
#include "flash/fsl_flash.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define FTFx_FOPT_BOOTSRCSEL_MASK 0xC0U  //!< bit mask for FOPT[BOOTSRC_SEL]
#define FTFx_FOPT_BOOTSRCSEL_SHIFT 0x06U //!< shift bit for FOPT[BOOTSRC_SEL]

//! @brief Get FOPT value from FTFx Module
#if defined(FTFA)
#define FTFx_FOPT FTFA->FOPT
#elif defined(FTFL)
#define FTFx_FOPT FTFL->FOPT
#elif defined(FTFE)
#define FTFx_FOPT FTFE->FOPT
#endif

enum
{
    //! @brief Boot Source indicating that code is running from rom, needn't to configure QSPI module
    kBootSource_ROM = 0x03,
    //! @brief Boot source indicating that code is running from rom, need to configure QSPI module
    kBootSource_QSPI = 0x02,

    //! @brief OTFAD module instance number
    kOtfadInstance = 0,

    //! @brief Address of key blob array on internal flash
    kKeyBlobAddress = 0x410
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
#if BL_FEATURE_QSPI_MODULE
status_t s_qspi_otfad_init_status = kStatus_QspiNotConfigured;
#endif // #if BL_FEATURE_QSPI_MODULE

#if BL_FEATURE_OTFAD_MODULE
static bool s_isOtfadEnabled = false;
#endif
////////////////////////////////////////////////////////////////////////////////
// Local function prototypes
////////////////////////////////////////////////////////////////////////////////

#if BL_FEATURE_OTFAD_MODULE
static status_t get_otfad_key(otfad_kek_t *kek);
#endif // BL_FEATURE_OTFAD_MODULE

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bootloader_common.h for documentation on this function
bool qspi_need_configure(void)
{
#if BL_FEATURE_QSPI_MODULE
    return true;
#else
    return false;
#endif
}

// See bootloader_common.h for documentation on this function
#if BL_FEATURE_OTFAD_MODULE
status_t otfad_init_as_needed(void)
{
    uint32_t keyBlobAddress;

    // Initialize OTFAD module, if present.
    if (is_otfad_present())
    {
        otfad_kek_t otfadKek;
        status_t status = get_otfad_key(&otfadKek);
        if (status == kStatus_OtfadInvalidKey)
        {
            // KEK was not programmed, so must assume code is not
            // encrypted on QSPI. Bypass OTFAD.
            return kStatus_Success;
        }

        // Reload the BCA in case the keyBlobPointer in BCA has been updated.
        g_bootloaderContext.propertyInterface->load_user_config();
        // If we have a valid key blob address in the BCA use that
        if (g_bootloaderContext.propertyInterface->store->configurationData.keyBlobPointer != ~0)
        {
            keyBlobAddress = g_bootloaderContext.propertyInterface->store->configurationData.keyBlobPointer;
        }
        // Otherwise use the default
        else
        {
            keyBlobAddress = kKeyBlobAddress;
        }

        status = otfad_init(kOtfadInstance, (uint8_t *)keyBlobAddress, &otfadKek);

        // Clear otfadKek memory on stack.
        memset(&otfadKek, 0, sizeof(otfadKek));

        if (status == kStatus_Success)
        {
            s_isOtfadEnabled = true;
        }

        return status;
    }
    else
    {
        return kStatus_Success;
    }
}

// See bootloader_common.h for documentation on this function
status_t otfad_bypass_as_needed(void)
{
    if (s_isOtfadEnabled)
    {
        otfad_bypass(kOtfadInstance);
    }

    return kStatus_Success;
}

// See bootloader_common.h for documentation on this function
status_t oftfad_resume_as_needed(void)
{
    if (s_isOtfadEnabled)
    {
        otfad_resume(kOtfadInstance);
    }

    return kStatus_Success;
}

#endif // BL_FEATURE_OTFAD_MODULE

// See bootloader_common.h for documentation on this function
bool is_qspi_present(void)
{
#if BL_FEATURE_QSPI_MODULE
    return is_quadspi_configured();
#else
    return false;
#endif // BL_FEATURE_QSPI_MODULE
}

// See bootloader_common.h for documentation on this function
bool is_otfad_present(void)
{
#if defined(K80F25615_SERIES) || defined(K81F25615_SERIES) || defined(K82F25615_SERIES)
    uint8_t subfamily_id = (SIM->SDID & SIM_SDID_SUBFAMID_MASK) >> SIM_SDID_SUBFAMID_SHIFT;

    // OTFAD is only available on K81 & K82 parts.
    return (subfamily_id > 0);
#else
    return false;
#endif // defined(CPU_MK80FN256VLQR15)
}

// See bootloader_common.h for documentation on this function
bool is_ltc_present(void)
{
#ifdef BL_FEATURE_ENCRYPTION_MMCAU
    return false;
#elif defined(K80F25615_SERIES) || defined(K81F25615_SERIES) || defined(K82F25615_SERIES)
    uint8_t subfamily_id = (SIM->SDID & SIM_SDID_SUBFAMID_MASK) >> SIM_SDID_SUBFAMID_SHIFT;

    // LTC is only available on K81/2 and KL81/2 devices.
    return ((subfamily_id == 1) || (subfamily_id == 2));
#elif FSL_FEATURE_SIM_HAS_MISCCTRL_LTCEN
    return (SIM->MISCCTRL & SIM_MISCCTRL_LTCEN_MASK);
#else
    return false;
#endif // BL_FEATURE_ENCRYPTION_MMCAU
}

//! @brief Read OTFAD KEK from SIM module.
//!
//! OTFAD key blob decription key (KEK) was read from IFR by hardware and placed
//! in SIM_SECKEY. It is only readable by ROM. All 0xF's means invalid because not programmed.
//! All 0x0's means invalid because security violation detected.
//!
//! @param kek Pointer to returned KEK
//! @retval kStatus_Success Key is valid
//! @retval kStatus_OtfadSecurityViolation Key is all 0
//! @retval kStatus_Fail Key is all 0xF (not programmed)
#if BL_FEATURE_OTFAD_MODULE
static status_t get_otfad_key(otfad_kek_t *kek)
{
#if BL_TARGET_FLASH
    assert(kek);

    const uint32_t *kekTable = (const uint32_t *)BL_FEATURE_OTFAD_KEK_ADDRESS;

    kek->keyWord0 = kekTable[0];
    kek->keyWord1 = kekTable[1];
    kek->keyWord2 = kekTable[2];
    kek->keyWord3 = kekTable[3];

    if (!kek->keyWord0 && !kek->keyWord1 && !kek->keyWord2 && !kek->keyWord3)
    {
        // Keys are all 0.
        return kStatus_OtfadSecurityViolation;
    }
    else if (!~kek->keyWord0 && !~kek->keyWord1 && !~kek->keyWord2 && !~kek->keyWord3)
    {
        // Keys are all 0xF.
        return kStatus_OtfadInvalidKey;
    }
    else
    {
        return kStatus_Success;
    }
#else
    return kStatus_Success;
#endif // BL_TARGET_FLASH
}
#endif // BL_HAS_OTFAD_MODULE

#if BL_FEATURE_QSPI_MODULE
//! @brief Return status for intializing qspi and otfad modules
status_t get_qspi_otfad_init_status(void)
{
    return s_qspi_otfad_init_status;
}

//!@bief Update status for intializing qspi and otfad modules
void update_qspi_otfad_init_status(status_t initStatus)
{
    s_qspi_otfad_init_status = initStatus;
    g_bootloaderContext.propertyInterface->store->qspiInitStatus = s_qspi_otfad_init_status;
}
#endif // #if BL_FEATURE_QSPI_MODULE

bool is_in_execute_only_region(uint32_t start, uint32_t lengthInBytes)
{
#if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
    flash_execute_only_access_state_t state = kFLASH_AccessStateUnLimited;
    g_bootloaderContext.flashDriverInterface->flash_is_execute_only(&g_bootloaderContext.flashState, start,
                                                                    lengthInBytes, &state);
    if (state == kFLASH_AccessStateUnLimited)
    {
        return false;
    }
    else
    {
        return true;
    }
#else
    return false;
#endif // FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
