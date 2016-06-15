/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Shell.h"
#include "CLS1.h"
#include "Bootloader.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
    CLS1_ParseCommand,
    BL_ParseCommand,
    NULL /* Sentinel */
};

static unsigned char buf[48];

void SHELL_Parse(void) {
	(void) CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Init(void) {
	buf[0] = '\0';
	(void) CLS1_ParseWithCommandTable((unsigned char*) CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Deinit(void) {
	/* nothing to do */
}
