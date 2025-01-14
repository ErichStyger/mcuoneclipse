/*
 * buttons_config.h
 *
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef BUTTONS_CONFIG_H_
#define BUTTONS_CONFIG_H_

#include "platform.h"
#include "McuLib.h"

#if PL_CONFIG_HAS_USER_BUTTON
  /* user button on LPC55S16-EVK board: PIO1_9 */
  #define BUTTONS_USER_GPIO       GPIO
  #define BUTTONS_USER_PORT       1
  #define BUTTONS_USER_PIN        9
#endif

/* wake-up button on LPC55S16-EVK board: PIO1_18 */
#define BUTTONS_WAKEUP_GPIO     GPIO
#define BUTTONS_WAKEUP_PORT     1
#define BUTTONS_WAKEUP_PIN      18

/* user up button on LPC55S16-EVK board J22 HDR_1X1: PIO0_7 */
#define BUTTONS_UP_GPIO         GPIO
#define BUTTONS_UP_PORT         0
#define BUTTONS_UP_PIN          7

typedef enum {
#if PL_CONFIG_HAS_USER_BUTTON
  BTN_USER,
#endif
  BTN_WAKEUP,
  BTN_UP,
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#if PL_CONFIG_HAS_USER_BUTTON
  #define BTN_BIT_USER        (1<<0)
#endif
#define BTN_BIT_WAKEUP      (1<<1)
#define BTN_BIT_UP          (1<<2)

#endif /* BUTTONS_CONFIG_H_ */
