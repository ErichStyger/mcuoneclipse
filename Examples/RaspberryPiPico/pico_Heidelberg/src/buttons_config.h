/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_CONFIG_H_
#define BUTTONS_CONFIG_H_

/* GPIO pins for buttons */
#define BUTTONS_PINS_HATNAVUP_PIN       15u /* GPIO15 */
#define BUTTONS_PINS_HATNAVDOWN_PIN     14u /* GPIO14 */
#define BUTTONS_PINS_HATNAVLEFT_PIN     13u /* GPIO13 */
#define BUTTONS_PINS_HATNAVRIGHT_PIN    12u /* GPIO12 */
#define BUTTONS_PINS_HATNAVCENTER_PIN   11u /* GPIO11 */
#define BUTTONS_PINS_HATNAVSET_PIN      10u /* GPIO10 */
#define BUTTONS_PINS_HATNAVRESET_PIN     9u /* GPIO9 */

#define BUTTONS_ENABLE_CLOCK()  /* enable clocking */

typedef enum {
  BTN_NAV_UP,
  BTN_NAV_DOWN,
  BTN_NAV_LEFT,
  BTN_NAV_RIGHT,
  BTN_NAV_CENTER,
  BTN_NAV_SET,
  BTN_NAV_RESET,
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;


/* bits of the buttons */
#define BTN_BIT_NAV_UP        (1<<0)
#define BTN_BIT_NAV_DOWN      (1<<1)
#define BTN_BIT_NAV_LEFT      (1<<2)
#define BTN_BIT_NAV_RIGHT     (1<<3)
#define BTN_BIT_NAV_CENTER    (1<<4)
#define BTN_BIT_NAV_SET       (1<<5)
#define BTN_BIT_NAV_RESET     (1<<6)

#include "app_platform.h"
#if 1 || PL_CONFIG_HW_ACTIVE_HW_VERSION ==PL_CONFIG_HW_VERSION_0_1
  #define BTN_CONFIG_ROTATION  (0)
#else
  #define BTN_CONFIG_ROTATION  (180) /* 180 for rotated nav PCB 180 degree */
#endif

#endif /* BUTTONS_CONFIG_H_ */
