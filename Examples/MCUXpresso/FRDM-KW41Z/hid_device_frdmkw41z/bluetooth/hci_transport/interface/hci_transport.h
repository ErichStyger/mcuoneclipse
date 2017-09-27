/*! *********************************************************************************
* \defgroup HCI
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
* \file hci_transport.h
* This file is the interface file for the HCI Transport module
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

#ifndef _HCI_TRANSPORT_H_
#define _HCI_TRANSPORT_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "hci_types.h"

#include "SerialManager.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
#ifndef gHcitMaxPayloadLen_c
#define gHcitMaxPayloadLen_c    (gHcLeAclDataPacketLengthDefault_c + gHciAclDataPacketHeaderLength_c)
#endif

/* Enables Upward HCI Transport. 
   The controller sends HCI packets to be transported through the serial interface */
#ifndef gUseHciTransportUpward_d
#define gUseHciTransportUpward_d      0
#endif

/* Enables Downward HCI Transport. 
   The Host sends HCI packets to be transported through the serial interface */
#ifndef gUseHciTransportDownward_d
#define gUseHciTransportDownward_d    0
#endif

#if (gUseHciTransportDownward_d) && (gUseHciTransportUpward_d)
#error "Select maximum one HCI transport method!"
#endif

/* Interface configuration */
#ifndef gHcitInterfaceType_d
#define gHcitInterfaceType_d        (APP_SERIAL_INTERFACE_TYPE)
#endif

#ifndef gHcitInterfaceNumber_d
#define gHcitInterfaceNumber_d      (APP_SERIAL_INTERFACE_INSTANCE)
#endif

#ifndef gHcitInterfaceSpeed_d
#define gHcitInterfaceSpeed_d        (gUARTBaudRate115200_c)
#endif

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

typedef bleResult_t (* hciTransportInterface_t)
(
    hciPacketType_t packetType,     /*!< HCI Packet Type. */
    void* pPacket,                  /*!< Pointer to packet payload. */
    uint16_t packetSize             /*!< Packet payload size. */  
);

typedef struct hcitConfigStruct_tag
{
    serialInterfaceType_t   interfaceType;
    uint8_t                 interfaceChannel;
    uint32_t                interfaceBaudrate;
    hciTransportInterface_t transportInterface;
}hcitConfigStruct_t;

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

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
    extern "C" {
#endif

/*! *********************************************************************************
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
bleResult_t Hcit_Init(hcitConfigStruct_t* hcitConfigStruct);

/*! *********************************************************************************
* \brief  
*
* \param[in]    pPacket
* \param[in]    packetSize
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
void Hcit_SendPacket(hciPacketType_t packetType, void* pPacket, uint16_t packetSize);

/*! *********************************************************************************
* \brief  
*
* \param[in]    
*
* \param[out]   pPacket
* \param[out]   packetSize
*
* \return  
*
* \pre 
*
* \remarks 
*
********************************************************************************** */
bleResult_t Hcit_RecvPacket(void* pPacket, uint16_t packetSize);

#ifdef __cplusplus
    }
#endif 

#endif /* _HCI_TRANSPORT_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
