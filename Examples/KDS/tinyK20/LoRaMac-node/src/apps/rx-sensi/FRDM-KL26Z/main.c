/*
 / _____)             _              | |
 ( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
 (______/|_____)_|_|_| \__)_____)\____)_| |_|
 (C)2013 Semtech

 Description: Radio sensitivity test.
 When LED1 stops blinking LoRa packets aren't received any more and
 the sensitivity level has been reached.
 By reading the RF generator output power we can estimate the board
 sensitivity.

 License: Revised BSD License, see LICENSE.TXT file include in the project

 Maintainer: Miguel Luis and Gregory Cristian
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

#define RF_FREQUENCY                                868300000 // Hz

#elif defined( USE_BAND_915 )

#define RF_FREQUENCY                                915000000 // Hz

#else
#error "Please define a frequency band in the compiler options."
#endif

#if defined( USE_MODEM_LORA )

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
//  1: 250 kHz,
//  2: 500 kHz,
//  3: Reserved]
#define LORA_SPREADING_FACTOR                       7        // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
//  2: 4/6,
//  3: 4/7,
//  4: 4/8]
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_FIX_LENGTH_PAYLOAD                     0
#define LORA_CRC_ON                                 true
#define LORA_IQ_INVERSION_ON                        false

#elif defined( USE_MODEM_FSK )

#define FSK_DATARATE                                50e3      // bps
#define FSK_BANDWIDTH                               50e3      // Hz
#define FSK_AFC_BANDWIDTH                           83.333e3  // Hz
#define FSK_PREAMBLE_LENGTH                         5         // Same for Tx and Rx
#define FSK_FIX_LENGTH_PAYLOAD_ON                   false

#else
#error "Please define a modem in the compiler options."
#endif

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

static TimerEvent_t HeartBeatTimer;
static bool heartBeat;
static bool rxReceived;
static uint8_t heartBeatCnt;
static uint8_t rxFrame[64];
static uint32_t rxFrameSize;

/*!
 * \brief Function executed on TxNextPacket Timeout event
 */
static void OnHeartBeatTimerTimerEvent( void )
{
    TimerStop(&HeartBeatTimer);
    heartBeat = true;
}

/*!
 * Main application entry point.
 */
int main( void )
{
    // Target board initialisation
    BoardInitMcu();
    LOG_DEBUG("Mcu initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

    // Radio initialization
    RadioEvents.RxDone = OnRxDone;

    rxReceived = false;
    heartBeat = true;
    heartBeatCnt = 0;

    Radio.Init(&RadioEvents);
    LOG_DEBUG("Radio initialized.");

    Radio.SetChannel(RF_FREQUENCY);

#if defined( USE_MODEM_LORA )

    Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
            LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
            LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
            LORA_FIX_LENGTH_PAYLOAD, LORA_CRC_ON, 0, 0, LORA_IQ_INVERSION_ON, true );

#elif defined( USE_MODEM_FSK )

    Radio.SetRxConfig( MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
            0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
            0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
            0, 0, false, true );

#else
#error "Please define a frequency band in the compiler options."
#endif

    Radio.Rx(0); // Continuous Rx

    LOG_DEBUG("Starting Rx sens application...");

    TimerInit(&HeartBeatTimer, OnHeartBeatTimerTimerEvent);
    TimerSetValue(&HeartBeatTimer, 1000000);

    while (1) {
        if ( heartBeat ) {
            heartBeat = false;
            TimerStart(&HeartBeatTimer);
            LOG_TRACE_BARE(".");
            if ( heartBeatCnt > 128 ) {
                LOG_TRACE_BARE("\r\n");
                heartBeatCnt = 0;
            } else {
                heartBeatCnt++;
            }
        }
        if ( rxReceived ) {
            rxReceived = false;
            heartBeatCnt = 0;
            LOG_TRACE_BARE("\r\nDATA: ");
            for ( uint32_t i = 0; i < rxFrameSize; i++ ) {
                LOG_TRACE_BARE("0x%02x ", rxFrame[i]);
            }
            LOG_TRACE_BARE("\r\n");
        }
        TimerLowPowerHandler();
    }
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    LOG_TRACE_BARE("\r\n");
    LOG_TRACE_BARE("Packet with %u bytes received.", size);
    rxReceived = true;
    rxFrameSize = size;
    memcpy(rxFrame, payload, rxFrameSize);
}
