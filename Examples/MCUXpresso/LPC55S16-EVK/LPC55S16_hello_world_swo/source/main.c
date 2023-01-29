/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"

#include "platform.h"
#include "McuSWO.h"
#include "McuWait.h"
#include "McuUtility.h"

static void SimpleAdder(void) {
  unsigned char buf[32];
  const unsigned char *p;
  int32_t a, b;

  McuSWO_SendStr("\nSimple SWO Adder\n----------------\nType the first number and press ENTER:\n");
  McuSWO_ReadLineBlocking(buf, sizeof(buf));
  p = buf;
  McuUtility_xatoi(&p, &a);
  McuSWO_SendStr("Type a second number and press ENTER:\n");
  McuSWO_ReadLineBlocking(buf, sizeof(buf));
  p = buf;
  McuUtility_xatoi(&p, &b);
//  McuSWO_printf("The result of %d + %d is %d\n", a, b, a+b);
}

static void ReadLineTimeout(void) {
  unsigned char buf[32], res;
  int timeoutMs = 5000;

  buf[0] = '\0'; /* init */
  McuSWO_printf("Enter a line of text:\n", buf);
  for(;;) { /* breaks */
    res = McuSWO_ReadAppendLine(buf, sizeof(buf));
    if (res==ERR_OK) {
      McuSWO_printf("received: %s\n", buf);
      break;
    }
    McuWait_Waitms(1);
    timeoutMs--;
    if (timeoutMs<0) {
      break;
    }
  }
}

int main(void) {
  int i = 0;

#if !McuSWO_CONFIG_DO_MUXING /* if Muxing will be done inside McuSWO_Init(), don't need to to do it with the pins tool */
  BOARD_InitBootPins();
#endif
  BOARD_InitBootClocks(); /* note: SystemCoreClock has to be set, otherwise SWO debugger will fail! */

  PL_Init(); /* initializes modules including SWO */
  McuSWO_TestStdio(); /* set a breakpoint here and configure SWO (SWO Trace Config) and enable SWO ITM Console */
 // for(;;) {
//    SimpleAdder();
 // }
#if 1
  for(;;) {
    ReadLineTimeout();
	  McuSWO_printf("hello from SWO: %d\n", i);
	  i++;
	  McuWait_Waitms(1000);
  }
#endif
}
