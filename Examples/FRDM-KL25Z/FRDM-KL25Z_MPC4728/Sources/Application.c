/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "Shell.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "MPC4728.h"

static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  } /* for */
}


void APP_Run(void) {
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  SHELL_Init();
  MPC4728_Init();
  FRTOS1_vTaskStartScheduler();
}

