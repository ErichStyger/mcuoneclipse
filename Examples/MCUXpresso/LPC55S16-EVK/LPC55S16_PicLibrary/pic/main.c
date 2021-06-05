/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "myLib.h"

int var1;
int var2;
int var3 = 0xdeadbeef;

int main ( void ) {
	var1 = 1;
	var2 = 2;
	var3 = MyLib_Calc(5);
	for(;;) {
	}
}
