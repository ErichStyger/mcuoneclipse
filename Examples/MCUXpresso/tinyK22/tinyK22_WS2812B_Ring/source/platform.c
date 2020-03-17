/*
 * Copyright (c) 2020, Erich Styger
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
#include "McuTimeout.h"
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
#if PL_CONFIG_USE_X12_STEPPER
  #include "McuX12_017.h"
#endif

/* SDK */
#include "fsl_gpio.h"

/* application modules: */
#if PL_CONFIG_USE_RS485
  #include "rs485.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_MATRIX
  #include "matrix.h"
#endif
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
  #include "i2clibconfig.h"
#endif
#if PL_CONFIG_USE_STEPPER
  #include "stepper.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#if PL_CONFIG_USE_CLOCK
  #include "Clock.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL
  #include "NeoPixel.h"
  #include "PixelDMA.h"
#endif
#include "StepperBoard.h"

void PL_InitFromTask(void) {
#if PL_CONFIG_USE_RTC && PL_CONFIG_USE_HW_I2C
  (void)McuTimeDate_Init(); /* might use I2C with interrupts */
#endif
}

void PL_Init(void) {
  /* SDK */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0 (PIO0_19): used LED */
  GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1, used by motor driver signals */
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #if PL_CONFIG_USE_RS485
  CLOCK_EnableClock(kCLOCK_PortB); /* EN for RS-485 */
  #endif
  #if CONFIG_I2C_USE_PORT_B
  CLOCK_EnableClock(kCLOCK_PortB); /* PTB0, PTB1 for I2C */
  #elif CONFIG_I2C_USE_PORT_E
  CLOCK_EnableClock(kCLOCK_PortE); /* PTE0, PTE1 for I2C */
  #endif
#endif
  /* McuLib modules */
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
  McuTimeout_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
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
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
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
#if PL_CONFIG_USE_WDT
  WDT_Init();
#endif
#if PL_CONFIG_USE_CLOCK
  CLOCK_Init();
#endif
#if PL_CONFIG_USE_NEO_PIXEL
  PIXDMA_Init();
  NEO_Init();
#endif
  STEPBOARD_Init();
}
