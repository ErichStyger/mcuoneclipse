/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"

void APP_Run(void) {
  PL_Init(); /* init modules */
  for(;;) { /* should not get here */ }
}
