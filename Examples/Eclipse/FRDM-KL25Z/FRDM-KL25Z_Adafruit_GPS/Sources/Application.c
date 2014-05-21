/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "GPS.h"
#include "CLS1.h"
#include "PORT_PDD.h"
#include "NMEA.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LEDR_Neg();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  /* pull-up on Rx pin (PTE0) */
  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 1, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);
  SHELL_Init();
  NMEA_Init();
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

