/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "PORT_PDD.h"
#include "Inhr1.h"
#include "USB1.h"
#include "USB0.h"
#include "FATM1.h"

static void AppTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  vTaskDelay(1000/portTICK_RATE_MS);
  FATM1_disk_initialize(0);
  USB1_Init();
  for(;;) {
    Inhr1_App_Task();
    vTaskDelay(50/portTICK_RATE_MS);
  }
}


void APP_Run(void) {
  /* SD card detection: PTE6 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);
  SHELL_Init();
  if (xTaskCreate(AppTask, (signed portCHAR *)"App", configMINIMAL_STACK_SIZE+400, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
}

