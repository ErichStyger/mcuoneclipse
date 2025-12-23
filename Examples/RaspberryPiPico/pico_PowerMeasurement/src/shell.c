/*
 * Copyright (c) 2019-2025, Erich Styger
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
#include "McuSHT31.h"
#include "McuShellCdcDevice.h"
#include "sensor.h"
#if PL_CONFIG_USE_INA260
  #include "McuINA260.h"
#endif
#if PL_CONFIG_USE_ADS1115
  #include "McuADS1115.h"
#endif
#if PL_CONFIG_USE_GP8403
  #include "McuGP8403.h"
#endif
#if PL_CONFIG_USE_INA229
  #include "McuINA229.h"
#endif
#if PL_CONFIG_USE_RELAIS
  #include "McuRelais.h"
#endif

typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
  {&McuShellCdcDevice_stdio,  McuShellCdcDevice_DefaultShellBuffer,  sizeof(McuShellCdcDevice_DefaultShellBuffer)},
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
};

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand, /* McuShell component, is first in list */
  McuRTOS_ParseCommand, /* FreeRTOS shell parser */
  McuArmTools_ParseCommand,
#if PL_CONFIG_USE_SHT31
  McuSHT31_ParseCommand,
#endif
  McuLog_ParseCommand,
  McuShellCdcDevice_ParseCommand,
  Leds_ParseCommand,
#if PL_CONFIG_USE_INA260
  McuINA260_ParseCommand,
#endif
#if PL_CONFIG_USE_ADS1115
  McuADS1115_ParseCommand,
#endif
#if PL_CONFIG_USE_GP8403
  McuGP8403_ParseCommand,
#endif
#if PL_CONFIG_USE_INA229
  McuINA229_ParseCommand,
#endif
#if PL_CONFIG_USE_SENSOR_TASK
  Sensor_ParseCommand,
#endif
#if PL_CONFIG_USE_RELAIS
  McuRelais_ParseCommand,
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

void Shell_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  McuShell_SetStdio(ios[0].stdio);
}

void Shell_Deinit(void) {
  McuShell_SetStdio(NULL);
}

#endif /* PL_CONFIG_USE_SHELL */
