/*! *********************************************************************************
 * \addtogroup GATT_DB
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file gatt_db_app_interface.h
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

#ifndef _GATT_DB_APP_INTERFACE_H_
#define _GATT_DB_APP_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief    Initializes the GATT database at runtime.
*
* \remarks  This function should be called only once at device start-up. In the current
* stack implementation, it is called internally by Ble_HostInitialize.
*
* \remarks This function executes synchronously.
*
* \return   gBleSuccess_c or error.
*
********************************************************************************** */
bleResult_t GattDb_Init();

/*!
 * \brief Writes an attribute from the application level.
 *
 * This function can be called by the application code to modify an attribute in the database.
 * It should only be used by the application to modify a Characteristic's value
 * based on the application logic (e.g., external sensor readings).
 *
 * \param[in] handle             The handle of the attribute to be written.
 * \param[in] valueLength        The number of bytes to be written.
 * \param[in] aValue             The source buffer containing the value to be written.
 *
 * \return                       gBleSuccess_c or error.
 *
 * \remarks This function executes synchronously.
 */
bleResult_t GattDb_WriteAttribute
(
    uint16_t    handle,
    uint16_t    valueLength,
    uint8_t*    aValue
);

/*!
 * \brief Reads an attribute from the application level.
 *
 * This function can be called by the application code to read an attribute in the database.
 *
 * \param[in]  handle           The handle of the attribute to be read.
 * \param[in]  maxBytes         The maximum number of bytes to be received.
 * \param[out] aOutValue        The pre-allocated buffer ready to receive the bytes.
 * \param[out] pOutValueLength  The actual number of bytes received.
 *
 * \return                  gBleSuccess_c or error.
 *
 * \remarks This function executes synchronously.
 */
bleResult_t GattDb_ReadAttribute
(
    uint16_t    handle,
    uint16_t    maxBytes,
    uint8_t*    aOutValue,
    uint16_t*   pOutValueLength
);

/*!
 * \brief Finds the handle of a Service Declaration with a given UUID inside the database.
 *
 * \param[in]  startHandle              The handle to start the search. Should be 0x0001 on the first call.
 * \param[in]  serviceUuidType          Service UUID type.
 * \param[in]  pServiceUuid             Service UUID.
 * \param[out] pOutServiceHandle        Pointer to the service declaration handle to be written.
 *
 * \return                          gBleSuccess_c or error.
 *
 * \retval  gBleSuccess_c                       Service Declaration found, handle written in pOutCharValueHandle.
 * \retval  gGattDbInvalidHandle_c              Invalid Start Handle.
 * \retval  gGattDbServiceNotFound_c            Service with given UUID not found.
 *
 * \remarks This function executes synchronously.
 * \remarks The startHandle should be set to 0x0001 when this function is called for the first time.
 * If multiple Services with the same UUID are expected, then after the first successful call the function
 * may be called again with the startHandle equal to the found service handle plus one.
 */
bleResult_t GattDb_FindServiceHandle
(
    uint16_t        startHandle,
    bleUuidType_t   serviceUuidType,
    bleUuid_t*      pServiceUuid,
    uint16_t*       pOutServiceHandle
);

/*!
 * \brief Finds the handle of a Characteristic Value with a given UUID inside a Service.
 *
 * The Service is input by its declaration handle.
 *
 * \param[in]  serviceHandle            The handle of the Service declaration.
 * \param[in]  characteristicUuidType   Characteristic UUID type.
 * \param[in]  pCharacteristicUuid      Characteristic UUID.
 * \param[out] pOutCharValueHandle      Pointer to the characteristic value handle to be written.
 *
 * \return                          gBleSuccess_c or error.
 *
 * \retval  gBleSuccess_c                    Characteristic Value found, handle written in pOutCharValueHandle.
 * \retval  gGattDbInvalidHandle_c           Handle not found or not a Service declaration.
 * \retval  gGattDbCharacteristicNotFound_c  Characteristic Value with given UUID not found.
 *
 * \remarks This function executes synchronously.
 */
bleResult_t GattDb_FindCharValueHandleInService
(
    uint16_t        serviceHandle,
    bleUuidType_t   characteristicUuidType,
    bleUuid_t*      pCharacteristicUuid,
    uint16_t*       pOutCharValueHandle
);

/*!
 * \brief Finds the handle of a Characteristic's CCCD given the Characteristic's Value handle.
 *
 * \param[in]  charValueHandle      The handle of the Service declaration.
 * \param[out] pOutCccdHandle       Pointer to the CCCD handle to be written.
 *
 * \return                          gBleSuccess_c or error.
 *
 * \retval  gBleSuccess_c              CCCD found, handle written in pOutCccdHandle.
 * \retval  gGattDbInvalidHandle_c     Invalid Characteristic Value handle.
 * \retval  gGattDbCccdNotFound_c      CCCD not found for this Characteristic.
 *
 * \remarks This function executes synchronously.
 */
bleResult_t GattDb_FindCccdHandleForCharValueHandle
(
    uint16_t        charValueHandle,
    uint16_t*       pOutCccdHandle
);

/*!
 * \brief Finds the handle of a Characteristic Descriptor given the Characteristic's Value handle and Descriptor's UUID.
 *
 * \param[in]  charValueHandle          The handle of the Service declaration.
 * \param[in]  descriptorUuidType       Descriptor's UUID type.
 * \param[in]  pDescriptorUuid          Descriptor's UUID.
 * \param[out] pOutDescriptorHandle     Pointer to the Descriptor handle to be written.
 *
 * \return                          gBleSuccess_c or error.
 *
 * \retval  gBleSuccess_c                    Descriptor found, handle written in pOutDescriptorHandle.
 * \retval  gGattDbInvalidHandle_c           Invalid Characteristic Value handle.
 * \retval  gGattDbDescriptorNotFound_c      Descriptor not found for this Characteristic.
 *
 * \remarks This function executes synchronously.
 */
bleResult_t GattDb_FindDescriptorHandleForCharValueHandle
(
    uint16_t        charValueHandle,
    bleUuidType_t   descriptorUuidType,
    bleUuid_t*      pDescriptorUuid,
    uint16_t*       pOutDescriptorHandle
);

#ifdef __cplusplus
}
#endif 

#endif /* _GATT_DB_APP_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
