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

#if PL_CONFIG_USE_LIGHTS
  /* section for the light/LED settings */
  #define NVMC_MININI_SECTION_LIGHT             "Light"
  #define NVMC_MININI_KEY_LIGHT_ON                "on"      /* 0: light off, 1: light on */
  #define NVMC_MININI_KEY_LIGHT_COLOR             "color"   /* 32bit RGB value */
  #define NVMC_MININI_KEY_LIGHT_BRIGHTNESS        "bright"  /* brightness: 0..255  */
#endif

#endif /* MININIKEYS_H_ */
