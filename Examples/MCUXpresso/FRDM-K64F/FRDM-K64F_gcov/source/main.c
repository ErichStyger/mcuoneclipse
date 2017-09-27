/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    FRDM-K64F_gcov.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"

/* TODO: insert other include files here. */
#include "gcov_support.h"

/* TODO: insert other definitions and declarations here. */
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

static void TestCoverage(int i) {
  Test2(&i);
  if (i==0) {
    printf("i is zero!\n");
  } else {
    printf("i is not zero!\n");
  }
}
/*
 * @brief   Application entry point.
 */
int main(void) {
#if GCOV_DO_COVERAGE
    gcov_init();
    if (!gcov_check()) {
      printf("WARNING: writing coverage does not work! Wrong library used?\n");
    }
#endif
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
  	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

    printf("Hello World\n");


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    TestCoverage(3);
#if GCOV_USE_TCOV
    gcov_write();
#endif
    while(1) {
        i++ ;
    }
    return 0 ;
}
