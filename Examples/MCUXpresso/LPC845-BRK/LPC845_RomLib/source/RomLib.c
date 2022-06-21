/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "RomLib.h" /* own interface */

static int RomLib_Counter; /* not initialized variable in RAM */
static int RomLib_InitVar = 0x12345678; /* initialized variable in RAM */
int RomLib_Variable = 0xfedcba; /* Variable */

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
  /* here do any special initialization, if needed */
  RomLib_Counter = 0x10;
  return 0; /* ok */
}
