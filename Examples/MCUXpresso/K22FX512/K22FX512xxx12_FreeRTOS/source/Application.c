/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
		for(;;){}
	}
	vTaskStartScheduler();
	for(;;){}
}
