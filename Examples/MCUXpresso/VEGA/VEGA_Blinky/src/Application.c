/*
 * Application.c
 *
  *      Author: Erich Styger
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
    McuLED1_On();
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED1_Off();
    McuLED2_On();
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED2_Off();
    McuLED3_On();
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED3_Off();
    McuLED4_On();
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED4_Off();
    vTaskDelay(pdMS_TO_TICKS(500));
    McuLED4_Neg();
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

  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
  /* shoul not end up here... */
  for(;;) { }
}
