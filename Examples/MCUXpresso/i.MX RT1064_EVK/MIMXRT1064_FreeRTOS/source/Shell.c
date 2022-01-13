/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_CONFIG_USE_SHELL
#include "Shell.h"
#include "Application.h"
#include "McuRTOS.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "MsgQueue.h"
#include "McuLED.h"
#include "uart.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif

static bool UART_DataInRx(void) {
  return MSG_NofElementsRxQueue()>0;
}

void UART_StdIOReadChar(uint8_t *c) {
  *c = MSG_GetCharRxQueue();
}

void UART_StdIOSendChar(uint8_t ch) {
  MSG_SendCharTxQueue(ch);
}

static unsigned char localConsole_buf[McuShell_DEFAULT_SHELL_BUFFER_SIZE];

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

typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
#if PL_CONFIG_USE_SHELL_UART
  {&UART_stdio,  localConsole_buf,  sizeof(localConsole_buf)},
#endif
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_USB_CDC
  {&USB_CdcStdio,  USB_CdcDefaultShellBuffer,  sizeof(USB_CdcDefaultShellBuffer)},
#endif
};

void SHELL_Process(void) {
  (void)McuShell_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), McuShell_GetStdio(), CmdParserTable);
}

static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  SHELL_SendString((unsigned char*)"Shell task started.\r\n");
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(20));
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
