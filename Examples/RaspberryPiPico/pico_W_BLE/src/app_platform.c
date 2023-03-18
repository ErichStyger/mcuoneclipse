/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if 1 || PL_CONFIG_USE_USB_CDC
  #include "pico/stdlib.h"
#endif
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "McuHardFault.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#include "McuLog.h"
#include "Shell.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if McuLog_CONFIG_IS_ENABLED
  #include "McuLog.h"
#endif
#if PL_CONFIG_USE_WIFI
  #include "PicoWiFi.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "myBLE.h"
#endif

/* \todo need to have it globally defined, as not present anywhere else */
uint32_t SystemCoreClock = 120000000;

void PL_Init(void) {
#if PL_CONFIG_USE_USB_CDC
  stdio_init_all(); /* needed for USB CDC, but problems with debugger?? */
#endif
  McuLib_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
  McuTimeDate_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
#if McuLog_CONFIG_IS_ENABLED
  McuLog_Init();
#endif
  McuWait_Init();
  McuArmTools_Init();
  McuUtility_Init();
  McuHardFault_Init();
  SHELL_Init();
#if PL_CONFIG_USE_WIFI
  PicoWiFi_Init();
#endif
#if PL_CONFIG_USE_BLE
  BLE_Init();
#endif
}

