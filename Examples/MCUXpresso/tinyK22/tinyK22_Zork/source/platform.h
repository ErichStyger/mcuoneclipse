/*
 * platform.h
 *
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* configuration makros: */
#define USE_FATFS         (0) /* using FatFS with SD card */
#define USE_SEMIHOSTING   (0) /* using semihosting with the debug probe for file I/O */
#define USE_FLASH_FILE    (1) /* using a flash file for the game data */
#define USE_CONSOLE       (1) /* required, using Console input/output */
#define USE_MCURSES       (0) /* use mcurses */

#define PL_CONFIG_USE_UART_SHELL     (0)
#define PL_CONFIG_USE_RTT            (1)
#define PL_CONFIG_USE_USB_CDC_SHELL  (0)

void PL_Init(void);


#endif /* PLATFORM_H_ */
