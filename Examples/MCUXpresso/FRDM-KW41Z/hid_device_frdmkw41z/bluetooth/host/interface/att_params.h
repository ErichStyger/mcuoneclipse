/*! *********************************************************************************
* \addtogroup ATT
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.

* \file att_params.h
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

#ifndef _ATT_PARAMS_H_
#define _ATT_PARAMS_H_

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! Error Response Parameters */
typedef struct attErrorResponseParams_tag
{
    attOpcode_t    requestOpcodeInError;
    uint16_t       attributeHandleInError;
    attErrorCode_t errorCode;
} attErrorResponseParams_t;

/*! Exchange MTU Request Parameters */
typedef struct attExchangeMtuRequestParams_tag
{
    uint16_t clientRxMtu;
} attExchangeMtuRequestParams_t;

/*! Exchange MTU Response Parameters */
typedef struct attExchangeMtuResponseParams_tag
{
    uint16_t serverRxMtu;
} attExchangeMtuResponseParams_t;

/*! Find Information Request Parameters */
typedef struct attFindInformationRequestParams_tag
{
    uint16_t startingHandle;
    uint16_t endingHandle;
} attFindInformationRequestParams_t;

typedef struct attFindInfoHandleUuid16Pair_tag
{
    uint16_t handle;
    uint16_t uuid16;
} attFindInfoHandleUuid16Pair_t;
typedef struct attFindInfoHandleUuid128Pair_tag
{
    uint16_t handle;
    uint8_t  uuid128[16];
} attFindInfoHandleUuid128Pair_t;

/*! Find Information Response Parameters */
typedef struct attFindInformationResponseParams_tag
{
    attUuidFormat_t format;
    uint8_t         handleUuidPairCount;
    union
    {
        attFindInfoHandleUuid16Pair_t  handleUuid16[(gAttMaxDataSize_d(gAttMaxMtu_c) - 1)/4]; /* 4 = 2+2 bytes per handle-UUID pair */
        attFindInfoHandleUuid128Pair_t handleUuid128[(gAttMaxDataSize_d(gAttMaxMtu_c) - 1)/18]; /* 18 = 2+16 bytes per handle-UUID pair */
    }               informationData;
} attFindInformationResponseParams_t;

/*! Find By Type Value Request Parameters */
typedef struct attFindByTypeValueRequestParams_tag
{
    uint16_t startingHandle;
    uint16_t endingHandle;
    uint16_t attributeType; /* 16 bit UUID */
    uint8_t  attributeValue[gAttMaxDataSize_d(gAttMaxMtu_c) - 6]; /* 6 = 4 for handles + 2 for type */
    uint16_t attributeLength;
} attFindByTypeValueRequestParams_t;

typedef attFindInformationRequestParams_t attFindByTypeValueHandleGroupPair_t;

/*! Find By Type Value Response - Parameters */
typedef struct attFindByTypeValueResponseParams_tag
{
    attFindByTypeValueHandleGroupPair_t handleGroup[gAttMaxDataSize_d(gAttMaxMtu_c)/4]; /* 4 bytes for starting and ending handle */
    uint16_t                            groupCount;
} attFindByTypeValueResponseParams_t;

/*! Read By Type Request Parameters */
typedef struct attReadByTypeRequestParams_tag
{
    uint16_t        startingHandle;
    uint16_t        endingHandle;
    attUuidFormat_t format;
    union
    {
        uint16_t uuid16;
        uint8_t  uuid128[16];
    }               attributeType;
} attReadByTypeRequestParams_t;

/*! Read By Type Response Parameters */
typedef struct attReadByTypeResponseParams_tag
{
    uint8_t  length; /* Fixed length of each handle+value pair in the Attribute Data List */
    uint8_t  attributeDataList[gAttMaxDataSize_d(gAttMaxMtu_c) - 1]; /* 1 byte for length */
    uint16_t attributeDataListLength;
} attReadByTypeResponseParams_t;

/*! Read Request Parameters */
typedef struct attReadRequestParams_tag
{
    uint16_t attributeHandle;
} attReadRequestParams_t;

/*! Read Response Parameters */
typedef struct attReadResponseParams_tag
{
    uint8_t  attributeValue[gAttMaxDataSize_d(gAttMaxMtu_c)];
    uint16_t attributeLength;
} attReadResponseParams_t;

/*! Read Blob Request Parameters */
typedef struct attReadBlobRequestParams_tag
{
    uint16_t attributeHandle;
    uint16_t valueOffset;
} attReadBlobRequestParams_t;

/*! Read Blob Response Parameters */
typedef attReadResponseParams_t attReadBlobResponseParams_t;

/*! Read Multiple Request Parameters */
typedef struct attReadMultipleRequestParams_tag
{
    uint16_t listOfHandles[gAttMaxDataSize_d(gAttMaxMtu_c) / 2]; /* 2 bytes for each handle */
    uint16_t handleCount;
} attReadMultipleRequestParams_t;

/*! Read Multiple Response Parameters */
typedef struct attReadMultipleResponseParams_tag
{
    uint8_t  listOfValues[gAttMaxDataSize_d(gAttMaxMtu_c)];
    uint16_t listLength;
} attReadMultipleResponseParams_t;

/*! Read By Group Type Request Parameters */
typedef attReadByTypeRequestParams_t attReadByGroupTypeRequestParams_t;

/*! Read By Group Type Response Parameters */
typedef attReadByTypeResponseParams_t attReadByGroupTypeResponseParams_t;
/* "length" = fixed length of each Handle+End Group Handle+Value in the Attribute Data List */

/*! Write Request and Write Command Parameters */
typedef struct attWriteRequestAndCommandParams_tag
{
    uint16_t  attributeHandle;
    uint8_t   attributeValue[gAttMaxWriteDataSize_d(gAttMaxMtu_c)];
    uint16_t  attributeLength;
} attWriteRequestAndCommandParams_t;

/*! Signed Write Command Parameters */
typedef struct attSignedWriteCommandParams_tag
{
    uint16_t attributeHandle;
    uint8_t  attributeValue[gAttMaxWriteDataSize_d(gAttMaxMtu_c) - gAttAuthSignatureSize];
    uint16_t attributeLength;
    uint8_t  authenticationSignature[gAttAuthSignatureSize];
} attSignedWriteCommandParams_t;

/*! Prepare Write Request and Prepare Write Response Parameters */
typedef struct attPrepareWriteRequestResponseParams_tag
{
    uint16_t attributeHandle;
    uint16_t valueOffset;
    uint8_t  attributeValue[gAttMaxPrepWriteDataSize_d(gAttMaxMtu_c)];
    uint16_t attributeLength;
} attPrepareWriteRequestResponseParams_t;

/*! Execute Write Request Parameters */
typedef struct attExecuteWriteRequestParams_tag
{
    attExecuteWriteRequestFlags_t flags;
} attExecuteWriteRequestParams_t;

/*! Handle Value Notification and Handle Value Indication Parameters */
typedef attWriteRequestAndCommandParams_t attHandleValueNotificationIndicationParams_t;

#endif /* _ATT_PARAMS_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
