/*
 * Application.c
 *
 *  Created on: 12.10.2016
 *      Author: Erich Styger Local
 */

#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"

static void led_task(void *pvParam) {
  for(;;) {
    LED1_On();
    vTaskDelay(pdMS_TO_TICKS(5));
    LED1_Off();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Start(void) {
  if (xTaskCreate(led_task, "Led", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;){}
}

