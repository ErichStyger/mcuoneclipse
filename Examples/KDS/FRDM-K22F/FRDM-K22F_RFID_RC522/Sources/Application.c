/*
 * Application.c
 *
 *  Created on: 29.10.2018
 *      Author: Erich Styger Local
 */

#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "rfid.h"
#include "rc522/MFRC522.h"

static void AppTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  RFID_Init();
  SHELL_Init();
  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
  for(;;){}
}

