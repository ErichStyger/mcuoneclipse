/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */
#include "LowPower.h"
#include "Shell.h"
#include "LED1.h"
#include "LED2.h"
#include "WAIT1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  LP_ParseCommand,
  NULL /* sentinel */
};

void SHELL_Run(void) {
  unsigned char buf[48];
  //uint8_t cnt = 0;
  CLS1_ConstStdIOType *ioLocal = CLS1_GetStdio();
  
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), ioLocal, CmdParserTable);
#if 0
    cnt++;
    if (cnt==150) {
      LED2_On();
    } else if (cnt==153) {
      LED2_Off();
      cnt = 0; /* restart */
    }
#endif
    LP_EnterLowPower();
    WAIT1_Waitms(50);
  } /* for */
}

void SHELL_Init(void) {
  CLS1_Init();
}

