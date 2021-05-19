/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#if PL_CONFIG_USE_SD_CARD
  #include "McuFatFS.h"
  #include "McuFatFS_CardPins.h"
  #include "disk.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuLog_Init();
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
  McuShell_Init();
  McuTimeDate_Init();
  McuDbnc_Init();

  /* user modules */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
  McuFatFS_CardPinInit();
  DISK_Init();
#endif
}
