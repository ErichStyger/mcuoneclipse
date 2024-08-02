/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "initPins.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuCriticalSection.h"
#include "McuRB.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "leds.h"
#include "shutdown.h"
#include "oled.h"
#include "gui.h"
#include "gateway.h"
#include "Shell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuXFormat.h"
#include "Sensor.h"
#include "toaster.h"
#include "RaspyUART.h"
#include "RaspyGPIO.h"
#include "buttons.h"
#include "McuButton.h"
#include "McuDebounce.h"
#include "McuI2CSpy.h"
#include "McuI2cLib.h"
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#elif PL_CONFIG_USE_SHT40
  #include "McuSHT40.h"
#endif

void PL_Init(void) {
  InitPins(); /* do all the pin muxing */

  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
  McuRB_Init();
  McuXFormat_Init();
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  #if PL_CONFIG_USE_HW_I2C
  McuI2cLib_Init();
  #else
  McuGenericSWI2C_Init();
  #endif
  #if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_Init();
  #endif
#endif
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
#if PL_CONFIG_USE_BUTTONS
  McuBtn_Init();
  McuDbnc_Init();
#endif
  /* initialize my own modules */
#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART/Gateway, because this changes the clock settings! */
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  LEDS_Init();
#if PL_CONFIG_USE_SHUTDOWN
  SHUTDOWN_Init();
#endif
#if PL_CONFIG_USE_OLED && !PL_CONFIG_USE_GUI
  OLED_Init(); /* initializes the needed McuLib components for the OLED */
#endif
#if PL_CONFIG_USE_GUI
  GUI_Init(); /* requires interrupts enabled if using HW I2C */
#endif
#if PL_CONFIG_USE_GATEWAY
  GATEWAY_Init();
#endif
#if PL_CONFIG_USE_TOASTER
  TOASTER_Init();
#endif
#if PL_CONFIG_USE_SHT31
  McuSHT31_Init();
#endif
#if PL_CONFIG_USE_SHT40
  McuSHT40_Init();
#endif
  SENSOR_Init(); /* does the SHT31 and SHT40 initialization inside a task */
#if PL_CONFIG_USE_RASPY_UART
  RASPYU_Init();
#endif
#if PL_CONFIG_USE_RASPBERRY
  RGPIO_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  BTN_Init();
#endif
}

void PL_Deinit(void) {
  /*! \todo */
}
