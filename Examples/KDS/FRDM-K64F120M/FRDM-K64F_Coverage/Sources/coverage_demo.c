/*
 * coverage_demo.c
 *
 *  Created on: 27.05.2015
 *      Author: tastyger
 */

#include "coverage_demo.h"
#include "UTIL1.h"
#include "Test.h"

#if 0
int k, i, j;

void xx(void) {
  k = 0;
  if (i==10) {
    i += j;
    j++;
  } else {
    foox();
  }
  barx();
}
#endif

static int foo(int i) {
	if (i<5) {
      return 1;
	} else if (i>20) {
      return 2;
	} else {
	  return 3;
	}
}

int COV_Demo(void) {
  int i = UTIL1_IsLeapYear(2015), j = 0;

  j = T_doit(3);
  for(i=0;i<10;i++) {
	  j += foo(i);
  }
  return j;
}
