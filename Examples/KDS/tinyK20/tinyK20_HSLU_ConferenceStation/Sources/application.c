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
#include "LED_Mic.h"
#include "LED_Cam.h"
#include "KEY1.h"
#include "EVNT1.h"
#include "PORT_PDD.h"

static volatile bool sendMicMute = FALSE;
static volatile bool sendCamMute = FALSE;
static volatile bool sendPushToTalkOn = FALSE;
static volatile bool sendPushToTalkOff = FALSE;

static void UsbTask(void *pv) {
  bool camIsMuted = FALSE;
  bool micIsMuted = FALSE;

  USB1_Init();
  for(;;) {
    if (HIDK1_App_Task()==ERR_OK) { /* run the USB application task: this will send the buffer */
      /* connected */
    } else {
      /* disconnected */
    }
    if (sendMicMute) {
      sendMicMute = FALSE;
      micIsMuted = !micIsMuted;
      LED_Mic_Off();
     /* Send <Alt>+<A> to start/stop mic in Zoom */
      HIDK1_Send(MODIFERKEYS_LEFT_ALT, KEY_A); /* press key */
      HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
      /* or: send <space> to temporarily unmute */
    }
    if (sendCamMute) {
      sendCamMute = FALSE;
      camIsMuted = !camIsMuted;
      LED_Cam_Off();
      /* send <Alt>+<V> to start/stop video in Zoom */
      HIDK1_Send(MODIFERKEYS_LEFT_ALT, KEY_V);
      HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
    }
    if (sendPushToTalkOn) {
      /* send <SPACE> as push-to-talk in Zoom */
      sendPushToTalkOn = FALSE;
      HIDK1_Send(MODIFERKEYS_NONE, KEY_SPACEBAR); /* send <space> */
    } else if (sendPushToTalkOff) {
      sendPushToTalkOff = FALSE;
      HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release <space> */
    }
    if (micIsMuted) {
      LED_Mic_Neg();
    } else {
      LED_Mic_On();
    }
    if (camIsMuted) {
      LED_Cam_Neg();
    } else {
      LED_Cam_On();
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void APP_HandleEvent(uint8_t event) {
  switch(event) {
    case EVNT1_SW_MUTE_CAM_PRESSED:
      sendCamMute = TRUE;
      break;
    case EVNT1_SW_MUTE_MIC_PRESSED:
      sendMicMute = TRUE;
      break;
    case EVNT1_SW_MUTE_MIC_PRESSED_LONG:
      sendPushToTalkOn = TRUE;
      break;
    case EVNT1_SW_MUTE_CAM_PRESSED_LONG:
      break;
    case EVNT1_SW_MUTE_MIC_RELEASED_LONG:
      sendPushToTalkOff = TRUE;
      break;
    case EVNT1_SW_MUTE_CAM_RELEASED_LONG:
      break;
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    KEY1_ScanKeys();
    EVNT1_HandleEvent();
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

