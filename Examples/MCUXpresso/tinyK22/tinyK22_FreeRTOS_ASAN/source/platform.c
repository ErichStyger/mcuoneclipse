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
#include "McuTimeDate.h"
#include "McuASAN.h"
#include "McuLog.h"

void PL_Init(void) {
  /* initialize McuLib modules */
  McuLib_Init();
  McuASAN_Init(); /* initialize ASAN */
  McuWait_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuArmTools_Init();
  McuTimeDate_Init();
  McuCriticalSection_Init();
  McuLog_Init();
  McuLog_set_console(&McuRTT_stdio, 0);
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
#endif
  McuGPIO_Init();
  McuLED_Init();

  /* initialize my own modules */
  LEDS_Init();
}

void PL_Deinit(void) {
  /*! \todo */
}
