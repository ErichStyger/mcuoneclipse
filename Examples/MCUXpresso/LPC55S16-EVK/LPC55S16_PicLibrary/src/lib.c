/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "lib.h"

static int cntr = 0;

int LIB_Utility(void) {
  return 1;
}

int LIB_Calculate(int i) {
  return cntr++;
}

void LIB_Init(void) {
  cntr = LIB_Utility();
}
