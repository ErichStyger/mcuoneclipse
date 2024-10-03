/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdio_usb.h"
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
#if McuSemihost_CONFIG_IS_ENABLED
  #include "McuSemihost.h"
#endif
#if PL_CONFIG_USE_LEDS
  #include "leds.h"
#endif
#if PL_CONFIG_USE_GCOV
  #include "McuCoverage.h"
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  #include "tests/tests.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#include "McuHardFault.h"
#include "application.h"
#include "hardware/timer.h"

void PL_Init(void) {
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
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
#if PL_CONFIG_USE_GCOV
  McuCoverage_Init();  /* initialize library */
  //McuCoverage_Check(); /* testing file I/O */
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
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
  McuLog_Init();
#if PL_CONFIG_USE_RTT
  McuLog_set_console(McuRTT_GetStdio(), 0);
#endif
  McuUtility_Init();
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_LEDS
  Leds_Init();
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  Tests_Init();
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init();
#endif
#if PL_CONFIG_USE_SHELL
  McuXFormat_Init();
  McuShell_Init();
  SHELL_Init();
#endif
  App_Init();
}
