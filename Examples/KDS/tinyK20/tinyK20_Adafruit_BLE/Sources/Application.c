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
#if PL_BLEUART_CMDMODE_ENABLED
  #include "bleuart_cmdmode.h"
#endif


static void AppTask(void *pvParameters) {
#if 0
  SYS1_Print("Starting BLE application\r\n");
  SYS1_PrintfHost("status 1:%d\r\n", 35);
  SYS1_PrintfTarget("status 2:%d\r\n", 38);
  SYS1_Warn("Warning: BLE module not connected\r\n");
  SYS1_WarnfHost("BLE status 1:%d\r\n", 15);
  SYS1_WarnfTarget("BLE status 2:%d\r\n", 33);
  SYS1_Error("Error: BLE IRQ is high\r\n");
  SYS1_ErrorfHost("BLE IRQ:%d\r\n", 444);
  SYS1_ErrorfTarget("BLE IRQ:%d\r\n", 103);
#endif
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  SHELL_Init();
#if PL_BLEUART_CMDMODE_ENABLED
  BLEUART_CMDMODE_Init();
#endif
#if 0
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
  vTaskStartScheduler();
}
