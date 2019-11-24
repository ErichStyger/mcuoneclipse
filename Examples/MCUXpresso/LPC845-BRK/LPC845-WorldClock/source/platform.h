/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_BOARD_VERSION     (1) /* 1: V0.1, 10: V1.0 */

#define PL_CONFIG_USE_SHELL         (1) /* use command line shell */
#define PL_CONFIG_USE_RTT           (1) /* use SEGGER RTT (only possible with a J-Link */
#define PL_CONFIG_USE_UART          (0) /* using UART */
#define PL_CONFIG_USE_USB_CDC       (0) /* not supported on LPC845 */
#define PL_CONFIG_USE_I2C           (0) /* use I2C bus */
#define PL_CONFIG_USE_HW_I2C        (0 && PL_CONFIG_USE_I2C) /* 1: use hardware, 0: use bit-banging */
#define PL_CONFIG_USE_I2C_SPY       (0 && PL_CONFIG_USE_I2C) /* using shell component to scan I2C bus */
#define PL_CONFIG_USE_MAG_SENSOR    (1) /* using magnets and hall sensors */
#define PL_CONFIG_USE_RTC           (1 /*&& PL_CONFIG_USE_I2C*/)
#define PL_CONFIG_USE_RS485         (1)
#define PL_CONFIG_USE_NVMC          (1) /* using non-volatile configuration memory */

#define PL_CONFIG_USE_EXT_I2C_RTC   (1 && PL_CONFIG_USE_RTC && PL_CONFIG_USE_I2C) /* DS3231 with AT24C32 */
#define PL_CONFIG_USE_EXT_EEPROM    (1 && PL_CONFIG_USE_I2C) /* AT24C32 */
#define PL_CONFIG_USE_STEPPER       (1)
#define PL_CONFIG_USE_X12_STEPPER   (1 /*&& PL_CONFIG_USE_STEPPER*/) /* X12 stepper motors */
#define PL_CONFIG_USE_BUTTON        (0)

/* NYI */
#define PL_CONFIG_USE_KBI     (0)
#define PL_CONFIG_USE_GUI     (0)

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
