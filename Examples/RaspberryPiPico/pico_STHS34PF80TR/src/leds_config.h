/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_
 
#define LEDS_CONFIG_HAS_RED_LED            (1) /* 1: has red LED */
#define LEDS_CONFIG_HAS_GREEN_LED          (1) /* 1: has green LED */
#define LEDS_CONFIG_HAS_BLUE_LED           (0) /* 1: has blue LED */

#if LEDS_CONFIG_HAS_RED_LED
  #define LEDS_CONFIG_RED_PIN             0U
  #define LEDS_CONFIG_RED_LOW_ACTIVE      false
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  #define LEDS_CONFIG_GREEN_PIN           1U
  #define LEDS_CONFIG_GREEN_LOW_ACTIVE    false
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  #define LEDS_CONFIG_BLUE_PIN            18U
  #define LEDS_CONFIG_BLUE_LOW_ACTIVE     false
#endif

#endif /* LEDS_CONFIG_H_ */
