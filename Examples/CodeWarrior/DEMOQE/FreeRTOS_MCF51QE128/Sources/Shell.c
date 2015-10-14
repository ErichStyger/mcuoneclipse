/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Shell.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "CLS1.h"

void SHELL_SendStr(const unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}

static CLS1_ParseCommandCallback CmdParserTable[] =
{
  NULL
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[32];

  (void)pvParameters; /* not used */
  cmd_buf[0] = '\0';
  CLS1_Init();
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
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

