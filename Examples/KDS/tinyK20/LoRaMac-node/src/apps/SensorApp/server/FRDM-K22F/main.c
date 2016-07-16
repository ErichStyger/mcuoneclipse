/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 09.11.2015
 * \brief SensorApp server implementation
 *
 */
#include <string.h>
#include "board.h"
#include "radio.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

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
    LOWPOWER, RX, RX_TIMEOUT, RX_ERROR, TX, TX_TIMEOUT, BUTTON_PUSHED
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

static bool AppLedStateOn = false;
static bool AppSensorTransmissionStateOn = true;

static States_t State = LOWPOWER;

static accel_sensor_data_t SensorData;

static int8_t RssiValue = 0;
static int8_t SnrValue = 0;

bool SwitchAPushEvent = false;
bool SwitchBPushEvent = false;

/*!
 * \brief Switch A IRQ callback
 */
void SwitchAIrq( void );

/*!
 * \brief Switch B IRQ callback
 */
void SwitchBIrq( void );

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone( void );

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError( void );

/*!
 * Prepares the frame buffer to be sent
 */
static void PrepareTxFrame( void )
{
    AppData[0] = AppLedStateOn;
    AppData[1] = AppSensorTransmissionStateOn;
}

static uint8_t ProcessRxFrame( void )
{
    if ( ReceivedDataSize != AppDataSize ) {
        LOG_ERROR("Unexpected data format in rx frame!");
        return FAIL;
    }

    AppLedStateOn = (AppData[0] == 0 ? false : true);
    AppSensorTransmissionStateOn = (AppData[1] == 0 ? false : true);

    SensorData.accelX = (uint16_t)((AppData[2] << 8) | AppData[3]);
    SensorData.accelY = (uint16_t)((AppData[4] << 8) | AppData[5]);
    SensorData.accelZ = (uint16_t)((AppData[6] << 8) | AppData[7]);

    SensorData.magX = (uint16_t)((AppData[9] << 8) | AppData[10]);
    SensorData.magY = (uint16_t)((AppData[11] << 8) | AppData[12]);
    SensorData.magZ = (uint16_t)((AppData[13] << 8) | AppData[14]);

    return SUCCESS;
}

/**
 * Main application entry point.
 */
int main( void )
{
// Target board initialisation
    BoardInitMcu();
    LOG_DEBUG("Mcu initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

    /* Switch A & B */
    GpioSetInterrupt(&SwitchA, IRQ_FALLING_EDGE, IRQ_LOW_PRIORITY, SwitchAIrq);
    GpioSetInterrupt(&SwitchB, IRQ_FALLING_EDGE, IRQ_LOW_PRIORITY, SwitchBIrq);

// Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    LOG_DEBUG("Radio initialized.");

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

    Radio.Rx(APP_RX_TIMEOUT);

    LOG_DEBUG("\r\nSensor Application starting...");

    while (1) {
        switch (State) {
            case BUTTON_PUSHED:
                if ( SwitchAPushEvent ) {
                    SwitchAPushEvent = false;
                    if ( AppLedStateOn )
                        LOG_TRACE("Remotely disable LED.");
                    else
                        LOG_TRACE("Remotely enable LED.");
                    AppLedStateOn = !AppLedStateOn;
                    State = TX;
                } else if ( SwitchBPushEvent ) {
                    SwitchBPushEvent = false;
                    if ( AppSensorTransmissionStateOn )
                        LOG_TRACE("Remotely disable sensor data collecting.");
                    else
                        LOG_TRACE("Remotely enable sensor data collecting.");
                    AppSensorTransmissionStateOn = !AppSensorTransmissionStateOn;
                    State = TX;
                } else {
                    State = LOWPOWER;
                }
                break;
            case RX:
                LOG_TRACE("Frame received.");
                if ( ProcessRxFrame() == SUCCESS ) {
                    LOG_DEBUG_BARE("DATA: Accelerometer (x/y/z) \t%d \t%d \t%d\r\n",
                            SensorData.accelX, SensorData.accelY, SensorData.accelZ);
                    LOG_DEBUG_BARE("DATA: Magnetometer (x/y/z) \t%d \t%d \t%d\r\n", SensorData.magX,
                            SensorData.magY, SensorData.magZ);
                }
                Radio.Rx(APP_RX_TIMEOUT);
                State = LOWPOWER;
                break;
            case TX:
                LOG_TRACE("Trying to send frame...");
                PrepareTxFrame();
                Radio.Send(AppData, AppDataSize);
                State = LOWPOWER;
                break;
            case RX_TIMEOUT:
            case RX_ERROR:
                LOG_TRACE("Rx timeout occured!");
                Radio.Rx(APP_RX_TIMEOUT);
                State = LOWPOWER;
                break;
            case TX_TIMEOUT:
                LOG_TRACE("Tx timeout occured!");
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

void SwitchAIrq( void )
{
    DelayMs(20);    // Software debouncing
    PORT_HAL_ClearPortIntFlag (PORTB_BASE_PTR);
    SwitchAPushEvent = true;
    State = BUTTON_PUSHED;
}

void SwitchBIrq( void )
{
    DelayMs(20);    // Software debouncing
    PORT_HAL_ClearPortIntFlag (PORTC_BASE_PTR);
    SwitchBPushEvent = true;
    State = BUTTON_PUSHED;
}

void OnTxDone( void )
{
    LOG_TRACE("Frame sent successfully.");
    Radio.Rx(APP_RX_TIMEOUT);
    State = LOWPOWER;
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    Radio.Sleep();
    ReceivedDataSize = size;
    memcpy(AppData, payload, ReceivedDataSize);
    RssiValue = rssi;
    SnrValue = snr;
    LOG_TRACE("Measured rssi and snr values (%d / %d)", RssiValue, SnrValue);
    State = RX;
}

void OnTxTimeout( void )
{
    Radio.Sleep();
    State = TX_TIMEOUT;
}

void OnRxTimeout( void )
{
    Radio.Sleep();
    State = RX_TIMEOUT;
}

void OnRxError( void )
{
    Radio.Sleep();
    State = RX_ERROR;
}
