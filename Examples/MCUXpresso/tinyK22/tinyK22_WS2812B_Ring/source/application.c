/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "platform.h"
#include "leds.h"
#include "fsl_pit.h"
#include "NeoPixel.h"
#include "stepper.h"
#include "NeoStepperRing.h"
#include "matrix.h"

#if PL_CONFIG_USE_SHELL
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}
#endif

typedef enum {
  NEO_POS_LOW_12 = 0,
  NEO_POS_LOW_3 = 10,
  NEO_POS_LOW_6 = 20,
  NEO_POS_LOW_9 = 30,
  NEO_POS_HIGH_12 = 40,
  NEO_POS_HIGH_9 = 50,
  NEO_POS_HIGH_6 = 60,
  NEO_POS_HIGH_3 = 70,
} NEO_POS_e;

#define TEST_MODE  (0)

static void AppTask(void *pv) {
  //int i = 0;
  //int color = 0;
  //uint8_t level;

  vTaskDelay(pdMS_TO_TICKS(1000)); /* wait a second to turn on the LEDs, just to avoid the current rush with the motors */
  NEO_ClearAllPixel();
#if 0 && PL_CONFIG_USE_NEO_PIXEL
  NEO_ClearAllPixel();
  NEO_TransferPixels();
  //NEO_SetPixelRGB(0, 0, 0x00, 0xff, 0x00);

  NEO_SetPixelRGB(0, 0, 0x00, 0xff/8, 0x00);
  NEO_TransferPixels();

  NEO_SetPixelRGB(0, 20, 0x00, 0xff/8, 0x00);
  NEO_TransferPixels();

  NEO_SetPixelRGB(0, 40+5, 0xff/8, 0x00, 0);
  NEO_TransferPixels();

  NEO_SetPixelRGB(0, 40+5+20, 0xff/8, 0, 0);
  NEO_TransferPixels();

  NEO_TransferPixels();


  NEO_ClearAllPixel();
  NEO_SetPixelRGB(0, 0, 0x00, 0, 0xff/8);
  NEO_SetPixelRGB(0, 20, 0x00, 0, 0xff/8);
  NEO_SetPixelRGB(0, 40+30, 0x00, 0, 0xff/8);
  NEO_TransferPixels();

  /* 12-6 both levels */
  NEO_ClearAllPixel();
  NEO_SetPixelRGB(0, NEO_POS_LOW_12, 0x00, 0, 0xff); /* 12 lower */
  NEO_SetPixelRGB(0, NEO_POS_LOW_6, 0x00, 0, 0xff); /* 6 lower */
  NEO_SetPixelRGB(0, NEO_POS_HIGH_12, 0x00, 0, 0xff); /* 12 upper */
  NEO_SetPixelRGB(0, NEO_POS_HIGH_6, 0x00, 0, 0xff); /* 6 upper */
  NEO_TransferPixels();

//NEO_SetPixelRGB(0, 40+0+10, 0xff, 0, 0x00);
  //NEO_SetPixelRGB(0, 40+0+10+20, 0xff/8, 0, 0x00);
#endif

  int i = 0;
  NEO_ClearAllPixel();

#if 1 && TEST_MODE && PL_CONFIG_USE_NEO_PIXEL  /* testing a ring */
  uint8_t cR, cG, cB;

  cR = 0x10;
  cG = 0;
  cB = 0;
  i = 0;
  for(;;) {
    NEO_ClearAllPixel();
    for(int lane=0; lane<NEOC_NOF_LANES; lane++) {
      NEO_SetPixelRGB(lane, i, cR, cG, cB);
    }
  //  i++;
  //  if (i==40/*NEOC_NOF_LEDS_IN_LANE*/) {
  //    i = 0;
  //  }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(20));
  }
#endif

#if 0 && TEST_MODE && PL_CONFIG_USE_NEO_PIXEL  /* testing a ring */
  uint8_t cR, cG, cB;

  cR = 0x10;
  cG = 0x10;
  cB = 0x10;
  for(;;) {
    NEO_ClearAllPixel();
    for(int lane=0; lane<NEOC_NOF_LANES; lane++) {
      NEO_SetPixelRGB(lane, i, cR, cG, cB);
    }
    i++;
    if (i==40/*NEOC_NOF_LEDS_IN_LANE*/) {
      i = 0;
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
#endif

#if 0 && TEST_MODE && PL_CONFIG_USE_NEO_PIXEL  /* testing a ring */
  for(;;) {
   for(int lane=0; lane<NEOC_NOF_LANES; lane++) {
     NEO_SetPixelRGB(lane, i, 0xff/16, 0x00, 0x00);
   }
   //NEO_SetPixelRGB(0, 0, 0x00, 0xff, 0x00);
   //NEO_SetPixelRGB(0, 1, 0, 0xff, 0x00);
   //NEO_SetPixelRGB(0, 2, 0, 0x00, 0xff/4);
   //NEO_SetPixelRGB(0, 3, 0xff/4, 0x00, 0x00);
   //NEO_SetPixelRGB(0, 4, 0x00, 0xff/4, 0x00);
   //if (color==0) {
   //  NEO_SetPixelRGB(0, i, 0xff/4, 0x00, 0x00);
   //} else if (color==1) {
   //  NEO_SetPixelRGB(0, i, 0x00, 0xff/4, 0x00);
   //} else if (color==2) {
   //  NEO_SetPixelRGB(0, i, 0x00, 0x00, 0xff/4);
   //}
//   if (i>0) {
//     NEO_SetPixelRGB(0, i-1, 0x00, 0x00, 0x00); /* clear */
//   } else if (i==0) {
//     NEO_SetPixelRGB(0, NEOC_NOF_LEDS_IN_LANE-1, 0, 0x00, 0x00);
//   }
   i++;
   if (i==40/*NEOC_NOF_LEDS_IN_LANE*/) {
     i = 0;
   }
   NEO_TransferPixels();
   vTaskDelay(pdMS_TO_TICKS(50));
  }
#endif
  for(;;) {
#if 0 && PL_CONFIG_USE_NEO_PIXEL
    for(i=0, level=0x20; i<5; i++, level+=0xff/5) {
      NEO_ClearAllPixel();
      NEO_SetPixelRGB(0, NEO_POS_LOW_12, level, 0, 0);
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(2000));

      NEO_SetPixelRGB(0, NEO_POS_LOW_12, 0, level, 0);
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(2000));

      NEO_SetPixelRGB(0, NEO_POS_LOW_12, 0, 0, level);
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(2000));
    }

    for(i=0, level=0x20; i<5; i++, level+=0xff/5) {
      NEO_ClearAllPixel();
      NEO_SetPixelRGB(0, NEO_POS_LOW_12, level, 0, 0);
      NEO_SetPixelRGB(0, NEO_POS_LOW_6, level, 0, 0);
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(2000));
    }

    level = 0xff/5;
    NEO_ClearAllPixel();
    NEO_SetPixelRGB(0, NEO_POS_LOW_12, level, 0, 0);
    NEO_SetPixelRGB(0, NEO_POS_LOW_6, 0, level, 0);
    NEO_SetPixelRGB(0, NEO_POS_HIGH_3, level, 0, 0);
    NEO_SetPixelRGB(0, NEO_POS_HIGH_9, 0, level, 0);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));

    level = 0xff/5;
    NEO_ClearAllPixel();
    NEO_SetPixelRGB(0, NEO_POS_LOW_12, 0, 0, level);
    NEO_SetPixelRGB(0, NEO_POS_LOW_6, level, level, 0);
    NEO_SetPixelRGB(0, NEO_POS_HIGH_3, 0, 0, level);
    NEO_SetPixelRGB(0, NEO_POS_HIGH_9, level, level, 0);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));

    level = 0xff/5;
    NEO_ClearAllPixel();
    NEO_SetPixelRGB(0, NEO_POS_LOW_12, 0, 0, level);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));
    NEO_SetPixelRGB(0, NEO_POS_HIGH_3, 0, 0, level);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));
    NEO_SetPixelRGB(0, NEO_POS_LOW_6, 0, 0, level);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));
    NEO_SetPixelRGB(0, NEO_POS_HIGH_9, 0, 0, level);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(2000));
#endif
    //(void)STEPPER_CheckAndExecuteQueue(McuShell_GetStdio());
#if !TEST_MODE && PL_CONFIG_USE_STEPPER_EMUL
    if (MATRIX_UpdateLed()) {
      NEO_ClearAllPixel();
      MATRIX_SetLEDs();
      NEO_TransferPixels();
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(20));
  } /* for */
}

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      900/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
