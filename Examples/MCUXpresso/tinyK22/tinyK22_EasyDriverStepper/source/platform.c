/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuCriticalSection.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuXFormat.h"
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#include "McuA3967.h"
#include "stepper.h"

void PL_Init(void) {
//  InitPins(); /* do all the pin muxing */

  /* initialize McuLib modules */
  McuLib_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuWait_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
  McuXFormat_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();

  /* initialize my own modules */
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  LEDS_Init();
  McuA3967_Init();
  STEPPER_Init();
}

void PL_Deinit(void) {
  /*! \todo */
}
