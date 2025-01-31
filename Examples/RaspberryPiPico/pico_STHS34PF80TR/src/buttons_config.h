/*
 * buttons_config.h
 *
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_CONFIG_H_
#define BUTTONS_CONFIG_H_

#include "McuLib.h"
#include "platform.h"

#define BUTTON_HAS_NAV_UP      (0)
#define BUTTON_HAS_NAV_DOWN    (0)
#define BUTTON_HAS_NAV_LEFT    (0)
#define BUTTON_HAS_NAV_RIGHT   (0)
#define BUTTON_HAS_NAV_CENTER  (1)

#if BUTTON_HAS_NAV_UP
  #define BUTTONS_PINS_NAVUP_PIN         15u
#endif
#if BUTTON_HAS_NAV_DOWN
  #define BUTTONS_PINS_NAVDOWN_PIN       14u
#endif
#if BUTTON_HAS_NAV_LEFT
  #define BUTTONS_PINS_NAVLEFT_PIN       13u
#endif
#if BUTTON_HAS_NAV_RIGHT
  #define BUTTONS_PINS_NAVRIGHT_PIN      12u
#endif
#if BUTTON_HAS_NAV_CENTER
  #define BUTTONS_PINS_NAVCENTER_PIN     8u /* SW2 */
#endif

#define BUTTONS_ENABLE_CLOCK() /* nothing */

typedef enum {
#if BUTTON_HAS_NAV_UP
  BTN_NAV_UP,
#endif
#if BUTTON_HAS_NAV_DOWN
  BTN_NAV_DOWN,
#endif
#if BUTTON_HAS_NAV_LEFT
  BTN_NAV_LEFT,
#endif
#if BUTTON_HAS_NAV_RIGHT
  BTN_NAV_RIGHT,
#endif
#if BUTTON_HAS_NAV_CENTER
  BTN_NAV_CENTER,
#endif
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#if BUTTON_HAS_NAV_UP
  #define BTN_BIT_NAV_UP        (1<<0)
#endif
#if BUTTON_HAS_NAV_DOWN
  #define BTN_BIT_NAV_DOWN      (1<<1)
#endif
#if BUTTON_HAS_NAV_LEFT
  #define BTN_BIT_NAV_LEFT      (1<<2)
#endif
#if BUTTON_HAS_NAV_RIGHT
  #define BTN_BIT_NAV_RIGHT     (1<<3)
#endif
#if BUTTON_HAS_NAV_CENTER
  #define BTN_BIT_NAV_CENTER    (1<<4)
#endif

#define BTN_CONFIG_ROTATION  (0) /* 180 for rotated nav 180 degree */

#endif /* BUTTONS_CONFIG_H_ */