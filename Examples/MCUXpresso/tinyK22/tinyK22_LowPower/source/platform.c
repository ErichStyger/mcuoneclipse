/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Platform.h"
#include "McuLib.h"
#include "McuArmTools.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuCriticalSection.h"
#include "McuLED.h"
#include "leds.h"
#include "McuRTT.h"
#include "McuPercepio.h"
#include "LowPower.h"

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_PortD); /* FRDM-K22 has LED on port D */

  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
  McuUtility_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
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
