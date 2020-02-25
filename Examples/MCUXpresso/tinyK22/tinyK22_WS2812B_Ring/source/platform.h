/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* configure the HW/Board version with TINYK22_HAT_VERSION in IncludeMcuLibConfig.h */

#define PL_CONFIG_USE_RTT                 (1)  /* if using the SEGGER RTT */
#define PL_CONFIG_USE_NEO_PIXEL           (0)  /* if using the WS2812B */
#define PL_CONFIG_USE_RS485               (1)  /* if using the RS485 bus */
#define PL_CONFIG_USE_SHELL_UART          (1)
#define PL_CONFIG_USE_SHELL               (1)  /* if using the Shell */
#define PL_CONFIG_USE_USB_CDC             (0)

#define PL_CONFIG_IS_CLIENT (1)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
