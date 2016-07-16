/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 09.11.2015
 * \brief Channel activity detection example
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

#define RF_FREQUENCY                                868000000 // Hz
#define LC1                                         868100000
#define LC2                                         868300000
#define LC3                                         868500000

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

#define RECEIVE_DELAY1								2500000

static TimerEvent_t TxPacketTimer;

static bool channelActivityDetected;
static bool txDone;
static bool cadDone;
static bool rxDone;
static bool sendPacket;

static uint8_t TxBuffer[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0' };
static uint32_t TxBufferSize = 12;

static uint8_t RxBuffer[64];
static uint32_t RxBufferSize;

static int8_t Snr;
static int16_t Rssi;

static uint32_t Channels[] = { LC1, LC2, LC3 };
static uint8_t SelectedChannel;

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
 * \brief Function executed on Radio Cad Done event
 */
void OnCadDone(bool channelActivityDetected);

/**
 * Main application entry point.
 */
int main(void)
{
    static uint32_t cnt[] = { 0, 0, 0 };
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
    RadioEvents.CadDone = OnCadDone;

    txDone = false;
	cadDone = false;
	channelActivityDetected = false;
	rxDone = false;
	sendPacket = false;

	SelectedChannel = 1;

    Radio.Init(&RadioEvents);
    PRINTF("TRACE: Radio initialized.\r\n");

    Radio.SetChannel(Channels[SelectedChannel]);

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

    srand1 (BoardGetRandomSeed() );
#if 0
    PRINTF("Start channel activity detection...\r\n");
    Radio.StartCad();

    while (1) {
        if (cadDone) {
            cadDone = false;
            if (channelActivityDetected) {
                PRINTF("Channel activity detected (%u. on channel %u).\r\n", ++cnt[SelectedChannel],
                        Channels[SelectedChannel]);
                DelayMs(100); /* Wait for Rx1 to open */
                Radio.SetChannel(Channels[0]); /* Set to default channel */
                Radio.Send(TxBuffer, TxBufferSize);
                while (!txDone) {
                };
                txDone = false;
                SelectedChannel = randr(0, 2);
                PRINTF("Channel activity detection on channel %u activated.\r\n",
                        Channels[SelectedChannel]);
                Radio.SetChannel(Channels[SelectedChannel]);
            }
            DelayMs(50);
            Radio.StartCad();
        }
    }
#else
    PRINTF("Start package receiving...\r\n");
	Radio.Rx(0);

	while(1){
		if(rxDone) {
			rxDone = false;
//			TimerSetValue(&TxPacketTimer, RECEIVE_DELAY1);
//			TimerStart(&TxPacketTimer);
			PRINTF("TRACE: %s - Incoming message. %u bytes. (%d/%d)\r\n", __FUNCTION__, RxBufferSize, Rssi, Snr);
			for(uint8_t i = 0; i < RxBufferSize; i++) {
				PRINTF("%02x", RxBuffer[i]);
			}
			PRINTF("\r\n");
			Radio.Rx(0);
		}
	}
#endif
}

void OnCadDone(bool cad)
{
    Radio.Sleep();
    cadDone = true;
    channelActivityDetected = cad;
}

void OnTxDone(void)
{
	Radio.Sleep();
    PRINTF("TRACE: Test frame on channel %u sent.\r\n", Channels[0]);
    txDone = true;
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    Radio.Sleep();
    rxDone = true;
    RxBufferSize = size;
    Rssi = rssi;
    Snr = snr;
    memcpy(RxBuffer, payload, RxBufferSize);
}

void OnTxTimeout(void)
{
	PRINTF("TRACE: %s.\r\n", __FUNCTION__);
    Radio.Sleep();
}

void OnRxTimeout(void)
{
	PRINTF("TRACE: %s.\r\n", __FUNCTION__);
    Radio.Sleep();
}

void OnRxError(void)
{
	PRINTF("TRACE: %s.\r\n", __FUNCTION__);
    Radio.Sleep();
}
