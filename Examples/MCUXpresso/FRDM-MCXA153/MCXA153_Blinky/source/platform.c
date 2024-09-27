/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "platform.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuRTT.h"
#include "McuSemihost.h"
#include "McuLog.h"

void PL_Init(void) {
  McuGPIO_Init();
  McuLED_Init();
  McuWait_Init();
  McuLog_Init();
#if PL_CONFIG_USE_SEMIHOSTING
  McuSemiHost_Init();
#endif
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_SEMIHOSTING && !PL_CONFIG_USE_RTT
  McuLog_set_console(McuSemihost_GetStdio(), 0);
#elif !PL_CONFIG_USE_SEMIHOSTING && PL_CONFIG_USE_RTT
  McuLog_set_console(McuRTT_GetStdio(), 0);
#elif McuLog_CONFIG_NOF_CONSOLE_LOGGER==2 && PL_CONFIG_USE_SEMIHOSTING && PL_CONFIG_USE_RTT
  McuLog_set_console(McuRTT_GetStdio(), 0);
  McuLog_set_console(McuSemihost_GetStdio(), 1);
#endif
}
