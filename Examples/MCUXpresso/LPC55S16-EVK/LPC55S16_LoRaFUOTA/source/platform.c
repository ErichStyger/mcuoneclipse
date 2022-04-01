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
#include "McuFlash.h"
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
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_I2C_SPY
  #include "McuI2CSpy.h"
#endif
#if PL_CONFIG_USE_RTC
  #include "McuTimeDate.h"
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  #include "McuEE24.h"
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  #include "McuExtRTC.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#endif
#if PL_CONFIG_USE_LOW_POWER
  #include "LowPower.h"
#endif
#if PL_CONFIG_USE_ESP32_UART
  #include "ESP32_Uart.h"
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
	#include "W25Q128.h"
#endif
#include "application.h"

void PL_Init(void) {


  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons, plus I2C */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

 //
  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTT_Init();
  McuLog_Init();


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

#if PL_CONFIG_USE_EXT_I2C_RTC
  McuExtRTC_Init();
#endif

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  //McuLog_Init();
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
  McuShell_Init();
  McuTimeDate_Init();
  McuDbnc_Init();

#if PL_CONFIG_USE_NVMC
  //NVMC_Init();
#endif
#if PL_CONFIG_INIT_SWO
  /*!< Switch TRACE to TRACE_DIV */
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE); /* needed for SWO */
  McuSWO_Init(SystemCoreClock, McuSWO_CONFIG_SPEED_BAUD); /* if initialization is not done by the debugger, need to do it manually here */
  McuSWO_ChangeSpeed(McuSWO_CONFIG_SPEED_BAUD); /* execute again if J-Link has changed speed */
#endif
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE);
  if (!McuFlash_IsAccessible((const void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)) {
    McuLog_info("Flash for EEPROM emulation is not accessible, initializing memory ...");
    if (McuFlash_Erase((void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)!=ERR_OK) {
      McuLog_fatal("Erasing flash memory failed");
      for(;;) {}
    }
  }
  //APP_Init();
  W25_Init();
}
