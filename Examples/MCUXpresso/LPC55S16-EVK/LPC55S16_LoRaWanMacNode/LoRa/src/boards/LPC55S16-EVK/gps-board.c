/*!
 * \file      gps-board.c
 *
 * \brief     Target board GPS driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "board-config.h"
#include "board.h"
#include "gpio.h"
#include "gps.h"
#include "uart.h"
#include "gps-board.h"
#include "delay.h"
#include "lpm-board.h"
#include "timer.h"
#include "utilities.h"

#if BOARD_CONFIG_HAS_GNSS

#define DATA_PARSING_RETRIES			10
#define PERIOD_TO_CHECK_GPS_SILENT		300

/*!
 * Retries for parsing of the nmea string
 */
static uint8_t retry = DATA_PARSING_RETRIES;

/*!
 * Pin and Uart definition
 */
extern Uart_t Uart1;

/*!
 * Pin for RESET of the GPS
 */
static Gpio_t gpsResetPin;

/*!
 * Pin for the PPS signal of the GPS
 */
static Gpio_t gpsPpsPin;

/*!
 * Timer used to check when GPS is silent and messages can be sent
 */
static TimerEvent_t CheckGpsOutputTimer;

/*!
 * Function executed on GpsSilentTimer event
 */
static void OnCheckGpsOutputTimerEvent( void* context );

#if 0 /* not used */
/*!
 * Function to calculate checksums and add them to the UBX message
 */
static void AddChecksumToUbxMsg( uint8_t* ubxMessage, uint8_t fullMessageLength);
#endif

/*!
 * Bool to check if GPS is currently silent or sending messages on UART
 */
static bool GpsIsSilent = false;

/*!
 * Bool to check we are waiting for the GPS to be silent
 */
static bool WaitingForSilentGps = false;

/*!
 * UBX Message for stop the GPS module (UBX-RXM-PMREQ)
 */
static const uint8_t ubxPmreqStop[] = {
		0xb5, /* Header */
		0x62, /* Header */
		0x02, /* Class */
		0x41, /* ID */
		0x10, /* Length (LSB) */
		0x00, /* Length (MSB) */
		0x00, /* Version */
		0x00, /* Reserved */
		0x00, /* Reserved */
		0x00, /* Reserved */
		0x00, /* Duration */
		0x00, /* Duration */
		0x00, /* Duration */
		0x00, /* Duration */
		0x02, /* Flags (Enabled Backup Mode) */
		0x00, /* Flags */
		0x00, /* Flags */
		0x00, /* Flags */
		0x00, /* Wake-Up Sources */
		0x00, /* Wake-Up Sources */
		0x00, /* Wake-Up Sources */
		0x00, /* Wake-Up Sources */
		0x55, /* CK_A */
		0x2B, /* CK_B */
};

/*!
 * \brief Buffer holding the  raw data received from the gps
 */
static uint8_t NmeaString[128];
#endif

/*!
 * \brief Maximum number of data byte that we will accept from the GPS
 */
static volatile uint8_t NmeaStringSize = 0;

void GpsMcuOnPpsSignal(void *context) {
#if BOARD_CONFIG_HAS_GNSS
	bool parseData = false;

	GpsPpsHandler(&parseData);

	if (parseData == true && Uart1.IsInitialized == false) {
		/* If data should be parsed, enabled uart and wait for receving the gps info */
		UartInit(&Uart1, UART_2, NC, NC);
		UartConfig(&Uart1, RX_TX, GNSS_UART_BAUDRATE, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL);
	}
#endif
}

void GpsMcuInvertPpsTrigger(void) {
	/* Nothing to do. Not implemented */
}

/*!
 * CAUTION:
 * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
 * You can also use the pin configuration tool of NXP.
 * This init function doesn't care about the defined pins
 */
void GpsMcuInit(void) {
#if BOARD_CONFIG_HAS_GNSS
	NmeaStringSize = 0;
	Uart1.IrqNotify = GpsMcuIrqNotify;

	GpsMcuStart();

	GpioInit(&gpsPpsPin, GNSS_PPS_PIN, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
	GpioSetInterrupt(&gpsPpsPin, IRQ_FALLING_EDGE, IRQ_VERY_LOW_PRIORITY, &GpsMcuOnPpsSignal);

  TimerInit( &CheckGpsOutputTimer, OnCheckGpsOutputTimerEvent );
  TimerSetValue( &CheckGpsOutputTimer, PERIOD_TO_CHECK_GPS_SILENT );
#endif
}

void GpsMcuStart(void) {
#if BOARD_CONFIG_HAS_GNSS
	/* Reset the Module */
	GpioInit(&gpsResetPin, GNSS_RESET_PIN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
	DelayMs(10);
	GpioInit(&gpsResetPin, GNSS_RESET_PIN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);

	/* Disable stop mode, so interrupts from GPS can fire an event */
	LpmSetStopMode(LPM_GPS_ID, LPM_DISABLE);
#endif
}

/*!
 * This function can take up so several seconds, because we need to wait for the GNSS module
 * to be silent in order to send a stop command.
 */
void GpsMcuStop(void) {
#if BOARD_CONFIG_HAS_GNSS
	/* Init of the UART to receive and send data */
	if(Uart1.IsInitialized == false){
		UartInit(&Uart1, UART_2, NC, NC);
		UartConfig(&Uart1, RX_TX, GNSS_UART_BAUDRATE, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL);
		DelayMs(PERIOD_TO_CHECK_GPS_SILENT);
	}

	/* Start process to periodically check if the GNSS module is silent
	 * (means stop sending data on the UART)
	 */
	GpsIsSilent = true;
	TimerStart( &CheckGpsOutputTimer );
	WaitingForSilentGps = true;
	while(WaitingForSilentGps == true){
		DelayMs(100);
	}

	/* If the GNSS module is silent finally, we can send the stop command over UART */
	CRITICAL_SECTION_BEGIN( );
	UartPutBuffer(&Uart1, (uint8_t*) ubxPmreqStop, 24);
	DelayMs(250);
	UartDeInit(&Uart1);
	CRITICAL_SECTION_END( );

	/* Enable stop mode again when GPS is not used anymore */
	LpmSetStopMode(LPM_GPS_ID, LPM_ENABLE);
#endif
}

void GpsMcuProcess(void) {
	/* Nothing to do */
}

void GpsMcuIrqNotify(UartNotifyId_t id) {
#if BOARD_CONFIG_HAS_GNSS
	uint8_t data;
	if (id == UART_NOTIFY_RX) {
		if (UartGetChar(&Uart1, &data) == 0) {
			if ((data == '$') || (NmeaStringSize >= 127)) {
				NmeaStringSize = 0;
			}

			NmeaString[NmeaStringSize++] = (int8_t) data;

			if (data == '\n') {
				NmeaString[NmeaStringSize++] = '\0';
				if(GpsParseGpsData((int8_t*) NmeaString, NmeaStringSize) && retry-- <= 0){
					if(WaitingForSilentGps == false){ /* Check if stop procedure is ongoing */
						UartDeInit(&Uart1);
					}
					retry = DATA_PARSING_RETRIES;
				}
			}
		}
		/* We received something and this means, the GNSS module is not silent */
		GpsIsSilent = false;
	}
#endif
}

#if BOARD_CONFIG_HAS_GNSS
static void OnCheckGpsOutputTimerEvent( void* context ){
	/* Stop timer, check if GNSS module was silent since last execution, and if not, start timer again */
	TimerStop( &CheckGpsOutputTimer );
	if( GpsIsSilent == true ){
		WaitingForSilentGps = false;
	}
	else {
		GpsIsSilent = true;
		TimerStart( &CheckGpsOutputTimer );
	}
}
#endif

#if 0 /* not used */
static void AddChecksumToUbxMsg( uint8_t* ubxMessage, uint8_t fullMessageLength){
	uint8_t CK_A = 0, CK_B = 0;

	for(uint8_t i = 2;i < fullMessageLength-2; i++) {
		CK_A = CK_A + ubxMessage[i];
		CK_B = CK_B + CK_A;
	}

	ubxMessage[fullMessageLength-2] = CK_A;
	ubxMessage[fullMessageLength-1] = CK_B;
}
#endif

