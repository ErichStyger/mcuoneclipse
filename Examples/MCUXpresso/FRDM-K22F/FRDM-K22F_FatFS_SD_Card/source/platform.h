/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_


/* Shell */
#define PL_CONFIG_USE_SHELL         (1) /* if using shell */
#define PL_CONFIG_USE_SHELL_UART    (1) /* if using (OpenSDA) UART */
#define PL_CONFIG_USE_RTT           (1) /* if using RTT */
#define PL_CONFIG_USE_USB_CDC       (0) /* if using USB CDC */

void PL_Init(void);

#endif /* PLATFORM_H_ */
