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
#include "McuGenericI2C.h"
#include "McuI2CSpy.h"
#include "McuTimeDate.h"

/* SDK */
#include "fsl_gpio.h"
/* application modules: */
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#include "i2clib.h"

void PL_Init(void) {
  /* SDK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0: used for push buttons and I2C */
  GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1: used for LEDs */

  /* McuLib modules: */
  McuLib_Init();
  McuRTOS_Init();
  McuGenericI2C_Init();
#if PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#else
  McuGenericSWI2C_Init();
#endif
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();
  McuShellUart_Init();
  McuI2CSpy_Init();
  McuTimeDate_Init();

  /* application modules: */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
}
