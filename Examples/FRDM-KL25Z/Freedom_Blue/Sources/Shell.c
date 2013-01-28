/**
 * \file
 * \brief This is the implementation module for the shell
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This interface file is used for a console and terminal.
 * That way we can interact with the target and change settings using a shell implementation
 */
#include "Shell.h"
#include "CLS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "BT1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if BT1_PARSE_COMMAND_ENABLED
  BT1_ParseCommand,
#endif
  NULL /* sentinel */
};

/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};

void SHELL_Run(void) {
  unsigned char buf[32];
  unsigned char bTbuf[32];
  
  buf[0]='\0';
  bTbuf[0]='\0';
  CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    (void)CLS1_ReadAndParseWithCommandTable(bTbuf, sizeof(bTbuf), &BT_stdio, CmdParserTable);
  }
}

