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
#include "i2clib.h"
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
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
  I2CLIB_Init();
  #else
  McuGenericSWI2C_Init();
  #endif
  #if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_Init();
  #endif
#endif
#if PL_CONFIG_USE_OLED
  //McuWait_Waitms(100); /* display needs some time to power up */
  //McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
#endif
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
  McuBtn_Init();
  McuDbnc_Init();

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
#if PL_CONFIG_USE_OLED
  //OLED_Init(); /* initializes the needed McuLib components for the OLED */
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
  SENSOR_Init();
#if PL_CONFIG_USE_RASPY_UART
  RASPYU_Init();
#endif
#if PL_CONFIG_USE_RASPBERRY
  RGPIO_Init();
#endif
  BTN_Init();
}

void PL_Deinit(void) {
  /*! \todo */
}
