/*
 * Application.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
  #include "Shell.h"
#endif
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif

#if PL_HAS_DEBUG_PRINT
void APP_DebugPrint(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}
#endif

static void AppTask(void *pvParameters) {
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        (signed char *)"App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}
