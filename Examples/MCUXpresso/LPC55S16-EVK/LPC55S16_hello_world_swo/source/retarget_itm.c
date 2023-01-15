//*****************************************************************************
// retarget_itm.c - Provides retargeting of C library printf/scanf
//                  functions via ITM / SWO Trace
//*****************************************************************************
// Copyright 2015, 2017-2023 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************

#include <stdint.h>

// ******************************************************************
// Cortex-M SWO Trace / Debug registers used for accessing ITM
// ******************************************************************

// CoreDebug - Debug Exception and Monitor Control Register
#define DEMCR           (*((volatile uint32_t *) (0xE000EDFC)))
// DEMCR Trace Enable Bit
#define TRCENA          (1UL << 24)

// ITM Stimulus Port Access Registers
#define ITM_Port8(n)    (*((volatile uint8_t *) (0xE0000000 + 4 * n)))
#define ITM_Port16(n)   (*((volatile uint16_t *) (0xE0000000 + 4 * n)))
#define ITM_Port32(n)   (*((volatile uint32_t *) (0xE0000000 + 4 * n)))

// ITM Trace Control Register
#define ITM_TCR (*((volatile  uint32_t *) (0xE0000000 + 0xE80)))
// ITM TCR: ITM Enable bit
#define ITM_TCR_ITMENA (1UL << 0)

// ITM Trace Enable Register
#define ITM_TER (*((volatile  uint32_t *) (0xE0000000 + 0xE00)))
// ITM Stimulus Port #0 Enable bit
#define ITM_TER_PORT0ENA (1UL << 0)

// ******************************************************************
// Buffer used for pseudo-ITM reads from the host debugger
// ******************************************************************

// Value identifying ITM_RxBuffer is ready for next character
#define ITM_RXBUFFER_EMPTY    0x5AA55AA5
// variable to receive ITM input characters
//volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
extern volatile int32_t ITM_RxBuffer;

// ******************************************************************
// Redlib C Library function : __sys_write
// Newlib C library function : _write
//
// Function called by bottom level of printf routine within C library.
// With the default semihosting stub, this would write the
// character(s) to the debugger console window (which acts as
// stdout). But this version writes the character(s) from the Cortex
// M3/M4 SWO / ITM interface for display in the ITM Console.
// ******************************************************************
#if defined (__REDLIB__)
int __sys_write(int iFileHandle, char *pcBuffer, int iLength) {
#elif defined (__NEWLIB__)
int _write(int iFileHandle, char *pcBuffer, int iLength) {
#endif

	int32_t num = 0;

	// TODO : Should potentially check that iFileHandle == 1 to confirm
	// that write is to stdout

	// check if debugger connected and ITM channel enabled for tracing
	if ((DEMCR & TRCENA) &&
	// ITM enabled
			(ITM_TCR & ITM_TCR_ITMENA) &&
			// ITM Port #0 enabled
			(ITM_TER & ITM_TER_PORT0ENA)) {

		while (num < iLength) {
			while (ITM_Port32(0) == 0) {
			}
			ITM_Port8(0) = pcBuffer[num++];
		}
		return 0;
	} else
		// Function returns number of unwritten bytes if error
		return (iLength);
}

#if defined (__REDLIB__)
// ******************************************************************
// Redlib C Library function : __sys_readc
//
// Called by bottom level of scanf routine within RedLib C library
// to read a character. With the default semihosting stub, this
// would read the character from the debugger console window (which
// acts as stdin). But this version reads the character from a buffer
// which acts as a pseudo-interface to the Cortex-M3/M4 ITM.
// ******************************************************************

int __sys_readc(void) {
	int32_t c = -1;
	// check if debugger connected and ITM channel enabled for tracing
	if ((DEMCR & TRCENA) &&
	// ITM enabled
			(ITM_TCR & ITM_TCR_ITMENA) &&
	// ITM Port #0 enabled
			(ITM_TER & ITM_TER_PORT0ENA)) {
		do {
			if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY) {
				// Read from buffer written to by tools
				c = ITM_RxBuffer;
				// Flag ready for next character
				ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
			}
		}while (c == -1);
	}
	return c;
}
// #endif REDLIB __sys_readc()

#elif defined (__NEWLIB__)
// ******************************************************************
// Function _read
//
// Called by bottom level of scanf routine within Newlib C library
// to read multiple characters. With the default semihosting stub, this
// would read  characters from the debugger console window (which
// acts as stdin). But this version reads the characters from a buffer
// which acts as a pseudo-interface to the Cortex-M3/M4 ITM.
// ******************************************************************
int _read(int iFileHandle, char *pcBuffer, int iLength) {

	// TODO : Should potentially check that iFileHandle == 0 to confirm
	// that read is from stdin

	int iCcount = 0x00; // Count of characters read

	// check if debugger connected and ITM channel enabled for tracing
	if ((DEMCR & TRCENA) &&
	// ITM enabled
			(ITM_TCR & ITM_TCR_ITMENA) &&
			// ITM Port #0 enabled
			(ITM_TER & ITM_TER_PORT0ENA)) {

		// Read up to 'iLength' characters
		for (; iLength > 0x00; --iLength) {
			int32_t c = -1;
			do {
				if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY) {
					// Read from buffer written to by tools
					c = ITM_RxBuffer;
					// Flag ready for next character
					ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
				}
			} while (c == -1);

			iCcount++;  // Increase char counter
			*pcBuffer = (char) c; // Save character into the receive buffer

			// Non-printable character is received ?
			if (*pcBuffer < 32 || *pcBuffer > 126) {
				*pcBuffer = '\n'; // Yes, convert  to '\n' char.
				break; // Stop loop and return received char(s)
			}
			(char*) pcBuffer++;  // Increase buffer pointer
		}
	}
	return iCcount;
}

#endif // NEWLIB _read()

