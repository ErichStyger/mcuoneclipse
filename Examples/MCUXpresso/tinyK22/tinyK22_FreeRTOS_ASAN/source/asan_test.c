/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "asan_test.h"
#include "McuASAN.h"
#include <stdlib.h>
#include <stdint.h>
#include "cr_section_macros.h"

static int arr[] = {1,2,3};
static int *p = &arr[0];

static int TestPointer(void) {
  int *p = arr;
  int sum = 0;

  for(int i=0; i<5; i++) {
     sum += *p;
     p++;
  }
  return sum;
}

static void TestMalloc_1(void) {
  p = malloc(16);
  free(p);
  arr[0] = *p;
  *p = 0;  /* bug: access to released memory */
}

static int TestMalloc_2(void) {
  int i, *p;
  uint8_t c;

  p = malloc(10);
  c = *((uint8_t*)p);
  *p = 0xdeadbeef;
  for(int j=0; j<10; j++) {
    p[j] = j; /* BUG: initialize memory */
  }
  free(p);
  i = *p; /* BUG: access to released memory! */
  return i+c;
}

void ASAN_TEST_Init(void)  {
  TestPointer();
  TestMalloc_1();
  TestMalloc_2();
}

