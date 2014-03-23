/**
 * \file
 * \brief Application main loop.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This implements the application main task.
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
  #include "Shell.h"
#endif
#include "RNet_App.h"

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
  RNETA_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
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
