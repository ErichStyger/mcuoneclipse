/*! *********************************************************************************
* \addtogroup HID Service
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file hid_service.c
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
#include "hid_interface.h"
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
/*! HID Service - Subscribed Client*/
static deviceId_t mHid_SubscribedClientId;
/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

static void Hid_SendReportNotifications(uint16_t handle);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
bleResult_t Hid_Start(hidConfig_t *pServiceConfig)
{
	mHid_SubscribedClientId = gInvalidDeviceId_c;
    Hid_SetProtocolMode(pServiceConfig->serviceHandle, pServiceConfig->protocolMode);

    return gBleSuccess_c;
}

bleResult_t Hid_Stop(hidConfig_t *pServiceConfig)
{
    return Hid_Unsubscribe();
}

bleResult_t Hid_Subscribe(deviceId_t clientdeviceId)
{
    if (mHid_SubscribedClientId == gInvalidDeviceId_c)
        mHid_SubscribedClientId = clientdeviceId;

    return gBleSuccess_c;
}

bleResult_t Hid_Unsubscribe()
{
    mHid_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Hid_SetProtocolMode(uint16_t serviceHandle, hidProtocolMode_t protocolMode)
{
    uint16_t  hProtocolMode;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_ProtocolMode_d);

    /* Get characteristic handle */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType16_c, &uuid, &hProtocolMode);

    if (result != gBleSuccess_c)
        return result;

    /* Write attribute value*/
    return GattDb_WriteAttribute(hProtocolMode, sizeof(hidProtocolMode_t), &protocolMode);
}

bleResult_t Hid_GetProtocolMode(uint16_t serviceHandle, hidProtocolMode_t *pOutProtocolMode)
{
    uint16_t  hProtocolMode;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_ProtocolMode_d);
    uint16_t outLen;

    /* Get characteristic handle */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType16_c, &uuid, &hProtocolMode);

    if (result != gBleSuccess_c)
        return result;

    /* Read attribute value*/
    return GattDb_ReadAttribute(hProtocolMode, sizeof(hidProtocolMode_t), pOutProtocolMode, &outLen);
}

bleResult_t Hid_SendInputReport(uint16_t serviceHandle, uint16_t reportlen, void* pInReport)
{
    uint16_t  hReport;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_Report_d);

    /* Get characteristic handle */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType16_c, &uuid, &hReport);

    if (result != gBleSuccess_c)
        return result;

    /* Update characteristic value and send notification */
    result = GattDb_WriteAttribute(hReport, reportlen, pInReport);

    if (result != gBleSuccess_c)
        return result;

    Hid_SendReportNotifications(hReport);

    return gBleSuccess_c;
}

bleResult_t Hid_SendBootMouseInputReport(uint16_t serviceHandle, uint16_t reportlen, void* pInReport)
{
    uint16_t  hReport;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_BootMouseInputReport_d);

    /* Get characteristic handle */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType16_c, &uuid, &hReport);

    if (result != gBleSuccess_c)
        return result;

    /* Update characteristic value and send notification */
    result = GattDb_WriteAttribute(hReport, reportlen, pInReport);

    if (result != gBleSuccess_c)
        return result;

    Hid_SendReportNotifications(hReport);

    return gBleSuccess_c;
}


uint8_t Hid_ControlPointHandler (uint16_t serviceHandle, hidControlPointValues_t value)
{
    uint8_t retStatus = gAttErrCodeNoError_c;

    switch (value)
    {
    case gHid_Suspend_c:
        break;
    case gHid_ExitSuspend_c:
        break;
    default:
        retStatus = gAttErrCodeRequestNotSupported_c;
        break;
    }
    return retStatus;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static void Hid_SendReportNotifications
(
 uint16_t handle
)
{
    uint16_t  hCccd;
    bool_t isNotifActive;

    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(handle, &hCccd) != gBleSuccess_c)
        return;

    if (gBleSuccess_c == Gap_CheckNotificationStatus
        (mHid_SubscribedClientId, hCccd, &isNotifActive) &&
        TRUE == isNotifActive)
    {
        GattServer_SendNotification(mHid_SubscribedClientId, handle);
    }
}
/*! *********************************************************************************
* @}
********************************************************************************** */
