/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "platform.h"

#define PL_CONFIG_USE_RTT         (1)
#define PL_CONFIG_USE_I2C         (1)
#define PL_CONFIG_USE_HW_I2C      (1)
#define PL_CONFIG_USE_I2C_SPY     (0)
#define PL_CONFIG_USE_RTC         (1)
#define PL_CONFIG_USE_SHT31       (1)
#define PL_CONFIG_USE_EXT_EEPROM  (0)
#define PL_CONFIG_USE_RS485       (1)
#define PL_CONFIG_USE_NVMC        (0)
#define PL_CONFIG_HAS_BUTTONS     (0)
#define PL_CONFIG_USE_SHELL       (1)
#define PL_CONFIG_USE_SHELL_UART  (1)
#define PL_CONFIG_USE_USB_CDC     (1)
#define PL_CONFIG_USE_ESP32       (0)
#define PL_CONFIG_USE_ESP32_UART  (0)
#define PL_CONFIG_USE_WDT         (0)
#define PL_CONFIG_USE_CLOCK       (1)
#define PL_CONFIG_USE_BLE         (1)
#define PL_CONFIG_USE_BLE_MSG     (1)
#define PL_CONFIG_USE_LOW_POWER   (0)

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
