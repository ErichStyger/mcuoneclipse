/*
 * Application.c
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#include "Cpu.h"
#include "Application.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "WAIT1.h"
#include "NeoRingClock.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "TmDt1.h"
#include "RTC1.h"

#if 1
void TestClock(void) {
  int hour, minute, second;

  for(;;) {
    for(hour=0;hour<24;hour++) {
      for(minute=0;minute<60;minute++) {
        for(second=0;second<60;second++) {
          CLOCK_SetTime(hour, minute, second);
          (void)NEO_TransferPixels();
          WAIT1_WaitOSms(1);
        }
      }
    }
  }
}
#endif

static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters; /* not used */
  RTC1_TTIME time;
  RTC1_TDATE date;

  if (RTC1_GetRTCTimeDate(&time, &date)==ERR_OK) {
    TmDt1_SetDate((uint16_t)date.year+2000, date.month, date.day);
    TmDt1_SetTime(time.hour, time.min, time.sec, 0);
  } else {
    for(;;) {} /* error */
  }
  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();

  CLOCK_Init();
  for(;;) {
    CLOCK_Update();
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}


void APP_Start(void) {
  NEO_Init();
  SHELL_Init();
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
