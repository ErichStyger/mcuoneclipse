/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_IS_TINY_K22       (1) /* if board is the tinyK22 instead of the FRDM-K22F */
#define PL_CONFIG_USE_SHELL         (1) /* if using Shell module */
#define PL_CONFIG_USE_RTT           (1)
#define PL_CONFIG_USE_USB_CDC       (0)
#define PL_CONFIG_USE_SHELL_UART    (0)

/* platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
