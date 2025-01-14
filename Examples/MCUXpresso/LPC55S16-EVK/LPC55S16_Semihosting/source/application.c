/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuSemihost.h"

int McuSemihost_ReadLine(unsigned char *buf, size_t bufSize) {
  int c, i = 0;
  do {
    c = McuSemihost_SysReadC(); /* first call is blocking until user presses enter. Then it returns each character on each iteration, until '\n' */
    if (i<bufSize-1) { /* -1 for zero byte at the end */
      buf[i++] = c; /* only store into buffer if there is enough space, but continue reading until '\n' */
    }
  } while(c!='\n');
  buf[i] = '\0'; /* zero terminate buffer */
  return i;
}

void APP_Run(void) {
  PL_Init(); /* init modules */
  McuSemihost_WriteString((unsigned char*)"hello world with semihosting!\n");
  for(;;) {
	  unsigned char buf[16];
	  int i;

	  McuSemihost_WriteString((unsigned char*)"Please type some text and press <ENTER>:\n");
	  i = McuSemihost_ReadLine(buf, sizeof(buf));
	  McuSemihost_printf("You entered %d characters: %s\n", i, buf);
  }
}
