/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuTimeout.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif

/* SDK */
#include "fsl_gpio.h"

/* application modules: */
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif

void PL_InitFromTask(void) {
}

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc); /* needed for muxing */
  /* McuLib modules */
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
  McuTimeout_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
#endif

  /* application modules: */
  LEDS_Init();
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
}
