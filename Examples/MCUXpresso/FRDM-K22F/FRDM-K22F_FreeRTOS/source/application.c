/*
 * application.c
 *
 *  Created on: 09.06.2021
 *      Author: erich
 */

#include "platform.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "leds.h"

static void AppTask(void *pv) {
	for(;;) {
		McuLED_Toggle(LEDS_LedBlue);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void APP_Run(void) {
	BaseType_t result;

	PL_Init();
	result =xTaskCreate(AppTask, "AppTask", 2500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
	if (result!=pdPASS) {
		for(;;) {}
	}
	vTaskStartScheduler();
	for(;;) {

	}
}
