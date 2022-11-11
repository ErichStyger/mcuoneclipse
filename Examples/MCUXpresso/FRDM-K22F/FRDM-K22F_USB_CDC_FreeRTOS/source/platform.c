/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuRB.h"
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuRTT.h"
  #include "McuSystemView.h"
#endif

void PL_Init(void) {
  McuLib_Init();
  McuRTOS_Init();
  McuRB_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuRTT_Init();
  McuSystemView_Init();
#endif
#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART, because this changes the clock settings! */
#endif
}


