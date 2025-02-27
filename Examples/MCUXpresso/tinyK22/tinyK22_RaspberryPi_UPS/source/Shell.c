/*
 * Copyright (c) 2019, Erich Styger
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
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#endif
#if PL_CONFIG_USE_SHT40
  #include "McuSHT40.h"
#endif
#include "RaspyUART.h"
#include "RaspyGPIO.h"
#include "gateway.h"

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
#if PL_CONFIG_USE_SHT31 && MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
  McuSHT31_ParseCommand,
#endif
#if PL_CONFIG_USE_SHT40 && MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED
  McuSHT40_ParseCommand,
#endif
#if PL_CONFIG_USE_RASPY_UART
  RASPYU_ParseCommand,
#endif
#if PL_CONFIG_USE_RASPBERRY
  RGPIO_ParseCommand,
#endif
#if PL_CONFIG_USE_GATEWAY
  GATEWAY_ParseCommand,
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
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_USB_CDC
  {&USB_CdcStdio,  USB_CdcDefaultShellBuffer,  sizeof(USB_CdcDefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_GATEWAY
  {&GATEWAY_stdioLinuxToShell, GATEWAY_LinuxToShellBuffer, sizeof(GATEWAY_LinuxToShellBuffer)},
  {&GATEWAY_stdioHostToShell, GATEWAY_HostToShellBuffer, sizeof(GATEWAY_HostToShellBuffer)},
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

  McuShell_SendStr((uint8_t*)"Shell task started.\r\n", McuShell_GetStdio()->stdOut);
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
      800/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  McuShell_SetStdio(McuRTT_GetStdio()); /* use RTT as the default */
}

void SHELL_Deinit(void) {}

#endif /* PL_CONFIG_USE_SHELL */
