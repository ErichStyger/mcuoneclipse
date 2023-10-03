/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* configure the HW/Board version with TINYK22_HAT_VERSION in IncludeMcuLibConfig.h */
#define PL_CONFIG_PCB_TEST_MODE           (0) /* 1: used for testing a new PCB */

#define PL_CONFIG_USE_RASPBERRY           (1 && !PL_CONFIG_PCB_TEST_MODE) /* board used with Raspberry Pi */
#define PL_CONFIG_USE_BUTTONS             (1) /* using buttons (navigation switch) */
#define PL_CONFIG_USE_KBI                 (1 && PL_CONFIG_USE_BUTTONS) /* using interrupts for buttons */
#define PL_CONFIG_USE_I2C                 (1) /* if I2C is enabled */
#define PL_CONFIG_USE_I2C_SPY             (1 && PL_CONFIG_USE_I2C)
#define PL_CONFIG_USE_RTT                 (1)
#define PL_CONFIG_USE_SHT31               (1 && PL_CONFIG_USE_I2C && TINYK22_HAT_VERSION<7) /* if using SHT31 sensor */
#define PL_CONFIG_USE_SHT40               (1 && PL_CONFIG_USE_I2C && TINYK22_HAT_VERSION>=7) /* if using SHT31 sensor */
#define PL_CONFIG_USE_OLED                (0 && PL_CONFIG_USE_I2C && !PL_CONFIG_PCB_TEST_MODE) /* if using OLED */
#define PL_CONFIG_USE_UPS                 (0 && PL_CONFIG_USE_I2C && PL_CONFIG_USE_RASPBERRY) /* if using UPS HAT */
#define PL_CONFIG_USE_GATEWAY             (1 && PL_CONFIG_USE_RASPBERRY) /* if implementing UART gateway to Raspberry Pi */
#define PL_CONFIG_USE_RASPY_UART          (1 && PL_CONFIG_USE_RASPBERRY) /* uses UART to Raspy as interface for joystick, led and sensor values */
#define PL_CONFIG_USE_SHELL               (1) /* if shell is enabled, uses RTT */
#define PL_CONFIG_USE_USB_CDC             (1)
#define PL_CONFIG_USE_SHUTDOWN            (1 && PL_CONFIG_USE_RASPBERRY) /* if implementing shutdown for Raspberry Pi */
#define PL_CONFIG_USE_POWER_ON            (0 && PL_CONFIG_USE_RASPBERRY && TINYK22_HAT_VERSION>=5) /* ability to power up Raspy, only possible with Rev5 or later of the board. See shutdown.c for Raspy settings! */

#define PL_CONFIG_USE_GUI                 (1 && PL_CONFIG_USE_OLED && PL_CONFIG_USE_BUTTONS) /* use LittlevGL */
#define PL_CONFIG_USE_GUI_SCREENSAVER     (1 && PL_CONFIG_USE_GUI)
#define PL_CONFIG_USE_TOASTER             (1 && PL_CONFIG_USE_GUI_SCREENSAVER) /* flying toaster screen saver, otherwise blanks screen */
#define PL_CONFIG_USE_GUI_KEY_NAV         (1 && PL_CONFIG_USE_BUTTONS && PL_CONFIG_USE_GUI)

#define PL_CONFIG_USE_POWER_DOWN_STATE_PIN  (1 && PL_CONFIG_USE_RASPBERRY && !PL_CONFIG_USE_POWER_ON && (TINYK22_HAT_VERSION>=5)) /* Raspy can indicate power down with a state pin. Not possible with wake-up functionality. On pre-V5 uses red LED instead. */
#define PL_CONFIG_USE_POWER_DOWN_RED_LED    (0 && PL_CONFIG_USE_RASPBERRY && (TINYK22_HAT_VERSION==3 || TINYK22_HAT_VERSION==4 || !PL_CONFIG_USE_POWER_ON)) /* uses the red HAT led as power down indicator */
#define PL_CONFIG_USE_POWER_DOWN_GREEN_LED  (1 && PL_CONFIG_USE_RASPBERRY && (TINYK22_HAT_VERSION==3 || TINYK22_HAT_VERSION==4 || !PL_CONFIG_USE_POWER_ON)) /* uses the green HAT led as power down indicator */

#define PL_CONFIG_USE_HW_I2C                (USE_HW_I2C) /* defined in IncludeMcuLibConfig.h */

/* defines for sensor.c */
#define PL_CONFIG_HAS_TSL2561       (0)
#define PL_CONFIG_HAS_MMA8451       (0)
#define PL_CONFIG_HAS_AMG8833       (0)
#define PL_CONFIG_HAS_RTC_DS3231    (0)

/* ESP32 related */
#define PL_CONFIG_USE_ESP32         (0)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
