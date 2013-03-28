/*
 * Application.c
 *
 *  Created on: 28.01.2012
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters;
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  //(void)RTOSTICK1_Enable();
  //FRTOS1_taskENABLE_INTERRUPTS();  
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(1000);
  }
  FRTOS1_vTaskStartScheduler();
}
