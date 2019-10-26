/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"

#include "fsl_iocon.h"
#include "pin_mux.h"
#include "leds.h"

#include "McuGenericI2C.h"

static void AppTask(void *pv) {
  for(;;) {
    McuLED_Toggle(LED_Green);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  PL_Init(); /* init modules */
  McuShell_SendStr((unsigned char*)"\r\n*** LPC55S69 with Adafruit LCD ***\r\n", McuShell_GetStdio()->stdOut);
#if 0 /* test code for LED */
  McuLED_On(LED_Red);
  McuWait_Waitms(100);
  McuLED_Off(LED_Red);

  McuLED_On(LED_Green);
  McuWait_Waitms(100);
  McuLED_Off(LED_Green);

  McuLED_On(LED_Blue);
  McuWait_Waitms(100);
  McuLED_Off(LED_Blue);
#endif
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
