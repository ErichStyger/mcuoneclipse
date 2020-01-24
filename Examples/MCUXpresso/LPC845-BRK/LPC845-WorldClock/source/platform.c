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
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericI2C.h"
#endif
#if PL_CONFIG_USE_I2C_SPY
  #include "McuI2CSpy.h"
#endif
#if PL_CONFIG_USE_RTC
  #include "McuTimeDate.h"
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  #include "McuEE24.h"
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  #include "McuExtRTC.h"
#endif
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#endif
#if PL_CONFIG_USE_RS485
  #include "rs485.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_MATRIX
  #include "matrix.h"
#endif

/* SDK */
#include "fsl_gpio.h"

/* application modules: */
#include "leds.h"
#if PL_CONFIG_USE_BUTTON
  #include "buttons.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "i2clib.h"
#endif
#if PL_CONFIG_USE_STEPPER
  #include "stepper.h"
#endif
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif

void PL_InitFromTask(void) {
#if PL_CONFIG_USE_RTC
  (void)McuTimeDate_Init(); /* might use I2C with interrupts */
#endif
}

void PL_Init(void) {
  /* SDK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0 (PIO0_19): used LED */
  GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1, used by motor driver signals */

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
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif

#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_Init();
#endif
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

  /* application modules: */
  LEDS_Init();
#if PL_CONFIG_USE_BUTTON
  BTN_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_X12_STEPPER
  McuX12_017_Init();
#endif
#if PL_CONFIG_USE_STEPPER
  STEPPER_Init();
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  MAG_Init();
#endif
#if PL_CONFIG_USE_RS485
  RS485_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
#endif
#if PL_CONFIG_USE_MATRIX
  MATRIX_Init();
#endif
}
