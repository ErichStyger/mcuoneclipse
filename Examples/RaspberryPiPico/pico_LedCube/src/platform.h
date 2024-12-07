/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "IncludeMcuLibConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PL_CONFIG_BOARD_IS_TSM        (0) /* if the board is the RP2040 TSM wireless board. Otherwise it is the board used in the 16x16x16 cube */

#define PL_CONFIG_USE_PICO_W          (0) /* if using Pico W board */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_WIFI              (0 && PL_CONFIG_USE_PICO_W) /* if using WiFi functionality */

#define PL_CONFIG_USE_RTT               (1) /* if using SEGGER RTT */

#define PL_CONFIG_USE_SHELL             (1)
#define PL_CONFIG_USE_SHELL_UART        (0 && PL_CONFIG_USE_SHELL) /* NYI, using an extra physical UART */
#define PL_CONFIG_USE_TUD_CDC           (0) /* tinyUSB CDC device with McuShellCdcDevice */
#define PL_CONFIG_USE_SHELL_CDC         (1 && PL_CONFIG_USE_TUD_CDC) /* if using CDC as shell interface */

#define PL_CONFIG_USE_NEO_PIXEL_HW      (1) /* using WS2812B */


/*!
 * \brief de-initializes the platform
 */
void PL_Deinit(void);

/*!
 * \brief initializes the platform
 */
void PL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* PLATFORM_H_ */
