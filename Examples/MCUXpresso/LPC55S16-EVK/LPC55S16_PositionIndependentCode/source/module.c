/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "module.h"

int var, var2;

void foo(void) {
  var = 1;
  var2 = 2;
}

void bar(void) {
  var = 2;
}

void MODULE_Init(void) {
  var = 1;
  foo();
  bar();
}
