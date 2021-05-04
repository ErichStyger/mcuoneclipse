/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Shell.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuShellUart.h"
#include "McuTimeDate.h"

typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
  {&McuShellUart_stdio,  McuShellUart_DefaultShellBuffer,  sizeof(McuShellUart_DefaultShellBuffer)},
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
};

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand, /* McuShell component, is first in list */
  McuTimeDate_ParseCommand,
  McuRTOS_ParseCommand, /* FreeRTOS shell parser */
  NULL /* Sentinel */
};

static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  /* initialize buffers */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  McuShell_SendStr((uint8_t*)"Shell task started!\r\n", McuShell_GetStdio()->stdOut);
  (void)McuShell_ParseWithCommandTable((unsigned char*)McuShell_CMD_HELP, ios[0].stdio, CmdParserTable);
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  McuShell_SetStdio(ios[0].stdio);
}

void SHELL_Deinit(void) {
  McuShell_SetStdio(NULL);
}
