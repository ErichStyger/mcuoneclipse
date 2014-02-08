/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "Shell.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "MPC4728.h"

void APP_Run(void) {
#if 0
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        (signed char *)"App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
  SHELL_Init();
  MPC4728_Init();
  FRTOS1_vTaskStartScheduler();
}

