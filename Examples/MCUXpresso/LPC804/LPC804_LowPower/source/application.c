/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"
#include "SelectionSort.h"

#if McuLib_CONFIG_SDK_USE_FREERTOS
static void blinky(void *pv) {
#if 0
  uint32_t ms = 0;
  for(;;) {
     LEDS_On(LEDS_GREEN);
     vTaskDelay(pdMS_TO_TICKS(50));
     ms += 50;
     LEDS_Off(LEDS_GREEN);
     //LEDS_On(LEDS_RED);
     vTaskDelay(pdMS_TO_TICKS(50));
     ms += 50;
     //LEDS_Off(LEDS_RED);
     vTaskDelay(pdMS_TO_TICKS(400));
     ms += 400;
     if ((ms%(10*1000))==0) { /* every 10 seconds */
         //LEDS_On(LEDS_RED);
         LEDS_On(LEDS_GREEN);
         vTaskDelay(pdMS_TO_TICKS(500));
         //LEDS_Off(LEDS_RED);
         LEDS_Off(LEDS_GREEN);
     }
  }
#elif 1
  for(;;) {
    LEDS_On(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(50));
    LEDS_Off(LEDS_GREEN);
    LEDS_On(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LEDS_Off(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
#elif 0
  for(;;) {
    //LEDS_On(LEDS_GREEN);
    McuWait_Waitus(50);
    vTaskDelay(pdMS_TO_TICKS(50));
    //LEDS_Off(LEDS_GREEN);
    McuWait_Waitus(2*50);
    //LEDS_On(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(50));
    //LEDS_Off(LEDS_RED);
    McuWait_Waitus(50);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
#else
  for(;;) {
    LEDS_On(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(10));
    LEDS_Off(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
#endif
}
#endif

void APP_Run(void) {
  PL_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  if (xTaskCreate(blinky, "blinky", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    for(;;) {}
  }
  vTaskStartScheduler();
#elif 1
  int arr[] = {0, 23, 14, 12, 9};
  for(;;) {
    LEDS_On(LEDS_GREEN);
    for(int i=0; i<500; i++) {
      selectionSort(arr, sizeof(arr)/sizeof(arr[0]));
    }
    LEDS_Off(LEDS_GREEN);
    McuWait_Waitms(1000); /* 1 Hz frequenzy */
  }
#else
  uint32_t ms = 0;
  for(;;) {
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(50);
    ms += 50;
    LEDS_Off(LEDS_GREEN);
    LEDS_On(LEDS_RED);
    McuWait_Waitms(50);
    ms += 50;
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(400);
    ms += 400;
    if ((ms%(10*1000))==0) { /* every 10 seconds */
      LEDS_On(LEDS_RED);
      LEDS_On(LEDS_GREEN);
      McuWait_Waitms(500);
      LEDS_Off(LEDS_RED);
      LEDS_Off(LEDS_GREEN);
    }
  }
#endif
}
