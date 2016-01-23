/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "NeoMatrix.h"
#include "RNet_App.h"
#include "TmDt1.h"
#if PL_HAS_RTC
  #include "RTC1.h"
#endif
#if PL_HAS_PONG
  #include "PongGame.h"
#endif
#if PL_HAS_MUSIC || PL_HAS_SD_CARD
#include "SPIBus.h"
#endif
#if PL_HAS_MUSIC
  #include "Music.h"
#endif
#if PL_HAS_MAZE_RACE
  #include "MazeRace.h"
#endif

static void DimmColor(NEO_PixelIdxT start, NEO_PixelIdxT end, bool isRed, bool isGreen, bool isBlue) {
  int i, j;
  uint8_t red, green, blue;

  for(i=0;i<0xff;i+=0x10){
    for(j=start;j<end;j++) {
      red = green = blue = 0;
      if (isRed) {
        red = i;
      }
      if (isGreen) {
        green = i;
      }
      if (isBlue) {
        blue = i;
      }
      NEO_SetPixelRGB(j, red, green, blue);
    }
    NEO_TransferPixels();
    FRTOS1_vTaskDelay(25/portTICK_RATE_MS);
  }
}

void ClockUpdate(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
    if (time.Hour!=prevHour || time.Min!=prevMinute || time.Sec!=prevSecond) {
      MATRIX_ShowClockTime(time.Hour, time.Min, time.Sec);
      //(void)NEO_TransferPixels();
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
    }
  }
}

#if PL_HAS_RTC
static void UpdateFromRTC(void) {
  RTC1_TTIME time;
  RTC1_TDATE date;
  uint8_t res;

  res = RTC1_GetRTCTimeDate(&time, &date);
  if (res==ERR_OK) {
     (void)TmDt1_SetTime(time.hour, time.min, time.sec, 0);
     (void)TmDt1_SetDate(date.year+2000, date.month, date.day);
  }
}
#endif

#if PL_HAS_NEO_PIXEL
static void NeoTask(void* pvParameters) {
  int i;

#define DIMM 0x50
  (void)pvParameters; /* parameter not used */

#if PL_NEO_DEMO
  NEO_ClearAllPixel();
  for(i=0;i<10;i++) {
    NEO_SetPixelRGB(0, 0xff, 0x00, 0x00);
    NEO_TransferPixels();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
#endif
#if PL_NEO_DEMO
  NEO_SetPixelRGB(0, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(1, 0x00, 0xFF, 0x00);
  NEO_SetPixelRGB(2, 0x00, 0x00, 0xff);
  NEO_SetPixelRGB(3, 0x40, 0x50, 0x80);
  NEO_SetPixelRGB(4, 0x60, 0x00, 0xA0);
  NEO_SetPixelRGB(5, 0x40, 0x20, 0x80);
  NEO_SetPixelRGB(6, 0x20, 0x40, 0xFF);
  NEO_SetPixelRGB(7, 0xff, 0x60, 0x30);
  NEO_TransferPixels();
  for(i=0;i<7;i++) {
    NEO_DimmPercentPixel(i,50);
  }
  NEO_TransferPixels();
#endif
  //MATRIX_Test();
  UpdateFromRTC();
  for(;;) {
    //ClockUpdate();
#if 0 && PL_NEO_DEMO
    for(i=0;i<=NEO_PIXEL_LAST;i++) {
      NEO_SetPixelRGB(i, 0xff, 0x00, 0x00);
      if (i>0) {
        NEO_SetPixelRGB(i-1, 0x00, 0x00, 0x00); /* clear previous pixel */
      } else if (i==0) {
        NEO_SetPixelRGB(NEO_PIXEL_LAST, 0x00, 0x00, 0x00);
      }
      NEO_TransferPixels();
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    }
#endif
#if 0 && PL_NEO_DEMO
    NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, TRUE, FALSE, FALSE);
    NEOL_PixelTrail(0xff, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, FALSE, TRUE, FALSE);
    NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, FALSE, FALSE, TRUE);
    NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, FALSE, TRUE, TRUE);
    NEO_ClearAllPixel();
    NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, TRUE, FALSE, TRUE);
    NEO_ClearAllPixel();
    NEOL_PixelTrail(0xff, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, TRUE, TRUE, TRUE);
#endif
#if 0
    NEO_ClearAllPixel();
    NEOL_PixelTrail(0x10, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 36, 50, 2);
//    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, TRUE, FALSE, FALSE);
//    NEOL_PixelTrail(0x00, 0xff/64, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 36, 50, 2);
//    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, FALSE, TRUE, FALSE);
//    NEOL_PixelTrail(0x00, 0x00, 0xff/64, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 36, 50, 2);
//    DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, FALSE, TRUE, TRUE);
#endif
    //LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    //NEO_TransferPixels();
  }
}
#endif

void APP_Run(void) {
#if PL_HAS_NEO_PIXEL
  NEO_Init();
  MATRIX_Init();
#endif
  SHELL_Init();
#if PL_HAS_MAZE_RACE
  MR_Init();
#endif
#if PL_HAS_MUSIC || PL_HAS_SD_CARD
  SPIBus_Init();
#endif
#if PL_HAS_MUSIC
  MUSIC_Init();
#endif
#if PL_HAS_RNET
  RNETA_Init();
#endif
#if PL_HAS_PONG
  PONG_Init();
#elif PL_HAS_NEO_PIXEL
  if (FRTOS1_xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
  FRTOS1_vTaskStartScheduler();
}

