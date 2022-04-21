/*
 * buttons_config.h
 *
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef BUTTONS_CONFIG_H_
#define BUTTONS_CONFIG_H_

#include "McuLib.h"

///* user button on LPC55S16-EVK board: PIO1_9 */
//#define BUTTONS_USER_GPIO       GPIO
//#define BUTTONS_USER_PORT       1
//#define BUTTONS_USER_PIN        9
//
///* wakeup button on LPC55S16-EVK board: PIO1_18 */
//#define BUTTONS_WAKEUP_GPIO     GPIO
//#define BUTTONS_WAKEUP_PORT     1
//#define BUTTONS_WAKEUP_PIN      18
//
///* user up button on LPC55S16-EVK board J22 HDR_1X1: PIO0_7 */
//#define BUTTONS_UP_GPIO         GPIO
//#define BUTTONS_UP_PORT         0
//#define BUTTONS_UP_PIN          7

/* wakeup button on LPC55S16-EVK board: PIO1_18 */
#define BUTTONS_SHIELD_BTN1_GPIO     GPIO
#define BUTTONS_SHIELD_BTN1_PORT     1
#define BUTTONS_SHIELD_BTN1_PIN      31

/* user up button on LPC55S16-EVK board J22 HDR_1X1: PIO0_7 */
#define BUTTONS_SHIELD_BTN2_GPIO         GPIO
#define BUTTONS_SHIELD_BTN2_PORT         1
#define BUTTONS_SHIELD_BTN2_PIN          5

typedef enum {
  BTN_BT1,
  BTN_BT2,
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#define BTN_BIT_BT1        (1<<0)
#define BTN_BIT_BT2      (1<<1)

#endif /* BUTTONS_CONFIG_H_ */
