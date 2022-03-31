/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "McuSWO.h"
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#include "disk.h"
#include "cr_section_macros.h"
#include "W25Q128.h"


#include "McuSSD1306.h"
#include "McuUtility.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv08Bold.h"
#include "McuFontCour08Normal.h"
#include "McuFontCour08Bold.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv14Normal.h"
#include "McuFontHelv14Bold.h"
#include "McuFontHelv18Normal.h"
#include "McuFontHelv18Bold.h"

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static SemaphoreHandle_t mutex;

static void AppOnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      McuLog_info("Dbnc pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      McuLog_info("Dbnc repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      McuLog_info("Dbnc long pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      McuLog_info("Dbnc pressed repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      McuLog_info("Dbnc released: %d", buttons);
      break;

    default:
    case MCUDBNC_EVENT_END:
      McuLog_info("Dbnc end: %d", buttons);
      break;
  }
}

static uint8_t DisplayAddDateToBuf(uint8_t *buf, uint16_t bufSize, DATEREC *tdate) {
  McuUtility_strcatNum16uFormatted(buf, bufSize, tdate->Day, '0', 2);
  McuUtility_chcat(buf, bufSize, '.');
  McuUtility_strcatNum16uFormatted(buf, bufSize, tdate->Month, '0', 2);
  McuUtility_chcat(buf, bufSize, '.');
  McuUtility_strcatNum16uFormatted(buf, bufSize, (uint16_t)tdate->Year, '0', 2);
  return ERR_OK;
}

static uint8_t DisplayAddTimeToBuf(uint8_t *buf, uint16_t bufSize, TIMEREC *ttime) {
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime->Hour, '0', 2);
  McuUtility_chcat(buf, bufSize, ':');
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime->Min, '0', 2);
  McuUtility_chcat(buf, bufSize, ':');
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime->Sec, '0', 2);
  McuUtility_chcat(buf, bufSize, ',');
#if McuTimeDate_HAS_SEC100_IN_TIMEREC
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime->Sec100, '0', 2);
#else
  McuUtility_strcatNum16sFormatted(buf, bufSize, 0, '0', 2);
#endif
  return ERR_OK;
}

static uint8_t DisplayAddDate(uint8_t *buf, uint16_t bufSize, uint8_t (*GetTimeDateFn)(TIMEREC*, DATEREC*)) {
  DATEREC tdate;

  if (GetTimeDateFn(NULL, &tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  return DisplayAddDateToBuf(buf, bufSize, &tdate);
}

static uint8_t DisplayAddTime(uint8_t *buf, uint16_t bufSize, uint8_t (*GetTimeDateFn)(TIMEREC*, DATEREC*)) {
  TIMEREC ttime;

  if (GetTimeDateFn(&ttime, NULL)!=ERR_OK) {
    return ERR_FAILED;
  }
  return DisplayAddTimeToBuf(buf, bufSize, &ttime);
}



static void AppTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif


  uint8_t res;
  int32_t prevClockUpdateTimestampSec = 0; /* time of previous clock update time stamp, seconds since 1972 */
  TIMEREC time;
  DATEREC date;
  TickType_t lastUpdateFromRTCtickCount; /* time stamp when last time the SW RTC has been update from HW RTC: it gets updated every hour */
  uint32_t ulNotificationValue;

  res = McuTimeDate_Init();
  res = McuTimeDate_GetTime(&time);
  McuLog_info("App Task started.");
  BTN_RegisterAppCallback(AppOnDebounceEvent);
  for(;;) {
	  uint8_t buf[24];
	  McuFontDisplay_PixelDim x, y;
	  x = 5;
	  y = 20;
	  buf[0] = '\0';
	  if (DisplayAddTime(buf, sizeof(buf), McuTimeDate_GetExternalRTCTimeDate)!=ERR_OK) {
		  return ERR_FAILED;
	  } else {
	    //McuShell_SendStr(buf, io->stdOut);
	  }
	  McuGDisplaySSD1306_Clear();
	  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv18Bold_GetFont());
	  McuGDisplaySSD1306_UpdateFull();

#if PL_CONFIG_USE_SD_CARD
    present = DISK_IsInserted((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
#endif
    if (BTN_IsPressed(BTN_UP)) {
      McuLog_info("User Up pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
#if 1
    BTN_PollDebounce(); /* check and debounce */
#else /* simply button polling */
    if (BTN_IsPressed(BTN_USER)) {
      McuLog_info("User Button pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
    if (BTN_IsPressed(BTN_WAKEUP)) {
      McuLog_info("Wakeup Button pressed.");
      LEDS_Neg(LEDS_GREEN);
    }
#endif
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS    McuTimeDate_CONFIG_TICK_TIME_MS

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
 // McuTimeDate_AddTick();
}

void APP_Run(void) {
  PL_Init(); /* init modules */

  W25_Init();
  for(int i=0;i<2;i++) {
//  for(;;) {
#if PL_CONFIG_USE_SWO
    McuSWO_SendStr((unsigned char*)"Hello World using ITM console.\n");
#endif
    LEDS_On(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_On(LEDS_BLUE);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_BLUE);
    McuWait_Waitms(100);
    if (BTN_IsPressed(BTN_USER)) {
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
    }
  } /* for */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      700/sizeof(StackType_t), /* task stack size */
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
