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

#define PL_CONFIG_USE_UART_SHELL     (1)
#define PL_CONFIG_USE_RTT            (0)
#define PL_CONFIG_USE_USB_CDC_SHELL  (0)

void PL_Init(void);


#endif /* PLATFORM_H_ */
