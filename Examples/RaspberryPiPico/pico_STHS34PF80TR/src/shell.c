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
#include "McuShellUart.h"
#include "McuShellCdcDevice.h"
#include "McuArmTools.h"
#include "McuTimeDate.h"
#include "McuLog.h"
#if PL_CONFIG_USE_PCF85063A
  #include "McuPCF85063A.h"
#endif
#if PL_HAS_RADIO
  #include "RNet/McuRNet.h"
  #include "RNet/RStdIO.h"
  #include "RNet_App.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuI2CSpy.h"
#endif
#include "leds.h"
#include "power.h"
#include "application.h"

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
#if PL_CONFIG_USE_SHELL_CDC
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
  McuArmTools_ParseCommand,
  McuTimeDate_ParseCommand,
#if McuLog_CONFIG_IS_ENABLED
  McuLog_ParseCommand,
#endif
#if PL_CONFIG_USE_TUD_CDC
  McuShellCdcDevice_ParseCommand,
#endif
#if PL_CONFIG_USE_PCF85063A
  McuPCF85063A_ParseCommand,
#endif
#if PL_CONFIG_USE_POWER
  Power_ParseCommand,
#endif
#if PL_HAS_RADIO
  McuRNet_ParseCommand,
  RNETA_ParseCommand,
#endif
#if PL_CONFIG_USE_I2C
  McuI2CSpy_ParseCommand,
#endif
#if PL_CONFIG_USE_LEDS
  Leds_ParseCommand,
#endif
  App_ParseCommand,
  NULL /* Sentinel */
};

void SHELL_SendStringToIO(const unsigned char *str, McuShell_ConstStdIOType *io) {
  McuShell_SendStr(str, io->stdOut);
}

void SHELL_SendString(const unsigned char *str) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    McuShell_SendStr(str, ios[i].stdio->stdOut);
  }
}

uint8_t SHELL_ParseCommandIO(const unsigned char *command, McuShell_ConstStdIOType *io, bool silent) {
  if (io==NULL) { /* use a default */
#if PL_CONFIG_USE_SHELL_UART
    io = &McuShellUart_stdio;
#elif PL_CONFIG_USE_USB_CDC
    io = &cdc_stdio;
#elif PL_CONFIG_USE_RTT
    io = &McuRTT_stdio;
#else
  #error "no shell std IO?"
#endif
  }
  return McuShell_ParseWithCommandTableExt(command, io, CmdParserTable, silent);
}

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
  #if PL_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
    RSTDIO_Print(McuRTT_GetStdio()); /* dispatch incoming messages */
  #endif
    vTaskDelay(pdMS_TO_TICKS(50));
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#if PL_CONFIG_USE_RTT
  McuShell_SetStdio(McuRTT_GetStdio()); /* use RTT as the default */
#else
  // McuShell_SetStdio(&McuShellUart_stdio); /* use UART as the default */
#endif
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

void SHELL_Deinit(void) {     // GCOVR_EXCL_LINE
  McuShell_SetStdio(NULL);    // GCOVR_EXCL_LINE
}                             // GCOVR_EXCL_LINE

#endif /* PL_CONFIG_USE_SHELL */
