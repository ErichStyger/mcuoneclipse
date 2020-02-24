/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuCriticalSection.h"
#include "McuLED.h"
#include "leds.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuPercepio.h"
#include "LowPower.h"

void PL_Init(void) {
  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuUtility_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
#endif
  McuGPIO_Init();
  McuLED_Init();

  /* initialize application modules */
  LEDS_Init();
  LP_Init();
}

void PL_Deinit(void) {
  /*! \todo */
}
