/*
 * application.c
 *
 *  Created on: 22.04.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"

#include "fsl_iocon.h"
#include "pin_mux.h"
#include "leds.h"
#include "McuILI9341.h"

static SemaphoreHandle_t mutex;

static void ErrMsg(void) {
  for(;;) { /* error */
    McuLED_Neg(LED_Red);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void AppTask(void *pv) {
  uint8_t res;
  uint8_t var1, var2, var3, mode;

  if (McuILI9341_InitLCD()!=ERR_OK) {
    ErrMsg();
  }

  res = McuILI9341_DrawBox(0, 0, 20, 30, MCUILI9341_BLUE);
  res = McuILI9341_DrawBox(50, 10, 20, 30, MCUILI9341_BLUE);
  res = McuILI9341_DrawBox(20, 20, 10, 10, MCUILI9341_GREEN);

  res = McuILI9341_GetDisplayPowerMode(&mode);
  if (res!=ERR_OK) {
    ErrMsg();
  }
  res = McuILI9341_GetDisplayIdentification(&var1, &var2, &var3);
  if (res!=ERR_OK) {
     ErrMsg();
  }
  res = McuILI9341_InvertDisplay(true);
  if (res!=ERR_OK) {
     ErrMsg();
  }
  res = McuILI9341_InvertDisplay(false);
  if (res!=ERR_OK) {
     ErrMsg();
  }
  res = McuILI9341_DisplayOn(false);
  if (res!=ERR_OK) {
     ErrMsg();
   }
  res = McuILI9341_DisplayOn(true);
  if (res!=ERR_OK) {
     ErrMsg();
  }
  for(;;) {
    McuLED_Neg(LED_Green);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

void APP_Run(void) {
  PL_Init(); /* init modules */

  McuLED_On(LED_Red);
  McuWait_Waitms(100);
  McuLED_Off(LED_Red);

  McuLED_On(LED_Green);
  McuWait_Waitms(100);
  McuLED_Off(LED_Green);

  McuLED_On(LED_Blue);
  McuWait_Waitms(100);
  McuLED_Off(LED_Blue);

  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  mutex = xSemaphoreCreateMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "Mutex");
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
