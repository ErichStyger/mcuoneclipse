/*
 * Copyright (c) 2025-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_WIFI_CONFIG_H_
#define MCU_WIFI_CONFIG_H_

#ifndef MCU_WIFI_CONFIG_ENABLED
  #define MCU_WIFI_CONFIG_ENABLED        (0)
    /*!< if module is enabled or not */
#endif

#ifndef MCU_WIFI_CONFIG_USE_SHELL
  #define MCU_WIFI_CONFIG_USE_SHELL     (1 && MCU_WIFI_CONFIG_ENABLED)
    /*!< if module shall implements McuShell support */
#endif

#ifndef MCU_WIFI_CONFIG_USE_MININI
  #define MCU_WIFI_CONFIG_USE_MININI     (1 && MCU_WIFI_CONFIG_ENABLED)
    /*!< if module uses MinINI for settings */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_FILE_NAME
  #define MCU_WIFI_CONFIG_MININI_FILE_NAME       "settings.ini" 
    /*!< 'file' name used */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_SECTION_WIFI
  #define MCU_WIFI_CONFIG_MININI_SECTION_WIFI              "WiFi"
#endif

#ifndef MCU_WIFI_CONFIG_MININI_KEY_WIFI_SSID
  #define MCU_WIFI_CONFIG_MININI_KEY_WIFI_SSID                "ssid"     /* string, SSID of network */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_KEY_WIFI_PASS
  #define MCU_WIFI_CONFIG_MININI_KEY_WIFI_PASS                "pass"     /* string, password */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_KEY_WIFI_HOSTNAME
  #define MCU_WIFI_CONFIG_MININI_KEY_WIFI_HOSTNAME            "hostname" /* string, hostname to be used */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_KEY_WIFI_ENABLE
  #define MCU_WIFI_CONFIG_MININI_KEY_WIFI_ENABLE              "enable"   /* bool, if WiFi is enabled */
#endif

#ifndef MCU_WIFI_CONFIG_MININI_KEY_WIFI_RECONNECT
  #define MCU_WIFI_CONFIG_MININI_KEY_WIFI_RECONNECT           "reconnect"   /* bool, if automatic reconnect is enabled */
#endif

/* default values */
#ifndef MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE
  #define MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE       true
#endif

#ifndef MCU_WIFI_CONFIG_WIFI_DEFAULT_RECONNECT
  #define MCU_WIFI_CONFIG_WIFI_DEFAULT_RECONNECT    true
#endif

#endif /* MCU_WIFI_CONFIG_H_ */