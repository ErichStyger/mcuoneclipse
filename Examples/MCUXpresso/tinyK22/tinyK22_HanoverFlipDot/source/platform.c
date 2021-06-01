/*
 * Copyright (c) 2021, Erich Styger
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
#include "McuTimeout.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericI2C.h"
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
#include "McuLog.h"
#include "McuButton.h"
#include "flipdot.h"

/* SDK */
#include "fsl_gpio.h"

/* application modules: */
#if PL_CONFIG_USE_RS485
  #include "rs485.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#include "leds.h"
#if PL_CONFIG_HAS_BUTTONS
  #include "buttons.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "i2clib.h"
  #include "i2clibconfig.h"
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#if PL_CONFIG_USE_CLOCK
  #include "Clock.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "bleuart_cmdmode.h"
#endif
#if PL_CONFIG_USE_BLE_MSG
  #include "bleMsg.h"
#endif
#if PL_CONFIG_USE_ESP32
  #include "esp32.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif

void PL_InitFromTask(void) {
  /* call here things which need interrupts enabled */
  /* the clock time/date gets initialized in the clock task */
}

void PL_Init(void) {
  /* SDK */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0 (PIO0_19): used LED */
  GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1, used by motor driver signals */
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #if PL_CONFIG_USE_RS485
  CLOCK_EnableClock(kCLOCK_PortB); /* EN for RS-485 */
  #endif
  #if CONFIG_I2C_USE_PORT_B
  CLOCK_EnableClock(kCLOCK_PortB); /* PTB0, PTB1 for I2C */
  #elif CONFIG_I2C_USE_PORT_E
  CLOCK_EnableClock(kCLOCK_PortE); /* PTE0, PTE1 for I2C */
  #endif
#endif
  /* McuLib modules */
  McuLog_Init();
  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuArmTools_Init();
  McuUtility_Init();
  { /* different random seed for each board with using the UID of the device */
    McuArmTools_UID uid;
    uint32_t seed;

    if (McuArmTools_UIDGet(&uid)!=ERR_OK) {
      McuLog_error("failed getting UID");
    }
    seed = (uid.id[0]<<24)|(uid.id[0]<<16)|(uid.id[0]<<8)|uid.id[0];
    McuUtility_randomSetSeed(seed); /* set new random seed */
  }
  McuLED_Init();
  McuGPIO_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
  McuTimeout_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#elif configUSE_PERCEPIO_TRACE_HOOKS
  McuPercepio_Startup();
  //vTraceEnable(TRC_START);
#endif
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_Init();
#endif
#if PL_CONFIG_USE_I2C && PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#elif PL_CONFIG_USE_I2C
  McuGenericSWI2C_Init();
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  McuExtRTC_Init();
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  McuEE24_Init();
#endif
#if PL_CONFIG_USE_SHT31
  McuSHT31_Init();
#endif

  /* application modules: */
#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART/Gateway, because this changes the clock settings! */
#endif
  LEDS_Init();
#if PL_CONFIG_HAS_BUTTONS
  BTN_Init();
#endif
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_ESP32_UART
  Esp32ShellUart_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_RS485
  RS485_Init();
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_Init();
#endif
#if PL_CONFIG_USE_WDT
  WDT_Init();
#endif
#if PL_CONFIG_USE_CLOCK
  CLOCK_Init();
#endif
#if PL_CONFIG_USE_BLE
  BLEUART_CMDMODE_Init();
#endif
#if PL_CONFIG_USE_BLE_MSG
  BLEMSG_Init();
#endif
#if PL_CONFIG_USE_ESP32
  ESP_Init();
#endif
#if PL_CONFIG_USE_LOW_POWER
  LP_Init();
#endif
  FlipDot_Init();
}
