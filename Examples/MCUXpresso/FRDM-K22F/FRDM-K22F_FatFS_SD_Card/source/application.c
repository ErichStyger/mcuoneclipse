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
  #define SD_CARD_INI_FILENAME "0:/config.ini"
  #define USB_MSD_INI_FILENAME "1:/log.ini"
  #define DEFAULT_LOG_SRC_FILENAME "0:/log.txt"
  #define DEFAULT_LOG_DST_FILENAME "1:/log.txt"
  McuLED_Handle_t led;
  uint8_t keyValueBuf[24];
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
  bool logFileOpen = false;
  bool doCloseLogFile = false; /* set by push button or similar */
#endif

  McuLog_trace("Starting App Task");
  PL_InitFromTask();
  vTaskDelay(pdMS_TO_TICKS(1000));
  led = LEDS_LedGreen; /* default */
  if (ini_gets(
      (const TCHAR *)"LED", /* section */
      (const TCHAR *)"color", /* key */
      (const TCHAR *)"green",  /* default value */
      (TCHAR *)keyValueBuf, sizeof(keyValueBuf), /* key value from ini */
      (const TCHAR *)SD_CARD_INI_FILENAME /* ini file */
      )
      > 0) /* success */
  {
    if (McuUtility_strcmp((char*)keyValueBuf, (char*)"red")==0) {
      led = LEDS_LedRed;
    } else if (McuUtility_strcmp((char*)keyValueBuf, (char*)"green")==0) {
      led = LEDS_LedGreen;
    } else if (McuUtility_strcmp((char*)keyValueBuf, (char*)"blue")==0) {
      led = LEDS_LedBlue;
    }
  }
  for(;;) {
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
#if PL_CONFIG_USE_SD_CARD
  if (!logFileOpen && DISK_IsMounted((unsigned char*)DISK_DRIVE_SD_CARD)) {
    if (McuLog_open_logfile((const unsigned char*)DEFAULT_LOG_SRC_FILENAME)!=0) {
      McuLog_error("Failed opening log file '%s'.", DEFAULT_LOG_SRC_FILENAME);
    } else {
      McuLog_info("Logging to file '%s'.", DEFAULT_LOG_SRC_FILENAME);
      logFileOpen = true;
    }
  }
  if (logFileOpen && doCloseLogFile) {
    if (McuLog_close_logfile()!=0) {
      McuLog_error("Failed closing log file '%s'.", DEFAULT_LOG_SRC_FILENAME);
    } else {
      McuLog_info("Closed log file '%s'.", DEFAULT_LOG_SRC_FILENAME);
    }
    doCloseLogFile = false;
  }
#endif
#if PL_CONFIG_USE_USB_MSD
   /* log.ini example content:
        [Mount]
        copyLog=yes
        srcLogFile=0:\log.txt
        dstLogFile=1:\log.txt
        unmount=yes
      */
    unsigned char srcLogFileName[32], dstLogFileName[32];

    if (DISK_IsMounted((unsigned char*)DISK_DRIVE_USB_MSD)) {
      if (ini_gets(
          (const TCHAR *)"Mount", /* section */
          (const TCHAR *)"copyLog", /* key */
          (const TCHAR *)"no",  /* default value */
          (TCHAR *)keyValueBuf, sizeof(keyValueBuf), /* key value from ini */
          (const TCHAR *)USB_MSD_INI_FILENAME /* ini file */
          )
          > 0) /* success */
      {
        if (McuUtility_strcmp((char*)keyValueBuf, (char*)"yes")==0) { /* copyLog=yes ? */
          if (
              ini_gets(
              (const TCHAR *)"Mount", /* section */
              (const TCHAR *)"srcLogFile", /* key */
              (const TCHAR *)DEFAULT_LOG_SRC_FILENAME,  /* default value */
              (TCHAR *)srcLogFileName, sizeof(srcLogFileName), /* key value from ini */
              (const TCHAR *)USB_MSD_INI_FILENAME /* ini file */
              ) > 0 /* success */
              &&
              ini_gets(
              (const TCHAR *)"Mount", /* section */
              (const TCHAR *)"dstLogFile", /* key */
              (const TCHAR *)DEFAULT_LOG_DST_FILENAME,  /* default value */
              (TCHAR *)dstLogFileName, sizeof(dstLogFileName), /* key value from ini */
              (const TCHAR *)USB_MSD_INI_FILENAME /* ini file */
              ) > 0) /* success */
          {
            /* copy log file */
           McuLog_info("Copy log file '%s' => '%s'", srcLogFileName, dstLogFileName);
           if (McuFatFS_CopyFile(srcLogFileName, dstLogFileName, NULL)!=ERR_OK) {
             McuLED_Off(led);
             for(int i=0;i<10;i++) { /* indicate error with 10 red blinks */
               McuLED_Toggle(LEDS_LedRed);
               vTaskDelay(pdMS_TO_TICKS(500));
             }
             McuLog_error("Copy of log file failed");
           }
          }
        }
      }
      if (ini_gets(
          (const TCHAR *)"Mount", /* section */
          (const TCHAR *)"unmount", /* key */
          (const TCHAR *)"no",  /* default value */
          (TCHAR *)keyValueBuf, sizeof(keyValueBuf), /* key value from ini */
          (const TCHAR *)USB_MSD_INI_FILENAME /* ini file */
          )
          > 0) /* success */
      {
        if (McuUtility_strcmp((char*)keyValueBuf, (char*)"yes")==0) { /* unmount=yes ? */
          DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_UNMOUNT);
          McuLED_Off(led);
          for(int i=0;i<10;i++) { /* indicate unmount with 5 blue blinks */
            McuLED_Toggle(LEDS_LedBlue);
            vTaskDelay(pdMS_TO_TICKS(500));
          }
        }
      }
    }
#endif
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
