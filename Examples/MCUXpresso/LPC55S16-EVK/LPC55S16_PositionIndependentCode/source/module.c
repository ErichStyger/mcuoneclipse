/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "module.h"

const int carr[] = {1,2,3,4};
int var, var2;

int calc2(int i) {
  var = i;
  return i*2;
}

int calc(int i) {
  var = i;
  var2 = calc2(i+1);
  return var+var2;
}

int doIt(int i) {
  return calc2(i);
}

void foo(void) {
  var++;
}

extern void foobar(void);
void bar(void) {
  foo();
  foobar();
}

void MODULE_Init(void) {
  var = 1;
  foo();
  bar();
}
