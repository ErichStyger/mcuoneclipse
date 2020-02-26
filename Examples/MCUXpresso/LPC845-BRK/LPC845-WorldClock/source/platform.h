/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_IS_MASTER         (0) /* otherwise it is the client */
#define PL_CONFIG_IS_CLIENT         (!PL_CONFIG_IS_MASTER) /* otherwise it is the master */

/* hardware versions:
 * V0.1: initial version with 2x2 arrangement
 * V1.0: second version with 1x4 arrangement, different pin assignment and better hall sensors */
#if 1
  #define PL_CONFIG_BOARD_VERSION   (10) /* 1: V0.1, 10: V1.0 */
#else
  #define PL_CONFIG_BOARD_VERSION   (1) /* 1: V0.1, 10: V1.0 */
#endif

#define PL_CONFIG_WORLD_CLOCK       (0) /* clock showing different time zones */

#define PL_CONFIG_USE_SHELL         (1) /* use command line shell */
#define PL_CONFIG_USE_RTT           (1 && PL_CONFIG_IS_CLIENT) /* use SEGGER RTT (only possible with a J-Link */
#define PL_CONFIG_USE_RTC           (1) /* 1: enable RTC; 0: disable it */
#define PL_CONFIG_USE_RS485         (1 && PL_CONFIG_USE_SHELL) /* RS-485 connection, 1: enabled, 0: disabled: it requires the shell to parse the commands */
#define PL_CONFIG_USE_NVMC          (1) /* using non-volatile configuration memory */
#define PL_CONFIG_USE_WDT           (1) /* if using watchdog timer */

/* client only: */
#define PL_CONFIG_USE_MAG_SENSOR    (1 && PL_CONFIG_IS_CLIENT) /* using magnets and hall sensors */
#define PL_CONFIG_USE_STEPPER       (1 && PL_CONFIG_IS_CLIENT) /* enable stepper motors */
#define PL_CONFIG_USE_X12_STEPPER   (1 && PL_CONFIG_USE_STEPPER) /* X12 stepper motors */

/* master only: */
#define PL_CONFIG_USE_SHELL_UART    (1 && PL_CONFIG_IS_MASTER) /* using UART for USB-CDC to host */
#define PL_CONFIG_USE_I2C           (1 && PL_CONFIG_IS_MASTER) /* use I2C bus */
#define PL_CONFIG_USE_HW_I2C        (CONFIG_USE_HW_I2C) /* set in IncludMcuLibConfig.h! */
#define PL_CONFIG_USE_EXT_I2C_RTC   (1 && PL_CONFIG_USE_RTC && PL_CONFIG_USE_I2C) /* DS3231 with AT24C32 */
#define PL_CONFIG_USE_EXT_EEPROM    (1 && PL_CONFIG_USE_I2C) /* AT24C32 */
#define PL_CONFIG_USE_MATRIX        (1 && PL_CONFIG_IS_MASTER && PL_CONFIG_USE_RS485)

#define PL_CONFIG_USE_NEO_PIXEL     (0)

/* NYI or not applicable */
#define PL_CONFIG_USE_KBI           (0)
#define PL_CONFIG_USE_GUI           (0)
#define PL_CONFIG_USE_BUTTON        (0)
#define PL_CONFIG_USE_USB_CDC       (0) /* not supported on LPC845 */
#define PL_CONFIG_USE_I2C_SPY       (0 && PL_CONFIG_USE_I2C) /* using shell component to scan I2C bus */

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
