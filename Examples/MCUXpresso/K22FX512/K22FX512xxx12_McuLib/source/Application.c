/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "McuShell.h"
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif

static void myTask(void *pvParameters) {
  for (;;) {
#if PL_CONFIG_USE_USB_CDC
    McuShell_SendStr((unsigned char*)"hello world\n", USB_CdcStdio.stdOut);
    McuShell_printfIO(&USB_CdcStdio, "%s\n", "hello world!");
#endif
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
 PL_Init();
	if (xTaskCreate(myTask, "myTask", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS)  {
	    printf("ERROR: Creating task failed, not enough memory?\n");
		for(;;){}
	}
	vTaskStartScheduler();
	for(;;){}
}
