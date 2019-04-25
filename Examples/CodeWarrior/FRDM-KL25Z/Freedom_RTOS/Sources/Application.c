/*
 * Application.c
 *
 *  Created on: Oct 22, 2014
 *      Author: tastyger
 */

#include "Application.h"
#include "B8.h"
#include "LED1.h"
#include "LED2.h"
#include "FRTOS1.h"

static TaskHandle_t task2Handle;

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */

  LED1_Neg();
  //FRTOS1_vTaskDelete(NULL);
  FRTOS1_vTaskDelete(task2Handle);
}

#if 0
/* Task to verify proper timing of WAIT1_Waitms(). 
 * Additionally it allows to verify tickless idle mode. TI1 will interrupt the idle mode.
 * */
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    B8_SetVal();
    LED1_On();
    WAIT1_Waitms(1); /* LED1 must be on for 1 ms, B8/LE1 with logic analyzer */
    LED1_Off();
    B8_ClrVal();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}
#else
/* normal task toggling a LED every second */
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED2_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
#endif

void APP_Run(void) {
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    for(;;){}; /* Out of heap memory? */
  }
  if (FRTOS1_xTaskCreate(
        Task2,  /* pointer to the task */
        "Task2", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        &task2Handle /* optional task handle to create */
      ) != pdPASS) {
    for(;;){}; /* Out of heap memory? */
  }
  FRTOS1_vTaskStartScheduler();
}
