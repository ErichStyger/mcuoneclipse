/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BLINKY

#include "blinky.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "leds.h"

static TaskHandle_t taskHandle;
static bool blinkyIsRunning = false;

#define LED_OFF_TIME_MS    1000
static uint32_t onTimeMs = 10; /* default on time of LED */

void Blinky_SetOnTime(uint32_t ms) {
  onTimeMs = ms;
}

void Blinky_On(void) {
#if LEDS_CONFIG_HAS_RED_LED
  Leds_On(LEDS_CONFIG_HAS_RED_LED);
#endif
}

void Blinky_Off(void) {
#if LEDS_CONFIG_HAS_RED_LED
  Leds_Off(LEDS_CONFIG_HAS_RED_LED);
#endif
}

void Blinky_Suspend(void) {
  if (taskHandle!=NULL) {
    vTaskSuspend(taskHandle);
    blinkyIsRunning = false;
    Blinky_Off();
  }
}

void Blinky_Resume(void) {
  if (taskHandle!=NULL) {
    vTaskResume(taskHandle);
    blinkyIsRunning = true;
  }
}

void Blinky_GetStatus(unsigned char *buf, size_t bufSize) {
  buf[0] = '\0';
  if (taskHandle!=NULL) {
    eTaskState state;

    state = eTaskGetState(taskHandle);
    switch(state) {
    case eSuspended:
      McuUtility_strcpy(buf, bufSize, (unsigned char*)"suspended");
      break;
    case eRunning:
    case eBlocked:
      McuUtility_strcpy(buf, bufSize, (unsigned char*)"running");
      break;
    default:
    case eDeleted:
      McuUtility_strcpy(buf, bufSize, (unsigned char*)"ERROR!");
      break;
    }
  } else {
    McuUtility_strcpy(buf, bufSize, (unsigned char*)"ERROR: no task!");
  }
}

static void blinkyTask(void *pv) {
  (void)pv;
  blinkyIsRunning = true;
  McuLog_info("started blinky task");
  for(;;) {
#if 0
    LED_On();
    vTaskDelay(pdMS_TO_TICKS(onTimeMs));
    LED_Off();
    vTaskDelay(pdMS_TO_TICKS(LED_OFF_TIME_MS));
#endif
#if LEDS_CONFIG_HAS_RED_LED
    Leds_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
    Leds_Neg(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(100));
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
    Leds_Neg(LEDS_BLUE);
    vTaskDelay(pdMS_TO_TICKS(100));
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED
    Leds_Neg(LEDS_ONBOARD);
    vTaskDelay(pdMS_TO_TICKS(100));
#endif
  }
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"blinky", (unsigned char*)"Blinky status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  status", blinkyIsRunning?(unsigned char*)"resumed\r\n":(unsigned char*)"suspended\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"blinky", (unsigned char*)"Group of blinky commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Show help or status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  suspend", (unsigned char*)"Suspend the blinky task\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  resume", (unsigned char*)"Resume the blinky task\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t Blinky_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"blinky help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"blinky status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)"blinky suspend")==0) {
    *handled = TRUE;
    Blinky_Suspend();
  } else if (McuUtility_strcmp((char*)cmd, (char*)"blinky resume")==0) {
    *handled = TRUE;
    Blinky_Resume();
  }
  return ERR_OK;
}
#endif /* PL_CONFIG_USE_SHELL */

void Blinky_Deinit(void) {
}

void Blinky_Init(void) {
  BaseType_t res;
  res = xTaskCreate(blinkyTask, "blinkyTask", 4*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY, &taskHandle);
  if (res!=pdPASS) {
    McuLog_fatal("failed creating blinky!");
  }
}

#endif /* PL_CONFIG_USE_BLINKY */
