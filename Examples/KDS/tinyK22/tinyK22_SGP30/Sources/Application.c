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
  vTaskStartScheduler();
  for(;;) {
    __asm("nop"); /* should not get here! */
  }
}

