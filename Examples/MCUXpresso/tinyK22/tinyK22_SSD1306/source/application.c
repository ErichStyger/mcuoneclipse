/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* own modules and standard library */
#include "platform.h"
#include "application.h" /* own interface */

/* own modules */
#include "oled.h"

void APP_Run(void) {
  PL_Init();
  OLED_doOLED();
}
