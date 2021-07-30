/*
 * Copyright (c) 2019, Erich Styger
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
#if PL_CONFIG_USE_BUTTON
  #include "buttons.h"
#endif
#include "Shell.h"

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
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
  McuShellUart_Init();

  McuGenericI2C_Init();
#if PL_CONFIG_USE_I2C && PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#elif PL_CONFIG_USE_I2C
  McuGenericSWI2C_Init();
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  McuExtRTC_Init();
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  McuEE24_Init();
#endif
#if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_Init();
#endif

  /* application modules: */
  LEDS_Init();
#if PL_CONFIG_USE_BUTTON
  BTN_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_STEPPER
  McuULN2003_Init();
  STEPPER_Init();
#endif
#if PL_CONFIG_USE_HALL_SENSOR
  MAG_Init();
#endif
}
