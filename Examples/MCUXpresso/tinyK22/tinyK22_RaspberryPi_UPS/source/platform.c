/*
 * platform.c
 *
 *  Created on: 20.04.2019
 *      Author: Erich Styger
 */
#include "Platform.h"
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
#include "Keys.h"
#include "KeyDebounce.h"
#include "Trigger.h"
#include "Event.h"
#include "Shell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuXFormat.h"
#include "Sensor.h"
#include "toaster.h"
#include "RaspyUART.h"

void PL_Init(void) {
  InitPins(); /* do all the pin muxing */

  /* initialize McuLib modules */
  McuLib_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuWait_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
  McuRB_Init();
  McuXFormat_Init();
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  McuGenericSWI2C_Init();
#endif
#if PL_CONFIG_USE_OLED
  McuSSD1306_Init();
#endif
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();

  /* initialize my own modules */
  KEY_Init();
  KEYDBNC_Init();
  TRG_Init();
  EVNT_Init();
  LEDS_Init();
#if PL_CONFIG_USE_SHUTDOWN
  SHUTDOWN_Init();
#endif
#if PL_CONFIG_USE_OLED
  OLED_Init(); /* initializes the needed McuLib components for the OLED */
#endif
#if PL_CONFIG_USE_LVGL
  GUI_Init();
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
}

void PL_Deinit(void) {
  /* \todo */
}
