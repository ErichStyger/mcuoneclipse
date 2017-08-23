/*! *********************************************************************************
* \defgroup L2CA L2CAP
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

#ifndef _L2CA_INTERFACE_H
#define _L2CA_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"

#include "fsl_os_abstraction.h"

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
typedef struct l2caConfigStruct_tag
{
    /* The list of the supported LE features for the Controller */
    uint32_t    leFeatures;

    /* Maximum length (in octets) of the data portion of each HCI ACL Data Packet
        that the Controller is able to accept. */
    uint32_t    hciLeBufferSize;

    /* The maximum size of payload data in octets that the L2CAP layer entity is 
    capable of accepting. The MPS corresponds to the maximum PDU payload size. */
    uint16_t    maxPduPayloadSize;
}l2caConfigStruct_t;

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
typedef l2caGenericCallback_t   l2caAttChannelCallback_t;
typedef l2caGenericCallback_t   l2caSmpChannelCallback_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*
* L2CAP Interface Primitives
*/


bleResult_t L2ca_Init( void );

/**********************************************************************************
* \brief
*
* \param[in]
*
* \param[out]
*
* \return
*
* \pre
*
* \remarks
*
********************************************************************************** */
bleResult_t L2ca_Config
    (
        l2caConfigStruct_t* pConfigStruct
    );

/**********************************************************************************
* \brief        Sends a data packet through ATT Channel
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    pPacket             Data buffer to be transmitted
* \param[in]    packetLength        Length of the data buffer
*
* \return       Result of the operation
*
* \pre 
*
* \remarks 
*
********************************************************************************** */
bleResult_t L2ca_SendAttData
    (
        deviceId_t  deviceId,
        uint8_t*    pPacket,
        uint16_t    packetLength
    );

/**********************************************************************************
* \brief        Sends a data packet through SM Channel
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    pPacket             Data buffer to be transmitted
* \param[in]    packetLength        Length of the data buffer
*
* \return       Result of the operation
*
* \pre 
*
* \remarks 
*
********************************************************************************** */
bleResult_t L2ca_SendSmpData
    (
        deviceId_t  deviceId,
        uint8_t*    pPacket,
        uint16_t    packetLength
    );

/**********************************************************************************
* \brief        
*
* \param[in]
*
* \return       Result of the operation
*
* \pre 
*
* \remarks 
*
********************************************************************************** */
bleResult_t L2ca_RegisterAttCallback
    (
        l2caAttChannelCallback_t    pCallback
    );

/**********************************************************************************
* \brief        
*
* \param[in]
*
* \return       Result of the operation
*
* \pre 
*
* \remarks 
*
********************************************************************************** */
bleResult_t L2ca_RegisterSmpCallback
    (
        l2caSmpChannelCallback_t    pCallback
    );

void L2ca_NotifyConnection(deviceId_t deviceId);

void L2ca_NotifyDisconnection(deviceId_t deviceId);

#ifdef __cplusplus
}
#endif

#endif /* _L2CA_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
