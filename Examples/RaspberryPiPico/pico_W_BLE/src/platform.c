/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_WIFI
  #include "wifi.h"
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
#if PL_CONFIG_USE_MCUFLASH
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
#endif
#if PL_CONFIG_USE_WIFI
  #include "wifi.h"
#endif
#if McuLog_CONFIG_IS_ENABLED
  #include "McuLog.h"
#endif
#if PL_CONFIG_USE_NTP_CLIENT
  #include "ntp_client.h"
#endif
#if PL_CONFIG_USE_UDP_SERVER
  #include "udp_server.h"
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  #include "udp_client.h"
#endif
#if PL_CONFIG_USE_TCP_SERVER
  #include "tcp_server.h"
#endif
#if PL_CONFIG_USE_TCP_CLIENT
  #include "tcp_client.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "ble_server.h"
  #include "ble_client.h"
#endif

void McuGenericI2C_CONFIG_ON_ERROR_EVENT(void) {
}

#if PL_CONFIG_USE_WATCHDOG
void PL_InitWatchdogReportTable(void) {
  McuWatchdog_InitReportEntry(McuWatchdog_REPORT_ID_TASK_APP, "App", 1000, 70, 120);
  #if PL_CONFIG_USE_GUI
  McuWatchdog_InitReportEntry(McuWatchdog_REPORT_ID_TASK_GUI, "Gui", 1000, 70, 120);
  #endif
  #if PL_CONFIG_USE_SHELL
    McuWatchdog_InitReportEntry(McuWatchdog_REPORT_ID_TASK_SHELL, "Shell", 1000, 70, 120);
  #endif
  #if PL_CONFIG_USE_LIGHTS
    McuWatchdog_InitReportEntry(McuWatchdog_REPORT_ID_TASK_LIGHTS, "Lights", 1000, 70, 120);
  #endif
  #if PL_CONFIG_USE_WIFI
    McuWatchdog_InitReportEntry(McuWatchdog_REPORT_ID_TASK_WIFI, "WiFi", 1000, 70, 120);
  #endif
}
#endif

/* https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c, around line 147
 * change call of pico_get_unique_board_id_string() to the following:  */
#if 0
  #if 1 /* << EST */
      extern void pico_usb_get_unique_board_id_string(char *id_out, uint len);
      pico_usb_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #else
        pico_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #endif
#endif

void pico_usb_get_unique_board_id_string(char *id_out, uint len) {
#if 1 /* original version */
  pico_get_unique_board_id_string(id_out, len); /* default */
#else /* use same USB serial number for all boards, so sharing the same COM interface */
  McuUtility_strcpy(id_out, len, "mySerialNumber");
#endif
}

void PL_Init(void) {
#if PL_CONFIG_USE_WATCHDOG
  PL_InitWatchdogReportTable();
  McuWatchdog_EnableTimer(); /* Enable watchdog timer early, to catch any deadlocks during initialization */
#endif
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
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_Init();
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
#if PL_CONFIG_USE_UDP_SERVER
  UdpServer_Init();
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  UdpClient_Init();
#endif
#if PL_CONFIG_USE_TCP_SERVER
  TcpServer_Init();
#endif
#if PL_CONFIG_USE_TCP_CLIENT
  TcpClient_Init();
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
