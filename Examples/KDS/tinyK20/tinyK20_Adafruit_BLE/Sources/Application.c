/*
 * Application.c
 *
 *  Created on: 27.12.2015
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SM1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "BLEAdafruit.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  #include "bleuart_cmdmode.h"
#endif

static void AppTask(void *pvParameters) {
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  SHELL_Init();
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  BLEUART_CMDMODE_Init();
#endif
#if 0
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
  vTaskStartScheduler();
}
