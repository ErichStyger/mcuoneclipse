/*
 * Application.c
 *
 *  Created on: 30.09.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LED1.h"
#include "Shell.h"
#include "CLS1.h"
#include "TRG1.h"
#include "TMOUT1.h"
#if PL_CONFIG_HAS_TSL2561
  #include "TSL1.h"
#endif
#if PL_CONFIG_HAS_SGP30
  #include "SGP30.h"
#endif
#if PL_CONFIG_HAS_RTC_DS3231
  #include "TmDt1.h"
#endif
#if PL_CONFIG_HAS_SGP30
  #include "SGP30.h"
#endif
#if PL_CONFIG_HAS_GUI
  #include "lvgl/lvgl.h"
  #include "lv.h"
  #include "gui.h"
#endif

#define APP_PERIODIC_TIMER_PERIOD_MS   10
#if TmDt1_TICK_TIME_MS!=APP_PERIODIC_TIMER_PERIOD_MS
  #error "Software RTC tick time has to match timer time"
#endif
#if TRG1_CONFIG_TICK_PERIOD_MS!=APP_PERIODIC_TIMER_PERIOD_MS
  #error "Trigger tick time has to match timer time"
#endif
#if TMOUT1_TICK_PERIOD_MS!=APP_PERIODIC_TIMER_PERIOD_MS
  #error "Timeout tick time has to match timer time"
#endif
static xTimerHandle timerHndl;

static void vTimerCallbackExpired(xTimerHandle pxTimer) {
#if PL_CONFIG_HAS_GUI
  lv_tick_inc(APP_PERIODIC_TIMER_PERIOD_MS);
#endif
  TRG1_AddTick();
  TMOUT1_AddTick();
  TmDt1_AddTick();
}

static void SensorTask(void *pv) {
#if PL_CONFIG_HAS_RTC_DS3231
  TmDt1_Init(); /* get time/date from external RTC */
#endif
#if PL_CONFIG_HAS_TSL2561
  uint8_t res;
  uint16_t tvoc, co2;
  uint16_t TVOC_base, eCO2_base;
  int cntr = 0;

  CLS1_SendStr("Enabling TLS2561 sensor.\r\n", CLS1_GetStdio()->stdOut);
  TSL1_Init();

  res = TSL1_Disable();
  vTaskDelay(pdMS_TO_TICKS(5));
  if (res!=ERR_OK) {
    for(;;){}
  }
  vTaskDelay(pdMS_TO_TICKS(50));
  res = TSL1_Enable();
  vTaskDelay(pdMS_TO_TICKS(5));
  if (res!=ERR_OK) {
    for(;;){}
  }

  res = TSL1_SetIntegrationTime(TSL2561_INTEGRATION_TIME_13MS);
  vTaskDelay(pdMS_TO_TICKS(5));
  if (res!=ERR_OK) {
    for(;;){}
  }
  res = TSL1_SetGain(TSL2561_GAIN_16X);
  if (res!=ERR_OK) {
    for(;;){}
  }
#endif
#if PL_CONFIG_HAS_SGP30
   CLS1_SendStr("Enabling SGP30 sensor.\r\n", CLS1_GetStdio()->stdOut);
   SGP30_Init();
#endif

  for(;;) {
    res = SGP30_IAQmeasure(&tvoc, &co2);
    if (res!=ERR_OK) {
      CLS1_SendStr("Failed SGP30_IAQmeasure()!\r\n", CLS1_GetStdio()->stdErr);
    } else {
      CLS1_printfIO(CLS1_GetStdio(), "TVOC %5d ppb, eCO2 %5d ppm\n", tvoc, co2);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    cntr++;
    if (cntr==30) {
      cntr = 0;
      res = SGP30_GetIAQBaseline(&TVOC_base, &eCO2_base);
      if (res!=ERR_OK) {
        CLS1_SendStr("Failed SGP30_GetIAQBaseline()!\r\n", CLS1_GetStdio()->stdErr);
      } else {
        CLS1_printfIO(CLS1_GetStdio(), "*** Baseline TVOC: 0x%4x, eCO2 0x%4x\n", TVOC_base, eCO2_base);
      }
    }
  }
}

static void AppTask(void *pv) {
  (void)pv;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  SHELL_Init();
#if PL_CONFIG_HAS_GUI
  GUI_Init();
#endif
  if (xTaskCreate(
        SensorTask,  /* pointer to the task */
        "Sensor", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  timerHndl = xTimerCreate(
        "timer1Sec", /* name */
        pdMS_TO_TICKS(APP_PERIODIC_TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackExpired); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  vTaskStartScheduler();
  for(;;) {
    __asm("nop"); /* should not get here! */
  }
}

