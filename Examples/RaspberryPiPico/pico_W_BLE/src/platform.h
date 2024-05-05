/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

/* client: getting data from the server */
#define PL_CONFIG_STANDALONE_BLE_CLIENT  (0) /* << change this to switch between client and server implementation */

/* server: providing temperature values to the client */
#define PL_CONFIG_STANDALONE_BLE_SERVER  (1 && !PL_CONFIG_STANDALONE_BLE_CLIENT)

#define PL_CONFIG_USE_PICO_W          (1) /* if using Pico-W */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */

/* Combination of WiFi and BLE is possible: */
#define PL_CONFIG_USE_WIFI            (1 && PL_CONFIG_USE_PICO_W) /* if using WiFi functionality */
#define PL_CONFIG_USE_BLE             (1 && PL_CONFIG_USE_PICO_W) /* if using BLE functionality */

#define PL_CONFIG_USE_SHELL           (1) /* if using a command line shell */
#define PL_CONFIG_USE_RTT             (1 && PL_CONFIG_USE_SHELL) /* if using SEGGER RTT with J-Link */
#define PL_CONFIG_USE_USB_CDC         (1 && PL_CONFIG_USE_SHELL) /* if using USB CDC as shell interface */
#define PL_CONFIG_USE_SHELL_UART      (0 && PL_CONFIG_USE_SHELL) /* if using UART for shell (NYI) */
#define PL_CONFIG_USE_MCUFLASH        (1) /* used to enable McuFlash, needed for MinINI */
#define PL_CONFIG_USE_MINI            (1 && PL_CONFIG_USE_MCUFLASH) /* if using MinINI to store values in FLASH */

/* WiFi configuration items */
#define PL_CONFIG_USE_PING            (0 && PL_CONFIG_USE_WIFI)   /* using ping application */
#define PL_CONFIG_USE_NTP_CLIENT      (0 && PL_CONFIG_USE_WIFI)   /* using ntp application */
#define PL_CONFIG_USE_UDP_SERVER      (0 && PL_CONFIG_USE_WIFI)   /* using udp server application */
#define PL_CONFIG_USE_UDP_CLIENT      (0 && PL_CONFIG_USE_WIFI)   /* if using udp client */
#define PL_CONFIG_USE_TCP_SERVER      (0 && PL_CONFIG_USE_WIFI)   /* if running TCP server */
#define PL_CONFIG_USE_TCP_CLIENT      (1 && PL_CONFIG_USE_WIFI)   /* if running TCP client */
#define PL_CONFIG_USE_MQTT_CLIENT     (0 && PL_CONFIG_USE_WIFI)   /* if running MQTT client */

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#endif /* APP_PLATFORM_H_ */
