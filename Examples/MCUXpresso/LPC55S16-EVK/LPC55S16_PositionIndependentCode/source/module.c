/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "module.h"

static int var;

void MODULE_Init(void) {
  var = 1;
}
