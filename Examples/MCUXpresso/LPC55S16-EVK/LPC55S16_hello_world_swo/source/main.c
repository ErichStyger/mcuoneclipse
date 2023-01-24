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

static void SwoTest(void) {
  unsigned char ch;
  unsigned char buf[64];

  McuSWO_SendStr((unsigned char*)"Application using SWO\n"); /* stop with the debugger here and configure SWO */
  for(;;) {
    McuSWO_SendStr((unsigned char*)"Enter some text and press ENTER:\n");
	//printf("swo hello from printf!\n");
	//printf("Please enter a key:\n");
   // scanf("%c", &c);
	//c = getc(stdin);
    buf[0] = '\0'; /* init buffer */
    for(;;) { /* breaks */
    	if (McuSWO_StdIOKeyPressed()) {
    		McuSWO_stdio.stdIn(&ch);
    		if (ch!='\0') {
    		  McuUtility_chcat(buf, sizeof(buf), ch);
    		  if (ch=='\n') {
    			  break;
    		  }
    		}
    	}
    }
	McuSWO_SendStr((unsigned char*)"Received: ");
	McuSWO_SendStr(buf);

	//printf("character entered:\n");
	//putc(ch, stdout);
	//McuWait_Waitms(100);
  }
}

int main(void) {
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
//#if !McuSWO_CONFIG_DO_MUXING
  BOARD_InitBootPins();
//#endif
#if 1  /* << if commented out, SWO configuration fails */
  BOARD_BootClockFROHF96M();
#endif
//  CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 2U, false);          /* Set AHBCLKDIV divider to value 2 */
//  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 2U, false);     /* Set ARMTRCLKDIV divider to value 2 */
//  PL_Init();
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE); /*!< Switch TRACE to TRACE_DIV */
  SwoTest(); /* set a breakpoint here and configure SWO (SWO Trace Config) and enable SWO ITM Console */
  for(;;) {
	  __asm("nop");
  }
}
