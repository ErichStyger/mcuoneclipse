/*! *********************************************************************************
 * \addtogroup HID Device
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 * \file app.c
 * This file is the source file for the HID Device application
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
/* Framework / Drivers */
#include "RNG_Interface.h"
#include "Keyboard.h"
#include "LED.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "Panic.h"

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "battery_interface.h"
#include "device_info_interface.h"
#include "hid_interface.h"

/* Connection Manager */
#include "ble_conn_manager.h"

#ifdef NTAG_I2C
/* NTAG handler */
#include "app_ntag.h"
#endif // NTAG_I2C

#include "board.h"
#include "ApplMain.h"
#include "app.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define AXIS_MIN  100
#define AXIS_MAX  500
#define MOUSE_STEP 10

#define mBatteryLevelReportInterval_c   (10)        /* battery level report interval in seconds  */
#define mHidReportInterval_c   (100)        /* battery level report interval in msec  */

#ifdef NTAG_I2C
#define NDEF_OVERWRITE_TIMEOUT		10 		/* (seconds) - timeout when the NDEF message for BLE
											pairing is overwritten by default NDEF */
#endif
/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef enum
{
#if gAppUseBonding_d
    fastWhiteListAdvState_c,
#endif
    fastAdvState_c,
    slowAdvState_c
}advType_t;

typedef struct advState_tag{
    bool_t      advOn;
    advType_t   advType;
}advState_t;

typedef struct mouseHidReport_tag{
  uint8_t buttonStatus;
  uint8_t xAxis;
  uint8_t yAxis;
}mouseHidReport_t;
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/* Adv State */
static advState_t  mAdvState;
static deviceId_t  mPeerDeviceId = gInvalidDeviceId_c;

/* Service Data*/
static basConfig_t basServiceConfig = {service_battery, 0};
static disConfig_t disServiceConfig = {service_device_info};
static hidConfig_t hidServiceConfig = {service_hid, gHid_ReportProtocolMode_c};
static uint16_t cpHandles[] = { value_hid_control_point };

/* Application specific data*/
static tmrTimerID_t mAdvTimerId;
static tmrTimerID_t mHidDemoTimerId;
static tmrTimerID_t mBatteryMeasurementTimerId;
static uint16_t xAxis = AXIS_MIN;
static uint16_t yAxis = AXIS_MIN;

#ifdef NTAG_I2C
static tmrTimerID_t mNDEFTimerId;
static bool boNDEFState = FALSE;
#endif

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent);
static void BleApp_Config();

/* Timer Callbacks */
static void AdvertisingTimerCallback (void *);
static void TimerHidMouseCallback (void *);
static void BatteryMeasurementTimerCallback (void *);

static void BleApp_Advertise(void);

#ifdef NTAG_I2C
static void NDEFTimerCallback(void *);
#endif

/* Mouse events */
static void SendReport(mouseHidReport_t *pReport);
static void MoveMouseLeft(uint8_t pixels);
static void MoveMouseRight(uint8_t pixels);
static void MoveMouseUp(uint8_t pixels);
static void MoveMouseDown(uint8_t pixels);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */
void BleApp_Init(void)
{
    /* Initialize application support for drivers */
    BOARD_InitAdc();
}

/*! *********************************************************************************
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(void)
{
#if gAppUseBonding_d
    if (gcBondedDevices > 0)
    {
        mAdvState.advType = fastWhiteListAdvState_c;
    }
    else
    {
#endif
        mAdvState.advType = fastAdvState_c;
#if gAppUseBonding_d
    }
#endif

    BleApp_Advertise();
}

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
    {
        uint32_t timeout = NDEF_OVERWRITE_TIMEOUT;

#ifdef NTAG_I2C

        switch (events)
            {
            case gKBD_EventPressPB1_c:  // short press of SW4
                {
                BleApp_Start();
                boNDEFState = TRUE;   // pairing via NDEF is allowed in case the apk. is running
                break;
                }

            case gKBD_EventPressPB2_c:  // short press of SW3
                {
                if (boNDEFState)
                    {
                    /* added to copy the pairing NDEF message to NTAG_I2C chip */
                    NDEF_pairing_write(); // NTAG
                    Led3On(); // green LED is lighting
                    /* Start advertising timer */
                    TMR_StartLowPowerTimer(mNDEFTimerId, gTmrLowPowerSecondTimer_c,
                            TmrSeconds(timeout), NDEFTimerCallback, NULL);
                    }
                break;
                }

            case gKBD_EventLongPB1_c:   // long press of SW4
                {
                if (mPeerDeviceId != gInvalidDeviceId_c)
                    {
                    Gap_Disconnect(mPeerDeviceId);
                    boNDEFState = FALSE;
                    }
                break;
                }

            case gKBD_EventLongPB2_c:   // long press of SW3
                {
                /* nothing action */
                break;
                }

            default:
                break;
            }

#else // NTAG_I2C

        switch (events)
            {
            case gKBD_EventPressPB1_c:
                {
                BleApp_Start();
                break;
                }

            case gKBD_EventPressPB2_c:
                {
                hidProtocolMode_t protocolMode;

                /* Toggle Protocol Mode */
                Hid_GetProtocolMode(service_hid, &protocolMode);
                protocolMode = (protocolMode == gHid_BootProtocolMode_c)?gHid_ReportProtocolMode_c:gHid_BootProtocolMode_c;
                Hid_SetProtocolMode(service_hid, protocolMode);
                break;
                }

            case gKBD_EventLongPB1_c:
                {
                if (mPeerDeviceId != gInvalidDeviceId_c)
                Gap_Disconnect(mPeerDeviceId);
                break;
                }

            case gKBD_EventLongPB2_c:
                {
                break;
                }

            default:
            break;
            }
#endif // NTAG_I2C
    }

/*! *********************************************************************************
* \brief        Handles BLE generic callback.
*
* \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
********************************************************************************** */
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    /* Call BLE Conn Manager */
    BleConnManager_GenericEvent(pGenericEvent);
    
    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:    
        {
            BleApp_Config();
        }
        break;    
        
        case gAdvertisingParametersSetupComplete_c:
        {
            App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
        }
        break;         

        default: 
            break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{
    /* Configure as GAP peripheral */
    BleConnManager_GapPeripheralConfig();

    /* Register for callbacks*/
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    GattServer_RegisterHandlesForWriteNotifications(sizeof(cpHandles), cpHandles);    
       
    /* Setup Advertising and scanning data */
    Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);

    mAdvState.advOn = FALSE;

        /* Start services */
        basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
        Bas_Start(&basServiceConfig);
        Dis_Start(&disServiceConfig);
        Hid_Start(&hidServiceConfig);

        /* Allocate application timers */
        mAdvTimerId = TMR_AllocateTimer();
        mHidDemoTimerId = TMR_AllocateTimer();
        mBatteryMeasurementTimerId = TMR_AllocateTimer();
#ifdef NTAG_I2C
        mNDEFTimerId = TMR_AllocateTimer();
#endif
    }

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will satrt after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    uint32_t timeout = 0;

    switch (mAdvState.advType)
    {
#if gAppUseBonding_d
        case fastWhiteListAdvState_c:
        {
            gAdvParams.minInterval = gFastConnMinAdvInterval_c;
            gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
            gAdvParams.filterPolicy = gProcessWhiteListOnly_c;
            timeout = gFastConnWhiteListAdvTime_c;
        }
        break;
#endif
        case fastAdvState_c:
        {
            gAdvParams.minInterval = gFastConnMinAdvInterval_c;
            gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
            gAdvParams.filterPolicy = gProcessAll_c;
            timeout = gFastConnAdvTime_c - gFastConnWhiteListAdvTime_c;
        }
        break;

        case slowAdvState_c:
        {
            gAdvParams.minInterval = gReducedPowerMinAdvInterval_c;
            gAdvParams.maxInterval = gReducedPowerMinAdvInterval_c;
            gAdvParams.filterPolicy = gProcessAll_c;
            timeout = gReducedPowerAdvTime_c;
        }
        break;
    }
    
    /* Set advertising parameters*/
    Gap_SetAdvertisingParameters(&gAdvParams);

    /* Start advertising timer */
    TMR_StartLowPowerTimer(mAdvTimerId,gTmrLowPowerSecondTimer_c,
               TmrSeconds(timeout), AdvertisingTimerCallback, NULL);
}

/*! *********************************************************************************
* \brief        Handles BLE Advertising callback from host stack.
*
* \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        {
            mAdvState.advOn = !mAdvState.advOn;
            LED_StopFlashingAllLeds();
            Led1Flashing();

            if(!mAdvState.advOn)
            {
                Led2Flashing();
                Led3Flashing();
                Led4Flashing();
            }
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
            break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE Connection callback from host stack.
*
* \param[in]    peerDeviceId        Peer device ID.
* \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
	/* Connection Manager to handle Host Stack interactions */
	BleConnManager_GapPeripheralEvent(peerDeviceId, pConnectionEvent);

    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
            mPeerDeviceId = peerDeviceId;

            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;            
        
            /* Subscribe client*/
            Bas_Subscribe(peerDeviceId);        
            Hid_Subscribe(peerDeviceId);

                /* UI */
                LED_StopFlashingAllLeds();
                Led1On();

#ifdef NTAG_I2C
                Led4On(); // If the HID demo is connected, the blue LED is lighting
                NDEF_Defaul_write(); // Default NXP NDEF message is wiritten to the NTAG I2C chip
#endif // NTAG_I2C

                /* Stop Advertising Timer*/
                TMR_StopTimer(mAdvTimerId);

                /* Start HID demo */
                TMR_StartLowPowerTimer(mHidDemoTimerId, gTmrLowPowerSingleShotMillisTimer_c,
                mHidReportInterval_c, TimerHidMouseCallback, NULL);

            /* Start battery measurements */
            TMR_StartLowPowerTimer(mBatteryMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                       TmrSeconds(mBatteryLevelReportInterval_c), BatteryMeasurementTimerCallback, NULL);            
        }
        break;
        
        case gConnEvtDisconnected_c:
        {
            /* Unsubscribe client */
            Bas_Unsubscribe();
            Hid_Unsubscribe();

            mPeerDeviceId = gInvalidDeviceId_c;

            if (pConnectionEvent->eventData.disconnectedEvent.reason == gHciConnectionTimeout_c)
            {
                /* Link loss detected*/
                BleApp_Start();
            }
            else
            {
              /* Connection was terminated by peer or application */
                BleApp_Start();
            }
        }
        break;
    default:
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles GATT server callback from host stack.
*
* \param[in]    deviceId        Peer device ID.
* \param[in]    pServerEvent    Pointer to gattServerEvent_t.
********************************************************************************** */
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
    uint16_t handle;
    uint8_t status;
    
    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWritten_c:
        {
            handle = pServerEvent->eventData.attributeWrittenEvent.handle;
            status = gAttErrCodeNoError_c;
            
            if (handle == value_hid_control_point)
            {
                status = Hid_ControlPointHandler(service_hid, pServerEvent->eventData.attributeWrittenEvent.aValue[0]);
            }
            GattServer_SendAttributeWrittenStatus(deviceId, handle, status);
        }
        break;
    default:
        break;
    }
}


/*! *********************************************************************************
* \brief        Handles advertising timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void AdvertisingTimerCallback(void * pParam)
{
    /* Stop and restart advertising with new parameters */
    Gap_StopAdvertising();

    switch (mAdvState.advType)
    {
#if gAppUseBonding_d
        case fastWhiteListAdvState_c:
        {
            mAdvState.advType = fastAdvState_c;
        }
        break;
#endif
        case fastAdvState_c:
        {
            mAdvState.advType = slowAdvState_c;
        }
        break;

        default:
        break;
    }
    BleApp_Advertise();
}

/*! *********************************************************************************
* \brief        Handles HID Mouse timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void TimerHidMouseCallback(void * pParam)
{
    if ((xAxis < AXIS_MAX) && (yAxis == AXIS_MIN))
    {
        MoveMouseRight(MOUSE_STEP);
        xAxis += MOUSE_STEP;
    }

    if ((xAxis == AXIS_MAX) && (yAxis < AXIS_MAX))
    {
        MoveMouseDown(MOUSE_STEP);
        yAxis += MOUSE_STEP;
    }
       
    if ((xAxis > AXIS_MIN) && (yAxis == AXIS_MAX))
    {
        MoveMouseLeft(MOUSE_STEP);
        xAxis -= MOUSE_STEP;
    }
       
    if ((xAxis == AXIS_MIN) && (yAxis > AXIS_MIN))
    {
        MoveMouseUp(MOUSE_STEP);
        yAxis -= MOUSE_STEP;
    }
       
    /* Start measurements */
    TMR_StartLowPowerTimer(mHidDemoTimerId, gTmrLowPowerSingleShotMillisTimer_c,
           mHidReportInterval_c, TimerHidMouseCallback, NULL);
}


/*! *********************************************************************************
* \brief        Handles battery measurement timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void BatteryMeasurementTimerCallback(void * pParam)
{
    basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_RecordBatteryMeasurement(basServiceConfig.serviceHandle, basServiceConfig.batteryLevel);
}

/*! *********************************************************************************
* \brief        Sends HID Report Over-the-Air.
*
* \param[in]    pReport        Pointer to mouseHidReport_t.
********************************************************************************** */
static void SendReport(mouseHidReport_t *pReport)
{
    hidProtocolMode_t protocolMode;

    /* Toggle Protocol Mode */
    Hid_GetProtocolMode(service_hid, &protocolMode);
    
    if (protocolMode == gHid_BootProtocolMode_c)
    {
        Hid_SendBootMouseInputReport(hidServiceConfig.serviceHandle, sizeof(mouseHidReport_t), pReport);
    }
    else if (protocolMode == gHid_ReportProtocolMode_c)
    {
        Hid_SendInputReport(hidServiceConfig.serviceHandle, sizeof(mouseHidReport_t), pReport);
    }
}

static void MoveMouseLeft(uint8_t pixels)
{
    mouseHidReport_t mouseReport = {0,0,0};
    mouseReport.xAxis = -pixels;
    SendReport(&mouseReport);
}

static void MoveMouseRight(uint8_t pixels)
{
    mouseHidReport_t mouseReport = {0,0,0};
    mouseReport.xAxis = pixels;
    SendReport(&mouseReport);
}

static void MoveMouseUp(uint8_t pixels)
{
    mouseHidReport_t mouseReport = {0,0,0};
    mouseReport.yAxis = -pixels;
    SendReport(&mouseReport);
}

static void MoveMouseDown(uint8_t pixels)
{
    mouseHidReport_t mouseReport = {0,0,0};
    mouseReport.yAxis = pixels;
    SendReport(&mouseReport);
}

#ifdef NTAG_I2C
/*! *********************************************************************************
 * \brief        Handles timer callback for writing NDEF messages
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void NDEFTimerCallback(void * pParam)
    {

        /* Stop Advertising Timer*/
        TMR_StopTimer(mNDEFTimerId);

        Led3Off(); // green LED off

        NDEF_Defaul_write(); // NTAG
    }

#endif // NTAG_I2C

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
