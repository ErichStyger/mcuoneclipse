/**
 * \file
 * \brief Interface Platform initialization of the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the hardware dependent initialization of board and drivers and offers configuration settings.
 */

#ifndef SRC_PLATFORM_H_
#define SRC_PLATFORM_H_

#include "McuLib.h"  /* include standard types */
#include "SEGGER_RTT.h"
#include <stdint.h>

#if 1 /* mapping stdio basic functions to RTT/Shell */
#include <stdio.h>
#include "McuShell.h"

/*!
 * \brief put a character to a stream
 * \return number of character written
 */
int _putc(int c, __FILE *fp);
/*!
 * \brief Return a character from a stream
 */
int _getc(__FILE *fp);
/*!
 * \brief Writes a character to the standard stream
 */
int _putchar(int c);

#undef putc
#undef getc
#undef putchar
#define putc(c, fp)  	_putc(c,fp)
	/*!< write a character to a stream */
#define getc(fp)   		_getc(fp)
	/*!< get a character from a stream */
#define putchar(c)  	_putchar(c)
	/*!< write a character to stdout */
#endif

/** @addtogroup Platform
  * @{
  */

#define printf  SEGGER_printf
	/*!< we substitute the standard I/O libraries with the SEGGER RTT version */

#define PL_CONFIG_BOARD_ID_STM32_NUCLEO   1  /*!< Board is the STM32 Nucleo Board */
#define PL_CONFIG_BOARD_ID_TINY_K22       2  /*!< Board is the NXP K22FN512 tinyK22 board */

#define PL_CONFIG_BOARD   PL_CONFIG_BOARD_ID_STM32_NUCLEO  /*!< configures the board used */

/*!
 * \brief Platform initialization.
 */
void PL_Init(void);

/**
  * @}
  */

#endif /* SRC_PLATFORM_H_ */
