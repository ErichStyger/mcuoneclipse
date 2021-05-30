/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "asan_test.h"
#include "McuASAN.h"
#include <stdlib.h>
#include <stdint.h>

static int arr[] = {1,2,3};
static int *p = &arr[0];

static void Test1(void) {
  p = malloc(16);
  free(p);
  arr[0] = *p;
  *p = 0;  /* BOOM: access to released memory */
}

static int Test2(void) {
  int i, *p;
  uint8_t c;

  p = malloc(10);
  c = *((uint8_t*)p);
  for(int j=0; j<10; j++) {
    p[j] = j; /* BOOM: accessing beyond allocated memory */
  }
  free(p);
  i = *p; /* BOOM: access to released memory! */
  return i+c;
}

void ASAN_Test(void)  {
  Test1();
  Test2();
}

