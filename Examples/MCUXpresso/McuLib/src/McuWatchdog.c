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

static uint16_t McuWatchdog_State = 0; /* additional watchdog protection with state variable */

typedef struct McuWatchdog_Reports {
  McuWatchdog_ReportID_e id; /* task reporter ID */
  bool isSuspended;  /* if suspended or not */
  const unsigned char *name; /* reporter or task name */
  uint32_t reportMsPerSec; /* average number of ms reported for one second */
  uint8_t minPercent, maxPercent; /* percentage range */
} McuWatchdog_Reports;

static McuWatchdog_Reports reports[McuWatchdog_REPORT_ID_NOF];

void McuWatchdog_InitReportEntry(McuWatchdog_ReportID_e id, const unsigned char *name, uint32_t msForOneSec, uint8_t minPercent, uint8_t maxPercent) {
  if (id<McuWatchdog_REPORT_ID_NOF) {
    reports[id].id = id;
    reports[id].isSuspended = false;
    reports[id].name = name;
    reports[id].reportMsPerSec = msForOneSec;
    reports[id].minPercent = minPercent;
    reports[id].maxPercent = maxPercent;
  } else {
    McuLog_fatal("wrong id %d", id);
  }
}

typedef struct {
  int32_t ms;
  TaskHandle_t task;
} McuWatchdog_Recording_s;

static McuWatchdog_Recording_s McuWatchdog_Recordings[McuWatchdog_REPORT_ID_NOF]; /* array were we record the time reported */

void McuWatchdog_SetTaskHandle(McuWatchdog_ReportID_e id, TaskHandle_t task) {
  if (id<McuWatchdog_REPORT_ID_NOF) {
    McuWatchdog_Recordings[id].task = task;
  }
}

TickType_t McuWatchdog_ReportTimeStart(void) {
  return xTaskGetTickCount();
}

void McuWatchdog_ReportTimeEnd(McuWatchdog_ReportID_e id, TickType_t startTickCount) {
  McuWatchdog_Report(id, ((xTaskGetTickCount()-startTickCount)*configTICK_RATE_HZ)/1000);
}

void McuWatchdog_Report(McuWatchdog_ReportID_e id, uint32_t ms) {
  if (id==McuWatchdog_REPORT_ID_CURR_TASK) { /* get current task handle */
    TaskHandle_t handle;

    handle = xTaskGetCurrentTaskHandle();
    for(int i=0; i<McuWatchdog_REPORT_ID_NOF; i++) {
      if (McuWatchdog_Recordings[i].task==handle) {
        id = i;
        break;
      }
    }
  }
  taskENTER_CRITICAL();
  if (id<McuWatchdog_REPORT_ID_NOF) {
    McuWatchdog_Recordings[id].ms += ms;
  } else { /* something wrong! */
    McuLog_fatal("something wrong");
    for(;;) {
      __asm("nop"); /* wait for WDT to time out */
    }
  }
  taskEXIT_CRITICAL();
}

void McuWatchdog_DelayAndReport(McuWatchdog_ReportID_e id, uint32_t nof, uint32_t ms) {
  for (int i=0; i<nof; i++) {
    vTaskDelay(pdMS_TO_TICKS(ms));
    McuWatchdog_Report(id, ms);
  } /* for */
}

void McuWatchdog_SuspendCheck(McuWatchdog_ReportID_e id) {
  if (id<McuWatchdog_REPORT_ID_NOF) {
    reports[id].isSuspended = true;
  } else {
    McuLog_fatal("wrong id %d", id);
  }
}

void McuWatchdog_ResumeCheck(McuWatchdog_ReportID_e id) {
  if (id<McuWatchdog_REPORT_ID_NOF) {
    reports[id].isSuspended = false;
  } else {
    McuLog_fatal("wrong id %d", id);
  }
}

#if McuWatchdog_REPORT_TIME_VALUES
static void ReportTime(void) {
  uint8_t buf[32];

  for(int i=0; i<McuWatchdog_REPORT_ID_NOF; i++) {
    McuUtility_Num32uToStrFormatted(buf, sizeof(buf), McuWatchdog_Recordings[i].ms, ' ', 4);
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_strcat(buf, sizeof(buf), reports[i].str);
    McuLog_trace(buf);
  } /* for */
}
#endif /* McuWatchdog_REPORT_TIME_VALUES */

static void McuWatchdog_CheckHealth(void) {
  uint32_t min, max;

#if McuWatchdog_REPORT_TIME_VALUES
  ReportTime();
#endif
  for(int i=0; i<McuWatchdog_REPORT_ID_NOF; i++) {
    min = (McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC*reports[i].reportMsPerSec)*reports[i].minPercent/100;
    max = (McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC*reports[i].reportMsPerSec)*reports[i].maxPercent/100;
    taskENTER_CRITICAL();
    if (McuWatchdog_Recordings[i].ms>=min && McuWatchdog_Recordings[i].ms<=max) {
      McuWatchdog_Recordings[i].ms = 0;  /* within boundaries, reset counter */
    } else if (reports[i].isSuspended) {
      McuLog_warn("%s is suspended", reports[i].name);
      McuWatchdog_Recordings[i].ms = 0;  /* reset counter */
    } else {
      uint8_t buf[48];

      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WDT FAILURE: ");
      McuUtility_strcat(buf, sizeof(buf), reports[i].name);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ms:");
      McuUtility_strcatNum32u(buf, sizeof(buf), McuWatchdog_Recordings[i].ms);
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
    taskEXIT_CRITICAL();
  }
}

/* extra safety checks, idea by Jack Ganssle, see "Great Watchdog Timers for Embedded Systems" */
static void McuWatchdog_a(void) {
  if (McuWatchdog_State!=0x5555) {
    McuLog_fatal("something wrong");
    for(;;) {
      __asm("nop");
    }
  }
  McuWatchdog_State += 0x1111;
}

static void McuWatchdog_b(void) {
  if (McuWatchdog_State!=0x8888) {
    McuLog_fatal("something wrong");
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
#if McuWatchdog_DISABLED_FOR_DEBUG
  #warning "Watchdog is disabled!"
#else
  watchdog_update();
#endif
  if (McuWatchdog_State!=0x8888) {
    McuLog_fatal("something wrong");
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
  McuWatchdog_State = 0; /* reset state */
}

static void McuWatchdog_StateA(void) {
  McuWatchdog_State = 0x5555;
  McuWatchdog_a();
}

static void McuWatchdog_StateB(void) {
  McuWatchdog_State += 0x2222;
  McuWatchdog_b(); /* here we kick the dog */
}

static void WatchdogTask(void *pv) {
  uint32_t ms = 0;

  McuLog_trace("started watchdog task");
  for(;;) {
    McuWatchdog_StateA();
    vTaskDelay(pdMS_TO_TICKS(McuWatchdog_CONFIG_TIMEOUT_MS/4)); /* give back some CPU time. We are doing this here at a higher rate then the HW watchdog timer timeout */
    ms += McuWatchdog_CONFIG_TIMEOUT_MS/4;
    McuWatchdog_StateB();
    if (ms>=McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC*1000) {
      McuWatchdog_CheckHealth(); /* if not healthy, we will block here */
      ms = 0;
    }
  }
}

void McuWatchdog_EnableTimer(void) {
#if McuWatchdog_DISABLED_FOR_DEBUG
  #warning "Watchdog is disabled"
#else
  /* Enable the watchdog, requiring the watchdog to be updated or the chip will reboot
     second arg is pause on debug which means the watchdog will pause when stepping through code */
  watchdog_enable(McuWatchdog_CONFIG_TIMEOUT_MS, true); /* enable watchdog timer */
#endif
}

void McuWatchdog_Deinit(void) {
  /* nothing needed */
}

void McuWatchdog_Init(void) {
  if (watchdog_caused_reboot()) {
    McuLog_fatal("Rebooted by Watchdog");
  } else {
    McuLog_info("Clean boot");
  }
  for(int i=0; i<McuWatchdog_REPORT_ID_NOF; i++) {
    McuWatchdog_Recordings[i].ms = 0;
    McuWatchdog_Recordings[i].task = NULL;
  }
  if (xTaskCreate(WatchdogTask, "Watchdog", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    McuLog_fatal("failed creating Watchdog task");
    for(;;){} /* error */
  }
}

#endif /* McuWatchdog_CONFIG_USE_WATCHDOG */
