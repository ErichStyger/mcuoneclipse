/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include "fsl_power.h"

#include "platform.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuSWO.h"

static void ReadLine_McuLib(unsigned char *buf, size_t bufSize) {
  unsigned char ch;

  buf[0] = '\0'; /* init buffer */
  for(;;) { /* breaks */
    if (McuSWO_StdIOKeyPressed()) {
      McuSWO_stdio.stdIn(&ch);
      if (ch!='\0') {
        McuUtility_chcat(buf, bufSize, ch);
        if (ch=='\n') {
          break;
        }
      } /* if */
    } /* if */
  } /* for */
}

static void ReadLine_getc(unsigned char *buf, size_t bufSize) {
  int c;
  size_t i = 0;

  do {
    do {
      c = getc(stdin);
    } while(c==EOF);
    if (i<bufSize) { /* avoid buffer overflow */
      buf[i] = c;
    }
  } while(c!='\n');
  buf[bufSize-1] = '\0';
}

static void TestStdOut(void) {
  printf("Using printf() with SWO\n");
  putc('*', stdout);
  putc('#', stderr);
  putchar('!');
  putchar('\n');
}

static void SwoTest(void) {
  unsigned char ch;
  unsigned char buf[64];
  int c;

  McuSWO_SendStr((unsigned char*)"Application using SWO\n"); /* stop with the debugger here and configure SWO */
  TestStdOut();
  for(;;) {
    printf("Enter some text and press ENTER:\n");
    ReadLine_getc(buf, sizeof(buf));
#if 0
    // scanf("%c", &c);
    do {
      c = getc(stdin);
    } while(c==EOF);
    printf("getc(): '%c'\n", c);
#endif
    McuSWO_SendStr((unsigned char*)"Enter some text and press ENTER:\n");
	  ReadLine_McuLib(buf, sizeof(buf));
    McuSWO_SendStr((unsigned char*)"McuLib: ");
    McuSWO_SendStr(buf);
  }
}

int main(void) {
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false); /* required for LPC55Sxx, otherwise might generate brown-out reset */
#if !McuSWO_CONFIG_DO_MUXING /* if Muxing will be done inside McuSWO_Init() */
  BOARD_InitBootPins();
#endif
  BOARD_BootClockFROHF96M(); /* Note: need this, otherwise debugger fails to configure SWO */
  PL_Init(); /* initializes modules including SWO */
  SwoTest(); /* set a breakpoint here and configure SWO (SWO Trace Config) and enable SWO ITM Console */
  for(;;) {
	  __asm("nop");
  }
}
