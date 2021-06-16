/*
 * application.c
 *
 *  Created on: 09.06.2021
 *      Author: erich
 */

#include "platform.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "McuWait.h"
#include "leds.h"

static void AppTask(void *pv) {
	TickType_t prevTick = xTaskGetTickCount();
	for(;;) {
		McuLED_On(LEDS_LedBlue);
		McuWait_Waitms(50);
		McuLED_Off(LEDS_LedBlue);
		vTaskDelayUntil(&prevTick, pdMS_TO_TICKS(1000));
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
