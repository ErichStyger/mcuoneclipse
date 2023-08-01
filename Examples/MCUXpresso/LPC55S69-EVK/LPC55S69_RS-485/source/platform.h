/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL         (1)
#define PL_CONFIG_USE_SHELL_UART    (0  && PL_CONFIG_USE_SHELL)
#define PL_CONFIG_USE_USB_CDC       (0 && PL_CONFIG_USE_SHELL)
#define PL_CONFIG_USE_RTT           (1)

void PL_Init(void);

#endif /* PLATFORM_H_ */
