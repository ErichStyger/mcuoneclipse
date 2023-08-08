/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

#include "IncludeMcuLibConfig.h"

#define PL_CONFIG_USE_PICO_W          (1) /* if using Pico W board */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_WIFI              (0 && PL_CONFIG_USE_PICO_W) /* if using WiFi functionality */


#define PL_CONFIG_USE_DISPLAY_ST7735    (1)

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */
