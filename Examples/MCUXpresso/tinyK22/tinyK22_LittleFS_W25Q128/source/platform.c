/*
 * Copyright (c) 2021, Erich Styger
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
#include "McuTimeDate.h"
#include "McuLog.h"
#include "McuButton.h"

/* SDK */
#include "fsl_gpio.h"

/* application modules: */
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif

void PL_InitFromTask(void) {
  /* call here things which need interrupts enabled */
  /* the clock time/date gets initialized in the clock task */
}

void PL_Init(void) {
  /* SDK */
  CLOCK_EnableClock(kCLOCK_PortC); /* LED */

  /* McuLib modules */
  McuLog_Init();
  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuArmTools_Init();
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
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
}
