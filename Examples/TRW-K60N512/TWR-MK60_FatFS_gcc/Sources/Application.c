/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "FRTOS1.h"
#include "Shell.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  LED4_Neg();
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

