/*
 * application.c
 *
 *  Created on: 18.05.2021
 *      Author: erich
 */

#include "application.h"
#include "McuRTOS.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "leds.h"

uint32_t blinkyCounter = 0;

static void blinky(void *pv) {
	TickType_t prevTime;
	for(;;) {
	  prevTime = xTaskGetTickCount();
	  McuLED_On(LEDS_green);
	  //vTaskDelay(pdMS_TO_TICKS(10));
	  McuWait_Waitms(100);
	  McuLED_Off(LEDS_green);
	  vTaskDelayUntil(&prevTime, pdMS_TO_TICKS(1000));
	  blinkyCounter++;
	}
}

void APP_Run(void) {
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortD);

    McuLib_Init();
    McuWait_Init();
    McuGPIO_Init();
    McuLED_Init();
    LEDS_Init();

    if (xTaskCreate(blinky, "blinky", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    	for(;;) {}
    }

    vTaskStartScheduler();
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
      McuLED_On(LEDS_red);
      McuWait_Waitms(100);
      McuLED_Off(LEDS_red);
      McuWait_Waitms(500);

      McuLED_On(LEDS_green);
      McuWait_Waitms(100);
      McuLED_Off(LEDS_green);
      McuWait_Waitms(500);

      McuLED_On(LEDS_blue);
      McuWait_Waitms(100);
      McuLED_Off(LEDS_blue);
      McuWait_Waitms(500);
    }
}
