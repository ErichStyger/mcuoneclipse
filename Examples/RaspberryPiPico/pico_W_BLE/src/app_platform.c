/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
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
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#include "McuLog.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if McuLog_CONFIG_IS_ENABLED
  #include "McuLog.h"
#endif
#if PL_CONFIG_USE_MCUFLASH
  #include "minIni/McuFlash.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
#endif
#if PL_CONFIG_USE_WIFI
  #include "PicoWiFi.h"
#endif
#if PL_CONFIG_USE_NTP_CLIENT
  #include "ntp_client.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "ble_server.h"
  #include "ble_client.h"
#endif

/* \todo need to have it globally defined, as not present anywhere else */
uint32_t SystemCoreClock = 120000000;

void PL_Init(void) {
#if PL_CONFIG_USE_USB_CDC
  stdio_init_all(); /* needed for USB CDC, but might cause issues while debugging, because USB traffic might stall */
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
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_MCUFLASH
  McuFlash_Init();
  McuFlash_RegisterMemory((void*)McuMinINI_CONFIG_FLASH_NVM_ADDR_START, McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE);
#endif
#if PL_CONFIG_USE_MINI
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_WIFI
  PicoWiFi_Init();
#endif
#if PL_CONFIG_USE_NTP_CLIENT
  NtpClient_Init();
#endif
#if PL_CONFIG_USE_BLE
#if PL_CONFIG_STANDALONE_BLE_CLIENT
  BleClient_Init();
#elif PL_CONFIG_STANDALONE_BLE_SERVER
  BleServer_Init();
#else
  #error"unknown configuration"
#endif
#endif
}
