/*
 * Logic.c
 *
 *  Created on: Feb 2, 2013
 *      Author: Erich Styger
 *  Edited on:  Feb 10, 2013 by: Reiner Geiger why: started with simple trigger support
 *   			Feb 11, 2013 by: Reiner Geiger why: started with 1 MHz support
 *   			Feb 25, 2013 by: Reiner Geiger why: updating to Version 1.1 from E. Styger
 *   			Mar 20, 2013 by: Reiner Geiger why: 1st DMA based Impl. works up to 4 MHz
 *  
 */
#include "IO_Map.h"
#include "Logic.h"
#include "AS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "Byte1.h"

#include "DMAT1.h"
#include "TPM0_TP1.h"

/* 
 * SUMP command definitions, 
 * see http://www.sump.org/projects/analyzer/protocol/ 
 * http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol 
 */

/* Trigger Data and Sampling setup */
TRIGGER_DATA triggerData[4]; // we actually support only ONE trigger stage
frequencyDivider freqDivider; // supported from V1.02
RandDCount rdCount; // actually not supported 
triggerFlags flags; // actually not supported 

/* Sampling buffer */
volatile uint8_t sampleBuffer[BUFFERSIZE];

/* Sampling Logic */
static volatile bool doSampling = FALSE;
static volatile bool finishedSampling = FALSE;
static volatile bool triggered = FALSE;

/* utility */
#define DEFAULT_HEARTBEAT_COUNTER 250000
static volatile uint32_t brg;
//
static unsigned int bufferSize = BUFFERSIZE;
static uint32_t heartBeat;
//
static LDD_TDeviceData *TU1Handl;

//##########################################################################
/* Local Functions */

/* \brief Send single character over UART */
static void PutChar(uint8_t ch)
{
	while (AS1_SendChar(ch) != ERR_OK)
	{
		/* retry */
	}
}

/* \brief Send null terminated string over UART */
static void PutString(char *s)
{
	while (*s != 0)
	{
		PutChar(*s);
		s++;
	}
}

/* \brief Send 32bit unsigned integer as SUMP meta data */
static void SUMP_sendmeta_uint32(char type, unsigned int i)
{
	PutChar(type);
	PutChar((i >> 24) & 0xff);
	PutChar((i >> 16) & 0xff);
	PutChar((i >> 8) & 0xff);
	PutChar(i & 0xff);
}

/* \brief Send 8bit unsigned integer as SUMP meta data */
static void SUMP_sendmeta_uint8(char type, unsigned char i)
{
	PutChar(type);
	PutChar(i);
}

/* \brief Send it over UART */
static void SendData(void)
{
	int i;

	AS1_ClearTxBuf();
	for (i = 0; i < bufferSize; i++)
	{
		PutChar(sampleBuffer[i]);
	}
}

void LOGIC_dmat1OnError(void)
{
	TP1_disableTimer(TU1Handl);
	DMAT1_DisableChannel0();
	finishedSampling = TRUE;
}

void LOGIC_dmat1OnCompleted(void)
{
	TP1_disableTimer(TU1Handl);
	DMAT1_DisableChannel0();
	finishedSampling = TRUE;
}

/*  \brief Setup timing for T1 and Heartbeat */
void setSampleFrequency(void)
{
	switch (freqDivider)
	{
	case 9999:
		// 10 kHz
		brg = 2400;
		break;
	case 3999:
		// 25 kHz
		brg = 960;
		break;
	case 1999:
		// 50 kHz
		brg = 480;
		break;
	case 999:
		// 100 kHz
		brg = 240;
		break;
	case 399:
		// 250 kHz
		brg = 96;
		break;
	case 199:
		// 500 kHz
		brg = 48;
		break;
	case 99:
		// 1 MHz
		brg = 24;
		break;
	case 49:
		// 2 MHz
		brg = 12;
		break;
	case 24:
		// 4 MHz
		brg = 6;
		break;
	case 11:
		// 8 MHz
		brg = 3;
		break;
	case 7:
		// 12 MHz
		brg = 2;
		break;
	case 3:
		// 24 MHz
		brg = 1;
		break;
	default:
		brg = DEFAULT_CLOCK_DIVIDER;
		break;
	}
	// To keep things variable with timing allow changing counter value
	// in future releases
	heartBeat = DEFAULT_HEARTBEAT_COUNTER;
}

uint8_t GetChar(void)
{
	uint8_t ch;

	while (AS1_RecvChar(&ch) != ERR_OK)
	{
	}
	return ch;
}

void LOGIC_Run(void)
{
	unsigned long data;
	unsigned char cmd;
	int i = 0;

	TU1Handl = TP1_initTimer();
	// TP1_enableTimer(TU1Handl);
	DMAT1_Init();

	// prepare SUMP variables
	triggerData[0].mask = 0;
	triggerData[0].values = 0;
	triggerData[0].configuration = 0;
	triggerData[1].mask = 0;
	triggerData[1].values = 0;
	triggerData[1].configuration = 0;
	triggerData[2].mask = 0;
	triggerData[2].values = 0;
	triggerData[2].configuration = 0;
	triggerData[3].mask = 0;
	triggerData[3].values = 0;
	triggerData[3].configuration = 0;
	// and preset Timer
	freqDivider = DEFAULT_CLOCK_DIVIDER;
	setSampleFrequency();
	TP1_setTimerValue(TU1Handl, brg);

	for (;;)
	{
		i++;
		if (i > heartBeat)
		{ /* heartbeat LED (red) if not sampling */
			if (!doSampling)
			{
				LEDR_Neg();
			}
			i = 0;
		}
		if (finishedSampling)
		{
			finishedSampling = FALSE;
			doSampling = FALSE;
			triggered = FALSE;
			SendData();
			LEDB_Off();
			LEDG_Off();
		}
		if (AS1_GetCharsInRxBuf() != 0)
		{
			cmd = GetChar();
			switch (cmd)
			{
			case SUMP_RESET:
				TP1_disableTimer(TU1Handl);
				DMAT1_DisableChannel0();
				finishedSampling = FALSE;
				doSampling = FALSE;
				triggered = FALSE;
				LEDB_Off();
				LEDG_Off();
				break;
			case SUMP_RUN:
				bufferSize = BUFFERSIZE;
				finishedSampling = FALSE;
				doSampling = TRUE;

				DMAT1_EnableChannel0();
				if (TP1_setTimerValue(TU1Handl, brg) != ERR_OK
						|| DMAT1_SetDestinationAddress0(
								(LDD_DMA_TAddress) &sampleBuffer[0]) != ERR_OK
						|| DMAT1_SetDestinationTransferSize0(
								bufferSize) != ERR_OK)
				{
					DMAT1_DisableChannel0();
					doSampling = FALSE;
					triggered = FALSE;
					// Keep Blue AND Red LED ON as error signal
					LEDB_On();
					LEDR_On();
					LEDG_Off();
					break;
				}
				doSampling = TRUE;

				if (triggerData[0].mask == 0)
				{ // no trigger active, simply start sampling
					LEDR_Off();
					LEDB_On();
					triggered = TRUE;
					DMAT1_EnableChannel0();

					// see also: SUMP Protocol f = clock / ( divider+1)
					// start LPTMR Timer and enable DMA
					TP1_enableTimer(TU1Handl);
				}
				else
				{
					LEDR_Off();
					LEDG_On();
					while (!triggered)
					{
						// Use short (fast) loop to detect trigger
						data = (Byte1_GetVal() & 0xFF);
						/* for now, we support only reading from 8 Probes
						 data = ( Byte2_GetVal() & 0xFF ) << 8;
						 data = ( Byte3_GetVal() & 0xFF ) << 16;
						 data = ( Byte4_GetVal() & 0xFF ) << 24;
						 */

						/* use this, if single condition mask (AND) needed */
						{
							if (!triggered && triggerData[0].mask != 0)
							{
								if ((data & triggerData[0].mask)
										== triggerData[0].values)
								{ /* matching trigger */

									/* use this, if multiple conditions (OR) are needed
									 for (i = 0; i < DEVICE_NOF_PROBES; i++)
									 { // we can handle all supported 32 Bits
									 if ((triggerData[0].mask & 1 << i) > 0)
									 { // if mask bit is set, check if values bit meets the probe bit
									 if ((triggerData[0].values & 1 << i)
									 == (data & 1 << i))
									 { // yes, we start if any trigger bit meets condition (primitive trigger only)
									 */
									LEDG_Off();
									LEDB_On();
									triggered = TRUE;

									// enable DMA AND Trigger first transfer to pick up Trigger
									// port value from Port
									// TODO: replace trigger handling by GPIO external trigger
									//       for Level and Edge
									DMAT1_EnableChannel0();
									DMAT1_StartTransfer0();

									// see also: SUMP Protocol f = clock / ( divider+1)
									// start LPTMR Timer and enable DMA
									TP1_enableTimer(TU1Handl);
									break;
								}
							}
						}

						// BUT : do not lockup the analyzer!!!
						if (AS1_GetCharsInRxBuf()
								!= 0 && GetChar() == SUMP_RESET)
						{
							TP1_disableTimer(TU1Handl);
							DMAT1_DisableChannel0();
							finishedSampling = FALSE;
							doSampling = FALSE;
							triggered = FALSE;
							LEDB_Off();
							LEDG_Off();
							break; // leave the While(!triggered) loop 
						}
					}
				}
				break;
			case SUMP_ID:
				PutString("1ALS");
				break;
			case SUMP_GET_METADATA:
				/* device name: */
				PutChar(0x01);
				PutString(DEVICE_NAME);
				PutChar(0x00);
				/* 'Firmware version: */
				PutChar(0x02);
				PutString(DEVICE_FW_VERSION);
				PutChar(0x00);
				/* 'Ancillary' version: */
				PutChar(0x03);
				PutString(DEVICE_ANCILLARY);
				PutChar(0x00);
				/* amount of sample memory available (bytes) */
				SUMP_sendmeta_uint32(0x21, BUFFERSIZE);
				/* maximum sample rate (Hz) */
				SUMP_sendmeta_uint32(0x23, MAX_SAMPLERATE);
				/* number of usable probes (short) */
				SUMP_sendmeta_uint8(0x40, DEVICE_NOF_PROBES);
				/* protocol version (short) */
				SUMP_sendmeta_uint8(0x41, DEVICE_PROTOCOL_VERSION);
				/* end of meta data */
				PutChar(0x00);
				break;
				/* long commands.. consume bytes from UART, NYI */
				/* Set Trigger Mask*/
			case 0xC0:
				triggerData[0].mask = GetChar();
				triggerData[0].mask |= GetChar() << 8;
				triggerData[0].mask |= GetChar() << 16;
				triggerData[0].mask |= GetChar() << 24;
				break;
			case 0xC4:
				triggerData[1].mask = GetChar();
				triggerData[1].mask |= GetChar() << 8;
				triggerData[1].mask |= GetChar() << 16;
				triggerData[1].mask |= GetChar() << 24;
				break;
			case 0xC8:
				triggerData[2].mask = GetChar();
				triggerData[2].mask |= GetChar() << 8;
				triggerData[2].mask |= GetChar() << 16;
				triggerData[2].mask |= GetChar() << 24;
				break;
			case 0xCC:
				triggerData[3].mask = GetChar();
				triggerData[3].mask |= GetChar() << 8;
				triggerData[3].mask |= GetChar() << 16;
				triggerData[3].mask |= GetChar() << 24;
				break;
				/* Set Trigger Values */
			case 0xC1:
				triggerData[0].values = GetChar();
				triggerData[0].values |= GetChar() << 8;
				triggerData[0].values |= GetChar() << 16;
				triggerData[0].values |= GetChar() << 24;
				break;
			case 0xC5:
				triggerData[1].values = GetChar();
				triggerData[1].values |= GetChar() << 8;
				triggerData[1].values |= GetChar() << 16;
				triggerData[1].values |= GetChar() << 24;
				break;
			case 0xC9:
				triggerData[2].values = GetChar();
				triggerData[2].values |= GetChar() << 8;
				triggerData[2].values |= GetChar() << 16;
				triggerData[2].values |= GetChar() << 24;
				break;
			case 0xCD:
				triggerData[3].values = GetChar();
				triggerData[3].values |= GetChar() << 8;
				triggerData[3].values |= GetChar() << 16;
				triggerData[3].values |= GetChar() << 24;
				break;
				/* Set Trigger Configuration */
			case 0xC2:
				triggerData[0].configuration = GetChar();
				triggerData[0].configuration |= GetChar() << 8;
				triggerData[0].configuration |= GetChar() << 16;
				triggerData[0].configuration |= GetChar() << 24;
				break;
			case 0xC6:
				triggerData[1].configuration = GetChar();
				triggerData[1].configuration |= GetChar() << 8;
				triggerData[1].configuration |= GetChar() << 16;
				triggerData[1].configuration |= GetChar() << 24;
				break;
			case 0xCA:
				triggerData[2].configuration = GetChar();
				triggerData[2].configuration |= GetChar() << 8;
				triggerData[2].configuration |= GetChar() << 16;
				triggerData[2].configuration |= GetChar() << 24;
				break;
			case 0xCE:
				triggerData[3].configuration = GetChar();
				triggerData[3].configuration |= GetChar() << 8;
				triggerData[3].configuration |= GetChar() << 16;
				triggerData[3].configuration |= GetChar() << 24;
				break;
			case SUMP_SET_DIVIDER:
				// preliminary; received divider values seems to need more testing
				freqDivider = GetChar();
				freqDivider |= GetChar() << 8;
				freqDivider |= GetChar() << 16;
				(void) GetChar();
				setSampleFrequency();
				break;
			case SUMP_SET_READ_DELAY_COUNT:
				rdCount = GetChar();
				rdCount |= GetChar() << 8;
				rdCount |= GetChar() << 16;
				rdCount |= GetChar() << 24;
				break;
				/* Set Flag */
			case SUMP_SET_FLAGS:
				flags = GetChar();
				flags |= (GetChar() << 8);
				flags |= (GetChar() << 16);
				flags |= (GetChar() << 24);
				break;
			default:
				break;
			} /* switch */
		}
	}
}
