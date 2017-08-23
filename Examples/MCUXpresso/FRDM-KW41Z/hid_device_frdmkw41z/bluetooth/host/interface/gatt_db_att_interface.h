/*! *********************************************************************************
 * \addtogroup GATT_DB
 * @{
 ********************************************************************************** */

/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file gatt_db_att_interface.h
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

#ifndef _GATT_DB_ATT_INTERFACE_H_
#define _GATT_DB_ATT_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "att_types.h"
#include "att_params.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Find Information Request handler
 *
 * This function handles an ATT Find Information Request and writes the result
 * in a Find Information Response parameter structure.
 *
 * \param[in] deviceId                  The device ID of the requesting ATT Client.
 * \param[in] pReqParams                The request parameters.
 * \param[out] pOutRspParams            The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle  The attribute handle where an error occured.
 * \return                              Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttFindInformation
(
    deviceId_t                          deviceId,
    attFindInformationRequestParams_t*  pReqParams,
    attFindInformationResponseParams_t* pOutRspParams,
    uint16_t*                           outErrorAttributeHandle
);

/*!
 * \brief Find By Type Value Request handler
 *
 * This function handles an ATT Find By Type Value Request and writes the result
 * in a Find By Type Value Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttFindByTypeValue
(
    deviceId_t                          deviceId,
    attFindByTypeValueRequestParams_t*  pReqParams,
    attFindByTypeValueResponseParams_t* pOutRspParams,
    uint16_t*                           outErrorAttributeHandle
);

/*!
 * \brief Read By Type Request handler
 *
 * This function handles an ATT Read By Type Request and writes the result
 * in a Read By Type Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttReadByType
(
    deviceId_t                     deviceId,
    attReadByTypeRequestParams_t*  pReqParams,
    attReadByTypeResponseParams_t* pOutRspParams,
    uint16_t*                      outErrorAttributeHandle
);

/*!
 * \brief Read Request handler
 *
 * This function handles an ATT Read Request and writes the result
 * in a Read Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttRead
(
    deviceId_t               deviceId,
    attReadRequestParams_t*  pReqParams,
    attReadResponseParams_t* pOutRspParams,
    uint16_t*                outErrorAttributeHandle
);

/*!
 * \brief Read Blob Request handler
 *
 * This function handles an ATT Read Blob Request and writes the result
 * in a Read Blob Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttReadBlob
(
    deviceId_t                   deviceId,
    attReadBlobRequestParams_t*  pReqParams,
    attReadBlobResponseParams_t* pOutRspParams,
    uint16_t*                    outErrorAttributeHandle
);

/*!
 * \brief Read Multiple Request handler
 *
 * This function handles an ATT Read Multiple Request and writes the result
 * in a Read Multiple Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttReadMultiple
(
    deviceId_t                       deviceId,
    attReadMultipleRequestParams_t*  pReqParams,
    attReadMultipleResponseParams_t* pOutRspParams,
    uint16_t*                        outErrorAttributeHandle
);

/*!
 * \brief Read By Group Type Request handler
 *
 * This function handles an ATT Read By Group Type Request and writes the result
 * in a Read By Group Type Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttReadByGroupType
(
    deviceId_t                          deviceId,
    attReadByGroupTypeRequestParams_t*  pReqParams,
    attReadByGroupTypeResponseParams_t* pOutRspParams,
    uint16_t*                           outErrorAttributeHandle
);

/*!
 * \brief Write Request handler
 *
 * This function handles an ATT Write Request and writes the result
 * in a Write Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttWrite
(
    deviceId_t                          deviceId,
    attWriteRequestAndCommandParams_t*  pReqParams,
    uint16_t*                           outErrorAttributeHandle
);

/*!
 * \brief Write Command handler
 *
 * This function handles an ATT Write Command.
 *
 * \param[in] deviceId       The device ID of the requesting ATT Client.
 * \param[in] pReqParams     The command parameters.
 * \return                   TRUE if value has been written, FALSE otherwise
  */
void GattDb_AttWriteCommand
(
    deviceId_t                          deviceId,
    attWriteRequestAndCommandParams_t*  pReqParams
);

/*!
 * \brief Signed Write Command handler
 *
 * This function handles an ATT Signed Write Command.
 *
 * \param[in] deviceId       The device ID of the requesting ATT Client.
 * \param[in] pReqParams     The command parameters.
 */
void GattDb_AttSignedWriteCommand
(
    deviceId_t                      deviceId,
    attSignedWriteCommandParams_t*  pReqParams
);

/*!
 * \brief Prepare Write Request handler
 *
 * This function handles an ATT Prepare Write Request and writes the result
 * in a Prepare Write Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] pOutRspParams             The pre-allocated response parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttPrepareWrite
(
    deviceId_t                              deviceId,
    attPrepareWriteRequestResponseParams_t* pReqParams,
    attPrepareWriteRequestResponseParams_t* pOutRspParams,
    uint16_t*                               outErrorAttributeHandle
);

/*!
 * \brief Execute Write Request handler
 *
 * This function handles an ATT Execute Write Request and writes the result
 * in an Execute Write Response parameter structure.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttExecuteWrite
(
    deviceId_t                      deviceId,
    attExecuteWriteRequestParams_t* pReqParams,
    uint16_t*                       outErrorAttributeHandle
);

/*!
 * \brief Executes an operation from a Prepare Write Queue.
 *
 * This function is used by the AttPrepareWriteQueue module to execute a single
 * operation from a Prepare Write Queue.
 *
 * \param[in] deviceId                   The device ID of the requesting ATT Client.
 * \param[in] pReqParams                 The request parameters.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttExecuteWriteFromQueue
(
    deviceId_t                              deviceId,
    attPrepareWriteRequestResponseParams_t* pReqParams,
    uint16_t*                               outErrorAttributeHandle
);

/*!
 * \brief Notification/Indication preparing function
 *
 * This function prepares a parameter structure for sending a Notification or an Indication.
 *
 * \param[in] deviceId                   The device ID of the target Client.
 * \param[inout] pIoParams               The pre-allocated parameter to be filled.
 * \param[out] outErrorAttributeHandle   The attribute handle where an error occured.
 * \return                               Success or error code (bleResult_t)
 */
attErrorCode_t GattDb_AttPrepareNotificationIndication
(
    deviceId_t                                      deviceId,
    attHandleValueNotificationIndicationParams_t*   pIoParams,
    uint16_t*                                       outErrorAttributeHandle
);

#ifdef __cplusplus
}
#endif 

#endif /* _GATT_DB_ATT_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
