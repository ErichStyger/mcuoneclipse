/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_SHELL
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#include "LowPower.h"
#include "Shell.h"
#include "LED1.h"
#include "LED2.h"
#include "WAIT1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  LP_ParseCommand,
#if PL_HAS_RTOS
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#endif
  NULL /* sentinel */
};

#if !PL_HAS_RTOS
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
#endif

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];
  uint8_t cnt = 0;
  CLS1_ConstStdIOType *ioLocal = CLS1_GetStdio();
  
  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), ioLocal, CmdParserTable);
    /* do a short blink with the the green LED */
    cnt++;
    if (cnt==50) {
      LED2_On();
    } else if (cnt==53) {
      LED2_Off();
      cnt = 0; /* restart */
    }
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}
#endif /* PL_HAS_RTOS */

void SHELL_Init(void) {
  CLS1_Init();
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#else
  SHELL_Run();
#endif
}
#endif /* PL_HAS_SHELL */

