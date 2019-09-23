/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _CRC16_H_
#define _CRC16_H_

#include <stdint.h>

//! @addtogroup crc16
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief State information for the CRC16 algorithm.
typedef struct Crc16Data
{
    uint16_t currentCrc; //!< Current CRC value.
} crc16_data_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C" {
#endif

//! @name CRC16
//@{

//! @brief Initializes the parameters of the crc function, must be called first.
//!
//! @param crc16Config Instantiation of the data structure of type crc16_data_t.
void crc16_init(crc16_data_t *crc16Config);

//! @brief A "running" crc calculator that updates the crc value after each call.
//!
//! @param crc16Config Instantiation of the data structure of type crc16_data_t.
//! @param src Pointer to the source buffer of data.
//! @param lengthInBytes The length, given in bytes (not words or long-words).
void crc16_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes);

//! @brief Calculates the final crc value, padding with zeros if necessary, must be called last.
//!
//! @param crc16Config Instantiation of the data structure of type crc16_data_t.
//! @param hash Pointer to the value returned for the final calculated crc value.
void crc16_finalize(crc16_data_t *crc16Config, uint16_t *hash);

void crc16_onfi_init(crc16_data_t *crc16Config);

void crc16_onfi_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes);

//@}

#if __cplusplus
}
#endif

//! @}

#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
