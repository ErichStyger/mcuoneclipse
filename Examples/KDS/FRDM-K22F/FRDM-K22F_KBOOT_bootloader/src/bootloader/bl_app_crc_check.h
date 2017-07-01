/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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

#ifndef __APP_CRC_CHECK_H__
#define __APP_CRC_CHECK_H__

#include <stdint.h>
#include "bootloader_common.h"

//! @addtogroup app_crc_check
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Application crc check status codes.
enum _crc_check_status
{
    kStatus_AppCrcCheckPassed = MAKE_STATUS(kStatusGroup_AppCrcCheck, 0), //!< Crc check is valid and passed.
    kStatus_AppCrcCheckFailed = MAKE_STATUS(kStatusGroup_AppCrcCheck, 1), //!< Crc check is valid but failed.
    kStatus_AppCrcCheckInactive =
        MAKE_STATUS(kStatusGroup_AppCrcCheck, 2), //!< Crc check is inactive, Needs to be verified.
    kStatus_AppCrcCheckInvalid =
        MAKE_STATUS(kStatusGroup_AppCrcCheck,
                    3), //!< Crc check is invalid, As the BCA is invalid or crc parameters are unset (all 0xff bytes).
    kStatus_AppCrcCheckOutOfRange =
        MAKE_STATUS(kStatusGroup_AppCrcCheck, 4) //!< Crc check is valid but addresses are out of range.
};

//! @brief CRC Checksum Header
typedef struct _crc_checksum_header
{
    uint32_t tag; //!< [00:03] Tag value used to validate the bootloader configuration data. Must be set to 'kcfg'.
    uint32_t crcStartAddress;  //!< [04:07]
    uint32_t crcByteCount;     //!< [08:0b]
    uint32_t crcExpectedValue; //!< [0c:0f]
} crc_checksum_header_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C" {
#endif

//! @name Crc check
//@{

#if BL_FEATURE_CRC_ASSERT
//! @brief Restore crc check failure pin to default state.
void restore_crc_check_failure_pin(void);
#endif

//! @brief Initialize crc check status property based on BCA related fields.
void init_crc_check_status(property_store_t *propertyStore);

//! @brief Compare the CRC on a range of flash(specified in BCA) against a precomputed CRC value(stored in the BCA).
bool is_application_crc_check_pass(void);

//! @brief Calculate CRC checksum according to specified checksum header
uint32_t calculate_application_crc32(crc_checksum_header_t *header, uint32_t crcHeaderStart);

//@}

#if __cplusplus
}
#endif

//! @}

#endif // __APP_CRC_CHECK_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
