/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "virtual_com.h"

static void echoTask(void *pv) {
  unsigned char ch;

  for(;;) {
    if (USB_CdcStdio.keyPressed()) {
      do {
        USB_CdcStdio.stdIn(&ch);
        if (ch!='\0') {
          USB_CdcStdio.stdOut(ch); /* echo */
        }
      } while(USB_CdcStdio.keyPressed());
    } else {
      vTaskDelay(pdMS_TO_TICKS(2)); /* give back some time */
    }
  }
}

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  PL_Init();
  if (xTaskCreate(
      echoTask,  /* pointer to the task */
      "echo", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {
  }
  return 0;
}



