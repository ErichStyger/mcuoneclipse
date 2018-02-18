/*
 * Application.c
 *
 *  Created on: 17.02.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "WAIT1.h"

static void led_task(void *param) {
  (void)param;
  for(;;) {
    WAIT1_Waitus(100); /* burn some time */
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}

static void T50_task(void *param) {
  (void)param;
  for(;;) {
    WAIT1_Waitms(50); /* burn 5 ms */
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}


void APP_Run(void) {
  if (xTaskCreate(led_task, "Led", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(T50_task, "T50", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {}
}
