/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ApplMain.c
* This is a source file for the main application.
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
/* Drv */
#include "LED.h"
#include "Keyboard.h"

/* Fwk */
#include "fsl_os_abstraction.h"
#include "MemManager.h"
#include "TimersManager.h"
#include "RNG_Interface.h"
#include "Messaging.h"
#include "Flash_Adapter.h"
#include "SecLib.h"
#include "Panic.h"

#if gFsciIncluded_c    
#include "FsciInterface.h"
#include "FsciCommands.h"
#endif

/* KSDK */
#include "board.h"

/* Bluetooth Low Energy */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "ble_init.h"
#include "l2ca_cb_interface.h"

#ifdef cPWR_UsePowerDownMode
#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#endif
#endif

#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOSConfig.h"
#endif

#ifdef NTAG_I2C
/* NTAG middleware module */
#include "HAL_I2C_driver.h"
#include "app_ntag.h"
#endif //NTAG_I2C

#include "ApplMain.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

/* Application Events */
#define gAppEvtMsgFromHostStack_c       (1 << 0)
#define gAppEvtAppCallback_c            (1 << 1)

#ifdef FSL_RTOS_FREE_RTOS
    #if (configUSE_IDLE_HOOK)
        #define mAppIdleHook_c 1
    #endif
#endif

#ifndef mAppIdleHook_c
#define mAppIdleHook_c 0
#endif

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
/* Host to Application Messages Types */
typedef enum {
    gAppGapGenericMsg_c = 0,
    gAppGapConnectionMsg_c,
    gAppGapAdvertisementMsg_c,
    gAppGapScanMsg_c,
    gAppGattServerMsg_c,
    gAppGattClientProcedureMsg_c,
    gAppGattClientNotificationMsg_c,
    gAppGattClientIndicationMsg_c,
    gAppL2caLeDataMsg_c,
    gAppL2caLeControlMsg_c,
}appHostMsgType_tag;

typedef uint8_t appHostMsgType_t;

/* Host to Application Connection Message */
typedef struct connectionMsg_tag{
    deviceId_t              deviceId;
    gapConnectionEvent_t    connEvent;
}connectionMsg_t;

/* Host to Application GATT Server Message */
typedef struct gattServerMsg_tag{
    deviceId_t          deviceId;
    gattServerEvent_t   serverEvent;
}gattServerMsg_t;

/* Host to Application GATT Client Procedure Message */
typedef struct gattClientProcMsg_tag{
    deviceId_t              deviceId;
    gattProcedureType_t     procedureType;
    gattProcedureResult_t   procedureResult;
    bleResult_t             error;
}gattClientProcMsg_t;

/* Host to Application GATT Client Notification/Indication Message */
typedef struct gattClientNotifIndMsg_tag{
    uint8_t*    aValue;
    uint16_t    characteristicValueHandle;
    uint16_t    valueLength;
    deviceId_t  deviceId;
}gattClientNotifIndMsg_t;

/* L2ca to Application Data Message */
typedef struct l2caLeCbDataMsg_tag{
    deviceId_t  deviceId;
    uint16_t    lePsm;
    uint16_t    packetLength;
    uint8_t     aPacket[0];
}l2caLeCbDataMsg_t;

/* L2ca to Application Control Message */
typedef struct l2caLeCbControlMsg_tag{
    l2capControlMessageType_t   messageType;
    uint16_t                    padding;
    uint8_t                     aMessage[0];
}l2caLeCbControlMsg_t;

typedef struct appMsgFromHost_tag{
    appHostMsgType_t    msgType;
    union {
        gapGenericEvent_t       genericMsg;
        gapAdvertisingEvent_t   advMsg;
        connectionMsg_t         connMsg;
        gapScanningEvent_t      scanMsg;
        gattServerMsg_t         gattServerMsg;
        gattClientProcMsg_t     gattClientProcMsg;
        gattClientNotifIndMsg_t gattClientNotifIndMsg;
        l2caLeCbDataMsg_t       l2caLeCbDataMsg;
        l2caLeCbControlMsg_t    l2caLeCbControlMsg;
    } msgData;
}appMsgFromHost_t;

typedef struct appMsgCallback_tag{
    appCallbackHandler_t   handler;
    appCallbackParam_t     param;
}appMsgCallback_t;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/

#if (cPWR_UsePowerDownMode)
#if (mAppIdleHook_c)
    #define AppIdle_TaskInit()
    #define App_Idle_Task()
#else
    static osaStatus_t AppIdle_TaskInit(void);
    static void App_Idle_Task(osaTaskParam_t argument);
#endif
#endif

#if gKeyBoardSupported_d && (gKBD_KeysCount_c > 0)   
static void App_KeyboardCallBack(uint8_t events);
#endif

static void App_Thread (uint32_t param);
static void App_HandleHostMessageInput(appMsgFromHost_t* pMsg);
static void App_GenericCallback (gapGenericEvent_t* pGenericEvent);
static void App_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void App_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void App_ScanningCallback (gapScanningEvent_t* pAdvertisingEvent);
static void App_GattServerCallback (deviceId_t peerDeviceId, gattServerEvent_t* pServerEvent);
static void App_GattClientProcedureCallback
(
    deviceId_t              deviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);
static void App_GattClientNotificationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
);
static void App_GattClientIndicationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
);

static void App_L2caLeDataCallback
(
    deviceId_t deviceId,
    uint16_t   lePsm,
    uint8_t* pPacket,
    uint16_t packetLength
);

static void App_L2caLeControlCallback
(
    l2capControlMessageType_t  messageType,
    void* pMessage
);

#if !gUseHciTransportDownward_d
static void BLE_SignalFromISRCallback(void);
#endif

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
extern void BleApp_Init(void);
extern void BleApp_HandleKeys(key_event_t events);

#if gUseHciTransportUpward_d
#define BleApp_GenericCallback(param)
#else
extern void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent);
#endif

#if !gUseHciTransportDownward_d
extern void (*pfBLE_SignalFromISR)(void);
#endif /* gUseHciTransportDownward_d */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
#if (cPWR_UsePowerDownMode)
#if (!mAppIdleHook_c)
OSA_TASK_DEFINE( App_Idle_Task, gAppIdleTaskPriority_c, 1, gAppIdleTaskStackSize_c, FALSE );
osaTaskId_t gAppIdleTaskId = 0;
#endif
#endif  /* cPWR_UsePowerDownMode */
  
static osaEventId_t  mAppEvent;

/* Application input queues */
static anchor_t mHostAppInputQueue;
static anchor_t mAppCbInputQueue;

static uint8_t platformInitialized = 0;

static gapGenericCallback_t pfGenericCallback = NULL;
static gapAdvertisingCallback_t pfAdvCallback = NULL;
static gapScanningCallback_t pfScanCallback = NULL;
static gapConnectionCallback_t  pfConnCallback = NULL;
static gattServerCallback_t pfGattServerCallback = NULL;
static gattClientProcedureCallback_t pfGattClientProcCallback = NULL;
static gattClientNotificationCallback_t pfGattClientNotifCallback = NULL;
static gattClientNotificationCallback_t pfGattClientIndCallback = NULL;
static l2caLeCbDataCallback_t           pfL2caLeCbDataCallback = NULL;
static l2caLeCbControlCallback_t        pfL2caLeCbControlCallback = NULL;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
#if gRNG_HWSupport_d == gRNG_NoHWSupport_d
extern uint32_t mRandomNumber;
#endif
extern const uint8_t gUseRtos_c;
extern uint32_t NV_STORAGE_END_ADDRESS[];
extern uint32_t NV_STORAGE_START_ADDRESS[];

#ifdef NTAG_I2C
NFC_HANDLE_T ntag_handle;			 // NTAG handle
#endif // NTAG_I2C

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief  This is the first task created by the OS. This task will initialize 
*         the system
*
* \param[in]  param
*
********************************************************************************** */
void main_task(uint32_t param)
{  
    if (!platformInitialized)
    {
        uint8_t pseudoRNGSeed[20] = {0};
		
        platformInitialized = 1;
        
        hardware_init();
        
        /* Framework init */
        MEM_Init();
        TMR_Init();       
        LED_Init();
        SecLib_Init();
        
        RNG_Init();   
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[0])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[4])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[8])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[12])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[16])));
        RNG_SetPseudoRandomNoSeed(pseudoRNGSeed);
        
#if gKeyBoardSupported_d && (gKBD_KeysCount_c > 0)        
        KBD_Init(App_KeyboardCallBack);
#endif

#if gAppUseNvm_d        
        /* Initialize NV module */
        NV_Init();
#endif
        
#if !gUseHciTransportDownward_d
        pfBLE_SignalFromISR = BLE_SignalFromISRCallback;        
#endif /* !gUseHciTransportDownward_d */
        
#if (cPWR_UsePowerDownMode)
#if (!mAppIdleHook_c)
        AppIdle_TaskInit();
#endif
        PWR_Init();
        PWR_DisallowDeviceToSleep();
#else    
        Led1Flashing();	        // alone RED
        Led2Flashing();		// RGB - RED
        Led3Flashing();		// RGB - GREEN
        Led4Flashing();		// RGB - BLUE
#endif    
       
        /* Initialize peripheral drivers specific to the application */
        BleApp_Init();
            
        /* Create application event */
        mAppEvent = OSA_EventCreate(TRUE);
        if( NULL == mAppEvent )
        {
            panic(0,0,0,0);
            return;
        }
        
        /* Prepare application input queue.*/
        MSG_InitQueue(&mHostAppInputQueue);
        
        /* Prepare callback input queue.*/
        MSG_InitQueue(&mAppCbInputQueue);
        
        /* BLE Host Stack Init */
        if (Ble_Initialize(App_GenericCallback) != gBleSuccess_c)
        {
            panic(0,0,0,0);
            return;
        }

#ifdef NTAG_I2C
    	/* Initialize I2C for NTAG communication */
    	HAL_I2C_InitDevice(HAL_I2C_INIT_DEFAULT, I2C_MASTER_CLK_SRC, NTAG_I2C_MASTER_BASEADDR);
    	SystemCoreClockUpdate();

    	/* Initialize the NTAG I2C components */
    	ntag_handle = NFC_InitDevice((NTAG_ID_T)0, NTAG_I2C_MASTER_BASEADDR);
//    	HAL_ISR_RegisterCallback((ISR_SOURCE_T)0, ISR_LEVEL_LO, NULL, NULL);
#endif // NTAG_I2C
    }
    
    /* Call application task */
    App_Thread( param );
}


/*! *********************************************************************************
* \brief  This function represents the Application task. 
*         This task reuses the stack allocated for the MainThread.
*         This function is called to process all events for the task. Events 
*         include timers, messages and any other user defined events.
* \param[in]  argument
*
********************************************************************************** */
void App_Thread (uint32_t param)
{
    osaEventFlags_t event;
    
    while(1)
    { 
        OSA_EventWait(mAppEvent, osaEventFlagsAll_c, FALSE, osaWaitForever_c , &event);
        
        /* Dequeue the host to app message */
        if (event & gAppEvtMsgFromHostStack_c)
        {
            /* Pointer for storing the messages from host. */
            appMsgFromHost_t *pMsgIn = NULL;  
            
            /* Check for existing messages in queue */
            while(MSG_Pending(&mHostAppInputQueue))
            {
                pMsgIn = MSG_DeQueue(&mHostAppInputQueue);
            
                if (pMsgIn)
                {
                    /* Process it */
                    App_HandleHostMessageInput(pMsgIn);
                    
                    /* Messages must always be freed. */
                    MSG_Free(pMsgIn);
                    pMsgIn = NULL;
                }
            }
        }
        
        /* Dequeue the callback message */
        if (event & gAppEvtAppCallback_c)
        {
            /* Pointer for storing the callback messages. */
            appMsgCallback_t *pMsgIn = NULL;  
            
            /* Check for existing messages in queue */
            while(MSG_Pending(&mAppCbInputQueue))
            {
                pMsgIn = MSG_DeQueue(&mAppCbInputQueue);
            
                if (pMsgIn)
                {
                    /* Execute callback handler */
                    if (pMsgIn->handler)
                    {
                        pMsgIn->handler (pMsgIn->param);
                    }
                    
                    /* Messages must always be freed. */
                    MSG_Free(pMsgIn);
                    pMsgIn = NULL;
                }
            }
        }

        /* For BareMetal break the while(1) after 1 run */
        if( gUseRtos_c == 0 )
        {
            break;
        }
    }
}

#if (cPWR_UsePowerDownMode)

static void App_Idle(void)
{
    PWRLib_WakeupReason_t wakeupReason;
    
    if( PWR_CheckIfDeviceCanGoToSleep() )
    {
        /* Enter Low Power */
        wakeupReason = PWR_EnterLowPower();

#if gFSCI_IncludeLpmCommands_c
        /* Send Wake Up indication to FSCI */
        FSCI_SendWakeUpIndication();
#endif

#if gKBD_KeysCount_c > 0      
        /* Woke up on Keyboard Press */
        if(wakeupReason.Bits.FromKeyBoard)
        {
            KBD_SwitchPressedOnWakeUp();
            PWR_DisallowDeviceToSleep();
        }
#endif   
    }
    else
    {
        /* Enter MCU Sleep */
        PWR_EnterSleep(); 
    }
}

#endif /* cPWR_UsePowerDownMode */

#if (mAppIdleHook_c)

void vApplicationIdleHook(void)
{
#if (cPWR_UsePowerDownMode)
    App_Idle();  
#endif  
}

#else /* mAppIdleHook_c */

#if (cPWR_UsePowerDownMode)

static void App_Idle_Task(osaTaskParam_t argument)
{
    while(1)
    {           
        App_Idle();
 
        /* For BareMetal break the while(1) after 1 run */
        if (gUseRtos_c == 0)
        {
            break;
        }
    }
}

static osaStatus_t AppIdle_TaskInit(void)
{	     
    if(gAppIdleTaskId)
    {      
        return osaStatus_Error;
    }
   
    /* Task creation */
    gAppIdleTaskId = OSA_TaskCreate(OSA_TASK(App_Idle_Task), NULL);
    
    if( NULL == gAppIdleTaskId )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }

    return osaStatus_Success;
}
#endif /* cPWR_UsePowerDownMode */

#endif /* mAppIdleHook_c */

bleResult_t App_Connect(
    gapConnectionRequestParameters_t*   pParameters,
    gapConnectionCallback_t             connCallback
)
{
    pfConnCallback = connCallback;
    
    return Gap_Connect(pParameters, App_ConnectionCallback);
}

bleResult_t App_StartAdvertising(
    gapAdvertisingCallback_t    advertisingCallback,
    gapConnectionCallback_t     connectionCallback
)
{
    pfAdvCallback = advertisingCallback;
    pfConnCallback = connectionCallback;
    
    return Gap_StartAdvertising(App_AdvertisingCallback, App_ConnectionCallback);
}

bleResult_t App_StartScanning(
    gapScanningParameters_t*    pScanningParameters,
    gapScanningCallback_t       scanningCallback
)
{
    pfScanCallback = scanningCallback;
    
    return Gap_StartScanning(pScanningParameters, App_ScanningCallback);
}

bleResult_t App_RegisterGattServerCallback(gattServerCallback_t  serverCallback)
{
    pfGattServerCallback = serverCallback;
    
    return GattServer_RegisterCallback(App_GattServerCallback);
}

bleResult_t App_RegisterGattClientProcedureCallback(gattClientProcedureCallback_t  callback)
{
    pfGattClientProcCallback = callback;

    return GattClient_RegisterProcedureCallback(App_GattClientProcedureCallback);
}

bleResult_t App_RegisterGattClientNotificationCallback(gattClientNotificationCallback_t  callback)
{
    pfGattClientNotifCallback = callback;

    return GattClient_RegisterNotificationCallback(App_GattClientNotificationCallback);
}

bleResult_t App_RegisterGattClientIndicationCallback(gattClientIndicationCallback_t  callback)
{
    pfGattClientIndCallback = callback;

    return GattClient_RegisterIndicationCallback(App_GattClientIndicationCallback);
}

bleResult_t App_RegisterLeCbCallbacks
(
    l2caLeCbDataCallback_t      pCallback,
    l2caLeCbControlCallback_t   pCtrlCallback
)
{
    pfL2caLeCbDataCallback = pCallback;
    pfL2caLeCbControlCallback = pCtrlCallback;

    return L2ca_RegisterLeCbCallbacks(App_L2caLeDataCallback, App_L2caLeControlCallback);
}

bleResult_t App_PostCallbackMessage
(
    appCallbackHandler_t   handler,
    appCallbackParam_t     param
)
{
    appMsgCallback_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store the packet */
    pMsgIn = MSG_Alloc(sizeof (appMsgCallback_t));

    if (!pMsgIn)
    {
        return gBleOutOfMemory_c;
    }

    pMsgIn->handler = handler;
    pMsgIn->param = param;

    /* Put message in the Cb App queue */
    MSG_Queue(&mAppCbInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtAppCallback_c);
    
    return gBleSuccess_c;
}

void App_NvmErase(void)
{
#if gAppUseNvm_d  
    uint32_t startAddress = (uint32_t)(uint8_t*)NV_STORAGE_END_ADDRESS;
    uint32_t endAddress = (uint32_t)(uint8_t*)NV_STORAGE_START_ADDRESS;
    NV_FlashEraseSector( startAddress, endAddress - startAddress + 1);
#endif    
}

void App_NvmWrite
(
    void*    pvRamSource,
    uint32_t cDataSize
)
{
#if gAppUseNvm_d  
     uint32_t startAddress = (uint32_t)(uint8_t*)NV_STORAGE_END_ADDRESS;
    NV_FlashProgramUnaligned(startAddress, cDataSize, pvRamSource);
#endif
}

void App_NvmRead
(
    void*    pvRamDestination,
    uint32_t cDataSize
)
{
#if gAppUseNvm_d 
    NV_FlashRead(NV_STORAGE_END_ADDRESS, pvRamDestination, cDataSize);
#endif    
}
/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*****************************************************************************
* Handles all key events for this device.
* Interface assumptions: None
* Return value: None
*****************************************************************************/
#if gKeyBoardSupported_d && (gKBD_KeysCount_c > 0)   
static void App_KeyboardCallBack
  (
  uint8_t events  /*IN: Events from keyboard module  */
  )
{
    BleApp_HandleKeys(events);
}
#endif
/*****************************************************************************
* Handles all messages received from the host task.
* Interface assumptions: None
* Return value: None
*****************************************************************************/
static void App_HandleHostMessageInput(appMsgFromHost_t* pMsg)
{
    switch ( pMsg->msgType ) 
    { 
        case gAppGapGenericMsg_c:
        {
            if (pfGenericCallback)
                pfGenericCallback(&pMsg->msgData.genericMsg);
            else
                BleApp_GenericCallback(&pMsg->msgData.genericMsg);
            break;
        }
        case gAppGapAdvertisementMsg_c:
        {
            if (pfAdvCallback)
                pfAdvCallback(&pMsg->msgData.advMsg);
            break;
        }
        case gAppGapScanMsg_c:
        {
            if (pfScanCallback)
                pfScanCallback(&pMsg->msgData.scanMsg);
            break;
        }
        case gAppGapConnectionMsg_c:
        {
            if (pfConnCallback)
                pfConnCallback(pMsg->msgData.connMsg.deviceId, &pMsg->msgData.connMsg.connEvent);
            break;
        }
        case gAppGattServerMsg_c:
        {
            if (pfGattServerCallback)
                pfGattServerCallback(pMsg->msgData.gattServerMsg.deviceId, &pMsg->msgData.gattServerMsg.serverEvent);
            break;
        }
        case gAppGattClientProcedureMsg_c:
        {
            if (pfGattClientProcCallback)
                pfGattClientProcCallback(
                    pMsg->msgData.gattClientProcMsg.deviceId,
                    pMsg->msgData.gattClientProcMsg.procedureType,
                    pMsg->msgData.gattClientProcMsg.procedureResult,
                    pMsg->msgData.gattClientProcMsg.error);
            break;
        }
        case gAppGattClientNotificationMsg_c:
        {
            if (pfGattClientNotifCallback)
                pfGattClientNotifCallback(
                    pMsg->msgData.gattClientNotifIndMsg.deviceId,
                    pMsg->msgData.gattClientNotifIndMsg.characteristicValueHandle,
                    pMsg->msgData.gattClientNotifIndMsg.aValue,
                    pMsg->msgData.gattClientNotifIndMsg.valueLength);
            break;
        }
        case gAppGattClientIndicationMsg_c:
        {
            if (pfGattClientIndCallback)
                pfGattClientIndCallback(
                    pMsg->msgData.gattClientNotifIndMsg.deviceId,
                    pMsg->msgData.gattClientNotifIndMsg.characteristicValueHandle,
                    pMsg->msgData.gattClientNotifIndMsg.aValue,
                    pMsg->msgData.gattClientNotifIndMsg.valueLength);
            break;
        }
        case gAppL2caLeDataMsg_c:
        {
            if (pfL2caLeCbDataCallback)
                pfL2caLeCbDataCallback(
                    pMsg->msgData.l2caLeCbDataMsg.deviceId,
                    pMsg->msgData.l2caLeCbDataMsg.lePsm,                    
                    pMsg->msgData.l2caLeCbDataMsg.aPacket,
                    pMsg->msgData.l2caLeCbDataMsg.packetLength);
            break;
        }
        case gAppL2caLeControlMsg_c:
        {
            if (pfL2caLeCbControlCallback)
                pfL2caLeCbControlCallback(
                    pMsg->msgData.l2caLeCbControlMsg.messageType,
                    pMsg->msgData.l2caLeCbControlMsg.aMessage);
            break;
        }
        default:
        {
            break;
        }
    }   
}

static void App_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapGenericEvent_t));
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapGenericMsg_c;
    FLib_MemCpy(&pMsgIn->msgData.genericMsg, pGenericEvent, sizeof(gapGenericEvent_t));

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    uint8_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapConnectionEvent_t);
    
    if(pConnectionEvent->eventType == gConnEvtKeysReceived_c)
    {
        gapSmpKeys_t    *pKeys = pConnectionEvent->eventData.keysReceivedEvent.pKeys;

        /* Take into account alignment */
        msgLen = GetRelAddr(appMsgFromHost_t, msgData) + GetRelAddr(connectionMsg_t, connEvent) + 
                 GetRelAddr(gapConnectionEvent_t, eventData) + sizeof(gapKeysReceivedEvent_t) + sizeof(gapSmpKeys_t);
                 
        if (pKeys->aLtk != NULL)
        {
            msgLen += 2 * sizeof(uint8_t) + pKeys->cLtkSize + pKeys->cRandSize;
        }

        msgLen += (pKeys->aIrk != NULL) ? (gcSmpIrkSize_c + gcBleDeviceAddressSize_c) : 0;
        msgLen += (pKeys->aCsrk != NULL) ? gcSmpCsrkSize_c : 0;
    }

    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapConnectionMsg_c;
    pMsgIn->msgData.connMsg.deviceId = peerDeviceId;

    if(pConnectionEvent->eventType == gConnEvtKeysReceived_c)
    {
        gapSmpKeys_t    *pKeys = pConnectionEvent->eventData.keysReceivedEvent.pKeys;
        uint8_t         *pCursor = (uint8_t*)&pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys;

        pMsgIn->msgData.connMsg.connEvent.eventType = gConnEvtKeysReceived_c;
        pCursor += sizeof(void*);
        pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys = (gapSmpKeys_t* )pCursor;
        
        /* Copy SMP Keys structure */
        FLib_MemCpy(pCursor, pConnectionEvent->eventData.keysReceivedEvent.pKeys, sizeof(gapSmpKeys_t));
        pCursor += sizeof(gapSmpKeys_t);
        
        if (pKeys->aLtk != NULL)
        {
            /* Copy LTK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->cLtkSize = pKeys->cLtkSize;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aLtk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aLtk, pKeys->cLtkSize);
            pCursor += pKeys->cLtkSize;

            /* Copy RAND */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->cRandSize = pKeys->cRandSize;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aRand = pCursor;
            FLib_MemCpy(pCursor, pKeys->aRand, pKeys->cRandSize);
            pCursor += pKeys->cRandSize;
        }
        else
          

        if (pKeys->aIrk != NULL)
        {
            /* Copy IRK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aIrk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aIrk, gcSmpIrkSize_c);
            pCursor += gcSmpIrkSize_c;

            /* Copy Address*/
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->addressType = pKeys->addressType;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aAddress = pCursor;
            FLib_MemCpy(pCursor, pKeys->aAddress, gcBleDeviceAddressSize_c);
            pCursor += gcBleDeviceAddressSize_c;
        }

        if (pKeys->aCsrk != NULL)
        {
            /* Copy CSRK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aCsrk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aCsrk, gcSmpCsrkSize_c);
        }
    }
    else
    {
        FLib_MemCpy(&pMsgIn->msgData.connMsg.connEvent, pConnectionEvent, sizeof(gapConnectionEvent_t));
    }

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapAdvertisingEvent_t));
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapAdvertisementMsg_c;
    pMsgIn->msgData.advMsg.eventType = pAdvertisingEvent->eventType;
    pMsgIn->msgData.advMsg.eventData = pAdvertisingEvent->eventData;

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_ScanningCallback (gapScanningEvent_t* pScanningEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;  
    
    uint8_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapScanningEvent_t);
    
    if (pScanningEvent->eventType == gDeviceScanned_c)
    {
        msgLen += pScanningEvent->eventData.scannedDevice.dataLength;
    }
    
    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapScanMsg_c;
    pMsgIn->msgData.scanMsg.eventType = pScanningEvent->eventType;
    
    if (pScanningEvent->eventType == gScanCommandFailed_c)
    {
        pMsgIn->msgData.scanMsg.eventData.failReason = pScanningEvent->eventData.failReason;
    }
    
    if (pScanningEvent->eventType == gDeviceScanned_c)
    {
        FLib_MemCpy(&pMsgIn->msgData.scanMsg.eventData.scannedDevice, 
                    &pScanningEvent->eventData.scannedDevice, 
                    sizeof(gapScanningEvent_t));
        
        /* Copy data after the gapScanningEvent_t structure and update the data pointer*/
        pMsgIn->msgData.scanMsg.eventData.scannedDevice.data = (uint8_t*)&pMsgIn->msgData + sizeof(gapScanningEvent_t);
        FLib_MemCpy(pMsgIn->msgData.scanMsg.eventData.scannedDevice.data, 
                    pScanningEvent->eventData.scannedDevice.data, 
                    pScanningEvent->eventData.scannedDevice.dataLength);
    }

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_GattServerCallback
(
    deviceId_t          deviceId,
    gattServerEvent_t*  pServerEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    uint16_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattServerMsg_t);
    
    if (pServerEvent->eventType == gEvtAttributeWritten_c ||
        pServerEvent->eventType == gEvtAttributeWrittenWithoutResponse_c)
    {
        msgLen += pServerEvent->eventData.attributeWrittenEvent.cValueLength;
    }

    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGattServerMsg_c;
    pMsgIn->msgData.gattServerMsg.deviceId = deviceId;
    FLib_MemCpy(&pMsgIn->msgData.gattServerMsg.serverEvent, pServerEvent, sizeof(gattServerEvent_t));

    if ((pMsgIn->msgData.gattServerMsg.serverEvent.eventType == gEvtAttributeWritten_c) ||
        (pMsgIn->msgData.gattServerMsg.serverEvent.eventType == gEvtAttributeWrittenWithoutResponse_c))
    {
        /* Copy value after the gattServerEvent_t structure and update the aValue pointer*/
        pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue = 
          (uint8_t *)&pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue + sizeof(uint8_t*);
        FLib_MemCpy(pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue,
                    pServerEvent->eventData.attributeWrittenEvent.aValue,
                    pServerEvent->eventData.attributeWrittenEvent.cValueLength);

    }
    
    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_GattClientProcedureCallback
(
    deviceId_t              deviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error)
{
    appMsgFromHost_t *pMsgIn = NULL;

    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientProcMsg_t));

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientProcedureMsg_c;
    pMsgIn->msgData.gattClientProcMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientProcMsg.procedureType = procedureType;
    pMsgIn->msgData.gattClientProcMsg.error = error;
    pMsgIn->msgData.gattClientProcMsg.procedureResult = procedureResult;

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_GattClientNotificationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store also the notified value*/
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientNotifIndMsg_t)
                        + valueLength);

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientNotificationMsg_c;
    pMsgIn->msgData.gattClientNotifIndMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientNotifIndMsg.characteristicValueHandle = characteristicValueHandle;
    pMsgIn->msgData.gattClientNotifIndMsg.valueLength = valueLength;

    /* Copy value after the gattClientNotifIndMsg_t structure and update the aValue pointer*/
    pMsgIn->msgData.gattClientNotifIndMsg.aValue = (uint8_t*)&pMsgIn->msgData + sizeof(gattClientNotifIndMsg_t);
    FLib_MemCpy(pMsgIn->msgData.gattClientNotifIndMsg.aValue, aValue, valueLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_GattClientIndicationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store also the notified value*/
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientNotifIndMsg_t)
                        + valueLength);

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientIndicationMsg_c;
    pMsgIn->msgData.gattClientNotifIndMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientNotifIndMsg.characteristicValueHandle = characteristicValueHandle;
    pMsgIn->msgData.gattClientNotifIndMsg.valueLength = valueLength;

    /* Copy value after the gattClientIndIndMsg_t structure and update the aValue pointer*/
    pMsgIn->msgData.gattClientNotifIndMsg.aValue = (uint8_t*)&pMsgIn->msgData + sizeof(gattClientNotifIndMsg_t);
    FLib_MemCpy(pMsgIn->msgData.gattClientNotifIndMsg.aValue, aValue, valueLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_L2caLeDataCallback
(
    deviceId_t deviceId,
    uint16_t   lePsm,
    uint8_t* pPacket,
    uint16_t packetLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store the packet */
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(l2caLeCbDataMsg_t) 
                        + packetLength);

    if (!pMsgIn)
    {
        return;
    }

    pMsgIn->msgType = gAppL2caLeDataMsg_c;
    pMsgIn->msgData.l2caLeCbDataMsg.deviceId = deviceId;
    pMsgIn->msgData.l2caLeCbDataMsg.lePsm = lePsm;
    pMsgIn->msgData.l2caLeCbDataMsg.packetLength = packetLength;

    FLib_MemCpy(pMsgIn->msgData.l2caLeCbDataMsg.aPacket, pPacket, packetLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_L2caLeControlCallback
(
    l2capControlMessageType_t  messageType,
    void* pMessage
)
{
    appMsgFromHost_t *pMsgIn = NULL;
    uint8_t messageLength = 0;

    switch (messageType) {
        case gL2ca_LePsmConnectRequest_c:
        {
            messageLength = sizeof(l2caLeCbConnectionRequest_t);
            break;
        }
        case gL2ca_LePsmConnectionComplete_c:
        {
            messageLength = sizeof(l2caLeCbConnectionComplete_t);
            break;
        }
        case gL2ca_LePsmDisconnectNotification_c:
        {
            messageLength = sizeof(l2caLeCbDisconnection_t);
            break;
        }
        case gL2ca_NoPeerCredits_c:
        {
            messageLength = sizeof(l2caLeCbNoPeerCredits_t);
            break;
        }
        case gL2ca_LocalCreditsNotification_c:
        {
            messageLength = sizeof(l2caLeCbLocalCreditsNotification_t);
            break;
        }
        default:
            return;
    }


    /* Allocate a buffer with enough space to store the biggest packet */
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(l2caLeCbConnectionComplete_t));

    if (!pMsgIn)
    {
        return;
    }

    pMsgIn->msgType = gAppL2caLeControlMsg_c;
    pMsgIn->msgData.l2caLeCbControlMsg.messageType = messageType;
    
    FLib_MemCpy(pMsgIn->msgData.l2caLeCbControlMsg.aMessage, pMessage, messageLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(mAppEvent, gAppEvtMsgFromHostStack_c);
}

#if !gUseHciTransportDownward_d
/* Called by BLE when a connect is received */
static void BLE_SignalFromISRCallback(void)
{
#if (cPWR_UsePowerDownMode)  
    PWR_DisallowDeviceToSleep();  
#endif    
}
#endif
