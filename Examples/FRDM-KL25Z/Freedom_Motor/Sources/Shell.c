/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Shell.h"
#include "LED1.h"
#include "PE_LDD.h"
#include "FRTOS1.h"
#include "FSSH1.h"
#include "Motor.h"


static FSSH1_ParseCommandCallback ShellParsers[] =
{
  MOT_ParseCommand
};

static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  int i;

  /* iterate through all parser functions in table */
  for(i=0;i<sizeof(ShellParsers)/sizeof(FSSH1_ParseCommandCallback);i++) {
    if (ShellParsers[i](cmd, handled, io)!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[32];

  (void)pvParameters; /* not used */
  cmd_buf[0] = '\0';
  FSSH1_Init();
  (void)FSSH1_ParseCommand((const unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand);
  for(;;) {
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand /* local cmd parser */);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED1_Neg();
  }
}

void SHELL_Init(void) {
  MOT_Init();
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}

