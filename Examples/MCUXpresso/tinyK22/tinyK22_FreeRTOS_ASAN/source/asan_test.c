/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "asan_test.h"
#include "McuASAN.h"
#include <stdlib.h>
#include <stdint.h>

static int arr[] = {1,2,3};
static int *p = &arr[0];

void ASAN_TEST_1(void) {
  int *p;
  p = malloc(10);
  free(p);
  arr[0] = *p;
  *p = 0;
  //for(;;) {}
  //p = malloc(10);
  //p = malloc(100);
  //p = malloc(1024);
}

static void ASAN_TEST_2(void) {
  int i, *p;
  uint8_t c;

#if 0
  p = malloc(10);
  free(p);
#else
  p = __asan_malloc(10);
  c = *((uint8_t*)p);
  *p = 0xdeadbeef;
  for(int j=0; j<10; j++) {
    p[j] = j; /* read */
  }
  __asan_free(p);
#endif
  i = *p; /* access to released memory! */
}

void ASAN_TEST_Init(void)  {
  ASAN_TEST_2();
  ASAN_TEST_1();
}

