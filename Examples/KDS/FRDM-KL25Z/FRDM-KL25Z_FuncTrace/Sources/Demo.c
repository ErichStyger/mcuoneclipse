/*
 * Demo.c
 *
 *  Created on: 15.03.2015
 *      Author: tastyger
 */

#include "Demo.h"
#include "CygProfile.h"

static int foobar(int i, int j) {
  return i+j;
}

static int bar(int i) {
  return foobar(i, 5);
}

static int foo(int i) {
  if (i<10) {
    return foobar(i,5)+bar(7);
  } else {
    return bar(i);
  }
}

int DEMO_Run(void) {
  int i, j, k;

  for(i=0;i<3;i++) {
    j = foo(i);
  }
  k = bar(j*4);
  return j+k;
}

void DEMO_Init(void) {
}

#if CYG_FUNC_TRACE_NAMES_ENABLED
__attribute__((no_instrument_function))
const char *DEMO_getFuncName(void *addr) {
  if (addr==foobar) {
    return "foobar";
  } else if (addr==foo) {
    return "foo";
  } else if (addr==bar) {
    return "bar";
  } else if (addr==DEMO_Run) {
    return "DEMO_Run";
  } else if (addr==DEMO_Init) {
    return "DEMO_Init";
  }
  return "";
}
#endif /* __FUNC_TRACE_ENABLED */
