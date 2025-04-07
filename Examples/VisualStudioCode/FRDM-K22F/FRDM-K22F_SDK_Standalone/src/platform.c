/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuXFormat.h"
#include "McuFlash.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"
  #include "shell.h"
#endif
#include "app_blinky.h"
#include "led.h"

void PL_Init(void) { 
  __disable_irq();
  McuWait_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init(); /* UART of tinyK22 to K20 (debugger) */
#endif
  McuLog_Init();
#if PL_CONFIG_USE_RTT && !PL_CONFIG_USE_SHELL_UART
  McuLog_set_console(McuRTT_GetStdio(), 0);
#elif PL_CONFIG_USE_SHELL_UART && !PL_CONFIG_USE_RTT
  McuLog_set_console(&McuShellUart_stdio, 0);
#elif PL_CONFIG_USE_SHELL_UART && PL_CONFIG_USE_RTT
  McuLog_set_console(McuRTT_GetStdio(), 0);
  McuLog_set_console(&McuShellUart_stdio, 1);
#endif
#if PL_CONFIG_USE_SHELL
  McuShell_Init();
  #if PL_CONFIG_USE_ARES_BLINKY
    Shell_Init();
  #endif
#endif
  McuRTOS_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuFlash_Init();
  McuFlash_RegisterMemory(0, 0x400);
  McuUtility_Init();
  Led_Init();

  /* application parts */
  App_BlinkyInit();
}
