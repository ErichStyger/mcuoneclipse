/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
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
#include "McuTimeout.h"
#if PL_CONFIG_HAS_NEO_PIXEL
  #include "NeoPixel.h"
  #include "PixelDMA.h"
#endif

void PL_Init(void) {
  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
  McuRTT_Init();
  McuTimeout_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
#endif
  McuGPIO_Init();
  McuLED_Init();

  /* initialize application modules */
  LEDS_Init();
#if PL_CONFIG_HAS_NEO_PIXEL
  PIXDMA_Init();
  NEO_Init();
#endif
}

void PL_Deinit(void) {
  /*! \todo */
}
