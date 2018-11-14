/*
 * Shell.c
 *
 *      Author: Erich Styger
 */

#include "Shell.h"
#include "CLS1.h"
#include "ESP8266.h"
#include "LEDR.h"

/* table with shell parser/handler */
static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
  ESP_ParseCommand,
  NULL /* sentinel */
};

static unsigned char localConsole_buf[48]; /* buffer for command line */

void SHELL_Parse(void) {
  (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Init(void) {
  localConsole_buf[0] = '\0'; /* initialize buffer */
}
