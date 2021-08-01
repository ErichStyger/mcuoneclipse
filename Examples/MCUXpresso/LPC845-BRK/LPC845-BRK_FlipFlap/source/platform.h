/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_NOF_UNITS             (1)

#define PL_CONFIG_USE_SHELL             (1) /* use command line shell */
#define PL_CONFIG_USE_RTT               (0) /* use SEGGER RTT (only possible with a J-Link) */
#define PL_CONFIG_USE_I2C               (0) /* use I2C bus, only on master! */
#define PL_CONFIG_USE_HW_I2C            (0)
#define PL_CONFIG_USE_I2C_SPY           (0 && PL_CONFIG_USE_I2C) /* using shell component to scan I2C bus */
#define PL_CONFIG_USE_HALL_SENSOR       (1) /* using magnets and hall sensors */

#define PL_CONFIG_USE_EXT_I2C_RTC       (1 && PL_CONFIG_USE_I2C) /* DS3231 with AT24C32 */
#define PL_CONFIG_USE_EXT_EEPROM        (1 && PL_CONFIG_USE_I2C) /* AT24C32 */
#define PL_CONFIG_USE_STEPPER           (1)
#define PL_CONFIG_USE_BUTTON            (0)
#define PL_CONFIG_USE_TIME_DATE         (0)

/* NYI */
#define PL_CONFIG_USE_KBI     (0)
#define PL_CONFIG_USE_GUI     (0)
#define PL_CONFIG_USE_USB_CDC (0)

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
