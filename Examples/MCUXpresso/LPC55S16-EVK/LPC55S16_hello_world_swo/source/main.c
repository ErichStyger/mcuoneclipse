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
#include "McuSWO.h"

static void SwoTest(void) {
  unsigned char ch;
  McuSWO_SendStr((unsigned char*)"Application using SWO\n"); /* stop with the debugger here and configure SWO */
  for(;;) {
	McuSWO_SendStr((unsigned char*)"test, type in text and press ENTER:\n");
	//printf("swo hello from printf!\n");
	//printf("Please enter a key:\n");
   // scanf("%c", &c);
	//c = getc(stdin);
	while(!McuSWO_StdIOKeyPressed()) {
	  __asm("nop");
	}
	McuSWO_stdio.stdIn(&ch);
	McuSWO_StdIOSendChar(ch);
	//printf("character entered:\n");
	//putc(ch, stdout);
	McuWait_Waitms(100);
  }
}

int main(void) {
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE); /*!< Switch TRACE to TRACE_DIV */
#if !McuSWO_CONFIG_DO_MUXING
  BOARD_InitBootPins();
#endif
  BOARD_BootClockFROHF96M();
  CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 2U, false);          /* Set AHBCLKDIV divider to value 2 */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 2U, false);     /* Set ARMTRCLKDIV divider to value 2 */
  PL_Init();
  SwoTest();
  for(;;) {
	  __asm("nop");
  }
}
