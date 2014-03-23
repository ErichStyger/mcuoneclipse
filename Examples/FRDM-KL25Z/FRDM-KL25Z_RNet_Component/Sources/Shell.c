/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "Radio.h"
#include "RApp.h"
#include "RNet_App.h"
#if PL_HAS_RSTDIO
  #include "RStdIO.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
  RADIO_ParseCommand,
  RNWK_ParseCommand,
  RNETA_ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_RSTDIO
  static unsigned char radio_cmd_buf[96];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
  static unsigned char buf[96];
  CLS1_ConstStdIOType *ioLocal = CLS1_GetStdio();
  
  (void)pvParameters; /* not used */
  APP_DebugPrint((unsigned char*)"INFO: Shell startup.\r\n");
#if PL_HAS_RSTDIO
  radio_cmd_buf[0] = '\0';
#endif
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), ioLocal, CmdParserTable);
#if PL_HAS_RSTDIO
    RSTDIO_Print(ioLocal); /* dispatch incoming messages */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

#if !CLS1_DEFAULT_SERIAL
static void Dummy_StdIOReadChar(byte *c) {
  *c = '\0';
}

static void Dummy_StdIOSendChar(byte ch) {
}

static bool Dummy_StdIOKeyPressed(void) {
  return FALSE;
}

static CLS1_ConstStdIOType Dummy_stdio = {
  (CLS1_StdIO_In_FctType)Dummy_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)Dummy_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)Dummy_StdIOSendChar, /* stderr */
  Dummy_StdIOKeyPressed /* if input is not empty */
};
#endif

void SHELL_Init(void) {
  CLS1_Init();
#if !CLS1_DEFAULT_SERIAL
  (void)CLS1_SetStdio(&Dummy_stdio); /* use the Bluetooth stdio as default */
#endif
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_SHELL */
