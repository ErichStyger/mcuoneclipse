/*
 * Application.c
 *
 *  Created on: 30.09.2018
 *      Author: Erich Styger
 */


#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LED1.h"
#include "Shell.h"

static void AppTask(void *pv) {
  (void)pv;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  SHELL_Init();
  if (xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler();
  for(;;) {
  }
}

