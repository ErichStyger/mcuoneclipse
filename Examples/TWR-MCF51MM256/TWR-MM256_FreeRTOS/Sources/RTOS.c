/*
 * RTOS.c
 *
 *  Created on: 18.10.2010
 *      Author: Erich Styger
 */

#include "RTOS.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"


/** 
 * \brief FreeRTOS task
 */
static portTASK_FUNCTION(MyTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
    LED2_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
    LED3_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
    LED4_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  } /* for */
}

void RTOS_Start(void) {
  if (FRTOS1_xTaskCreate(
        MyTask,  /* pointer to the task */
        (signed portCHAR *)"MyTask", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
     for(;;){}; /* error! probably out of memory */
  }
  FRTOS1_vTaskStartScheduler();
}
