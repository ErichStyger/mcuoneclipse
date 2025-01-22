/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_EXT_RTC
#include "extRTC.h"
#if PL_CONFIG_USE_PCF85063A
  #include "McuPCF85063A.h"
#endif
#include "McuRTOS.h"
#include "McuLog.h"
#include "power.h"

static SemaphoreHandle_t ExtRTC_Sem = NULL;

uint8_t ExtRTC_GetTime(TIMEREC *time) {
#if PL_CONFIG_USE_PCF85063A
  uint8_t res;

#if POWER_CONFIG_USE_EN_VCC2
  if (!Power_GetVcc2IsOn()) { /* bus not powered? */
    return McuTimeDate_GetSWTimeDate(time, NULL); /* use SW RTC info */
  }
#endif
  if (xSemaphoreTake(ExtRTC_Sem, 0)==pdTRUE) {
    res = McuPCF85063A_GetTime(time);
    (void)xSemaphoreGive(ExtRTC_Sem);
    return res;
  } else { /* cannot access bus, Vcc2 turned off? */
    return McuTimeDate_GetSWTimeDate(time, NULL); /* use SW RTC info */
  }
#else
  return McuTimeDate_GetSWTimeDate(time, NULL); /* use SW RTC info */
#endif
}

uint8_t ExtRTC_SetTimeInfo(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100) {
#if PL_CONFIG_USE_PCF85063A
  uint8_t res;

#if POWER_CONFIG_USE_EN_VCC2
  if (!Power_GetVcc2IsOn()) { /* bus not powered? */
    return ERR_OK; /* don't do anything, SW RTC is set by caller */
  }
#endif
  if (xSemaphoreTake(ExtRTC_Sem, 0)==pdTRUE) {
     res = McuPCF85063A_SetTimeInfo(Hour, Min, Sec, Sec100);
     (void)xSemaphoreGive(ExtRTC_Sem);
     return res;
   } else { /* cannot access bus, Vcc2 turned off? */
     return ERR_OK; /* don't do anything, SW RTC is set by caller */
   }
#else
  return ERR_OK; /* don't do anything, SW RTC is set by caller */
#endif
}

uint8_t ExtRTC_GetDate(DATEREC *date) {
#if PL_CONFIG_USE_PCF85063A
  uint8_t res;

#if POWER_CONFIG_USE_EN_VCC2
  if (!Power_GetVcc2IsOn()) { /* bus not powered? */
    return McuTimeDate_GetSWTimeDate(NULL, date); /* use SW RTC info */
  }
#endif
  if (xSemaphoreTake(ExtRTC_Sem, 0)==pdTRUE) {
    res = McuPCF85063A_GetDate(date);
    (void)xSemaphoreGive(ExtRTC_Sem);
    return res;
  } else {
    return McuTimeDate_GetSWTimeDate(NULL, date); /* use SW RTC info */
  }
#else
  return McuTimeDate_GetSWTimeDate(NULL, date); /* use SW RTC info */
#endif
}

uint8_t ExtRTC_SetDateInfo(uint16_t Year, uint8_t Month, uint8_t Day) {
#if PL_CONFIG_USE_PCF85063A
  uint8_t res;

#if POWER_CONFIG_USE_EN_VCC2
  if (!Power_GetVcc2IsOn()) { /* bus not powered? */
    return ERR_OK; /* don't do anything, SW RTC is set by caller */
  }
#endif
  if (xSemaphoreTake(ExtRTC_Sem, 0)==pdTRUE) {
    res = McuPCF85063A_SetDateInfo(Year, Month, Day);
    (void)xSemaphoreGive(ExtRTC_Sem);
    return res;
  } else {
    return ERR_OK; /* don't do anything, SW RTC is set by caller */
  }
#else
  return ERR_OK; /* don't do anything, SW RTC is set by caller */
#endif
}

void ExtRTC_Suspend(void) {
  if (xSemaphoreTake(ExtRTC_Sem, portMAX_DELAY)!=pdTRUE) {
    McuLog_fatal("failed getting semaphore");
  }
}

void ExtRTC_Resume(void) {
  if (xSemaphoreGive(ExtRTC_Sem)!=pdTRUE) {
    McuLog_fatal("failed giving semaphore");
  }
}

void ExtRTC_Deinit(void) {
  vSemaphoreDelete(ExtRTC_Sem);
  ExtRTC_Sem = NULL;
}

void ExtRTC_Init(void) {
  ExtRTC_Sem = xSemaphoreCreateBinary(); /* semaphore is created 'empty' */
  if (ExtRTC_Sem==NULL) {
    McuLog_fatal("failed creating semaphore");
    for(;;) {}
  }
  if (xSemaphoreGive(ExtRTC_Sem)!=pdTRUE) { /* 'give' it first, so we can take it */
    McuLog_fatal("failed giving semaphore");
  }
  vQueueAddToRegistry(ExtRTC_Sem, "ExtRTC_Sem");
#if PL_CONFIG_USE_PCF85063A
  McuPCF85063A_Init();
#else
  return ERR_FAILED;
#endif
}
#endif /* PL_CONFIG_USE_EXT_RTC */
