/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
/* library modules */
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuRTT.h"
#include "McuLog.h"
#include "McuShell.h"
#include "McuShellUart.h"
#include "McuArmTools.h"

#include "leds.h"
#include "Shell.h"

/* application modulMcues */
#include "leds.h"

void PL_Init(void) {
  /* clocking */
#if PL_CONFIG_IS_TINY_K22
  CLOCK_EnableClock(kCLOCK_PortC); /* used by blue LED */
#else
  CLOCK_EnableClock(kCLOCK_PortA); /* used by leds */
  CLOCK_EnableClock(kCLOCK_PortB); /* used by sd card detect and I2C */
  CLOCK_EnableClock(kCLOCK_PortD); /* used by leds */
#endif

  /* library modules */
  McuLib_Init();
  #if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
  #endif
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();
  McuLog_Init();
  McuShellUart_Init();
  McuShell_Init();
  McuLog_set_console(McuRTT_GetStdio(), 0);

  /* application modules */
  LEDS_Init();
  SHELL_Init();
}
