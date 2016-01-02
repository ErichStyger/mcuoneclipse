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
#include "CLS1.h"

static void bleuurat_cmdmode(void) {
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  CLS1_SendStr("Adafruit BLE UART CMD Mode\r\n", io->stdOut);
  BLE_Echo(FALSE); /* Disable command echo from Bluefruit */
}

static void AppTask(void *pvParameters) {
  BLE_Init(); /* initialize BLE module */
  for(;;) {
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
