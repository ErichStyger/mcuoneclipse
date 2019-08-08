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
#include "McuEE24.h"
#include "McuExtRTC.h"

/* SDK */
#include "fsl_gpio.h"
/* application modules: */
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#include "i2clib.h"
#include "McuULN2003.h"
#include "stepper.h"

void PL_InitFromTask(void) {
  (void)McuTimeDate_Init(); /* uses I2C */
}

void PL_Init(void) {
  /* SDK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0: used for push buttons and I2C */
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

  McuGenericI2C_Init();
  McuI2CSpy_Init();
#if PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#else
  McuGenericSWI2C_Init();
#endif
#if PL_HAS_EXT_I2C_RTC
  McuExtRTC_Init();
#endif
#if PL_HAS_EXT_EEPROM
  McuEE24_Init();
#endif

  /* application modules: */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
  McuULN2003_Init();
  STEPPER_Init();
}
