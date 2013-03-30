/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Shell.h"
#include "CLS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if defined(LEDR_PARSE_COMMAND_ENABLED) && LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if defined(LEDG_PARSE_COMMAND_ENABLED) && LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if defined(LEDB_PARSE_COMMAND_ENABLED) && LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
  NULL /* Sentinel */
};

static unsigned char buf[32];
 
void SHELL_Parse(void) {
  (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Init(void) {
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Deinit(void) {
  /* nothing to do */
}


