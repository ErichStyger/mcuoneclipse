/*! *********************************************************************************
* \addtogroup HID Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file hid_interface.h
 * This file is the interface file for the HID Profile
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

#ifndef _HID_INTERFACE_H_
#define _HID_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
#define gGattService_HumanInterfaceDevice_c 0x1812
/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! HID Service - Control Point Values*/
typedef uint8_t hidControlPointValues_t;
typedef enum
{
    gHid_Suspend_c,
    gHid_ExitSuspend_c
}hidControlPointValues_tag;

/*! HID Service - Protocol Mode Values*/
typedef uint8_t hidProtocolMode_t;
typedef enum
{
    gHid_BootProtocolMode_c,
    gHid_ReportProtocolMode_c
}hidProtocolModeValues_tag;

/*! HID Service - Report Type */
typedef uint8_t hidReportType_t;
typedef enum
{
    gHid_InputReport_c = 0x01,
    gHid_OutputReport_c = 0x02,
    gHid_FeatureReport_c = 0x03,
}hidReportType_tag;

/*! HID Service - HID Info Flags */
typedef uint8_t hidInfoFlags_t;
typedef enum
{
    gHid_InfoFlagsNone_C        = 0x00,
    gHid_RemoteWake_c           = BIT0,
    gHid_NormallyConnectable_c  = BIT1
}hidInfoFlags_tag;

/*! HID Service - HID Information */
typedef struct hidInfo_tag
{
    uint16_t        bcdHID;
    uint8_t         bCountryCode;
    hidInfoFlags_t  flags;
} hidInfo_t;

/*! HID Service - Configuration */
typedef struct hidConfig_tag
{
    uint16_t            serviceHandle;
    hidProtocolMode_t   protocolMode;
    hidInfo_t           hidInfo;
    uint8_t             *pReportMap;
} hidConfig_t;


/*! HID Client - Configuration */
typedef struct hidcConfig_tag
{
    uint16_t    hService;
    uint16_t    hHidReport;
    uint16_t    hHidReportCccd; 
} hidcConfig_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
* \brief        Starts HID Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_Start(hidConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops HID Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_Stop(hidConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the HID service
*
* \param[in]    clientDeviceId  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_Subscribe(deviceId_t clientDeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the HID service
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_Unsubscribe();

/*!**********************************************************************************
* \brief        Sets the Protocol Mode value on a specified service.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]   protocolMode    Protocol Mode value.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_SetProtocolMode(uint16_t serviceHandle, hidProtocolMode_t protocolMode);

/*!**********************************************************************************
* \brief        Gets the Protocol Mode value on a specified service.
*
* \param[in]    serviceHandle       Service handle.
* \param[out]   pOutProtocolMode    Pointer to store the Protocol Mode value.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_GetProtocolMode(uint16_t serviceHandle, hidProtocolMode_t *pOutProtocolMode);

/*!**********************************************************************************
* \brief        Sends an HID input report on a specified service.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    reportlen       Length of report.
* \param[in]    pInReport       Pointer to report value.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_SendInputReport(uint16_t serviceHandle, uint16_t reportlen, void* pInReport);

/*!**********************************************************************************
* \brief        Sends an HID boot mouse input report on a specified service.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    reportlen       Length of report.
* \param[in]    pInReport       Pointer to report value.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hid_SendBootMouseInputReport(uint16_t serviceHandle, uint16_t reportlen, void* pInReport);
/*!**********************************************************************************
* \brief        Handles command on the HID Control Point
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    value           Command Value.
*
* \return       gAttErrCodeNoError_c or error.
*************************************************************************************/
uint8_t Hid_ControlPointHandler (uint16_t serviceHandle, hidControlPointValues_t value);

#ifdef __cplusplus
}
#endif 

#endif /* _HID_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
