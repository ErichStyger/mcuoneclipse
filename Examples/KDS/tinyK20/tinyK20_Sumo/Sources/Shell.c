/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "RTT1.h"
#include "Q4CLeft.h"
#include "Q4CRight.h"
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
#if PL_CONFIG_HAS_MOTOR
  MOT_ParseCommand,
#endif
  Q4CLeft_ParseCommand,
  Q4CRight_ParseCommand,
  NULL /* sentinel */
};

typedef struct {
  CLS1_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
  {&CLS1_stdio, CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer)},
};

static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  CLS1_SendStr("Shell task started!\r\n", CLS1_GetStdio()->stdOut);
  for(;;) {
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

