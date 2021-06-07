/**
 * \file
 * \brief Implementation Platform initialization of the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the hardware dependent initialization of board and drivers.
 */

#include "Platform.h"
#include "McuWait.h"
#include "McuRTT.h"
#include "McuUtility.h"
#if PL_CONFIG_USE_FREERTOS
  #include "McuRTOS.h"
  #include "RTOS.h"
#endif
#if PL_CONFIG_USE_SEGGER_SYSVIEW
  #include "McuSystemView.h"
#endif
#include "Board.h"
#include "McuShell.h"


void PL_Init(void) {
#if PL_CONFIG_USE_FREERTOS
  McuRTOS_Init(); /* must be first to disable the interrupts */
#endif
 // BOARD_Init();

  McuWait_Init();
  McuRTT_Init();
  McuUtility_Init();
 // McuShell_SetStdio(&McuRTT_stdio); /* use RTT for standard I/O */
#if PL_CONFIG_USE_SEGGER_SYSVIEW
  McuSystemView_Init();
#endif
#if PL_CONFIG_USE_FREERTOS
  RTOS_Init();
#endif
}
