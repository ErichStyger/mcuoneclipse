/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LEDR.h"
#include "LEDG.h"
#if !APP_HAS_SD_CARD
#include "LEDB.h"  /* Blue LED used by SD card (SPI clock) */
#endif
#include "FRTOS1.h"
#include "WAIT1.h"
#include "Shell.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    //LEDR_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed portCHAR *)"Task1", /* task name for kernel awareness debugging */
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

