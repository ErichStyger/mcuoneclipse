/*
 * Application.c
 *
 *  Created on: 13.03.2019
 *      Author: Erich Styger Local
 */

#include "Application.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED1.h"
#include "McuLED2.h"
#include "McuLED3.h"
#include "McuLED4.h"
#include "McuRTOS.h"
#include "FreeRTOS.h"
#include "task.h"


static void AppTask(void *pv) {
	for(;;) {
		McuLED4_Neg();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void APP_Run(void) {
  /* initialize McuLib drivers */
  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuLED1_Init(); /* red */
  McuLED2_Init(); /* green */
  McuLED3_Init(); /* blue */
  McuLED4_Init(); /* red status */

//  wait();
  /* test the LEDs */
  McuLED1_On();
  McuLED1_Off();
  McuLED2_On();
  McuLED2_Off();
  McuLED3_On();
  McuLED3_Off();
  McuLED4_On();
  McuLED4_Off();

  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();

  for(;;) {
	  McuWait_Waitms(950);
	  McuLED1_On();
	  McuWait_Waitms(50);
	  McuLED1_Off();
  }
}
