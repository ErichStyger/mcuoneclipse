/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "leds.h"
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  #include "McuSemihost.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons, plus I2C */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
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
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init();
#endif

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();

  LEDS_Init();
}
