/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL   (1)
#define PL_CONFIG_USE_I2C     (1)

#define PL_HAS_EXT_I2C_RTC    (1 && PL_CONFIG_USE_I2C) /* DS3231 with AT24C32 */
#define PL_HAS_EXT_EEPROM     (1) /* AT24C32 */

/* NYI */
#define PL_CONFIG_USE_KBI     (0)
#define PL_CONFIG_USE_GUI     (0)
#define PL_CONFIG_USE_USB_CDC (0)

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
