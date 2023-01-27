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

  /* McuLib way: */
  McuSWO_SendStr((unsigned char*)"Enter some text and press ENTER:\n");
  McuSWO_ReadLine(buf, bufSize);
  McuSWO_SendStr((unsigned char*)"Received: ");
  McuSWO_SendStr(buf);
}

static void ReadLine_getc(unsigned char *buf, size_t bufSize) {
  int c;
  size_t i = 0;

  /* C standard library way with getc() */
  printf("getc: Enter some text and press ENTER:\n");
  do {
    do {
      c = getc(stdin);
    } while(c==EOF); /* poll for input */
    if (i<bufSize) { /* avoid buffer overflow */
      buf[i++] = c;
    }
  } while(c!='\n');
  buf[bufSize-1] = '\0';
  printf("getc: %s", buf);
}

static void ReadLine_getchar(unsigned char *buf, size_t bufSize) {
  int c;
  size_t i = 0;

  /* C standard library way with getchar() */
  printf("getchar: Enter some text and press ENTER:\n");
  do {
    do {
      c = getchar();
    } while(c==EOF);
    if (i<bufSize) { /* avoid buffer overflow */
      buf[i++] = c;
    }
  } while(c!='\n');
  buf[bufSize-1] = '\0';
  printf("getchar: %s", buf);
}

static void ReadLine_scanf(unsigned char *buf, size_t bufSize) {
  /* C standard library way with scanf() */
  int res;
  char ch;

  printf("scanf: Enter a single name/word and press ENTER:\n");
  assert(bufSize>=20);
  res = scanf("%20s%c", buf, &ch); /* note: ch for the newline */
  printf("scanf: %s, res: %d, ch:%d\n", buf, res, ch);
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
 // TestStdOut();
  for(;;) {
   // ReadLine_McuLib(buf, sizeof(buf));
  //  ReadLine_getc(buf, sizeof(buf));
  //  ReadLine_getchar(buf, sizeof(buf));
    ReadLine_scanf(buf, sizeof(buf));
  }
}

int main(void) {
#if !McuSWO_CONFIG_DO_MUXING /* if Muxing will be done inside McuSWO_Init() */
  BOARD_InitBootPins();
#endif
  BOARD_InitBootClocks();

  PL_Init(); /* initializes modules including SWO */
  SwoTest(); /* set a breakpoint here and configure SWO (SWO Trace Config) and enable SWO ITM Console */
  for(;;) {
	  __asm("nop");
  }
}
