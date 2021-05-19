/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL       (1)
#define PL_CONFIG_USE_SHELL_UART  (1)
#define PL_CONFIG_USE_RTT         (1)
#define PL_CONFIG_USE_USB_CDC     (0)
#define PL_CONFIG_USE_SD_CARD     (1)
#define PL_CONFIG_USE_MININI      (1)
#define PL_CONFIG_USE_USB_MSD     (0)
#define PL_CONFIG_USE_SWO         (0)  /* does not work yet! */

#define PL_CONFIG_USE_I2C           (1)
#define PL_CONFIG_USE_HW_I2C        (USE_HW_I2C && PL_CONFIG_USE_I2C) /* USE_HW_I2C defined in IncludeMcuLibConfig.h */

void PL_Init(void);


#endif /* PLATFORM_H_ */
