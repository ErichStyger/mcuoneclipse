/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuUtility.h"
#include "LoRaWAN.h"
#include "McuShell.h"
#include "LmHandler.h"
#include "LmhpCompliance.h"
#include "CayenneLpp.h"
#include "LmHandlerMsgDisplay.h"
#include "Commissioning.h"
#include "RegionCommon.h"
#include "boards/board.h"
#include "NvmDataMgmt.h"

extern const char* MacStatusStrings[];

#define FIRMWARE_VERSION  0x01020000 // 1.2.0.0

static TaskHandle_t LoRaTaskHandle;

void LORAWAN_LmHandlerNotififyTaskRequest(uint32_t event) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if (xPortIsInsideInterrupt()) {
	  xTaskNotifyAndQueryFromISR(LoRaTaskHandle, event, eSetBits, NULL, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  } else {
	  xTaskNotifyAndQuery(LoRaTaskHandle, event, eSetBits, NULL);
  }
}

/*!
 * User application data buffer size
 */
#define LORAWAN_APP_DATA_BUFFER_MAX_SIZE            242

/*!
 * User application data
 */
static uint8_t AppDataBuffer[LORAWAN_APP_DATA_BUFFER_MAX_SIZE];


#ifndef ACTIVE_REGION

#warning "No active region defined, LORAMAC_REGION_EU868 will be used as default."

#define ACTIVE_REGION LORAMAC_REGION_EU868

#endif

/*!
 * LoRaWAN default end-device class
 */
#ifndef LORAWAN_DEFAULT_CLASS
#define LORAWAN_DEFAULT_CLASS                       CLASS_A
#endif

/*!
 * Defines the application data transmission duty cycle. 5s, value in [ms].
 */
#define APP_TX_DUTYCYCLE                            5000

/*!
 * Defines a random delay for application data transmission duty cycle. 1s,
 * value in [ms].
 */
#define APP_TX_DUTYCYCLE_RND                        1000

/*!
 * LoRaWAN Adaptive Data Rate
 *
 * \remark Please note that when ADR is enabled the end-device should be static
 */
#define LORAWAN_ADR_STATE                           LORAMAC_HANDLER_ADR_ON

/*!
 * Default datarate
 *
 * \remark Please note that LORAWAN_DEFAULT_DATARATE is used only when ADR is disabled
 */
#define LORAWAN_DEFAULT_DATARATE                    DR_0

/*!
 * LoRaWAN confirmed messages
 */
#define LORAWAN_DEFAULT_CONFIRMED_MSG_STATE         LORAMAC_HANDLER_UNCONFIRMED_MSG

/*!
 * User application data buffer size
 */
#define LORAWAN_APP_DATA_BUFFER_MAX_SIZE            242

/*!
 * LoRaWAN ETSI duty cycle control enable/disable
 *
 * \remark Please note that ETSI mandates duty cycled transmissions. Use only for test purposes
 */
#define LORAWAN_DUTYCYCLE_ON                        false



/*!
 * LoRaWAN application port
 * @remark The allowed port range is from 1 up to 223. Other values are reserved.
 */
#define LORAWAN_APP_PORT                            2


/* ----------------------------------------------------------------------------------------------- */
static bool startUplink = false;

bool LORAWAN_StartUplink(void) {
  if (startUplink) {
    startUplink = false;
    return true;
  }
  return false;
}

void LORAWAN_StartJoin(void) {
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_START_JOINING);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"lorawan", (unsigned char*)"LoRaWAN Application status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  startUplink", startUplink?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t LORAWAN_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "lorawan help")==0) {
    McuShell_SendHelpStr((unsigned char*)"lorawan", (const unsigned char*)"Group of LoRaWAN application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  join", (unsigned char*)"Start joining the network\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  startUplink on|off", (unsigned char*)"Send uplink messages\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  factoryreset", (unsigned char*)"Factory reset NVM Data\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "lorawan status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "lorawan join")==0) {
    *handled = TRUE;
    LORAWAN_StartJoin();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startUplink on")==0) {
    *handled = TRUE;
    startUplink = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startUplink off")==0) {
    *handled = TRUE;
    startUplink = false;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan factoryreset")==0) {
    *handled = TRUE;
    startUplink = false;
    if (!NvmDataMgmtFactoryReset()) {
      return ERR_FAILED;
    }
    return ERR_OK;
  }
  return ERR_OK;
}
/* ----------------------------------------------------------------------------------------------- */
static void OnMacProcessNotify( void );
static void OnNvmDataChange( LmHandlerNvmContextStates_t state, uint16_t size );
static void OnNetworkParametersChange( CommissioningParams_t* params );
static void OnMacMcpsRequest( LoRaMacStatus_t status, McpsReq_t *mcpsReq, TimerTime_t nextTxIn );
static void OnMacMlmeRequest( LoRaMacStatus_t status, MlmeReq_t *mlmeReq, TimerTime_t nextTxIn );
static void OnJoinRequest( LmHandlerJoinParams_t* params );
static void OnTxData( LmHandlerTxParams_t* params );
static void OnRxData( LmHandlerAppData_t* appData, LmHandlerRxParams_t* params );
static void OnClassChange( DeviceClass_t deviceClass );
static void OnBeaconStatusChange( LoRaMacHandlerBeaconParams_t* params );
#if( LMH_SYS_TIME_UPDATE_NEW_API == 1 )
static void OnSysTimeUpdate( bool isSynchronized, int32_t timeCorrection );
#else
static void OnSysTimeUpdate( void );
#endif

static LmHandlerCallbacks_t LmHandlerCallbacks =
{
  .GetBatteryLevel = NULL,
  .GetTemperature = NULL,
  .GetRandomSeed = BoardGetRandomSeed,
  .OnMacProcess = OnMacProcessNotify,
  .OnNvmDataChange = OnNvmDataChange,
  .OnNetworkParametersChange = OnNetworkParametersChange,
  .OnMacMcpsRequest = OnMacMcpsRequest,
  .OnMacMlmeRequest = OnMacMlmeRequest,
  .OnJoinRequest = OnJoinRequest,
  .OnTxData = OnTxData,
  .OnRxData = OnRxData,
  .OnClassChange= OnClassChange,
  .OnBeaconStatusChange = OnBeaconStatusChange,
  .OnSysTimeUpdate = OnSysTimeUpdate,
};

static LmHandlerParams_t LmHandlerParams =
{
  .Region = ACTIVE_REGION,
  .AdrEnable = LORAWAN_ADR_STATE,
  .IsTxConfirmed = LORAWAN_DEFAULT_CONFIRMED_MSG_STATE,
  .TxDatarate = LORAWAN_DEFAULT_DATARATE,
  .PublicNetworkEnable = LORAWAN_PUBLIC_NETWORK,
  .DutyCycleEnabled = LORAWAN_DUTYCYCLE_ON,
  .DataBufferMaxSize = LORAWAN_APP_DATA_BUFFER_MAX_SIZE,
  .DataBuffer = AppDataBuffer,
  .PingSlotPeriodicity = REGION_COMMON_DEFAULT_PING_SLOT_PERIODICITY,
};

/*!
 * User application data structure
 */
static LmHandlerAppData_t AppData =
{
    .Buffer = AppDataBuffer,
    .BufferSize = 0,
    .Port = 0,
};


/*!
 * Specifies the state of the application LED
 */
static bool AppLedStateOn = false;

static void OnTxPeriodicityChanged( uint32_t periodicity );
static void OnTxFrameCtrlChanged( LmHandlerMsgTypes_t isTxConfirmed );
static void OnPingSlotPeriodicityChanged( uint8_t pingSlotPeriodicity );

static LmhpComplianceParams_t LmhpComplianceParams =
{
  .FwVersion.Value = FIRMWARE_VERSION,
  .OnTxPeriodicityChanged = OnTxPeriodicityChanged,
  .OnTxFrameCtrlChanged = OnTxFrameCtrlChanged,
  .OnPingSlotPeriodicityChanged = OnPingSlotPeriodicityChanged,
};

static void OnMacProcessNotify(void) {
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_MAC_PENDING);
  McuLog_trace("OnMacProcessNotify");
}

static void OnNvmDataChange(LmHandlerNvmContextStates_t state, uint16_t size) {
  /* save/restore of NVMC data */
  DisplayNvmDataChange(state, size);
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnNetworkParametersChange(CommissioningParams_t* params) {
  DisplayNetworkParametersUpdate(params);
  McuLog_trace("OnNetworkParametersChange");
 // LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnMacMcpsRequest(LoRaMacStatus_t status, McpsReq_t *mcpsReq, TimerTime_t nextTxIn) {
  /* MAC Common Part Sublayer request */
  DisplayMacMcpsRequestUpdate(status, mcpsReq, nextTxIn);
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnMacMlmeRequest(LoRaMacStatus_t status, MlmeReq_t *mlmeReq, TimerTime_t nextTxIn) {
  /* MAC Layer Management Entity request */
  DisplayMacMlmeRequestUpdate(status, mlmeReq, nextTxIn);
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnJoinRequest(LmHandlerJoinParams_t* params) {
  DisplayJoinRequestUpdate(params);
  if(params->Status == LORAMAC_HANDLER_ERROR) {
    LmHandlerJoin();
  } else {
    LmHandlerRequestClass(LORAWAN_DEFAULT_CLASS);
  }
  if (params->Status==LORAMAC_HANDLER_SUCCESS) {
    LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_CONNECTED);
  }
}

static void OnTxData(LmHandlerTxParams_t* params) {
  DisplayTxUpdate(params);
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnRxData(LmHandlerAppData_t* appData, LmHandlerRxParams_t* params) {
  DisplayRxUpdate(appData, params);
  switch(appData->Port) {
    case 1: // The application LED can be controlled on port 1 or 2
//    case LORAWAN_APP_PORT:
//            AppLedStateOn = appData->Buffer[0] & 0x01;
      break;
    default:
      break;
  }
 // LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnClassChange(DeviceClass_t deviceClass) {
  DisplayClassUpdate( deviceClass );
  McuLog_trace("OnClassChange");
  // Inform the server as soon as possible that the end-device has switched to ClassB
  LmHandlerAppData_t appData =
  {
      .Buffer = NULL,
      .BufferSize = 0,
      .Port = 0,
  };
  LmHandlerSend(&appData, LORAMAC_HANDLER_UNCONFIRMED_MSG);
 // LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnBeaconStatusChange(LoRaMacHandlerBeaconParams_t* params) {
    switch( params->State )
    {
        case LORAMAC_HANDLER_BEACON_RX:
        {
//            TimerStart( &LedBeaconTimer );
            break;
        }
        case LORAMAC_HANDLER_BEACON_LOST:
        case LORAMAC_HANDLER_BEACON_NRX:
        {
//            TimerStop( &LedBeaconTimer );
            break;
        }
        default:
        {
            break;
        }
    }
    DisplayBeaconUpdate( params );
    //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

#if( LMH_SYS_TIME_UPDATE_NEW_API == 1 )
static void OnSysTimeUpdate(bool isSynchronized, int32_t timeCorrection) {
}
#else
static void OnSysTimeUpdate(void) {
}
#endif

#if 0
/*!
 * Prepares the payload of the frame and transmits it.
 */
static void PrepareTxFrame(void) {
    if( LmHandlerIsBusy( ) == true )
    {
        return;
    }

    uint8_t channel = 0;

    AppData.Port = LORAWAN_APP_PORT;

    CayenneLppReset( );
    CayenneLppAddDigitalInput( channel++, AppLedStateOn );
    CayenneLppAddAnalogInput( channel++, BoardGetBatteryLevel( ) * 100 / 254 );

    CayenneLppCopy( AppData.Buffer );
    AppData.BufferSize = CayenneLppGetSize( );

    if( LmHandlerSend( &AppData, LmHandlerParams.IsTxConfirmed ) == LORAMAC_HANDLER_SUCCESS )
    {
#if PL_CONFIG_USE_LED1
       // Switch LED 1 ON
        GpioWrite( &Led1, 1 );
        TimerStart( &Led1Timer );
#endif
    }
}
#endif

#if 0
static void UplinkProcess(void) {
    uint8_t isPending = 0;
    CRITICAL_SECTION_BEGIN( );
    isPending = IsTxFramePending;
    IsTxFramePending = 0;
    CRITICAL_SECTION_END( );
    if( isPending == 1 )
    {
        PrepareTxFrame( );
    }
}
#endif

static void OnTxPeriodicityChanged(uint32_t periodicity) {
  McuLog_trace("OnTxPeriodicityChanged %u", periodicity);
#if 0
    TxPeriodicity = periodicity;

    if( TxPeriodicity == 0 )
    { // Revert to application default periodicity
        TxPeriodicity = APP_TX_DUTYCYCLE + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
    }

    // Update timer periodicity
    TimerStop( &TxTimer );
    TimerSetValue( &TxTimer, TxPeriodicity );
    TimerStart( &TxTimer );
#endif
}

static void OnTxFrameCtrlChanged( LmHandlerMsgTypes_t isTxConfirmed ) {
  LmHandlerParams.IsTxConfirmed = isTxConfirmed;
  McuLog_trace("OnTxFrameCtrlChanged, isTxConfirmed %u", isTxConfirmed);
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnPingSlotPeriodicityChanged( uint8_t pingSlotPeriodicity ) {
  LmHandlerParams.PingSlotPeriodicity = pingSlotPeriodicity;
  McuLog_trace("OnTxFrameCtrlChanged: %u", pingSlotPeriodicity);
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

typedef enum LoRaTaskState_e {
  LORA_TASK_STATE_INIT,
  LORA_TASK_STATE_JOINING,
  LORA_TASK_STATE_CONNECTED,
  LORA_TASK_STATE_TX_DATA,
} LoRaTaskState_e;

static void LoRaTask(void *pv) {
  uint32_t notification;
  BaseType_t res;
  LoRaTaskState_e state = LORA_TASK_STATE_INIT;

  if (LmHandlerInit(&LmHandlerCallbacks, &LmHandlerParams) != LORAMAC_HANDLER_SUCCESS) {
    McuLog_fatal("LoRaMac wasn't properly initialized");
    for(;;) {}
  }
  /* Set system maximum tolerated rx error in milliseconds */
  LmHandlerSetSystemMaxRxError(20);

  // The LoRa-Alliance Compliance protocol package should always be
  // initialized and activated.
  LmHandlerPackageRegister(PACKAGE_ID_COMPLIANCE, &LmhpComplianceParams);
  //StartTxProcess(LORAMAC_HANDLER_TX_ON_TIMER);
#if 0
  if( LmHandlerSend( &AppData, LmHandlerParams.IsTxConfirmed ) == LORAMAC_HANDLER_SUCCESS )
  {

  }
#endif
  for(;;) {
      res = xTaskNotifyWait(0, -1, &notification, portMAX_DELAY);
      if (res==pdPASS) { /* notification received */
        LmHandlerProcess();
        switch(state) {
          case LORA_TASK_STATE_INIT:
            if (notification&LORAWAN_NOTIFICATION_START_JOINING) {
              McuLog_info("start joining ...");
              LmHandlerJoin();
              state = LORA_TASK_STATE_JOINING;
            }
          break;
          case LORA_TASK_STATE_JOINING:
            if (notification&LORAWAN_NOTIFICATION_CONNECTED) { /* join successful? */
              McuLog_info("... connected");
              state = LORA_TASK_STATE_CONNECTED;
            } else { /* wait during joining */
              for(int i=0; i<70; i++) { /* 7s: need to process multiple messages: Rx1 delay is 5s and RX2 is at 6s */
                LmHandlerProcess();
                vTaskDelay(pdMS_TO_TICKS(100));
              }
            }
            break;
          case LORA_TASK_STATE_CONNECTED:
            if (notification&LORAWAN_NOTIFICATION_TX_DATA) {
          //     StartTxProcess(LORAMAC_HANDLER_TX_ON_TIMER);
             }
           break;
          case LORA_TASK_STATE_TX_DATA:
            //UplinkProcess();
             state = LORA_TASK_STATE_CONNECTED;
            break;
          default:
            break;
        } /* switch */
#if 0
      // Process application uplinks management
      //UplinkProcess();
      if (notification&LORAWAN_NOTIFICATION_EVENT_WAKEUP) {
        LmHandlerProcess();
      } else if (notification&(LORAWAN_NOTIFICATION_EVENT_LMHANDLER|LORAWAN_NOTIFICATION_EVENT_MAC_PENDING)) {
        for(int i=0; i<70; i++) { /* 7s: need to process multiple messages: Rx1 delay is 5s and RX2 is at 6s */
          LmHandlerProcess();
          vTaskDelay(pdMS_TO_TICKS(100));
        }
      }
#endif
      if (notification&LORAWAN_NOTIFICATION_EVENT_TX_REQUEST) {
        //printf("event LORAWAN_NOTIFICATION_EVENT_TX_REQUEST received\n");
        McuLog_trace("event LORAWAN_NOTIFICATION_EVENT_TX_REQUEST received");
      }
    } /* if notification received */
  } /* for */
}

static TimerHandle_t rtc_timer;
static TimerHandle_t wakeup_timer;

static void vTimerCallbackRTC(TimerHandle_t pxTimer) {
  McuTimeDate_AddTick();
}

static void vTimerCallbackWakeup(TimerHandle_t pxTimer) {
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_WAKEUP);
  McuLog_trace("timer wakeup");
}

void LoRaWAN_Init(void) {
  if (xTaskCreate(
      LoRaTask,  /* pointer to the task */
      "LoRaTask", /* task name for kernel awareness debugging */
      5000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
	  configMAX_PRIORITIES-1,  /* initial priority */
      &LoRaTaskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating LoRaWan task");
    for(;;){} /* error! probably out of memory */
  }
  rtc_timer = xTimerCreate(
        "rtcTimer", /* name */
        pdMS_TO_TICKS(McuTimeDate_CONFIG_TICK_TIME_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackRTC); /* callback */
  if (rtc_timer==NULL) {
    McuLog_fatal("failed creating RTC Timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(rtc_timer, pdMS_TO_TICKS(50))!=pdPASS) {
    McuLog_fatal("failed starting RTC Timer");
    for(;;); /* failure! */
  }
  wakeup_timer = xTimerCreate(
        "wakeupTimer", /* name */
        pdMS_TO_TICKS(20*1000), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackWakeup); /* callback */
  if (wakeup_timer==NULL) {
    McuLog_fatal("failed creating wakeup Timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(wakeup_timer, pdMS_TO_TICKS(50))!=pdPASS) {
    McuLog_fatal("failed starting wakeup Timer");
    for(;;); /* failure! */
  }
}
