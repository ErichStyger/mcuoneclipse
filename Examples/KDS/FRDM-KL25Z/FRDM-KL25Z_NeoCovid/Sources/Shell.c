/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#if PL_HAS_LED3
  #include "LED3.h"
#endif
#if PL_HAS_NEO_PIXEL
  #include "NeoPixel.h"
#endif
#include "KIN1.h"


static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
#if PL_HAS_NEO_PIXEL
  NEO_ParseCommand,
#endif
  NULL /* sentinel */
};

static void ShellTask(void *pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", (800/sizeof(StackType_t)), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
