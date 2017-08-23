/*! *********************************************************************************
 * \defgroup GATT GATT - Generic Attribute Profile Interface
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file gatt_interface.h
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

#ifndef _GATT_INTERFACE_H_
#define _GATT_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "gatt_types.h"
#include "gap_types.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Initializes the GATT module.
*
* \remarks If the GAP module is present, this function is called internally by Ble_HostInitialize().
* Otherwise, the application must call this function once at device start-up.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t Gatt_Init(void);

/*! *********************************************************************************
* \brief  Retrieves the MTU used with a given connected device.
*
* \param[in]  deviceId The device ID of the connected peer.
* \param[out] pOutMtu  Pointer to integer to be written.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t Gatt_GetMtu
(
    deviceId_t deviceId,
    uint16_t*  pOutMtu
);


#ifdef __cplusplus
}
#endif 

#endif /* _GATT_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
