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
#if PL_CONFIG_USE_SHELL_UART
  #include "McuShellUart.h"
#endif
#if PL_CONFIG_USE_SD_CARD
  #include "McuFatFS.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#include "McuTimeDate.h"
#include "McuLog.h"

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
  McuRTOS_ParseCommand,
  McuTimeDate_ParseCommand,
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_ParseCommand,
#endif
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_ParseCommand,
#endif
#if MCULOG_CONFIG_PARSE_COMMAND_ENABLED
  McuLog_ParseCommand,
#endif
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
#if PL_CONFIG_USE_USB_CDC
  {&USB_CdcStdio,  USB_CdcDefaultShellBuffer,  sizeof(USB_CdcDefaultShellBuffer)},
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
#if PL_CONFIG_USE_RTT
    if (ios[i].stdio==&McuRTT_stdio) { /* only send to RTT if there is enough space available to avoid slowing down things */
      unsigned int rttUpSize = SEGGER_RTT_GetUpBufferFreeSize(0);
      if (rttUpSize>strlen((char*)str)) { /* there is enough space available in the RTT up buffer */
        McuShell_SendStr(str, ios[i].stdio->stdOut);
      }
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
#elif PL_CONFIG_USE_RTT
    io = &McuRTT_stdio;
#else
  #error "no shell std IO?"
#endif
  }
  return McuShell_ParseWithCommandTableExt(command, io, CmdParserTable, silent);
}

static void ShellTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool cardMounted = false;
  static McuFatFS_FATFS fileSystemObject;
  bool logFileOpen = false;
  bool doCloseLogFile = false; /* request closing the file e.g. with a push button */
  const unsigned char *logFileName = (unsigned char*)"0:/log.txt";
#endif

  McuLog_info("Started Shell Task");
  vTaskDelay(pdMS_TO_TICKS(1000));
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
#if PL_CONFIG_USE_SD_CARD
    (void)McuFatFS_CheckCardPresence(&cardMounted, (uint8_t*)McuFatFS_CONFIG_DEFAULT_DRIVE_STRING, &fileSystemObject, McuShell_GetStdio());
    if (cardMounted && !logFileOpen) {
      if (McuLog_open_logfile(logFileName)!=0) {
        McuLog_error("Failed opening log file '%s'.", logFileName);
      } else {
        McuLog_info("Logging to file '%s'.", logFileName);
        logFileOpen = true;
      }
    }
    if (logFileOpen && doCloseLogFile) {
      if (McuLog_close_logfile()!=0) {
        McuLog_error("Failed closing log file '%s'.", logFileName);
      } else {
        McuLog_info("Closed log file '%s'.", logFileName);
      }
      doCloseLogFile = false;
    }
#endif
    /* process all I/Os */
    for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
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
      3000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("Failed creating Shell task.");
    for(;;){} /* error! probably out of memory */
  }
  McuShell_SetStdio(ios[0].stdio); /* default */
#if PL_CONFIG_USE_RTT
  McuLog_set_console(&McuRTT_stdio);
#else
  McuLog_set_console(ios[0].stdio);
#endif
}

void SHELL_Deinit(void) {}

#endif /* PL_CONFIG_USE_SHELL */
