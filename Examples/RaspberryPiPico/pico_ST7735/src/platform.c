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
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if PL_CONFIG_USE_DISPLAY_ST7735
  #include "McuSPI.h"
  #include "McuST7735.h"
#endif

void PL_Init(void) {
  McuLib_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_WIFI
  PicoWiFi_Init();
#endif
#if PL_CONFIG_USE_DISPLAY_ST7735
  McuSPI_Init();
  McuST7735_Init();
#endif
}
