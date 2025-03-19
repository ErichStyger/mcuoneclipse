/*
 * Copyright (c) 2019-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_SHELL
#include "shell.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuArmTools.h"
#include "McuLog.h"
#include "McuShellUart.h"
#include "McuTimeDate.h"
#include "leds.h"
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
  #include "minGlue-Flash.h"
#endif
#if PL_CONFIG_USE_NVMC
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#if PL_CONFIG_USE_TUD_CDC
  #include "McuShellCdcDevice.h"
#endif

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
#if (PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PICO || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PICO_W) && PL_CONFIG_USE_TUD_CDC
  {&McuShellCdcDevice_stdio,  McuShellCdcDevice_DefaultShellBuffer,  sizeof(McuShellCdcDevice_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
};

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand, /* McuShell component, is first in list */
  McuRTOS_ParseCommand, /* FreeRTOS shell parser */
  Leds_ParseCommand,
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
#if PL_CONFIG_USE_NVMC
  McuFlash_ParseCommand,
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_ParseCommand,
  ini_ParseCommand,
#endif
#if McuLog_CONFIG_IS_ENABLED
  McuLog_ParseCommand,
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  NEO_ParseCommand,
#endif
#if PL_CONFIG_USE_TUD_CDC
  McuShellCdcDevice_ParseCommand,
#endif
  NULL /* Sentinel */
};

static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  McuLog_trace("started shell task");
  /* initialize buffers */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 1000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  McuShell_SetStdio(ios[0].stdio);
#if McuLog_CONFIG_IS_ENABLED
  #if PL_CONFIG_USE_RTT && PL_CONFIG_USE_SHELL_UART && McuLog_CONFIG_NOF_CONSOLE_LOGGER==2 /* both */
    McuLog_set_console(McuRTT_GetStdio(), 0);
    McuLog_set_console(&McuShellUart_stdio, 1);
  #elif PL_CONFIG_USE_RTT && PL_CONFIG_USE_USB_CDC && McuLog_CONFIG_NOF_CONSOLE_LOGGER==2 /* both */
    McuLog_set_console(McuRTT_GetStdio(), 0);
    McuLog_set_console(&cdc_stdio, 1);
  #elif PL_CONFIG_USE_RTT /* only RTT */
    McuLog_set_console(McuRTT_GetStdio(), 0);
  #elif PL_CONFIG_USE_SHELL_UART /* only UART */
    McuLog_set_console(&McuShellUart_stdio, 0);
  #endif
#endif
}

void SHELL_Deinit(void) {
  McuShell_SetStdio(NULL);
}

#endif /* PL_CONFIG_USE_SHELL */
