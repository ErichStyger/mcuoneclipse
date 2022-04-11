/*
 * Copyright (c) 2020-2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_SHELL
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuArmTools.h"
#include "McuShellUart.h"
#include "McuTimeDate.h"
#include "application.h"
#include "McuLog.h"
#include "McuLittleFS.h"
#include "McuW25Q128.h"

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
  McuRTOS_ParseCommand,
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
  McuTimeDate_ParseCommand,
  McuLog_ParseCommand,
  APP_ParseCommand,
  McuLFS_ParseCommand,
  McuW25_ParseCommand,
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
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
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
    McuShell_SendCh(ch, ios[i].stdio->stdOut);
  }
}

void SHELL_SendString(unsigned char *str) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    McuShell_SendStr(str, ios[i].stdio->stdOut);
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
  vTaskDelay(pdMS_TO_TICKS(1000));
  McuLog_trace("Starting Shell Task");
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    if (!SHELL_HasStdIoInput()) {
      vTaskDelay(pdMS_TO_TICKS(20));
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
