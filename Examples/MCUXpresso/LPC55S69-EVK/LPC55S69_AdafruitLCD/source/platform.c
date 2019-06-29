/*
 * platform.c
 *
 *  Created on: 20.04.2019
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuCriticalSection.h"
#include "McuRB.h"
#include "McuSSD1306.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuXFormat.h"
#include "McuButton.h"
#include "McuDebounce.h"
#include "leds.h"
#if PL_CONFIG_USE_GUI
  #include "gui.h"
#endif

void PL_Init(void) {
//  InitPins(); /* do all the pin muxing */

  /* initialize McuLib modules */
  McuLib_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuWait_Init();
  McuArmTools_Init();
  McuCriticalSection_Init();
  McuRB_Init();
  McuXFormat_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
  McuBtn_Init();
  McuDbnc_Init();

  /* initialize my own modules */
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  LEDS_Init();
#if PL_CONFIG_USE_GUI
  GUI_Init();
#endif
}

void PL_Deinit(void) {
  /*! \todo */
}
