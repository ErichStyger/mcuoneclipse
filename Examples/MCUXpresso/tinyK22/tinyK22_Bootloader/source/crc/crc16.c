/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "bootloader_common.h"
#include "crc/crc16.h"
#include "utilities/fsl_assert.h"
#include "utilities/fsl_rtos_abstraction.h"

#include "fsl_device_registers.h"
#include "utilities/fsl_rtos_abstraction.h"

#if FSL_FEATURE_SOC_CRC_COUNT && !defined(BL_TARGET_RAM)
#if !BL_DEVICE_IS_LPC_SERIES
#include "fsl_crc.h"
#else // BL_DEVICE_IS_LPC_SERIES
#include "lpc_crc/fsl_crc.h"
#endif // !BL_DEVICE_IS_LPC_SERIES

/* Table of base addresses for crc instances. */
static CRC_Type *const g_crcBase[1] = CRC_BASE_PTRS;

void crc16_init(crc16_data_t *crc16Config)
{
    assert(crc16Config);

    crc16Config->currentCrc = 0x0000U;
}

void crc16_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes)
{
    assert(crc16Config);
    assert(src);

    crc_config_t crcUserConfigPtr;

    CRC_GetDefaultConfig(&crcUserConfigPtr);

#if !BL_DEVICE_IS_LPC_SERIES
    crcUserConfigPtr.crcBits = kCrcBits16;
    crcUserConfigPtr.seed = crc16Config->currentCrc;
    crcUserConfigPtr.polynomial = 0x1021U;
    crcUserConfigPtr.complementChecksum = false;
    crcUserConfigPtr.reflectIn = false;
    crcUserConfigPtr.reflectOut = false;
#else // BL_DEVICE_IS_LPC_SERIES
    crcUserConfigPtr.seed = crc16Config->currentCrc;
    crcUserConfigPtr.polynomial = kCRC_Polynomial_CRC_CCITT;
    crcUserConfigPtr.reverseIn = false;
    crcUserConfigPtr.reverseOut = false;
    crcUserConfigPtr.complementIn = false;
    crcUserConfigPtr.complementOut = false;
#endif // !BL_DEVICE_IS_LPC_SERIES

    // Init CRC module and then run it
    //! Note: We must init CRC module here, As we may seperate one crc calculation into several times
    //! Note: It is better to use lock to ensure the integrity of current updating operation of crc calculation
    //        in case crc module is shared by multiple crc updating requests at the same time
    if (lengthInBytes)
    {
        lock_acquire();
        CRC_Init(g_crcBase[0], &crcUserConfigPtr);
        CRC_WriteData(g_crcBase[0], src, lengthInBytes);
        crcUserConfigPtr.seed = CRC_Get16bitResult(g_crcBase[0]);
        lock_release();
    }

    crc16Config->currentCrc = crcUserConfigPtr.seed;
}

void crc16_finalize(crc16_data_t *crc16Config, uint16_t *hash)
{
    assert(crc16Config);
    assert(hash);

    *hash = crc16Config->currentCrc;

    // De-init CRC module when we complete a full crc calculation
    CRC_Deinit(g_crcBase[0]);
}

void crc16_onfi_init(crc16_data_t *crc16Config)
{
    assert(crc16Config);

    crc16Config->currentCrc = 0x4F4EU;
}

void crc16_onfi_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes)
{
    assert(crc16Config);
    assert(src);

    crc_config_t crcUserConfigPtr;

    CRC_GetDefaultConfig(&crcUserConfigPtr);

    crcUserConfigPtr.crcBits = kCrcBits16;
    crcUserConfigPtr.seed = crc16Config->currentCrc;
    crcUserConfigPtr.polynomial = 0x8005U;
    crcUserConfigPtr.complementChecksum = false;
    crcUserConfigPtr.reflectIn = false;
    crcUserConfigPtr.reflectOut = false;

    // Init CRC module and then run it
    //! Note: We must init CRC module here, As we may seperate one crc calculation into several times
    //! Note: It is better to use lock to ensure the integrity of current updating operation of crc calculation
    //        in case crc module is shared by multiple crc updating requests at the same time
    if (lengthInBytes)
    {
        lock_acquire();
        CRC_Init(g_crcBase[0], &crcUserConfigPtr);
        CRC_WriteData(g_crcBase[0], src, lengthInBytes);
        crcUserConfigPtr.seed = CRC_Get16bitResult(g_crcBase[0]);
        lock_release();
    }

    crc16Config->currentCrc = crcUserConfigPtr.seed;
}

#else
////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
void crc16_init(crc16_data_t *crc16Config)
{
    assert(crc16Config);

    // initialize running crc and byte count
    crc16Config->currentCrc = 0;
}

void crc16_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes)
{
    assert(crc16Config);
    assert(src);

    uint32_t crc = crc16Config->currentCrc;

    uint32_t j;
    for (j = 0; j < lengthInBytes; ++j)
    {
        uint32_t i;
        uint32_t byte = src[j];
        crc ^= byte << 8;
        for (i = 0; i < 8; ++i)
        {
            uint32_t temp = crc << 1;
            if (crc & 0x8000)
            {
                temp ^= 0x1021;
            }
            crc = temp;
        }
    }

    crc16Config->currentCrc = crc;
}

void crc16_finalize(crc16_data_t *crc16Config, uint16_t *hash)
{
    assert(crc16Config);
    assert(hash);

    *hash = crc16Config->currentCrc;
}

void crc16_onfi_init(crc16_data_t *crc16Config)
{
    assert(crc16Config);

    // initialize running crc and byte count
    crc16Config->currentCrc = 0x4F4EU;
}

void crc16_onfi_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes)
{
    assert(crc16Config);
    assert(src);

    uint32_t crc = crc16Config->currentCrc;

    uint32_t j;
    for (j = 0; j < lengthInBytes; ++j)
    {
        uint32_t i;
        uint32_t byte = src[j];
        crc ^= byte << 8;
        for (i = 0; i < 8; ++i)
        {
            uint32_t temp = crc << 1;
            if (crc & 0x8000)
            {
                temp ^= 0x8005U;
            }
            crc = temp;
        }
    }

    crc16Config->currentCrc = crc;
}
#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
