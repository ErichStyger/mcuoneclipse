/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "NeoStepperRingConfig.h"
#include "NeoStepperRing.h"
#include "stepper.h"
#include "NeoPixel.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#if NEOSR_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

#define NEOSR_NOF_LED        (40)  /* number of LEDs in ring */
#define NEOSR_NOF_360        (STEPPER_CLOCK_360_STEPS) /* number of steps for 360 degree */
#define NEOSR_STEPS_FOR_LED  (NEOSR_NOF_360/NEOSR_NOF_LED) /* number of steps for each LED */
#define NEOSR_LED_WIDTH      (NEOSR_STEPS_FOR_LED + 50) /* width for LED */

/* default configuration, used for initializing the config */
static const NEOSR_Config_t defaultConfig =
{
  .ledCw = true,
  .ledLane = 0,
  .ledStartPos = 0,
  .ledRed = 0,
  .ledGreen = 0,
  .ledBlue = 0,
};

/* device for a single LED ring */
typedef struct {
  //int pos; /* stepper motor position */ /*!\todo needed? have it in the stepper */
  bool ledCw;      /* clock-wise */
  int ledLane;     /* LED lane */
  int ledStartPos; /* LED starting position in lane */
  uint8_t ledRed, ledGreen, ledBlue; /* colors */
} NEOSR_Device_t;

void NEOSR_GetDefaultConfig(NEOSR_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

NEOSR_Handle_t NEOSR_DeinitDevice(NEOSR_Handle_t device) {
#if NEOSR_CONFIG_USE_FREERTOS_HEAP
  vPortFree(device);
#else
  free(device);
#endif
  return NULL;
}

NEOSR_Handle_t NEOSR_InitDevice(NEOSR_Config_t *config) {
  NEOSR_Device_t *handle;

#if NEOSR_CONFIG_USE_FREERTOS_HEAP
  handle = (NEOSR_Device_t*)pvPortMalloc(sizeof(NEOSR_Device_t)); /* get a new device descriptor */
#else
  handle = (NEOSR_Device_t*)malloc(sizeof(NEOSR_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(NEOSR_Device_t)); /* init all fields */
//    handle->pos = 0;
    handle->ledCw = config->ledCw;
    handle->ledLane = config->ledLane;
    handle->ledStartPos = config->ledStartPos;
    handle->ledRed = config->ledRed;
    handle->ledGreen = config->ledGreen;
    handle->ledBlue = config->ledBlue;
  }
  return handle;
}

//int32_t NEOSR_GetPos(NEOSR_Handle_t device) {
//  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;
//  return dev->pos;
//}

//void NEOSR_SetPos(NEOSR_Handle_t device, int32_t pos) {
//  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;
//  dev->pos = pos;
//}

//void NEOSR_SingleStep(NEOSR_Handle_t device, int step) {
//  NEOSR_Device_t *handle = (NEOSR_Device_t*)device;
//
//  handle->pos += step;
//}

/* return a scale between 0 and 0xff, depending on how much there is an overlap */
static int ScaleRange(int ledPos, int startPos, int endPos) {
  int percentage, diff;
  int a, b;

  if (startPos<0) {
    startPos += STEPPER_CLOCK_360_STEPS; /* make it positive */
    endPos += STEPPER_CLOCK_360_STEPS; /* adjust end pos too */
    ledPos += NEOSR_NOF_LED;
  }
  if (ledPos<0) {
    ledPos = NEOSR_NOF_LED+ledPos;
  }
  /* calculate start and end position of LED */
  a = ledPos*NEOSR_STEPS_FOR_LED;
  b = a+NEOSR_STEPS_FOR_LED-1;
  /* match start and end to a and b */
  if (a>=startPos && a<=endPos) {
    startPos = a;
  }
  if (b>=startPos && b<=endPos) {
    endPos = b;
  }
  if (b>=startPos && a<=endPos) { /* they do overlap */
    diff = endPos-startPos+1;
    percentage = diff*0xff/NEOSR_STEPS_FOR_LED;
  } else {
    percentage = 0; /* no overlap */
  }
  return percentage;
}

void NEOSR_IlluminatePos(int stepperPos, int ledLane, int ledStartPos, bool cw, int ledRed, int ledGreen, int ledBlue) {
  int ledPos, pos;
  int dist[3];

  stepperPos += NEOSR_STEPS_FOR_LED/2; /* adjust by half a LED, because 0 is at the middle of the 12-o-clock LED */
  /* make stepperPos fit within 0...NEOSR_NOF_360 */
  if (stepperPos<0) {
    stepperPos = -stepperPos;
    stepperPos %= NEOSR_NOF_360;
    stepperPos = NEOSR_NOF_360-stepperPos;
  }
  /* stepperPos is now positive */
  stepperPos %= NEOSR_NOF_360;
  /* stepperPos is now within 0..NEOSR_NOF_360 */
  ledPos = stepperPos/NEOSR_STEPS_FOR_LED;
  /*
   *  stepper pos  ... 4319 | 0 107 | 108 | ...
   *  led pos                    53|54-161 | 162..(+108) |
   *  led index        39       0        1
   */
  dist[0] = ScaleRange(ledPos-1, stepperPos-NEOSR_LED_WIDTH/2, stepperPos+NEOSR_LED_WIDTH/2-1);
  dist[1] = ScaleRange(ledPos, stepperPos-NEOSR_LED_WIDTH/2, stepperPos+NEOSR_LED_WIDTH/2-1);
  dist[2] = ScaleRange(ledPos+1, stepperPos-NEOSR_LED_WIDTH/2, stepperPos+NEOSR_LED_WIDTH/2-1);

  uint8_t r,g,b;

  /* perform a gamma correction */
  r = NEO_GammaCorrect8(ledRed*dist[0]/0xff);
  g = NEO_GammaCorrect8(ledGreen*dist[0]/0xff);
  b = NEO_GammaCorrect8(ledBlue*dist[0]/0xff);
  pos = ledPos-1;
  if (pos<0) {
    pos = NEOSR_NOF_LED-1;
  }
  if (!cw && pos!=0) { /* counter-clockwise order of LEDs */
    pos = NEOSR_NOF_LED-pos;
  }
  NEO_OrPixelRGB(ledLane, ledStartPos+pos, r, g, b);

  r = NEO_GammaCorrect8(ledRed*dist[1]/0xff);
  g = NEO_GammaCorrect8(ledGreen*dist[1]/0xff);
  b = NEO_GammaCorrect8(ledBlue*dist[1]/0xff);
  pos = ledPos;
  if (!cw && pos!=0) { /* counter-clockwise order of LEDs */
    pos = NEOSR_NOF_LED-pos;
  }
  NEO_OrPixelRGB(ledLane, ledStartPos+pos, r, g, b);

  r = NEO_GammaCorrect8(ledRed*dist[2]/0xff);
  g = NEO_GammaCorrect8(ledGreen*dist[2]/0xff);
  b = NEO_GammaCorrect8(ledBlue*dist[2]/0xff);
  pos = ledPos+1;
  if (pos>NEOSR_NOF_LED-1) {
    pos = 0;
  }
  if (!cw && pos!=0) { /* counter-clockwise order of LEDs */
    pos = NEOSR_NOF_LED-pos;
  }
  if (r!=0 || g!=0 || b!=0) { /* ORing makes only sense if it is not zero */
    NEO_OrPixelRGB(ledLane, ledStartPos+pos, r, g, b);
  }
}

void NEOSR_SetRotorColor(NEOSR_Handle_t device, uint8_t red, uint8_t green, uint8_t blue) {
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;

  dev->ledRed = red;
  dev->ledGreen = green;
  dev->ledBlue = blue;
}

void NEOSR_SetRotorPixel(NEOSR_Handle_t device, int32_t stepperPos) {
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;

  NEOSR_IlluminatePos(stepperPos, dev->ledLane, dev->ledStartPos, dev->ledCw, dev->ledRed, dev->ledGreen, dev->ledBlue);
}

void NEOSR_Deinit(void) {
  /* nothing needed */
}

void NEOSR_Init(void) {
  /* nothing needed */
}
