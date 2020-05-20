/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* Features */
#define PL_CONFIG_USE_SD_CARD       (1) /* if using FatFS with SD card */
#define PL_CONFIG_USE_MININI        (1 && PL_CONFIG_USE_SD_CARD) /* if using minIni */
#define PL_CONFIG_USE_USB_MSD       (1) /* if using FatFS with USB MSD */

/* Shell */
#define PL_CONFIG_USE_SHELL         (1) /* if using shell */
#define PL_CONFIG_USE_SHELL_UART    (1) /* if using (OpenSDA) UART */
#define PL_CONFIG_USE_RTT           (1) /* if using RTT */
#define PL_CONFIG_USE_USB_CDC       (0) /* if using USB CDC */

/* platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
