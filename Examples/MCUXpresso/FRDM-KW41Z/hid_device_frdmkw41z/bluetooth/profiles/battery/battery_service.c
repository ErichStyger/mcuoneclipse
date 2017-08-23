/*! *********************************************************************************
* \addtogroup Battery Service
* @{
********************************************************************************** */
/*!
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file battery_service.c
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "battery_interface.h"

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Battery Service - Subscribed Client*/
deviceId_t mBas_SubscribedClientId;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

static void Bas_SendNotifications(uint16_t handle);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

bleResult_t Bas_Start (basConfig_t *pServiceConfig)
{
    /* Record initial battery level measurement */
    Bas_RecordBatteryMeasurement(pServiceConfig->serviceHandle, pServiceConfig->batteryLevel);

    return gBleSuccess_c;
}

bleResult_t Bas_Stop (basConfig_t *pServiceConfig)
{
    mBas_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Bas_Subscribe(deviceId_t clientDeviceId)
{
    mBas_SubscribedClientId = clientDeviceId;
    return gBleSuccess_c;
}

bleResult_t Bas_Unsubscribe()
{
    mBas_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Bas_RecordBatteryMeasurement (uint16_t serviceHandle, uint8_t batteryLevel)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_BatteryLevel_d);

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(serviceHandle,
        gBleUuidType16_c, &uuid, &handle);

    if (result != gBleSuccess_c)
        return result;

    /* Update characteristic value and send notification */
    result = GattDb_WriteAttribute(handle, sizeof(uint8_t), &batteryLevel);

    if (result != gBleSuccess_c)
        return result;

    Bas_SendNotifications(handle);

    return gBleSuccess_c;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static void Bas_SendNotifications
(
  uint16_t handle
)
{
    uint16_t  handleCccd;
    bool_t isNotifActive;
   
    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(handle, &handleCccd) != gBleSuccess_c)
        return;

    if (gBleSuccess_c == Gap_CheckNotificationStatus
        (mBas_SubscribedClientId, handleCccd, &isNotifActive) &&
        TRUE == isNotifActive)
    {
        GattServer_SendNotification(mBas_SubscribedClientId, handle);
    }
}
/*! *********************************************************************************
* @}
********************************************************************************** */
