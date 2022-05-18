/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuLog.h"
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

#define FIRMWARE_VERSION  0x01020000 // 1.2.0.0


static TaskHandle_t LoRaTaskHandle;
static uint8_t IsMacProcessPending = 0;

TaskHandle_t  lorawan_task_handle;
QueueHandle_t lorawan_task_queue;


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
static bool startJoin = false;

bool LORAWAN_StartUplink(void) {
  return startUplink;
}

bool LORAWAN_StartJoin(void) {
  if (startJoin) {
    startJoin = false;
    return true;
  }
  return false;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"lorawan", (unsigned char*)"LoRaWAN Application status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  startUplink", startUplink?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  startJoin", startJoin?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t LORAWAN_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "lorawan help")==0) {
    McuShell_SendHelpStr((unsigned char*)"lorawan", (const unsigned char*)"Group of LoRaWAN application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  startJoin on|off", (unsigned char*)"Start joining the network\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  startUplink on|off", (unsigned char*)"Send uplink messages\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "lorawan status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startJoin on")==0) {
    *handled = TRUE;
    startJoin = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startJoin off")==0) {
    *handled = TRUE;
    startJoin = false;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startUplink on")==0) {
    *handled = TRUE;
    startUplink = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "lorawan startUplink off")==0) {
    *handled = TRUE;
    startUplink = false;
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

//static void UplinkProcess( void );

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
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_MAC_PENDING);
  IsMacProcessPending = 1;
  printf( "\n###### =========== MacProcessNotify ============ ######\n" );
  printf( "######            xxxxxxxxxxxxxxxxxxx             ######\n");
  printf( "###### ========================================== ######\n");

}

static void OnNvmDataChange(LmHandlerNvmContextStates_t state, uint16_t size) {
  DisplayNvmDataChange(state, size);
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnNetworkParametersChange(CommissioningParams_t* params) {
  DisplayNetworkParametersUpdate(params);
 // LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnMacMcpsRequest(LoRaMacStatus_t status, McpsReq_t *mcpsReq, TimerTime_t nextTxIn) {
  DisplayMacMcpsRequestUpdate(status, mcpsReq, nextTxIn);
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnMacMlmeRequest(LoRaMacStatus_t status, MlmeReq_t *mlmeReq, TimerTime_t nextTxIn) {
  DisplayMacMlmeRequestUpdate(status, mlmeReq, nextTxIn);
  LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnJoinRequest(LmHandlerJoinParams_t* params) {
  DisplayJoinRequestUpdate(params);
  if(params->Status == LORAMAC_HANDLER_ERROR) {
    LmHandlerJoin();
  } else {
    LmHandlerRequestClass( LORAWAN_DEFAULT_CLASS );
  }
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnTxData(LmHandlerTxParams_t* params) {
  DisplayTxUpdate(params);
 // LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
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
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}

static void OnPingSlotPeriodicityChanged( uint8_t pingSlotPeriodicity ) {
  LmHandlerParams.PingSlotPeriodicity = pingSlotPeriodicity;
  //LORAWAN_LmHandlerNotififyTaskRequest(LORAWAN_NOTIFICATION_EVENT_LMHANDLER);
}



static void LoRaTask(void *pv) {
  uint32_t notification;
  BaseType_t res;

  if (LmHandlerInit(&LmHandlerCallbacks, &LmHandlerParams) != LORAMAC_HANDLER_SUCCESS) {
    McuLog_fatal("LoRaMac wasn't properly initialized");
    for(;;) {}
  }
  /* Set system maximum tolerated rx error in milliseconds */
  LmHandlerSetSystemMaxRxError(20);

  // The LoRa-Alliance Compliance protocol package should always be
  // initialized and activated.
  LmHandlerPackageRegister(PACKAGE_ID_COMPLIANCE, &LmhpComplianceParams);

  LmHandlerJoin();
  //StartTxProcess(LORAMAC_HANDLER_TX_ON_TIMER);
  if( LmHandlerSend( &AppData, LmHandlerParams.IsTxConfirmed ) == LORAMAC_HANDLER_SUCCESS )
  {

  }
  for(;;) {
    taskENTER_CRITICAL();
    if (IsMacProcessPending == 1) {
      // Clear flag and prevent MCU to go into low power modes.
      IsMacProcessPending = 0;
      printf("process pending\n");
      taskEXIT_CRITICAL();
      LmHandlerProcess();

    } else {
      taskEXIT_CRITICAL();
      /* wait for notification */
      res = xTaskNotifyWait(0, -1, &notification, pdMS_TO_TICKS(5) /*portMAX_DELAY*/);
      if (res==pdPASS) { /* notification received */
        if (notification&(LORAWAN_NOTIFICATION_EVENT_LMHANDLER|LORAWAN_NOTIFICATION_EVENT_MAC_PENDING)) {

         // taskENTER_CRITICAL();
         // printf("event received\n");
          LmHandlerProcess();
          //taskEXIT_CRITICAL();
          // Process application uplinks management
                  //UplinkProcess( );

                  CRITICAL_SECTION_BEGIN( );
                  if( IsMacProcessPending == 1 )
                  {
                      // Clear flag and prevent MCU to go into low power modes.
                      IsMacProcessPending = 0;
                      printf("*clear\n");
                  }
                  else
                  {
                      // The MCU wakes up through events
                     // printf("*low power\n");
                      BoardLowPowerHandler( );
                  }
                  CRITICAL_SECTION_END( );
        }
        if (notification&LORAWAN_NOTIFICATION_EVENT_TX_REQUEST) {
        	printf("event LORAWAN_NOTIFICATION_EVENT_TX_REQUEST received\n");
        }
      }
    }
  } /* for */
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
}
