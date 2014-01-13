/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module demonstrating semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"

#define USE_SEMAPHORES 0

#if USE_SEMAPHORES
static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  xSemaphoreHandle sem;
  
  sem = (xSemaphoreHandle)pvParameters;
  for(;;) {
    if (sem != NULL) {
      if (FRTOS1_xSemaphoreTake(sem, portMAX_DELAY)==pdTRUE) {
        LED3_Neg();
      }
    }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  xSemaphoreHandle sem = NULL;

  (void)pvParameters; /* parameter not used */
  FRTOS1_vSemaphoreCreateBinary(sem);
  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(sem, "IPC_Sem");
#endif
  /* create slave task */
  if (FRTOS1_xTaskCreate(vSlaveTask, (signed portCHAR *)"Slave", configMINIMAL_STACK_SIZE, sem, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  for(;;) {
    if (sem != NULL) { /* valid semaphore? */
      (void)xSemaphoreGive(sem); /* give control to other task */
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    }
  }
}
#endif /* USE_SEMAPHORES */

/*! \brief Initializes module */
void SEM_Init(void) {
#if USE_SEMAPHORES
  if (FRTOS1_xTaskCreate(vMasterTask, (signed portCHAR *)"Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_HAS_SEMAPHORE */
