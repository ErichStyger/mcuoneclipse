/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_CONFIG_H_
#define BUTTONS_CONFIG_H_

#include "platform.h"

#if PL_CONFIG_USE_BUTTONS

/* GPIO pins for buttons */
#if (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5) || (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_7)
  #define BUTTONS_PINS_NAV_UP_PIN       3u
  #define BUTTONS_PINS_NAV_DOWN_PIN     6u
  #define BUTTONS_PINS_NAV_LEFT_PIN     4u
  #define BUTTONS_PINS_NAV_RIGHT_PIN    7u
  #define BUTTONS_PINS_NAV_CENTER_PIN   8u
  #if PL_CONFIG_USE_BUTTON_NEXT_PREV
    #define BUTTONS_PINS_NAV_NEXT_PIN     9u
    #define BUTTONS_PINS_NAV_PREV_PIN     5u
  #endif
#else
  #define BUTTONS_PINS_NAV_UP_PIN       15u /* GPIO15 */
  #define BUTTONS_PINS_NAV_DOWN_PIN     14u /* GPIO14 */
  #define BUTTONS_PINS_NAV_LEFT_PIN     13u /* GPIO13 */
  #define BUTTONS_PINS_NAV_RIGHT_PIN    12u /* GPIO12 */
  #define BUTTONS_PINS_NAV_CENTER_PIN   11u /* GPIO11 */
  #if PL_CONFIG_USE_BUTTON_NEXT_PREV
    #define BUTTONS_PINS_NAV_NEXT_PIN     10u /* GPIO10 */
    #define BUTTONS_PINS_NAV_PREV_PIN     9u  /* GPIO9 */
  #endif
#endif

#define BUTTONS_ENABLE_CLOCK()  /* enable clocking */

typedef enum {
  BTN_NAV_UP,
  BTN_NAV_DOWN,
  BTN_NAV_LEFT,
  BTN_NAV_RIGHT,
  BTN_NAV_CENTER,
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
  BTN_NAV_NEXT,
  BTN_NAV_PREV,
#endif
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#define BTN_BIT_NAV_UP        (1<<0)
#define BTN_BIT_NAV_DOWN      (1<<1)
#define BTN_BIT_NAV_LEFT      (1<<2)
#define BTN_BIT_NAV_RIGHT     (1<<3)
#define BTN_BIT_NAV_CENTER    (1<<4)
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
#define BTN_BIT_NAV_NEXT      (1<<5)
#define BTN_BIT_NAV_PREV      (1<<6)
#endif

#if PL_CONFIG_HW_ACTIVE_HW_VERSION ==PL_CONFIG_HW_VERSION_0_1
  #define BTN_CONFIG_ROTATION  (180)
#elif PL_CONFIG_HW_ACTIVE_HW_VERSION ==PL_CONFIG_HW_VERSION_0_2
  #define BTN_CONFIG_ROTATION  (180)
#elif PL_CONFIG_HW_ACTIVE_HW_VERSION ==PL_CONFIG_HW_VERSION_0_3
  #define BTN_CONFIG_ROTATION  (0) /* \todo check */
#elif PL_CONFIG_HW_ACTIVE_HW_VERSION ==PL_CONFIG_HW_VERSION_0_4
  #define BTN_CONFIG_ROTATION  (0)
#elif (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5) || (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_7)
  #define BTN_CONFIG_ROTATION  (0)
#else
  #define BTN_CONFIG_ROTATION  (0) /* 180 for rotated nav PCB 180 degree */
#endif

#endif /* PL_CONFIG_USE_BUTTONS */

#endif /* BUTTONS_CONFIG_H_ */
