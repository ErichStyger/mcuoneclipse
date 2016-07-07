/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Shell.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "FAT1.h"
#include "TmDt1.h"

void SHELL_SendStr(const unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}

static CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
  NULL
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  unsigned char cmd_buf[32];

  (void)pvParameters; /* not used */
  cmd_buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
#endif
    (void)CLS1_ReadAndParseWithCommandTable(cmd_buf, sizeof(cmd_buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED1_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}

