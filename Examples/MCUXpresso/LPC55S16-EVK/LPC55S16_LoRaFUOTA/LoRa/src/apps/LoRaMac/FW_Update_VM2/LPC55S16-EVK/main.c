/*!
 * \file      main.c
 *
 * \brief     Performs a periodic uplink
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2018 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 * \author    Diego Bienz (HSLU)
 * \author    Erich Styger (HSLU)
 */

/* configuration macros */
#define CONFIG_USE_UART2   (0)
#define CONFIG_USE_LEDS    (0)

#include <stdio.h>
#include "../firmwareVersion.h"
#include "fragment_Data_handler.h"
#include "../../common/githubVersion.h"
#include "utilities.h"
#include "board-config.h"
#include "board.h"
#include "boards/board.h"
#include "gpio.h"
#include "uart.h"
#include "RegionCommon.h"
#include "lpm-board.h"
#include "gps.h"

#include "cli.h"
#include "Commissioning.h"
#include "LmHandler.h"
#include "LmhpCompliance.h"
#include "CayenneLpp.h"
#include "LmHandlerMsgDisplay.h"
				 
#include "platform.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
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


/*!
 * LoRaWAN Switch class application port
 * @note do not use 224. It is reserved for certification
 */
#define LORAWAN_SWITCH_CLASS_PORT                   3




/*!
 *
 */
typedef enum
{
    LORAMAC_HANDLER_TX_ON_TIMER,
    LORAMAC_HANDLER_TX_ON_EVENT,
}LmHandlerTxEvents_t;

/*!
 * User application data
 */
static uint8_t AppDataBuffer[LORAWAN_APP_DATA_BUFFER_MAX_SIZE];

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

/*!
 * Timer to handle the application data transmission duty cycle
 */
static TimerEvent_t TxTimer;

#if PL_CONFIG_USE_LED1
/*!
 * Timer to handle the state of LED1
 */
static TimerEvent_t Led1Timer;
#endif

#if PL_CONFIG_USE_LED2
/*!
 * Timer to handle the state of LED2
 */
static TimerEvent_t Led2Timer;
#endif
/*!
 * Timer to handle the state of LED beacon indicator
 */
static TimerEvent_t LedBeaconTimer;

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
static void PrepareTxFrame( void );
static void StartTxProcess( LmHandlerTxEvents_t txEvent );
static void UplinkProcess( void );
static void FuotaProcess( void );


static void OnTxPeriodicityChanged( uint32_t periodicity );
static void OnTxFrameCtrlChanged( LmHandlerMsgTypes_t isTxConfirmed );
static void OnPingSlotPeriodicityChanged( uint8_t pingSlotPeriodicity );

static void ConfirmClassC_FUOTA();

static void Ready_for_FUOTA();

static void Error_FUOTA();

static void RCV_Fragment_Answer();



/*!
 * Function executed on TxTimer event
 */
static void OnTxTimerEvent( void* context );

#if PL_CONFIG_USE_LED1
/*!
 * Function executed on Led 1 Timeout event
 */
static void OnLed1TimerEvent( void* context );
#endif

#if PL_CONFIG_USE_LED2
/*!
 * Function executed on Led 2 Timeout event
 */
static void OnLed2TimerEvent( void* context );
#endif

/*!
 * \brief Function executed on Beacon timer Timeout event
 */
static void OnLedBeaconTimerEvent( void* context );

static LmHandlerCallbacks_t LmHandlerCallbacks =
{
    .GetBatteryLevel = BoardGetBatteryLevel,
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

static LmhpComplianceParams_t LmhpComplianceParams =
{
    .FwVersion.Value = FIRMWARE_VERSION,
    .OnTxPeriodicityChanged = OnTxPeriodicityChanged,
    .OnTxFrameCtrlChanged = OnTxFrameCtrlChanged,
    .OnPingSlotPeriodicityChanged = OnPingSlotPeriodicityChanged,
};

/*!
 * Indicates if LoRaMacProcess call is pending.
 * 
 * \warning If variable is equal to 0 then the MCU can be set in low power mode
 */
static volatile uint8_t IsMacProcessPending = 0;

static volatile uint8_t IsTxFramePending = 0;

static volatile uint32_t TxPeriodicity = 0;

static volatile uint8_t globalCnt = 0;


static uint16_t fragmentCnt_old = 0;


uint32_t fragment_line_Numbers = 10;
DeviceClass_t actClass;

FuotaState_t fuotaState = IDLE;



/*!
 * LED GPIO pins objects
 */
#if PL_CONFIG_USE_LED1
extern Gpio_t Led1; // Tx
#endif
#if PL_CONFIG_USE_LED2
extern Gpio_t Led2; // Rx
#endif

#if PL_CONFIG_USE_UART2
/*!
 * UART object used for command line interface handling
 */
extern Uart_t Uart2;
#endif

/*!
 * Main application entry point.
 */
int main( void )
{
    BoardInitMcu( );
    BoardInitPeriph( );
    PL_Init();

	#if PL_CONFIG_USE_LED1
		TimerInit( &Led1Timer, OnLed1TimerEvent );
		TimerSetValue( &Led1Timer, 25 );
	#endif
	#if PL_CONFIG_USE_LED2
		TimerInit( &Led2Timer, OnLed2TimerEvent );
		TimerSetValue( &Led2Timer, 25 );
	#endif
    TimerInit( &LedBeaconTimer, OnLedBeaconTimerEvent );
    TimerSetValue( &LedBeaconTimer, 5000 );

    printf("THIS IS MAIN IMAGE:\r\n\r\n\r\n");

    //printf("Vektortable-Address of Application: 0x%08X\r\n\r\n\r\n", (unsigned int)SCB->VTOR);


    // Initialize transmission periodicity variable
    TxPeriodicity = APP_TX_DUTYCYCLE + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );

    const Version_t appVersion = { .Value = FIRMWARE_VERSION };
    const Version_t gitHubVersion = { .Value = GITHUB_VERSION };
    DisplayAppInfo( "FUOTA application",
                    &appVersion,
                    &gitHubVersion );
    BoardPrintUUID();

    /* Application won't use low power off mode */
    LpmSetOffMode(LPM_APPLI_ID, LPM_DISABLE);
    LpmSetStopMode(LPM_APPLI_ID, LPM_DISABLE);

    /* GPS is not required for this application. In order to save power consumption, it is disabled here */
    GpsStop();

    if ( LmHandlerInit( &LmHandlerCallbacks, &LmHandlerParams ) != LORAMAC_HANDLER_SUCCESS )
    {
        printf( "LoRaMac wasn't properly initialized\n" );
        // Fatal error, endless loop.
        while ( 1 )
        {
        }
    }

    // Set system maximum tolerated rx error in milliseconds
    LmHandlerSetSystemMaxRxError( 20 );

    // The LoRa-Alliance Compliance protocol package should always be
    // initialized and activated.
    LmHandlerPackageRegister( PACKAGE_ID_COMPLIANCE, &LmhpComplianceParams );

    LmHandlerJoin( );

    StartTxProcess( LORAMAC_HANDLER_TX_ON_TIMER );

    fuota_nvm_init();

#if McuLib_CONFIG_SDK_USE_FREERTOS
    if (xTaskCreate(
        LoRaTask,  /* pointer to the task */
        "LoRaTask", /* task name for kernel awareness debugging */
        5000/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS)
    {
       for(;;){} /* error! probably out of memory */
    }
    vTaskStartScheduler();
    for(;;) {}
#else
    while( 1 )
    {
#if PL_CONFIG_USE_SHELL
        SHELL_Process();
#endif

#if PL_CONFIG_USE_UART2
        // Process characters sent over the command line interface
        CliProcess( &Uart2 );
#endif
        // Processes the LoRaMac events
        LmHandlerProcess( );

        actClass =  LmHandlerGetCurrentClass();
        if(actClass != CLASS_C){
             UplinkProcess( );
        }
        else{
        	FuotaProcess( );
        }

        CRITICAL_SECTION_BEGIN( );
        if( IsMacProcessPending == 1 )
        {
            // Clear flag and prevent MCU to go into low power modes.
            IsMacProcessPending = 0;
        }
        else
        {
            // The MCU wakes up through events
            BoardLowPowerHandler( );
        }
        CRITICAL_SECTION_END( );
    }
#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */	 
}

static void OnMacProcessNotify( void )
{
    IsMacProcessPending = 1;
}

static void OnNvmDataChange( LmHandlerNvmContextStates_t state, uint16_t size )
{
    DisplayNvmDataChange( state, size );
}

static void OnNetworkParametersChange( CommissioningParams_t* params )
{
    DisplayNetworkParametersUpdate( params );
}

static void OnMacMcpsRequest( LoRaMacStatus_t status, McpsReq_t *mcpsReq, TimerTime_t nextTxIn )
{
    //DisplayMacMcpsRequestUpdate( status, mcpsReq, nextTxIn );
}

static void OnMacMlmeRequest( LoRaMacStatus_t status, MlmeReq_t *mlmeReq, TimerTime_t nextTxIn )
{
    DisplayMacMlmeRequestUpdate( status, mlmeReq, nextTxIn );
}

static void OnJoinRequest( LmHandlerJoinParams_t* params )
{
    DisplayJoinRequestUpdate( params );
    if( params->Status == LORAMAC_HANDLER_ERROR )
    {
        LmHandlerJoin( );
    }
    else
    {
        LmHandlerRequestClass( LORAWAN_DEFAULT_CLASS );
    }
}

static void OnTxData( LmHandlerTxParams_t* params )
{
    DisplayTxUpdate( params );
}

static void OnRxData( LmHandlerAppData_t* appData, LmHandlerRxParams_t* params )
{
    DisplayRxUpdate( appData, params );

    switch( appData->Port )
    {

    case LORAWAN_APP_PORT:
        {
            AppLedStateOn = appData->Buffer[0] & 0x01;
        }
        break;

    case LORAWAN_SWITCH_CLASS_PORT:
          /*this port switches the class*/
          if (appData->BufferSize == 1)
          {
        	  printf( "\n###### =========== LORAWAN_SWITCH_CLASS_PORT ============ ######\n" );

            switch (appData->Buffer[0])
            {
              case 0:
              {
                LmHandlerRequestClass(CLASS_A);
                fuotaState = IDLE;
                break;
              }
              case 1:
              {
                LmHandlerRequestClass(CLASS_B);
                fuotaState = IDLE;
                break;
              }
              case 2:
              {
            	printf( "\n###### =========== LORAWAN_SWITCH_CLASS C ============ ######\n" );
                LmHandlerRequestClass(CLASS_C);
                break;
              }
              default:
                break;
            }
          }
          break;

    case LORAWAN_FRAGMENTED_BLOCK_PORT:

              if (appData->BufferSize >= 1)
              {
            	 // char c_arr[255][fragment_line_Numbers];
            	  int i;

            	  printf("\r\n###### ========== Buffer Fragmented Block ==========\r\n");
				  for (i=0;i<appData->BufferSize;i++)
				  {
					  	//sprintf(c_arr[fragmentCNT][i], "%d",appData->Buffer[i]);
						printf( "%02X", appData->Buffer[i]);
//						if(num_written == -1)
//						{
//						 //error handling
//						 break;
//						}
				  }
				  printf("\r\n###### ========== Buffer finished ==========\r\n\r\n\r\n\r\n\r\n");
              }
              break;


    case FUOTA_PRE_PROCESS:

                 if (appData->BufferSize >= 1){
                	 // char c_arr[255][fragment_line_Numbers];
                	  int i;

                	  printf("\r\n###### ========== FUOTA META DATA ==========\r\n");
    				  for (i=0;i<appData->BufferSize;i++)
    				  {
    					  	//sprintf(c_arr[fragmentCNT][i], "%d",appData->Buffer[i]);
    						printf( "%02X", appData->Buffer[i]);
    				  }
    				  printf("\r\n\r\n\r\n\r\n\r\n\r\n");

    				  if(FUOTA_FW_Meta_Data(appData)==ERROR_OK){
        				  fuotaState = CONF_READY;
    				  }
    				  else{
    					  fuotaState = Error_State;
    				  }
                 }
                 break;

    case FUOTA_FRAGMENT_HANDLING:

                 if (appData->BufferSize >= 1)
                 {
                	 // char c_arr[255][fragment_line_Numbers];
                	  int i;

                	  printf("\r\n###### ========== FUOTA FRAGMENT DATA ==========\r\n");
    				  for (i=0;i<appData->BufferSize;i++)
    				  {
    					  	//sprintf(c_arr[fragmentCNT][i], "%d",appData->Buffer[i]);
    						printf( "%02X", appData->Buffer[i]);
    				  }
    				  printf("\r\n\r\n\r\n\r\n\r\n\r\n");

    				  if(FUOTA_FW_Fragmt_Data(appData)==ERROR_OK){
        				 //TODO: if fragment block finish go to fuotaState idle
    					  if(get_FragmentCnt() == (uint16_t)get_fragm_numbers()){
    						  fuotaState = FINISH;
    					  }
    				  }
    				  else{
    					  fuotaState = Error_State;
    				  }
    					//getFW_Version uint16
    				  //incFragmentCnt();

                 }
                 break;

    case FUOTA_FRAGMENT_INFO:
                 if (appData->BufferSize >= 1)
                 {

					  int i;
					  printf("\r\n###### ========== FUOTA FINISH DATA ==========\r\n");
					  for (i=0;i<appData->BufferSize;i++)
					  {
							//sprintf(c_arr[fragmentCNT][i], "%d",appData->Buffer[i]);
							printf( "%02X", appData->Buffer[i]);
					  }
					  printf("\r\n\r\n\r\n\r\n\r\n\r\n");

					  if(FUOTA_FW_FINISH_Data(appData)==ERROR_OK){
						  fuotaState = UPDATE_NODE;
					  }
					  else{
						  fuotaState = Error_State;
					  }
						//getFW_Version uint16
					  //incFragmentCnt();

				}
                 break;

    default:
        break;
    }

    // Switch LED 2 ON for each received downlink
    // Switch LED 2 ON for each received downlink
	#if PL_CONFIG_USE_LED2
		GpioWrite( &Led2, 1 );
		TimerStart( &Led2Timer );
	#endif
}

static void OnClassChange( DeviceClass_t deviceClass )
{
    DisplayClassUpdate( deviceClass );

    // Inform the server as soon as possible that the end-device has switched to ClassB
    LmHandlerAppData_t appData =
    {
        .Buffer = NULL,
        .BufferSize = 0,
        .Port = 0,
    };
    //LmHandlerSend( &appData, LORAMAC_HANDLER_UNCONFIRMED_MSG );
    //ConfirmClassC_FUOTA();
    LmHandlerSend( &appData,  LmHandlerParams.IsTxConfirmed);
}

static void ConfirmClassC_FUOTA( )
{
	LmHandlerAppData_t appDataFUOTA  =
	{
	    .Buffer = AppDataBuffer,
	    .BufferSize = 0,
	    .Port = 0,
	};
	appDataFUOTA.Port = FUOTA_PRE_PROCESS;
	appDataFUOTA.BufferSize = FUOTA_PrePro_Data( appDataFUOTA.Buffer );
    if( LmHandlerSend( &appDataFUOTA, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
        TimerStart( &Led1Timer );
        fuotaState = IDLE;
    }
}


static void Ready_for_FUOTA( )
{
	LmHandlerAppData_t appDataFUOTA  =
	{
	    .Buffer = AppDataBuffer,
	    .BufferSize = 0,
	    .Port = 0,
	};
	appDataFUOTA.Port = FUOTA_FRAGMENT_HANDLING;
	appDataFUOTA.BufferSize = FUOTA_Ready_Data( appDataFUOTA.Buffer );
    if( LmHandlerSend( &appDataFUOTA, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
        TimerStart( &Led1Timer );
        fuotaState = FRAGMENT_RECEIVING;
    }
}


static void Error_FUOTA( )
{
	LmHandlerAppData_t appDataFUOTA  =
	{
	    .Buffer = AppDataBuffer,
	    .BufferSize = 0,
	    .Port = 0,
	};
	appDataFUOTA.Port = FUOTA_FRAGMENT_INFO;
	appDataFUOTA.BufferSize = FUOTA_Error_Data( appDataFUOTA.Buffer );
    if( LmHandlerSend( &appDataFUOTA, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
        TimerStart( &Led1Timer );
        fuotaState = FRAGMENT_RECEIVING;
    }
}

static void RCV_Fragment_Answer( )
{
	LmHandlerAppData_t appDataFUOTA  =
	{
	    .Buffer = AppDataBuffer,
	    .BufferSize = 0,
	    .Port = 0,
	};
	appDataFUOTA.Port = FUOTA_FRAGMENT_INFO;
	appDataFUOTA.BufferSize = FUOTA_Fragment_rcv_Answer( appDataFUOTA.Buffer );
    if( LmHandlerSend( &appDataFUOTA, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
        TimerStart( &Led1Timer );

    }
}



static void FINISH_Answer( )
{
	LmHandlerAppData_t appDataFUOTA  =
	{
	    .Buffer = AppDataBuffer,
	    .BufferSize = 0,
	    .Port = 0,
	};
	appDataFUOTA.Port = FUOTA_FRAGMENT_INFO;
	appDataFUOTA.BufferSize = FUOTA_FINISH_rcv_Answer( appDataFUOTA.Buffer );
    if( LmHandlerSend( &appDataFUOTA, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
        TimerStart( &Led1Timer );

    }
}





static void OnBeaconStatusChange( LoRaMacHandlerBeaconParams_t* params )
{
    switch( params->State )
    {
        case LORAMAC_HANDLER_BEACON_RX:
        {
            TimerStart( &LedBeaconTimer );
            break;
        }
        case LORAMAC_HANDLER_BEACON_LOST:
        case LORAMAC_HANDLER_BEACON_NRX:
        {
            TimerStop( &LedBeaconTimer );
            break;
        }
        default:
        {
            break;
        }
    }

    DisplayBeaconUpdate( params );
}

#if( LMH_SYS_TIME_UPDATE_NEW_API == 1 )
static void OnSysTimeUpdate( bool isSynchronized, int32_t timeCorrection )
{

}
#else
static void OnSysTimeUpdate( void )
{

}
#endif

/*!
 * Prepares the payload of the frame and transmits it.
 */
static void PrepareTxFrame( void )
{
    if( LmHandlerIsBusy( ) == true )
    {
        return;
    }

    uint8_t channel = 0;

    AppData.Port = LORAWAN_APP_PORT;

    CayenneLppReset( );
    CayenneLppAddDigitalInput( channel++, 0x33 );
    CayenneLppAddAnalogInput( channel++, (float)4.44 * 100 / 254 );

    CayenneLppCopy( AppData.Buffer );
    AppData.BufferSize = CayenneLppGetSize( );
   // printf( "\n\r\n\r######   AppData Buffer: ");
//    printf( "%X", AppData.Buffer );
    if( LmHandlerSend( &AppData, LORAMAC_HANDLER_UNCONFIRMED_MSG ) == LORAMAC_HANDLER_SUCCESS )
    {
#if CONFIG_USE_LEDS
       // Switch LED 1 ON
        GpioWrite( &Led1, 1 );
        TimerStart( &Led1Timer );
#endif
        TimerStart( &Led1Timer );

    }
}

static void StartTxProcess( LmHandlerTxEvents_t txEvent )
{
    switch( txEvent )
    {
    default:
        // Intentional fall through
    case LORAMAC_HANDLER_TX_ON_TIMER:
        {
            // Schedule 1st packet transmission
            TimerInit( &TxTimer, OnTxTimerEvent );
            TimerSetValue( &TxTimer, TxPeriodicity );
            OnTxTimerEvent( NULL );
        }
        break;
    case LORAMAC_HANDLER_TX_ON_EVENT:
        {
        }
        break;
    }
}

static void UplinkProcess( void )
{
    uint8_t isPending = 0;
    CRITICAL_SECTION_BEGIN( );
    isPending = IsTxFramePending;
    IsTxFramePending = 0;
    CRITICAL_SECTION_END( );
    if( isPending == 1 )
    {
    	if(globalCnt>=1){
            PrepareTxFrame( );
            globalCnt = 0;
    	}else{
    		globalCnt++;
    	}
    }
}

static void FuotaProcess( void )
{
    uint8_t isPending = 0;
    CRITICAL_SECTION_BEGIN( );
    isPending = IsTxFramePending;
    IsTxFramePending = 0;
    CRITICAL_SECTION_END( );
    if( isPending == 1 )
    {
    	switch(fuotaState)
        {
        default:
            // Intentional fall through
        case IDLE:
            {
            	fuotaState = CONF_CLASS_C;
            }
            break;
        case CONF_CLASS_C:
            {
            	ConfirmClassC_FUOTA();
            }
            break;

        case CONF_READY:
            {
            	Ready_for_FUOTA();
            }
            break;


        case FRAGMENT_RECEIVING:
            {
            	if(get_FragmentCnt()!=fragmentCnt_old){
               	 RCV_Fragment_Answer();
               	 fragmentCnt_old = get_FragmentCnt();
            	}

            }
            break;

        case Error_State:
            {
            	Error_FUOTA();
            }
            break;

        case FINISH:

            {
            	FINISH_Answer();
            }
            break;

        case UPDATE_NODE:
            {
            	LmHandlerRequestClass(CLASS_A);
            	fuotaState = IDLE;
            }
            break;
        }
    }
}

static void OnTxPeriodicityChanged( uint32_t periodicity )
{
    TxPeriodicity = periodicity;

    if( TxPeriodicity == 0 )
    { // Revert to application default periodicity
        TxPeriodicity = APP_TX_DUTYCYCLE + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
    }

    // Update timer periodicity
    TimerStop( &TxTimer );
    TimerSetValue( &TxTimer, TxPeriodicity );
    TimerStart( &TxTimer );
}

static void OnTxFrameCtrlChanged( LmHandlerMsgTypes_t isTxConfirmed )
{
    LmHandlerParams.IsTxConfirmed = isTxConfirmed;
}

static void OnPingSlotPeriodicityChanged( uint8_t pingSlotPeriodicity )
{
    LmHandlerParams.PingSlotPeriodicity = pingSlotPeriodicity;
}

/*!
 * Function executed on TxTimer event
 */
static void OnTxTimerEvent( void* context )
{
    TimerStop( &TxTimer );

    IsTxFramePending = 1;

    // Schedule next transmission
    TimerSetValue( &TxTimer, TxPeriodicity );
    TimerStart( &TxTimer );
}


/*!
 * Function executed on Led 1 Timeout event
 */
#if PL_CONFIG_USE_LED1
static void OnLed1TimerEvent( void* context )
{
    TimerStop( &Led1Timer );
				   
   // Switch LED 1 OFF
    GpioWrite( &Led1, 0 );
}
#endif
 

/*!
 * Function executed on Led 2 Timeout event
 */
#if PL_CONFIG_USE_LED2
static void OnLed2TimerEvent( void* context )
{
    TimerStop( &Led2Timer );
				   
    // Switch LED 2 OFF
    GpioWrite( &Led2, 0 );
}
#endif
 

/*!
 * \brief Function executed on Beacon timer Timeout event
 */
static void OnLedBeaconTimerEvent( void* context )
{
#if PL_CONFIG_USE_LED2
    GpioWrite( &Led2, 1 );
    TimerStart( &Led2Timer );
#endif
							 

    TimerStart( &LedBeaconTimer );
}
