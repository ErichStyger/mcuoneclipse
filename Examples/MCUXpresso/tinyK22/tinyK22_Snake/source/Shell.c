/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "platform.h"
#include "Shell.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuShellUart.h"
#include "McuTimeDate.h"
#if USE_FATFS
  #include "McuFatFS.h"
#endif

TaskHandle_t ShellTaskHandle = NULL;
typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
#if PL_CONFIG_USE_UART_SHELL
  {&McuShellUart_stdio,  McuShellUart_DefaultShellBuffer,  sizeof(McuShellUart_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_USB_CDC_SHELL
  {&USB_CdcStdio,  USB_CdcDefaultShellBuffer,  sizeof(USB_CdcDefaultShellBuffer)},
#endif
};

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand, /* Processor Expert Shell component, is first in list */
  McuRTOS_ParseCommand, /* FreeRTOS shell parser */
  McuTimeDate_ParseCommand,
#if USE_FATFS
  McuFatFS_ParseCommand,
#endif
  NULL /* Sentinel */
};

static void ShellTask(void *pvParameters) {
#if USE_FATFS
  bool cardMounted = FALSE;
  static McuFatFS_FATFS fileSystemObject;
#endif
  int i;

  (void)pvParameters; /* not used */
  /* initialize buffers */
#if USE_FATFS
  McuFatFS_Init();
#endif
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  McuShell_SendStr((uint8_t*)"Shell task started!\r\n", McuShell_GetStdio()->stdOut);
  (void)McuShell_ParseWithCommandTable((unsigned char*)McuShell_CMD_HELP, ios[0].stdio, CmdParserTable);
  for(;;) {
#if USE_FATFS
    (void)McuFatFS_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, McuShell_GetStdio());
#endif
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &ShellTaskHandle) != pdPASS) {
    for(;;){} /* error */
  }
  McuShell_SetStdio(ios[0].stdio);
}

void SHELL_Deinit(void) {
}

