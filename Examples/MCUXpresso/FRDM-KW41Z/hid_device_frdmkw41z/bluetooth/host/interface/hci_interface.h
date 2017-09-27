/*! *********************************************************************************
* \defgroup HCI HCI
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file
*
* This file is the interface file for the HCI module
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

#ifndef _HCI_INTERFACE_H_
#define _HCI_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "hci_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*******************************************************************************
*   COMMANDS and EVENTS parameters
***************************************************************************** */
/*! HCI Commands and Events for ************************************************
*   OGF : 0x01 : Link Control Commands 
***************************************************************************** */

/*! OCF 0x0006 */
/*! HCI_Disconnect */
typedef struct hciDisconnectCommand_tag
{
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciDisconnectCommand_t;
/*! Disconnection Complete Event : 0x05 */
typedef struct hciDisconnectionCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciDisconnectionCompleteEvent_t;

/*! OCF 0x001D */
/*! HCI_Read_Remote_Version_Information */
typedef struct hciReadRemoteVersionInformationCommand_tag
{
    uint16_t            connectionHandle;
} hciReadRemoteVersionInformationCommand_t;
/*! Read Remote Version Information Complete Event : 0x0C */
typedef struct hciReadRemoteVersionInformationCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             version;
    uint16_t            manufacturerName;
    uint16_t            subversion;
} hciReadRemoteVersionInformationCompleteEvent_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x03 : Controller & Baseband Commands 
***************************************************************************** */
/*! OCF 0x0001 */
/*! HCI_Set_Event_Mask - Command Complete Parameters */
typedef struct hciSetEventMaskCommandComplete_tag
{
    hciErrorCode_t      status;
} hciSetEventMaskCommandComplete_t;

/*! Command Status Event : 0x0F */
typedef struct hciCommandStatusEvent_tag
{
    hciErrorCode_t          status;
    uint8_t                 numHciCommandPackets;
    hciCommandOpCode_t      commandOpCode;
} hciCommandStatusEvent_t;

/*! Hardware Error Event : 0x10 */
typedef struct hciHardwareErrorEvent_tag
{
    bleHardwareErrorCode_t      status;
} hciHardwareErrorEvent_t;

/*! Number Of Completed Packets Event : 0x13 */
typedef struct hciNumberOfCompletedPacketsEventParams_tag
{
    uint16_t                connectionHandle;
    uint16_t                hcNumOfCompletedPackets;
} hciNumberOfCompletedPacketsEventParams_t;
typedef struct hciNumberOfCompletedPacketsEvent_tag
{
    uint8_t                 numberOfHandles;
    uint16_t                connectionHandle[gcGapMaximumActiveConnections_c];
    uint16_t                hcNumCompletedPackets[gcGapMaximumActiveConnections_c];
} hciNumberOfCompletedPacketsEvent_t;

/*! Data Buffer Overflow Event : 0x1A */
typedef struct hciDataBufferOverflowEvent_tag
{
    hciDataBufferOverflowLinkType_t         linkType;
} hciDataBufferOverflowEvent_t;

/*! Authenticated Payload Timeout Expired Event : 0x57 */
typedef struct hciAuthenticatedPayloadTimeoutExpiredEvent_tag
{
    uint16_t                connectionHandle;
} hciAuthenticatedPayloadTimeoutExpiredEvent_t;

/*! OCF 0x0001 */
/*! HCI_Set_Event_Mask */
typedef struct hciSetEventMaskCommand_tag
{
    uint8_t             eventMask[8]; /* hciSetEventMaskEventShift_t */
} hciSetEventMaskCommand_t;

/*! OCF 0x0003 */
/*! HCI_Reset */
/*! No parameters */
/*! HCI_Reset - Command Complete Parameters */
typedef struct hciResetCommandComplete_tag
{
    hciErrorCode_t      status;
} hciResetCommandComplete_t;

/*! OCF 0x002D */
/*! HCI_Read_Transmit_Power_Level */
typedef struct hciReadTransmitPowerLevelCommand_tag
{
    uint16_t                        connectionHandle;
    bleTransmitPowerLevelType_t     type;
} hciReadTransmitPowerLevelCommand_t;

/*! HCI_Read_Transmit_Power_Level - Command Complete Parameters */
typedef struct hciReadTransmitPowerLevelCommandComplete_tag
{
    hciErrorCode_t                  status;
    uint16_t                        connectionHandle;
    int8_t                          transmitPowerlevel;  /* This is a signed 8 bit integer - Range: -30..20 dBm*/
} hciReadTransmitPowerLevelCommandComplete_t;

/*! OCF 0x0031 */
/*! HCI_Set_Controller_To_Host_Flow_Control */
typedef struct hciSetControllerToHostFlowControlCommand_tag
{
    hciControllerToHostFlowControlEnable_t      eventMask;
} hciSetControllerToHostFlowControlCommand_t;

/*! HCI_Set_Controller_To_Host_Flow_Control - Command Complete Parameters */
typedef struct hciSetControllerToHostFlowControlCommandComplete_tag
{
    hciErrorCode_t                              status;
} hciSetControllerToHostFlowControlCommandComplete_t;

/*! OCF 0x0033 */
/*! HCI_Host_Buffer_Size */
typedef struct hciHostBufferSizeCommand_tag
{
    uint16_t            hostAclDataPacketlength;
    uint8_t             hostSynchronousDataPacketLength;
    uint16_t            hostTotalNumAclDataPackets;
    uint16_t            hostTotalNumSynchronousDataPackets;
} hciHostBufferSizeCommand_t;

/*! HCI_Host_Buffer_Size - Command Complete Parameters */
typedef struct hciHostBufferSizeCommandComplete_tag
{
    hciErrorCode_t      status;
} hciHostBufferSizeCommandComplete_t;

/*! OCF 0x0035 */
/*! HCI_Host_Number_Of_Completed_Packets */
typedef struct bleHostCompletedPacketsParams_tag
{
    uint16_t            connectionHandle;
    uint16_t            hostNrOfCompletedPackets;
} bleHostCompletedPacketsParams_t;

typedef struct hciHostNumberOfCompletedPacketsCommand_tag
{
    uint8_t             numberOfHandles;
    uint16_t            connectionHandle[gcGapMaximumActiveConnections_c];
    uint16_t            hostNrOfCompletedPackets[gcGapMaximumActiveConnections_c];
} hciHostNumberOfCompletedPacketsCommand_t;

/*! HCI_Host_Number_Of_Completed_Packets - Command Complete Parameters */
typedef struct hciHostNumberOfCompletedPacketsCommandComplete_tag
{
    hciErrorCode_t                      status;
} hciHostNumberOfCompletedPacketsCommandComplete_t;

#if (gBLE41_d == TRUE)
/*! OCF 0x0063 */
/*! HCI_Set_Event_Mask_Page_2 */
typedef struct hciSetEventMaskPage2Command_tag
{
    uint8_t             eventMaskPage2[8]; /* hciSetEventMaskPage2EventShift_t */
} hciSetEventMaskPage2Command_t;

/*! HCI_Set_Event_Mask_Page_2 - Command Complete Parameters */
typedef struct hciSetEventMaskPage2CommandComplete_tag
{
    hciErrorCode_t      status;
} hciSetEventMaskPage2CommandComplete_t;

/*! OCF 0x007B */
/*! HCI_Read_Authenticated_Payload_Timeout */
typedef struct hciReadAuthenticatedPayloadTimeoutCommand_tag
{
    uint16_t            connectionHandle;
} hciReadAuthenticatedPayloadTimeoutCommand_t;

/*! HCI_Read_Authenticated_Payload_Timeout - Command Complete Parameters */
typedef struct hciReadAuthenticatedPayloadTimeoutCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint16_t            authenticatedPayloadTimeout;
} hciReadAuthenticatedPayloadTimeoutCommandComplete_t;

/*! OCF 0x007C */
/*! HCI_Write_Authenticated_Payload_Timeout */
typedef struct hciWriteAuthenticatedPayloadTimeoutCommand_tag
{
    uint16_t            connectionHandle;
    uint16_t            authenticatedPayloadTimeout;
} hciWriteAuthenticatedPayloadTimeoutCommand_t;

/*! HCI_Write_Authenticated_Payload_Timeout - Command Complete Parameters */
typedef struct hciWriteAuthenticatedPayloadTimeoutCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciWriteAuthenticatedPayloadTimeoutCommandComplete_t;

#endif /* gBLE41_d */

#if (gMwsIsSupported_d == TRUE)
typedef struct hciMwsChannelParametersCommand_tag
{
    mwsChannelEnable_t  channelEnable;
    uint16_t            rxCenterFrequency;
    uint16_t            txCenterFrequency;
    uint16_t            rxChannelBandwidth;
    uint16_t            txChannelBandwidth;
    uint8_t             channelType;
}hciMwsChannelParametersCommand_t;

typedef struct hciSetExternalFrameConfigurationCommand_tag
{
    uint16_t            extFrameDuration;
    uint16_t            extFrameSyncAssertOffset;
    uint16_t            extFrameSyncAssertJitter;
    uint8_t             extNumPeriods;
    uint16_t            aPeriodDuration[];
    periodType_t        aPeriodType[];
}hciSetExternalFrameConfigurationCommand_t;

typedef struct hciSetMwsSignalingCommand_tag
{
    uint16_t            mwsRxAssertOffset;
    uint16_t            mwsRxAssertJitter;
    uint16_t            mwsRxDeassertOffset;
    uint16_t            mwsRxDeassertJitter;
    uint16_t            mwsTxAssertOffset;
    uint16_t            mwsTxAssertJitter;
    uint16_t            mwsTxDeassertOffset;
    uint16_t            mwsTxDeassertJitter;
    uint16_t            mwsPatternAssertOffset;
    uint16_t            mwsPatternAssertJitter;
    uint16_t            mwsInactivityDurationAssertOffset;
    uint16_t            mwsInactivityDurationAssertJitter;
    uint16_t            mwsScanFrequencyAssertOffset;
    uint16_t            mwsScanFrequencyAssertJitter;
    uint16_t            mwsPriorityAssertOffsetRequest;
}hciSetMwsSignalingCommand_t;

typedef struct hciSetMwsSignalingRet_tag
{
    uint16_t            bluetoothRxPriorityAssertOffset;
    uint16_t            bluetoothRxPriorityAssertJitter;
    uint16_t            bluetoothRxPriorityDeassertOffset;
    uint16_t            bluetoothRxPriorityDeassertJitter;
    uint16_t            _802RxPriorityAssertOffset;
    uint16_t            _802RxPriorityAssertJitter;
    uint16_t            _802RxPriorityDeassertOffset;
    uint16_t            _802RxPriorityDeassertJitter;
    uint16_t            bluetoothTxOnAssertOffset;
    uint16_t            bluetoothTxOnAssertJitter;
    uint16_t            bluetoothTxOnDeassertOffset;
    uint16_t            bluetoothTxOnDeassertJitter;
    uint16_t            _802TxOnAssertOffset;
    uint16_t            _802TxOnAssertJitter;
    uint16_t            _802TxOnDeassertOffset;
    uint16_t            _802TxOnDeassertJitter;
}hciSetMwsSignalingRet_t;

typedef struct hciSetMwsTransportLayerCommand_tag
{
    uint8_t             transportLayer;
    uint32_t            toMwsBaudRate;
    uint32_t            fromMwsBaudRate;
}hciSetMwsTransportLayerCommand_t;

typedef struct hciGetMwsTransportLayerConfigurationCommand_tag
{
}hciGetMwsTransportLayerConfigurationCommand_t;

typedef struct hciSetMwsScanFrequencyTableCommand_tag
{
    uint8_t             numScanFrequencies;
    uint16_t            aScanFrequencyLow[];
    uint16_t            aScanFrequencyHigh[];
}hciSetMwsScanFrequencyTableCommand_t;

typedef struct hciSetMwsPatternConfigurationCommand_tag
{
    uint8_t             mwsPatternIndex;
    uint8_t             mwsPatternNumIntervals;
    uint16_t            aMwsPatternIntervalDuration[];
    uint16_t            aMwsPatternIntervalType[];
}hciSetMwsPatternConfigurationCommand_t;
#endif

/*! HCI Commands and Events for ************************************************
*   OGF : 0x04 : Informational Parameters
***************************************************************************** */

/*! OCF 0x0001 */
/*! HCI_LE_Read_Local_Version_Information */
/*! No parameters */
/*! HCI_LE_Read_Local_Version_Information - Command Complete Parameters */
typedef struct hciReadLocalVersionInfoCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             hciVersion;
    uint16_t            hciRevision;
    uint8_t             lmpPalVersion;
    uint16_t            manufacturerName;
    uint16_t            lmpPalSubversion;
} hciReadLocalVersionInfoCommandComplete_t;

/*! OCF 0x0002 */
/*! HCI_Read_Local_Supported_Commands */
/*! No parameters */
/*! HCI_Read_Local_Supported_Commands - Command Complete Parameters */
typedef struct hciReadLocalSupportedCommandsCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             supportedCommands[64]; /* hciSupportedCommandsShift_t */
} hciReadLocalSupportedCommandsCommandComplete_t;

/*! OCF 0x0003 */
/*! HCI_Read_Local_Supported_Features */
/*! No parameters */
/*! HCI_Read_Local_Supported_Features - Command Complete Parameters */
typedef struct hciReadLocalSupportedFeaturesCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             lmpFeatures[8];
} hciReadLocalSupportedFeaturesCommandComplete_t;

/*! OCF 0x0009 */
/*! HCI_Read_BD_ADDR */
/*! No parameters */
/*! HCI_Read_BD_ADDR - Command Complete Parameters */
typedef struct hciReadBdAddrCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             bdAddr[gcBleDeviceAddressSize_c];
} hciReadBdAddrCommandComplete_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x05 : Status Parameters 
***************************************************************************** */

/*! OCF 0x0005 */
/*! HCI_Read_RSSI */
typedef struct hciReadRssiCommand_tag
{
    uint16_t            handle;
} hciReadRssiCommand_t;
/*! HCI_Read_RSSI - Command Complete Parameters */
typedef struct hciReadRssiCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            handle;
    int8_t              rssi; /* This is a signed 8 bit integer - Range: -127..20 dBm for a LE Controller*/
} hciReadRssiCommandComplete_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x08 : LE Controller Commands 
***************************************************************************** */

/*! OCF 0x0001 */
/*! HCI_LE_Set_Event_Mask */
typedef struct hciLeSetEventMaskCommand_tag
{
    uint8_t             leEventMask[8]; /* hciLeSetEventMaskEventShift_t */
} hciLeSetEventMaskCommand_t;

/*! OCF 0x0002 */
/*! HCI_LE_Read_Buffer_Size */
/*! No parameters */

/*! OCF 0x0003 */
/*! HCI_LE_Read_Local_Supported_Features */
/*! No parameters */

/*! OCF 0x0005 */
/*! HCI_LE_Set_Random_Address */
typedef struct hciLeSetRandomAddressCommand_tag
{
    uint8_t             randomAddress[gcBleDeviceAddressSize_c];
} hciLeSetRandomAddressCommand_t;

/*! OCF 0x0006 */
/*! HCI_LE_Set_Advertising_Parameters */
typedef struct hciLeSetAdvertisingParametersCommand_tag
{
    uint16_t                        advertisingIntervalMin;
    uint16_t                        advertisingIntervalMax;
    bleAdvertisingType_t            advertisingType;
    bleAddressType_t                ownAddressType;
    bleAddressType_t                directAddressType;
    uint8_t                         directAddress[gcBleDeviceAddressSize_c];
    bleAdvertisingChannelMap_t      advertisingChannelMap;
    bleAdvertisingFilterPolicy_t    advertisigFilterPolicy;
} hciLeSetAdvertisingParametersCommand_t;

/*! OCF 0x0007 */
/*! HCI_LE_Read_Advertising_Channel_Tx_Power */
/*! No parameters */

/*! OCF 0x0008 */
/*! HCI_LE_Set_Advertising_Data */
typedef struct hciLeSetAdvertisingDataCommand_tag
{
    uint8_t             advertisingDataLength;
    uint8_t             advertisingData[gHciLeAdvertisingDataLength_c];
} hciLeSetAdvertisingDataCommand_t;

/*! OCF 0x0009 */
/*! HCI_LE_Set_Scan_Response_Data */
typedef struct hciLeScanResponseDataCommand_tag
{
    uint8_t             scanResponseDataLength;
    uint8_t             scanResponseData[gHciLeScanResponseDataLength_c];
} hciLeSetScanResponseDataCommand_t;

/*! OCF 0x000A */
/*! HCI_LE_Set_Advertise_Enable */
typedef struct hciLeSetAdvertiseEnableCommand_tag
{
    hciLeAdvertiseEnable_t      advertiseEnable;
} hciLeSetAdvertiseEnableCommand_t;

/*! OCF 0x000B */
/*! HCI_LE_Set_Scan_Parameters */
typedef struct hciLeSetScanParametersCommand_tag
{
    bleScanType_t               scanType;
    uint16_t                    scanInterval;
    uint16_t                    scanWindow;
    bleAddressType_t            ownAddressType;
    bleScanningFilterPolicy_t   scanningFilterPolicy;
} hciLeSetScanParametersCommand_t;

/*! OCF 0x000C */
/*! HCI_LE_Set_Scan_Enable */
typedef struct hciLeSetScanEnableCommand_tag
{
    hciLeScanEnable_t           scanEnable;
    hciLeFilterDuplicates_t     filterDuplicates;
} hciLeSetScanEnableCommand_t;

/*! LE Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x02 */
typedef struct bleAdvertisingReportEventParams_tag
{
    bleAdvertisingReportEventType_t         eventType;
    bleAddressType_t                        addressType;
    uint8_t                                 address[gcBleDeviceAddressSize_c];
    uint8_t                                 dataLength;
    uint8_t                                 data[gHciLeAdvertisingDataLength_c];
    uint8_t                                 rssi;
} bleAdvertisingReportEventParams_t;

/*! LE Direct Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x0B */
typedef struct bleDirectAdvertisingReportEventParams_tag
{
    bleAdvertisingReportEventType_t         eventType;
    bleAddressType_t                        directAddressType;
    uint8_t                                 directAddress[gcBleDeviceAddressSize_c];
    bleAddressType_t                        addressType;
    uint8_t                                 address[gcBleDeviceAddressSize_c];
    uint8_t                                 rssi;
} bleDirectAdvertisingReportEventParams_t;

typedef struct hciLeAdvertisingReportEvent_tag
{
    uint8_t                                 numReports;
    bleAdvertisingReportEventParams_t       *aAdvReports;
} hciLeAdvertisingReportEvent_t;

/*! OCF 0x000D */
/*! HCI_LE_Create_Connection */
typedef struct hciLeCreateConnectionCommand_tag
{
    uint16_t                    scanInterval;
    uint16_t                    scanWindow;
    bleInitiatorFilterPolicy_t  initiatorFilterPolicy;
    bleAddressType_t            peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    bleAddressType_t            ownAddressType;
    uint16_t                    connIntervalMin;
    uint16_t                    connIntervalMax;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    uint16_t                    minimumCELength;
    uint16_t                    maximumCELength;
} hciLeCreateConnectionCommand_t;

/*! LE Connection Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x01 */
typedef struct hciLeConnectionCompleteEvent_tag
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    bleLlConnectionRole_t       role;
    bleAddressType_t            peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    uint16_t                    connInterval;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    bleMasterClockAccuracy_t    masterClockAccuracy;
} hciLeConnectionCompleteEvent_t;

/*! OCF 0x000E */
/*! HCI_LE_Create_Connection_Cancel */
/*! No parameters */

/*! OCF 0x000F */
/*! HCI_LE_Read_White_List_Size */
/*! No parameters */

/*! OCF 0x0010 */
/*! HCI_LE_Clear_White_List */
/*! No parameters */

/*! OCF 0x0011 */
/*! HCI_LE_Add_Device_To_White_List */
typedef struct hciLeAddDeviceToWhiteListCommand_tag
{
    bleAddressType_t    addressType;
    uint8_t             address[gcBleDeviceAddressSize_c];
} hciLeAddDeviceToWhiteListCommand_t;

/*! OCF 0x0012 */
/*! HCI_LE_Remove_Device_From_White_List */
typedef struct hciLeRemoveDeviceFromWhiteListCommand_tag
{
    bleAddressType_t    addressType;
    uint8_t             address[gcBleDeviceAddressSize_c];
} hciLeRemoveDeviceFromWhiteListCommand_t;

/*! OCF 0x0013 */
/*! HCI_LE_Connection_Update */
typedef struct hciLeConnectionUpdateCommand_tag
{
    uint16_t            connectionHandle;
    uint16_t            connIntervalMin;
    uint16_t            connIntervalMax;
    uint16_t            connLatency;
    uint16_t            supervisionTimeout;
    uint16_t            minimumCeLength;
    uint16_t            maximumCeLength;
} hciLeConnectionUpdateCommand_t;

/*! LE Connection Update Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x03 */
typedef struct hciLeConnectionUpdateCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint16_t            connInterval;
    uint16_t            connLatency;
    uint16_t            supervisionTimeout;
} hciLeConnectionUpdateCompleteEvent_t;

/*! OCF 0x0014 */
/*! HCI_LE_Set_Host_Channel_Classification */
typedef struct hciLeSetHostChannelClassificationCommand_tag
{
    uint8_t             channelMap[5];
} hciLeSetHostChannelClassificationCommand_t;

/*! OCF 0x0015 */
/*! HCI_LE_Read_Channel_Map */
typedef struct hciLeReadChannelMapCommand_tag
{
    uint16_t            connectionHandle;
} hciLeReadChannelMapCommand_t;

/*! OCF 0x0016 */
/*! HCI_LE_Read_Remote_Used_Features */
typedef struct hciLeReadRemoteUsedFeaturesCommand_tag
{
    uint16_t            connectionHandle;
} hciLeReadRemoteUsedFeaturesCommand_t;

/*! LE Read Remote Used Features Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x04 */
typedef struct hciLeReadRemoteUsedFeaturesCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             leFeatures[8]; /* hciLeSupportedFeatures_tag */
} hciLeReadRemoteUsedFeaturesCompleteEvent_t;

/*! LE Long Term Key Request Event : LE Meta Event : 0x3E - Subevent Code : 0x05 */
typedef struct hciLeLongTermKeyRequestEvent_tag
{
    uint16_t                connectionHandle;
    uint8_t                 randomNumber[8];
    uint16_t                encryptionDiversifier;
} hciLeLongTermKeyRequestEvent_t;

/*! LE Long Term Key Request Event : LE Meta Event : 0x3E - Subevent Code : 0x06 */
typedef struct hciLeRemoteConnectionParameterRequestEvent_tag
{
    uint16_t                connectionHandle;
    uint16_t                intervalMin;
    uint16_t                intervalMax;
    uint16_t                latency;
    uint16_t                timeout;
} hciLeRemoteConnectionParameterRequestEvent_t;

#if (gBLE42_d == TRUE)
/*! LE Data Length Change Event : LE Meta Event : 0x3E - Subevent Code : 0x07 */
typedef struct hciLeDataLengthChangeEvent_tag
{
    uint16_t                connectionHandle;
    uint16_t                maxTxOctets;
    uint16_t                maxTxTime;
    uint16_t                maxRxOctets;
    uint16_t                maxRxTime;
}hciLeDataLengthChangeEvent_t;

/*! LE Read Local P-256 Public Key Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x08 */
typedef struct hciLeReadLocalP256PublicKeyCompleteEvent_tag
{
    hciErrorCode_t          status;
    uint8_t                 localP256PublicKey[64];
}hciLeReadLocalP256PublicKeyCompleteEvent_t;

/*! LE Generate DHKey Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x09 */
typedef struct hciLeGenerateDhKeyCompleteEvent_tag
{
    hciErrorCode_t          status;
    uint8_t                 dhKey[32];
}hciLeGenerateDhKeyCompleteEvent_t;

/*! LE Enhanced Connection Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x0A */
typedef struct hciLeEnhancedConnectionCompleteEvent_tag
{

    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    bleLlConnectionRole_t       role;
    bleAddressType_t            peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    uint8_t                     localResolvablePrivateAddress[gcBleDeviceAddressSize_c];
    uint8_t                     peerResolvablePrivateAddress[gcBleDeviceAddressSize_c];
    uint16_t                    connInterval;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    bleMasterClockAccuracy_t    masterClockAccuracy;
}hciLeEnhancedConnectionCompleteEvent_t;

typedef struct hciLeDirectAdvertisingReportEvent_tag
{
    uint8_t                                 numReports;
    bleDirectAdvertisingReportEventParams_t *aAdvReports;
} hciLeDirectAdvertisingReportEvent_t;
#endif /* gBLE42_d */

/*! OCF 0x0017 */
/*! HCI_LE_Encrypt */
typedef struct hciLeEncryptCommand_tag
{
    uint8_t             key[16];
    uint8_t             plaintextData[16];
} hciLeEncryptCommand_t;

/*! OCF 0x0018 */
/*! HCI_LE_Rand */
/*! No parameters */

/*! OCF 0x0019 */
/*! HCI_LE_Start_Encryption */
typedef struct hciLeStartEncryptionCommand_tag
{
    uint16_t            connectionHandle;
    uint8_t             randomNumber[8];
    uint16_t            encryptedDiversifier;
    uint8_t             longTermKey[16];
} hciLeStartEncryptionCommand_t;

/*! Encryption Change Event : 0x08 */
typedef struct hciEncryptionChangeEvent_tag
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    hciLlEncryptionEnabled_t    encryptionEnabled;
} hciEncryptionChangeEvent_t;

/*! Encryption Key refresh Complete Event : 0x30 */
typedef struct hciEncryptionKeyRefreshCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciEncryptionKeyRefreshCompleteEvent_t;

/*! OCF 0x001A */
/*! HCI_LE_Long_Term_Key_Request_Reply */
typedef struct hciLeLongTermKeyRequestReplyCommand_tag
{
    uint16_t            connectionHandle;
    uint8_t             longTermKey[16];
} hciLeLongTermKeyRequestReplyCommand_t;

/*! OCF 0x001B */
/*! HCI_LE_Long_Term_Key_Request_Negative_Reply */
typedef struct hciLeLongTermKeyRequestNegativeReplyCommand_tag
{
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestNegativeReplyCommand_t;

/*! OCF 0x001D */
/*! HCI_LE_Receiver_Test */
typedef struct hciLeReceiverTestCommand_tag
{
    bleChannelFrequency_t   rxChannel;
} hciLeReceiverTestCommand_t;

/*! OCF 0x001E */
/*! HCI_LE_Transmitter_Test */
typedef struct hciLeTransmitterTestCommand_tag
{
    bleChannelFrequency_t       txChannel;
    uint8_t                     lengthOfTestData;
    bleTxTestPacketPayload_t    packetPayload;
} hciLeTransmitterTestCommand_t;

#if (gBLE41_d == TRUE)
/*! OCF 0x0020 */
/*! LE_Remote_Connection_Parameter_Request_Reply */
typedef struct hciLeRemoteConnectionParameterRequestReplyCommand_tag
{
    uint16_t            connectionHandle;
    uint16_t            intervalMin;
    uint16_t            intervalMax;
    uint16_t            latency;
    uint16_t            timeout;
    uint16_t            minimumCeLength;
    uint16_t            maximumCeLength;
} hciLeRemoteConnectionParameterRequestReplyCommand_t;

/*! OCF 0x0021 */
/*! LE_Remote_Connection_Parameter_Request_Negative_Reply */
typedef struct hciLeRemoteConnectionParameterRequestNegativeReplyCommand_tag
{
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t;
#endif /* gBLE41_d */

#if (gBLE42_d == TRUE)
/*! HCI_LE_Set_Data_Length */
typedef struct hciLeSetDataLengthCommand_tag
{
    uint16_t            connectionHandle;
    uint16_t            txOctets;
    uint16_t            txTime;
} hciLeSetDataLengthCommand_t;

/*! HCI_LE_Write_Suggested_Default_Data_Length */
typedef struct hciLeWriteSuggestedDefaultDataLengthCommand_tag
{
    uint16_t            suggestedMaxTxOctets;
    uint16_t            suggestedMaxTxTime;
} hciLeWriteSuggestedDefaultDataLengthCommand_t;

/*! HCI_LE_Generate_DHKey */
typedef struct hciLeGenerateDhKeyCommand_tag
{
    uint8_t             remoteP256PublicKey[64];
} hciLeGenerateDhKeyCommand_t;

/*! HCI_LE_Add_Device_To_Resolving_List */
typedef struct hciLeAddDeviceToResolvingListCommand_tag
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
    uint8_t             peerIRK[gcSmpIrkSize_c];
    uint8_t             localIRK[gcSmpIrkSize_c];
} hciLeAddDeviceToResolvingListCommand_t;

/*! HCI_LE_Remove_Device_From_Resolving_List */
typedef struct hciLeRemoveDeviceFromResolvingListCommand_tag
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeRemoveDeviceFromResolvingListCommand_t;

/*! HCI_LE_Read_Peer_Resolvable_Address */
typedef struct hciLeReadPeerResolvableAddressCommand_tag
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeReadPeerResolvableAddressCommand_t;

/*! HCI_LE_Read_Local_Resolvable_Address */
typedef struct hciLeReadLocalResolvableAddressCommand_tag
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeReadLocalResolvableAddressCommand_t;

/*! HCI_LE_Set_Address_Resolution_Enable */
typedef struct hciLeSetAddressResolutionEnableCommand_tag
{
    bool_t              addressResolutionEnable;
} hciLeSetAddressResolutionEnableCommand_t;

/*! HCI_LE_Set_Resolvable_Private_Address_Timeout */
typedef struct hciLeSetResolvablePrivateAddressTimeoutCommand_tag
{
    uint16_t            rpaTimeout;
} hciLeSetResolvablePrivateAddressTimeoutCommand_t;
#endif

typedef struct hciVendorSpecificDebugCommand_tag
{
    uint16_t            cmdFlag;
    uint8_t*            pParams;
    uint8_t             paramsLength;
}hciVendorSpecificDebugCommand_t;

/*
* Command Complete Parameters
*/
/*! HCI Command Complete Events ************************************************
*   OGF : 0x08 : LE Controller Commands 
***************************************************************************** */
/*! HCI_LE_Set_Event_Mask - Return Parameters */
typedef struct hciLeSetEventMaskCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetEventMaskCommandComplete_t;

/*! HCI_LE_Read_Buffer_Size - Return Parameters */
typedef struct hciLeReadBufferSizeCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            hcLeDataPacketLength;
    uint8_t             hcTotalNumLeDataPackets;
} hciLeReadBufferSizeCommandComplete_t;

/*! HCI_LE_Read_Local_Supported_Features - Return Parameters */
/* Only LMP Feature Page 0 is supported and required by BLE */
typedef struct hciLeReadLocalSupportedFeaturesCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             leFeatures[8]; /* hciLeSupportedFeatures_tag */
} hciLeReadLocalSupportedFeaturesCommandComplete_t;

/*! HCI_LE_Set_Random_Address - Return Parameters */
typedef struct hciLeSetRandomAddressCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetRandomAddressCommandComplete_t;

/*! HCI_LE_Set_Advertising_Parameters - Return Parameters */
typedef struct hciLeSetAdvertisingParametersCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetAdvertingParametersCommandComplete_t;

/*! HCI_LE_Read_Advertising_Channel_Tx_Power - Return Parameters */
typedef struct hciLeReadAdvertisingChannelTxPowerCommandComplete_tag
{
    hciErrorCode_t      status;
    int8_t              transmitPowerlevel; /* This is a signed 8 bit integer - Range: -20..10 dBm */
} hciLeReadAdvertisingChannelTxPowerCommandComplete_t;

/*! HCI_LE_Set_Advertising_Data - Return Parameters */
typedef struct hciLeSetAdvertisingDataCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetAdvertisingDataCommandComplete_t;

/*! HCI_LE_Set_Scan_Response_Data - Return Parameters */
typedef struct hciLeSetScanResponseDataCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetScanResponseDataCommandComplete_t;

/*! HCI_LE_Set_Advertise_Enable - Return Parameters */
typedef struct hciLeSetAdvertiseEnableCommandComplete_tag
{
    hciErrorCode_t              status;
} hciLeSetAdvertiseEnableCommandComplete_t;

/*! HCI_LE_Set_Scan_Parameters - Return Parameters */
typedef struct hciLeSetScanParametersCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetScanParametersCommandComplete_t;

/*! HCI_LE_Set_Scan_Enable - Return Parameters */
typedef struct hciLeSetScanEnableCommandComplete_tag
{
    hciErrorCode_t              status;
} hciLeSetScanEnableCommandComplete_t;

/*! HCI_LE_Create_Connection_Cancel - Return Parameters */
typedef struct hciLeCreateConnectionCancelCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeCreateConnectionCancelCommandComplete_t;

/*! HCI_LE_Read_White_List_Size - Return Parameters */
typedef struct hciLeReadWhiteListSizeCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             whiteListSize;
} hciLeReadWhiteListSizeCommandComplete_t;

/*! HCI_LE_Clear_White_List - Return Parameters */
typedef struct hciLeClearWhiteListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeClearWhiteListCommandComplete_t;

/*! HCI_LE_Add_Device_To_White_List - Return Parameters */
typedef struct hciLeAddDeviceToWhiteListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeAddDeviceToWhiteListCommandComplete_t;

/*! HCI_LE_Remove_Device_From_White_List - Return Parameters */
typedef struct hciLeRemoveDeviceFromWhiteListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeRemoveDeviceFromWhiteListCommandComplete_t;

/*! HCI_LE_Set_Host_Channel_Classification - Return Parameters */
typedef struct hciLeSetHostChannelClassificationCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetHostChannelClassificationCommandComplete_t;

/*! HCI_LE_Read_Channel_Map - Return Parameters */
typedef struct hciLeReadChannelMapCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             channelMap[5];
} hciLeReadChannelMapCommandComplete_t;

/*! HCI_LE_Encrypt - Return Parameters */
typedef struct hciLeEncryptCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             encryptedData[16];
} hciLeEncryptCommandComplete_t;

/*! HCI_LE_Rand - Return Parameters */
typedef struct hciLeRandCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             randomNumber[8];
} hciLeRandCommandComplete_t;
/*! HCI_LE_Long_Term_Key_Request_Reply - Return Parameters */
typedef struct hciLeLongTermKeyRequestReplyCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestReplyCommandComplete_t;

/*! HCI_LE_Long_Term_Key_Request_Negative_Reply - Return Parameters */
typedef struct hciLeLongTermKeyRequestNegativeReplyCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestNegativeReplyCommandComplete_t;

/*! HCI_LE_Read_Supported_States - Return Parameters */
typedef struct hciLeReadSupportedStatesCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             leStates[8]; /* hciLeLLSupportedStatesShift_t */
} hciLeReadSupportedStatesCommandComplete_t;

/*! HCI_LE_Receiver_Test - Return Parameters */
typedef struct hciLeReceiverTestCommandComplete_tag
{
    hciErrorCode_t          status;
} hciLeReceiverTestCommandComplete_t;

/*! HCI_LE_Transmitter_Test - Return Parameters */
typedef struct hciLeTransmitterTestCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeTransmitterTestCommandComplete_t;

/*! HCI_LE_Test_End - Return Parameters */
typedef struct hciLeTestEndCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            numberOfPackets;
} hciLeTestEndCommandComplete_t;

#if (gBLE41_d == TRUE)
/*! LE_Remote_Connection_Parameter_Request_Reply - Return Parameters */
typedef struct hciLeRemoteConnectionParameterRequestReplyCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeRemoteConnectionParameterRequestReplyCommandComplete_t;

/*! LE_Remote_Connection_Parameter_Request_Negative_Reply - Return Parameters */
typedef struct hciLeRemoteConnectionParameterRequestReplyNegativeCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeRemoteConnectionParameterRequestNegativeReplyCommandComplete_t;
#endif /* gBLE41_d */

#if (gBLE42_d == TRUE)
/*! HCI_LE_Set_Data_Length Return Parameters */
typedef struct hciLeSetDataLengthCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeSetDataLengthCommandComplete_t;

/*! HCI_LE_Read_Suggested_Default_Data_Length Return Parameters */
typedef struct hciLeReadSuggestedDefaultDataLengthCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            suggestedMaxTxOctets;
    uint16_t            suggestedMaxTxTime;
} hciLeReadSuggestedDefaultDataLengthCommandComplete_t;

/*! HCI_LE_Write_Suggested_Default_Data_Length Return Parameters */
typedef struct hciLeWriteSuggestedDefaultDataLengthCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeWriteSuggestedDefaultDataLengthCommandComplete_t;

/*! HCI_LE_Add_Device_To_Resolving_List Return Parameters */
typedef struct hciLeAddDeviceToResolvingListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeAddDeviceToResolvingListCommandComplete_t;

/*! HCI_LE_Remove_Device_From_Resolving_List Return Parameters */
typedef struct hciLeRemoveDeviceFromResolvingListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeRemoveDeviceFromResolvingListCommandComplete_t;

/*! HCI_LE_Clear_Resolving_List Return Parameters */
typedef struct hciLeClearResolvingListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeClearResolvingListCommandComplete_t;

/*! HCI_LE_Read_Peer_Resolvable_Address Return Parameters */
typedef struct hciLeReadPeerResolvableAddressCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             peerResolvableAddress[gcBleDeviceAddressSize_c];
} hciLeReadPeerResolvableAddressCommandComplete_t;

/*! HCI_LE_Read_Local_Resolvable_Address Return Parameters */
typedef struct hciLeReadLocalResolvableAddressCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             localResolvableAddress[gcBleDeviceAddressSize_c];
} hciLeReadLocalResolvableAddressCommandComplete_t;

/*! HCI_LE_Set_Address_Resolution_Enable Return Parameters */
typedef struct hciLeSetAddressResolutionEnableCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetAddressResolutionEnableCommandComplete_t;

/*! HCI_LE_Set_Resolvable_Private_Address_Timeout Return Parameters */
typedef struct hciLeSetResolvablePrivateAddressTimeoutCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetResolvablePrivateAddressTimeoutCommandComplete_t;

/*! HCI_LE_Read_Maximum_Data_Length Return Parameters */
typedef struct hciLeReadMaximumDataLengthCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            supportedMaxTxOctets;
    uint16_t            supportedMaxTxTime;
    uint16_t            supportedMaxRxOctets;
    uint16_t            supportedMaxRxTime;
} hciLeReadMaximumDataLengthCommandComplete_t;
#endif

/*! LE Meta Event : 0x3E */
typedef struct hciLeMetaEvent_tag
{
    hciLeMetaSubEventCode_t        subEventCode;
    PACKED_UNION
    {
        hciLeConnectionCompleteEvent_t                  hciLeConnCompleteEvent;
        hciLeAdvertisingReportEvent_t                   hciLeAdvReportEvent;
        hciLeConnectionUpdateCompleteEvent_t            hciLeConnUpdateCompleteEvent;
        hciLeReadRemoteUsedFeaturesCompleteEvent_t      hciLeReadRemoteUsedFeaturesCompleteEvent;
        hciLeLongTermKeyRequestEvent_t                  hciLeLongTermKeyReqEvent;
#if (gBLE41_d == TRUE)
        hciLeRemoteConnectionParameterRequestEvent_t    hciLeRemoteConnectionParameterRequestEvent;
#endif /* gBLE41_d */
#if (gBLE42_d == TRUE)
        hciLeDataLengthChangeEvent_t                    hciLeDataLengthChangeEvent;
        hciLeReadLocalP256PublicKeyCompleteEvent_t      hciLeReadLocalP256PublicKeyCompleteEvent;
        hciLeGenerateDhKeyCompleteEvent_t               hciLeGenerateDhKeyCompleteEvent;
        hciLeEnhancedConnectionCompleteEvent_t          hciLeEnhancedConnCompleteEvent;
        hciLeDirectAdvertisingReportEvent_t             hciLeDirectAdvReportEvent;
#endif /* gBLE42_d */
    }eventData;
} hciLeMetaEvent_t;

typedef struct hciCommandCompleteEvent_tag
{
    uint8_t                 numHciCommandPackets;
    hciCommandOpCode_t      commandOpCode;
    union
    {
        /*! HCI OGF : 0x03 : Controller & Baseband Commands */
        hciSetEventMaskCommandComplete_t                        hciSetEventMaskCommComplete;
        hciResetCommandComplete_t                               hciResetCommComplete;
        hciReadTransmitPowerLevelCommandComplete_t              hciReadTransmitPowerLevelCommComplete;
        hciSetControllerToHostFlowControlCommandComplete_t      hciSetControllerToHostFlowControlCommComplete;
        hciHostBufferSizeCommandComplete_t                      hciHostBufferSizeCommComplete;
        hciHostNumberOfCompletedPacketsCommandComplete_t        hciHostNumberOfCompletedPacketsCommComplete;
#if (gBLE41_d == TRUE)
        hciSetEventMaskPage2CommandComplete_t                   hciSetEventMaskPage2CommComplete;
        hciReadAuthenticatedPayloadTimeoutCommandComplete_t     hciReadAuthenticatedPayloadTimeoutCommComplete;
        hciWriteAuthenticatedPayloadTimeoutCommandComplete_t    hciWriteAuthenticatedPayloadTimeoutCommComplete;
#endif /* gBLE41_d */
        /*! HCI OGF : 0x04 : Informational Parameters */
        hciReadLocalVersionInfoCommandComplete_t                hciReadLocalVersionInfoCommComplete;
        hciReadLocalSupportedCommandsCommandComplete_t          hciReadLocalSupportedCommandsCommComplete;
        hciReadLocalSupportedFeaturesCommandComplete_t          hciReadLocalSupportedFeaturesCommComplete;
        hciReadBdAddrCommandComplete_t                          hciReadBdAddrCommComplete;
        /*! HCI OGF : 0x05 : Status Parameters */
        hciReadRssiCommandComplete_t                            hciReadRssiCommComplete;
        /*! HCI OGF : 0x08 : LE Controller Commands */
        hciLeSetEventMaskCommandComplete_t                      hciLeSetEventMaskCommComplete;
        hciLeReadBufferSizeCommandComplete_t                    hciLeReadBufferSizeCommComplete;
        hciLeReadLocalSupportedFeaturesCommandComplete_t        hciLeReadLocalSupportedFeaturesCommComplete;
        hciLeSetRandomAddressCommandComplete_t                  hciLeSetRandomAddressCommComplete;
        hciLeSetAdvertingParametersCommandComplete_t            hciLeSetAdvertingParametersCommComplete;
        hciLeReadAdvertisingChannelTxPowerCommandComplete_t     hciLeReadAdvertisingChannelTxPowerCommComplete;
        hciLeSetAdvertisingDataCommandComplete_t                hciLeSetAdvertiseDataCommComplete;
        hciLeSetScanResponseDataCommandComplete_t               hciLeSetScanResponseDataCommComplete;
        hciLeSetAdvertiseEnableCommandComplete_t                hciLeSetAdvertiseEnableCommComplete;
        hciLeSetScanParametersCommandComplete_t                 hciLeSetScanParametersCommComplete;
        hciLeSetScanEnableCommandComplete_t                     hciLeSetScanEnableCommComplete;
        hciLeCreateConnectionCancelCommandComplete_t            hciLeCreateConnectionCancelCommComplete;
        hciLeReadWhiteListSizeCommandComplete_t                 hciLeReadWhiteListSizeCommComplete;
        hciLeClearWhiteListCommandComplete_t                    hciLeClearWhiteListCommComplete;
        hciLeAddDeviceToWhiteListCommandComplete_t              hciLeAddDeviceToWhiteListCommComplete;
        hciLeRemoveDeviceFromWhiteListCommandComplete_t         hciLeRemoveDeviceFromWhiteListCommComplete;
        hciLeSetHostChannelClassificationCommandComplete_t      hciLeSetHostChannelClassificationCommComplete;
        hciLeReadChannelMapCommandComplete_t                    hciLeReadChannelMapCommComplete;
        hciLeEncryptCommandComplete_t                           hciLeEncryptCommComplete;
        hciLeRandCommandComplete_t                              hciLeRandCommComplete;
        hciLeLongTermKeyRequestReplyCommandComplete_t           hciLeLongTermKeyRequestReplyCommComplete;
        hciLeLongTermKeyRequestNegativeReplyCommandComplete_t   hciLeLongTermKeyRequestNegativeReplyCommComplete;
        hciLeReadSupportedStatesCommandComplete_t               hciLeReadSupportedStatesCommComplete;
        hciLeReceiverTestCommandComplete_t                      hciLeReceiverTestCommComplete;
        hciLeTransmitterTestCommandComplete_t                   hciLeTransmitterTestCommComplete;
        hciLeTestEndCommandComplete_t                           hciLeTestEndCommComplete;
#if (gBLE41_d == TRUE)
        hciLeRemoteConnectionParameterRequestReplyCommandComplete_t             hciLeRemoteConnectionParameterRequestReplyCommComplete;
        hciLeRemoteConnectionParameterRequestNegativeReplyCommandComplete_t     hciLeRemoteConnectionParameterRequestNegativeReplyCommComplete;
#endif /* gBLE41_d */
#if (gBLE42_d == TRUE)
        hciLeWriteSuggestedDefaultDataLengthCommandComplete_t    hciLeWriteSuggestedDefaultDataLengthCommComplete;
        hciLeReadSuggestedDefaultDataLengthCommandComplete_t     hciLeReadSuggestedDefaultDataLengthCommComplete;
        hciLeSetDataLengthCommandComplete_t						 hciLeSetDataLengthDataLengthCommComplete;
        hciLeSetResolvablePrivateAddressTimeoutCommandComplete_t hciLeSetResolvablePrivateAddressTimeoutCommComplete;
        hciLeSetAddressResolutionEnableCommandComplete_t         hciLeSetAddressResolutionEnableCommComplete;
        hciLeClearResolvingListCommandComplete_t                 hciLeClearResolvingListCommComplete;
        hciLeAddDeviceToResolvingListCommandComplete_t           hciLeAddDeviceToResolvingListCommComplete;
        hciLeReadPeerResolvableAddressCommandComplete_t          hciLeReadPeerResolvableAddressCommComplete;
        hciLeReadLocalResolvableAddressCommandComplete_t         hciLeReadLocalResolvableAddressCommComplete;
#endif /* gBLE41_d */
    }commCompleteReturnParams;
} hciCommandCompleteEvent_t;

typedef struct hciEvent_tag
{
    hciEventCode_t      eventCode;
    uint8_t             parLength;
    union
    {
        hciDisconnectionCompleteEvent_t                 hciDisconnectionCompleteEvent;
        hciEncryptionChangeEvent_t                      hciEncryptionChangeEvent;
        hciReadRemoteVersionInformationCompleteEvent_t  hciReadRemoteVersionInformationCompleteEvent;
        hciCommandCompleteEvent_t                       hciCommandCompleteEvent;
        hciCommandStatusEvent_t                         hciCommandStatusEvent;
        hciHardwareErrorEvent_t                         hciHardwareErrorEvent;
        hciNumberOfCompletedPacketsEvent_t              hciNumberOfCompletedPacketsEvent;
        hciDataBufferOverflowEvent_t                    hciDataBufferOverflowEvent;
        hciEncryptionKeyRefreshCompleteEvent_t          hciEncryptionKeyRefreshCompleteEvent;
        hciLeMetaEvent_t                                hciLeMetaEvent;
#if (gBLE41_d == TRUE)
        hciAuthenticatedPayloadTimeoutExpiredEvent_t    hciAuthenticatedPayloadTimeoutExpiredEvent;
#endif /* gBLE41_d */
    }eventData;
} hciEvent_t;

/*! ****************************************************************************
*   COMMANDS
***************************************************************************** */
typedef struct hciCommand_tag
{
    hciCommandOpCode_t  opCode;
    uint8_t             parLength;
    union
    {
        /*! HCI OGF : 0x01 : Link Control Commands */
        hciDisconnectCommand_t                          hciDisconnectCmd;
        hciReadRemoteVersionInformationCommand_t        hciReadRemoteVersionInformationCmd;
        /*! HCI OGF : 0x03 : Controller & Baseband Commands */
        hciSetEventMaskCommand_t                        hciSetEventMaskCmd;
     /* hciResetCommand_t                               hciResetCmd; */                        // No parameters
        hciReadTransmitPowerLevelCommand_t              hciReadTransmitPowerLevelCmd;
        hciSetControllerToHostFlowControlCommand_t      hciSetControllerToHostFlowControlCmd;
        hciHostBufferSizeCommand_t                      hciHostBufferSizeCmd;
        hciHostNumberOfCompletedPacketsCommand_t        hciHostNumberOfCompletedPacketsCmd;
#if (gBLE41_d == TRUE)
#if (gLePingIsSupported_d == TRUE)
        hciSetEventMaskPage2Command_t                   hciSetEventMaskPage2Cmd;
#endif
        hciReadAuthenticatedPayloadTimeoutCommand_t     hciReadAuthenticatedPayloadTimeoutCmd;
        hciWriteAuthenticatedPayloadTimeoutCommand_t    hciWriteAuthenticatedPayloadTimeoutCmd;
#endif /* gBLE41_d */
        /*! HCI OGF : 0x04 : Informational Parameters */
     /* hciReadLocalVersionInfoCommand_t                hciReadLocalVerInfoCmd; */             // No parameters
     /* hciReadLocalSupportedCommandsCommand_t          hciReadLocalSupportedCommandsCmd; */    // No parameters
     /* hciReadLocalSupportedFeaturesCommand_t          hciReadLocalSupportedFeaturesCmd; */    // No parameters
     /* hciReadBufferSizeCommand_t                      hciReadBufferSizeCmd; */               // Only needed for BR/EDR and LE Controllers?
     /* hciReadBdAddrCommand_t                          hciReadBdAddrComm */                    // No parameters
        /*! HCI OGF : 0x05 : Status Parameters */
        hciReadRssiCommand_t                            hciReadRssiCmd;
        /*! HCI OGF : 0x08 : LE Controller Commands */
        hciLeSetEventMaskCommand_t                      hciLeSetEventMaskCmd;
     /* hciLeReadBufferSizeCommand_t                    hciLeReadBuffSizeCmd; */               // No parameters
     /* hciLeReadLocalSupportedFeaturesCommand_t        hciLeReadLocalSupportedFeaturesCmd; */ // No parameters
        hciLeSetRandomAddressCommand_t                  hciLeSetRandomAddressCmd;
        hciLeSetAdvertisingParametersCommand_t          hciLeSetAdvertisingParametersCmd;
     /* hciLeReadAdvertisingChannelTxPowerCommand_t     hciLeReadAdvertisingChannelTxPowerCmd; */  // No parameters
        hciLeSetAdvertisingDataCommand_t                hciLeSetAdvertisingDataCmd;
        hciLeSetScanResponseDataCommand_t               hciLeSetScanResponseDataCmd;
        hciLeSetAdvertiseEnableCommand_t                hciLeSetAdvertiseEnableCmd;
        hciLeSetScanParametersCommand_t                 hciLeSetScanParametersCmd;
        hciLeSetScanEnableCommand_t                     hciLeSetScanEnableCmd;
        hciLeCreateConnectionCommand_t                  hciLeCreateConnectionCmd;
     /* hciLeCreateConnectionCancelCommand_t            hciLeCreateConnectionCancelCmd; */     // No parameters
     /* hciLeReadWhiteListSizeCommand_t                 hciLeReadWhiteListSizeCmd; */          // No parameters
     /* hciLeClearWhiteListCommand_t                    hciLeClearWhiteListCmd; */             // No parameters
        hciLeAddDeviceToWhiteListCommand_t              hciLeAddDeviceToWhiteListCmd;
        hciLeRemoveDeviceFromWhiteListCommand_t         hciLeRemoveDeviceFromWhiteListCmd;
        hciLeConnectionUpdateCommand_t                  hciLeConnectionUpdateCmd;
        hciLeSetHostChannelClassificationCommand_t      hciLeSetHostChannelClassificationCmd;
        hciLeReadChannelMapCommand_t                    hciLeReadChannelMapCmd;
        hciLeReadRemoteUsedFeaturesCommand_t            hciLeReadRemoteUsedFeaturesCmd;
        hciLeEncryptCommand_t                           hciLeEncryptCmd;
     /* hciLeRandCommand_t                              hciLeRandCmd; */                       // No parameters
        hciLeStartEncryptionCommand_t                   hciLeStartEncryptionCmd;
        hciLeLongTermKeyRequestReplyCommand_t           hciLeLongTermKeyRequestReplyCmd;
        hciLeLongTermKeyRequestNegativeReplyCommand_t   hciLeLongTermKeyRequestNegativeReplyCmd;
     /* hciLeReadSupportedStatesCommand_t               hciLeReadSupportedStatesCmd; */        // No parameters
        hciLeReceiverTestCommand_t                      hciLeReceiverTestCmd;
        hciLeTransmitterTestCommand_t                   hciLeTransmitterTestCmd;
     /* hciLeTestEndCommand_t                           hciLeTestEndCmd; */                    // No parameters
#if (gBLE41_d == TRUE)
        hciLeRemoteConnectionParameterRequestReplyCommand_t             hciLeRemoteConnectionParameterRequestReplyCmd;
        hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t     hciLeRemoteConnectionParameterRequestNegativeReplyCmd;
#endif /* gBLE41_d */
    }commData;
} hciCommand_t;

/*! ****************************************************************************
*   DATA PACKETS
***************************************************************************** */

/*! HCI Data Packet Boundary Flag Type */
typedef enum
{
    gBlePBFlagStartNonAutomaticallyFlushableHigherLayerPktMsg_c      = 0x00, /* LE || H2C : Allowed      || C2H : Not Allowed */
    gBlePBFlagContinuingFragmentOfHigherLayerPktMsg_c                = 0x01, /* LE || H2C : Allowed      || C2H : Allowed     */
    gBlePBFlagStartAutomaticallyFlushableHigherLayerPktMsg_c         = 0x02, /* LE || H2C : Not Allowed  || C2H : Allowed     */
    gBlePBFlagCompleteAutomaticallyFlushableHigherLayerPktMsg_c      = 0x03, /* LE || H2C : Not Allowed  || C2H : Not Allowed */
} blePacketBoundaryFlagType_t;

/*! HCI Data Packet Broadcast Flag Type  - Host To Controller */
typedef enum
{
    gBleH2CBFNoBroadcast_c              = 0x00,
    gBleH2CBFActiveSlaveBroadcast_c     = 0x01,
    gBleH2CBFParkedSlaveBroadcast_c     = 0x02,
    gBleH2CBFReserved_c                 = 0x03,
} bleH2CBroadcastFlagType_t;

/*! HCI Data Packet Broadcast Flag Type  - Controller To Host */
typedef enum
{
    gBleC2HBFPointToPoint_c                             = 0x00,
    gBleC2HBFPacketReceivedAsSlaveNotInParkState_c      = 0x01,
    gBleC2HBFPacketReceivedAsSlaveInParkState_c         = 0x02,
    gBleC2HBFReserved_c                                 = 0x03,
} bleC2HBroadcastFlagType_t;

typedef struct hciDataPacket_tag
{
    uint16_t            handle:     12;
    uint16_t            pbFlag:     2;
    uint16_t            bcFlag:     2;
    uint16_t            dataTotalLength;
    uint8_t             data[19];
} hciDataPacket_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Interface callback type definitions
*************************************************************************************
************************************************************************************/
typedef bleResult_t (*hciLeEventCallback_t) (hciLeMetaEvent_t* pEvent);

typedef bleResult_t (*hciCommandCompleteCallback_t) (hciCommandCompleteEvent_t* pEvent);

typedef bleResult_t (*hciCommandStatusCallback_t) (hciCommandStatusEvent_t* pEvent);

typedef bleResult_t (*hciEventCallback_t) (hciEvent_t* pEvent);

typedef bleResult_t (*hciAclDataCallback_t) (uint16_t connectionHandle, void* pPacket);

typedef struct hciInterfaceStruct_tag
{
    /* LE Controller Uplink Interface function pointer */
    hciHostToControllerInterface_t   pHostToController;
}hciInterfaceStruct_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
    extern "C" {
#endif

/* Generic Interface */
bleResult_t Hci_Init(
                hciInterfaceStruct_t* pConfigStruct);

bleResult_t Hci_RegisterLeEventCallback(
                hciLeEventCallback_t pLeCallback);

bleResult_t Hci_RegisterCommandCompleteEventCallback(
                hciCommandCompleteCallback_t pCcCallback);

bleResult_t Hci_RegisterCommandStatusEventCallback(
                hciCommandStatusCallback_t pCsCallback);

bleResult_t Hci_RegisterGenericEventCallback(
                hciEventCallback_t pCallback);

bleResult_t Hci_RegisterL2caCallback(
                hciEventCallback_t      pCallback,
                hciAclDataCallback_t    pAclCallback);

bleResult_t Hci_RegisterSmCallback(
                hciEventCallback_t pSmCallback);


/* Device Setup Group */
bleResult_t Hci_Reset(void);                                                                    /* 3.2 */

/* Controller Flow Control Group */
#if (gHciBrEdrCommandSupport_d == TRUE)
bleResult_t Hci_ReadBufferSize(void);                                                           /* 4.5 */
#endif

bleResult_t Hci_LeReadBufferSize(void);                                                         /* 8.2 */

/* Controller Information Group */
bleResult_t Hci_ReadLocalVersionInformation(void);                                              /* 4.1 */
bleResult_t Hci_ReadLocalSupportedCommands(void);                                               /* 4.2 */
bleResult_t Hci_ReadLocalSupportedFeatures(void);                                               /* 4.3 */
bleResult_t Hci_ReadBdAddr(void);                                                               /* 4.6 */
bleResult_t Hci_LeReadLocalSupportedFeatures(void);                                             /* 8.3 */
bleResult_t Hci_LeReadSupportedStates(void);                                                    /* 8.27 */

#if (gMwsIsSupported_d == TRUE)
bleResult_t Hci_SetMwsChannelParameters(
                hciMwsChannelParametersCommand_t *pParam);                                      /* 3.80 */
bleResult_t Hci_SetExternalFrameConfiguration(
                hciSetExternalFrameConfigurationCommand_t *pParam);                             /* 3.81 */
bleResult_t Hci_SetMwsSignaling(
                hciSetMwsSignalingCommand_t *pParam);                                           /* 3.82 */
bleResult_t Hci_SetMwsTransportLayer(
                hciSetMwsTransportLayerCommand_t *pParam);                                      /* 3.83 */
bleResult_t Hci_GetMwsTransportLayerConfiguration(
                hciGetMwsTransportLayerConfigurationCommand_t *pParam);                         /* 5.11 */
bleResult_t Hci_SetMwsScanFrequencyTable(
                hciSetMwsScanFrequencyTableCommand_t *pParam);                                  /* 3.84 */
bleResult_t Hci_SetMwsPatternConfiguration(
                hciSetMwsPatternConfigurationCommand_t *pParam);                                /* 3.85 */
#endif

/* Controller Configuration Group */
bleResult_t Hci_LeSetAdvertiseEnable(void);                                                     /* 8.9 */
bleResult_t Hci_LeSetAdvertiseDisable(void);                                                    /* 8.9 */
bleResult_t Hci_LeSetAdvertisingData(
                hciLeSetAdvertisingDataCommand_t* pParam);                                      /* 8.7 */
bleResult_t Hci_LeSetAdvertisingParameters(
                hciLeSetAdvertisingParametersCommand_t *pParam);                                /* 8.5 */
bleResult_t Hci_LeSetRandomAddress(
                hciLeSetRandomAddressCommand_t *pParam);                                        /* 8.4 */
bleResult_t Hci_LeSetScanResponseData(
                hciLeSetScanResponseDataCommand_t *pParam);                                     /* 8.8 */

/* Device Discovery Group */
bleResult_t Hci_LeSetScanEnable(hciLeSetScanEnableCommand_t *pParam);                           /* 8.11 */
#if 0
bleResult_t Hci_LeSetScanDisable();                                                             /* 8.11 */
#endif
bleResult_t Hci_LeSetScanParameters(hciLeSetScanParametersCommand_t* pParam);                   /* 8.10 */

/* Connection Setup Group */
bleResult_t Hci_Disconnect(hciDisconnectCommand_t *pParam);                                     /* 1.6 */
bleResult_t Hci_LeCreateConnection(hciLeCreateConnectionCommand_t *pParam);                     /* 8.12 */
bleResult_t Hci_LeCreateConnectionCancel(void);                                                 /* 8.13 */

/* Remote Information Group */
bleResult_t Hci_ReadRemoteVersionInformation(
                hciReadRemoteVersionInformationCommand_t *pParam);                              /* 1.23 */
bleResult_t Hci_LeReadRemoteUsedFeatures(
                hciLeReadRemoteUsedFeaturesCommand_t *pParam);                                  /* 8.21 */

/* Connection State Group */
bleResult_t Hci_LeConnectionUpdate(hciLeConnectionUpdateCommand_t* pParam);                     /* 8.18 */
bleResult_t Hci_LeRemoteConnectionParameterRequestReply(
                hciLeRemoteConnectionParameterRequestReplyCommand_t *pParam);                   /* 8.31 */
bleResult_t Hci_LeRemoteConnectionParameterRequestNegativeReply(
                hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t *pParam);           /* 8.32 */

/* Physical Links Group */
bleResult_t Hci_LeSetHostChannelClassification(
                hciLeSetHostChannelClassificationCommand_t *pParam);                            /* 8.19 */

/* Host Flow Control Group */
bleResult_t Hci_HostBufferSize(
                hciHostBufferSizeCommand_t *pParam);                                            /* 3.39 */
bleResult_t Hci_SetControllerToHostFlowControl(
                hciSetControllerToHostFlowControlCommand_t *pParam);                            /* 3.38 */
bleResult_t Hci_HostNumberOfCompletedPackets(
                hciHostNumberOfCompletedPacketsCommand_t *pParam);                              /* 3.40 */
bleResult_t Hci_SetEventMask(
                hciSetEventMaskCommand_t *pParam);                                              /* 3.1 */
#if (gLePingIsSupported_d == TRUE)
bleResult_t Hci_SetEventMaskPage2(
                hciSetEventMaskPage2Command_t *pParam);                                         /* 3.69 */
#endif
bleResult_t Hci_LeAddDeviceToWhiteList(
                hciLeAddDeviceToWhiteListCommand_t *pParam);                                    /* 8.16 */
bleResult_t Hci_LeClearWhiteList(void);                                                         /* 8.15 */
bleResult_t Hci_LeReadWhiteListSize(void);                                                      /* 8.14 */
bleResult_t Hci_LeRemoveDeviceFromWhiteList(
                hciLeRemoveDeviceFromWhiteListCommand_t *pParam);                               /* 8.17 */
bleResult_t Hci_LeSetEventMask(
                hciLeSetEventMaskCommand_t *pParam);                                            /* 8.1 */

/* Link Information Group */
bleResult_t Hci_ReadTransmitPowerLevel(hciReadTransmitPowerLevelCommand_t *pParam);             /* 3.35 */
bleResult_t Hci_ReadRssi(hciReadRssiCommand_t *pParam);                                         /* 5.4 */
bleResult_t Hci_LeReadAdvertisingChannelTxPower(void);                                          /* 8.6 */
bleResult_t Hci_LeReadChannelMap(hciLeReadChannelMapCommand_t *pParam);                         /* 8.20 */

/* Data Transfer Group */
bleResult_t Hci_SendAclData(
                uint16_t    connectionHandle,
                void*       pPacket,
                uint16_t    packetSize);
bleResult_t Hci_SendAclDataWithSegmentation
    (
        uint16_t    connectionHandle,
        void*       pPacket,
        uint16_t    packetLength
    );

/* Authentication and Encryption Group */
bleResult_t Hci_LeEncrypt(hciLeEncryptCommand_t *pParam);                                       /* 8.22 */
bleResult_t Hci_LeLongTermKeyRequestReply(
                hciLeLongTermKeyRequestReplyCommand_t   *pParam);                               /* 8.25 */
bleResult_t Hci_LeLongTermKeyRequestNegativeReply(
                hciLeLongTermKeyRequestNegativeReplyCommand_t *pParam);                         /* 8.26 */
bleResult_t Hci_LeRand(void);                                                                   /* 8.23 */
bleResult_t Hci_LeStartEncryption(hciLeStartEncryptionCommand_t *pParam);                       /* 8.24 */
#if (gLePingIsSupported_d == TRUE)
bleResult_t Hci_ReadAuthenticatedPayloadTimeout(
                hciReadAuthenticatedPayloadTimeoutCommand_t *pParam);                           /* 3.93 */
bleResult_t Hci_WriteAuthenticatedPayloadTimeout(
                hciWriteAuthenticatedPayloadTimeoutCommand_t *pParam);                          /* 3.94 */
#endif

/* Testing Group */
bleResult_t Hci_LeReceiverTest(hciLeReceiverTestCommand_t *pParam);                             /* 8.28 */
bleResult_t Hci_LeTransmitterTest(hciLeTransmitterTestCommand_t *pParam);                       /* 8.29 */
bleResult_t Hci_LeTestEnd(void);                                                                /* 8.30 */

/* HCI Vendor Specific Commands */
bleResult_t Hci_VendorSpecificDebug(hciVendorSpecificDebugCommand_t *pParam);

#if (gBLE42_d == TRUE)
/* v4.2 specific interface */
bleResult_t Hci_LeSetDataLength(
                hciLeSetDataLengthCommand_t *pParam);                                           /* 8.33 */
bleResult_t Hci_LeReadSuggestedDefaultDataLength(void);                                         /* 8.34 */
bleResult_t Hci_LeWriteSuggestedDefaultDataLength(
                hciLeWriteSuggestedDefaultDataLengthCommand_t *pParam);                         /* 8.35 */
bleResult_t Hci_LeReadLocalP256PublicKey(void);                                                 /* 8.36 */
bleResult_t Hci_LeGenerateDhKey(
                hciLeGenerateDhKeyCommand_t *pParam);                                           /* 8.37 */
bleResult_t Hci_LeAddDeviceToResolvingList(
                hciLeAddDeviceToResolvingListCommand_t *pParam);                                /* 8.38 */
bleResult_t Hci_LeRemoveDeviceFromResolvingList(
                hciLeRemoveDeviceFromResolvingListCommand_t *pParam);                           /* 8.39 */
bleResult_t Hci_LeClearResolvingList(void);                                                     /* 8.40 */
bleResult_t Hci_LeReadResolvingListSize(void);                                                  /* 8.41 */
bleResult_t Hci_LeReadPeerResolvableAddress(
                hciLeReadPeerResolvableAddressCommand_t *pParam);                               /* 8.42 */
bleResult_t Hci_LeReadLocalResolvableAddress(
                hciLeReadLocalResolvableAddressCommand_t *pParam);                              /* 8.43 */
bleResult_t Hci_LeSetAddressResolutionEnable(
                hciLeSetAddressResolutionEnableCommand_t *pParam);                              /* 8.44 */
bleResult_t Hci_LeSetResolvablePrivateAddressTimeout(
                hciLeSetResolvablePrivateAddressTimeoutCommand_t *pParam);                      /* 8.45 */
bleResult_t Hci_LeReadMaximumDataLength(void);                                                  /* 8.46 */
#endif /* gBLE42_d */


#ifdef __cplusplus
    }
#endif 

#endif /* _HCI_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
