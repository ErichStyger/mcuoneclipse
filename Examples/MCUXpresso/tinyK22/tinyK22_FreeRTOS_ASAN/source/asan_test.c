/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "asan_test.h"
#include <stdlib.h>

static int arr[] = {1,2,3};
static int *p = &arr[0];

void ASAN_TEST_1(void) {
  //int *p;
  //p = malloc(10);
  //free(p);
  arr[0] = *p;
  *p = 0;
  //for(;;) {}
  //p = malloc(10);
  //p = malloc(100);
  //p = malloc(1024);
}

static void ASAN_TEST_2(void) {
  int i, *p;

  p = malloc(10);
  free(p);
  i = *p; /* access to released memory! */
}

void ASAN_TEST_Init(void)  {
  ASAN_TEST_2();
  ASAN_TEST_1();
}
