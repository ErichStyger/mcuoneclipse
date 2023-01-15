/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include <stdbool.h>
#include <stdio.h>
#include "fsl_power.h"

#include "platform.h"
#include "McuWait.h"
#include "McuSWO.h"

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
  McuSWO_SendStr("Application using SWO\n");
  for(;;) {
    //printf("swo hello!\n");
    McuSWO_SendStr("test\n");
    McuWait_Waitms(1000);
  }
}
