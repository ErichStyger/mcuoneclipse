/*
 * Application.c
 *
 *  Created on: Dec 22, 2013
 *      Author: tastyger
 */
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "EVNT1.h"

static void AppTask(void *pvParameters) {
  for(;;) {
    EVNT1_HandleEvent();
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
    CLS1_SendStr((unsigned char*)"Hello\r\n", CLS1_GetStdio()->stdOut);
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
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
  FRTOS1_vTaskStartScheduler();
}
