/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#if PL_CONFIG_HAS_KINETIS_TOOLS
  #include "KIN1.h"
#endif
#if PL_CONFIG_HAS_TIME_DATE
  #include "TmDt1.h"
#else
  #define TmDt1_PARSE_COMMAND_ENABLED 0
#endif
#if PL_CONFIG_HAS_I2CSPY
  #include "I2CSPY1.h"
#else
  #define I2CSPY1_PARSE_COMMAND_ENABLED 0
#endif
#if PL_CONFIG_HAS_ACCEL
  #include "MMA1.h"
#else
  #define MMA1_PARSE_COMMAND_ENABLED 0
#endif
#if PL_CONFIG_HAS_ONE_WIRE
  #include "DS1.h"
  #include "OW1.h"
#endif

void SHELL_SendString(unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if PL_CONFIG_HAS_KINETIS_TOOLS && KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if MMA1_PARSE_COMMAND_ENABLED
  MMA1_ParseCommand,
#endif
#if I2CSPY1_PARSE_COMMAND_ENABLED
  I2CSPY1_ParseCommand,
#endif
#if PL_CONFIG_HAS_ONE_WIRE && DS1_PARSE_COMMAND_ENABLED
  DS1_ParseCommand,
#endif
#if 1 || PL_CONFIG_HAS_ONE_WIRE && OW1_PARSE_COMMAND_ENABLED
  OW1_ParseCommand,
#endif
  NULL /* Sentinel */
};

static void ShellTask(void *pvParameters) {
#if CLS1_DEFAULT_SERIAL
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
#endif
  
  (void)pvParameters; /* not used */
  CLS1_DefaultShellBuffer[0] = '\0';
#if CLS1_DEFAULT_SERIAL
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
#endif
  for(;;) {
#if CLS1_DEFAULT_SERIAL
    (void)CLS1_ReadAndParseWithCommandTable(CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer), ioLocal, CmdParserTable);
#endif
    vTaskDelay(pdMS_TO_TICKS(50));
  } /* for */
}

void SHELL_Init(void) {
  CLS1_Init();
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void SHELL_Deinit(void) {
  CLS1_Deinit();
}
#endif /* PL_CONFIG_HAS_SHELL */
