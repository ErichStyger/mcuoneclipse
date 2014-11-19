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

#define HAS_CLOCK    1
#define HAS_ELEVATOR 0
#define HAS_SHELL    1

#if HAS_CLOCK
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

#if HAS_ELEVATOR
static void Elevator(void) {
  NEO_PixelIdxT i;

  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();
  for(i=NEO_PIXEL_FIRST; i<=NEO_PIXEL_LAST; i++) {
    NEO_SetPixelRGB(i, 0xff/2, 0xff/2, 0xff/2);
    (void)NEO_TransferPixels();
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}
#endif

static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters; /* not used */
  RTC1_TTIME time;
  RTC1_TDATE date;
  TIMEREC swTime;

  if (RTC1_GetRTCTimeDate(&time, &date)==ERR_OK) {
    TmDt1_SetDate((uint16_t)date.year+2000, date.month, date.day);
    TmDt1_SetTime(time.hour, time.min, time.sec, 0);
  } else {
    for(;;) {} /* error */
  }
  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();
#if HAS_CLOCK
  (void)NEOL_PixelTrail(0x00, 0x00, 0xFF, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 25, 20);
  (void)NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  16, 25, 15);
  (void)NEOL_PixelTrail(0x00, 0x50, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  16, 25, 10);

  CLOCK_Init();
#endif
  for(;;) {
#if HAS_ELEVATOR
    Elevator();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
#else
    if (TmDt1_GetTime(&swTime)==ERR_OK) {
      if (swTime.Sec==0) {
        if (swTime.Min==0) { /* every full hour */
          (void)NEOL_PixelTrail(0x00, 0x00, 0xFF, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  16, 25, 25);
          (void)NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  16, 25, 25);
          RTC1_GetRTCTime(&time); /* propagate RTC time to software RTC */
          TmDt1_SetTime(time.hour, time.min, time.sec, 0);
        } else if (swTime.Min==15 || swTime.Min==30 || swTime.Min==45) {
          (void)NEOL_PixelTrail(0xFF, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  32, 25, 20);
        }
      }
    }
    CLOCK_Update();
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
#endif
  } /* for */
}


void APP_Start(void) {
  NEO_Init();
#if HAS_SHELL
  SHELL_Init();
#endif
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
