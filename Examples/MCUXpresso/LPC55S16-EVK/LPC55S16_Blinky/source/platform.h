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
#define PL_CONFIG_USE_SD_CARD     (0)
#define PL_CONFIG_USE_MININI      (1 && PL_CONFIG_USE_SD_CARD)
#define PL_CONFIG_USE_USB_MSD     (0)
#define PL_CONFIG_USE_SWO         (0)  /* for J-Link need to call SWO_SetSpeed()! */
#define PL_CONFIG_INIT_SWO        (1 && PL_CONFIG_USE_SWO)

#define PL_CONFIG_USE_I2C         (0)
#define PL_CONFIG_USE_HW_I2C      (USE_HW_I2C && PL_CONFIG_USE_I2C) /* USE_HW_I2C defined in IncludeMcuLibConfig.h */
#define PL_CONFIG_USE_OLED        (1 && PL_CONFIG_USE_I2C)

#define PL_CONFIG_USE_NVMC        (1)

void PL_Init(void);


#endif /* PLATFORM_H_ */
