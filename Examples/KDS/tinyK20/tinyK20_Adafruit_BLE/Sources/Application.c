/*
 * Application.c
 *
 *  Created on: 27.12.2015
 *      Author: tastyger
 */


#include "Application.h"
#include "SM1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "AdaBLE.h"
#include "FRTOS1.h"
#include "Shell.h"

static void Test(void) {
  ABLE_sendPacket(SDEP_CMDTYPE_AT_WRAPPER, "AT\n", sizeof("AT\n")-1, 0);
  ABLE_getResponse();
}


static void AppTask(void *pvParameters) {
  bool doIt = FALSE;

  ABLE_Init();
  for(;;) {
    if (doIt) {
      Test();
    }
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(10));
  }
}


void APP_Run(void) {
  SHELL_Init();
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
}
