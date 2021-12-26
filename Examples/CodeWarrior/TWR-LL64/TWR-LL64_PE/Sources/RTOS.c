/*
 * RTOS.c
 *
 *  Created on: 18.10.2010
 *      Author: Erich Styger
 */

#include "RTOS.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LCD.h"
#include "EVNT1.h"

/** 
 * \brief FreeRTOS task
 */
static portTASK_FUNCTION(MyTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(100));
    EVNT1_HandleEvent();
    LCD_ShowTime();
    //APP_ShowTemperature();
  } /* for */
}

void RTOS_Start(void) {
  if (FRTOS1_xTaskCreate(
        MyTask,  /* pointer to the task */
        "MyTask", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
     for(;;){}; /* error! probably out of memory */
  }
  FRTOS1_vTaskStartScheduler();
}
