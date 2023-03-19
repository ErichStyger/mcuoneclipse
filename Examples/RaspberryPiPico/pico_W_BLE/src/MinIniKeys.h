/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MININIKEYS_H_
#define MININIKEYS_H_

/* strings and names used in minINI configuration file */

#include "app_platform.h"

#define NVMC_MININI_FILE_NAME       "settings.ini" /* 'file' name used */

#if PL_CONFIG_USE_WIFI
  /* section for WiFi settings */
  #define NVMC_MININI_SECTION_WIFI              "WiFi"
  #define NVMC_MININI_KEY_WIFI_SSID                "ssid"     /* SSID of network */
  #define NVMC_MININI_KEY_WIFI_PASS                "pass"     /* pass */
  #define NVMC_MININI_KEY_WIFI_HOSTNAME            "hostname" /* hostname to be used */
#endif

#endif /* MININIKEYS_H_ */
