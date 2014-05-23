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
#include "WAIT1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
  NULL /* Sentinel */
};


void SHELL_Run(void) {
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
  unsigned char localConsole_buf[48];

  CLS1_Init();
  localConsole_buf[0] = '\0';
  Cpu_EnableInt();
  ///(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
    LEDR_Neg();
    WAIT1_Waitms(100);
    CLS1_SendStr((unsigned char*)"hello!\r\n", ioLocal->stdOut);
  } /* for */
}
