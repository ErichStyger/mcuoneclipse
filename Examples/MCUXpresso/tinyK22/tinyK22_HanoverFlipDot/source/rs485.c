/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_RS485
#include "rs485.h"
#include "McuGPIO.h"
#include "rs485Uart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "Shell.h"
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif

static void RS485_SendChar(unsigned char ch) {
  RS485Uart_stdio.stdOut(ch);
}

static void RS485_NullSend(unsigned char ch) {
  /* do nothing */
}

static void RS485_ReadChar(uint8_t *c) {
  *c = '\0'; /* only sending on this channel */
}

static bool RS485_CharPresent(void) {
  return false; /* only sending on this channel */
}

McuShell_ConstStdIOType RS485_stdio = {
    (McuShell_StdIO_In_FctType)RS485_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)RS485_SendChar,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)RS485_SendChar,  /* stderr */
    RS485_CharPresent /* if input is not empty */
  };

McuShell_ConstStdIOType RS485_stdioBroadcast = {
    (McuShell_StdIO_In_FctType)RS485_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)RS485_NullSend,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)RS485_NullSend,  /* stderr */
    RS485_CharPresent /* if input is not empty */
  };


static void RS485_SendStr(unsigned char *str) {
  while(*str!='\0') {
    RS485_stdio.stdOut(*str++);
  }
}

void RS485_SendData(uint8_t *data, size_t dataSize) {
  while(dataSize>0) {
    RS485_stdio.stdOut(*data++);
    dataSize--;
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"rs", (unsigned char*)"RS-485 settings\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rs", (unsigned char*)"Group of RS-458 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <text>", (unsigned char*)"Send a text to the RS-485 bus\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "rs help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "rs status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "rs send ", sizeof("rs send ")-1)==0) {
    *handled = true;
    RS485_SendStr((unsigned char*)cmd+sizeof("rs send ")-1);
    RS485_SendStr((unsigned char*)("\n"));
  }
  return ERR_OK;
}

void RS485_Deinit(void) {
  RS485Uart_Deinit();
}

void RS485_Init(void) {
  RS485Uart_Init();
}

#endif /* PL_CONFIG_USE_RS485 */
