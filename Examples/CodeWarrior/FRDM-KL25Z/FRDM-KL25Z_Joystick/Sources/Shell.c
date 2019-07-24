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
#if PL_HAS_NRF24
  #include "RNET1.h"
#endif
#if PL_HAS_RSTDIO
  #include "RStdIO.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
#if PL_HAS_NRF24
  RNET1_ParseCommand,
#endif
  APP_ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_RSTDIO
  static unsigned char radio_cmd_buf[96];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
  static unsigned char buf[96];
  CLS1_ConstStdIOType *ioLocal = CLS1_GetStdio();
  
  (void)pvParameters; /* not used */
#if PL_HAS_RSTDIO
  radio_cmd_buf[0] = '\0';
#endif
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), ioLocal, CmdParserTable);
#if PL_HAS_RSTDIO
    RSTDIO_Print(ioLocal); /* dispatch incoming messages */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+250, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

