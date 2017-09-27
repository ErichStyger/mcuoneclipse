/*! *********************************************************************************
 * \addtogroup GAP
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file gap_types.h
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

#ifndef _GAP_TYPES_H_
#define _GAP_TYPES_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"

/*************************************************************************************
 *************************************************************************************
 * Public macros
 *************************************************************************************
 ************************************************************************************/
/*! Use this value as a parameter to the Gap_Disconnect(deviceId) function to
 * cancel any ongoing connection initiation, for example if the connection has timed out. */
#define gCancelOngoingInitiatingConnection_d    gInvalidDeviceId_c

/*! Mask to check if a Security Mode-and-Level is Mode 2 */
#define gMode_2_Mask_d  0x20

/*
 * Useful macros for combining security requirements
 * - When two requirements of the same mode meet, the highest one has priority.
 * - When two requirements of different modes meet, the following table (Core v.4.1) applies:
 *
 * [M_L]   1_0       1_1       1_2
 *
 * 2_1     2_1       1_1       1_2
 *
 * 2_2     2_2       1_2       1_2
 *
 */

/*! Extracts the security level (see gapSecurityLevel_t) from the combined security mode-level (gapSecurityModeAndLevel_t). */
#define getSecurityLevel(modeLevel) (modeLevel & 0x0F)

/*! Extracts the security mode (see gapSecurityMode_t) from the combined security mode-level (gapSecurityModeAndLevel_t). */
#define getSecurityMode(modeLevel) (modeLevel & 0xF0)

#define isMode_2(modeLevel) ((modeLevel & gMode_2_Mask_d) != 0x00)
#define isMode_1(modeLevel) (!isMode_2(modeLevel))
#define isSameMode(modeLevelA, modeLevelB) (isMode_1(modeLevelA) == isMode_1(modeLevelB))
#define addSameSecurityModes(modeLevelA,modeLevelB) \
    (modeLevelA > modeLevelB ? modeLevelA : modeLevelB)     
#define addMode1AndMode2(mode1,mode2) \
    (mode1 == gSecurityMode_1_Level_1_c ? \
     mode2 : \
         (mode1 == gSecurityMode_1_Level_2_c && mode2 == gSecurityMode_2_Level_1_c ? \
          gSecurityMode_1_Level_2_c : \
          gSecurityMode_1_Level_3_c))        
#define addDifferentSecurityModes(modeLevelA,modeLevelB) \
    (isMode_1(modeLevelA) ? \
     addMode1AndMode2(modeLevelA, modeLevelB) : \
     addMode1AndMode2(modeLevelB, modeLevelA))

/*! The default value for the LTK size */
#define gDefaultEncryptionKeySize_d   7
        
/*! The default value for the Device Security (no requirements) */
#define gGapDefaultDeviceSecurity_d \
{ \
  /* masterSecurityRequirements */      NULL, \
  /* cNumServices */                    0, \
  /* aServiceSecurityRequirements */    NULL \
}

/*! The default value for a Security Requirement */
#define gGapDefaultSecurityRequirements_d \
{ \
      /* securityModeLevel */               gSecurityMode_1_Level_1_c, \
      /* authorization */                   FALSE, \
      /* minimumEncryptionKeySize */        gDefaultEncryptionKeySize_d \
}

/*
* Advertising Interval Ranges
* Size: 2 bytes
* Unit: 0.625ms.
* Range: 20ms - 10.24s.
* Default: 1.28s
*/

/*! Minimum advertising interval (20 ms) */
#define gGapAdvertisingIntervalRangeMinimum_c       0x0020
/*! Default advertising interval (1.28 s) */
#define gGapAdvertisingIntervalDefault_c            0x0800
/*! Maximum advertising interval (10.24 s) */
#define gGapAdvertisingIntervalRangeMaximum_c       0x4000

/*! Default Advertising Channel Map - all 3 channels are enabled */
#define gGapAdvertisingChannelMapDefault_c \
         ( gAdvChanMapFlag37_c \
         | gAdvChanMapFlag38_c \
         | gAdvChanMapFlag39_c )

/*! Default value for Advertising Parameters struct */
#define gGapDefaultAdvertisingParameters_d \
{ \
    /* minInterval */         gGapAdvertisingIntervalDefault_c, \
    /* maxInterval */         gGapAdvertisingIntervalDefault_c, \
    /* advertisingType */     gAdvConnectableUndirected_c, \
    /* addressType */         gBleAddrTypePublic_c, \
    /* peerAddressType */     gBleAddrTypePublic_c, \
    /* peerAddress */         {0, 0, 0, 0, 0, 0}, \
    /* channelMap */          (gapAdvertisingChannelMapFlags_t) (gAdvChanMapFlag37_c | gAdvChanMapFlag38_c | gAdvChanMapFlag39_c), \
    /* filterPolicy */        gProcessAll_c \
}

/*
* Scan Interval Ranges
* Size: 2 bytes
* Unit: 0.625ms.
* Range: 2.5ms - 10.24s.
* Default: 10ms
*/

/*! Minimum scan interval (2.5 ms) */
#define gGapScanIntervalMin_d       0x0004
/*! Default scan interval (10 ms) */
#define gGapScanIntervalDefault_d   0x0010
/*! Maximum scan interval (10.24 ms) */
#define gGapScanIntervalMax_d       0x4000

/*
* Scan Window Ranges
* Size: 2 bytes
* Unit: 0.625ms.
* Range: 2.5ms - 10.24s.
* Default: 10ms
*/

/*! Minimum scan window (2.5 ms) */
#define gGapScanWindowMin_d       0x0004
/*! Default scan window (10 ms) */
#define gGapScanWindowDefault_d   0x0010
/*! Maximum scan window (10.24 ms) */
#define gGapScanWindowMax_d       0x4000

/*
* RSSI Ranges
* Size: 1 byte, signed
* Unit: dBm.
* Range: (-128) - (+20).
* Special value: 127 = RSSI not available
*/

/*! Minimum valid value for RSSI (dB) */
#define gGapRssiMin_d               -128
/*! Maximum valid value for RSSI (dB) */
#define gGapRssiMax_d                +20
/*! A special invalid value for the RSSI indicating that the measurement is not available. */
#define gGapRssiNotAvailable_d       127 

/*! Default value for Scanning Parameters struct */
#define gGapDefaultScanningParameters_d \
{ \
    /* type */              gScanTypePassive_c, \
    /* interval */          gGapScanIntervalDefault_d, \
    /* window */            gGapScanWindowDefault_d, \
    /* ownAddressType */    gBleAddrTypePublic_c, \
    /* filterPolicy */      gScanAll_c \
}

/*
* Connection Interval Ranges
* Size: 2 bytes
* Unit: 1.25ms.
* Range: 7.5ms - 4s.
*/

/*! Minimum connection interval (7.5 ms) */
#define gGapConnIntervalMin_d       0x0006
/*! Maximum connection interval (4 s) */
#define gGapConnIntervalMax_d       0x0C80

/*
* Connection Latency Ranges
* Size: 2 bytes.
* Unit: 1 ignored event.
* Range: 0 - 499.
*/

/*! Minimum connection latency value (0 - no connection event may be ignored) */
#define gGapConnLatencyMin_d       0x0000
/*! Maximum connection latency value (499 connection events may be ignored) */
#define gGapConnLatencyMax_d       0x01F3

/*
* Supervision Timeout Ranges
* Size: 2 bytes.
* Unit: 10ms.
* Range: 100ms - 32s.
*/

/*! Minimum supervision timeout (100 ms) */
#define gGapConnSuperTimeoutMin_d       0x000A
/*! Maximum supervision timeout (32 s) */
#define gGapConnSuperTimeoutMax_d       0x0C80

/*
* Connection Event Length Ranges
* Size: 2 bytes.
* Unit: 0.625ms.
* Range: maximum possible (0 - 40959.375ms)
*/

/*! Minimum value of the connection event length (0 ms) */
#define gGapConnEventLengthMin_d       0x0000
/*! Maximum value of the connection event length (~41 s) */
#define gGapConnEventLengthMax_d       0xFFFF

/* Non-standard defaults for connection parameters */

/*! Default connection latency: 0 */
#define gGapDefaultConnectionLatency_d      0x0000
/*! Default supervision timeout: 10s */
#define gGapDefaultSupervisionTimeout_d     0x03E8
/*! Default minimum connection interval: 100ms */
#define gGapDefaultMinConnectionInterval_d  0x0050
/*! Default maximum connection interval: 200ms */
#define gGapDefaultMaxConnectionInterval_d  0x00A0

/*! The default value for the Connection Request Parameters structure */
#define gGapDefaultConnectionRequestParameters_d \
{ \
    /* scanInterval */          gGapScanIntervalDefault_d, \
    /* scanWindow */            gGapScanWindowDefault_d, \
    /* filterPolicy */          gUseDeviceAddress_c, \
    /* ownAddressType */        gBleAddrTypePublic_c, \
    /* peerAddressType */       gBleAddrTypePublic_c, \
    /* peerAddress */           { 0, 0, 0, 0, 0, 0 }, \
    /* connIntervalMin */       gGapDefaultMinConnectionInterval_d, \
    /* connIntervalMax */       gGapDefaultMaxConnectionInterval_d, \
    /* connLatency */           gGapDefaultConnectionLatency_d, \
    /* supervisionTimeout */    gGapDefaultSupervisionTimeout_d, \
    /* connEventLengthMin */    gGapConnEventLengthMin_d, \
    /* connEventLengthMax */    gGapConnEventLengthMax_d \
}

/*************************************************************************************
 *************************************************************************************
 * Public type definitions
 *************************************************************************************
 ************************************************************************************/

/*! GAP Role of a BLE device */
typedef enum gapRole_tag {
    gGapCentral_c,      /*!< Central scans and connects to Peripherals. */
    gGapPeripheral_c,   /*!< Peripheral advertises and connects to Centrals. */
    gGapObserver_c,     /*!< Observer only scans and makes no connections. */
    gGapBroadcaster_c   /*!< Broadcaster only advertises and makes no connections. */
} gapRole_t;

/*! I/O Capabilities as defined by the SMP */
typedef enum gapIoCapabilities_tag {
    gIoDisplayOnly_c        = 0x00,     /*!< May display a PIN, no input. */
    gIoDisplayYesNo_c       = 0x01,     /*!< May display a PIN and has a binary input (e.g., YES and NO buttons). */
    gIoKeyboardOnly_c       = 0x02,     /*!< Has keyboard input, no display. */
    gIoNone_c               = 0x03,     /*!< No input and no display. */
    gIoKeyboardDisplay_c    = 0x04      /*!< Has keyboard input and display. */
} gapIoCapabilities_t;

/*! Flags indicating the Keys to be exchanged by the SMP during the key exchange phase of pairing. */
typedef enum gapSmpKeyFlags_tag {
    gNoKeys_c   = 0x00,     /*!< No key can be distributed. */
    gLtk_c      = BIT0,     /*!< Long Term Key. */
    gIrk_c      = BIT1,     /*!< Identity Resolving Key. */
    gCsrk_c     = BIT2      /*!< Connection Signature Resolving Key. */
} gapSmpKeyFlags_t;

/*! Structure containing the SMP information exchanged during pairing. */
typedef struct gapSmpKeys_tag {
    uint8_t     cLtkSize;   /*!< Encryption Key Size. If aLtk is NULL, this is ignored. */
    uint8_t*    aLtk;       /*!< Long Term (Encryption) Key. NULL if LTK is not distributed, else size is given by cLtkSize.*/

    uint8_t*    aIrk;       /*!< Identity Resolving Key. NULL if aIrk is not distributed. */
    uint8_t*    aCsrk;      /*!< Connection Signature Resolving Key. NULL if aCsrk is not distributed. */
   
    uint8_t     cRandSize;  /*!< Size of RAND; usually equal to gcMaxRandSize_d. If aLtk is NULL, this is ignored. */
    uint8_t*    aRand;      /*!< RAND value used to identify the LTK. If aLtk is NULL, this is ignored. */
    uint16_t    ediv;       /*!< EDIV value used to identify the LTK. If aLtk is NULL, this is ignored. */
    
    bleAddressType_t    addressType; /*!< Public or Random address. If aAddress is NULL, this is ignored. */
    uint8_t*            aAddress;    /*!< Device Address. NULL if address is not distributed. If aIrk is NULL, this is ignored. */
} gapSmpKeys_t;

/*! LE Security Mode */
typedef enum gapSecurityMode_tag {
    gSecurityMode_1_c = 0x10,   /*!< Mode 1 - Encryption required (except for Level 1). */
    gSecurityMode_2_c = 0x20    /*!< Mode 2 - Data Signing required. */
} gapSecurityMode_t;

/*! LE Security Level */
typedef enum gapSecurityLevel_tag {
    gSecurityLevel_NoSecurity_c =           0x00,  /*!< No security (combined only with Mode 1). */
    gSecurityLevel_NoMitmProtection_c =     0x01,  /*!< Unauthenticated (no MITM protection). */
    gSecurityLevel_WithMitmProtection_c =   0x02,  /*!< Authenticated (MITM protection by PIN or OOB). */
    gSecurityLevel_LeSecureConnections_c =  0x03   /*!< Authenticated with LE Secure Connections (BLE 4.2 only). */
} gapSecurityLevel_t;

/*! Security Mode-and-Level definitions */
typedef enum gapSecurityModeAndLevel_tag {
    gSecurityMode_1_Level_1_c = (uint8_t)gSecurityMode_1_c | (uint8_t)gSecurityLevel_NoSecurity_c,          /*!< Mode 1 Level 1 - No Security. */
    gSecurityMode_1_Level_2_c = (uint8_t)gSecurityMode_1_c | (uint8_t)gSecurityLevel_NoMitmProtection_c,    /*!< Mode 1 Level 2 - Encryption without authentication. */
    gSecurityMode_1_Level_3_c = (uint8_t)gSecurityMode_1_c | (uint8_t)gSecurityLevel_WithMitmProtection_c,  /*!< Mode 1 Level 3 - Encryption with authentication. */
    gSecurityMode_1_Level_4_c = (uint8_t)gSecurityMode_1_c | (uint8_t)gSecurityLevel_LeSecureConnections_c, /*!< Mode 1 Level 4 - Encryption with LE Secure Connections pairing (BLE 4.2 only). */
    gSecurityMode_2_Level_1_c = (uint8_t)gSecurityMode_2_c | (uint8_t)gSecurityLevel_NoMitmProtection_c,    /*!< Mode 2 Level 1 - Data Signing without authentication. */
    gSecurityMode_2_Level_2_c = (uint8_t)gSecurityMode_2_c | (uint8_t)gSecurityLevel_WithMitmProtection_c   /*!< Mode 2 Level 2 - Data Signing with authentication. */
} gapSecurityModeAndLevel_t;
    
/*! Security Requirements structure for a Device, a Service or a Characteristic */
typedef struct gapSecurityRequirements_tag {
    gapSecurityModeAndLevel_t   securityModeLevel;          /*!< Security mode and level. */
    bool_t                      authorization;              /*!< Authorization required. */
    uint16_t                    minimumEncryptionKeySize;   /*!< Minimum encryption key (LTK) size. */
} gapSecurityRequirements_t;

/*! Service Security Requirements */
typedef struct gapServiceSecurityRequirements_tag {
    uint16_t                    serviceHandle;  /*!< Handle of the Service declaration in the GATT Database. */
    gapSecurityRequirements_t   requirements;   /*!< Requirements for all attributes in this service. */
} gapServiceSecurityRequirements_t;

/*! Device Security - Master Security Requirements + Service Security Requirements */
typedef struct gapDeviceSecurityRequirements_tag {
    gapSecurityRequirements_t*          pMasterSecurityRequirements;    /*!< Security requirements added to all services. */
    uint8_t                             cNumServices;                   /*!< Number of service-specific requirements; must be less than or equal to gcMaxServiceSpecificSecurityRequirements_d. */
    gapServiceSecurityRequirements_t*   aServiceSecurityRequirements;   /*!< Array of service-specific requirements. */
} gapDeviceSecurityRequirements_t;

/*! Keypress Notification Types */
typedef enum gapKeypressNotification_tag
{
    gKnPasskeyEntryStarted_c,   /*!< Start of the Passkey Entry. */
    gKnPasskeyDigitStarted_c,   /*!< Digit entered. */
    gKnPasskeyDigitErased_c,    /*!< Digit erased. */
    gKnPasskeyCleared_c,        /*!< Passkey cleared. */
    gKnPasskeyEntryCompleted_c  /*!< Passkey Entry completed. */
} gapKeypressNotification_t;

/*! List of Attribute Handles for authorization lists. */
typedef struct gapHandleList_tag {
    uint8_t     cNumHandles;                            /*!< Number of handles in this list. */
    uint16_t    aHandles[gcGapMaxAuthorizationHandles_c];  /*!< List of handles. */
} gapHandleList_t;

/*! Connection Security Information structure */
typedef struct gapConnectionSecurityInformation_tag {
    bool_t                      authenticated;      /*!< TRUE if pairing was performed with MITM protection. */
#if gcGapMaxAuthorizationHandles_c > 0
    gapHandleList_t             authorizedToRead;   /*!< List of handles the peer has been authorized to read. */
    gapHandleList_t             authorizedToWrite;  /*!< List of handles the peer has been authorized to write. */
#endif
} gapConnectionSecurityInformation_t;

/*! Pairing parameters structure for the Gap_Pair and Gap_AcceptPairingRequest APIs */
typedef struct gapPairingParameters_tag {
    bool_t                      withBonding;            /*!< TRUE if this device is able to and wants to bond after pairing, FALSE otherwise. */
    gapSecurityModeAndLevel_t   securityModeAndLevel;   /*!< The desired security mode-level. */
    uint8_t                     maxEncryptionKeySize;   /*!< Maximum LTK size supported by the device. */
    gapIoCapabilities_t         localIoCapabilities;    /*!< I/O capabilities used to determine the pairing method. */
    bool_t                      oobAvailable;           /*!< TRUE if this device has Out-of-Band data that can be used for authenticated pairing. FALSE otherwise. */
    gapSmpKeyFlags_t            centralKeys;            /*!< Indicates the SMP keys to be distributed by the Central. */
    gapSmpKeyFlags_t            peripheralKeys;         /*!< Indicates the SMP keys to be distributed by the Peripheral. */
    bool_t                      leSecureConnectionSupported;    /*!< In BLE 4.2, indicates if device supports LE Secure Connections pairing. */
    bool_t                      useKeypressNotifications;       /*!< In BLE 4.2, indicates if device supports Keypress Notification PDUs during Passkey Entry pairing. */
} gapPairingParameters_t;

/*! Parameters of a Slave Security Request. */
typedef struct gapSlaveSecurityRequestParameters_tag {
    bool_t                      bondAfterPairing;       /*!< TRUE if the Slave supports bonding. */
    bool_t                      authenticationRequired; /*!< TRUE if the Slave requires authentication for MITM protection. */
} gapSlaveSecurityRequestParameters_t;

/*! Reason for rejecting the pairing request. These values are
 * equal to the corresponding reasons from SMP. */
typedef enum gapAuthenticationRejectReason_tag {
    gLinkEncryptionFailed_c         = 0xF0,     /*!< Link could not be encrypted. This reason may not be used by Gap_RejectPairing! */

    gOobNotAvailable_c              = 0x02,     /*!< This device does not have the required OOB for authenticated pairing. */
    gIncompatibleIoCapabilities_c   = 0x03,     /*!< The combination of I/O capabilities does not allow pairing with the desired level of security. */
    gPairingNotSupported_c          = 0x05,     /*!< This device does not support pairing. */
    gLowEncryptionKeySize_c         = 0x06,     /*!< The peer's encryption key size is too low for this device's required security level. */
    gRepeatedAttempts_c             = 0x09,     /*!< This device is the target of repeated unsuccessful pairing attempts and does not allow further pairing attempts at the moment.  */
    gUnspecifiedReason_c            = 0x08      /*!< The host has rejected the pairing for an unknown reason. */
} gapAuthenticationRejectReason_t;

/*! Scan Mode options; used as parameter for Gap_SetScanMode. */
typedef enum gapScanMode_tag {
    gDefaultScan_c,         /*!< Reports all scanned devices to the application. */
    gLimitedDiscovery_c,    /*!< Reports only devices in Limited Discoverable Mode, i.e., containing the Flags AD with the LE Limited Discoverable Flag set. */
    gGeneralDiscovery_c,    /*!< Reports only devices in General Discoverable Mode, i.e., containing the Flags AD with the LE General Discoverable Flag set. */
    gAutoConnect_c          /*!< Automatically connects with devices with known addresses and does not report any scanned device to the application. */
} gapScanMode_t;

/*! Advertising Channel Map flags - setting a bit activates advertising on the respective channel. */
typedef enum {
    gAdvChanMapFlag37_c        = BIT0,   /*!< Bit for channel 37. */
    gAdvChanMapFlag38_c        = BIT1,   /*!< Bit for channel 38. */
    gAdvChanMapFlag39_c        = BIT2    /*!< Bit for channel 39. */
} gapAdvertisingChannelMapFlags_t;

/*! Advertising Filter Policy values */
typedef enum {
    gProcessAll_c                    = 0x00,     /*!< Default value: accept all connect and scan requests. */
    gProcessConnAllScanWL_c          = 0x01,     /*!< Accept all connect requests, but scan requests only from devices in White List. */
    gProcessScanAllConnWL_c          = 0x02,     /*!< Accept all scan requests, but connect requests only from devices in White List. */
    gProcessWhiteListOnly_c          = 0x03,     /*!< Accept connect and scan requests only from devices in White List. */
} gapAdvertisingFilterPolicy_t;
    
/*! Advertising Parameters; for defaults see gGapDefaultAdvertisingParameters_d. */
typedef struct gapAdvertisingParameters_tag {
    uint16_t                            minInterval;            /*!< Minimum desired advertising interval. Default: 1.28 s. */
    uint16_t                            maxInterval;            /*!< Maximum desired advertising interval. Default: 1.28 s. */
    bleAdvertisingType_t                advertisingType;        /*!< Advertising type. Default: connectable undirected. */
    bleAddressType_t                    ownAddressType;         /*!< Indicates whether the advertising address is the public address (BD_ADDR) or the random address (set by Gap_SetRandomAddress). Default: public address.
                                                                     If BLE 4.2 Controller Privacy is enabled, this parameter is irrelevant as Private Resolvable Addresses are always used. */
    bleAddressType_t                    peerAddressType;        /*!< Address type of the peer; only used in directed advertising and Enhanced Privacy (BLE 4.2). */
    bleDeviceAddress_t                  peerAddress;            /*!< Address of the peer; same as above. */
    gapAdvertisingChannelMapFlags_t     channelMap;             /*!< Bit mask indicating which of the three advertising channels are used. Default: all three. */
    gapAdvertisingFilterPolicy_t        filterPolicy;           /*!< Indicates whether the connect and scan requests are filtered using the White List. Default: does not use White List (process all). */
} gapAdvertisingParameters_t;

/*
*
* Scanning Parameters
*
*/

/*! Scanning parameters; for defaults see gGapDefaultScanningParameters_d. */
typedef struct gapScanningParameters_tag {
    bleScanType_t               type;               /*!< Scanning type. Default: passive. */
    uint16_t                    interval;           /*!< Scanning interval. Default: 10 ms. */
    uint16_t                    window;             /*!< Scanning window. Default: 10 ms. */
    bleAddressType_t            ownAddressType;     /*!< Indicates whether the address used in scan requests is the public address (BD_ADDR) or the random address (set by Gap_SetRandomAddress). Default: public address. 
                                                         If BLE 4.2 Controller Privacy is enabled, this parameter is irrelevant as Private Resolvable Addresses are always used. */
    bleScanningFilterPolicy_t   filterPolicy;       /*!< Indicates whether the advertising packets are filtered using the White List. Default: does not use White List (scan all). */
} gapScanningParameters_t;

/*
*
* Connection Parameters
*
*/

/*! Connection request parameter structure to be used in the Gap_Connect function; for API-defined defaults, use gGapDefaultConnectionRequestParameters_d. */
typedef struct gapConnectionRequestParameters_tag {
    uint16_t                    scanInterval;           /*!< Scanning interval. Default: 10 ms. */
    uint16_t                    scanWindow;             /*!< Scanning window. Default: 10 ms. */
    bleInitiatorFilterPolicy_t  filterPolicy;           /*!< Indicates whether the connection request is issued for a specific device or for all the devices in the White List. Default: specific device.*/
    bleAddressType_t            ownAddressType;         /*!< Indicates whether the address used in connection requests is the public address (BD_ADDR) or the random address (set by Gap_SetRandomAddress). Default: public address. */
    bleAddressType_t            peerAddressType;        /*!< When connecting to a specific device (see filterPolicy), this indicates that device's address type. Default: public address. */
    bleDeviceAddress_t          peerAddress;            /*!< When connecting to a specific device (see filterPolicy), this indicates that device's address. */
    uint16_t                    connIntervalMin;        /*!< The minimum desired connection interval. Default: 100 ms. */
    uint16_t                    connIntervalMax;        /*!< The maximum desired connection interval. Default: 200 ms. */
    uint16_t                    connLatency;            /*!< The desired connection latency (the maximum number of consecutive connection events the Slave is allowed to ignore). Default: 0. */
    uint16_t                    supervisionTimeout;     /*!< The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped. Default: 10 s. */
    uint16_t                    connEventLengthMin;     /*!< The minimum desired connection event length. Default: 0 ms. */
    uint16_t                    connEventLengthMax;     /*!< The maximum desired connection event length. Default: maximum possible, ~41 s. (lets the Controller decide). */
    bool_t                      usePeerIdentityAddress; /*!< If Controller Privacy is enabled and this parameter is TRUE, the address defined in the peerAddressType and peerAddress is an identity address. 
                                                             Otherwise, it is a device address. */
} gapConnectionRequestParameters_t;

/*! Connection parameters as received in the gConnEvtConnected_c connection event. */
typedef struct gapConnectionParameters_tag {
    uint16_t                    connInterval;           /*!< Interval between connection events. */
    uint16_t                    connLatency;            /*!< Number of consecutive connection events the Slave may ignore. */
    uint16_t                    supervisionTimeout;     /*!< The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped. */
    bleMasterClockAccuracy_t    masterClockAccuracy;    /*!< Accuracy of master's clock, allowing for frame detection optimizations. */
} gapConnectionParameters_t;

/*
*
* Advertising and Scan Response Data
*
*/

/*! AD Type values as defined by Bluetooth SIG used when defining gapAdStructure_t structures for advertising or scan response data. */
typedef enum gapAdType_tag {
    gAdFlags_c                               = 0x01,    /*!< Defined by the Bluetooth SIG. */
    gAdIncomplete16bitServiceList_c          = 0x02,    /*!< Defined by the Bluetooth SIG. */
    gAdComplete16bitServiceList_c            = 0x03,    /*!< Defined by the Bluetooth SIG. */
    gAdIncomplete32bitServiceList_c          = 0x04,    /*!< Defined by the Bluetooth SIG. */
    gAdComplete32bitServiceList_c            = 0x05,    /*!< Defined by the Bluetooth SIG. */
    gAdIncomplete128bitServiceList_c         = 0x06,    /*!< Defined by the Bluetooth SIG. */
    gAdComplete128bitServiceList_c           = 0x07,    /*!< Defined by the Bluetooth SIG. */
    gAdShortenedLocalName_c                  = 0x08,    /*!< Defined by the Bluetooth SIG. */
    gAdCompleteLocalName_c                   = 0x09,    /*!< Defined by the Bluetooth SIG. */
    gAdTxPowerLevel_c                        = 0x0A,    /*!< Defined by the Bluetooth SIG. */
    gAdClassOfDevice_c                       = 0x0D,    /*!< Defined by the Bluetooth SIG. */
    gAdSimplePairingHashC192_c               = 0x0E,    /*!< Defined by the Bluetooth SIG. */
    gAdSimplePairingRandomizerR192_c         = 0x0F,    /*!< Defined by the Bluetooth SIG. */
    gAdSecurityManagerTkValue_c              = 0x10,    /*!< Defined by the Bluetooth SIG. */
    gAdSecurityManagerOobFlags_c             = 0x11,    /*!< Defined by the Bluetooth SIG. */
    gAdSlaveConnectionIntervalRange_c        = 0x12,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceSolicitationList16bit_c        = 0x14,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceSolicitationList32bit_c        = 0x1F,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceSolicitationList128bit_c       = 0x15,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceData16bit_c                    = 0x16,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceData32bit_c                    = 0x20,    /*!< Defined by the Bluetooth SIG. */
    gAdServiceData128bit_c                   = 0x21,    /*!< Defined by the Bluetooth SIG. */
    gAdPublicTargetAddress_c                 = 0x17,    /*!< Defined by the Bluetooth SIG. */
    gAdRandomTargetAddress_c                 = 0x18,    /*!< Defined by the Bluetooth SIG. */
    gAdAppearance_c                          = 0x19,    /*!< Defined by the Bluetooth SIG. */
    gAdAdvertisingInterval_c                 = 0x1A,    /*!< Defined by the Bluetooth SIG. */
    gAdLeDeviceAddress_c                     = 0x1B,    /*!< Defined by the Bluetooth SIG. */
    gAdLeRole_c                              = 0x1C,    /*!< Defined by the Bluetooth SIG. */
    gAdSimplePairingHashC256_c               = 0x1D,    /*!< Defined by the Bluetooth SIG. */
    gAdSimplePairingRandomizerR256_c         = 0x1E,    /*!< Defined by the Bluetooth SIG. */
    gAd3dInformationData_c                   = 0x3D,    /*!< Defined by the Bluetooth SIG. */
    gAdManufacturerSpecificData_c            = 0xFF     /*!< Defined by the Bluetooth SIG. */
} gapAdType_t;

/*! Values of the AD Flags advertising data structure. */
typedef enum gapAdTypeFlags_tag {
    gNone_c                                     = 0x00,     /*!< No information. */
    gLeLimitedDiscoverableMode_c                = BIT0,     /*!< This device is in Limited Discoverable mode. */
    gLeGeneralDiscoverableMode_c                = BIT1,     /*!< This device is in General Discoverable mode. */
    gBrEdrNotSupported_c                        = BIT2,     /*!< This device supports only Bluetooth Low Energy; no support for Classic Bluetooth. */
    gSimultaneousLeBrEdrCapableController_c     = BIT3,     /*!< This device's Controller also supports Classic Bluetooth. */
    gSimultaneousLeBrEdrCapableHost_c           = BIT4,     /*!< This device's Host also supports Classic Bluetooth. */
} gapAdTypeFlags_t;

/*! Definition of an AD Structure as contained in Advertising and Scan Response packets. An Advertising or Scan Response packet contains several AD Structures. */
typedef struct gapAdStructure_tag
{
    uint8_t         length;     /*!< Total length of the [adType + aData] fields. Equal to 1 + lengthOf(aData). */
    gapAdType_t     adType;     /*!< AD Type of this AD Structure. */
    uint8_t*        aData;      /*!< Data contained in this AD Structure; length of this array is equal to (gapAdStructure_t.length - 1). */
} gapAdStructure_t;

/*! Advertising Data structure : a list of several gapAdStructure_t structures. */
typedef struct gapAdvertisingData_tag {
    uint8_t             cNumAdStructures;   /*!< Number of AD Structures. */
    gapAdStructure_t*   aAdStructures;      /*!< Array of AD Structures. */
} gapAdvertisingData_t;

/*! Scan Response Data structure : a list of several gapAdStructure_t structures. */
typedef gapAdvertisingData_t gapScanResponseData_t;

/*! Enumeration used by the Gap_ReadRadioPowerLevel function. */
typedef enum gapRadioPowerLevelReadType_tag {
    gTxPowerCurrentLevelInConnection_c = gReadCurrentTxPowerLevel_c,        /*!< Reading the instantaneous TX power level in a connection. */
    gTxPowerMaximumLevelInConnection_c = gReadMaximumTxPowerLevel_c,        /*!< Reading the maximum TX power level achieved during a connection. */
    gTxPowerLevelForAdvertising_c,                                          /*!< Reading the TX power on the advertising channels. */
    gRssi_c                                                                 /*!< Reading the Received Signal Strength Indication in a connection. */
} gapRadioPowerLevelReadType_t;

/*! Enumeration for Controller Test commands. */
typedef enum gapControllerTestCmd_tag
{
    gControllerTestCmdStartRx_c,    /*!< Start Receiver Test. */
    gControllerTestCmdStartTx_c,    /*!< Start Transmitter Test. */
    gControllerTestCmdEnd_c,        /*!< End Test. */
} gapControllerTestCmd_t;

/*! Enumeration for Controller Transmitter Test payload types. */
typedef enum gapControllerTestTxType_tag
{
    gControllerTestTxPrbs9_c,   /*!< PRBS9 sequence ‘11111111100000111101…’ */
    gControllerTestTxF0_c,      /*!< Repeated ‘11110000’ */
    gControllerTestTxAA_c,      /*!< Repeated ‘10101010’ */
    gControllerTestTxPrbs15_c,  /*!< PRBS15 sequence */
    gControllerTestTxFF_c,      /*!< Repeated ‘11111111’ */
    gControllerTestTx00_c,      /*!< Repeated ‘00000000’ */
    gControllerTestTx0F_c,      /*!< Repeated ‘00001111’ */
    gControllerTestTx55_c,      /*!< Repeated ‘01010101’ */
} gapControllerTestTxType_t;    /*!<  */

/*
*
* GAP Events
*
*/

/* Advertising events */

/*! Advertising event type enumeration, as contained in the gapAdvertisingEvent_t. */
typedef enum gapAdvertisingEventType_tag {
    gAdvertisingStateChanged_c,     /*!< Event received when advertising has been successfully enabled or disabled. */
    gAdvertisingCommandFailed_c,    /*!< Event received when advertising could not be enabled or disabled. Reason contained in gapAdvertisingEvent_t.eventData.failReason. */
} gapAdvertisingEventType_t;

/*! Advertising event structure: type + data. */
typedef struct gapAdvertisingEvent_tag {
    gapAdvertisingEventType_t eventType;    /*!< Event type. */
    union {
        bleResult_t  failReason;    /*!< Event data for gAdvertisingCommandFailed_c event type: reason of failure to enable or disable advertising. */
    } eventData;                            /*!< Event data, to be interpreted according to gapAdvertisingEvent_t.eventType. */
} gapAdvertisingEvent_t;

/* Scanning events */

/*! Scanning event type enumeration, as contained in the gapScanningEvent_t. */
typedef enum gapScanningEventType_tag {
    gScanStateChanged_c,    /*!< Event received when scanning had been successfully enabled or disabled. */
    gScanCommandFailed_c,   /*!< Event received when scanning could not be enabled or disabled. Reason contained in gapScanningEvent_t.eventData.failReason. */
    gDeviceScanned_c        /*!< Event received when an advertising device has been scanned. Device data contained in gapScanningEvent_t.eventData.scannedDevice. */
} gapScanningEventType_t;

/*! Scanned device information structure, obtained from LE Advertising Reports. */
typedef struct gapScannedDevice_tag {
    bleAddressType_t                addressType;    /*!< Device's advertising address type. */
    bleDeviceAddress_t              aAddress;       /*!< Device's advertising address. */
    int8_t                          rssi;           /*!< RSSI on the advertising channel; may be compared to the TX power contained in the AD Structure of type gAdTxPowerLevel_c to estimate distance from the advertiser.  */
    uint8_t                         dataLength;     /*!< Length of the advertising or scan response data. */
    uint8_t*                        data;           /*!< Advertising or scan response data. */
    bleAdvertisingReportEventType_t advEventType;   /*!< Advertising report type, indicating what type of event generated this data (advertising, scan response). */
    bool_t                          directRpaUsed;  /*!< TRUE if directed advertising with Resolvable Private Address as Direct Address was detected while Enhanced Privacy is enabled.  */
    bleDeviceAddress_t              directRpa;      /*!< Resolvable Private Address set as Direct Address for directed advertising. Valid only when directRpaUsed is TRUE. */
    bool_t                          advertisingAddressResolved;  /*!< If this is TRUE, the address contained in the addressType and aAddress fields is the identity address of a resolved RPA from the Advertising Address field.
                                                                      Otherwise, the adress from the respective fields is the public or random device address contained in the Advertising Address field. */
} gapScannedDevice_t;

/*! Scanning event structure: type + data. */
typedef struct gapScanningEvent_tag {
    gapScanningEventType_t eventType;   /*!< Event type. */
    union {
        bleResult_t         failReason;     /*!< Event data for gScanCommandFailed_c event type: reason of failure to enable or disable scanning. */
        gapScannedDevice_t  scannedDevice;  /*!< Event data for gGapScanEventDeviceScanned_c event type: scanned device information. */
    } eventData;                        /*!< Event data, to be interpreted according to gapScanningEvent_t.eventType. */
} gapScanningEvent_t;

/* Connection events */

/*! Connection event type enumeration, as contained in the gapConnectionEvent_t. */
typedef enum gapConnectionEventType_tag {
    gConnEvtConnected_c,                    /*!< A connection has been established. Data in gapConnectionEvent_t.eventData.connectedEvent. */
    gConnEvtPairingRequest_c,               /*!< A pairing request has been received from the peer Master. Data in gapConnectionEvent_t.eventData.pairingEvent. */
    gConnEvtSlaveSecurityRequest_c,         /*!< A Slave Security Request has been received from the peer Slave. Data in gapConnectionEvent_t.eventData.slaveSecurityRequestEvent. */
    gConnEvtPairingResponse_c,              /*!< A pairing response has been received from the peer Slave. Data in gapConnectionEvent_t.eventData.pairingEvent. */
    gConnEvtAuthenticationRejected_c,       /*!< A link encryption or pairing request has been rejected by the peer Slave. Data in gapConnectionEvent_t.eventData.authenticationRejectedEvent. */
    gConnEvtPasskeyRequest_c,               /*!< Peer Slave has requested a passkey (maximum 6 digit PIN) for the pairing procedure. Master should respond with Gap_EnterPasskey. Slave will not receive this event! Slave's application must call Gap_SetLocalPasskey before any connection. */
    gConnEvtOobRequest_c,                   /*!< Out-of-Band data must be provided for the pairing procedure. Master or Slave should respond with Gap_ProvideOob. */
    gConnEvtPasskeyDisplay_c,               /*!< The pairing procedure requires this Slave to display the passkey for the Master's user. */
    gConnEvtKeyExchangeRequest_c,           /*!< The pairing procedure requires the SMP keys to be distributed to the peer. Data in gapConnectionEvent_t.eventData.keyExchangeRequestEvent. */
    gConnEvtKeysReceived_c,                 /*!< SMP keys distributed by the peer during pairing have been received. Data in gapConnectionEvent_t.eventData.keysReceivedEvent. */
    gConnEvtLongTermKeyRequest_c,           /*!< The bonded peer Master has requested link encryption and the LTK must be provided. Slave should respond with Gap_ProvideLongTermKey. Data in gapConnectionEvent_t.eventData.longTermKeyRequestEvent. */
    gConnEvtEncryptionChanged_c,            /*!< Link's encryption state has changed, e.g., during pairing or after a reconnection with a bonded peer. Data in gapConnectionEvent_t.eventData.encryptionChangedEvent. */
    gConnEvtPairingComplete_c,              /*!< Pairing procedure is complete, either successfully or with failure. Data in gapConnectionEvent_t.eventData.pairingCompleteEvent. */
    gConnEvtDisconnected_c,                 /*!< A connection has been terminated. Data in gapConnectionEvent_t.eventData.disconnectedEvent. */
    gConnEvtRssiRead_c,                     /*!< RSSI for an active connection has been read. Data in gapConnectionEvent_t.eventData.rssi_dBm. */
    gConnEvtTxPowerLevelRead_c,             /*!< TX power level for an active connection has been read. Data in gapConnectionEvent_t.eventData.txPowerLevel_dBm. */
    gConnEvtPowerReadFailure_c,             /*!< Power reading could not be performed. Data in gapConnectionEvent_t.eventData.failReason. */
    gConnEvtParameterUpdateRequest_c,       /*!< A connection parameter update request has been received. Data in gapConnectionEvent_t.eventData.connectionUpdateRequest. */
    gConnEvtParameterUpdateComplete_c,      /*!< The connection has new parameters. Data in gapConnectionEvent_t.eventData.connectionUpdateComplete. */      
    gConnEvtLeDataLengthChanged_c,          /*!< The new TX/RX Data Length paramaters. Data in gapConnectionEvent_t.eventData.rssi_dBm.leDataLengthChanged. */
    gConnEvtLeScOobDataRequest_c,           /*!< Event sent to request LE SC OOB Data (r, Cr and Addr) received from a peer. */
    gConnEvtLeScDisplayNumericValue_c,      /*!< Event sent to display and confirm a Numeric Comparison Value when using the LE SC Numeric Comparison pairing method. */
    gConnEvtLeScKeypressNotification_c,     /*!< Remote Keypress Notification recieved during Passkey Entry Pairing Method. */
} gapConnectionEventType_t;

/*! Event data structure for the gConnEvtConnected_c event. */
typedef struct gapConnectedEvent_tag {
    gapConnectionParameters_t   connParameters;         /*!< Connection parameters established by the Controller. */
    bleAddressType_t            peerAddressType;        /*!< Connected device's address type. */
    bleDeviceAddress_t          peerAddress;            /*!< Connected device's address. */
    bool_t                      peerRpaResolved;        /*!< If this is TRUE, the address defined by peerAddressType and peerAddress is the identity address of the peer, and the peer used an RPA
                                                             that was resolved by the Controller and is contained in the peerRpa field. Otherwise, it is a device address. This parameter is irrelevant
                                                             if BLE 4.2 Controller Privacy is not enabled. */
    bleDeviceAddress_t          peerRpa;                /*!< Peer Resolvable Private Address if Controller Privacy is active and peerRpaResolved is TRUE. */
    bool_t                      localRpaUsed;           /*!< If this is TRUE, the Controller has used an RPA contained in the localRpa field. This parameter is irrelevant
                                                             if BLE 4.2 Controller Privacy is not enabled. */
    bleDeviceAddress_t          localRpa;               /*!< Local Resolvable Private Address if Controller Privacy is active and localRpaUsed is TRUE. */    
} gapConnectedEvent_t;

/*! Event data structure for the gConnEvtKeyExchangeRequest_c event. */
typedef struct gapKeyExchangeRequestEvent_tag {
    gapSmpKeyFlags_t    requestedKeys;      /*!< Mask identifying the keys being requested. */
    uint8_t             requestedLtkSize;   /*!< Requested size of the encryption key. */
} gapKeyExchangeRequestEvent_t;

/*! Event data structure for the gConnEvtKeysReceived_c event. */
typedef struct gapKeysReceivedEvent_tag {
    gapSmpKeys_t*        pKeys;   /*!< The SMP keys distributed by the peer. */
} gapKeysReceivedEvent_t;

/*! Event data structure for the gConnEvtAuthenticationRejected_c event. */
typedef struct gapAuthenticationRejectedEvent_tag {
    gapAuthenticationRejectReason_t rejectReason;   /*!< Slave's reason for rejecting the authentication. */
} gapAuthenticationRejectedEvent_t;

/*! Event data structure for the gConnEvtPairingComplete_c event. */
typedef struct gapPairingCompleteEvent_tag {
    bool_t    pairingSuccessful;    /*!< TRUE if pairing succeeded, FALSE otherwise. */
    union {
        bool_t      withBonding;        /*!< If pairingSuccessful is TRUE, this indicates whether the devices bonded. */
        bleResult_t failReason;         /*!< If pairingSuccessful is FALSE, this contains the reason of failure. */
    } pairingCompleteData;          /*!< Information of completion, selected upon the value of gapPairingCompleteEvent_t.pairingSuccessful. */
} gapPairingCompleteEvent_t;

/*! Event data structure for the gConnEvtLongTermKeyRequest_c event. */
typedef struct gapLongTermKeyRequestEvent_tag {
    uint16_t ediv;                          /*!< The Encryption Diversifier, as defined by the SMP. */
    uint8_t  aRand[gcSmpMaxRandSize_c];    /*!< The Random number, as defined by the SMP.  */
    uint8_t  randSize;                      /*!< Usually equal to gcMaxRandSize_d. */
} gapLongTermKeyRequestEvent_t;

/*! Event data structure for the gConnEvtEncryptionChanged_c event. */
typedef struct gapEncryptionChangedEvent_tag {
    bool_t    newEncryptionState;   /*!< TRUE if link has been encrypted, FALSE if encryption was paused or removed. */
} gapEncryptionChangedEvent_t;

/*! Disconnection reason alias - reasons are contained in HCI error codes. */
typedef bleResult_t gapDisconnectionReason_t;

/*! Event data structure for the gConnEvtDisconnected_c event. */
typedef struct gapDisconnectedEvent_tag {
    gapDisconnectionReason_t    reason;     /*!< Reason for disconnection. */
} gapDisconnectedEvent_t;

/*! Event data structure for the gConnEvtParameterUpdateRequest_c event. */
typedef struct gapConnParamsUpdateReq_tag {
    uint16_t    intervalMin;        /*!< Minimum interval between connection events. */
    uint16_t    intervalMax;        /*!< Maximum interval between connection events. */
    uint16_t    slaveLatency;       /*!< Number of consecutive connection events the Slave may ignore. */
    uint16_t    timeoutMultiplier;  /*!< The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped. */
} gapConnParamsUpdateReq_t;

/*! Event data structure for the gConnEvtParameterUpdateComplete_c event. */
typedef struct gapConnParamsUpdateComplete_tag {
    bleResult_t status;
    uint16_t    connInterval;       /*!< Interval between connection events. */
    uint16_t    connLatency;        /*!< Number of consecutive connection events the Slave may ignore. */
    uint16_t    supervisionTimeout; /*!< The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped. */
} gapConnParamsUpdateComplete_t;

/*! Event data structure for the gConnEvtLeDataLengthChanged_c event. */
typedef struct gapConnLeDataLengthChanged_tag {
    uint16_t    maxTxOctets;       /*!< The maximum number of payload octets in a Link Layer Data Channel PDU to transmit on this connection. */
    uint16_t    maxTxTime;         /*!< The maximum time that the local Controller will take to send a Link Layer Data Channel PDU on this connection. */
    uint16_t    maxRxOctets;       /*!< The maximum number of payload octets in a Link Layer Data Channel PDU to receive on this connection. */
    uint16_t    maxRxTime;         /*!< The maximum time that the local Controller will take to receive a Link Layer Data Channel PDU on this connection. */
} gapConnLeDataLengthChanged_t;

/*! Connection event structure: type + data. */
typedef struct gapConnectionEvent_tag {
    gapConnectionEventType_t eventType;  /*!< Event type */
    union {
        gapConnectedEvent_t                 connectedEvent;                 /*!< Data for gConnEvtConnected_c: information about the connection parameters. */
        gapPairingParameters_t              pairingEvent;                   /*!< Data for gConnEvtPairingRequest_c, gConnEvtPairingResponse_c: pairing parameters. */
        gapAuthenticationRejectedEvent_t    authenticationRejectedEvent;    /*!< Data for gConnEvtAuthenticationRejected_c: reason for rejection. */
        gapSlaveSecurityRequestParameters_t slaveSecurityRequestEvent;      /*!< Data for gConnEvtSlaveSecurityRequest_c: Slave's security requirements. */
        gapKeyExchangeRequestEvent_t        keyExchangeRequestEvent;        /*!< Data for gConnEvtKeyExchangeRequest_c: mask indicating the keys that were requested by the peer. */
        gapKeysReceivedEvent_t              keysReceivedEvent;              /*!< Data for gConnEvtKeysReceived_c: the keys received from the peer. */
        gapPairingCompleteEvent_t           pairingCompleteEvent;           /*!< Data for gConnEvtPairingComplete_c: fail reason or (if successful) bonding state. */
        gapLongTermKeyRequestEvent_t        longTermKeyRequestEvent;        /*!< Data for gConnEvtLongTermKeyRequest_c: encryption diversifier and random number. */
        gapEncryptionChangedEvent_t         encryptionChangedEvent;         /*!< Data for gConnEvtEncryptionChanged_c: new encryption state. */
        gapDisconnectedEvent_t              disconnectedEvent;              /*!< Data for gConnEvtDisconnected_c: reason for disconnection. */
        int8_t                              rssi_dBm;                       /*!< Data for gConnEvtRssiRead_c: value of the RSSI in dBm. */
        int8_t                              txPowerLevel_dBm;               /*!< Data for gConnEvtTxPowerLevelRead_c: value of the TX power. */
        bleResult_t                         failReason;                     /*!< Data for gConnEvtPowerReadFailure_c: reason for power reading failure. */
        uint32_t                            passkeyForDisplay;
        gapConnParamsUpdateReq_t            connectionUpdateRequest;        /*!< Data for gConnEvtParameterUpdateRequest_c: connection parameters update. */
        gapConnParamsUpdateComplete_t       connectionUpdateComplete;       /*!< Data for gConnEvtParameterUpdateComplete_c: connection parameters update. */
        gapConnLeDataLengthChanged_t        leDataLengthChanged;       		/*!< Data for gConnEvtLeDataLengthChanged_c: new data length parameters */
        gapKeypressNotification_t           incomingKeypressNotification;
        uint32_t                            numericValueForDisplay;
    } eventData;                        /*!< Event data, to be interpreted according to gapConnectionEvent_t.eventType. */
} gapConnectionEvent_t;

/*! Indentity Information structure definition */
typedef struct gapIdentityInformation_tag
{
    bleIdentityAddress_t    identityAddress;        /*!< Identity Address - Public or Random Static */
    uint8_t                 irk[gcSmpIrkSize_c];    /*!< Identity Resolving Key */
} gapIdentityInformation_t;

/*
*
* GAP Callbacks
*
*/

/*! Advertising Callback prototype. */
typedef void (*gapAdvertisingCallback_t)
(
    gapAdvertisingEvent_t* pAdvertisingEvent    /*!< Advertising event. */
);

/*! Scanning Callback prototype. */
typedef void (*gapScanningCallback_t)
(
    gapScanningEvent_t* pScanningEvent          /*!< Scanning event. */
);

/*! Connection Callback prototype. */
typedef void (*gapConnectionCallback_t)
(
    deviceId_t              deviceId,           /*!< Device ID identifying the connection. */
    gapConnectionEvent_t*   pConnectionEvent    /*!< Connection event. */
);

/*! Parameters for the Auto Connect Scan Mode. */
typedef struct gapAutoConnectParams_tag {
    uint8_t                             cNumAddresses;      /*!< Number of device addresses to automatically connect to. */
    bool_t                              writeInWhiteList;   /*!< If set to TRUE, the device addresses are written in the White List before scanning is enabled. */
    gapConnectionRequestParameters_t*   aAutoConnectData;   /*!< The array of connection request parameters, of size equal to cNumAddresses. */
    gapConnectionCallback_t             connectionCallback; /*!< The callback used to receive connection events if the device auto-connects. */
} gapAutoConnectParams_t;

/*
*
* GAP Service
*
*/

/*! Appearance characteristic enumeration, also used in advertising. */
typedef enum gapAppearance_tag {
    gUnknown_c                              = 0,
    gGenericPhone_c                         = 64,
    gGenericComputer_c                      = 128,
    gGenericWatch_c                         = 192,
    gSportsWatch_c                          = 193,
    gGenericClock_c                         = 256,
    gGenericDisplay_c                       = 320,
    gGenericRemoteControl_c                 = 384,
    gGenericEyeglasses_c                    = 448,
    gGenericTag_c                           = 512,
    gGenericKeyring_c                       = 576,
    gGenericMediaPlayer_c                   = 640,
    gGenericBarcodeScanner_c                = 704,
    gGenericThermometer_c                   = 768,
    gThermometerEar_c                       = 769,
    gGenericHeartrateSensor_c               = 832,
    gHeartRateSensorHeartRateBelt_c         = 833,
    gGenericBloodPressure_c                 = 896,
    gBloodPressureArm_c                     = 897,
    gBloodPressureWrist_c                   = 898,
    gHumanInterfaceDevice_c                 = 960,
    gKeyboard_c                             = 961,
    gMouse_c                                = 962,
    gJoystick_c                             = 963,
    gGamepad_c                              = 964,
    gDigitizerTablet_c                      = 965,
    gCardReader_c                           = 966,
    gDigitalPen_c                           = 967,
    gBarcodeScanner_c                       = 968,
    gGenericGlucoseMeter_c                  = 1024,
    gGenericRunningWalkingSensor_c          = 1088,
    gRunningWalkingSensorInShoe_c           = 1089,
    gRunningWalkingSensorOnShoe_c           = 1090,
    gRunningWalkingSensorOnHip_c            = 1091,
    gGenericCycling_c                       = 1152,
    gCyclingComputer_c                      = 1153,
    gCyclingSpeedSensor_c                   = 1154,
    gCyclingCadenceSensor_c                 = 1155,
    gCyclingPowerSensor_c                   = 1156,
    gCyclingSpeedandCadenceSensor_c         = 1157,
    gGenericPulseOximeter_c                 = 3136,
    gFingertip_c                            = 3137,
    gWristWorn_c                            = 3138,
    gGenericWeightScale_c                   = 3200,
    gGenericOutdoorSportsActivity_c         = 5184,
    gLocationDisplayDevice_c                = 5185,
    gLocationandNavigationDisplayDevice_c   = 5186,
    gLocationPod_c                          = 5187,
    gLocationAndNavigationPod_c             = 5188
}gapAppearance_t;

#endif /* _GAP_TYPES_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
