/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_host_tasks.c
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
#include "Messaging.h"
#include "ble_host_tasks.h"
#include "ble_host_task_config.h"
#include "fsl_os_abstraction.h"
#include "Panic.h"

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
osaTaskId_t  gHost_TaskId;
osaEventId_t gHost_TaskEvent;

msgQueue_t   gApp2Host_TaskQueue;
msgQueue_t   gHci2Host_TaskQueue;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void Host_Task(osaTaskParam_t argument);
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
OSA_TASK_DEFINE(Host_Task, gHost_TaskPriority_c, 1, gHost_TaskStackSize_c, FALSE);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

osaStatus_t Ble_HostTaskInit(void)
{     
    /* Already initialized? */
    if(gHost_TaskId)
    {      
      return osaStatus_Error;
    }
    
    /* Initialization of task related */
    gHost_TaskEvent = OSA_EventCreate(TRUE);
    if( gHost_TaskEvent == NULL)
    {
        return osaStatus_Error;
    }

    /* Initialization of task message queue */
    MSG_InitQueue ( &gApp2Host_TaskQueue );
    MSG_InitQueue ( &gHci2Host_TaskQueue );

    /* Task creation */
     
    gHost_TaskId = OSA_TaskCreate(OSA_TASK(Host_Task), NULL);
    
    if( NULL == gHost_TaskId )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }

    return osaStatus_Success;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

static void Host_Task(osaTaskParam_t argument)
{
    Host_TaskHandler((void *) NULL);    
}

/*! *********************************************************************************
* @}
********************************************************************************** */
