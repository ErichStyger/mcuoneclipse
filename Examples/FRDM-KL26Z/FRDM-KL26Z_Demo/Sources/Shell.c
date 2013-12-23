/**
 * \file
 * \brief Shell and console interface implementation.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module implements a command line interface to the application.
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
//#include "I2CSPY1.h"
#include "EVNT1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
//#if PL_HAS_I2C_SPY
//#if defined(I2CSPY1_PARSE_COMMAND_ENABLED) && I2CSPY1_PARSE_COMMAND_ENABLED==1
//  I2CSPY1_ParseCommand,
//#endif
//#endif
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  static unsigned char buf[96];
  CLS1_ConstStdIOType *ioLocal = CLS1_GetStdio();
  
  (void)pvParameters; /* not used */
  CLS1_SendStr((unsigned char*)"Shell startup.\r\n", ioLocal->stdOut);
  buf[0] = '\0';
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), ioLocal, CmdParserTable);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

void SHELL_Init(void) {
  CLS1_Init();
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
