/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "BLEAdafruit.h"
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  #include "bleuart_cmdmode.h"
#endif

uint8_t BLE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
  BLE_ParseCommand,
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  BLEUART_CMDMODE_ParseCommand,
#endif
  NULL /* sentinel */
};

#if PL_CONFIG_HAS_SEGGER_RTT
static CLS1_ConstStdIOType RTT_Stdio = {
  (CLS1_StdIO_In_FctType)RTT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stderr */
  RTT1_StdIOKeyPressed /* if input is not empty */
};
#endif

static void ShellTask(void *pvParameters) {
#if PL_CONFIG_HAS_SEGGER_RTT
  static unsigned char rtt_buf[128];
#endif
  static unsigned char buf[128];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
#if PL_CONFIG_HAS_SEGGER_RTT
  rtt_buf[0] = '\0';
#endif
  //(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
#if PL_CONFIG_HAS_SEGGER_RTT
    (void)CLS1_ReadAndParseWithCommandTable(rtt_buf, sizeof(rtt_buf), &RTT_Stdio, CmdParserTable);
#endif
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+300, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

