/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 09.11.2015
 * \brief SensorApp node implementation
 *
 */
#include <string.h>
#include "board.h"
#include "radio.h"

#if defined( USE_BAND_433 )

#define RF_FREQUENCY                                434000000 // Hz

#elif defined( USE_BAND_470 )

#define RF_FREQUENCY                                470000000 // Hz

#elif defined( USE_BAND_868 )

#define RF_FREQUENCY                                868100000 // Hz

#elif defined( USE_BAND_915 )

#define RF_FREQUENCY                                915000000 // Hz

#else
#error "Please define a frequency band in the compiler options."
#endif

#define TX_OUTPUT_POWER                             2        // dBm

#if defined( USE_MODEM_LORA )

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
//  1: 250 kHz,
//  2: 500 kHz,
//  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
//  2: 4/6,
//  3: 4/7,
//  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#elif defined( USE_MODEM_FSK )

#define FSK_FDEV                                    25e3      // Hz
#define FSK_DATARATE                                50e3      // bps
#define FSK_BANDWIDTH                               50e3      // Hz
#define FSK_AFC_BANDWIDTH                           83.333e3  // Hz
#define FSK_PREAMBLE_LENGTH                         5         // Same for Tx and Rx
#define FSK_FIX_LENGTH_PAYLOAD_ON                   false

#else
#error "Please define a modem in the compiler options."
#endif

typedef enum {
    LOWPOWER, RX, RX_TIMEOUT, RX_ERROR, TX, TX_TIMEOUT,
} States_t;

/*!
 * Defines the application data transmission duty cycle
 */
#define APP_TX_DUTYCYCLE                            5000000  // 5 [s] value in us
#define APP_RX_TIMEOUT                              0        // continuous

/*!
 * User application data buffer size
 */
#define LORAWAN_APP_DATA_SIZE                       15

/*!
 * User application data buffer size
 */
#define LORAWAN_APP_DATA_MAX_SIZE                           64

/*!
 * User application data size
 */
static uint8_t AppDataSize = LORAWAN_APP_DATA_SIZE;

/*!
 * User application data
 */
static uint8_t AppData[LORAWAN_APP_DATA_MAX_SIZE];

static uint8_t ReceivedDataSize = 0;

static TimerEvent_t TxNextPacketTimer;

static bool AppLedStateOn = false;
static bool AppSensorTransmissionStateOn = true;

volatile bool AppSensorTransmissionStateChanged = false;
volatile bool AppLedStateChanged = false;

static States_t State = TX;

static int8_t RssiValue = 0;
static int8_t SnrValue = 0;

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone(void);

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError(void);

/*!
 * \brief Function executed on TxNextPacket Timeout event
 */
static void OnTxNextPacketTimerEvent(void)
{
    TimerStop(&TxNextPacketTimer);
    State = TX;
}

/*!
 * Prepares the frame buffer to be sent
 */
static void PrepareTxFrame(void)
{
    accel_sensor_data_t sensorData;
    uint8_t batteryLevel = 0;

    if (FxosReadSensorData(&sensorData) == FAIL) {
        PRINTF("ERROR: Failed to retrieve sensor data!\r\n");
        return;
    }

    batteryLevel = BoardGetBatteryLevel();       // 1 (very low) to 254 (fully charged)

    AppData[0] = AppLedStateOn;
    AppData[1] = AppSensorTransmissionStateOn;
    AppData[2] = (sensorData.accelX >> 8) & 0xFF;
    AppData[3] = sensorData.accelX & 0xFF;
    AppData[4] = (sensorData.accelY >> 8) & 0xFF;
    AppData[5] = sensorData.accelY & 0xFF;
    AppData[6] = (sensorData.accelZ >> 8) & 0xFF;
    AppData[7] = sensorData.accelZ & 0xFF;
    AppData[8] = batteryLevel;
    AppData[9] = (sensorData.magX >> 8) & 0xFF;
    AppData[10] = sensorData.magX & 0xFF;
    AppData[11] = (sensorData.magY >> 8) & 0xFF;
    AppData[12] = sensorData.magY & 0xFF;
    AppData[13] = (sensorData.magZ >> 8) & 0xFF;
    AppData[14] = sensorData.magZ & 0xFF;
}

static void ProcessRxFrame(void)
{
    if (AppData[0] == 1 && !AppLedStateOn) {
        AppLedStateOn = true;
        AppLedStateChanged = true;
        PRINTF("TRACE: LED was remotely turned on.\r\n");
    } else if (AppData[0] == 0 && AppLedStateOn) {
        AppLedStateOn = false;
        AppLedStateChanged = true;
        PRINTF("TRACE: LED was remotely turned off.\r\n");
    }

    if (AppData[1] == 1 && !AppSensorTransmissionStateOn) {
        PRINTF("TRACE: Sensor data collecting was remotely turned on.\r\n");
        AppSensorTransmissionStateOn = true;
        AppSensorTransmissionStateChanged = true;
        State = TX;
    } else if (AppData[1] == 0 && AppSensorTransmissionStateOn) {
        PRINTF("TRACE: Sensor data collecting was remotely turned off.\r\n");
        AppSensorTransmissionStateOn = false;
        AppSensorTransmissionStateChanged = true;
    }
}

/**
 * Main application entry point.
 */
int main(void)
{
// Target board initialisation
    BoardInitMcu();
    PRINTF("\r\n\r\nTRACE: Mcu initialized.\r\n");
    BoardInitPeriph();
    PRINTF("TRACE: Peripherals initialized.\r\n");

// Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    PRINTF("TRACE: Radio initialized.\r\n");

    Radio.SetChannel(RF_FREQUENCY);

#if defined( USE_MODEM_LORA )

    Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
            LORA_SPREADING_FACTOR, LORA_CODINGRATE,
            LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
            true, 0, 0, LORA_IQ_INVERSION_ON, 3000000 );

    Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
            LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
            LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
            0, true, 0, 0, LORA_IQ_INVERSION_ON, true );

#elif defined( USE_MODEM_FSK )

    Radio.SetTxConfig( MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
            FSK_DATARATE, 0,
            FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
            true, 0, 0, 0, 3000000 );

    Radio.SetRxConfig( MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
            0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
            0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
            0, 0,false, true );

#else
#error "Please define a frequency band in the compiler options."
#endif

    TimerInit(&TxNextPacketTimer, OnTxNextPacketTimerEvent);

    PRINTF("\r\nSensor Application starting...\r\n");

    while (1) {
        switch (State) {
            case RX:
                PRINTF("TRACE: Frame received.\r\n");
                ProcessRxFrame();
                if (AppLedStateChanged) {
                    if (AppLedStateOn)
                        GpioWrite(&Led1, 0);
                    else
                        GpioWrite(&Led1, 1);
                }
                if (AppSensorTransmissionStateChanged && AppSensorTransmissionStateOn) {
                    State = TX;
                    continue;
                } else if (AppSensorTransmissionStateChanged && !AppSensorTransmissionStateOn) {
                    TimerStop(&TxNextPacketTimer);
                }
                Radio.Rx(APP_RX_TIMEOUT);
                State = LOWPOWER;
                break;
            case TX:
                PRINTF("TRACE: Trying to send frame...\r\n");
                PrepareTxFrame();
                Radio.Send(AppData, AppDataSize);
                if (AppSensorTransmissionStateOn) {
                    TimerSetValue(&TxNextPacketTimer, APP_TX_DUTYCYCLE);
                    TimerStart(&TxNextPacketTimer);
                }
                State = LOWPOWER;
                break;
            case RX_TIMEOUT:
            case RX_ERROR:
                PRINTF("DEBUG: Rx timeout occured!\r\n");
                Radio.Rx(APP_RX_TIMEOUT);
                State = LOWPOWER;
                break;
            case TX_TIMEOUT:
                PRINTF("DEBUG: Tx timeout occured!\r\n");
                Radio.Rx(APP_RX_TIMEOUT);
                State = LOWPOWER;
                break;
            case LOWPOWER:
            default:
                // Set low power
                break;
        }

        TimerLowPowerHandler();
    }
}

void OnTxDone(void)
{
    PRINTF("TRACE: Frame sent successfully.\r\n");
    Radio.Rx(APP_RX_TIMEOUT);
    State = LOWPOWER;
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    Radio.Sleep();
    ReceivedDataSize = size;
    memcpy(AppData, payload, ReceivedDataSize);
    RssiValue = rssi;
    SnrValue = snr;
    PRINTF("TRACE: Measured rssi and snr values (%d / %d)\r\n", RssiValue, SnrValue);
    State = RX;
}

void OnTxTimeout(void)
{
    Radio.Sleep();
    State = TX_TIMEOUT;
}

void OnRxTimeout(void)
{
    Radio.Sleep();
    State = RX_TIMEOUT;
}

void OnRxError(void)
{
    Radio.Sleep();
    State = RX_ERROR;
}
