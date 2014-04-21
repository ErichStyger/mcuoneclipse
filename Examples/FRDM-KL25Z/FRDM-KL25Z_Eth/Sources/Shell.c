/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "w5100.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  FRTOS1_ParseCommand,
  CLS1_ParseCommand,
  APP_ParseCommand,
  FAT1_ParseCommand,
  TmDt1_ParseCommand,
  W5100_ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)"app mount", CLS1_GetStdio(), CmdParserTable);
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+250, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

