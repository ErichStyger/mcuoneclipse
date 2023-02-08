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
#if PL_CONFIG_USE_LED_COUNTER_APP
  #include "neoCounter.h"
#endif
#if PL_CONFIG_USE_LIGHTS
  #include "lights.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericSWI2C.h"
  #include "McuGenericI2C.h"
  #include "McuI2cLib.h"
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
  #include "minIni/McuFlash.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
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
#if PL_CONFIG_USE_NTP_CLIENT
  #include "ntp_client.h"
#endif
#if PL_CONFIG_USE_EXT_FLASH
  #include "McuW25Q128.h"
  #include "McuSPI.h"
#endif
#if PL_CONFIG_USE_UDP_SERVER
  #include "udp_server.h"
#endif
#if PL_CONFIG_USE_MQTT_CLIENT
  #include "mqtt_client.h"
#endif
#if McuUart485_CONFIG_USE_RS_485
  #include "McuUart485.h"
#endif
#if PL_CONFIG_USE_RS485_SHELL
  #include "rs485.h"
#endif
#if McuModbus_CONFIG_IS_ENABLED
  #include "Modbus/McuModbus.h"
  #include "Modbus/McuHeidelberg.h"
#endif
#if PL_CONFIG_USE_POWER
  #include "power.h"
#endif
#if PL_CONFIG_USE_GUI
  #include "gui.h"
#endif

/* \todo need to have it globally defined, as not present anywhere else */
uint32_t SystemCoreClock = 120000000;

void McuGenericI2C_CONFIG_ON_ERROR_EVENT(void) {
}

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
#if PL_CONFIG_USE_LIGHTS
  Lights_Init();
#endif
#if PL_CONFIG_USE_I2C
  #if CONFIG_USE_HW_I2C
    McuI2cLib_Init();
  #else
    McuGenericSWI2C_Init();
  #endif
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_OLED
  /* McuSSD1306_Init(); */ /* done in OledTask()! */
  OLED_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  McuBtn_Init();
  BTN_Init();
  Debounce_Init();
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  NeoCounter_Init();
#endif
#if PL_CONFIG_USE_MINI
  McuFlash_Init();
  McuFlash_RegisterMemory((void*)McuMinINI_CONFIG_FLASH_NVM_ADDR_START, McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE);
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_PICO_W
  PicoWiFi_Init();
#endif
#if PL_CONFIG_USE_NTP_CLIENT
  NtpClient_Init();
#endif
#if PL_CONFIG_USE_UDP_SERVER
  UdpServer_Init();
#endif
#if PL_CONFIG_USE_MQTT_CLIENT
  MqttClient_Init();
#endif
#if PL_CONFIG_USE_EXT_FLASH
  McuSPI_Init();
  McuW25_Init();
#endif
#if PL_CONFIG_USE_LITTLE_FS
  McuLFS_Init();
#endif
#if PL_CONFIG_USE_POWER
  Power_Init();
#endif
#if PL_CONFIG_USE_GUI
  GUI_Init();
#endif
#if PL_CONFIG_USE_RS485 && McuUart485_CONFIG_USE_RS_485
  McuUart485_Init();
#endif
#if PL_CONFIG_USE_RS485_SHELL
  RS485_Init();
#endif
#if PL_CONFIG_USE_RS485 && McuModbus_CONFIG_IS_ENABLED
  McuModbus_Init();
  McuHeidelberg_Init();
#endif
}
