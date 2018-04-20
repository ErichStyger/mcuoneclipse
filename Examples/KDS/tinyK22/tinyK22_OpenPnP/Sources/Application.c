/*
 * Application.c
 *
 *  Created on: 18.04.2018
 *      Author: Erich Styger
 */

#include "FRTOS1.h"
#include "Shell.h"
#include "LED1.h"
#include "Feeder.h"
#include "Pressure.h"

static void AppTask(void *param) {
  (void)param;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}

void APP_Run(void) {
  SHELL_Init();
  FEED_Init();
  PRESSURE_Init();
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;){}
}

