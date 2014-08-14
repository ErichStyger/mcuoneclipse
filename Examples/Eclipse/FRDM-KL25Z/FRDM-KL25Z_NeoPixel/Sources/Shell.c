/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#include "FRTOS1.h"
#include "RTC1.h"
#include "EE241.h"
#include "TmDt1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if RTC1_PARSE_COMMAND_ENABLED
  RTC1_ParseCommand,
#endif
#if EE241_PARSE_COMMAND_ENABLED
  EE241_ParseCommand,
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
  NULL /* Sentinel */
};

static unsigned char localConsole_buf[48];

static portTASK_FUNCTION(ShellTask, pvParameters) {
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
  
  (void)pvParameters; /* not used */
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}

void SHELL_Init(void) {
  localConsole_buf[0] = '\0';
  CLS1_Init();
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+75, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
