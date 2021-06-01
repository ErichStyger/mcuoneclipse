/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_SHELL
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuArmTools.h"
#if PL_CONFIG_USE_I2C_SPY
  #include "McuI2CSpy.h"
#endif
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_RTC
  #include "McuTimeDate.h"
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  #include "McuExtRTC.h"
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  #include "McuEE24.h"
#endif
#if PL_CONFIG_USE_RS485
  #include "rs485.h"
  #include "rs485Uart.h"
#endif
#if PL_CONFIG_USE_STEPPER
  #include "Stepper.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_CLOCK
  #include "clock.h"
#endif
#if PL_CONFIG_USE_INTERMEZZO
  #include "intermezzo.h"
#endif
#include "application.h"
#if PL_CONFIG_USE_DEMOS
  #include "demos.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "ble.h"
  #include "bleuart_cmdmode.h"
#endif
#if PL_CONFIG_USE_BLE_MSG
  #include "bleMsg.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif
#if PL_CONFIG_USE_LED_PIXEL
  #include "pixel.h"
#endif
#if PL_CONFIG_USE_ESP32_UART
  #include "ESP32_Uart.h"
#endif
#include "McuLog.h"
#include "leds.h"
#include "flipdot.h"

#if PL_CONFIG_USE_AUTOMATIC_DEMO_MODE
static struct {
  const char *cmd; /* command string to execute */
  uint32_t delayMs; /* delay after command */
} SHELL_DemoList[] = {
    {"matrix test", 1000},
    {"demo led 0", 1000},
    {"demo led 1", 1000},
    {"demo hands random pos", 1000},
    {"demo hands random color", 1000},
    {"demo hands random pos", 1000},
    {"demo ring random color", 1000},
    {"demo clap", 1000},
};
#endif

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
  McuRTOS_ParseCommand,
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
#if PL_CONFIG_USE_I2C_SPY
  McuI2CSpy_ParseCommand,
#endif
#if PL_CONFIG_USE_RTC
  McuTimeDate_ParseCommand,
#endif
#if PL_CONFIG_USE_EXT_I2C_RTC
  McuExtRTC_ParseCommand,
#endif
#if PL_CONFIG_USE_EXT_EEPROM
  McuEE24_ParseCommand,
#endif
#if PL_CONFIG_USE_STEPPER
  STEPPER_ParseCommand,
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  MAG_ParseCommand,
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_ParseCommand,
#endif
#if PL_CONFIG_USE_RS485
  RS485_ParseCommand,
  RS485Uart_ParseCommand,
#endif
#if PL_CONFIG_USE_CLOCK
  CLOCK_ParseCommand,
#endif
#if PL_CONFIG_USE_INTERMEZZO
  INTERMEZZO_ParseCommand,
#endif
#if PL_CONFIG_USE_DEMOS
  DEMO_ParseCommand,
#endif
#if PL_CONFIG_USE_SHT31
  McuSHT31_ParseCommand,
#endif
#if PL_CONFIG_USE_BLE
  BLE_ParseCommand,
  BLEUART_CMDMODE_ParseCommand,
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  NEO_ParseCommand,
#endif
#if McuLog_CONFIG_PARSE_COMMAND_ENABLED
  McuLog_ParseCommand,
#endif
#if PL_CONFIG_USE_FONT
  MFONT_ParseCommand,
#endif
#if PL_CONFIG_USE_LED_PIXEL && PL_CONFIG_USE_NEO_PIXEL_HW
  PIXEL_ParseCommand,
#endif
  FlipDot_ParseCommand,
  APP_ParseCommand,
  NULL /* Sentinel */
};

typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
#if PL_CONFIG_USE_SHELL_UART
  {&McuShellUart_stdio,  McuShellUart_DefaultShellBuffer,  sizeof(McuShellUart_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_ESP32_UART
  {&Esp32ShellUart_stdio,  Esp32ShellUart_DefaultShellBuffer,  sizeof(Esp32ShellUart_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_USB_CDC
  {&USB_CdcStdio,  USB_CdcDefaultShellBuffer,  sizeof(USB_CdcDefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_BLE
  {&BLEUART_stdio,  BLEUART_DefaultShellBuffer,  sizeof(BLEUART_DefaultShellBuffer)},
#endif
};

bool SHELL_HasStdIoInput(void) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    if (ios[i].stdio->keyPressed()) {
      return true;
    }
  }
  return false; /* no input waiting */
}

void SHELL_SendChar(unsigned char ch) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
#if PL_CONFIG_USE_BLE
  if (ios[i].stdio==&BLEUART_stdio) {
    /* do not send to BLE to limit traffic */
  } else {
    McuShell_SendCh(ch, ios[i].stdio->stdOut);
  }
#else
  McuShell_SendCh(ch, ios[i].stdio->stdOut);
#endif
  }
}

void SHELL_SendString(unsigned char *str) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
#if PL_CONFIG_USE_RTT
    if (ios[i].stdio==&McuRTT_stdio) { /* only send to RTT if there is enough space available to avoid slowing down things */
      unsigned int rttUpSize = SEGGER_RTT_GetUpBufferFreeSize(0);
      if (rttUpSize>strlen((char*)str)) { /* there is enough space available in the RTT up buffer */
        McuShell_SendStr(str, ios[i].stdio->stdOut);
      }
#if PL_CONFIG_USE_BLE
    } else if (ios[i].stdio==&BLEUART_stdio) {
      /* do not send to BLE to limit traffic */
#endif
    } else {
      McuShell_SendStr(str, ios[i].stdio->stdOut);
    }
#else
    McuShell_SendStr(str, ios[i].stdio->stdOut);
#endif
  }
}

uint8_t SHELL_ParseCommand(const unsigned char *command, McuShell_ConstStdIOType *io, bool silent) {
  if (io==NULL) {
#if PL_CONFIG_USE_SHELL_UART
    io = &McuShellUart_stdio;
#elif PL_CONFIG_USE_USB_CDC
    io = &USB_CdcStdio;
#elif PL_CONFIG_USE_RTT
    io = &McuRTT_stdio;
#else
  #error "no shell std IO?"
#endif
  }
  return McuShell_ParseWithCommandTableExt(command, io, CmdParserTable, silent);
}

static void ShellTask(void *pv) {
  int i;
  int msCntr = 0;
#if PL_CONFIG_USE_AUTOMATIC_DEMO_MODE
  int demo = 0;
#endif
  vTaskDelay(pdMS_TO_TICKS(1000));
  McuLog_trace("Starting Shell Task");
#if PL_CONFIG_USE_WDT
  WDT_SetTaskHandle(WDT_REPORT_ID_TASK_SHELL, xTaskGetCurrentTaskHandle());
#endif
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    if (!SHELL_HasStdIoInput()) {
  #if PL_CONFIG_USE_BLE_MSG
      while(BLEMSG_HandleMessage()) {
        /* handle messages */
      }
  #endif
      vTaskDelay(pdMS_TO_TICKS(20));
    #if PL_CONFIG_USE_WDT
      WDT_Report(WDT_REPORT_ID_TASK_SHELL, 20);
    #endif
      msCntr += 20;
      if (msCntr>=200) {
        McuLED_Toggle(LEDS_Led);
        msCntr = 0;
      }
#if PL_CONFIG_USE_AUTOMATIC_DEMO_MODE
      McuLog_trace("execute auto demo '%s'", SHELL_DemoList[demo].cmd);
      if (McuShell_ParseWithCommandTableExt((unsigned char*)SHELL_DemoList[demo].cmd, ios[0].stdio, CmdParserTable, true)!=ERR_OK) {
        McuLog_error("Failed executing command '%s'", SHELL_DemoList[demo].cmd);
      }
      demo++;
      vTaskDelay(pdMS_TO_TICKS(SHELL_DemoList[demo].delayMs));
      msCntr += SHELL_DemoList[demo].delayMs;
      if (demo==sizeof(SHELL_DemoList)/sizeof(SHELL_DemoList[0])) {
        demo = 0;
      }
#endif
    }
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(
      ShellTask,  /* pointer to the task */
      "Shell", /* task name for kernel awareness debugging */
      2300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("Failed creating Shell task.");
    for(;;){} /* error! probably out of memory */
  }
  McuShell_SetStdio(ios[0].stdio); /* default */
#if PL_CONFIG_USE_USB_CDC && PL_CONFIG_USE_RTT && PL_CONFIG_USE_SHELL_UART && McuLog_CONFIG_NOF_CONSOLE_LOGGER==3
  McuLog_set_console(&McuRTT_stdio, 0);
  McuLog_set_console(&McuShellUart_stdio, 1);
  McuLog_set_console(&USB_CdcStdioNonBlockingSend, 2);
#elif PL_CONFIG_USE_RTT && PL_CONFIG_USE_SHELL_UART && McuLog_CONFIG_NOF_CONSOLE_LOGGER==2
  McuLog_set_console(&McuRTT_stdio, 0);
  McuLog_set_console(&McuShellUart_stdio, 1);
#elif PL_CONFIG_USE_RTT
  McuLog_set_console(&McuRTT_stdio, 0);
#elif PL_CONFIG_USE_SHELL_UART
  McuLog_set_console(&McuShellUart_stdio, 0);
#endif
}

void SHELL_Deinit(void) {}

#endif /* PL_CONFIG_USE_SHELL */
