/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "test.h"

int var = 5;

void TEST_Test(void) {
  if (var<10) {
    var++;
  } else {
    var = 20;
  }
}
