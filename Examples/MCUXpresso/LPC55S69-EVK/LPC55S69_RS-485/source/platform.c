/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif

void PL_Init(void) {
  McuLib_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTOS_Init();
  LEDS_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
}
