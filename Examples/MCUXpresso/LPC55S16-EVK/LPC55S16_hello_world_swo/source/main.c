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
#if defined(FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER) && FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER
#include "fsl_syscon.h"
#else
#include "fsl_inputmux.h"
#endif /* FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER */
#include "fsl_pint.h"
#include "fsl_power.h"

#include "platform.h"
#include "McuWait.h"
#include "McuSWO.h"

static void BOARD_InitDebugConsoleSWO(uint32_t port, uint32_t baudrate) {
  SystemCoreClockUpdate();
  uint32_t clkSrcFreq = SystemCoreClock;

  DbgConsole_Init(port, baudrate, kSerialPort_Swo, clkSrcFreq);
}

#if 0
/* Init board hardware. */
/* set BOD VBAT level to 1.65V */
POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

/* attach 12 MHz clock to FLEXCOMM0 (debug console) */
CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
CLOCK_AttachClk(kTRACE_DIV_to_TRACE); /*!< Switch TRACE to TRACE_DIV */

BOARD_InitBootPins();
BOARD_BootClockFROHF96M();
#if 1
CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 2U, false);          /* Set AHBCLKDIV divider to value 2 */
CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 2U, false);     /* Set ARMTRCLKDIV divider to value 2 */

//BOARD_InitDebugConsole();
BOARD_InitDebugConsoleSWO(McuSWO_CONFIG_TERMINAL_CHANNEL, McuSWO_CONFIG_SPEED_BAUD);
#endif
PL_Init();
#endif

int main(void) {
#if 1 /* working */
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

  CLOCK_AttachClk(kTRACE_DIV_to_TRACE); /*!< Switch TRACE to TRACE_DIV */

  BOARD_InitBootPins();
  BOARD_BootClockFROHF96M();
  CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 2U, false);          /* Set AHBCLKDIV divider to value 2 */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 2U, false);     /* Set ARMTRCLKDIV divider to value 2 */

  BOARD_InitDebugConsoleSWO(McuSWO_CONFIG_TERMINAL_CHANNEL, McuSWO_CONFIG_SPEED_BAUD);
#endif
  for(;;) {
    //printf("swo hello!\n");
    McuSWO_SendStr("test\n");
    McuWait_Waitms(1000);
  }
}
