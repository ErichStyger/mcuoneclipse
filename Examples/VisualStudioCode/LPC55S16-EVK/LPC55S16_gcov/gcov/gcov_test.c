/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "gcov_test.h"
#include <stdio.h>

static int Calc(int i, int j) {
  int res;
  if (i==0) {
    res = i+1;
  } else if (i>0 && j<10) {
    res = i+j;
  }
  return res;
}

static int Value(int i) {
  if (i==3) {
    return 5;
  }
  return 1;
}

static void Test2(int *p) {
  if (*p!=0) {
    if (Value(*p)==5) {
      printf("value is 5\n");
      *p = 0;
    }
  }
}

void gcov_test(int i) {
  int j = Calc(i, i*2);
  Test2(&j);
  if (j==0) {
    printf("j is zero!\n");
  } else {
    printf("j is not zero!\n");
  }
}
