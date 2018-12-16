/*
 * Application.c
 *
 *  Created on: 10.12.2018
 *      Author: Erich Styger
 */


#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

static void myTask(void *pvParameters) {
  for (;;) {
      vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
	if (xTaskCreate(myTask, "myTask", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS)  {
	    printf("ERROR: Creating task failed, not enough memory?\n");
	    snprintf(buf, 4, "");
		for(;;){}
	}
	vTaskStartScheduler();
	for(;;){}
}
