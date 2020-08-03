/*
 * application.c
 *
 *  Created on: 03.08.2020
 *      Author: Erich Styger
 */

#include "application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "USB1.h"
#include "HIDK1.h"
#include "KEY1.h"
#include "PORT_PDD.h"

static bool sendMicMute = FALSE;
static bool sendCamMute = FALSE;

static void UsbTask(void *pv) {
  USB1_Init();
  for(;;) {
    if (HIDK1_App_Task()==ERR_OK) { /* run the USB application task: this will send the buffer */
      /* connected */
    } else {
      /* disconnected */
    }
    if (sendMicMute) {
      sendMicMute = FALSE;
      /* send print screen */
      HIDK1_Send(MODIFERKEYS_NONE, KEY_PRINTSCREEN);
      HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    KEY1_ScanKeys();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static void AppTask(void *pv) {
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  /* enable pull-ups for push buttons */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 1, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 2, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 2, PORT_PDD_PULL_ENABLE);

  if (xTaskCreate(UsbTask, "Usb", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (xTaskCreate(BtnTask, "Btn", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
  for(;;) {
    __asm("nop");
  }
}

