/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuRTT.h"
#include "McuShellUart.h"
/* SDK */
#include "fsl_gpio.h"
/* application modules: */
#include "leds.h"
#include "buttons.h"
#include "Shell.h"

void PL_Init(void) {
  /* SDK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0: used for push buttons */
  GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1: used for LEDs */

  /* McuLib modules: */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();
  McuShellUart_Init();

  /* application modules: */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
}
