/*
 * Application.c
 *
 *  Created on: 10.10.2017
 *      Author: Erich Styger Local
 */
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"

static void MainTask(void *p) {
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  SHELL_Init();
  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+500, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }

  vTaskStartScheduler();
  for(;;) {}
#if 0
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
  }
#endif
}

