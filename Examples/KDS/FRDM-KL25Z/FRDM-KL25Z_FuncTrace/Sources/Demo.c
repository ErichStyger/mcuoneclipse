/**
 * \file
 * \brief Demo functions to test the profile/function recorder.
 * \author Erich Styger
 */

#include "Demo.h"
#include "CygProfile.h"

static int calcValue(int i, int j) {
  return i/j;
}

static int getValue(int i) {
  if (i>0) {
    return calcValue(i, 5);
  } else {
    return 0;
  }
}

static int decide(int i) {
  if (i<10) {
    return calcValue(i,5)+getValue(7);
  } else {
    return getValue(i);
  }
}

int DEMO_Run(void) {
  int i, j, k;

  for(i=0;i<3;i++) {
    j = decide(i);
  }
  k = getValue(j*4);
  return j+k;
}

void DEMO_Init(void) {
}

#if CYG_FUNC_TRACE_NAMES_ENABLED
__attribute__((no_instrument_function))
const char *DEMO_getFuncName(void *addr) {
  if (addr==calcValue) {
    return "calcValue";
  } else if (addr==decide) {
    return "decide";
  } else if (addr==getValue) {
    return "getValue";
  } else if (addr==DEMO_Run) {
    return "DEMO_Run";
  } else if (addr==DEMO_Init) {
    return "DEMO_Init";
  }
  return "";
}
#endif /* __FUNC_TRACE_ENABLED */
