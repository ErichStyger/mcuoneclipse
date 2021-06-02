/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "module.h"

const int carr[] = {1,2,3,4};
int var, var2;

void foo(void) {
  var = 1;
  var2 = 2;
}

void bar(void) {
  var = 2;
}

const int *foobar(void) {
  return &carr[0];
}

void MODULE_Init(void) {
  var = 1;
  foo();
  bar();
}
