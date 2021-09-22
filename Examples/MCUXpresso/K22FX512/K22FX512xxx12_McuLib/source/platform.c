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
#include "McuCriticalSection.h"
#include "McuSystemView.h"
#include "McuI2CSpy.h"
#include "McuShell.h"
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif

void PL_Init(void) {
  /* McuLib modules: */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuCriticalSection_Init();
  McuShell_Init();
#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART, because this changes the clock settings! */
#endif

}
