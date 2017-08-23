/*! *********************************************************************************
 * \defgroup BLE BLE General Definitions
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_general.h
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

#ifndef _BLE_GENERAL_H_
#define _BLE_GENERAL_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>

#include "EmbeddedTypes.h"
#include "FunctionLib.h"
#include "fsl_os_abstraction.h"
    
#include "ble_constants.h"
#include "ble_utils.h"

#include "ble_sig_defines.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

#define gInvalidDeviceId_c                          (0xFF)

/*! Boundary values for the Connection Parameters (Standard GAP). */
#define gcConnectionIntervalMin_c                   (0x0006)
#define gcConnectionIntervalMax_c                   (0x0C80)
#define gcConnectionSlaveLatencyMax_c               (0x01F3)
#define gcConnectionSupervisionTimeoutMin_c         (0x000A)
#define gcConnectionSupervisionTimeoutMax_c         (0x0C80)

/*! Default values for the Connection Parameters (Preferred). */

/*! connIntervalmin = Conn_Interval_Min * 1.25 ms */
/*! Value of 0xFFFF indicates no specific minimum. */
#ifndef gcConnectionIntervalMinDefault_c
#define gcConnectionIntervalMinDefault_c            (40)
#endif

/*! connIntervalmax = Conn_Interval_Max * 1.25 ms */
/*! Value of 0xFFFF indicates no specific maximum. */
#ifndef gcConnectionIntervalMaxDefault_c
#define gcConnectionIntervalMaxDefault_c            (160)
#endif

#ifndef gcConnectionSlaveLatencyDefault_c
#define gcConnectionSlaveLatencyDefault_c           (0)
#endif

/*! Time = N * 10 ms */
#ifndef gcConnectionSupervisionTimeoutDefault_c
#define gcConnectionSupervisionTimeoutDefault_c     (2000)
#endif

/*! Time = N * 0.625 ms */
#ifndef gcConnectionEventMinDefault_c
#define gcConnectionEventMinDefault_c               (0)
#endif

/*! Time = N * 0.625 ms */
#ifndef gcConnectionEventMaxDefault_c
#define gcConnectionEventMaxDefault_c               (0)
#endif

/*
 *
 * Device addresses may be:
 *
 * -> public
 * -> random -> static
 *           -> private -> resolvable
 *                      -> non-resolvable
 *
 */

/*! PRA condition: check the 6th byte - MSB should be 0; 2nd MSB should be 1. */
#define Ble_IsPrivateResolvableDeviceAddress(bleAddress)  \
    ( (bleAddress[5] & (BIT7|BIT6)) == BIT6 )

/*! PNRA condition: check the 6th byte - MSB should be 0; 2nd MSB should be 0. */
#define Ble_IsPrivateNonresolvableDeviceAddress(bleAddress)  \
    ( (bleAddress[5] & (BIT7|BIT6)) == 0 )

/*! RSA condition: check the 6th byte - MSB should be 1; 2nd MSB should be 1. */
#define Ble_IsRandomStaticDeviceAddress(bleAddress)  \
    ( (bleAddress[5] & (BIT7|BIT6)) == (BIT7|BIT6) )

/*! A macro used to compare two device addresses */
#define Ble_DeviceAddressesMatch(bleAddress1, bleAddress2) \
    ( (bleAddress1)[0] == (bleAddress2)[0] \
    && (bleAddress1)[1] == (bleAddress2)[1] \
    && (bleAddress1)[2] == (bleAddress2)[2] \
    && (bleAddress1)[3] == (bleAddress2)[3] \
    && (bleAddress1)[4] == (bleAddress2)[4] \
    && (bleAddress1)[5] == (bleAddress2)[5] )

/*! A macro used to copy device addresses */
#define Ble_CopyDeviceAddress(destinationAddress, sourceAddress) \
    { for (uint8_t j = 0; j < gcBleDeviceAddressSize_c; j++) { destinationAddress[j] = sourceAddress[j]; } }

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
/*! BLE result type - the return value of BLE API functions */ 
typedef enum
{
    /*
    *
    * Generic result values, base = 0x0000 
    *
    */

    gBleStatusBase_c = 0x0000,                                                              /*!< General status base. */
    gBleSuccess_c                                               = gBleStatusBase_c | 0x00,  /*!< Function executed successfully. */

    gBleInvalidParameter_c                                      = gBleStatusBase_c | 0x01,  /*!< Parameter has an invalid value or is outside the accepted range. */
    gBleOverflow_c                                              = gBleStatusBase_c | 0x02,  /*!< An internal limit is reached. */
    gBleUnavailable_c                                           = gBleStatusBase_c | 0x03,  /*!< A requested parameter is not available. */
    gBleFeatureNotSupported_c                                   = gBleStatusBase_c | 0x04,  /*!< The requested feature is not supported by this stack version. */
    gBleOutOfMemory_c                                           = gBleStatusBase_c | 0x05,  /*!< An internal memory allocation failed. */
    gBleAlreadyInitialized_c                                    = gBleStatusBase_c | 0x06,  /*!< Ble_HostInitialize function is incorrectly called a second time. */
    gBleOsError_c                                               = gBleStatusBase_c | 0x07,  /*!< An error occurred at the OS level. */
    gBleUnexpectedError_c                                       = gBleStatusBase_c | 0x08,  /*!< A "should never get here"-type error occurred. */
    gBleInvalidState_c                                          = gBleStatusBase_c | 0x09,  /*!< The requested API cannot be called in the current state. */

    /*
    *
    * HCI result values 
    *
    */

    gHciStatusBase_c = 0x0100,
    gHciSuccess_c                                               = gBleSuccess_c,
    /* HCI standard status codes */
    gHciUnknownHciCommand_c                                     = gHciStatusBase_c | 0x01,
    gHciUnknownConnectionIdentifier_c                           = gHciStatusBase_c | 0x02,
    gHciHardwareFailure_c                                       = gHciStatusBase_c | 0x03,
    gHciPageTimeout_c                                           = gHciStatusBase_c | 0x04,
    gHciAuthenticationFailure_c                                 = gHciStatusBase_c | 0x05,
    gHciPinOrKeyMissing_c                                       = gHciStatusBase_c | 0x06,
    gHciMemoryCapacityExceeded_c                                = gHciStatusBase_c | 0x07,
    gHciConnectionTimeout_c                                     = gHciStatusBase_c | 0x08,
    gHciConnectionLimitExceeded_c                               = gHciStatusBase_c | 0x09,
    gHciSynchronousConnectionLimitToADeviceExceeded_c           = gHciStatusBase_c | 0x0A,
    gHciAclConnectionAlreadyExists_c                            = gHciStatusBase_c | 0x0B,
    gHciCommandDisallowed_c                                     = gHciStatusBase_c | 0x0C,
    gHciConnectionRejectedDueToLimitedResources_c               = gHciStatusBase_c | 0x0D,
    gHciConnectionRejectedDueToSecurityReasons_c                = gHciStatusBase_c | 0x0E,
    gHciConnectionRejectedDueToUnacceptableBdAddr_c             = gHciStatusBase_c | 0x0F,
    gHciConnectionAcceptTimeoutExceeded_c                       = gHciStatusBase_c | 0x10,
    gHciUnsupportedFeatureOrParameterValue_c                    = gHciStatusBase_c | 0x11,
    gHciInvalidHciCommandParameters_c                           = gHciStatusBase_c | 0x12,
    gHciRemoteUserTerminatedConnection_c                        = gHciStatusBase_c | 0x13,
    gHciRemoteDeviceTerminatedConnectionLowResources_c          = gHciStatusBase_c | 0x14,
    gHciRemoteDeviceTerminatedConnectionPowerOff_c              = gHciStatusBase_c | 0x15,
    gHciConnectionTerminatedByLocalHost_c                       = gHciStatusBase_c | 0x16,
    gHciRepeatedAttempts_c                                      = gHciStatusBase_c | 0x17,
    gHciPairingNotAllowed_c                                     = gHciStatusBase_c | 0x18,
    gHciUnknownLpmPdu_c                                         = gHciStatusBase_c | 0x19,
    gHciUnsupportedRemoteFeature_c                              = gHciStatusBase_c | 0x1A,
    gHciScoOffsetRejected_c                                     = gHciStatusBase_c | 0x1B,
    gHciScoIntervalRejected_c                                   = gHciStatusBase_c | 0x1C,
    gHciScoAirModeRejected_c                                    = gHciStatusBase_c | 0x1D,
    gHciInvalidLpmParameters_c                                  = gHciStatusBase_c | 0x1E,
    gHciUnspecifiedError_c                                      = gHciStatusBase_c | 0x1F,
    gHciUnsupportedLpmParameterValue_c                          = gHciStatusBase_c | 0x20,
    gHciRoleChangeNotAllowed_c                                  = gHciStatusBase_c | 0x21,
    gHciLLResponseTimeout_c                                     = gHciStatusBase_c | 0x22,
    gHciLmpErrorTransactionCollision_c                          = gHciStatusBase_c | 0x23,
    gHciLmpPduNotAllowed_c                                      = gHciStatusBase_c | 0x24,
    gHciEncryptionModeNotAcceptable_c                           = gHciStatusBase_c | 0x25,
    gHciLinkKeyCannotBeChanged_c                                = gHciStatusBase_c | 0x26,
    gHciRequestedQosNotSupported_c                              = gHciStatusBase_c | 0x27,
    gHciInstantPassed_c                                         = gHciStatusBase_c | 0x28,
    gHciPairingWithUnitKeyNotSupported_c                        = gHciStatusBase_c | 0x29,
    gHciDifferentTransactionCollision_c                         = gHciStatusBase_c | 0x2A,
    gHciReserved_0x2B_c                                         = gHciStatusBase_c | 0x2B,
    gHciQosNotAcceptableParameter_c                             = gHciStatusBase_c | 0x2C,
    gHciQosRejected_c                                           = gHciStatusBase_c | 0x2D,
    gHciChannelClassificationNotSupported_c                     = gHciStatusBase_c | 0x2E,
    gHciInsufficientSecurity_c                                  = gHciStatusBase_c | 0x2F,
    gHciParameterOutOfMandatoryRange_c                          = gHciStatusBase_c | 0x30,
    gHciReserved_0x31_c                                         = gHciStatusBase_c | 0x31,
    gHciRoleSwitchPending_c                                     = gHciStatusBase_c | 0x32,
    gHciReserved_0x33_c                                         = gHciStatusBase_c | 0x33,
    gHciReservedSlotViolation_c                                 = gHciStatusBase_c | 0x34,
    gHciRoleSwitchFailed_c                                      = gHciStatusBase_c | 0x35,
    gHciExtendedInquiryResponseTooLarge_c                       = gHciStatusBase_c | 0x36,
    gHciSecureSimplePairingNotSupportedByHost_c                 = gHciStatusBase_c | 0x37,
    gHciHostBusyPairing_c                                       = gHciStatusBase_c | 0x38,
    gHciConnectionRejectedDueToNoSuitableChannelFound_c         = gHciStatusBase_c | 0x39,
    gHciControllerBusy_c                                        = gHciStatusBase_c | 0x3A,
    gHciUnacceptableConnectionParameters_c                      = gHciStatusBase_c | 0x3B,
    gHciDirectedAdvertisingTimeout_c                            = gHciStatusBase_c | 0x3C,
    gHciConnectionTerminatedDueToMicFailure_c                   = gHciStatusBase_c | 0x3D,
    gHciConnectionFailedToBeEstablished_c                       = gHciStatusBase_c | 0x3E,
    gHciMacConnectionFailed_c                                   = gHciStatusBase_c | 0x3F,
    gHciCoarseClockAdjustmentRejected_c                         = gHciStatusBase_c | 0x40,

    /* HCI internal status codes */
    gHciAlreadyInit_c                                           = gHciStatusBase_c | 0xA0,
    gHciInvalidParameter_c                                      = gHciStatusBase_c | 0xA1,
    gHciCallbackNotInstalled_c                                  = gHciStatusBase_c | 0xA2,
    gHciCallbackAlreadyInstalled_c                              = gHciStatusBase_c | 0xA3,
    gHciCommandNotSupported_c                                   = gHciStatusBase_c | 0xA4,
    gHciEventNotSupported_c                                     = gHciStatusBase_c | 0xA5,
    gHciTransportError_c                                        = gHciStatusBase_c | 0xA6,

    /*
    *
    * Controller result values 
    *
    */
    gCtrlStatusBase_c = 0x0200,
    gCtrlSuccess_c                                              = gBleSuccess_c,

    /*
    *
    * L2CAP result values 
    *
    */
    gL2caStatusBase_c = 0x0300,
    gL2caSuccess_c                                              = gBleSuccess_c,
    /* L2CAP standard status codes */

    /* L2CAP internal status codes */
    gL2caAlreadyInit_c                                          = gL2caStatusBase_c | 0xF0,
    gL2caInsufficientResources_c                                = gL2caStatusBase_c | 0xF1,
    gL2caCallbackNotInstalled_c                                 = gL2caStatusBase_c | 0xF2,
    gL2caCallbackAlreadyInstalled_c                             = gL2caStatusBase_c | 0xF3,
    gL2caLePsmInvalid_c                                         = gL2caStatusBase_c | 0xF4,
    gL2caLePsmAlreadyRegistered_c                               = gL2caStatusBase_c | 0xF5,
    gL2caLePsmNotRegistered_c                                   = gL2caStatusBase_c | 0xF6,
    gL2caLePsmInsufficientResources_c                           = gL2caStatusBase_c | 0xF7,
    gL2caChannelInvalid_c                                       = gL2caStatusBase_c | 0xF8,
    gL2caChannelClosed_c                                        = gL2caStatusBase_c | 0xF9,
    gL2caChannelAlreadyConnected_c                              = gL2caStatusBase_c | 0xFA,
    gL2caConnectionParametersRejected_c                         = gL2caStatusBase_c | 0xFB,
    gL2caChannelBusy_c                                          = gL2caStatusBase_c | 0xFC,

    gL2caInvalidParameter_c                                     = gL2caStatusBase_c | 0xFE,
    gL2caError_c                                                = gL2caStatusBase_c | 0xFF,

    /*
    *
    * SMP result values 
    *
    */
    gSmStatusBase_c = 0x0400,
    gSmSuccess_c                                                = gBleSuccess_c,

    gSmNullCBFunction_c                                         = gSmStatusBase_c | 0x01,
    gSmCommandNotSupported_c                                    = gSmStatusBase_c | 0x02, /*!< The Security Manager (SM) does not have the required features or version to support this command */
    gSmUnexpectedCommand_c                                      = gSmStatusBase_c | 0x03, /*!< This command is not or cannot be handled in the current context of the SM.  */
    gSmInvalidCommandCode_c                                     = gSmStatusBase_c | 0x04, /*!< The provided SM command code is invalid. */
    gSmInvalidCommandLength_c                                   = gSmStatusBase_c | 0x05, /*!< The provided command length is not valid for the SM command code. */
    gSmInvalidCommandParameter_c                                = gSmStatusBase_c | 0x06, /*!< One of the parameters of the SM command is not valid. */
    gSmInvalidDeviceId_c                                        = gSmStatusBase_c | 0x07, /*!< The provided Device ID is invalid. */
    gSmInvalidInternalOperation_c                               = gSmStatusBase_c | 0x08, /*!< There is a problem with the internal state of the SM. This should not happen during normal operation.
                                                                                           *   A memory corruption or invalid operation may have occurred.  */
    gSmInvalidConnectionHandle_c                                = gSmStatusBase_c | 0x09, /*!< The target device does not have a valid connection handle. It might be disconnected. */
    gSmInproperKeyDistributionField_c                           = gSmStatusBase_c | 0x0A, /*!< The Responder upper layer has set to "1" one or more flags in the Initiator or Responder Key Distribution Fields
                                                                                           *   from the Pairing Request which were set to "0" by the peer device. */
    gSmUnexpectedKeyType_c                                      = gSmStatusBase_c | 0x0B, /*!< The Responder upper layer has set a key type field in the Passkey Request Reply
                                                                                           *   command, which is different than the field negotiated with the peer device. */
    gSmUnexpectedPairingTerminationReason_c                     = gSmStatusBase_c | 0x0C, /*!< The upper layer tried to cancel the pairing procedure with an unexpected
                                                                                           *   pairing failure reason for the current phase of the pairing procedure. */
    gSmUnexpectedKeyset_c                                       = gSmStatusBase_c | 0x0D, /*!< The Responder upper layer is trying to distribute keys which were not requested during the pairing procedure
                                                                                           *   or the peer device has sent a Key Distribution packet which was not expected. */
    gSmSmpTimeoutOccurred_c                                     = gSmStatusBase_c | 0x0E, /*!< An SMP timeout has occurred for the peer device.
                                                                                           *   No more operations are accepted until a new physical link is established. */
    gSmUnknownSmpPacketType_c                                   = gSmStatusBase_c | 0x0F, /*!< An SMP packet with an unknown (or invalid) type has been received. */
    gSmInvalidSmpPacketLength_c                                 = gSmStatusBase_c | 0x10, /*!< An SMP packet with an invalid length for the SMP packet type has been received. */
    gSmInvalidSmpPacketParameter_c                              = gSmStatusBase_c | 0x11, /*!< An SMP packet with an invalid parameter has been received. */
    gSmReceivedUnexpectedSmpPacket_c                            = gSmStatusBase_c | 0x12, /*!< An unexpected SMP packet was received. */
    gSmReceivedSmpPacketFromUnknownDevice_c                     = gSmStatusBase_c | 0x13, /*!< An SMP packet is received but the source Device ID cannot be identified. */
    gSmReceivedUnexpectedHciEvent_c                             = gSmStatusBase_c | 0x14, /*!< An HCI event has been received which cannot be handled by the SM or cannot be
                                                                                           *   handled in the current context. */
    gSmReceivedHciEventFromUnknownDevice_c                      = gSmStatusBase_c | 0x15, /*!< An HCI event is received but the source Device ID cannot be identified. */
    gSmInvalidHciEventParameter_c                               = gSmStatusBase_c | 0x16, /*!< An HCI Event is received with an invalid parameter. */
    gSmLlConnectionEncryptionInProgress_c                       = gSmStatusBase_c | 0x17, /*!< A Link Layer Connection encryption was requested by the upper layer or attempted internally by
                                                                                           *   the SM, but it could no be completed because an encryption was already in progress.
                                                                                           *   This situation could lead to an SMP Pairing Failure when the SM cannot encrypt the
                                                                                           *   link with the STK. An unspecified pairing failure reason is used in this instance. */
    gSmLlConnectionEncryptionFailure_c                          = gSmStatusBase_c | 0x18, /*!< The Link Layer connection encryption procedure has failed. */                                                                                      
    gSmInsufficientResources_c                                  = gSmStatusBase_c | 0x19, /*!< The SM could not allocate resources to perform operations (memory or timers). */
    /* LE SC statuses. */
    gSmOobDataAddressMismatch_c                                 = gSmStatusBase_c | 0x1A, /*!< The address of the peer contained in the remote OOB data sent to the stack does not match
                                                                                           *   the address used by the remote device for the connection/pairing procedure. */
    gSmSmpPacketReceivedAfterTimeoutOccurred_c                  = gSmStatusBase_c | 0x1B, /*!< A SMP packet has been received from a peer device for which a pairing priocedure has timed out.
                                                                                           *   No further operations are permitted until a new connection sisestablished. */
    gSmReceivedTimerEventForUnknownDevice_c                     = gSmStatusBase_c | 0x1C, /*!< An Timer event is received but the source Device ID cannot be identified. */
    gSmUnattainableLocalDeviceSecRequirements_c                 = gSmStatusBase_c | 0x1D, /*!< The provided pairing parameters cannot lead to a Pairing Procedure which satisfies the minimum
                                                                                               security properties for the local device. */
    gSmUnattainableLocalDeviceMinKeySize_c                      = gSmStatusBase_c | 0x1E, /*!< The provided pairing parameters cannot lead to a Pairing Procedure which satisfies the minimum
                                                                                               encryption key size for the local device. */
    gSmUnattainableSlaveSecReqRequirements_c                    = gSmStatusBase_c | 0x1F, /*!< The provided pairing parameters cannot lead to a Pairing Procedure which satisfies the minimum
                                                                                               security properties requested by the local device via a SMP Slave Security Request. */

    /* Added for the GAP layer to signal the application about pairing failed reasons. */
    gSmPairingErrorPasskeyEntryFailed_c                         = gSmStatusBase_c | 0x31,
    gSmPairingErrorConfirmValueFailed_c                         = gSmStatusBase_c | 0x32,
    gSmPairingErrorCommandNotSupported_c                        = gSmStatusBase_c | 0x33,
    gSmPairingErrorInvalidParameters_c                          = gSmStatusBase_c | 0x34,
    gSmPairingErrorUnknownReason_c                              = gSmStatusBase_c | 0x35,
    
    /* SM Tool Box statuses. */
    gSmTbResolvableAddressDoesNotMatchIrk_c                     = gSmStatusBase_c | 0x60, /*!< The provided Resolvable Private Address and IRK do not match. */
    gSmTbInvalidDataSignature_c                                 = gSmStatusBase_c | 0x61, /*!< The provided data signature does not match the computed data signature. */
 
    /*
    *
    * ATT result values
    *
    */
    gAttStatusBase_c = 0x0500,                                                      /*!< ATT status base. */
    gAttSuccess_c                                               = gBleSuccess_c,    /*!< Alias. */

    /* ATT error codes as defined in "att_errors.h" are added to the gAttStatusBase_c. */
 
    /*
    *
    * GATT result values 
    *
    */
    gGattStatusBase_c = 0x0600,                                                         /*!< GATT status base. */
    gGattSuccess_c                                              = gBleSuccess_c,        /*!< Alias.  */

    gGattAnotherProcedureInProgress_c                     = gGattStatusBase_c | 0x01,   /*!< Trying to start a GATT procedure while one is already in progress. */
    gGattLongAttributePacketsCorrupted_c                  = gGattStatusBase_c | 0x02,   /*!< Writing a Long Characteristic failed because Prepare Write Request packets were corrupted. */
    gGattMultipleAttributesOverflow_c                     = gGattStatusBase_c | 0x03,   /*!< Too many Characteristics are given for a Read Multiple Characteristic procedure. */
    gGattUnexpectedReadMultipleResponseLength_c           = gGattStatusBase_c | 0x04,   /*!< Read Multiple Characteristic procedure failed because unexpectedly long data was read. */
    gGattInvalidValueLength_c                             = gGattStatusBase_c | 0x05,   /*!< An invalid value length was supplied to a Characteristic Read/Write operation. */
    gGattServerTimeout_c                                  = gGattStatusBase_c | 0x06,   /*!< No response was received from the Server. */

    gGattIndicationAlreadyInProgress_c                    = gGattStatusBase_c | 0x07,   /*!< A Server Indication is already waiting for Client Confirmation. */
    gGattClientConfirmationTimeout_c                      = gGattStatusBase_c | 0x08,   /*!< No Confirmation was received from the Client after a Server Indication. */
 
    /*
    *
    * GAP result values 
    *
    */
    gGapStatusBase_c = 0x0700,                                                          /*!< GAP status base. */
    gGapSuccess_c                                               = gBleSuccess_c,        /*!< Alias. */

    gGapAdvDataTooLong_c                                  = gGapStatusBase_c | 0x01,    /*!< Trying to set too many bytes in the advertising payload. */
    gGapScanRspDataTooLong_c                              = gGapStatusBase_c | 0x02,    /*!< Trying to set too many bytes in the scan response payload. */
    gGapDeviceNotBonded_c                                 = gGapStatusBase_c | 0x03,    /*!< Trying to execute an API that is only available for bonded devices. */

    /*
    *
    * Reserved result values 
    *
    */
    gDevDbStatusBase_c = 0x0800,                                                                /*!< DeviceDatabase status base. */
    gDevDbSuccess_c                                             = gBleSuccess_c,                /*!< Alias. */

    gDevDbCccdLimitReached_c                                    = gDevDbStatusBase_c | 0x01,    /*!< CCCD value cannot be saved because Server's CCCD list is full for the current client. */
    gDevDbCccdNotFound_c                                        = gDevDbStatusBase_c | 0x02,    /*!< CCCD with the given handle is not found in the Server's list for the current client. */
    
    /*
    *
    * GATT_DB result values 
    *
    */
    gGattDbStatusBase_c = 0x0900,                                                               /*!< GATT Database status base. */
    gGattDbSuccess_c                                            = gBleSuccess_c,                /*!< Alias. */

    gGattDbInvalidHandle_c                                      = gGattDbStatusBase_c | 0x01,   /*!< An invalid handle was passed as parameter. */
    gGattDbCharacteristicNotFound_c                             = gGattDbStatusBase_c | 0x02,   /*!< Characteristic was not found. */
    gGattDbCccdNotFound_c                                       = gGattDbStatusBase_c | 0x03,   /*!< CCCD was not found. */
    gGattDbServiceNotFound_c                                    = gGattDbStatusBase_c | 0x04,   /*!< Service Declaration was not found. */
    gGattDbDescriptorNotFound_c                                 = gGattDbStatusBase_c | 0x05,   /*!< Characteristic Descriptor was not found. */

} bleResult_t;

/*! Unique identifier type for a connected device. */
typedef uint8_t deviceId_t;

/*! Bluetooth Device Address Types */
typedef enum {
    gBleAddrTypePublic_c            = 0x00,     /*!< Public Device Address - fixed into the Controller by the manufacturer. */
    gBleAddrTypeRandom_c            = 0x01      /*!< Random Device Address - set by the Host into the Controller for privacy reasons. */
} bleAddressType_t;

/*! Bluetooth Device Address - array of 6 bytes. */
typedef uint8_t bleDeviceAddress_t[gcBleDeviceAddressSize_c];

/*! Bluetooth Identity Address - array of 6 bytes. */
typedef struct bleIdentityAddress_tag
{
    bleAddressType_t    idAddressType; /*!< Public or Random (static). */
    bleDeviceAddress_t  idAddress;     /*!< 6-byte address. */
} bleIdentityAddress_t;

/*! Bluetooth UUID type - values chosen to correspond with the ATT UUID format */
typedef enum {
    gBleUuidType16_c    = 0x01,    /*!< 16-bit standard UUID */
    gBleUuidType128_c   = 0x02,    /*!< 128-bit long/custom UUID */
    gBleUuidType32_c    = 0x03     /*!< 32-bit UUID - not available as ATT UUID format */
} bleUuidType_t;

/*! Union for a Bluetooth UUID; selected according to an accompanying bleUuidType_t */
typedef union {
    uint16_t    uuid16;         /*!< For gBleUuidType16_c. */
    uint32_t    uuid32;         /*!< For gBleUuidType32_c. */
    uint8_t     uuid128[16];    /*!< For gBleUuidType128_c. */
} bleUuid_t;

/*! Advertising Type */
typedef enum {
    gAdvConnectableUndirected_c                 = 0x00,     /*!< Answers to both connect and scan requests. */
    gAdvDirectedHighDutyCycle_c                 = 0x01,     /*!< Answers only to connect requests; smaller advertising interval for quicker connection. */
    gAdvScannable_c                             = 0x02,     /*!< Answers only to scan requests. */
    gAdvNonConnectable_c                        = 0x03,     /*!< Does not answer to connect nor scan requests. */
    gAdvDirectedLowDutyCycle_c                  = 0x04      /*!< Answers only to connect requests; larger advertising interval. */
} bleAdvertisingType_t;

typedef struct bleAdvertisingChannelMap_tag
{
    uint8_t     enableChannel37:    1;  /*!< Bit for channel 37. */
    uint8_t     enableChannel38:    1;  /*!< Bit for channel 38. */
    uint8_t     enableChannel39:    1;  /*!< Bit for channel 39. */
    uint8_t     reserved:           5;  /*!< Reserved for future use. */
} bleAdvertisingChannelMap_t;

typedef enum
{
    gBleAdvFilterAllowScanFromAnyAllowConnFromAny_c     = 0x00,     /*!< White List is ignored. */
    gBleAdvFilterAllowScanFromWLAllowConnFromAny_c      = 0x01,     /*!< White List is used only for Scan Requests. */
    gBleAdvFilterAllowScanFromAnyAllowConnFromWL_c      = 0x02,     /*!< White List is used only for Connection Requests. */
    gBleAdvFilterAllowScanFromWLAllowConnFromWL_c       = 0x03,     /*!< White List is used for both Scan and Connection Requests. */
} bleAdvertisingFilterPolicy_t;

typedef enum
{
    gBleLlConnectionMaster_c        = 0x00, /*!< Link Layer Master Role */
    gBleLlConnectionSlave_c         = 0x01, /*!< Link Layer Slave Role */
} bleLlConnectionRole_t;

typedef enum
{
    gBleMasterClkAcc500ppm_c        = 0x00,
    gBleMasterClkAcc250ppm_c        = 0x01,
    gBleMasterClkAcc150ppm_c        = 0x02,
    gBleMasterClkAcc100ppm_c        = 0x03,
    gBleMasterClkAcc75ppm_c         = 0x04,
    gBleMasterClkAcc50ppm_c         = 0x05,
    gBleMasterClkAcc30ppm_c         = 0x06,
    gBleMasterClkAcc20ppm_c         = 0x07,
} bleMasterClockAccuracy_t;

typedef enum
{
    gBleAdvRepAdvInd_c              = 0x00, /* Connectable undirected advertising (ADV_IND) */
    gBleAdvRepAdvDirectInd_c        = 0x01, /* Connectable directed advertising (ADV_DIRECT_IND) */
    gBleAdvRepAdvScanInd_c          = 0x02, /* Scannable undirected advertising (ADV_SCAN_IND) */
    gBleAdvRepAdvNonconnInd_c       = 0x03, /* Non Connectable undirected advertising (ADV_NONCONN_IND) */
    gBleAdvRepScanRsp_c             = 0x04, /* Scan Response (SCAN_RSP) */
} bleAdvertisingReportEventType_t;

typedef enum
{
    gHciCommandPacket_c          = 0x01, /*!<  HCI Command */
    gHciDataPacket_c             = 0x02, /*!<  L2CAP Data Packet */
    gHciSynchronousDataPacket_c  = 0x03, /*!<  Not used in BLE */
    gHciEventPacket_c            = 0x04, /*!<  HCI Event */
} hciPacketType_t;

/*! Scanning type enumeration. */
typedef enum bleScanType_tag {
    gScanTypePassive_c   = 0x00,     /*!< Passive Scanning - advertising packets are immediately reported to the Host. */
    gScanTypeActive_c    = 0x01      /*!< Active Scanning - the scanner sends scan requests to the advertiser and reports to the Host after the scan response is received. */
} bleScanType_t;

/*! Scanning filter policy enumeration. */
typedef enum {
    gScanAll_c              =  0x00,    /*!< Scans all advertising packets. */
    gScanWithWhiteList_c    =  0x01     /*!< Scans advertising packets using the White List. */
} bleScanningFilterPolicy_t;

/*! Initiator filter policy enumeration. */
typedef enum {
    gUseDeviceAddress_c      =  0x00,   /*!< Initiates a connection with a specific device identified by its address. */
    gUseWhiteList_c          =  0x01    /*!< Initiates connections with all the devices in the White List at the same time. */
} bleInitiatorFilterPolicy_t;

typedef enum
{
    gReadCurrentTxPowerLevel_c   = 0x00, /*!< Current TX Power level. */
    gReadMaximumTxPowerLevel_c   = 0x01, /*!< Maximum recorded TX Power level. */
} bleTransmitPowerLevelType_t;

typedef enum
{
    gBleFreq2402MHz_c       = 0x00,
    gBleFreq2404MHz_c       = 0x01,
    gBleFreq2406MHz_c       = 0x02,
    gBleFreq2408MHz_c       = 0x03,
    gBleFreq2410MHz_c       = 0x04,
    gBleFreq2412MHz_c       = 0x05,
    gBleFreq2414MHz_c       = 0x06,
    gBleFreq2416MHz_c       = 0x07,
    gBleFreq2418MHz_c       = 0x08,
    gBleFreq2420MHz_c       = 0x09,
    gBleFreq2422MHz_c       = 0x0A,
    gBleFreq2424MHz_c       = 0x0B,
    gBleFreq2426MHz_c       = 0x0C,
    gBleFreq2428MHz_c       = 0x0D,
    gBleFreq2430MHz_c       = 0x0E,
    gBleFreq2432MHz_c       = 0x0F,
    gBleFreq2434MHz_c       = 0x10,
    gBleFreq2436MHz_c       = 0x11,
    gBleFreq2438MHz_c       = 0x12,
    gBleFreq2440MHz_c       = 0x13,
    gBleFreq2442MHz_c       = 0x14,
    gBleFreq2444MHz_c       = 0x15,
    gBleFreq2446MHz_c       = 0x16,
    gBleFreq2448MHz_c       = 0x17,
    gBleFreq2450MHz_c       = 0x18,
    gBleFreq2452MHz_c       = 0x19,
    gBleFreq2454MHz_c       = 0x1A,
    gBleFreq2456MHz_c       = 0x1B,
    gBleFreq2458MHz_c       = 0x1C,
    gBleFreq2460MHz_c       = 0x1D,
    gBleFreq2462MHz_c       = 0x1E,
    gBleFreq2464MHz_c       = 0x1F,
    gBleFreq2466MHz_c       = 0x20,
    gBleFreq2468MHz_c       = 0x21,
    gBleFreq2470MHz_c       = 0x22,
    gBleFreq2472MHz_c       = 0x23,
    gBleFreq2474MHz_c       = 0x24,
    gBleFreq2476MHz_c       = 0x25,
    gBleFreq2478MHz_c       = 0x26,
    gBleFreq2480MHz_c       = 0x27,
} bleChannelFrequency_t;

typedef enum
{
    gBleTestPacketPayloadPrbs9_c            = 0x00,
    gBleTestPacketPayloadPattern11110000_c  = 0x01,
    gBleTestPacketPayloadPattern10101010_c  = 0x02,
    gBleTestPacketPayloadPrbs15_c           = 0x03,
    gBleTestPacketPayloadPatternAllBits1_c  = 0x04,
    gBleTestPacketPayloadPatternAllBits0_c  = 0x05,
    gBleTestPacketPayloadPattern00001111_c  = 0x06,
    gBleTestPacketPayloadPattern01010101_c  = 0x07,
} bleTxTestPacketPayload_t;

typedef enum
{
    bleHwErrCodeNoError_c                   = 0x00,
} bleHardwareErrorCode_t;

typedef struct gapLeScOobData_tag
{
    uint8_t     randomValue[gSmpLeScRandomValueSize_c];          /*!< LE SC OOB r (Random value) */
    uint8_t     confirmValue[gSmpLeScRandomConfirmValueSize_c];  /*!< LE SC OOB Cr (Random Confirm value) */
} gapLeScOobData_t;

/*! Generic Event Type */
typedef enum gapGenericEventType_tag {
    gInitializationComplete_c,                  /*!< Initial setup started by Ble_HostInitialize is complete. */
    gInternalError_c,                           /*!< An internal error occurred. */
    gAdvertisingSetupFailed_c,                  /*!< Error during advertising setup. */
    gAdvertisingParametersSetupComplete_c,      /*!< Advertising parameters have been successfully set. Response to Gap_SetAdvertisingParameters. */
    gAdvertisingDataSetupComplete_c,            /*!< Advertising and/or scan response data has been successfully set. Response to Gap_SetAdvertisingData. */
    gWhiteListSizeRead_c,                       /*!< Contains the White List size. Response to Gap_ReadWhiteListSize. */
    gDeviceAddedToWhiteList_c,                  /*!< Device has been added to White List. Response to Gap_AddDeviceToWhiteList. */
    gDeviceRemovedFromWhiteList_c,              /*!< Device has been removed from the White List. Response to Gap_RemoveDeviceFromWhiteList. */
    gWhiteListCleared_c,                        /*!< White List has been cleared. Response to Gap_ClearWhiteList. */
    gRandomAddressReady_c,                      /*!< A random device address has been created. Response to Gap_CreateRandomDeviceAddress. */
    gCreateConnectionCanceled_c,                /*!< Connection initiation was successfully cancelled. Response to Gap_CancelInitiatingConnection. */
    gPublicAddressRead_c,                       /*!< Contains the public device address. Response to Gap_ReadPublicDeviceAddress. */
    gAdvTxPowerLevelRead_c,                     /*!< Contains the TX power on the advertising channel. Response to Gap_ReadAdvertisingTxPowerLevel. */
    gPrivateResolvableAddressVerified_c,        /*!< Contains the result of PRA verification. Response to Gap_VerifyPrivateResolvableAddress. */
    gRandomAddressSet_c,                        /*!< Random address has been set into the Controller. Response to Gap_SetRandomAddress. */
    gControllerResetComplete_c,                 /*!< Controller has been successfully reset. */
    gLeScPublicKeyRegenerated_c,                /*!< The private/public key pair used for LE Secure Connections pairing has been regenerated. */
    gLeScLocalOobData_c,                        /*!< Local OOB data used for LE Secure Connections pairing. */
    gControllerPrivacyStateChanged_c,           /*!< Controller Privacy was enabled or disabled. */
    gControllerTestEvent_c,                     /*!< Controller Test was started or stopped. */
} gapGenericEventType_t;

/*! Internal Error Source - the command that triggered the error */
typedef enum gapInternalErrorSource_tag {
    gHciCommandStatus_c,
    gCheckPrivateResolvableAddress_c,
    gVerifySignature_c,
    gAddNewConnection_c,
    gResetController_c,
    gSetEventMask_c,
    gReadLeBufferSize_c,
    gSetLeEventMask_c,
    gReadDeviceAddress_c,
    gReadLocalSupportedFeatures_c,
    gReadWhiteListSize_c,
    gClearWhiteList_c,
    gAddDeviceToWhiteList_c,
    gRemoveDeviceFromWhiteList_c,
    gCancelCreateConnection_c,
    gReadRadioPower_c,
    gSetRandomAddress_c,
    gCreateRandomAddress_c,
    gEncryptLink_c,
    gProvideLongTermKey_c,
    gDenyLongTermKey_c,
    gConnect_c,
    gDisconnect_c,
    gTerminatePairing_c,
    gSendSlaveSecurityRequest_c,
    gEnterPasskey_c,
    gProvideOob_c,
    gSendSmpKeys_c,
    gWriteSuggestedDefaultDataLength_c,
    gReadSuggestedDefaultDataLength_c,
    gUpdateLeDataLength_c,
    gEnableControllerPrivacy_c, 
    gLeScSendKeypressNotification_c,
    gLeScSetPeerOobData_c,
    gLeScGetLocalOobData_c,
    gLeScValidateNumericValue_c,
    gLeScRegeneratePublicKey_c,
    gLeSetResolvablePrivateAddressTimeout_c,
	gDefaultPairingProcedure_c,
    gLeControllerTest_c
} gapInternalErrorSource_t;

/*! Internal Error Event Data */
typedef struct gapInternalError_tag {
    bleResult_t                 errorCode;          /*!< Host Stack error code. */
    gapInternalErrorSource_t    errorSource;        /*!< The command that generated the error; useful when it is not obvious from the error code. */
    uint16_t                    hciCommandOpcode;   /*!< Only for errorSource = gHciCommandStatus_c; the HCI Command that received an error status. */
} gapInternalError_t;

typedef enum gapControllerTestEventType_tag
{
    gControllerReceiverTestStarted_c,
    gControllerTransmitterTestStarted_c,
    gControllerTestEnded_c,
} gapControllerTestEventType_t;

typedef struct gapControllerTestEvent_tag {
    gapControllerTestEventType_t    testEventType;
    uint16_t                        receivedPackets; /* Valid only if testEventType == gControllerTestEnded_c and the test was a Receiver Test. */
} gapControllerTestEvent_t;

/*! Generic Event Structure = type + data */
typedef struct gapGenericEvent_tag {
    gapGenericEventType_t  eventType;       /*!< Event type. */
    union {
        gapInternalError_t          internalError;          /*!< Data for the gInternalError_c event. The error that has occurred and the command that triggered it. */
        uint8_t                     whiteListSize;          /*!< Data for the gWhiteListSizeReady_c event. The size of the White List. */
        bleDeviceAddress_t          aAddress;               /*!< Data for the gRandomAddressReady_c, gPublicAddressRead_c events. Contains the requested device address. */
        bleResult_t                 setupFailError;         /*!< Data for the gAdvertisingSetupFailed_c event. The error that occurred during the advertising setup. */
        int8_t                      advTxPowerLevel_dBm;    /*!< Data for the gAdvTxPowerLevelRead_c event. Value in dBm. */
        bool_t                      verified;               /*!< Data for the gPrivateResolvableAddressVerified_c event. TRUE if the PRA was resolved with the given IRK. */
        gapLeScOobData_t            localOobData;           /*!< Data for the gLeScLocalOobData_c event. Contains local OOB data for LESC Pairing. */
	    bool_t                      newControllerPrivacyState; /*!< Data for the gControllerPrivacyStateChanged_c event. TRUE if enabled, FALSE if disabled. */
        gapControllerTestEvent_t    testEvent;                 /*!< Data for the gControllerTestEvent_c event. Contains test event type and received packets. */
    } eventData;                            /*!< Event data, selected according to event type. */
} gapGenericEvent_t;

/*! Generic Callback prototype. */
typedef void (*gapGenericCallback_t)
(
    gapGenericEvent_t* pGenericEvent  /*!< Generic event. */
);

/*! Host-to-Controller API prototype. */
typedef bleResult_t (*hciHostToControllerInterface_t)
(
    hciPacketType_t packetType,     /*!< HCI Packet Type. */
    void* pPacket,                  /*!< Pointer to packet payload. */
    uint16_t packetSize             /*!< Packet payload size. */
);

typedef struct bleBondDataBlob_tag
{
    uint32_t raw[gBleBondDataSize_c / sizeof(uint32_t)];
} bleBondDataBlob_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Performs master initialization of the BLE Host stack.
*
* \param[in] genericCallback  Callback used to propagate GAP generic events to the application.
* \param[in] hostToControllerInterface  LE Controller uplink interface function pointer
*
* \return  gBleSuccess_c or error.
*
* \remarks Application must wait for the gInitializationComplete_c generic event.
*
********************************************************************************** */
bleResult_t Ble_HostInitialize
(
    gapGenericCallback_t            genericCallback,
    hciHostToControllerInterface_t  hostToControllerInterface
);

/*! *********************************************************************************
* \brief  This is the BLE Host downlink interface function.
*
* \param[in] packetType     The type of the packet sent by the LE Controller
* \param[in] pPacket        Pointer to the packet sent by the LE Controller
* \param[in] packetSize     Number of bytes sent by the LE Controller
*
* \return gBleSuccess_c or gBleOutOfMemory_c
*
* \remarks This function must be registered as a callback by the LE Controller and called
* to send HCI packets (events and LE-U data) to the BLE Host.
*
********************************************************************************** */
bleResult_t Ble_HciRecv
(
    hciPacketType_t     packetType,
    void*               pPacket,
    uint16_t            packetSize
);


#ifdef __cplusplus
}
#endif

#endif /* _BLE_GENERAL_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
