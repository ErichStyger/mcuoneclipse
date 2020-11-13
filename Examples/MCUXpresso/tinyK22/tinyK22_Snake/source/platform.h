/*
 * platform.h
 *
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_


#define PL_CONFIG_HAS_SNAKE_GAME    (1)

#define PL_CONFIG_USE_I2C           (1) /* if I2C is enabled */
#define PL_CONFIG_USE_OLED          (1 && PL_CONFIG_USE_I2C) /* if using OLED */
#define PL_CONFIG_USE_SHELL         (1) /* if shell is enabled, uses RTT */

#define PL_CONFIG_USE_HW_I2C        USE_HW_I2C /* defined in IncludeMcuLibConfig.h */


#define PL_CONFIG_USE_UART_SHELL     (1)
#define PL_CONFIG_USE_RTT            (0)
#define PL_CONFIG_USE_USB_CDC_SHELL  (0)

void PL_Init(void);


#endif /* PLATFORM_H_ */
