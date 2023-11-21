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
#include "FreeRTOS.h"
#include "task.h"

/* NOTE: might need to do a full clean/rebuild and remove existing coverage information first! */

int testFunc(int i) {
  if (i>5) {
    return -1;
  }
  return i;
}

static void AppTask(void *pv) {
#if 0
  vTaskDelay(pdMS_TO_TICKS(100));
  vTaskEndScheduler();
  for(;;) {}
#else
  int cntr = 0;
  (void)pv;
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(100));
    cntr++;
    if (cntr>20) {
      vTaskEndScheduler();
    }
  }
#endif
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

static void TestCoverage(int i) {
  Test2(&i);
  if (i==0) {
    printf("i is zero!\n");
  } else {
    printf("i is not zero!\n");
  }
}

int main(void) {
#if GCOV_DO_COVERAGE
  #if defined(__REDLIB__)
    #error "gcov not supported with RedLib"
  #else
    gcov_init(); /* do *not* call this for redlib as it does not implement constructors! */
  #endif
    if (!gcov_check()) {
      printf("WARNING: writing coverage does not work! Wrong library used?\n");
    }
#endif
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
  	/* Init FSL debug console. */
  	BOARD_InitDebugConsole();

    TestCoverage(3); /* quick coverage test */
    testFunc(3);
#if 1
    if (xTaskCreate(AppTask, "App", 1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!= pdPASS) {
      for(;;) {}
    }
    vTaskStartScheduler();
#endif
    /* here we have ended the scheduler so we can write the coverage data */
#if GCOV_DO_COVERAGE
    /* write coverage files, might take a while depending how many files are covered */
    gcov_write_files();
#endif
    for(;;) { /* do not leave main */
      __asm("nop");
      __asm volatile("bkpt #0");
    }
    return 0 ;
}
