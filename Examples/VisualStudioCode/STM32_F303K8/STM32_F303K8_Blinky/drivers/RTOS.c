/**
 * \file
 * \brief Implementation of the RTOS layer.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the RTOS hooks and initialization routines.
 */

#include "Platform.h"
#if PL_CONFIG_USE_FREERTOS
#include "RTOS.h"
#include "McuRTOS.h"
#include "Led.h"

#if PL_CONFIG_USE_FREERTOS

static void Task1(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED_On(LED_LED0);
    vTaskDelay(pdMS_TO_TICKS(100));
    LED_Off(LED_LED0);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void RTOS_Init(void) {
#if PL_CONFIG_USE_FREERTOS
  if (xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
//  vTaskStartScheduler();
#endif
}
#endif

#endif /* PL_CONFIG_USE_FREERTOS */
