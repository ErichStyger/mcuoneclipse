/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_controller_task_config.h
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

#ifndef _BLE_CONTROLLER_TASK_CONFIG_H_
#define _BLE_CONTROLLER_TASK_CONFIG_H_

/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/

/*
 * These values should be modified by the application as necessary.
 * They are used by the task initialization code from ble_controller_task.c.
 */

#ifndef gControllerTaskStackSize_c
#define gControllerTaskStackSize_c 900
#endif

#ifndef gControllerTaskPriority_c
#define gControllerTaskPriority_c 1
#endif

/* Controller configuration specifics, change at your own risk.*/

/* Time between the beginning of two consecutive advertising PDU's
 * Time = ADVERTISING_PACKET_INTERVAL * 0.625msec
 * Time range <= 10msec 
 */
#ifndef mcAdvertisingPacketInterval_c     
#define mcAdvertisingPacketInterval_c     0x08    /* 5msec */
#endif
      
/* Advertising channels that are enabled for scanning operation.
 * Range 0x01 - 0x07 
 * 0x01 - Enables channel 37 for use.
 * 0x02 - Enables channel 38 for use.
 * 0x04 - Enables channel 39 for use.
 */
#ifndef mcScanChannelMap_c 
#define mcScanChannelMap_c        0x07
#endif
      
/* Advertising channels that are enabled for initiator scanning operation.
 * Range 0x01 - 0x07 
 * 0x01 - Enables channel 37 for use.
 * 0x02 - Enables channel 38 for use.
 * 0x04 - Enables channel 39 for use.
 */
#ifndef mcInitiatorChannelMap_c 
#define mcInitiatorChannelMap_c        0x07
#endif

/* Offset to the first instant register. Units in 625uS time slots.
 * 
 * Ex. If current clock value is 0x0004 and offset is 0x0008, then
 *     the first event will begin when clock value becomes 0x000C.
 *
 * If mcOffsetToFirstInstant_c is 0xFFFF the value will be ignored 
 * and default value (0x0006) will be set.
 */ 
#ifndef mcOffsetToFirstInstant_c
#define mcOffsetToFirstInstant_c        0xFFFF
#endif

/* Default Tx Power on the advertising channel.
 * Power level as defined in the table for Controller_SetTxPowerLevel
*/ 
#ifndef mAdvertisingDefaultTxPower_c
#define mAdvertisingDefaultTxPower_c    20
#endif

/* Default Tx Power on the connection channel.
 * Power level as defined in the table for Controller_SetTxPowerLevel
*/ 
#ifndef mConnectionDefaultTxPower_c
#define mConnectionDefaultTxPower_c     20
#endif
   
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Initializes the two tasks of the BLE Host Stack.
*
* \return  osaStatus_t.
*
********************************************************************************** */
osaStatus_t Controller_TaskInit(void);

#ifdef __cplusplus
}
#endif 

#endif /* _BLE_CONTROLLER_TASK_CONFIG_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
