/*
 * Application.c
 *
 *  Created on: 29.12.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "McuRTOS.h"
#include "board.h"

static void AppTask(void *p) {
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(10));
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 0U);
    vTaskDelay(pdMS_TO_TICKS(10));
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 1U);
  }
}

void APP_Run(void) {
	xTaskCreate(/* The function that implements the task. */
      AppTask,
      /* Text name for the task, just to help debugging. */
      "App",
      /* The size (in words) of the stack that should be created
      for the task. */
      (800/sizeof(StackType_t)),
      /* A parameter that can be passed into the task.  Not used
      in this simple demo. */
      NULL,
      /* The priority to assign to the task.  tskIDLE_PRIORITY
      (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
      is the highest priority. */
      1,
      /* Used to obtain a handle to the created task.  Not used in
      this simple demo, so set to NULL. */
      NULL);
  vTaskStartScheduler();
	for(;;) {
	}
}
