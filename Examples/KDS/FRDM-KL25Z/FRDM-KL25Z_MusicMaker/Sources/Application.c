/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "VS1053.h"
#include "FAT1.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  uint16_t val;

  (void)pvParameters; /* parameter not used */
  for(;;) {
    LEDR_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  SHELL_Init();
  VS_Init();
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

