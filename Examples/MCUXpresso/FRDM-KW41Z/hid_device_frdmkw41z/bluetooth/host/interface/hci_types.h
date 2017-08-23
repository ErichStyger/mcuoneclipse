/*! *********************************************************************************
* \addtogroup HCI
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

#ifndef _HCI_TYPES_H_
#define _HCI_TYPES_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "vendor_debug_commands.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
    /* Generic constants */
#define gHciLeAdvertisingDataLength_c       (31)
#define gHciLeScanResponseDataLength_c      (31)

#if (gBLE41_d == TRUE)
#define gHciNumLeMetaSubEvents_c            (6)
#elif (gBLE42_d == TRUE)
#define gHciNumLeMetaSubEvents_c            (11)
#endif
#define gHciNumEvents_c                     (9)


/* Hci packets header lengths */
#define gHciCommandPacketHeaderLength_c     (3)
#define gHciAclDataPacketHeaderLength_c     (4)
#define gHciEventPacketHeaderLength_c       (2)

/* Both the Host and the Controller shall support command and event packets, where
the data portion (excluding header) contained in the packets is 500 - header size octets in size. */
#define gHcLeAclDataPacketLengthDefault_c   (500 - gHciAclDataPacketHeaderLength_c)
#define gHcEventPacketLengthDefault_c       (500 - gHciEventPacketHeaderLength_c)

    /*! HCI OGF : 0x01 : Link Control Commands */
#define gHciLinkControlCommands_c                       0x01
        /*! HCI Commands OCF for OGF : 0x01 : Link Control Commands */
#define gHciDisconnect_c                          0x0006
#define gHciReadRemoteVersionInformation_c        0x001D


    /*! HCI OGF : 0x03 : Controller & Baseband Commands */
#define gHciControllerBasebandCommands_c                0x03
        /*! HCI Commands OCF for OGF : 0x03 : Controller & Baseband Commands */
#define gHciSetEventMask_c                        0x0001
#define gHciReset_c                               0x0003
#define gHciReadTransmitPowerLevel_c              0x002D
#define gHciSetControllerToHostFlowControl_c      0x0031
#define gHciHostBufferSize_c                      0x0033
#define gHciHostNumberOfCompletedPackets_c        0x0035
#if (gMwsIsSupported_d == TRUE)
#define gHciSetMwsChannelParameters_c                   0x006E
#define gHciSetExternalFrameConfiguration_c             0x006F
#define gHciSetMwsSignaling_c                           0x0070
#define gHciSetMwsTransportLayer_c                      0x0071
    /* #define gHciGetMwsTransportLayerConfiguration_c */
#define gHciSetMwsScanFrequencyTable_c                  0x0072
#define gHciSetMwsPatternConfiguration_c                0x0073
#endif
#if (gLePingIsSupported_d == TRUE)
#define gHciSetEventMaskPage2_c                   0x0063
#define gHciReadAuthenticatedPayloadTimeout_c     0x007B
#define gHciWriteAuthenticatedPayloadTimeout_c    0x007C
#endif


    /*! HCI OGF : 0x04 : Informational Parameters */
#define gHciInformationalParameters_c                   0x04
        /*! HCI Commands OCF for OGF : 0x04 : Informational Parameters */
#define gHciReadLocalVersionInformation_c         0x0001
#define gHciReadLocalSupportedCommands_c          0x0002
#define gHciReadLocalSupportedFeatures_c          0x0003
#define gHciReadBufferSize_c                      0x0005
#define gHciReadBdAddr_c                          0x0009


    /*! HCI OGF : 0x05 : Status Parameters */
#define gHciStatusParameters_c                          0x05
        /*! HCI Commands OCF for OGF : 0x05 : Status Parameters */
#define gHciReadRssi_c                           0x0005
#if (gMwsIsSupported_d == TRUE)
#define gHciGetMwsTransportLayerConfiguration_c         0x000C
#endif


    /*! HCI OGF : 0x08 : LE Controller Commands */
#define gHciLeControllerCommands_c                      0x08
        /*! HCI Commands OCF for OGF : 0x08 : LE Controller Commands */
#define gHciLeSetEventMask_c                    0x0001
#define gHciLeReadBufferSize_c                  0x0002
#define gHciLeReadLocalSupportedFeatures_c      0x0003
#define gHciLeSetRandomAddress_c                0x0005
#define gHciLeSetAdvertisingParameters_c        0x0006
#define gHciLeReadAdvertisingChannelTxPower_c   0x0007
#define gHciLeSetAdvertisingData_c              0x0008
#define gHciLeSetScanResponseData_c             0x0009
#define gHciLeSetAdvertiseEnable_c              0x000A
#define gHciLeSetScanParameters_c               0x000B
#define gHciLeSetScanEnable_c                   0x000C
#define gHciLeCreateConnection_c                0x000D
#define gHciLeCreateConnectionCancel_c          0x000E
#define gHciLeReadWhiteListSize_c               0x000F
#define gHciLeClearWhiteList_c                  0x0010
#define gHciLeAddDeviceToWhiteList_c            0x0011
#define gHciLeRemoveDeviceFromWhiteList_c       0x0012
#define gHciLeConnectionUpdate_c                0x0013
#define gHciLeSetHostChannelClassification_c    0x0014
#define gHciLeReadChannelMap_c                  0x0015
#define gHciLeReadRemoteUsedFeatures_c          0x0016
#define gHciLeEncrypt_c                         0x0017
#define gHciLeRand_c                            0x0018
#define gHciLeStartEncryption_c                 0x0019
#define gHciLeLongTermKeyRequestReply_c         0x001A
#define gHciLeLongTermKeyRequestNegativeReply_c 0x001B
#define gHciLeReadSupportedStates_c             0x001C
#define gHciLeReceiverTest_c                    0x001D
#define gHciLeTransmitterTest_c                 0x001E
#define gHciLeTestEnd_c                         0x001F
                                                                        
#define gHciLeRemoteConnectionParameterRequestReply_c             0x0020
#define gHciLeRemoteConnectionParameterRequestNegativeReply_c     0x0021

#if (gBLE42_d == TRUE)
/* v4.2 specific interface */
#define gHciLeSetDataLength_c                       0x0022
#define gHciLeReadSuggestedDefaultDataLength_c      0x0023
#define gHciLeWriteSuggestedDefaultDataLength_c     0x0024
#define gHciLeReadLocalP256PublicKey_c              0x0025
#define gHciLeGenerateDhKey_c                       0x0026
#define gHciLeAddDeviceToResolvingList_c            0x0027
#define gHciLeRemoveDeviceFromResolvingList_c       0x0028
#define gHciLeClearResolvingList_c                  0x0029
#define gHciLeReadResolvingListSize_c               0x002A
#define gHciLeReadPeerResolvableAddress_c           0x002B
#define gHciLeReadLocalResolvableAddress_c          0x002C
#define gHciLeSetAddressResolutionEnable_c          0x002D
#define gHciLeSetResolvablePrivateAddressTimeout_c  0x002E
#define gHciLeReadMaximumDataLength_c               0x002F
#endif /* gBLE42_d */

     /*! HCI OGF : 0x3F : Vendor Specific Debug Commands */
#define gHciVendorSpecificDebugCommands_c               0x03F
        /*! HCI Commands OCF for OGF : 0x3F : Vendor Specific Debug Commands */
        /* Will be inherited from "vendor_debug_commands.h" */


    /* Macros used to build full HCI OpCodes */
#define HciCmdOpcode(cmdOgf, cmdOcf)        ((cmdOgf<<SHIFT10) | cmdOcf)
#define HciLeCmdOpcode(leCmdOcf)            (HciCmdOpcode(gHciLeControllerCommands_c, leCmdOcf))
#define HciInfoCmdOpcode(infoCmdOcf)        (HciCmdOpcode(gHciInformationalParameters_c, infoCmdOcf))
#define HciControllerCmdOpcode(ctrlCmdOcf)  (HciCmdOpcode(gHciControllerBasebandCommands_c, ctrlCmdOcf))
#define HciStatusCmdOpcode(statusCmdOcf)    (HciCmdOpcode(gHciStatusParameters_c, statusCmdOcf))

#define BIT(x) (1 << (x))

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
typedef enum
{
    gHciLeScanDisable_c   = 0x00,
    gHciLeScanEnable_c    = 0x01,
} hciLeScanEnable_t;

typedef enum
{
    gHciLeDuplicateFilteringDisable_c    = 0x00,
    gHciLeDuplicateFilteringEnable_c     = 0x01,
} hciLeFilterDuplicates_t;

typedef enum
{
    gLinkLayerEncryptionOff_c    = 0x00,
    gLinkLayerEncryptionOn_c     = 0x01,
} hciLlEncryptionEnabled_t;

typedef union hciCommandOpCode_tag
{
    struct
    {
        uint16_t    ocf:        10;
        uint16_t    ogf:        6;
    };
    uint16_t    opCode;
} hciCommandOpCode_t;

typedef uint8_t hciEventCode_t;
typedef enum
{
    gHciDisconnectionCompleteEvent_c                    = 0x05,
    gHciEncryptionChangeEvent_c                         = 0x08,
    gHciReadRemoteVersionInformationCompleteEvent_c     = 0x0C,
    gHciCommandCompleteEvent_c                          = 0x0E,
    gHciCommandStatusEvent_c                            = 0x0F,
    gHciHardwareErrorEvent_c                            = 0x10,
    gHciNumberOfCompletedPacketsEvent_c                 = 0x13,
    gHciDataBufferOverflowEvent_c                       = 0x1A,
    gHciEncryptionKeyRefreshCompleteEvent_c             = 0x30,
    gHciLeMetaEvent_c                                   = 0x3E,
#if (gBLE41_d == TRUE)
    gHciAuthenticatedPayloadTimeoutExpiredEvent_c       = 0x57,
#endif
} hciEventCode_tag;

typedef uint8_t hciLeMetaSubEventCode_t;
typedef enum
{
    gHciLeConnectionCompleteEvent_c                 = 0x01,
    gHciLeAdvertisingReportEvent_c                  = 0x02,
    gHciLeConnectionUpdateCompleteEvent_c           = 0x03,
    gHciLeReadRemoteUsedFeaturesCompleteEvent_c     = 0x04,
    gHciLeLongTermKeyRequestEvent_c                 = 0x05,
#if (gBLE41_d == TRUE)
    gHciLeRemoteConnectionParameterRequestEvent_c   = 0x06,
#endif
#if (gBLE42_d == TRUE)
    gHciLeDataLengthChangeEvent_c                   = 0x07,
    gHciLeReadLocalP256PublicKeyCompleteEvent_c     = 0x08,
    gHciLeGenerateDhKeyCompleteEvent_c              = 0x09,
    gHciLeEnhancedConnectionCompleteEvent_c         = 0x0A,
    gHciLeDirectAdvertisingReportEvent_c            = 0x0B,
#endif
} hciLeMetaSubEventCode_tag;

typedef uint8_t hciEventMaskShiftsPage1_t;
typedef enum
{
    /* 8 octets - 0x0000000000000000 = No Event Specified */
    gHciEventMaskShiftInuiryComplete_c                           = 0,  /* 0x0000000000000001 */
    gHciEventMaskShiftInuiryResult_c                             = 1,  /* 0x0000000000000002 */
    gHciEventMaskShiftConnectionComplete_c                       = 2,  /* 0x0000000000000004 */
    gHciEventMaskShiftConnectionRequest_c                        = 3,  /* 0x0000000000000008 */
    gHciEventMaskShiftDisconnectionComplete_c                    = 4,  /* 0x0000000000000010 */
    gHciEventMaskShiftAuthenticationComplete_c                   = 5,  /* 0x0000000000000020 */
    gHciEventMaskShiftRemoteNameRequestComplete_c                = 6,  /* 0x0000000000000040 */
    gHciEventMaskShiftEncryptionChange_c                         = 7,  /* 0x0000000000000080 */
    gHciEventMaskShiftChangeConnectionLinkKeyComplete_c          = 8,  /* 0x0000000000000100 */
    gHciEventMaskShiftMasterLinkKeyComplete_c                    = 9,  /* 0x0000000000000200 */
    gHciEventMaskShiftReadRemoteSupportedFeaturesComplete_c      = 10, /* 0x0000000000000400 */
    gHciEventMaskShiftReadRemoteVersionInformationComplete_c     = 11, /* 0x0000000000000800 */
    gHciEventMaskShiftQosSetupComplete_c                         = 12, /* 0x0000000000001000 */
    gHciEventMaskShiftReserved13_c                               = 13, /* 0x0000000000002000 */
    gHciEventMaskShiftReserved14_c                               = 14, /* 0x0000000000004000 */
    gHciEventMaskShiftHardwareError_c                            = 15, /* 0x0000000000008000 */
    gHciEventMaskShiftFlushOccured_c                             = 16, /* 0x0000000000010000 */
    gHciEventMaskShiftRoleChange_c                               = 17, /* 0x0000000000020000 */
    gHciEventMaskShiftReserved18_c                               = 18, /* 0x0000000000040000 */
    gHciEventMaskShiftModeChange_c                               = 19, /* 0x0000000000080000 */
    gHciEventMaskShiftReturnLinkKeys_c                           = 20, /* 0x0000000000100000 */
    gHciEventMaskShiftPinCodeRequest_c                           = 21, /* 0x0000000000200000 */
    gHciEventMaskShiftLinkKeyRequest_c                           = 22, /* 0x0000000000400000 */
    gHciEventMaskShiftLinkKeyNotification_c                      = 23, /* 0x0000000000800000 */
    gHciEventMaskShiftLoopbackCommandn_c                         = 24, /* 0x0000000001000000 */
    gHciEventMaskShiftDataBufferOferflow_c                       = 25, /* 0x0000000002000000 */
    gHciEventMaskShiftMaxSlotsChange_c                           = 26, /* 0x0000000004000000 */
    gHciEventMaskShiftReadClockOffsetComplete_c                  = 27, /* 0x0000000008000000 */
    gHciEventMaskShiftConnectionPacketType_c                     = 28, /* 0x0000000010000000 */
    gHciEventMaskShiftQosViolation_c                             = 29, /* 0x0000000020000000 */
    gHciEventMaskShiftPageScanModeChange_c                       = 30, /* 0x0000000040000000 */ /* Deprecated */
    gHciEventMaskShiftPageScanRepetitionModeChange_c             = 31, /* 0x0000000080000000 */
    gHciEventMaskShiftFlowSpecificationComplete_c                = 32, /* 0x0000000100000000 */
    gHciEventMaskShiftInquiryResultWithRssi_c                    = 33, /* 0x0000000200000000 */
    gHciEventMaskShiftReadRemoteExtendedFeaturesComplete_c       = 34, /* 0x0000000400000000 */
    gHciEventMaskShiftReserved35_c                               = 35, /* 0x0000000800000000 */
    gHciEventMaskShiftReserved36_c                               = 36, /* 0x0000001000000000 */
    gHciEventMaskShiftReserved37_c                               = 37, /* 0x0000002000000000 */
    gHciEventMaskShiftReserved38_c                               = 38, /* 0x0000004000000000 */
    gHciEventMaskShiftReserved39_c                               = 39, /* 0x0000008000000000 */
    gHciEventMaskShiftReserved40_c                               = 40, /* 0x0000010000000000 */
    gHciEventMaskShiftReserved41_c                               = 41, /* 0x0000020000000000 */
    gHciEventMaskShiftReserved42_c                               = 42, /* 0x0000040000000000 */
    gHciEventMaskShiftSynchronousConnectionComplete_c            = 43, /* 0x0000080000000000 */
    gHciEventMaskShiftSynchronousConnectionChanged_c             = 44, /* 0x0000100000000000 */
    gHciEventMaskShiftSniffSubrating_c                           = 45, /* 0x0000200000000000 */
    gHciEventMaskShiftExtendedInquiryResult_c                    = 46, /* 0x0000400000000000 */
    gHciEventMaskShiftEncryptionKeyRefreshComplete_c             = 47, /* 0x0000800000000000 */
    gHciEventMaskShiftIoCapabilityRequest_c                      = 48, /* 0x0001000000000000 */
    gHciEventMaskShiftIoCapabilityRequestReply_c                 = 49, /* 0x0002000000000000 */
    gHciEventMaskShiftUserConfirmationRequest_c                  = 50, /* 0x0004000000000000 */
    gHciEventMaskShiftUserPasskeyRequest_c                       = 51, /* 0x0008000000000000 */
    gHciEventMaskShiftRemoteOobDataRequest_c                     = 52, /* 0x0010000000000000 */
    gHciEventMaskShiftSimplePairingComplete_c                    = 53, /* 0x0020000000000000 */
    gHciEventMaskShiftReserved54_c                               = 54, /* 0x0040000000000000 */
    gHciEventMaskShiftLinkSupervisionTimeoutChanged_c            = 55, /* 0x0080000000000000 */
    gHciEventMaskShiftEnhancedFlushComplete_c                    = 56, /* 0x0100000000000000 */
    gHciEventMaskShiftReserved57_c                               = 57, /* 0x0200000000000000 */
    gHciEventMaskShiftUserPasskeyNotification_c                  = 58, /* 0x0400000000000000 */
    gHciEventMaskShiftKeypressNotification_c                     = 59, /* 0x0800000000000000 */
    gHciEventMaskShiftRemoteHostSupportedFeaturesNotification_c  = 60, /* 0x1000000000000000 */
    gHciEventMaskShiftLeMeta_c                                   = 61, /* 0x2000000000000000 */
} hciEventMaskShiftsPage1_tag;

typedef uint8_t hciEventMaskShiftsPage2_t;
typedef enum
{
    /* 8 octets - 0x0000000000000000 = No Event Specified */
    gHciEventMaskShiftPhysicalCompleteEvent_c                               = 0,  /* 0x0000000000000001 */
    gHciEventMaskShiftChannelSelectedEvent_c                                = 1,  /* 0x0000000000000002 */
    gHciEventMaskShiftDisconnectionPhysicalLinkEvent_c                      = 2,  /* 0x0000000000000004 */
    gHciEventMaskShiftPhysicalLinkLossEarlyWarningEvent_c                   = 3,  /* 0x0000000000000008 */
    gHciEventMaskShiftPhysicalLinkRecoveryEvent_c                           = 4,  /* 0x0000000000000010 */
    gHciEventMaskShiftLogicalLinkCompleteEvent_c                            = 5,  /* 0x0000000000000020 */
    gHciEventMaskShiftDisconnectionLogicalLinkCompleteEvent_c               = 6,  /* 0x0000000000000040 */
    gHciEventMaskShiftFlowSpecModifyCompleteEvent_c                         = 7,  /* 0x0000000000000080 */
    gHciEventMaskShiftNumberOfCompletedDataBlocksEvent_c                    = 8,  /* 0x0000000000000100 */
    gHciEventMaskShiftAmpStartTestEvent_c                                   = 9,  /* 0x0000000000000200 */
    gHciEventMaskShiftAmpTestEndEvent_c                                     = 10, /* 0x0000000000000400 */
    gHciEventMaskShiftAmpReceiverReportEvent_c                              = 11, /* 0x0000000000000800 */
    gHciEventMaskShiftShortRangeModeChangeCompleteEvent_c                   = 12, /* 0x0000000000001000 */
    gHciEventMaskShiftAmpStatusChangeEvent_c                                = 13, /* 0x0000000000002000 */
    gHciEventMaskShiftTriggeredClockCaptureEvent_c                          = 14, /* 0x0000000000004000 */
    gHciEventMaskShiftSynchronizationTrainCompleteEvent_c                   = 15, /* 0x0000000000008000 */
    gHciEventMaskShiftSynchronizationTrainReceivedEvent_c                   = 16, /* 0x0000000000010000 */
    gHciEventMaskShiftConnectionlessSlaveBroadcastReceiveEvent_c            = 17, /* 0x0000000000020000 */
    gHciEventMaskShiftConnectionlessSlaveBroadcastTimeoutEvent_c            = 18, /* 0x0000000000040000 */
    gHciEventMaskShiftTruncatedPageCompleteEvent_c                          = 19, /* 0x0000000000080000 */
    gHciEventMaskShiftSlavePageResponseTimeoutEvent_c                       = 20, /* 0x0000000000100000 */
    gHciEventMaskShiftConnectionlessSlaveBroadcastChannelMapChangeEvent_c   = 21, /* 0x0000000000200000 */
    gHciEventMaskShiftInquiryResponseNotificationEvent_c                    = 22, /* 0x0000000000400000 */
    gHciEventMaskShiftAuthenticatedPayloadTimeoutExpiredEvent_c             = 23, /* 0x0000000000800000 */
} hciEventMaskShiftsPage2_tag;

typedef uint8_t hciLeEventMaskShifts_t;
typedef enum
{
    /* 8 octets - 0x0000000000000000 = No Le Event Specified */
    gHciLeEventMaskShiftLeConnectionCompleteEvent_c                   = 0,  /* 0x0000000000000001 */
    gHciLeEventMaskShiftLeAdvertisingReportEvent_c                    = 1,  /* 0x0000000000000002 */
    gHciLeEventMaskShiftLeConnectionUpdateCompleteEvent_c             = 2,  /* 0x0000000000000004 */
    gHciLeEventMaskShiftLeReadRemoteUsedFeaturesCompleteEvent_c       = 3,  /* 0x0000000000000008 */
    gHciLeEventMaskShiftLeLongTermKeyRequestEvent_c                   = 4,  /* 0x0000000000000010 */
    gHciLeEventMaskShiftLeRemoteConnectionParameterRequestEvent_c     = 5,  /* 0x0000000000000020 */  
} hciLeEventMaskShifts_tag;

typedef uint16_t hciSupportedCommandsShifts_t;
typedef enum
{
    gHciSuppCommShiftInquiry_c                                       =  0 * 8 + 0,
    gHciSuppCommShiftInquiryCancel_c                                 =  0 * 8 + 1,
    gHciSuppCommShiftPeriodicInquiryMode_c                           =  0 * 8 + 2,
    gHciSuppCommShiftExitPeriodicInquiryMode_c                       =  0 * 8 + 3,
    gHciSuppCommShiftCreateConnection_c                              =  0 * 8 + 4,
    gHciSuppCommShiftDisconnect_c                                    =  0 * 8 + 5,
    gHciSuppCommShiftAddScoConnection_c                              =  0 * 8 + 6, /* Deprecated */
    gHciSuppCommShiftCancelCreateConnection_c                        =  0 * 8 + 7,
    gHciSuppCommShiftAcceptConnectionRequest_c                       =  1 * 8 + 0,
    gHciSuppCommShiftRejectConnectionRequest_c                       =  1 * 8 + 1,
    gHciSuppCommShiftLinkKeyRequestReply_c                           =  1 * 8 + 2,
    gHciSuppCommShiftLinkKeyRequestNegativeReply_c                   =  1 * 8 + 3,
    gHciSuppCommShiftPinCodeRequestReply_c                           =  1 * 8 + 4,
    gHciSuppCommShiftPinCodeRequestNegativeReply_c                   =  1 * 8 + 5,
    gHciSuppCommShiftChangeConnectionPacketType_c                    =  1 * 8 + 6,
    gHciSuppCommShiftAuthenticationRequest_c                         =  1 * 8 + 7,
    gHciSuppCommShiftSetConnectionEncryption_c                       =  2 * 8 + 0,
    gHciSuppCommShiftChangeConnectionLinkKey_c                       =  2 * 8 + 1,
    gHciSuppCommShiftMasterLinkKey_c                                 =  2 * 8 + 2,
    gHciSuppCommShiftRemoteNameRequest_c                             =  2 * 8 + 3,
    gHciSuppCommShiftCancelRemoteNameRequest_c                       =  2 * 8 + 4,
    gHciSuppCommShiftReadRemoteSupportedFeatures_c                   =  2 * 8 + 5,
    gHciSuppCommShiftReadRemoteExtendedFeatures_c                    =  2 * 8 + 6,
    gHciSuppCommShiftReadRemoteVersionInformation_c                  =  2 * 8 + 7,
    gHciSuppCommShiftReadClockOffset_c                               =  3 * 8 + 0,
    gHciSuppCommShiftReadLmpHandle_c                                 =  3 * 8 + 1,
    gHciSuppCommShiftReserved032_c                                   =  3 * 8 + 2,
    gHciSuppCommShiftReserved033_c                                   =  3 * 8 + 3,
    gHciSuppCommShiftReserved034_c                                   =  3 * 8 + 4,
    gHciSuppCommShiftReserved035_c                                   =  3 * 8 + 5,
    gHciSuppCommShiftReserved036_c                                   =  3 * 8 + 6,
    gHciSuppCommShiftReserved037_c                                   =  3 * 8 + 7,
    gHciSuppCommShiftReserved040_c                                   =  4 * 8 + 0,
    gHciSuppCommShiftHoldMode_c                                      =  4 * 8 + 1,
    gHciSuppCommShiftSniffMode_c                                     =  4 * 8 + 2,
    gHciSuppCommShiftExitSniffMode_c                                 =  4 * 8 + 3,
    gHciSuppCommShiftParkState_c                                     =  4 * 8 + 4,
    gHciSuppCommShiftExitParkState_c                                 =  4 * 8 + 5,
    gHciSuppCommShiftQosSetup_c                                      =  4 * 8 + 6,
    gHciSuppCommShiftRoleDiscovery_c                                 =  4 * 8 + 7,
    gHciSuppCommShiftSwitchRole_c                                    =  5 * 8 + 0,
    gHciSuppCommShiftReadLinkPolicySettings_c                        =  5 * 8 + 1,
    gHciSuppCommShiftWriteLinkPolicySettings_c                       =  5 * 8 + 2,
    gHciSuppCommShiftReadDefaultLinkPolicySettings_c                 =  5 * 8 + 3,
    gHciSuppCommShiftWriteDefaultLinkPolicySettings_c                =  5 * 8 + 4,
    gHciSuppCommShiftFlowSpecification_c                             =  5 * 8 + 5,
    gHciSuppCommShiftSetEventMark_c                                  =  5 * 8 + 6,
    gHciSuppCommShiftReset_c                                         =  5 * 8 + 7,
    gHciSuppCommShiftSetEventFilter_c                                =  6 * 8 + 0,
    gHciSuppCommShiftFlush_c                                         =  6 * 8 + 1,
    gHciSuppCommShiftReadPinType_c                                   =  6 * 8 + 2,
    gHciSuppCommShiftWritePinType_c                                  =  6 * 8 + 3,
    gHciSuppCommShiftCreateNewUnitKey_c                              =  6 * 8 + 4,
    gHciSuppCommShiftReadStoredLinkKey_c                             =  6 * 8 + 5,
    gHciSuppCommShiftWriteStoredLinkKey_c                            =  6 * 8 + 6,
    gHciSuppCommShiftDeleteStoredLinkKey_c                           =  6 * 8 + 7,
    gHciSuppCommShiftWriteLocalName_c                                =  7 * 8 + 0,
    gHciSuppCommShiftReadLocalName_c                                 =  7 * 8 + 1,
    gHciSuppCommShiftReadConnectionAcceptTimeout_c                   =  7 * 8 + 2,
    gHciSuppCommShiftWriteConnectionAcceptTimeout_c                  =  7 * 8 + 3,
    gHciSuppCommShiftReadPageTimeout_c                               =  7 * 8 + 4,
    gHciSuppCommShiftWritePageTimeout_c                              =  7 * 8 + 5,
    gHciSuppCommShiftReadScanEnable_c                                =  7 * 8 + 6,
    gHciSuppCommShiftWriteScanEnable_c                               =  7 * 8 + 7,
    gHciSuppCommShiftReadPageScanActivity_c                          =  8 * 8 + 0,
    gHciSuppCommShiftWritePageScanActivity_c                         =  8 * 8 + 1,
    gHciSuppCommShiftReadInquiryScanActivity_c                       =  8 * 8 + 2,
    gHciSuppCommShiftWriteInquiryScanActivity_c                      =  8 * 8 + 3,
    gHciSuppCommShiftReadAuthenticationEnable_c                      =  8 * 8 + 4,
    gHciSuppCommShiftWriteAuthenticationEnable_c                     =  8 * 8 + 5,
    gHciSuppCommShiftReadEncryptionMode_c                            =  8 * 8 + 6, /* Deprecated */
    gHciSuppCommShiftWriteEncryptionMode_c                           =  8 * 8 + 7, /* Deprecated */
    gHciSuppCommShiftReadClassOfDevice_c                             =  9 * 8 + 0,
    gHciSuppCommShiftWriteClassOfDevice_c                            =  9 * 8 + 1,
    gHciSuppCommShiftReadVoiceSetting_c                              =  9 * 8 + 2,
    gHciSuppCommShiftWriteVoiceSetting_c                             =  9 * 8 + 3,
    gHciSuppCommShiftReadAutomaticFlushTimeout_c                     =  9 * 8 + 4,
    gHciSuppCommShiftWriteAutomaticFlushTimeout_c                    =  9 * 8 + 5,
    gHciSuppCommShiftReadNumBroadcastRetransmissions_c               =  9 * 8 + 6,
    gHciSuppCommShiftWriteNumBroadcastRetransmissions_c              =  9 * 8 + 7,
    gHciSuppCommShiftReadHoldModeActivity_c                          = 10 * 8 + 0,
    gHciSuppCommShiftWriteHoldModeActivity_c                         = 10 * 8 + 1,
    gHciSuppCommShiftReadTransmitPowerLevel_c                        = 10 * 8 + 2,
    gHciSuppCommShiftReadSynchronousFlowControlEnable_c              = 10 * 8 + 3,
    gHciSuppCommShiftWriteSynchronousFlowControlEnable_c             = 10 * 8 + 4,
    gHciSuppCommShiftSetHostControllerToHostFlowControl_c            = 10 * 8 + 5,
    gHciSuppCommShiftHostBufferSize_c                                = 10 * 8 + 6,
    gHciSuppCommShiftHostNumberOfCompletedPackets_c                  = 10 * 8 + 7,
    gHciSuppCommShiftReadLinkSupervisionTimeout_c                    = 11 * 8 + 0,
    gHciSuppCommShiftWriteLinkSupervisionTimeout_c                   = 11 * 8 + 1,
    gHciSuppCommShiftReadNumberOfSupportedIac_c                      = 11 * 8 + 2,
    gHciSuppCommShiftReadCurrentIacLap_c                             = 11 * 8 + 3,
    gHciSuppCommShiftWriteCurrentIacLap_c                            = 11 * 8 + 4,
    gHciSuppCommShiftReadPageScanModePeriod_c                        = 11 * 8 + 5, /* Deprecated */
    gHciSuppCommShiftWritePageScanModePeriod_c                       = 11 * 8 + 6, /* Deprecated */
    gHciSuppCommShiftReadPageScanMode_c                              = 11 * 8 + 7, /* Deprecated */
    gHciSuppCommShiftWritePageScanMode_c                             = 12 * 8 + 0, /* Deprecated */
    gHciSuppCommShiftSetAfhChannelClassification_c                   = 12 * 8 + 1,
    gHciSuppCommShiftReserved122_c                                   = 12 * 8 + 2,
    gHciSuppCommShiftReserved123_c                                   = 12 * 8 + 3,
    gHciSuppCommShiftReadInquiryScanType_c                           = 12 * 8 + 4,
    gHciSuppCommShiftWriteInquiryScanType_c                          = 12 * 8 + 5,
    gHciSuppCommShiftReadInquiryMode_c                               = 12 * 8 + 6,
    gHciSuppCommShiftWriteInquiryMode_c                              = 12 * 8 + 7,
    gHciSuppCommShiftReadPageScanType_c                              = 13 * 8 + 0,
    gHciSuppCommShiftWritePageScanType_c                             = 13 * 8 + 1,
    gHciSuppCommShiftReadAfhChannelAssessmentMode_c                  = 13 * 8 + 2,
    gHciSuppCommShiftWriteAfhChannelAssessmentMode_c                 = 13 * 8 + 3,
    gHciSuppCommShiftReserved134_c                                   = 13 * 8 + 4,
    gHciSuppCommShiftReserved135_c                                   = 13 * 8 + 5,
    gHciSuppCommShiftReserved136_c                                   = 13 * 8 + 6,
    gHciSuppCommShiftReserved137_c                                   = 13 * 8 + 7,
    gHciSuppCommShiftReserved140_c                                   = 14 * 8 + 0,
    gHciSuppCommShiftReserved141_c                                   = 14 * 8 + 1,
    gHciSuppCommShiftReserved142_c                                   = 14 * 8 + 2,
    gHciSuppCommShiftReadLocalVersionInformation_c                   = 14 * 8 + 3,
    gHciSuppCommShiftReserved144_c                                   = 14 * 8 + 4,
    gHciSuppCommShiftReadLocalSupportedFeatures_c                    = 14 * 8 + 5,
    gHciSuppCommShiftReadLocalExtendedFeatures_c                     = 14 * 8 + 6,
    gHciSuppCommShiftReadBufferSize_c                                = 14 * 8 + 7,
    gHciSuppCommShiftReadCountryCode_c                               = 15 * 8 + 0, /* Deprecated */
    gHciSuppCommShiftReadBdAddr_c                                    = 15 * 8 + 1,
    gHciSuppCommShiftReadFailedContactCount_c                        = 15 * 8 + 2,
    gHciSuppCommShiftResetFailedContactCount_c                       = 15 * 8 + 3,
    gHciSuppCommShiftGetLinkQuality_c                                = 15 * 8 + 4,
    gHciSuppCommShiftReadRssi_c                                      = 15 * 8 + 5,
    gHciSuppCommShiftReadAfhChannelMap_c                             = 15 * 8 + 6,
    gHciSuppCommShiftReadBdClock_c                                   = 15 * 8 + 7,
    gHciSuppCommShiftReadLoopbackMode_c                              = 16 * 8 + 0,
    gHciSuppCommShiftWriteLoopbackMode_c                             = 16 * 8 + 1,
    gHciSuppCommShiftEnableDeviceUnderTestMode_c                     = 16 * 8 + 2,
    gHciSuppCommShiftSetupSynchronousConnection_c                    = 16 * 8 + 3,
    gHciSuppCommShiftAcceptSynchronousConnection_c                   = 16 * 8 + 4,
    gHciSuppCommShiftRejectSynchronousConnection_c                   = 16 * 8 + 5,
    gHciSuppCommShiftReserved166_c                                   = 16 * 8 + 6,
    gHciSuppCommShiftReserved167_c                                   = 16 * 8 + 7,
    gHciSuppCommShiftReadExtendedInquiryResponse_c                   = 17 * 8 + 0,
    gHciSuppCommShiftWriteExtendedInquiryResponse_c                  = 17 * 8 + 1,
    gHciSuppCommShiftRefreshEncryptionKey_c                          = 17 * 8 + 2,
    gHciSuppCommShiftReserved173_c                                   = 17 * 8 + 3,
    gHciSuppCommShiftSniffSubrating_c                                = 17 * 8 + 4,
    gHciSuppCommShiftReadSimplePairingMode_c                         = 17 * 8 + 5,
    gHciSuppCommShiftWriteSimplePairingMode_c                        = 17 * 8 + 6,
    gHciSuppCommShiftReadLocalOobData_c                              = 17 * 8 + 7,
    gHciSuppCommShiftReadInquiryResponseTransmitPower_c              = 18 * 8 + 0,
    gHciSuppCommShiftWriteInquiryTransmitPowerLevel_c                = 18 * 8 + 1,
    gHciSuppCommShiftReadDefaultErroneousDataReporting_c             = 18 * 8 + 2,
    gHciSuppCommShiftWriteDefaultErroneousDataReporting_c            = 18 * 8 + 3,
    gHciSuppCommShiftReserved184_c                                   = 18 * 8 + 4,
    gHciSuppCommShiftReserved185_c                                   = 18 * 8 + 5,
    gHciSuppCommShiftReserved186_c                                   = 18 * 8 + 6,
    gHciSuppCommShiftIoCapabilityRequestReply_c                      = 18 * 8 + 7,
    gHciSuppCommShiftUserConfirmationRequestReply_c                  = 19 * 8 + 0,
    gHciSuppCommShiftUserConfirmationRequestNegativeReply_c          = 19 * 8 + 1,
    gHciSuppCommShiftUserPasskeyRequestReply_c                       = 19 * 8 + 2,
    gHciSuppCommShiftUserPasskeyRequestNegativeReply_c               = 19 * 8 + 3,
    gHciSuppCommShiftRemoteOobDataRequestReply_c                     = 19 * 8 + 4,
    gHciSuppCommShiftWriteSimplePairingDebugMode_c                   = 19 * 8 + 5,
    gHciSuppCommShiftEnhancedFlush_c                                 = 19 * 8 + 6,
    gHciSuppCommShiftRemoteOobDataRequestNegativeReply_c             = 19 * 8 + 7,
    gHciSuppCommShiftReserved200_c                                   = 20 * 8 + 0,
    gHciSuppCommShiftReserved201_c                                   = 20 * 8 + 1,
    gHciSuppCommShiftSendKeypressNotification_c                      = 20 * 8 + 2,
    gHciSuppCommShiftIoCapabilityRequestNegativeReply_c              = 20 * 8 + 3,
    gHciSuppCommShiftReadEncryptionKeySize_c                         = 20 * 8 + 4,
    gHciSuppCommShiftReserved205_c                                   = 20 * 8 + 5,
    gHciSuppCommShiftReserved206_c                                   = 20 * 8 + 6,
    gHciSuppCommShiftReserved207_c                                   = 20 * 8 + 7,
    gHciSuppCommShiftCreatePhysicalLink_c                            = 21 * 8 + 0,
    gHciSuppCommShiftAcceptPhysicalLink_c                            = 21 * 8 + 1,
    gHciSuppCommShiftDisconnectPhysicalLink_c                        = 21 * 8 + 2,
    gHciSuppCommShiftCreateLogicalLink_c                             = 21 * 8 + 3,
    gHciSuppCommShiftAcceptLogicalLink_c                             = 21 * 8 + 4,
    gHciSuppCommShiftDisconnectLogicalLink_c                         = 21 * 8 + 5,
    gHciSuppCommShiftLogicalLinkCancel_c                             = 21 * 8 + 6,
    gHciSuppCommShiftFlowSpecModify_c                                = 21 * 8 + 7,
    gHciSuppCommShiftReadLogicalLinkAcceptTimeout_c                  = 22 * 8 + 0,
    gHciSuppCommShiftWriteLogicalLinkAcceptTimeout_c                 = 22 * 8 + 1,
    gHciSuppCommShiftSetEventMaskPage2_c                             = 22 * 8 + 2,
    gHciSuppCommShiftReadLocationData_c                              = 22 * 8 + 3,
    gHciSuppCommShiftWriteLocationData_c                             = 22 * 8 + 4,
    gHciSuppCommShiftReadLocalAmpInfo_c                              = 22 * 8 + 5,
    gHciSuppCommShiftReadLocalAmp_assoc_c                            = 22 * 8 + 6,
    gHciSuppCommShiftWriteRemoteAmp_assoc_c                          = 22 * 8 + 7,
    gHciSuppCommShiftReadFlowControlMode_c                           = 23 * 8 + 0,
    gHciSuppCommShiftWriteFlowControlMode_c                          = 23 * 8 + 1,
    gHciSuppCommShiftReadDataBlockSize_c                             = 23 * 8 + 2,
    gHciSuppCommShiftReserved233_c                                   = 23 * 8 + 3,
    gHciSuppCommShiftReserved234_c                                   = 23 * 8 + 4,
    gHciSuppCommShiftEnableAmpReceiverReports_c                      = 23 * 8 + 5,
    gHciSuppCommShiftAmpTestEnd_c                                    = 23 * 8 + 6,
    gHciSuppCommShiftAmpTestCommand_c                                = 23 * 8 + 7,
    gHciSuppCommShiftReadEnhancedTransmitPowerLevel_c                = 24 * 8 + 0,
    gHciSuppCommShiftReserved241_c                                   = 24 * 8 + 1,
    gHciSuppCommShiftReadBestEffortFlushTimeout_c                    = 24 * 8 + 2,
    gHciSuppCommShiftWriteBestEffortFlushTimeout_c                   = 24 * 8 + 3,
    gHciSuppCommShiftShortRangeMode_c                                = 24 * 8 + 4,
    gHciSuppCommShiftReadLeHostSupport_c                             = 24 * 8 + 5,
    gHciSuppCommShiftWriteLeHostSupport_c                            = 24 * 8 + 6,
    gHciSuppCommShiftReserved247_c                                   = 24 * 8 + 7,
    gHciSuppCommShiftLeSetEventMask_c                                = 25 * 8 + 0,
    gHciSuppCommShiftLeReadBufferSize_c                              = 25 * 8 + 1,
    gHciSuppCommShiftLeReadLocalSupportedFeatures_c                  = 25 * 8 + 2,
    gHciSuppCommShiftReserved253_c                                   = 25 * 8 + 3,
    gHciSuppCommShiftLeSetRandomAddress_c                            = 25 * 8 + 4,
    gHciSuppCommShiftLeSetAdvertisingParameters_c                    = 25 * 8 + 5,
    gHciSuppCommShiftLeReadAdvertisingChannelTxPower_c               = 25 * 8 + 6,
    gHciSuppCommShiftLeSetAdvertisingData_c                          = 25 * 8 + 7,
    gHciSuppCommShiftLeSetScanResponseData_c                         = 26 * 8 + 0,
    gHciSuppCommShiftLeSetAdvertiseEnable_c                          = 26 * 8 + 1,
    gHciSuppCommShiftLeSetScanParameters_c                           = 26 * 8 + 2,
    gHciSuppCommShiftLeSetScanEnable_c                               = 26 * 8 + 3,
    gHciSuppCommShiftLeCreateConnection_c                            = 26 * 8 + 4,
    gHciSuppCommShiftLeCreateConnectionCancel_c                      = 26 * 8 + 5,
    gHciSuppCommShiftLeReadWhiteListSize_c                           = 26 * 8 + 6,
    gHciSuppCommShiftLeClearWhiteList_c                              = 26 * 8 + 7,
    gHciSuppCommShiftLeAddDeviceToWhiteList_c                        = 27 * 8 + 0,
    gHciSuppCommShiftLeRemoveDeviceFromWhiteList_c                   = 27 * 8 + 1,
    gHciSuppCommShiftLeConnectionUpdate_c                            = 27 * 8 + 2,
    gHciSuppCommShiftLeSetHostChannelClassification_c                = 27 * 8 + 3,
    gHciSuppCommShiftLeReadChannelMap_c                              = 27 * 8 + 4,
    gHciSuppCommShiftLeReadRemoteUsedFeatures_c                      = 27 * 8 + 5,
    gHciSuppCommShiftLeEncrypt_c                                     = 27 * 8 + 6,
    gHciSuppCommShiftLeRand_c                                        = 27 * 8 + 7,
    gHciSuppCommShiftLeStartEncryption_c                             = 28 * 8 + 0,
    gHciSuppCommShiftLeLongTermKeyRequestReply_c                     = 28 * 8 + 1,
    gHciSuppCommShiftLeLongTermKeyRequestedNegativeReply_c           = 28 * 8 + 2,
    gHciSuppCommShiftLeReadSupportedStates_c                         = 28 * 8 + 3,
    gHciSuppCommShiftLeReceiverTest_c                                = 28 * 8 + 4,
    gHciSuppCommShiftLeTransmitterTest_c                             = 28 * 8 + 5,
    gHciSuppCommShiftLeTestEnd_c                                     = 28 * 8 + 6,
    gHciSuppCommShiftReserved287_c                                   = 28 * 8 + 7,
    gHciSuppCommShiftReserved290_c                                   = 29 * 8 + 0,
    gHciSuppCommShiftReserved291_c                                   = 29 * 8 + 1,
    gHciSuppCommShiftReserved292_c                                   = 29 * 8 + 2,
    gHciSuppCommShiftEnhancedSetupSynchronousConnection_c            = 29 * 8 + 3,
    gHciSuppCommShiftEnhancedAcceptSynchronousConnection_c           = 29 * 8 + 4,
    gHciSuppCommShiftReadLocalSupportedCodecs_c                      = 29 * 8 + 5,
    gHciSuppCommShiftSetMwsChannelParametersCommand_c                = 29 * 8 + 6,
    gHciSuppCommShiftSetExternalFrameConfigurationCommand_c          = 29 * 8 + 7,
    gHciSuppCommShiftSetMwsSignalingCommand_c                        = 30 * 8 + 0,
    gHciSuppCommShiftSetTransportLayerCommand_c                      = 30 * 8 + 1,
    gHciSuppCommShiftSetMwsScanFrequencyTableCommand_c               = 30 * 8 + 2,
    gHciSuppCommShiftGetTransportLayerConfigurationCommand_c         = 30 * 8 + 3,
    gHciSuppCommShiftSetMwsPatternConfigurationCommand_c             = 30 * 8 + 4,
    gHciSuppCommShiftSetTriggeredClockCapture_c                      = 30 * 8 + 5,
    gHciSuppCommShiftTruncatedPage_c                                 = 30 * 8 + 6,
    gHciSuppCommShiftTruncatedPageCancel_c                           = 30 * 8 + 7,
    gHciSuppCommShiftSetConnectionlessSlaveBroadcast_c               = 31 * 8 + 0,
    gHciSuppCommShiftSetConnectionlessSlaveBroadcastReceive_c        = 31 * 8 + 1,
    gHciSuppCommShiftStartSynchronizationTrain_c                     = 31 * 8 + 2,
    gHciSuppCommShiftReceiveSynchronizationTrain_c                   = 31 * 8 + 3,
    gHciSuppCommShiftSetReservedLt_addr314_c                         = 31 * 8 + 4,
    gHciSuppCommShiftDeleteReservedLt_addr315_c                      = 31 * 8 + 5,
    gHciSuppCommShiftSetConnectionlessSlaveBroadcastData_c           = 31 * 8 + 6,
    gHciSuppCommShiftReadSynchronizationTrainParameters_c            = 31 * 8 + 7,
    gHciSuppCommShiftWriteSynchronizationTrainParameters_c           = 32 * 8 + 0,
    gHciSuppCommShiftRemoteOobExtendedDataRequestReply_c             = 32 * 8 + 1,
    gHciSuppCommShiftReadSecureConnectionsHostSupport_c              = 32 * 8 + 2,
    gHciSuppCommShiftWriteSecureConnectionsHostSupport_c             = 32 * 8 + 3,
    gHciSuppCommShiftReadAuthenticatedPayloadTimeout_c               = 32 * 8 + 4,
    gHciSuppCommShiftWriteAuthenticatedPayloadTimeout_c              = 32 * 8 + 5,
    gHciSuppCommShiftReadLocalOobExtendedData_c                      = 32 * 8 + 6,
    gHciSuppCommShiftWriteSecureConnectionsTestMode_c                = 32 * 8 + 7,
    gHciSuppCommShiftReadExtendedPageTimeout_c                       = 33 * 8 + 0,
    gHciSuppCommShiftWriteExtendedPageTimeout_c                      = 33 * 8 + 1,
    gHciSuppCommShiftReadExtendedInquiryLength_c                     = 33 * 8 + 2,
    gHciSuppCommShiftWriteExtendedInquiryLength_c                    = 33 * 8 + 3,
    gHciSuppCommShiftLeRemoteConnectionParameterRequestReplyCommand_c            = 33 * 8 + 4,
    gHciSuppCommShiftLeRemoteConnectionParameterRequestNegativeReplyCommand_c    = 33 * 8 + 5,
    gHciSuppCommShiftReserved336_c                                   = 33 * 8 + 6,
    gHciSuppCommShiftReserved337_c                                   = 33 * 8 + 7,
} hciSupportedCommandsShifts_tag;

typedef uint16_t hciLocalSupportedFeaturesShifts_t;
typedef enum
{
    gHciLocSuppFeatShift3SlotPackets_c                               =  0 * 8 + 0, /* 0*/ 
    gHciLocSuppFeatShift5SlotPackets_c                               =  0 * 8 + 1, /* 1*/ 
    gHciLocSuppFeatShiftEncryption_c                                 =  0 * 8 + 2, /* 2*/ 
    gHciLocSuppFeatShiftSlotOffset_c                                 =  0 * 8 + 3, /* 3*/ 
    gHciLocSuppFeatShiftTimingAccuracy_c                             =  0 * 8 + 4, /* 4*/ 
    gHciLocSuppFeatShiftRoleSwitch_c                                 =  0 * 8 + 5, /* 5*/ 
    gHciLocSuppFeatShiftHoldMode_c                                   =  0 * 8 + 6, /* 6*/ 
    gHciLocSuppFeatShiftSniffMode_c                                  =  0 * 8 + 7, /* 7*/ 
    gHciLocSuppFeatShiftParkState_c                                  =  1 * 8 + 0, /* 8*/ 
    gHciLocSuppFeatShiftPowerControlRequests_c                       =  1 * 8 + 1, /* 9*/ 
    gHciLocSuppFeatShiftChannelQualityDrivenDataRateCqddr_c          =  1 * 8 + 2, /* 10*/ 
    gHciLocSuppFeatShiftScoLink_c                                    =  1 * 8 + 3, /* 11*/ 
    gHciLocSuppFeatShiftHv2Packets_c                                 =  1 * 8 + 4, /* 12*/ 
    gHciLocSuppFeatShiftHv3Packets_c                                 =  1 * 8 + 5, /* 13*/ 
    gHciLocSuppFeatShiftUlawLogSynchronousData_c                     =  1 * 8 + 6, /* 14*/ 
    gHciLocSuppFeatShiftAlawLogSynchronousData_c                     =  1 * 8 + 7, /* 15*/ 
    gHciLocSuppFeatShiftCvsdSynchronousData_c                        =  2 * 8 + 0, /* 16*/ 
    gHciLocSuppFeatShiftPagingParameterNegotiation_c                 =  2 * 8 + 1, /* 17*/ 
    gHciLocSuppFeatShiftPowerControl_c                               =  2 * 8 + 2, /* 18*/ 
    gHciLocSuppFeatShiftTransparentSynchronousData_c                 =  2 * 8 + 3, /* 19*/ 
    gHciLocSuppFeatShiftFlowControlLagLSBit_c                        =  2 * 8 + 4, /* 20*/ 
    gHciLocSuppFeatShiftFlowControlLagMiddleBit_c                    =  2 * 8 + 5, /* 21*/ 
    gHciLocSuppFeatShiftFlowControlLagMSBit_c                        =  2 * 8 + 6, /* 22*/ 
    gHciLocSuppFeatShiftBroadcastEncryption_c                        =  2 * 8 + 7, /* 23*/ 
    gHciLocSuppFeatShiftReserved30_c                                 =  3 * 8 + 0, /* 24*/ 
    gHciLocSuppFeatShiftEnhancedDataRateAcl2MbpsMode_c               =  3 * 8 + 1, /* 25*/ 
    gHciLocSuppFeatShiftEnhancedDataRateAcl3MbpsMode_c               =  3 * 8 + 2, /* 26*/ 
    gHciLocSuppFeatShiftEnhancedInquiryScan_c                        =  3 * 8 + 3, /* 27*/ 
    gHciLocSuppFeatShiftInterlacedInquiryScan_c                      =  3 * 8 + 4, /* 28*/ 
    gHciLocSuppFeatShiftInterlacedPageScan_c                         =  3 * 8 + 5, /* 29*/ 
    gHciLocSuppFeatShiftRssiWithInquiryResults_c                     =  3 * 8 + 6, /* 30*/ 
    gHciLocSuppFeatShiftExtendedScoLinkEv3Packets_c                  =  3 * 8 + 7, /* 31*/ 
    gHciLocSuppFeatShiftEv4Packets_c                                 =  4 * 8 + 0, /* 32*/ 
    gHciLocSuppFeatShiftEv5Packets_c                                 =  4 * 8 + 1, /* 33*/ 
    gHciLocSuppFeatShiftReserved42_c                                 =  4 * 8 + 2, /* 34*/ 
    gHciLocSuppFeatShiftAfhCapableSlave_c                            =  4 * 8 + 3, /* 35*/ 
    gHciLocSuppFeatShiftAfhClassificationSlave_c                     =  4 * 8 + 4, /* 36*/ 
    gHciLocSuppFeatShiftBrEdrNotSupported_c                          =  4 * 8 + 5, /* 37*/ 
    gHciLocSuppFeatShiftLeSupportedController_c                      =  4 * 8 + 6, /* 38*/ 
    gHciLocSuppFeatShift3SlotEnhancedDataRateAclPackets_c            =  4 * 8 + 7, /* 39*/ 
    gHciLocSuppFeatShift5SlotEnhancedDataRateAclPackets_c            =  5 * 8 + 0, /* 40*/ 
    gHciLocSuppFeatShiftSniffSubrating_c                             =  5 * 8 + 1, /* 41*/ 
    gHciLocSuppFeatShiftPauseEncryption_c                            =  5 * 8 + 2, /* 42*/ 
    gHciLocSuppFeatShiftAfhCapableMaster_c                           =  5 * 8 + 3, /* 43*/ 
    gHciLocSuppFeatShiftAfhClassificationMaster_c                    =  5 * 8 + 4, /* 44*/ 
    gHciLocSuppFeatShiftEnhancedDataRateEsco2MbpsMode_c              =  5 * 8 + 5, /* 45*/ 
    gHciLocSuppFeatShiftEnhancedDataRateEsco3MbpsMode_c              =  5 * 8 + 6, /* 46*/ 
    gHciLocSuppFeatShift3SlotEnhancedDataRateEscoPackets_c           =  5 * 8 + 7, /* 47*/ 
    gHciLocSuppFeatShiftExtendedInquiryResponse_c                    =  6 * 8 + 0, /* 48*/ 
    gHciLocSuppFeatShiftSimultaneousLeAndBrEdrToSameDeviceCapableController_c    =  6 * 8 + 1, /* 49*/ 
    gHciLocSuppFeatShiftReserved62_c                                 =  6 * 8 + 2, /* 50*/ 
    gHciLocSuppFeatShiftSecureSimplePairing_c                        =  6 * 8 + 3, /* 51*/ 
    gHciLocSuppFeatShiftEncapsulatedPdu_c                            =  6 * 8 + 4, /* 52*/ 
    gHciLocSuppFeatShiftErroneousDataReporting_c                     =  6 * 8 + 5, /* 53*/ 
    gHciLocSuppFeatShiftNonFlushablePacketBoundaryFlag_c             =  6 * 8 + 6, /* 54*/ 
    gHciLocSuppFeatShiftReserved67_c                                 =  6 * 8 + 7, /* 55*/ 
    gHciLocSuppFeatShiftLinkSupervisionTimeoutChangedEvent_c         =  7 * 8 + 0, /* 56*/ 
    gHciLocSuppFeatShiftInquiryTxPowerLevel_c                        =  7 * 8 + 1, /* 57*/ 
    gHciLocSuppFeatShiftEnhancedPowerControl_c                       =  7 * 8 + 2, /* 58*/ 
    gHciLocSuppFeatShiftReserved73_c                                 =  7 * 8 + 3, /* 59*/ 
    gHciLocSuppFeatShiftReserved74_c                                 =  7 * 8 + 4, /* 60*/ 
    gHciLocSuppFeatShiftReserved75_c                                 =  7 * 8 + 5, /* 61*/ 
    gHciLocSuppFeatShiftReserved76_c                                 =  7 * 8 + 6, /* 62*/ 
    gHciLocSuppFeatShiftExtendedFeatures_c                           =  7 * 8 + 7, /* 63*/ 
} hciLocalSupportedFeaturesShifts_tag; /* Page 0 */

typedef uint32_t hciLeSupportedFeatures_t;
typedef enum
{
    gHciLeEncryption_c                            = BIT(0 * 8 + 0), /* 0 */
    gHciConnectionParametersRequestProcedure_c    = BIT(0 * 8 + 1), /* 1 */
    gHciExtendedRejectIndication_c                = BIT(0 * 8 + 2), /* 2 */
    gHciSlaveInitiatedFeaturesExchange_c          = BIT(0 * 8 + 3), /* 3 */
    gHciLePing_c                                  = BIT(0 * 8 + 4), /* 4 */
#if (gBLE42_d == TRUE)
    gHciLeDataPacketLengthExtension_c             = BIT(0 * 8 + 5), /* 5 */
    gHciLlPrivacy_c                               = BIT(0 * 8 + 6), /* 6 */
    gHciExtendedScannerFilterPolicies_c           = BIT(0 * 8 + 7), /* 7 */
#endif
} hciLeSupportedFeatures_tag;

typedef uint16_t hciLeLLSupportedStateFlags_t;
typedef enum
{
    gHciLeLLSuppStateFlagsReserved_c                                = 0,
    gHciLeLLSuppStateFlagsSlaveConnection_c                         = BIT(0),
    gHciLeLLSuppStateFlagsMasterConnection_c                        = BIT(1),
    gHciLeLLSuppStateFlagsInitiating_c                              = BIT(2),
    gHciLeLLSuppStateFlagsPassiveScanning_c                         = BIT(3),
    gHciLeLLSuppStateFlagsActiveScanning_c                          = BIT(4),
    gHciLeLLSuppStateFlagsLowDutyCycleDirectedAdvertising_c         = BIT(5),
    gHciLeLLSuppStateFlagsHighDutyCycleDirectedAdvertising_c        = BIT(6),
    gHciLeLLSuppStateFlagsNonconnectableAdvertising_c               = BIT(7),
    gHciLeLLSuppStateFlagsConnectableAdvertising_c                  = BIT(8),
    gHciLeLLSuppStateFlagsScannableAdvertising_c                    = BIT(9),
    gHciLeLLSuppStateFlagsMasterAndMaster_c                         = BIT(10),
    gHciLeLLSuppStateFlagsMasterAndSlave_c                          = BIT(11),
    gHciLeLLSuppStateFlagsSlaveAndSlave_c                           = BIT(12)
} hciLeLLSupportedStateFlags_tag;

typedef uint8_t hciLeAdvertiseEnable_t;
typedef enum
{
    gHciLeAdvertisingDisable_c   = 0x00,
    gHciLeAdvertisingEnable_c    = 0x01,
} hciLeAdvertiseEnable_tag;

typedef uint8_t hciControllerToHostFlowControlEnable_t;
typedef enum
{
    gHciFlowControlOffAclPacketsOffHciSyncPackets_c  = 0x00,
    gHciFlowControlOnAclPacketsOffHciSyncPackets_c   = 0x01,
    gHciFlowControlOffAclPacketsOnHciSyncPackets_c   = 0x02,
    gHciFlowControlOnAclPacketsOnHciSyncPackets_c    = 0x03,
} hciControllerToHostFlowControlEnable_tag;

typedef uint8_t hciDataBufferOverflowLinkType_t;
typedef enum
{
    gHciDataBufferOverflowSynchronous_c  = 0x00,
    gHciDataBufferOverflowACL_c          = 0x01,
} hciDataBufferOverflowLinkType_tag;

#if (gMwsIsSupported_d == TRUE)
typedef uint8_t mwsChannelEnable_t;
typedef enum
{
    gMwsChannelDisabled_c               = 0x00,
    gMwsChannelEnabled_c                = 0x01
}mwsChannelEnable_tag;

typedef uint8_t periodType_t;
typedef enum
{
    gDownlink_c              = 0x00,
    gUplink_c                = 0x01,
    gBiDirectional_c         = 0x02,
    gGuardPeriod_c           = 0x03,
}periodType_tag;
#endif

typedef PACKED_STRUCT hciCommandPacket_tag
{
    uint16_t    opCode;
    uint8_t     parameterTotalLength;
    uint8_t     aData[0];
}hciCommandPacket_t;

typedef PACKED_STRUCT hciAclDataPacket_tag
{
    uint16_t    handle      :12;
    uint16_t    pbFlag      :2;
    uint16_t    bcFlag      :2;
    uint16_t    dataTotalLength;
    uint8_t     aData[0];
}hciAclDataPacket_t;

typedef PACKED_STRUCT hciEventPacket_tag
{
    hciEventCode_t  eventCode;
    uint8_t     dataTotalLength;
    uint8_t     aData[0];
}hciEventPacket_t;

typedef bleResult_t hciErrorCode_t;
    
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#endif /* _HCI_TYPES_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
