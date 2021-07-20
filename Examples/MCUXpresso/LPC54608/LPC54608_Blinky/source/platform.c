/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "leds.h"
#if PL_CONFIG_USE_BUTTON
  #include "buttons.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SD_CARD
  #include "McuFatFS.h"
  #include "McuFatFS_CardPins.h"
  #include "disk.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "i2clib.h"
  #include "McuGenericI2C.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "McuSSD1306.h"
  #include "MyGui.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio2); /* for LEDs */
  GPIO_PortInit(GPIO, 2); /* Initialize GPIO  */
  CLOCK_EnableClock(kCLOCK_Gpio3); /* LEDs */
  GPIO_PortInit(GPIO, 3); /* Initialize GPIO */

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
//  McuLog_Init();
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_SHELL
  McuShell_Init();
#endif
  McuTimeDate_Init();
#if PL_CONFIG_USE_BUTTON
  McuDbnc_Init();
#endif

  /* user modules */
  LEDS_Init();
#if PL_CONFIG_USE_BUTTON
  BTN_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
  McuFatFS_CardPinInit();
  DISK_Init();
#endif

#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  #if PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
  #else
  //CLOCK_EnableClock(kCLOCK_PortA);  /* need PORTA for I2C Bitbanging */
  McuGenericSWI2C_Init();
  #endif
#endif /* PL_CONFIG_USE_I2C */
#if PL_CONFIG_USE_OLED
  McuSSD1306_Init();
  MyGui_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
#endif
}
