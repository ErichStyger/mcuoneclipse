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
#include "McuSWO.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
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
  #include "McuI2cLib.h"
  #include "McuGenericI2C.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "McuSSD1306.h"
  #include "MyGui.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_HAS_HW_RTC
  #include "McuExtRTC.h"
#endif
#if PL_CONFIG_HAS_SHT31
  #include "McuSHT31.h"
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  #include "McuSPI.h"
  #include "littleFS/McuLittleFS.h"
  #include "McuW25Q128.h"
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  #include "McuSemihost.h"
#endif
#include "McuFlash.h"

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons, plus I2C */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTT_Init();
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init();
  // McuSemiHost_Test(); /* run it to test it */
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuLog_Init();
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
  McuShell_Init();
  McuDbnc_Init();
#if !McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  McuTimeDate_Init(); /* if using external RTC it uses I2C, need to do this from clock task */
#endif
#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  McuExtRTC_Init();
#endif
  /* user modules */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_Init();
  McuFatFS_CardPinInit();
  DISK_Init();
#endif

#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  #if PL_CONFIG_USE_HW_I2C
  McuI2cLib_Init();
  #else
  //CLOCK_EnableClock(kCLOCK_PortA);  /* need PORTA for I2C Bitbanging */
  McuGenericSWI2C_Init();
  #endif
#endif /* PL_CONFIG_USE_I2C */
#if PL_CONFIG_USE_OLED
  McuSSD1306_Init();
  MyGui_Init();
#endif
#if PL_CONFIG_HAS_SHT31
  McuSHT31_Init();
#endif
#if McuFlash_CONFIG_IS_ENABLED
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)McuFlash_CONFIG_MEM_START, McuFlash_CONFIG_NOF_BLOCKS*McuFlash_CONFIG_FLASH_BLOCK_SIZE);
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  #if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
  McuSPI_Init();
  McuW25_Init();
  #endif
  McuLFS_Init();
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
#endif
#if PL_CONFIG_INIT_SWO
  /*!< Switch TRACE to TRACE_DIV */
  McuSWO_Init(); /* if initialization is not done by the debugger, need to do it manually here */
  McuSWO_ChangeSpeed(McuSWO_CONFIG_SPEED_BAUD); /* execute again if J-Link has changed speed */
#elif PL_CONFIG_USE_SWO
  /* muxing of the SWO pin needs to be done in BOARD_InitBootPins()! */
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);
#endif
}
