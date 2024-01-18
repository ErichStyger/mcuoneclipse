/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

#include "IncludeMcuLibConfig.h"

#define PL_CONFIG_BOARD_IS_TSM        (0) /* if the board is the RP2040 TSM wireless board. Otherwise it is the board used in the 16x16x16 cube */

#define PL_CONFIG_USE_PICO_W          (0) /* if using Pico W board */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_WIFI              (0 && PL_CONFIG_USE_PICO_W) /* if using WiFi functionality */

#define PL_CONFIG_USE_USB_CDC           (1) /* caution, because issues while debugging! In Termite, need to connect with RTS/CTS! Putty works fine */
#define PL_CONFIG_USE_RTT               (1) /* if using SEGGER RTT */

#define PL_CONFIG_USE_SHELL             (1)
#define PL_CONFIG_USE_SHELL_UART        (0 && PL_CONFIG_USE_SHELL) /* NYI, using an extra physical UART */

#define PL_CONFIG_USE_NEO_PIXEL_HW      (1) /* using WS2812B */

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */
