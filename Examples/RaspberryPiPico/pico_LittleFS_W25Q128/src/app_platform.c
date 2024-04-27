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
#include "Shell.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
  #include "ws2812.h"
#endif
#if PL_CONFIG_USE_LED_DEMO_APP
  #include "neoApp.h"
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  #include "neoCounter.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericSWI2C.h"
  #include "McuGenericI2C.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "McuSSD1306.h"
  #include "oled.h"
#endif
#if PL_CONFIG_USE_BUTTONS
  #include "McuButton.h"
  #include "buttons.h"
  #include "debounce.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "McuMinINI.h"
#endif
#if PL_CONFIG_USE_ROAD
  #include "road.h"
#endif
#if PL_CONFIG_USE_ADC
  #include "analog.h"
#endif
#if PL_CONFIG_USE_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
#endif
#if McuLog_CONFIG_IS_ENABLED
  #include "McuLog.h"
#endif
#if PL_CONFIG_USE_PICO_W
  #include "PicoWiFi.h"
#endif
#if PL_CONFIG_USE_EXT_FLASH
  #include "McuW25Q128.h"
  #include "McuSPI.h"
#endif

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
#if PL_CONFIG_USE_NEO_PIXEL_HW
  WS2812_Init();
  NEO_Init();
#endif
#if PL_CONFIG_USE_LED_DEMO_APP
  NeoApp_Init();
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  NeoCounter_Init();
#endif
#if PL_CONFIG_USE_I2C
  #if CONFIG_USE_HW_I2C
  #error "nyi"
  McuGenericLib_Init();
  #else
  McuGenericSWI2C_Init();
  #endif
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_OLED
  //McuSSD1306_Init(); /* done in OledTask()! */
  OLED_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  McuBtn_Init();
  BTN_Init();
  Debounce_Init();
#endif
#if PL_CONFIG_USE_MINI && McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_FLASH_FS
  McuFlash_Init();
  McuFlash_RegisterMemory((void*)McuMinINI_CONFIG_FLASH_NVM_ADDR_START, McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE);
#endif
#if PL_CONFIG_USE_MINI
  McuMinINI_Init();
#endif

#if PL_CONFIG_USE_ROAD
  Road_Init();
#endif
#if PL_CONFIG_USE_ADC
  Analog_Init();
#endif
#if PL_CONFIG_USE_PICO_W
  PicoWiFi_Init();
#endif
#if PL_CONFIG_USE_EXT_FLASH
  McuSPI_Init();
  McuW25_Init();
#endif
#if PL_CONFIG_USE_LITTLE_FS
  McuLFS_Init();
#endif
}

