/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "host.h"

#if 0
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LEDR_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}
#endif

void APP_Run(void) {
  SHELL_Init();
  HOST_Init();
#if 0
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed portCHAR *)"Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
  FRTOS1_vTaskStartScheduler();
}

