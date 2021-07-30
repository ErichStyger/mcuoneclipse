/*
 * Copyright (c) 2019, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_BUTTON
  #include "buttons.h"
#endif
#include "leds.h"
#include "Shell.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_STEPPER
  #include "stepper.h"
#endif
#if PL_CONFIG_USE_HALL_SENSOR
  #include "magnets.h"
#endif

static bool clockIsOn = false;

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  clock", clockIsOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  clock on|off", (unsigned char*)"Enable or disable the clock\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "app help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "app status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "app clock on")==0) {
    *handled = true;
    clockIsOn = true;
  } else if (McuUtility_strcmp((char*)cmd, "app clock off")==0) {
    *handled = true;
    clockIsOn = false;
  }
  return ERR_OK;
}

#if PL_CONFIG_USE_HALL_SENSOR
static void SensorTask(void *pv) {
  bool mmMag;
  int32_t pos, prevPos = -1;
  uint8_t buf[32];

  for(;;) {
    mmMag = MAG_TriggeredMM();
    if (mmMag) {
      pos = STEPPER_GetPos();
      if (pos!=prevPos) {
        prevPos = pos;
        McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"zero pos:");
        McuUtility_strcatNum32s(buf, sizeof(buf), pos%512);
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\n");
        SHELL_SendString(buf);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}
#endif

static void AppTask(void *pv) {
  uint8_t oldHH=-1, oldMM = -1;
  TIMEREC time;

  SHELL_SendString((unsigned char*)"\r\n***************************\r\n* LPC845-BRK FlipFlap     *\r\n***************************\r\n");
  //(void)STEPPER_ZeroHourHand();
  (void)STEPPER_ZeroMinuteHand();
  vTaskDelay(pdMS_TO_TICKS(1000)); /* wait initializing external RTC below in PL_InitFromTask(), because it needs time to power up */
  PL_InitFromTask();
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(200));
    if (clockIsOn) {
      McuTimeDate_GetTime(&time);
      if (time.Hour!=oldHH || time.Min != oldMM) {
#if PL_CONFIG_USE_STEPPER
        STEPPER_ShowTime(time.Hour, time.Min);
#endif
        oldHH = time.Hour;
        oldMM = time.Min;
      }
    }
  }
}

void APP_Run(void) {
	PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
#if PL_CONFIG_USE_HALL_SENSOR
  if (xTaskCreate(
      SensorTask,  /* pointer to the task */
      "Sensor", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
#endif
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
