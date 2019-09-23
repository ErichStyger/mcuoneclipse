/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _CRC_H_
#define _CRC_H_

#include <stdint.h>
#include "bootloader_common.h"

//! @addtogroup crc32
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief State information for the CRC32 algorithm.
typedef struct Crc32Data
{
    uint32_t currentCrc;   //!< Current CRC value.
    uint32_t byteCountCrc; //!< Number of bytes processed.
} crc32_data_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C" {
#endif

//! @name CRC32
//@{

//! @brief Initializes the parameters of the crc function, must be called first
//!
//! @param crc32Config Instantiation of the data structure of type crc32_data_t
//! @retval kStatus_Success
void crc32_init(crc32_data_t *crc32Config);

//! @brief A "running" crc calculator that updates the crc value after each call
//!
//! @param crc32Config Instantiation of the data structure of type crc32_data_t
//! @param src Pointer to the source buffer of data
//! @param lengthInBytes The length, given in bytes (not words or long-words)
//! @retval kStatus_Success
void crc32_update(crc32_data_t *crc32Config, const uint8_t *src, uint32_t lengthInBytes);

//! @brief Calculates the final crc value, padding with zeros if necessary, must be called last
//!
//! @param crc32Config Instantiation of the data structure of type crc32_data_t
//! @param hash Pointer to the value returned for the final calculated crc value
//! @retval kStatus_Success
void crc32_finalize(crc32_data_t *crc32Config, uint32_t *hash);

//@}

#if __cplusplus
}
#endif

//! @}

#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
