/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MININIKEYS_H_
#define MININIKEYS_H_

/* strings and names used in minINI configuration file */

#include "platform.h"

#define NVMC_MININI_FILE_NAME       "settings.ini" /* 'file' name used */

/* section for the application settings */
#define NVMC_MININI_SECTION_APPLICATION       "App"
#define NVMC_MININI_APPLICATION_VERSION         "v" /* version number, not use yet */

#if PL_CONFIG_USE_LIGHTS
  /* section for the light/LED settings */
  #define NVMC_MININI_SECTION_LIGHT             "Light"
  #define NVMC_MININI_KEY_LIGHT_ON                "on"      /* 0: light off, 1: light on */
  #define NVMC_MININI_KEY_LIGHT_COLOR             "color"   /* 32bit RGB value */
  #define NVMC_MININI_KEY_LIGHT_BRIGHTNESS        "bright"  /* brightness: 0..255  */
#endif

#if PL_CONFIG_USE_ROAD
  /* section for vehicle/car settings */
  #define NVMC_MININI_SECTION_CAR               "Car"
  #define NVMC_MININI_KEY_CAR_ON                  "on"            /* 0: stopped, 1: on (not stored, always off at reboot to save power) */
  #define NVMC_MININI_KEY_CAR_SPEED               "speed"         /* 0..100 (%) */
  #define NVMC_MININI_KEY_CAR_MODE                "mode"          /* 0: fw, 1: bw, 2: auto */
  #define NVMC_MININI_KEY_CAR_SWITCH_SEG          "switchSeg"     /* 1: switch segments (saves power); 0: no segment switching */
#endif

#if PL_CONFIG_USE_WIFI
  /* section for WiFi settings
   * configure them using the shell and the following commands:
   * McuMinINI write settings.ini WiFi ssid YOUR_SSID
   * McuMinINI write settings.ini WiFi pass YOUR_PASSWORD
   */
  #define NVMC_MININI_SECTION_WIFI              "WiFi"
  #define NVMC_MININI_KEY_WIFI_SSID                "ssid"     /* SSID of network */
  #define NVMC_MININI_KEY_WIFI_PASS                "pass"     /* pass */
  #define NVMC_MININI_KEY_WIFI_HOSTNAME            "hostname" /* hostname to be used */
#endif

#if PL_CONFIG_USE_MQTT_CLIENT
  /* section for MQTT settings */
  #define NVMC_MININI_SECTION_MQTT              "MQTT"
  #define NVMC_MININI_KEY_MQTT_BROKER              "broker"   /* broker IP */
  #define NVMC_MININI_KEY_MQTT_CLIENT              "client"   /* client ID */
  #define NVMC_MININI_KEY_MQTT_USER                "user"     /* username */
  #define NVMC_MININI_KEY_MQTT_PASS                "pass"     /* password */
#endif

#if PL_CONFIG_IS_APP_LED_COUNTER
  /* settings for LED counter application */
  #define NVMC_MININI_SECTION_LED               "LED"
  #define NVMC_MININI_KEY_LED_POS                 "pos"     /* counter.pos */
  #define NVMC_MININI_KEY_LED_COLOR               "color"   /* counter.color */
  #define NVMC_MININI_KEY_LED_MODE                "mode"    /* counter.mode */
  #define NVMC_MININI_KEY_LED_BRIGHTNESS          "bright"  /* counter.brightness */
#endif

#endif /* MININIKEYS_H_ */
