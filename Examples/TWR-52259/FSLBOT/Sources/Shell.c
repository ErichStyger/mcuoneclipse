/*
 * Shell.c
 *
 *  Created on: May 28, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "CLS1.h"
#include "Shell.h"
#include "LFEET.h"
#include "RFEET.h"
#include "LHIP.h"
#include "RHIP.h"
#include "FRTOS1.h"
#include "Application.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  APP_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if LFEET_PARSE_COMMAND_ENABLED
  LFEET_ParseCommand,
#endif
#if RFEET_PARSE_COMMAND_ENABLED
  RFEET_ParseCommand,
#endif
#if RHIP_PARSE_COMMAND_ENABLED
  RHIP_ParseCommand,
#endif
#if LHIP_PARSE_COMMAND_ENABLED
  LHIP_ParseCommand,
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
