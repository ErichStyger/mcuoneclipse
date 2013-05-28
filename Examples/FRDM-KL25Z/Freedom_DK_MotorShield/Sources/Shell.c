/*
 * Shell.c
 *
 *  Created on: May 28, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#include "Shell.h"
#include "SERVO1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if SERVO1_PARSE_COMMAND_ENABLED
  SERVO1_ParseCommand,
#endif
  NULL /* Sentinel */
};

static unsigned char buf[32];
 
void SHELL_Parse(void) {
  (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Init(void) {
  buf[0] = '\0';
}
