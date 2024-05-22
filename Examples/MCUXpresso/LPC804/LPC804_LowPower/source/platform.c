/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "leds.h"
#include "fsl_iap.h"
#if PL_CONFIG_USE_LOW_POWER
  #include "LowPower.h"
#endif

void PL_Init(void) {
  /* McuLib modules */
  McuLib_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuWait_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  /* application modules */
  LEDS_Init();
#if PL_CONFIG_USE_LOW_POWER
  LP_Init();
#endif
}
