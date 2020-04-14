/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "WAIT1.h"
#include "FRTOS1.h"


static void MainTask(void *pvParameters) {

  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
    LED4_Neg();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void APP_Start(void) {
  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
  for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler();
}
