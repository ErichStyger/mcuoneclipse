/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "leds.h"
#if PL_CONFIG_USE_WS2812B
  #include "NeoPixel.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif

#if PL_CONFIG_USE_WS2812B
static void test(void) {
  uint8_t r, g, b, w;
#define MIN_VAL  1  /* miniumum brightness */
#if NEOC_NOF_LEDS>8
  #define MAX_VAL  80 /* maximum brightness */
#else
  #define MAX_VAL  150 /* maximum brightness */
#endif

  (void)NEO_ClearAllPixel();
  for(;;) {
    r = g = b = w = 0;
    for(r=MIN_VAL; r<=MAX_VAL; r++) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }
    for(r=MAX_VAL; r>=MIN_VAL; r--) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }

    r = g = b = w = 0;
    for(g=MIN_VAL; g<=MAX_VAL; g++) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }
    for(g=MAX_VAL; g>=MIN_VAL; g--) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }

    r = g = b = w = 0;
    for(b=MIN_VAL; b<=MAX_VAL; b++) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }
    for(b=MAX_VAL; b>=MIN_VAL; b--) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }

    r = g = b = w = 0;
    for(w=MIN_VAL; w<=MAX_VAL; w++) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }
    for(w=MAX_VAL; w>=MIN_VAL; w--) {
      for(int pos=0; pos<NEO_NOF_PIXEL; pos++) {
        (void)NEO_SetPixelRGBW(pos, r, g, b, w);
      }
      (void)NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(20));
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void neo(void *pv) {
  for(;;) {
    test();
  }
}
#endif /* PL_CONFIG_USE_WS2812B */

static void blinky(void *pv) {
  for(;;) {
    LEDS_Neg(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(500));
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

static void GetUID(void) {
  McuArmTools_UID uid;

  McuArmTools_UIDGet(&uid);
}

void APP_Run(void) {
  PL_Init();
#if PL_CONFIG_USE_MININI
  {
    int counter;
    /* some test code */
    counter = McuMinINI_ini_getl("app", "cnt", 5, "settings.ini");
    if (counter==0) {
      McuMinINI_ini_putl("app", "cnt", 3, "settings.ini");
    }
  }
#endif
  GetUID();
  for(int i=0; i<3; i++) {
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_GREEN);
    LEDS_On(LEDS_RED);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(500);
  }
  if (xTaskCreate(blinky, "blinky", 400/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    for(;;) {}
  }
#if PL_CONFIG_USE_WS2812B
  if (xTaskCreate(neo, "neo", 400/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    for(;;) {}
  }
#endif
  vTaskStartScheduler();
}
