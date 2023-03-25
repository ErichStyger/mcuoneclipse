/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuWatchdog.h"
#if McuWatchdog_CONFIG_USE_WATCHDOG
#include "McuRTOS.h"
#include "McuLog.h"
#include "hardware/watchdog.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "Shell.h"

static uint16_t WDT_State = 0; /* additional watchdog protection with state variable */

typedef struct {
  WDT_ReportID_e id; /* task reporter ID */
  const unsigned char *str; /* reporter name */
  uint32_t reportMsPerSec; /* average ms reported for one second */
  uint8_t minPercent, maxPercent; /* percentage range */
} WDT_Reports;

#define WDT_HEALT_CHECK_TIME_SEC (3)  /* interval for checking health */

static WDT_Reports WDT_ReportingBoundaries[WDT_REPORT_ID_NOF] = { /* order must match WDT_ReportID_e! */
  {.id=WDT_REPORT_ID_TASK_APP, .str=(const unsigned char*)"App", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#if 0
#if PL_CONFIG_USE_GUI
  {.id=WDT_REPORT_ID_TASK_GUI, .str=(const unsigned char*)"GUI", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#endif
#if PL_CONFIG_USE_SHELL
  {.id=WDT_REPORT_ID_TASK_SHELL, .str=(const unsigned char*)"Shell", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#endif
#if PL_CONFIG_USE_LIGHTS
  {.id=WDT_REPORT_ID_TASK_LIGHTS, .str=(const unsigned char*)"Lights", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#endif
#if PL_CONFIG_USE_LIGHTS
  {.id=WDT_REPORT_ID_TASK_EMONITOR, .str=(const unsigned char*)"eMonitor", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#endif
#if PL_CONFIG_USE_ROAD
  {.id=WDT_REPORT_ID_TASK_ROAD, .str=(const unsigned char*)"road", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=120},
#endif
#endif
};

typedef struct {
  int32_t ms;
  TaskHandle_t task;
} WDT_Recording_s;

static WDT_Recording_s WDT_Recordings[WDT_REPORT_ID_NOF]; /* array were we record the time reported */

void McuWatchdog_SetTaskHandle(WDT_ReportID_e id, TaskHandle_t task) {
  if (id<WDT_REPORT_ID_NOF) {
    WDT_Recordings[id].task = task;
  }
}

void McuWatchdog_Report(WDT_ReportID_e id, uint32_t ms) {
  if (id==WDT_REPORT_ID_CURR_TASK) { /* get current task handle */
    TaskHandle_t handle;

    handle = xTaskGetCurrentTaskHandle();
    for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
      if (WDT_Recordings[i].task==handle) {
        id = i;
        break;
      }
    }
  }
  taskENTER_CRITICAL();
  if (id<WDT_REPORT_ID_NOF) {
    WDT_Recordings[id].ms += ms;
  } else { /* something wrong! */
    McuLog_fatal("something wrong");
    for(;;) {
      __asm("nop"); /* wait for WDT to time out */
    }
  }
  taskEXIT_CRITICAL();
}

#if WDT_REPORT_TIME_VALUES
static void ReportTime(void) {
  uint8_t buf[32];

  for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
    McuUtility_Num32uToStrFormatted(buf, sizeof(buf), WDT_Recordings[i].ms, ' ', 4);
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_strcat(buf, sizeof(buf), WDT_ReportingBoundaries[i].str);
    McuLog_trace(buf);
  } /* for */
}
#endif /* WDT_REPORT_TIME_VALUES */

static void WDT_CheckHealth(void) {
  uint32_t min, max;

#if WDT_REPORT_TIME_VALUES
  ReportTime();
#endif
  taskENTER_CRITICAL();
  for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
    min = (WDT_HEALT_CHECK_TIME_SEC*WDT_ReportingBoundaries[i].reportMsPerSec)*WDT_ReportingBoundaries[i].minPercent/100;
    max = (WDT_HEALT_CHECK_TIME_SEC*WDT_ReportingBoundaries[i].reportMsPerSec)*WDT_ReportingBoundaries[i].maxPercent/100;
    if (WDT_Recordings[i].ms>=min && WDT_Recordings[i].ms<=max) {
      WDT_Recordings[i].ms = 0;  /* within boundaries, reset counter */
    } else {
      uint8_t buf[48];

      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WDT FAILURE: ");
      McuUtility_strcat(buf, sizeof(buf), WDT_ReportingBoundaries[i].str);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ms:");
      McuUtility_strcatNum32u(buf, sizeof(buf), WDT_Recordings[i].ms);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" min:");
      McuUtility_strcatNum32u(buf, sizeof(buf), min);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" max:");
      McuUtility_strcatNum32u(buf, sizeof(buf), max);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      McuLog_fatal(buf);
      for(;;) {
        __asm("nop"); /* wait for WDT to time out */
      }
    }
  }
  taskEXIT_CRITICAL();
}

/* extra safety checks, idea by Jack Ganssle, see "Great Watchdog Timers for Embedded Systems" */
static void WDT_a(void) {
  if (WDT_State!=0x5555) {
    McuLog_fatal("something wrong");
    for(;;) {
      __asm("nop");
    }
  }
  WDT_State += 0x1111;
}

static void WDT_b(void) {
  if (WDT_State!=0x8888) {
    McuLog_fatal("something wrong");
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
#if WDT_DISABLED_FOR_DEBUG
  #warning "Watchdog is disabled!"
#else
  watchdog_update();
#endif
  if (WDT_State!=0x8888) {
    McuLog_fatal("something wrong");
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
  WDT_State = 0; /* reset state */
}

static void WDT_StateA(void) {
  WDT_State = 0x5555;
  WDT_a();
}

static void WDT_StateB(void) {
  WDT_State += 0x2222;
  WDT_b(); /* here we kick the dog */
}

static void WatchdogTask(void *pv) {
  uint32_t ms = 0;

  McuLog_trace("started watchdog task");
  for(;;) {
    WDT_StateA();
    vTaskDelay(pdMS_TO_TICKS(WDT_WATCHDOG_TIMEOUT_MS/3)); /* give back some CPU time */
    ms += WDT_WATCHDOG_TIMEOUT_MS/3;
    WDT_StateB();
    if (ms>=WDT_HEALT_CHECK_TIME_SEC*1000) {
      WDT_CheckHealth(); /* if not healthy, we will block here */
      ms = 0;
    }
  }
}

void McuWatchdog_EnableTimer(void) {
#if WDT_DISABLED_FOR_DEBUG
  #warning "Watchdog is disabled"
#else
  /* Enable the watchdog, requiring the watchdog to be updated or the chip will reboot
    second arg is pause on debug which means the watchdog will pause when stepping through code */
  watchdog_enable(WDT_WATCHDOG_TIMEOUT_MS, true);
#endif
}

void McuWatchdog_Init(void) {
  if (watchdog_caused_reboot()) {
    McuLog_fatal("Rebooted by Watchdog");
  } else {
    McuLog_info("Clean boot");
  }
  for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
    WDT_Recordings[i].ms = 0;
    WDT_Recordings[i].task = NULL;
  }
  if (xTaskCreate(WatchdogTask, "Watchdog", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+4, NULL) != pdPASS) {
    McuLog_fatal("failed creating Watchdog task");
    for(;;){} /* error */
  }
}

#endif /* McuWatchdog_CONFIG_USE_WATCHDOG */
