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
#define BUTTONS_PINS_NAV_UP_PIN         14u
#define BUTTONS_PINS_NAV_DOWN_PIN       15u
#define BUTTONS_PINS_NAV_LEFT_PIN       28u
#define BUTTONS_PINS_NAV_RIGHT_PIN      26u
#define BUTTONS_PINS_NAV_CENTER_PIN     27u

#define BUTTONS_ENABLE_CLOCK()  /* enable clocking */

typedef enum {
  BTN_NAV_UP,
  BTN_NAV_DOWN,
  BTN_NAV_LEFT,
  BTN_NAV_RIGHT,
  BTN_NAV_CENTER,
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#define BTN_BIT_NAV_UP        (1<<0)
#define BTN_BIT_NAV_DOWN      (1<<1)
#define BTN_BIT_NAV_LEFT      (1<<2)
#define BTN_BIT_NAV_RIGHT     (1<<3)
#define BTN_BIT_NAV_CENTER    (1<<4)

#endif /* PL_CONFIG_USE_BUTTONS */

#endif /* BUTTONS_CONFIG_H_ */
