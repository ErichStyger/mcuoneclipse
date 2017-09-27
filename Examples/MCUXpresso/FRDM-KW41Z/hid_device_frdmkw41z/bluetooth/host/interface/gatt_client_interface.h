/*! *********************************************************************************
 * \defgroup GATT_CLIENT GATT - Client APIs
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file gatt_client_interface.h
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

#ifndef _GATT_CLIENT_INTERFACE_H_
#define _GATT_CLIENT_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "gatt_interface.h"

/************************************************************************************
*************************************************************************************
* Macros
*************************************************************************************
************************************************************************************/
/*! *********************************************************************************
* \brief  Executes the basic Characteristic Write operation (with server confirmation).
*
* \param[in] deviceId       Device ID of the connected GATT Server.
* \param[in] pChar          Pointer to the Characteristic being written.
* \param[in] valueLength    Size in bytes of the value to be written.
* \param[in] aValue         Array of bytes to be written.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
#define GattClient_SimpleCharacteristicWrite(deviceId, pChar, valueLength, aValue) \
    GattClient_WriteCharacteristicValue\
        (deviceId, pChar, valueLength, aValue, FALSE, FALSE, FALSE, NULL)

/*! *********************************************************************************
* \brief  Executes the Characteristic Write Without Response operation.
*
* \param[in] deviceId       Device ID of the connected GATT Server.
* \param[in] pChar          Pointer to the Characteristic being written.
* \param[in] valueLength    Size in bytes of the value to be written.
* \param[in] aValue         Array of bytes to be written.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
#define GattClient_CharacteristicWriteWithoutResponse(deviceId, pChar, valueLength, aValue) \
    GattClient_WriteCharacteristicValue\
        (deviceId, pChar, valueLength, aValue, TRUE, FALSE, FALSE, NULL)

/*! *********************************************************************************
* \brief  Executes the Characteristic Signed Write Without Response operation.
*
* \param[in] deviceId       Device ID of the connected GATT Server.
* \param[in] pChar          Pointer to the Characteristic being written.
* \param[in] valueLength    Size in bytes of the value to be written.
* \param[in] aValue         Array of bytes to be written.
* \param[in] aCsrk          CSRK to be used for data signing.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
#define GattClient_CharacteristicSignedWrite(deviceId, pChar, valueLength, aValue, aCsrk) \
    GattClient_WriteCharacteristicValue\
        (deviceId, pChar, valueLength, aValue, TRUE, TRUE, FALSE, aCsrk)

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
/*! GATT Client Procedure type */
typedef enum {
    gGattProcExchangeMtu_c,                             /*!< MTU Exchange */
    gGattProcDiscoverAllPrimaryServices_c,              /*!< Primary Service Discovery */
    gGattProcDiscoverPrimaryServicesByUuid_c,           /*!< Discovery of Services by UUID */
    gGattProcFindIncludedServices_c,                    /*!< Discovery of Included Services within a Service range */
    gGattProcDiscoverAllCharacteristics_c,              /*!< Characteristic Discovery within Service range */
    gGattProcDiscoverCharacteristicByUuid_c,            /*!< Characteristic Discovery by UUID */
    gGattProcDiscoverAllCharacteristicDescriptors_c,    /*!< Characteristic Descriptor Discovery */
    gGattProcReadCharacteristicValue_c,                 /*!< Characteristic Reading using Value handle */
    gGattProcReadUsingCharacteristicUuid_c,             /*!< Characteristic Reading by UUID */
    gGattProcReadMultipleCharacteristicValues_c,        /*!< Reading multiple Characteristics at once */
    gGattProcWriteCharacteristicValue_c,                /*!< Characteristic Writing */
    gGattProcReadCharacteristicDescriptor_c,            /*!< Reading Characteristic Descriptors */
    gGattProcWriteCharacteristicDescriptor_c,           /*!< Writing Characteristic Descriptors */
} gattProcedureType_t;

/*! GATT Client Procedure Result type */
typedef enum gattProcedureResult_tag {
    gGattProcSuccess_c,     /*!< The procedure was completed successfully. */
    gGattProcError_c        /*!< The procedure was terminated due to an error. */
} gattProcedureResult_t;

/*! GATT Client Procedure Callback type */
typedef void (*gattClientProcedureCallback_t)
(
    deviceId_t              deviceId,           /*!< Device ID identifying the active connection. */
    gattProcedureType_t     procedureType,      /*!< The type of the procedure that was completed. */
    gattProcedureResult_t   procedureResult,    /*!< The result of the completed procedure. */
    bleResult_t             error               /*!< If procedureResult is not gGattProcSuccess_c, this contains the error that terminated the procedure. */
); 

/*! GATT Client Notification Callback prototype */
typedef void (*gattClientNotificationCallback_t)
(
    deviceId_t  deviceId,                   /*!< Device ID identifying the active connection. */
    uint16_t    characteristicValueHandle,  /*!< Handle of the Characteristic Value attribute to be notified. */
    uint8_t*    aValue,                     /*!< The Characteristic value array. */
    uint16_t    valueLength                 /*!< Value array size. */
);

/*! GATT Client Indication Callback prototype */
typedef gattClientNotificationCallback_t gattClientIndicationCallback_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*
 *
 * Local Client Configuration
 *
 */

/*! *********************************************************************************
* \brief  Initializes the GATT Client functionality.
*
* \remarks This should be called once at device startup, if necessary.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattClient_Init(void);

/*! *********************************************************************************
* \brief  Resets any ongoing GATT Client Procedure.
*
* \remarks This function should be called if an ongoing Client procedure
* needs to be stopped.
*
********************************************************************************** */
bleResult_t GattClient_ResetProcedure(void);

/*! *********************************************************************************
* \brief  Installs the application callback for the GATT Client module Procedures.
*
* \param[in] callback   Application defined callback to be triggered by this module.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattClient_RegisterProcedureCallback
(
    gattClientProcedureCallback_t callback
);

/*! *********************************************************************************
* \brief  Installs the application callback for Server Notifications.
*
* \param[in] callback   Application defined callback to be triggered by this module.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattClient_RegisterNotificationCallback
(
    gattClientNotificationCallback_t callback
);

/*! *********************************************************************************
* \brief  Installs the application callback for Server Indications.
*
* \param[in] callback   Application defined callback to be triggered by this module.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattClient_RegisterIndicationCallback
(
    gattClientIndicationCallback_t callback
);


/* 
 * 
 * GATT Client Procedures 
 *
 */

/*! *********************************************************************************
* \brief  Initializes the MTU Exchange procedure.
*
* \param[in] deviceId       Device ID of the connected peer.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_ExchangeMtu
(
    deviceId_t      deviceId
);

/*! *********************************************************************************
* \brief  Initializes the Primary Service Discovery procedure.
*
* \param[in]  deviceId              Device ID of the connected peer.
* \param[out] aOutPrimaryServices   Statically allocated array of gattService_t. The GATT 
*                                   module fills each Service's handle range and UUID.
* \param[in]  maxServiceCount       Maximum number of services to be filled.
* \param[out] pOutDiscoveredCount   The actual number of services discovered.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_DiscoverAllPrimaryServices
(
    deviceId_t      deviceId,
    gattService_t*  aOutPrimaryServices, 
    uint8_t         maxServiceCount,
    uint8_t*        pOutDiscoveredCount
);

/*! *********************************************************************************
* \brief  Initializes the Primary Service Discovery By UUID procedure.
*
* \param[in]  deviceId              Device ID of the connected peer.
* \param[in]  uuidType              Service UUID type.
* \param[in]  pUuid                 Service UUID.
* \param[out] aOutPrimaryServices   Statically allocated array of gattService_t. The GATT
*                                   module fills each Service's handle range.
* \param[in]  maxServiceCount       Maximum number of services to be filled.
* \param[out] pOutDiscoveredCount   The actual number of services discovered.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_DiscoverPrimaryServicesByUuid
(
    deviceId_t      deviceId,
    bleUuidType_t   uuidType,
    bleUuid_t*      pUuid,
    gattService_t*  aOutPrimaryServices, 
    uint8_t         maxServiceCount,
    uint8_t*        pOutDiscoveredCount
);

/*! *********************************************************************************
* \brief  Initializes the Find Included Services procedure.
*
* \param[in]  deviceId              Device ID of the connected peer.
* \param[inout]  pIoService         The service within which inclusions should be searched.
*                                   The GATT module uses the Service's handle range and fills
*                                   the included Services' handle ranges, UUID types and
*                                   the UUIDs if they are 16-bit UUIDs.
* \param[in]  maxServiceCount       Maximum number of included services to be filled.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_FindIncludedServices
(
    deviceId_t      deviceId,
    gattService_t*  pIoService,
    uint8_t         maxServiceCount
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Discovery procedure for a given Service.
*
* \param[in]    deviceId                  Device ID of the connected peer.
* \param[inout] pIoService                The service within which characteristics should be searched.
*                                         The GATT module uses the Characteristic's range.
* \param[in]    maxCharacteristicCount    Maximum number of characteristics to be filled.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_DiscoverAllCharacteristicsOfService
(
    deviceId_t      deviceId,
    gattService_t*  pIoService,
    uint8_t         maxCharacteristicCount
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Discovery procedure for a given Service, with a given UUID.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[in]  uuidType                  Characteristic UUID type.
* \param[in]  pUuid                     Characteristic UUID.
* \param[in]  pService                  The service within which characteristics should be searched.
* \param[out] aOutCharacteristics       The allocated array of Characteristics to be filled.
* \param[in]  maxCharacteristicCount    Maximum number of characteristics to be filled.
* \param[out] pOutDiscoveredCount       The actual number of characteristics discovered.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_DiscoverCharacteristicOfServiceByUuid
(
    deviceId_t              deviceId,
    bleUuidType_t           uuidType, 
    bleUuid_t*              pUuid,
    gattService_t*          pService,
    gattCharacteristic_t*   aOutCharacteristics, 
    uint8_t                 maxCharacteristicCount,
    uint8_t*                pOutDiscoveredCount
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Descriptor Discovery procedure for a given Characteristic.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[inout]  pIoCharacteristic      The characteristic within which descriptors should be searched.
*                                       The GATT module uses the Characteristic's handle and fills each
*                                       descriptor's handle and UUID.
* \param[in]  endingHandle              The last handle of the Characteristic.
* \param[in]  maxDescriptorCount        Maximum number of descriptors to be filled.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback. The endingHandle parameter should be known by the
* application if Characteristic Discovery was performed, i.e., if the next Characteristic
* declaration handle is known, then subtract 1 to obtain the endingHandle for the current Characteristic.
* If the last handle of the Characteristic is still unknown, set the endingHandle parameter to 0xFFFF.
*
********************************************************************************** */
bleResult_t GattClient_DiscoverAllCharacteristicDescriptors
(
    deviceId_t              deviceId,
    gattCharacteristic_t*   pIoCharacteristic,
    uint16_t                endingHandle,
    uint8_t                 maxDescriptorCount
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Read procedure for a given Characteristic.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[inout]  pIoCharacteristic      The characteristic whose value must be read.
*                                       The GATT module uses the value handle and
*                                       fills the value and length.
* \param[in]  maxReadBytes              Maximum number of bytes to be read.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_ReadCharacteristicValue
(
    deviceId_t              deviceId,
    gattCharacteristic_t*   pIoCharacteristic,
    uint16_t                maxReadBytes
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Read By UUID procedure.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[in]  uuidType                  Characteristic UUID type.
* \param[in]  pUuid                     Characteristic UUID.
* \param[in]  pHandleRange              Handle range for the search or NULL. If
*                                       this is NULL, the search range is 0x0001-0xffff.
* \param[out] aOutBuffer                The allocated buffer to read into.
* \param[in]  maxReadBytes              Maximum number of bytes to be read.
* \param[out] pOutActualReadBytes       The actual number of bytes read.
*
* \return  gBleSuccess_c or error.
*
* \remarks This procedure returns the Characteristics found within the specified range
* with the specified UUID. aOutBuffer will contain the Handle-Value pair length (1 byte),
* then Handle-Value pairs for all Characteristic Values found with the specified UUID.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_ReadUsingCharacteristicUuid
(
    deviceId_t          deviceId,
    bleUuidType_t       uuidType,
    bleUuid_t*          pUuid,
    gattHandleRange_t*  pHandleRange,
    uint8_t*            aOutBuffer,
    uint16_t            maxReadBytes,
    uint16_t*           pOutActualReadBytes
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Read Multiple procedure.
*
* \param[in]    deviceId                  Device ID of the connected peer.
* \param[inout] aIoCharacteristics        Array of the characteristics whose values are to be read.
*                                         The GATT module uses each Characteristic's value handle and maxValueLength
*                                         fills each value and length.
* \param[in]    cNumCharacteristics       Number of characteristics in the array.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_ReadMultipleCharacteristicValues
(
    deviceId_t              deviceId,
    uint8_t                 cNumCharacteristics,
    gattCharacteristic_t*   aIoCharacteristics
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Write procedure for a given Characteristic.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[in]  pCharacteristic           The characteristic whose value must be written.
*                                       The GATT module uses the value handle.
* \param[in]  valueLength               Number of bytes to be written.
* \param[in]  aValue                    Array of bytes to be written.
* \param[in]  withoutResponse           Indicates if a Write Command is used.
* \param[in]  signedWrite               Indicates if a Signed Write is performed.
* \param[in]  doReliableLongCharWrites  Indicates Reliable Long Writes.
* \param[in]  aCsrk                     The CSRK (gcCsrkSize_d bytes) if signedWrite is TRUE, ignored otherwise.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_WriteCharacteristicValue
(
    deviceId_t              deviceId,
    gattCharacteristic_t*   pCharacteristic,
    uint16_t                valueLength,
    uint8_t*                aValue,
    bool_t                  withoutResponse,
    bool_t                  signedWrite,
    bool_t                  doReliableLongCharWrites,
    uint8_t*                aCsrk
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Descriptor Read procedure for a given Characteristic Descriptor.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[inout]  pIoDescriptor          The characteristic descriptor whose value must be read.
*                                       The GATT module uses the attribute's handle and fills
*                                       the attribute's value and length.
* \param[in]  maxReadBytes              Maximum number of bytes to be read.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_ReadCharacteristicDescriptor
(
    deviceId_t          deviceId,
    gattAttribute_t*    pIoDescriptor,
    uint16_t            maxReadBytes
);

/*! *********************************************************************************
* \brief  Initializes the Characteristic Descriptor Write procedure for a given Characteristic Descriptor.
*
* \param[in]  deviceId                  Device ID of the connected peer.
* \param[in]  pDescriptor               The characteristic descriptor whose value must be written.
*                                       The GATT module uses the attribute's handle.
* \param[in]  valueLength               Number of bytes to be written.
* \param[in]  aValue                    Array of bytes to be written.
*
* \return  gBleSuccess_c or error.
*
* \remarks If gBleSuccess_c is returned, the completion of this procedure is signalled
* by the Client Procedure callback.
*
********************************************************************************** */
bleResult_t GattClient_WriteCharacteristicDescriptor
(
    deviceId_t          deviceId,
    gattAttribute_t*    pDescriptor,
    uint16_t            valueLength,
    uint8_t*            aValue
);

#ifdef __cplusplus
}
#endif 

#endif /* _GATT_CLIENT_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
