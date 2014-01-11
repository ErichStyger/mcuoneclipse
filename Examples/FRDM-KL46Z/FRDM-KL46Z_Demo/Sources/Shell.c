/**
 * \file
 * \brief Shell
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This implements a command line shell.
 */


#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "I2CSPY1.h"
#include "MMA1.h"
#include "Trace.h"
#include "MAG1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LED1_PARSE_COMMAND_ENABLED
  LED1_ParseCommand,
#endif
#if LED2_PARSE_COMMAND_ENABLED
  LED2_ParseCommand,
#endif
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if defined(MMA1_PARSE_COMMAND_ENABLED) && MMA1_PARSE_COMMAND_ENABLED==1
  MMA1_ParseCommand,
#endif
#if defined(MAG1_PARSE_COMMAND_ENABLED) && MAG1_PARSE_COMMAND_ENABLED==1
  MAG1_ParseCommand,
#endif
#if defined(I2CSPY1_PARSE_COMMAND_ENABLED) && I2CSPY1_PARSE_COMMAND_ENABLED==1
  I2CSPY1_ParseCommand,
#endif
  TRACE_ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  }
}

void SHELL_Init(void) {
  CLS1_Init();
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

