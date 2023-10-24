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
#include "McuUtility.h"
#include "McuLog.h"
#include "McuXFormat.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdio_usb.h"
#endif
#if PL_CONFIG_USE_UART
  #include "pico/stdio_uart.h"
#endif
#if PL_CONFIG_USE_SEMIHOSTING
  #include "pico/stdio_semihosting.h"
#endif
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#include "McuHardFault.h"
#include "application.h"
#include "leds.h"
#include "hardware/timer.h"

#if McuLib_CONFIG_CPU_IS_RPxxxx
  uint32_t SystemCoreClock = 120000000; /* use clock_get_hz() or SYS_CLK_KHZ */
#endif

void PL_Init(void) {
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
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
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_LEDS
  Leds_Init();
#endif
  App_Init();
}
