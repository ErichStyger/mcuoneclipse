/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "buttons.h"
#include "leds.h"
#include "Shell.h"
#if PL_CONFIG_USE_HALL_SENSOR
  #include "magnets.h"
#endif

static bool clockIsOn = true;

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

static void AppTask(void *pv) {
#if PL_CONFIG_USE_HALL_SENSOR
  bool mmMag, hhMag;
#endif

  PL_InitFromTask();
  SHELL_SendString((unsigned char*)"\r\n***************************\r\n* LPC845-BRK StepperClock *\r\n***************************\r\n");
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(200));
  #if PL_CONFIG_USE_HALL_SENSOR
    mmMag = MAG_TriggeredHH();
    hhMag = MAG_TriggeredMM();
    if (mmMag) {
      McuLED_Toggle(LEDS_Red);
    } else {
      McuLED_Off(LEDS_Red);
    }
    if (hhMag) {
      McuLED_Toggle(LEDS_Blue);
    } else {
      McuLED_Off(LEDS_Blue);
    }
    if (!mmMag && !hhMag) {
      McuLED_Toggle(LEDS_Green);
    } else {
      McuLED_Off(LEDS_Green);
    }
  #else
    McuLED_Toggle(LEDS_Green);
  #endif
  }
}

void APP_Run(void) {
	PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
