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

#define BUTTONS_PINS_USER_PIN          0u /* GPIO0 */

#define BUTTONS_ENABLE_CLOCK() /* nothing */

typedef enum {
  BTN_USER,        /* user button */
  BTN_NOF_BUTTONS  /* sentinel, must be last in list! */
} BTN_Buttons_e;

/* bits of the buttons */
#define BTN_BIT_USER          (1<<0)


#endif /* BUTTONS_CONFIG_H_ */
