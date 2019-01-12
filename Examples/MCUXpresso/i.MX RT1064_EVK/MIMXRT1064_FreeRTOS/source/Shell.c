/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Shell.h"
#include "Application.h"
#include "McuRTOS.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "MsgQueue.h"
#include "McuLED.h"
#include "uart.h"

static bool UART_DataInRx(void) {
  return MSG_NofElementsRxQueue()>0;
}

void UART_StdIOReadChar(uint8_t *c) {
  *c = MSG_GetCharRxQueue();
}

void UART_StdIOSendChar(uint8_t ch) {
  MSG_SendCharTxQueue(ch);
}

static McuShell_ConstStdIOType UART_stdio = {
  (McuShell_StdIO_In_FctType)UART_StdIOReadChar, /* stdin */
  (McuShell_StdIO_OutErr_FctType)UART_StdIOSendChar, /* stdout */
  (McuShell_StdIO_OutErr_FctType)UART_StdIOSendChar, /* stderr */
  UART_DataInRx /* if input is not empty */
};


void SHELL_SendString(unsigned char *msg) {
  McuShell_SendStr(msg, McuShell_GetStdio()->stdOut);
}

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
#if McuRTOS_PARSE_COMMAND_ENABLED
  McuRTOS_ParseCommand,
#endif
#if McuArmTools_PARSE_COMMAND_ENABLED
  McuArmTools_ParseCommand,
#endif
#if McuLED_PARSE_COMMAND_ENABLED
  McuLED_ParseCommand,
#endif
  NULL /* Sentinel */
};

static unsigned char localConsole_buf[48];

void SHELL_Process(void) {
  (void)McuShell_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), McuShell_GetStdio(), CmdParserTable);
}

static void ShellTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  SHELL_SendString((unsigned char*)"Shell task started.\r\n");
  for(;;) {
    (void)McuShell_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), McuShell_GetStdio(), CmdParserTable);
    vTaskDelay(pdMS_TO_TICKS(50));
  } /* for */
}

void SHELL_Init(void) {
  localConsole_buf[0] = '\0';
  McuShell_Init();
  UART_Init();
  (void)McuShell_SetStdio(&UART_stdio);
  if (xTaskCreate(ShellTask, "Shell", 800/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void SHELL_Deinit(void) {
  McuShell_Deinit();
}
#endif /* PL_HAS_SHELL */
