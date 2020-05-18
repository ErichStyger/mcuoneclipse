/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
/* library modules */
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuRB.h"
#include "McuCriticalSection.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuArmTools.h"
/* application modules */
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SD_CARD
  #include "McuFatFS.h"
#endif

void PL_Init(void) {
  /* clocking */
  CLOCK_EnableClock(kCLOCK_PortA); /* used by leds */
  CLOCK_EnableClock(kCLOCK_PortD); /* used by leds */

  /* library modules */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
  if (configUSE_SEGGER_SYSTEM_VIEWER_HOOKS) {
    McuSystemView_Init();
  }

  /* application modules */
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  LEDS_Init();
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
#endif
}
