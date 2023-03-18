/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

/* client: getting data from the server */
#define PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT  (1)

/* server: providing temperature values to the client */
#define PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_SERVER  (1 && !PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT)

#define PL_CONFIG_USE_PICO_W          (1) /* if using Pico-W */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */

#define PL_CONFIG_USE_WIFI            (0 && PL_CONFIG_USE_PICO_W)
#define PL_CONFIG_USE_BLE             (1 && PL_CONFIG_USE_PICO_W)

#define PL_CONFIG_USE_RTT             (1)
#define PL_CONFIG_USE_USB_CDC         (1)
#define PL_CONFIG_USE_SHELL_UART      (0)

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */
