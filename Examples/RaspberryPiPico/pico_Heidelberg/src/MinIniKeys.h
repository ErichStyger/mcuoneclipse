/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MININIKEYS_H_
#define MININIKEYS_H_

/* strings and names used in minINI configuration file */

#include "app_platform.h"

#define NVMC_MININI_FILE_NAME       "settings.ini" /* 'file' name used */

/* section for the application settings */
#define NVMC_MININI_SECTION_APPLICATION       "App"
#define NVMC_MININI_APPLICATION_VERSION         "v" /* version number */

/* section for the light/LED settings */
#define NVMC_MININI_SECTION_LIGHT             "Light"
#define NVMC_MININI_KEY_LIGHT_ON                "on"      /* 0: light off, 1: light on */
#define NVMC_MININI_KEY_LIGHT_COLOR             "color"   /* 32bit RGB value */
#define NVMC_MININI_KEY_LIGHT_BRIGHTNESS        "bright"  /* brightness: 0..255  */

/* section for WiFi settings */
#define NVMC_MININI_SECTION_WIFI              "WiFi"
#define NVMC_MININI_KEY_WIFI_SSID                "ssid"     /* SSID of network */
#define NVMC_MININI_KEY_WIFI_PASS                "pass"     /* pass */
#define NVMC_MININI_KEY_WIFI_HOSTNAME            "hostname" /* hostname to be used */

/* section for MQTT settings */
#define NVMC_MININI_SECTION_MQTT              "MQTT"
#define NVMC_MININI_KEY_MQTT_BROKER              "broker"   /* broker IP */
#define NVMC_MININI_KEY_MQTT_CLIENT              "client"   /* client ID */
#define NVMC_MININI_KEY_MQTT_USER                "user"     /* username */
#define NVMC_MININI_KEY_MQTT_PASS                "pass"     /* password */

#endif /* MININIKEYS_H_ */
