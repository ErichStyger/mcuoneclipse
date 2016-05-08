/*
 * Application.c
 *
 *  Created on: 08.05.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "fsl_gpio.h"

xSemaphoreHandle semSW2, semSW3;

void vMainConfigureTimerForRunTimeStats(void) {
}

uint32_t ulMainGetRunTimeCounterValue(void) {
  return xTaskGetTickCountFromISR();
}

static bool SW2IsPressed(void) {
  return GPIO_ReadPinInput(GPIOC, 1u)==0; /* SW2 on PTC1 */
}

static bool SW3IsPressed(void) {
  return GPIO_ReadPinInput(GPIOB, 17u)==0; /* SW3 on PTB17 */
}

/* SW2: PTC1 (near USB)
 * SW3: PTB17
 */
static void ButtonTask(void *pvParameters) {
  (void)pvParameters;

  for(;;) {
    if (SW2IsPressed()) { /* SW2 pressed */
      vTaskDelay(pdMS_TO_TICKS(50)); /* debounce */
      while(SW2IsPressed()) {
        /* wait until released */
        //vTaskDelay(pdMS_TO_TICKS(10));
      }
      (void)xSemaphoreGive(semSW2); /* send message */
    }
    if (SW3IsPressed()) { /* SW3 pressed */
      vTaskDelay(pdMS_TO_TICKS(50)); /* debounce */
      while(SW3IsPressed()) {
        /* wait until released */
        //vTaskDelay(pdMS_TO_TICKS(10));
      }
      (void)xSemaphoreGive(semSW3); /* send message */
    }
    //vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void APP_Init(void) {
  semSW2 = xSemaphoreCreateBinary();
  if (semSW2==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semSW2, "SW2_Sem");
  semSW3 = xSemaphoreCreateBinary();
  if (semSW3==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semSW3, "SW3_Sem");
  if (xTaskCreate(ButtonTask, "Buttons", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
