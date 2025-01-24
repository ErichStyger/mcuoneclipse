/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "Shell.h"
#if PL_CONFIG_USE_SHELL
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuArmTools.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuShellUart.h"
#include "McuFlash.h"
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "nvmc.h"
#endif
#if PL_CONFIG_USE_SWO
  #include "McuSWO.h"
#endif
#if PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD
  #include "McuFatFS.h"
  #include "disk.h"
#endif
#if PL_CONFIG_USE_RTC
  #include "McuTimeDate.h"
#endif
#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  #include "McuExtRTC.h"
#endif
#if PL_CONFIG_HAS_SHT31
  #include "McuSHT31.h"
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
  #if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
    #include "McuW25Q128.h"
  #elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
    #include "McuFlash.h"
  #endif
#endif

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
  McuRTOS_ParseCommand,
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
#if McuLog_CONFIG_IS_ENABLED && McuLog_CONFIG_PARSE_COMMAND_ENABLED
  McuLog_ParseCommand,
#endif
  McuTimeDate_ParseCommand,
#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  McuExtRTC_ParseCommand,
#endif
#if PL_CONFIG_HAS_SHT31
  McuSHT31_ParseCommand,
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_ParseCommand,
#endif
#if PL_CONFIG_USE_NVMC
  NVMC_ParseCommand,
#endif
#if PL_CONFIG_USE_SWO
  McuSWO_ParseCommand,
#endif
#if PL_CONFIG_USE_SD_CARD
  McuFatFS_ParseCommand,
  DISK_ParseCommand,
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  McuLFS_ParseCommand,
#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_
#error
#endif
#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
#error
  McuW25_ParseCommand,
#endif
#endif
#if McuFlash_CONFIG_IS_ENABLED
  McuFlash_ParseCommand,
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
#if PL_CONFIG_USE_SWO
  {&McuSWO_stdio,  McuSWO_DefaultShellBuffer,  sizeof(McuSWO_DefaultShellBuffer)},
#endif
};

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

static void ShellTask(void *pv) {
  int i;

  McuLog_info("Shell task started.");
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
   /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(
      ShellTask,  /* pointer to the task */
      "Shell", /* task name for kernel awareness debugging */
      4000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  McuShell_SetStdio(ios[0].stdio);
#if McuLog_CONFIG_IS_ENABLED
  for(int i=0; i<sizeof(ios)/sizeof(ios[0]) && i<McuLog_CONFIG_NOF_CONSOLE_LOGGER; i++) {
    McuLog_set_console(ios[i].stdio, i);
  }
#endif /* McuLog_CONFIG_IS_ENABLED */
}

void SHELL_Deinit(void) {}

#endif /* PL_CONFIG_USE_SHELL */
