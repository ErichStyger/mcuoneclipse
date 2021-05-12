/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuCriticalSection.h"
#include "McuLED.h"
#include "McuRTT.h"
#include "McuShell.h"
#include "McuShellUart.h"
#include "McuSystemView.h"
#include "McuPercepio.h"
#include "McuTimeDate.h"
#include "McuLog.h"
#include "leds.h"
#include "Shell.h"
#include "myTimer.h"
#include "McuFatFS.h"
#include "fatfs_sdcard.h"
#include "disk.h"

void PL_Init(void) {
  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
  McuRTT_Init();
  McuRTOS_Init();
  McuUtility_Init();
  McuLog_Init();
  McuArmTools_Init();
  McuTimeDate_Init();
  McuCriticalSection_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  // McuPercepio_Startup(); /* done in McuRTOS_Init() */
  //vTraceEnable(TRC_START);
#endif
  McuGPIO_Init();
  McuLED_Init();
  McuShellUart_Init();

  /* initialize my own modules */
  LEDS_Init();
  SHELL_Init();
  MyTimer_Init();
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
  FatFS_SdCardInit();
  DISK_Init();
#endif
}

void PL_Deinit(void) {
  /*! \todo */
}
