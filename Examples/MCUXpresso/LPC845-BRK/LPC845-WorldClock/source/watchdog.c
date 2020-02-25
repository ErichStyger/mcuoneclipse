/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_WDT
#include "watchdog.h"
#include "fsl_wwdt.h"
#include "fsl_power.h"
#include "leds.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "Shell.h"

#define WDT_DISABLED_FOR_DEBUG (0)  /* set to 1 for easier debugging */

static uint16_t WDT_State = 0; /* additional watchdog protection with state variable */

typedef struct {
  WDT_ReportID_e id;
  const unsigned char *str;
  uint32_t reportMsPerSec; /* average ms reported for one second */
  uint8_t minPercent, maxPercent; /* percentage range */
} WDT_Reports;

#define WDT_HEALT_CHECK_TIME_SEC (2)  /* interval for checking health */

static WDT_Reports WDT_ReportingBoundaries[WDT_REPORT_ID_NOF] = {
    {.id=WDT_REPORT_ID_TASK_APP,   .str=(const unsigned char*)"AppTask",   .reportMsPerSec = 1000, .minPercent=70, .maxPercent=130},
  #if PL_CONFIG_USE_RS485
    {.id=WDT_REPORT_ID_TASK_RS485, .str=(const unsigned char*)"RS485Task", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=130},
  #endif
  #if PL_CONFIG_USE_SHELL
    {.id=WDT_REPORT_ID_TASK_RS485, .str=(const unsigned char*)"ShellTask", .reportMsPerSec = 1000, .minPercent=70, .maxPercent=130},
  #endif
};

typedef struct {
  int32_t ms;
  TaskHandle_t task;
} WDT_Recording_s;

static WDT_Recording_s WDT_Recordings[WDT_REPORT_ID_NOF];

void WDT_SetTaskHandle(WDT_ReportID_e id, TaskHandle_t task) {
  if (id<WDT_REPORT_ID_NOF) {
    WDT_Recordings[id].task = task;
  }
}

void WDT_Report(WDT_ReportID_e id, uint32_t ms) {
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
  if (id<WDT_REPORT_ID_NOF) {
    WDT_Recordings[id].ms += ms;
  } else { /* something wrong! */
    for(;;) {
      /* wait for WDT to time out */
    }
  }
}

static void WDT_CheckHealth(void) {
  uint32_t min, max;

  for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
    min = (WDT_HEALT_CHECK_TIME_SEC*WDT_ReportingBoundaries[i].reportMsPerSec)*WDT_ReportingBoundaries[i].minPercent/100;
    max = (WDT_HEALT_CHECK_TIME_SEC*WDT_ReportingBoundaries[i].reportMsPerSec)*WDT_ReportingBoundaries[i].maxPercent/100;
    if (WDT_Recordings[i].ms>=min && WDT_Recordings[i].ms<=max) {
      WDT_Recordings[i].ms = 0;  /* within boundaries, reset counter */
    } else {
  #if PL_CONFIG_USE_SHELL
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
      SHELL_SendString(buf);
  #endif
      for(;;) {
        /* wait for WDT to time out */
      }
    }
  }
}

void WDT_IRQHandler(void) {
  uint32_t wdtStatus = WWDT_GetStatusFlags(WWDT);

  McuLED_Toggle(LEDS_Led);
  /* The chip will reset before this happens */
  if (wdtStatus & kWWDT_TimeoutFlag) {
    /* Stop WDT */
    WWDT_Disable(WWDT);
    WWDT_ClearStatusFlags(WWDT, kWWDT_TimeoutFlag);
    /* Needs restart */
    WWDT_Enable(WWDT);
  }
  /* Handle warning interrupt */
  if (wdtStatus & kWWDT_WarningFlag) {
    /* A watchdog feed didn't occur prior to warning timeout */
    WWDT_ClearStatusFlags(WWDT, kWWDT_WarningFlag);
    /* User code. User can do urgent case before timeout reset.
     * IE. user can backup the ram data or ram log to flash.
     * the period is set by config.warningValue, user need to
     * check the period between warning interrupt and timeout.
     */
  }
}

/* extra safety checks, idea by Jack Ganssle, see "Great Watchdog Timers for Embedded Systems" */
static void WDT_a(void) {
  if (WDT_State!=0x5555) {
    for(;;) {
      __asm("nop");
    }
  }
  WDT_State += 0x1111;
}

static void WDT_b(void) {
  if (WDT_State!=0x8888) {
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
#if WDT_DISABLED_FOR_DEBUG
  #warning "Watchdog is disabled!"
#else
  WWDT_Refresh(WWDT);
#endif
  if (WDT_State!=0x8888) {
    for(;;) { /* getting here in case of run-away code?!? */
      __asm("nop");
    }
  }
  WDT_State = 0; /* reset state */
}

static void WatchdogTask(void *pv) {
  uint32_t ms = 0;

  for(;;) {
    WDT_State = 0x5555;
    WDT_a();
    vTaskDelay(pdMS_TO_TICKS(100)); /* give back some CPU time */
    ms += 100;
    WDT_State += 0x2222;
    WDT_b();
    if (ms>=WDT_HEALT_CHECK_TIME_SEC*1000) {
      WDT_CheckHealth();
      ms = 0;
    }
  }
}

void WDT_Init(void) {
  wwdt_config_t config;
  uint32_t wdtFreq;

  /* init recordings */
  for(int i=0; i<WDT_REPORT_ID_NOF; i++) {
    WDT_Recordings[i].ms = 0;
    WDT_Recordings[i].task = NULL;
  }
  if (xTaskCreate(
      WatchdogTask,  /* pointer to the task */
      "Watchdog", /* task name for kernel awareness debugging */
      300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+4,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }

  CLOCK_InitWdtOsc(kCLOCK_WdtAnaFreq600KHZ, 2U);
  POWER_DisablePD(kPDRUNCFG_PD_WDT_OSC);

  /* Check if reset was because of Watchdog */
  if (WWDT_GetStatusFlags(WWDT) & kWWDT_TimeoutFlag) {
  #if PL_CONFIG_USE_SHELL
    SHELL_SendString((unsigned char*)"Watchdog reset occurred!\r\n");
  #endif
    for(int i=0; i<5; i++) {
      McuLED_Toggle(LEDS_Led);
      McuWait_Waitms(50);
    }
  }
  /* The WDT divides the input frequency into it by 4 */
   wdtFreq = CLOCK_GetFreq(kCLOCK_WdtOsc)/4;
   WWDT_GetDefaultConfig(&config);
   /*
    * Set watchdog feed time constant to approximately 4s
    * Set watchdog warning time to 512 ticks after feed time constant
    * Set watchdog window time to 1s
    */
   config.timeoutValue = MSEC_TO_COUNT(4000, wdtFreq);
   config.warningValue = MSEC_TO_COUNT(3000, wdtFreq); /* warning interrupt after this time */
   config.windowValue  = MSEC_TO_COUNT(4000, wdtFreq); /* kick has to happen below that value */
   /* Configure WWDT to reset on timeout */
   config.enableWatchdogReset = true;
   /* Setup watchdog clock frequency(Hz). */
   config.clockFreq_Hz = CLOCK_GetFreq(kCLOCK_WdtOsc);
#if !WDT_DISABLED_FOR_DEBUG
   WWDT_Init(WWDT, &config);
#endif
   NVIC_EnableIRQ(WDT_IRQn);
}

#endif /* PL_CONFIG_USE_WDT */
