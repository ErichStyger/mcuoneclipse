/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuUtility.h"
#include "McuTimeout.h"
#include "McuTimeDate.h"
#include "McuMinINI.h"
#include "McuLog.h"
#include "disk.h"
#if PL_CONFIG_USE_USB_MSD
  #include "msd_app.h"
#endif

static TimerHandle_t timerTimeoutHndl, timerTimeHndl;

static void vTimerTimoutAddTick(TimerHandle_t pxTimer) {
  McuTimeout_AddTick();
}

static void vTimerTimeAddTick(TimerHandle_t pxTimer) {
  McuTimeDate_AddTick();
}

static void AppTask(void *pv) {
  McuLED_Handle_t led;
  uint8_t colorBuf[8];
  bool sdDiskPresent = false;
  bool present;

  McuLog_trace("Starting Task");
#if 0 /* test logging messages */
  McuLog_trace("Trace message");
  McuLog_debug("Debug message");
  McuLog_info("Information message");
  McuLog_warn("Warning message");
  McuLog_error("Error message");
  McuLog_fatal("Fatal message");
#endif
  vTaskDelay(pdMS_TO_TICKS(1000));
  led = LEDS_LedGreen; /* default */
  if (ini_gets(
      (const TCHAR *)"LED", /* section */
      (const TCHAR *)"color", /* key */
      (const TCHAR *)"green",  /* default value */
      (TCHAR *)colorBuf, sizeof(colorBuf), /* key value from ini */
      (const TCHAR *)"config.ini" /* ini file */
      )
      > 0) /* success */
  {
    if (McuUtility_strcmp((char*)colorBuf, (char*)"red")==0) {
      led = LEDS_LedRed;
    } else if (McuUtility_strcmp((char*)colorBuf, (char*)"green")==0) {
      led = LEDS_LedGreen;
    } else if (McuUtility_strcmp((char*)colorBuf, (char*)"blue")==0) {
      led = LEDS_LedBlue;
    }
  }
  for(;;) {
    present = DISK_IsDiskPresent((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
    McuLED_Toggle(led);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void NMI_Handler(void) {
  /* do nothing, just in case we get here */
}

void APP_Run(void) {
  BaseType_t result;

  PL_Init();
#if PL_CONFIG_USE_USB_MSD
  MSD_APP_Init();
#endif
  result =xTaskCreate(AppTask, "AppTask", 2500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
  if (result!=pdPASS) {
    McuLog_fatal("Failed creating AppTask");
    for(;;) {}
  }
  timerTimeoutHndl = xTimerCreate(  /* timer to handle periodic things */
        "timeout", /* name */
        pdMS_TO_TICKS(McuTimeout_TICK_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerTimoutAddTick); /* callback */
  if (timerTimeoutHndl==NULL) {
    McuLog_fatal("Failed creating timeout timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(timerTimeoutHndl, 0)!=pdPASS) { /* start the timer */
    McuLog_fatal("Failed starting timer");
    for(;;); /* failure!?! */
  }

  timerTimeHndl = xTimerCreate(  /* timer to handle periodic things */
        "time", /* name */
        pdMS_TO_TICKS(McuTimeDate_TICK_TIME_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerTimeAddTick); /* callback */
  if (timerTimeHndl==NULL) {
    McuLog_fatal("Failed creating time timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(timerTimeHndl, 0)!=pdPASS) { /* start the timer */
    McuLog_fatal("Failed starting timer");
    for(;;); /* failure!?! */
  }

  vTaskStartScheduler();
  for(;;) {}
}
