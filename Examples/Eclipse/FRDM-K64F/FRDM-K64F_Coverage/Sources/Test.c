/*
 * Test.c
 *
 *  Created on: 25.12.2014
 *      Author: Erich Styger
 */

#include "Test.h"

static int i;

static int bar(int i) {
  if (i==0) {
    return 2;
  } else if (i==1) {
    return 0;
  } else {
    return 1;
  }
}

void TEST_Test(int val) {
  if (val==10) {
    i = val;
  } else {
    i += bar(i);
  }
}
