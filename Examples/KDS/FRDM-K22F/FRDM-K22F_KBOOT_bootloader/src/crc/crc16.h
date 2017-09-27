/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

//@}

#if __cplusplus
}
#endif

//! @}

#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
