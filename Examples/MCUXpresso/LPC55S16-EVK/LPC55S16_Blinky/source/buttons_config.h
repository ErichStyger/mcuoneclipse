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

 /* user button on LPC55S16-EVK board: PIO1_9 */
#define BUTTONS_USER_GPIO       GPIO
#define BUTTONS_USER_PORT       1
#define BUTTONS_USER_PIN        9

typedef enum {
  BTN_USER,
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

#endif /* BUTTONS_CONFIG_H_ */
