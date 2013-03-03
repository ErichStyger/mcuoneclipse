/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LEDR.h"
#include "LEDG.h"
//#include "LEDB.h"
//#include "I2CSPY1.h"
#include "Reflectance.h"
#include "Motor.h"
//#include "LSM303.h"
#include "LineFollow.h"
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
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if I2CSPY1_PARSE_COMMAND_ENABLED
  I2CSPY1_ParseCommand,
#endif
#if BT1_PARSE_COMMAND_ENABLED
  BT1_ParseCommand,
#endif
  REF_ParseCommand,
  MOT_ParseCommand,
  //LSM_ParseCommand,
  LF_ParseCommand,
  NULL /* sentinel */
};

#if BT1_PARSE_COMMAND_ENABLED
/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};
#endif

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if BT1_PARSE_COMMAND_ENABLED
  unsigned char bTbuf[48];
#endif
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
#if BT1_PARSE_COMMAND_ENABLED
  bTbuf[0]='\0';
#endif
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
#if BT1_PARSE_COMMAND_ENABLED
    (void)CLS1_ReadAndParseWithCommandTable(bTbuf, sizeof(bTbuf), &BT_stdio, CmdParserTable);
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

