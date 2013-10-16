/*
 * Application.c
 *
 *  Created on: 11.01.2012
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "LED5.h"
#include "LED6.h"
#include "LED7.h"
#include "LED8.h"

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  LED4_Neg();
  LED5_Neg();
  LED6_Neg();
  LED7_Neg();
  LED8_Neg();
  
  if (FRTOS1_xTaskCreate(
        MainTask,  /* pointer to the task */
        (signed char *)"Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
#if 0
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(200);
  }
#endif
}
