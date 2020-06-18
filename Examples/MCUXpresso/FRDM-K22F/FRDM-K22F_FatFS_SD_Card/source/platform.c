/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
/* library modules */
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuRB.h"
#include "McuCriticalSection.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuArmTools.h"
#include "McuTimeout.h"
#include "McuLog.h"
#include "disk.h"
#if PL_CONFIG_USE_EXT_I2C_RTC
  #include "McuExtRTC.h"
  #include "i2clib.h"
#endif

/* application modulMcues */
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_SD_CARD
  #include "McuFatFS.h"
  #include "fatfs_sdcard.h"
#endif
#include "McuTimeDate.h"

void PL_InitFromTask(void) {
  McuTimeDate_Init();
}

void PL_Init(void) {
  /* clocking */
  CLOCK_EnableClock(kCLOCK_PortA); /* used by leds */
  CLOCK_EnableClock(kCLOCK_PortB); /* used by sd card detect and I2C */
  CLOCK_EnableClock(kCLOCK_PortD); /* used by leds */

  /* library modules */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuTimeout_Init();
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_I2C && PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#elif PL_CONFIG_USE_I2C
  McuGenericSWI2C_Init();
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  McuExtRTC_Init();
#endif
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
  if (configUSE_SEGGER_SYSTEM_VIEWER_HOOKS) {
    McuSystemView_Init();
  }
#if PL_CONFIG_USE_LOGGING
  McuLog_Init();
#endif

  /* application modules */
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  LEDS_Init();
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
  FatFS_SdCardInit();
#endif
#if PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD
  DISK_Init();
#endif
}
