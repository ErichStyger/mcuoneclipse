/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include <Sources/Shell.h>
#include <Sources/Zork.h>
#include "CLS1.h"
#include "FRTOS1.h"
#include "FAT1.h"

TaskHandle_t ShellTaskHandle = NULL;
typedef struct {
  CLS1_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
  {&CLS1_stdio, CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer)},
};

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand, /* Processor Expert Shell component, is first in list */
  FRTOS1_ParseCommand, /* FreeRTOS shell parser */
  FAT1_ParseCommand,
  ZORK_ParseCommand,
  NULL /* Sentinel */
};

static void ShellTask(void *pvParameters) {
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
  int i;

  (void)pvParameters; /* not used */
  /* initialize buffers */
  FAT1_Init();
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  CLS1_SendStr((uint8_t*)"Shell task started!\r\n", CLS1_GetStdio()->stdOut);
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ios[0].stdio, CmdParserTable);
  for(;;) {
    (void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &ShellTaskHandle) != pdPASS) {
    for(;;){} /* error */
  }
}

void SHELL_Deinit(void) {
}

