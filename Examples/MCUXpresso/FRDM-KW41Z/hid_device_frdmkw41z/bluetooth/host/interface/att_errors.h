/*! *********************************************************************************
 * \addtogroup GATT
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file att_errors.h
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

#ifndef _ATT_ERRORS_H_
#define _ATT_ERRORS_H_

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! ATT error codes */
typedef enum
{
    gAttErrCodeNoError_c                         = 0x00,
    gAttErrCodeInvalidHandle_c                   = 0x01,
    gAttErrCodeReadNotPermitted_c                = 0x02,
    gAttErrCodeWriteNotPermitted_c               = 0x03,
    gAttErrCodeInvalidPdu_c                      = 0x04,
    gAttErrCodeInsufficientAuthentication_c      = 0x05,
    gAttErrCodeRequestNotSupported_c             = 0x06,
    gAttErrCodeInvalidOffset_c                   = 0x07,
    gAttErrCodeInsufficientAuthorization_c       = 0x08,
    gAttErrCodePrepareQueueFull_c                = 0x09,
    gAttErrCodeAttributeNotFound_c               = 0x0A,
    gAttErrCodeAttributeNotLong_c                = 0x0B,
    gAttErrCodeInsufficientEncryptionKeySize_c   = 0x0C,
    gAttErrCodeInvalidAttributeValueLength_c     = 0x0D,
    gAttErrCodeUnlikelyError_c                   = 0x0E,
    gAttErrCodeInsufficientEncryption_c          = 0x0F,
    gAttErrCodeUnsupportedGroupType_c            = 0x10,
    gAttErrCodeInsufficientResources_c           = 0x11,
 /* Reserved Error Opcodes                          = 0x12 - 0x7F */
 /* Application Error Opcodes                       = 0x80 - 0x9F */
 /* Reserved Error Opcodes                          = 0xA0 - 0xDF */
 /* Common Profile And Service Error Opcodes        = 0xE0 - 0xFF */
} attErrorCode_t;

/*! Prepare Write Request Parameters Structure used by external reference */
typedef struct attPrepareWriteRequestParams_tag
{
    uint16_t attributeHandle;
    uint16_t valueOffset;
    uint8_t  attributeValue[gAttMaxMtu_c - 5];
    uint16_t attributeLength;
} attPrepareWriteRequestParams_t;

#endif /* _ATT_ERRORS_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
