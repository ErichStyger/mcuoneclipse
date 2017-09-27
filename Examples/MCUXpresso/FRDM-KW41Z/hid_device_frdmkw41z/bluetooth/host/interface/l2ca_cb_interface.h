/*! *********************************************************************************
* \addtogroup L2CA
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file
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

#ifndef _L2CA_CB_INTERFACE_H
#define _L2CA_CB_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"

#include "l2ca_types.h"

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
/* Result values for LE Credit Based Connection Response */
typedef enum
{
    gSuccessful_c                   = (uint16_t)0x0000,
    gLePsmNotSupported_c            = (uint16_t)0x0002,
    gNoResourcesAvailable_c         = (uint16_t)0x0004,
    gInsufficientAuthentication_c   = (uint16_t)0x0005,
    gInsufficientAuthorization_c    = (uint16_t)0x0006,
    gInsufficientEncryptionKeySize_c= (uint16_t)0x0007,
    gInsufficientEncryption_c       = (uint16_t)0x0008,
    gInvalidSourceCid_c             = (uint16_t)0x0009,
    gSourceCidAreadyAllocated_c     = (uint16_t)0x000A,
    gCommandRejected_c              = (uint16_t)0x0100,
    gResponseTimeout_c              = (uint16_t)0xFFFE
} l2caLeCbConnectionRequestResult_t;

typedef struct l2caLeCbConnectionRequest_tag
{
    deviceId_t  deviceId;
    uint16_t    lePsm;    
    uint16_t    peerMtu;
    uint16_t    peerMps;
    uint16_t    initialCredits;
} l2caLeCbConnectionRequest_t;

typedef struct l2caLeCbConnectionComplete_tag
{
    deviceId_t                          deviceId;
    uint16_t                            cId;    
    uint16_t                            peerMtu;
    uint16_t                            peerMps;
    uint16_t                            initialCredits;
    l2caLeCbConnectionRequestResult_t   result;
} l2caLeCbConnectionComplete_t;

typedef struct l2caLeCbDisconnection_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;      
} l2caLeCbDisconnection_t;

typedef struct l2caLeCbNoPeerCredits_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;    
} l2caLeCbNoPeerCredits_t;

typedef struct l2caLeCbLocalCreditsNotification_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;
    uint16_t    localCredits;
} l2caLeCbLocalCreditsNotification_t;

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
typedef l2caControlCallback_t l2caLeCbControlCallback_t;

typedef void(*l2caLeCbDataCallback_t)
                (deviceId_t deviceId,
                 uint16_t   channelId,
                 uint8_t* pPacket,
                 uint16_t packetLength);
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*
* L2CAP LE Credit Based Interface Primitives
*/

/*! *********************************************************************************
* \brief        Registers callbacks for credit based data and control events on L2CAP.
*
* \param[in]    pCallback           Callback function for data plane messages
* \param[in]    pCtrlCallback       Callback function for control plane messages
*
* \return       Result of the operation
*
********************************************************************************** */
bleResult_t L2ca_RegisterLeCbCallbacks
(
    l2caLeCbDataCallback_t      pCallback,
    l2caLeCbControlCallback_t   pCtrlCallback
);
  
/*! *********************************************************************************
* \brief        Registers the LE_PSM from the L2CAP.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM
* \param[in]    lePsmMtu            MTU of the registered PSM
*
* \return       Result of the operation
*
********************************************************************************** */
bleResult_t L2ca_RegisterLePsm
    (
        uint16_t                    lePsm,
        uint16_t                    lePsmMtu
    );

/*! *********************************************************************************
* \brief        Unregisters the LE_PSM from the L2CAP.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM
*
* \return       Result of the operation
*
* \pre          A LE_PSM must be registered a priori
*
********************************************************************************** */
bleResult_t L2ca_DeregisterLePsm
    (
        uint16_t    lePsm
    );

/*! *********************************************************************************
* \brief        Initiates a connection with a peer device for a registered LE_PSM.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    initialCredits      Initial credits
*
* \return       Result of the operation
*
* \pre          A LE_PSM must be registered a priori
*
********************************************************************************** */
bleResult_t L2ca_ConnectLePsm
    (
        uint16_t    lePsm,
        deviceId_t  deviceId,
        uint16_t    initialCredits
    );

/*! *********************************************************************************
* \brief        Disconnects a peer device for a registered LE_PSM.
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator
*
* \return       Result of the operation
*
* \pre          A connection must have already been created
*
* \remarks      Once this command is issued, all incoming data in transit for this
*               device shall be discarded and any new additional outgoing data shall
*               be discarded.
*
********************************************************************************** */
bleResult_t L2ca_DisconnectLeCbChannel
    (
        deviceId_t  deviceId,
        uint16_t    channelId
    );

/*! *********************************************************************************
* \brief        Terminates an L2CAP channel.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    refuseReason        Reason to refuse the channel creation
*
* \return       Result of the operation
*
* \remarks      This interface can be used for a connection pending creation.
*
********************************************************************************** */
bleResult_t L2ca_CancelConnection
    (
        uint16_t    lePsm,
        deviceId_t  deviceId,
        l2caLeCbConnectionRequestResult_t refuseReason
    );

/*! *********************************************************************************
* \brief        Sends a data packet through a Credit-Based Channel.
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator
* \param[in]    pPacket             Data buffer to be transmitted
* \param[in]    packetLength        Length of the data buffer
*
* \return       Result of the operation
*
* \pre          An L2CAP Credit Based connection must be in place
*
********************************************************************************** */
bleResult_t L2ca_SendLeCbData
    (
        deviceId_t  deviceId,
        uint16_t    channelId,
        uint8_t*    pPacket,
        uint16_t    packetLength
    );

/*! *********************************************************************************
* \brief        Sends credits to a device when capable of receiving additional LE-frames
*
* \param[in]    deviceId            The DeviceID to which credits are given
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator
* \param[in]    credits             Number of credits to be given
*
* \return       Result of the operation
*
* \pre          An L2CAP Credit Based connection must be in place
*
********************************************************************************** */
bleResult_t L2ca_SendLeCredit
    (
        deviceId_t  deviceId,
        uint16_t    channelId,
        uint16_t    credits
    );

#ifdef __cplusplus
}
#endif

#endif /* _L2CA_CB_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
