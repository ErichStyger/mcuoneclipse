/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "RomLib.h" /* own interface */

static int RomLib_Counter; /* initialized in RomLib_Init() */
static int RomLib_InitVar; /* initialized in RomLib_Init() */
int RomLib_Variable; /* not initialized! */

/* example data/constant table in ROM */
const int RomLib_lookupTable[16] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
};

int RomLib_Calculate(int a) {
  return a+RomLib_InitVar;
}

int RomLib_Count(void) {
  RomLib_Counter++;
  return RomLib_Counter;
}

int RomLib_Init(void) {
  /* perform initialization, as needed.
   * Keep in mind that usually ROM libraries do not get initialized by the normal startup code,
   * so all the initialization is done here */
  RomLib_Counter = 0x0;
  RomLib_InitVar = 0x12345678;
  return 0; /* ok */
}
