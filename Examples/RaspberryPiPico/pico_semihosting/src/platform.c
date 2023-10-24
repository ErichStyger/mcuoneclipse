/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#if PL_CONFIG_USE_WIFI && PL_CONFIG_USE_PICO_W
  #include "PicoWiFi.h"
  #include "pico/cyw43_arch.h" /* must be first, otherwise conflict with lwIP ERR_OK */
#elif PL_CONFIG_USE_WIFI && McuLib_CONFIG_CPU_IS_ESP32
  #include "WiFi.h"
#endif

#if McuLib_CONFIG_CPU_IS_ESP32
	#include "esp32_mac.h"
	#include "nvs_flash.h"
#endif

#if PL_CONFIG_USE_BLINKY
  #include "blinky.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_BUTTONS
  #include "McuButton.h"
  #include "McuDebounce.h"
  #include "buttons.h"
  #include "debounce.h"
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  #include "udp_client.h"
#endif
#if PL_CONFIG_USE_UDP_SERVER
  #include "udp_server.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "McuFlash.h"
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "MinIni/McuMinINI.h"
#endif
#if PL_CONFIG_USE_PING
  #include "ping_shell.h"
#endif
#if PL_CONFIG_USE_SNTP_TIME
  #include "sntp_time.h"
#endif
#if PL_CONFIG_USE_TIME_DATE
  #include "McuTimeDate.h"
  #include "timer.h"
#endif
#if PL_CONFIG_USE_ROBO_REMOTE
  #include "robot.h"
#endif
#if PL_CONFIG_USE_CHALLENGE
  #include "challenge.h"
#endif
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuXFormat.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdio_usb.h"
#endif
#if PL_CONFIG_USE_UART
  #include "pico/stdio_uart.h"
#endif
#if PL_CONFIG_USE_SEMIHOSTING
  #include "pico/stdio_semihosting.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SPI
  #include "McuSPI.h"
#endif
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericI2C.h"
  #include "McuGenericSWI2C.h"
  #include "McuI2cLib.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "McuSSD1306.h"
  #include "oled.h"
#endif
#if PL_CONFIG_USE_SENSOR
  #include "sensor.h"
#endif
#if McuUart485_CONFIG_USE_RS_485
  #include "McuUart485.h"
#endif
#if PL_CONFIG_USE_RS485_SHELL
  #include "rs485.h"
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  #include "tests.h"
#endif
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"
  #include "gcov_test.h"
#endif
#if PL_CONFIG_USE_LEDS
  #include "leds.h"
#endif
#include "McuHardFault.h"
#include "application.h"
#include "hardware/timer.h"

#if McuLib_CONFIG_CPU_IS_RPxxxx
  uint32_t SystemCoreClock = 120000000; /* use clock_get_hz() or SYS_CLK_KHZ */
#elif McuLib_CONFIG_CPU_IS_ESP32
  uint32_t SystemCoreClock = CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ*1000000; /* equivalent to ARM CMSIS core clock frequency */
#endif

void PL_Init(void) {
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
#endif
#if PL_CONFIG_USE_GCOV
  gcov_init();  /* initialize library */
  //gcov_check();
  //gcov_test(3);
#endif
#if PL_CONFIG_USE_UART
  stdio_uart_init();
#endif
#if PL_CONFIG_USE_USB_CDC
  if (!stdio_usb_init()) {
    for(;;) { /* failed initializing USB */} // GCOVR_EXCL_LINE
  }
#endif
#if PL_CONFIG_USE_SEMIHOSTING
  stdio_semihosting_init();
  stdio_set_translate_crlf(&stdio_semihosting, false);
#endif
#if 1 /* workaround for CMSIS-DAP, see https://github.com/raspberrypi/pico-sdk/issues/1152 */
  timer_hw->dbgpause = 0;
#endif
  McuLib_Init();
  McuHardFault_Init();
  McuWait_Init();
#if PL_CONFIG_USE_PICO_W
  McuWait_Waitms(50); /* need to wait some time, otherwise cyw43_arch_init() might hang. */
#endif
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuLog_Init();
  McuUtility_Init();
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_TIME_DATE
  McuTimeDate_Init();
  TMR_Init();
#endif
#if PL_CONFIG_USE_LEDS
  Leds_Init();
#endif
#if PL_CONFIG_USE_BLINKY
  Blinky_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  McuBtn_Init();
  BTN_Init();
  McuDbnc_Init();
  Debounce_Init();
#endif
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_WIFI && McuLib_CONFIG_CPU_IS_ESP32
  ESP_ERROR_CHECK(nvs_flash_init()); /* need to call this before using any WiFi functions */
  ESP32_MacInit();
  WiFi_Init();
#elif PL_CONFIG_USE_WIFI && McuLib_CONFIG_CPU_IS_RPxxxx
  PicoWiFi_Init();
#endif

#if PL_CONFIG_USE_UDP_SERVER
  UDP_Server_Init();
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  UDP_Client_Init();
#endif
#if PL_CONFIG_USE_PING
  PING_Init();
#endif
#if PL_CONFIG_USE_SNTP_TIME
  SNTP_Init();
#endif
#if PL_CONFIG_USE_SPI
  McuSPI_Init();
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
#if PL_CONFIG_USE_SHELL
  McuXFormat_Init();
  McuShell_Init();
  SHELL_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
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
  OLED_Init();
#endif
#if PL_CONFIG_USE_SENSOR
  Sensor_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_Init();
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)McuMinINI_CONFIG_FLASH_NVM_ADDR_START, 1*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE);
#endif
#if PL_CONFIG_USE_RS485
  RS485_Init();
#endif
#if PL_CONFIG_USE_ROBO_REMOTE
  ROBOT_Init();
#endif
#if PL_CONFIG_USE_CHALLENGE
  Challenge_Init();
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  Tests_Init();
#endif
  App_Init();
}
