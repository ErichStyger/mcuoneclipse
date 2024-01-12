/*
 * InterProcessComm.c
 *
 *  Created on: 06.07.2018
 *      Author: Erich Styger
 */

#include "App_Config.h"
#if APP_CONFIG_USE_FREERTOS && configSUPPORT_DYNAMIC_ALLOCATION
#include "InterProcessComm.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

static TaskHandle_t taskHndl;

static void vSlaveTask(void *pvParameters) {
  SemaphoreHandle_t sem = (SemaphoreHandle_t)pvParameters;
  uint32_t counter = 0;

  if (sem==NULL) {
    for(;;) {
      /* should not be NULL? */
    }
  }
  for(;;) {
    if (xSemaphoreTake(sem, portMAX_DELAY)==pdPASS) { /* block on semaphore */
    	counter++;
    }
  }
}

static void vMasterTask(void *pvParameters) {
  SemaphoreHandle_t sem = NULL;

  (void)pvParameters; /* parameter not used */
  sem = xSemaphoreCreateBinary();
  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(sem, "IPC_Sem");
  /* create slave task */
  if (xTaskCreate(vSlaveTask, "Slave", 500/sizeof(StackType_t), sem, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  for(;;) {
    (void)xSemaphoreGive(sem); /* give control to other task */
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


void IPC_Init(void) {
  if (xTaskCreate(vMasterTask, "Master", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &taskHndl) != pdPASS) {
	for(;;){} /* error */
  }
}

#endif
