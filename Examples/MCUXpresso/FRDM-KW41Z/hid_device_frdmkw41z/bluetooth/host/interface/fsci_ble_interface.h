/*! *********************************************************************************
* \defgroup FSCI_BLE_INTERFACE BLE FSCI
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef _FSCI_BLE_INTERFACE_H
#define _FSCI_BLE_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "FsciInterface.h"
#include "ble_general.h"
#include "gap_interface.h"
#include "gatt_client_interface.h"
#include "gatt_server_interface.h"

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

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

/*! *********************************************************************************
* \brief   This function registers the FSCI handlers for the enabled BLE layers.
*
* \param[in]    fsciInterfaceId        The interface on which data should be printed.
*
********************************************************************************** */
void fsciBleRegister
(
    uint32_t fsciInterfaceId
);


/*! *********************************************************************************
* \brief   This function sets the HCI host to controller interface to an application  
*          desired function.
*
* \param[in]    hostToControllerInterface   The function desired by the application to be 
*                                           used as host to controller interface, or NULL.
*                                           If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetHciHostToControllerInterface
(
    hciHostToControllerInterface_t hostToControllerInterface
);


/*! *********************************************************************************
* \brief   This function sets the GAP controller callback to an application desired
*          function.
*
* \param[in]    genericCallback         The function desired by the application to be 
*                                       used as controller callback, or NULL.
*                                       If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGapGenericCallback
(
    gapGenericCallback_t genericCallback
);


/*! *********************************************************************************
* \brief   This function sets the GAP advertising callback to an application desired
*          function.
*
* \param[in]    advertisingCallback     The function desired by the application to be 
*                                       used as advertising callback, or NULL.
*                                       If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGapAdvertisingCallback
(
    gapAdvertisingCallback_t advertisingCallback
);


/*! *********************************************************************************
* \brief   This function sets the GAP connection callback to an application desired
*          function.
*
* \param[in]    connectionCallback      The function desired by the application to be 
*                                       used as connection callback, or NULL.
*                                       If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGapConnectionCallback
(
    gapConnectionCallback_t connectionCallback
);


/*! *********************************************************************************
* \brief   This function sets the GAP scanning callback to an application desired
*          function.
*
* \param[in]    scanningCallback        The function desired by the application to be 
*                                       used as scanning callback, or NULL.
*                                       If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGapScanningCallback
(
    gapScanningCallback_t scanningCallback
);


/*! *********************************************************************************
* \brief   This function sets the GATT Client procedure callback to an application desired
*          function.
*
* \param[in]    clientProcedureCallback     The function desired by the application to be 
*                                           used as Client procedure callback, or NULL.
*                                           If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGattClientProcedureCallback
(
    gattClientProcedureCallback_t clientProcedureCallback
);


/*! *********************************************************************************
* \brief   This function sets the GATT Client notification callback to an application 
*          desired function.
*
* \param[in]    clientNotificationCallback      The function desired by the application to be 
*                                               used as Client notification callback, or NULL.
*                                               If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGattClientNotificationCallback
(
    gattClientNotificationCallback_t clientNotificationCallback
);


/*! *********************************************************************************
* \brief   This function sets the GATT Client indication callback to an application 
*          desired function.
*
* \param[in]    clientIndicationCallback        The function desired by the application to be 
*                                               used as Client indication callback, or NULL.
*                                               If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGattClientIndicationCallback
(
    gattClientIndicationCallback_t clientIndicationCallback
);


/*! *********************************************************************************
* \brief   This function sets the GATT Server callback to an application desired function.
*
* \param[in]    serverCallback      The function desired by the application to be 
*                                   used as Server callback, or NULL.
*                                   If NULL, the FSCI will use an empty function.
*
********************************************************************************** */
void fsciBleSetGattServerCallback
(
    gattServerCallback_t serverCallback
);


#ifdef __cplusplus
}
#endif 

#endif /* _FSCI_BLE_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
