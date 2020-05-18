/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
/* library modules */
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuRB.h"
#include "McuCriticalSection.h"
#include "McuRTT.h"
#include "McuSystemView.h"
/* application modules */
#include "leds.h"

void PL_Init(void) {
  /* clocking */
  CLOCK_EnableClock(kCLOCK_PortA); /* used by leds */
  CLOCK_EnableClock(kCLOCK_PortD); /* used by leds */

  /* library modules */
  McuLib_Init();
  McuWait_Init();
  McuUtility_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTOS_Init();
  McuRTT_Init();
  if (configUSE_SEGGER_SYSTEM_VIEWER_HOOKS) {
    McuSystemView_Init();
  }
  McuGenericI2C_Init();

  /* application modules */
  LEDS_Init();
}
