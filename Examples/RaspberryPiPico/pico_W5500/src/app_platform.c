/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif

void PL_Init(void) {
  McuLib_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
}
