/*! *********************************************************************************
 * \defgroup CONTROLLER
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_controller_task.c
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "Messaging.h"
#include "fsl_os_abstraction.h"
#include "fsl_device_registers.h"
#include "ble_controller_task_config.h"
#include "Panic.h"
#include "controller_interface.h"

#if gMWS_Enabled_d || gMWS_UseCoexistence_d
#include "MWS.h"
#include "fsl_xcvr.h"
#endif
/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
osaTaskId_t  gControllerTaskId;
osaEventId_t mControllerTaskEvent;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void ControllerTask(osaTaskParam_t argument);

extern void Controller_TaskHandler(void * args);
extern void Controller_InterruptHandler(void);

#if gMWS_Enabled_d
extern uint32_t MWS_BLE_Callback ( mwsEvents_t event );
#endif

#if gMWS_UseCoexistence_d
extern uint32_t MWS_COEX_BLE_Callback ( mwsEvents_t event );
#endif
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
OSA_TASK_DEFINE(ControllerTask, gControllerTaskPriority_c, 1, gControllerTaskStackSize_c, FALSE);

/* Radio system clock selection. */
#if (RF_OSC_26MHZ == 1)
const uint8_t gRfSysClk26MHz_c = 1;  /* 26MHz radio clock. */
#else
const uint8_t gRfSysClk26MHz_c = 0;  /* 32MHz radio clock. */
#endif

/* Public Device Address */
const uint8_t gBDAddress_c[6] = {BD_ADDR};
/* Time between the beginning of two consecutive advertising PDU's */
const uint8_t gAdvertisingPacketInterval_c = mcAdvertisingPacketInterval_c;
/* Advertising channels that are enabled for scanning operation. */
const uint8_t gScanChannelMap_c = mcScanChannelMap_c;
/* Advertising channels that are enabled for initiator scanning operation. */
const uint8_t gInitiatorChannelMap_c = mcInitiatorChannelMap_c;
/* Offset to the first instant register */
const uint16_t gOffsetToFirstInstant_c = mcOffsetToFirstInstant_c;

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

static void ControllerTask(osaTaskParam_t argument)
{
    Controller_TaskHandler((void *) NULL);    
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
/**
 * \fn 		Controller_TaskInit 
 * \brief   This Function
 * \return  osa_status_t
 */
osaStatus_t Controller_TaskInit(void)
{	  
    
    /* Initialization of task related objects */
    if(gControllerTaskId)
    {      
      return osaStatus_Error;
    }

    mControllerTaskEvent = OSA_EventCreate(TRUE);

    if(NULL == mControllerTaskEvent)
    {
        return osaStatus_Error;
    }
    
    /* Task creation */
    gControllerTaskId = OSA_TaskCreate(OSA_TASK(ControllerTask), NULL);
    if( NULL == gControllerTaskId )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }

#if (defined(CPU_MKW20Z160VHT4) || defined(CPU_MKW30Z160VHM4) || defined(CPU_MKW40Z160VHT4))
    OSA_InstallIntHandler(BTLL_RSIM_IRQn, &Controller_InterruptHandler);
  
    NVIC_ClearPendingIRQ(BTLL_RSIM_IRQn);
    NVIC_EnableIRQ(BTLL_RSIM_IRQn);
    NVIC_SetPriority(BTLL_RSIM_IRQn, 0xC0);
    
#elif (defined(CPU_MKW21Z256VHT4) || defined(CPU_MKW21Z512VHT4) || defined(CPU_MKW31Z256CAx4) || \
    defined(CPU_MKW31Z256VHT4) || defined(CPU_MKW31Z512CAx4) || defined(CPU_MKW31Z512VHT4) || \
    defined(CPU_MKW41Z256VHT4) || defined(CPU_MKW41Z512VHT4))

    /* Select BLE protocol on RADIO0_IRQ */
    XCVR_MISC->XCVR_CTRL = (uint32_t)((XCVR_MISC->XCVR_CTRL & (uint32_t)~(uint32_t)(
                               XCVR_CTRL_XCVR_CTRL_RADIO0_IRQ_SEL_MASK
                              )) | (uint32_t)(
                               (0 << XCVR_CTRL_XCVR_CTRL_RADIO0_IRQ_SEL_SHIFT)
                              ));
    
    OSA_InstallIntHandler(Radio_0_IRQn, &Controller_InterruptHandler);
  
    NVIC_ClearPendingIRQ(Radio_0_IRQn);
    NVIC_EnableIRQ(Radio_0_IRQn);
    NVIC_SetPriority(Radio_0_IRQn, 0xC0);
    
#else
    #error "No valid CPU defined!"
#endif
    
    /* Set Default Tx Power Level */
    Controller_SetTxPowerLevel(mAdvertisingDefaultTxPower_c, gAdvTxChannel_c);
    Controller_SetTxPowerLevel(mConnectionDefaultTxPower_c, gConnTxChannel_c);

#if gMWS_Enabled_d
    MWS_Register(gMWS_BLE_c, MWS_BLE_Callback);
#endif

#if gMWS_UseCoexistence_d
    XCVR_CoexistenceInit();
    MWS_CoexistenceRegister(gMWS_BLE_c, MWS_COEX_BLE_Callback);
#endif
    
    return osaStatus_Success;
}

/*! *********************************************************************************
* @}
********************************************************************************** */
