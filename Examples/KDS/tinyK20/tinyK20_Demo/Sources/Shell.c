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
#include "FAT1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "KIN1.h"
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
  FAT1_ParseCommand,
  KIN1_ParseCommand,
  TmDt1_ParseCommand,
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

static void SDTask(void *pvParameters) {
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;

  (void)pvParameters; /* not used */
  FAT1_Init(); /* initialize FAT module */
  for(;;) {
    (void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
  }
}


static void ShellTask(void *pvParameters) {
#if PL_CONFIG_HAS_SEGGER_RTT
  static unsigned char rtt_buf[48];
#endif
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
#if PL_CONFIG_HAS_SEGGER_RTT
  rtt_buf[0] = '\0';
#endif
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
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
  if (FRTOS1_xTaskCreate(SDTask, "SDCard", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

