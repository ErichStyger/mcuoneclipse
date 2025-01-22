/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_WIFI
  #include "PicoWiFi.h"
#elif PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h" /* must be first, otherwise conflict with lwIP ERR_OK */
#endif
#if PL_CONFIG_USE_USB_CDC
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
#include "McuShellCdcDevice.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#include "McuLog.h"
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if McuLog_CONFIG_IS_ENABLED
  #include "McuLog.h"
#endif
#if PL_CONFIG_USE_EXT_RTC
  #include "extRTC.h"
#endif
#if PL_CONFIG_USE_SPI
  #include "McuSPI.h"
#endif
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif
#include "leds.h"
#include "power.h"
#include "McuI2cLib.h"
#include "McuGenericI2C.h"

void PL_Init(void) {
  McuLib_Init();
#if PL_CONFIG_USE_TUD_CDC
  McuShellCdcDevice_Init();
  McuShellCdcDevice_SetBufferRxCharCallback(McuShellCdcDevice_QueueChar);
#endif
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
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_I2C
  #if CONFIG_USE_HW_I2C
    McuI2cLib_Init();
  #else
    McuGenericSWI2C_Init();
  #endif
  McuGenericI2C_Init();
#endif
#if 0 && PL_CONFIG_USE_BUTTONS
  McuBtn_Init();
  BTN_Init();
  Debounce_Init();
#endif
#if PL_CONFIG_USE_EXT_RTC
  ExtRTC_Init();
#endif
#if PL_CONFIG_USE_POWER
  Power_Init();
#endif
#if PL_CONFIG_USE_SPI
  McuSPI_Init();
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
  Leds_Init();
}
