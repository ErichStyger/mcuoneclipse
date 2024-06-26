/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_BOARD_H_
#define PLATFORM_BOARD_H_

#define PL_CONFIG_USE_ESA             (1)  /* board for ESA demonstrator */

#define PL_CONFIG_USE_NEO_PIXEL_HW    (1) /* if we have NeoPixels/SK6812 */
#define PL_CONFIG_USE_RTT             (1)
#define PL_CONFIG_USE_USB_CDC         (1)
#define PL_CONFIG_USE_SHELL           (1)
#define PL_CONFIG_USE_NEO_APP         (1)
#define PL_CONFIG_USE_BUTTONS         (1 && !PL_CONFIG_USE_ESA)
#define PL_HAS_ONBOARD_LED            (1 && !PL_CONFIG_USE_ESA)

#define PL_CONFIG_USE_OLED            (0)
#define PL_CONFIG_SHT_SENSOR          (0)
#define PL_CONFIG_USE_SCREENSAVER     (0)
#define PL_CONFIG_USE_MININI          (0)
#define PL_CONFIG_USE_NVMC            (0)
#define PL_CONFIG_USE_WIFI            (0)
#define PL_CONFIG_USE_DISPLAY_ST7735  (0)
#define PL_CONFIG_HAS_CUBE            (0 && PL_CONFIG_USE_NEO_PIXEL_HW)
#define PL_CONFIG_USE_DISPLAY_ST7735  (0)
#define PL_CONFIG_USE_LEDS            (0)
#define PL_CONFIG_USE_SENSOR          (0)
#define PL_CONFIG_USE_GAME            (0)

#define PL_CONFIG_IS_HARDWARE_TEST    (0) /* run some basic hardware tests, used after populating the boards */

#define PL_CONFIG_IS_SENSOR_ONLY      (0 && PL_CONFIG_IS_HARDWARE_TEST) /* show sensor values on OLED, used as 'room sensor' board */


void PL_Init(void);

#endif /* PLATFORM_BOARD_H_ */
