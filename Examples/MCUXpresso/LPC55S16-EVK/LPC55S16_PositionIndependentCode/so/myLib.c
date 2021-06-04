/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* library module which is built with -fPIC (position-independent code) mode, implemented as shared-object */

#include "myLib.h"

static int glob;

int MyLib_Calc(int x) {
  glob++;
  return x*2;
}

int MyLib_Mul2(int x) {
  return x*2;
}

void MyLib_Init(void) {
}
