/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

#include "platform.h"

#define LEDS_CONFIG_HAS_ONBOARD_LED        (1 && (PL_CONFIG_BOARD_IS_PICO || PL_CONFIG_BOARD_IS_ADAFRUIT))
#define LEDS_CONFIG_HAS_RED_LED            (0)
#define LEDS_CONFIG_HAS_GREEN_LED          (0)
#define LEDS_CONFIG_HAS_BLUE_LED           (0)
#define LEDS_CONFIG_HAS_ORANGE_LED         (0)
/* Green: GPIO18
  * Blue:  GPIO19
  * Red:   GPIO20 */
#define LEDS_CONFIG_ENABLE_CLOCK()    /* nothing */

#if LEDS_CONFIG_HAS_RED_LED
  #define LEDS_CONFIG_RED_PIN           20
  #define LEDS_CONFIG_RED_LOW_ACTIVE    false
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  #define LEDS_CONFIG_GREEN_PIN         19
  #define LEDS_CONFIG_GREEN_LOW_ACTIVE  false
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  #define LEDS_CONFIG_BLUE_PIN          18
  #define LEDS_CONFIG_BLUE_LOW_ACTIVE   false
#endif

#if LEDS_CONFIG_HAS_ONBOARD_LED
  #if PL_CONFIG_BOARD_IS_PICO
    #define LEDS_CONFIG_ONBOARD_PIN          25 /* only for non-W! */
    #define LEDS_CONFIG_ONBOARD_LOW_ACTIVE   false
  #elif PL_CONFIG_BOARD_IS_ADAFRUIT
    #define LEDS_CONFIG_ONBOARD_PIN          13 /* GPIO13 */
    #define LEDS_CONFIG_ONBOARD_LOW_ACTIVE   false
  #endif
#endif

#endif /* LEDS_CONFIG_H_ */
