/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MININIKEYS_H_
#define MININIKEYS_H_

/* strings and names used in minINI configuration file */

#include "app_platform.h"

#define NVMC_MININI_FILE_NAME       "vhs.ini" /* 'file' name used */

/* section for the application settings */
#define NVMC_MININI_SECTION_APPLICATION       "App"
#define NVMC_MININI_APPLICATION_VERSION         "v" /* version number */

/* section for the light/LED settings */
#define NVMC_MININI_SECTION_LIGHT             "Light"
#define NVMC_MININI_KEY_LIGHT_ON                "on"      /* 0: light off, 1: light on */
#define NVMC_MININI_KEY_LIGHT_COLOR             "color"   /* 32bit RGB value */
#define NVMC_MININI_KEY_LIGHT_BRIGHTNESS        "bright"  /* brightness: 0..255  */

/* section for vehicle/car settings */
#define NVMC_MININI_SECTION_CAR               "Car"
#define NVMC_MININI_KEY_CAR_ON                  "on"      /* 0: stopped, 1: on */
#define NVMC_MININI_KEY_CAR_SPEED               "speed"   /* 0..100 (%) */
#define NVMC_MININI_KEY_CAR_MODE                "mode"    /* 0: fw, 1: bw, 2: auto */

#endif /* MININIKEYS_H_ */
