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
#endif
//#if PL_CONFIG_USE_X12_STEPPER
//  #include "X12.h"
//#endif
#if PL_CONFIG_USE_STEPPER
  #include "Stepper.h"
#endif
#if PL_CONFIG_USE_MAG_SENSOR
  #include "magnets.h"
#endif
#if PL_CONFIG_USE_MATRIX
  #include "matrix.h"
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
#include "application.h"

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
#endif
#if PL_CONFIG_USE_MATRIX
  MATRIX_ParseCommand,
#endif
#if PL_CONFIG_USE_CLOCK
  CLOCK_ParseCommand,
#endif
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
      if (rttUpSize>32) {
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

uint8_t SHELL_ParseCommand(unsigned char *command, McuShell_ConstStdIOType *io, bool silent) {
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
  int i;

#if PL_CONFIG_USE_WDT
  WDT_SetTaskHandle(WDT_REPORT_ID_TASK_SHELL, xTaskGetCurrentTaskHandle());
#endif
  //McuShell_SendStr((uint8_t*)"Shell task started.\r\n", McuShell_GetStdio()->stdOut);
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
    #if PL_CONFIG_USE_WDT
      WDT_Report(WDT_REPORT_ID_TASK_SHELL, 20);
    #endif
    }
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(
      ShellTask,  /* pointer to the task */
      "Shell", /* task name for kernel awareness debugging */
      1200/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  McuShell_SetStdio(ios[0].stdio); /* default */
}

void SHELL_Deinit(void) {}

#endif /* PL_CONFIG_USE_SHELL */
