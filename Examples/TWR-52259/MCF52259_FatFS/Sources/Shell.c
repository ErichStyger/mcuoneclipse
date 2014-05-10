/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Shell.h"
#include "Application.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "TmDt1.h"
#include "FAT1.h"

#define PL_HAS_SD_CARD  1 /* if we have SD card support */

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
#if PL_HAS_SD_CARD
  FAT1_Init();
#endif
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted,
        0 /* volume */, &fileSystemObject, CLS1_GetStdio());
#endif
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

