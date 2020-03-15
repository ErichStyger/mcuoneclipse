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

#define NEOSR_NOF_LED   (40)  /* number of LEDs in ring */
#define NEOSR_NOF_360   (STEPPER_CLOCK_360_STEPS) /* number of steps for 360 degree */

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

typedef struct {
  int pos; /* stepper motor position */
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
    handle->pos = 0;
    handle->ledCw = config->ledCw;
    handle->ledLane = config->ledLane;
    handle->ledStartPos = config->ledStartPos;
    handle->ledRed = config->ledRed;
    handle->ledGreen = config->ledGreen;
    handle->ledBlue = config->ledBlue;
  }
  return handle;
}

int32_t NEOSR_GetPos(NEOSR_Handle_t device) {
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;
  return dev->pos;
}

void NEOSR_SetPos(NEOSR_Handle_t device, int32_t pos) {
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;
  dev->pos = pos;
}

void NEOSR_SingleStep(NEOSR_Handle_t device, int step) {
  NEOSR_Device_t *handle = (NEOSR_Device_t*)device;

  handle->pos += step;
}

static void NEOSR_SetPixels(NEOSR_Device_t *dev, int32_t centerPos, uint8_t trailPercent, uint8_t centerPercent, uint8_t headPercent) {
  int32_t pos;

  /* trailing */
  if (trailPercent!=0) {
    if (dev->ledCw) {
      pos = centerPos-1;
      if (pos < dev->ledStartPos) {
        pos = pos+NEOSR_NOF_LED-1;
      }
    } else {
      pos = centerPos+1;
      if (pos > dev->ledStartPos+NEOSR_NOF_LED-1) {
        pos = dev->ledStartPos;
      }
    }
    NEO_SetPixelRGB(dev->ledLane, pos, dev->ledRed*100/trailPercent, dev->ledGreen*100/trailPercent, dev->ledBlue*100/trailPercent);
  }
  /* center */
  if (centerPercent!=0) {
    NEO_SetPixelRGB(dev->ledLane, centerPos, dev->ledRed*100/centerPercent, dev->ledGreen*100/centerPercent, dev->ledBlue*100/centerPercent);
  }
  /* head */
  if (headPercent!=0) {
    if (dev->ledCw) {
      pos = centerPos+1;
      if (pos > dev->ledStartPos+NEOSR_NOF_LED-1) {
        pos = dev->ledStartPos;
      }
    } else {
      pos = centerPos-1;
      if (pos < dev->ledStartPos) {
        pos = dev->ledStartPos+NEOSR_NOF_LED-1;
      }
    }
    NEO_SetPixelRGB(dev->ledLane, pos, dev->ledRed*100/headPercent, dev->ledGreen*100/headPercent, dev->ledBlue*100/headPercent);
  }
}

static void Illuminate(NEOSR_Handle_t device) {
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;
  int ledPos;
  int pos;

  pos = dev->pos;
  /* make pos fit within 0...NEOSR_NOF_360 */
  if (pos<0) {
    pos = -pos;
    pos %= NEOSR_NOF_360;
    pos = NEOSR_NOF_360-pos;
  }
  /* pos is now positive */
  pos %= NEOSR_NOF_360;
  /* pos is now within 0..NEOSR_NOF_360 */
  ledPos = pos/(NEOSR_NOF_360/NEOSR_NOF_LED);

  ledPos = dev->ledStartPos + pos;
  /*
   *  stepper pos  ... 4319 | 0 107 | 108 | ...
   *  led pos                    53|54-161 | 162..(+108) |
   *  led index        39       0        1
   *
   */
  NEO_SetPixelRGB(dev->ledLane, ledPos, dev->ledRed, dev->ledGreen, dev->ledBlue);
}

void NEOSR_SetRotorPixel(NEOSR_Handle_t device) {
  Illuminate(device);
#if 0
  int32_t pos, rotorPos;
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;


  rotorPos = dev->pos;
  if (rotorPos<0) {
    rotorPos = -rotorPos;
    rotorPos %= NEOSR_NOF_360;
    rotorPos = NEOSR_NOF_360-rotorPos;
  }
  /* pos is now positive */
  rotorPos %= NEOSR_NOF_360;
  if (rotorPos<(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2) || rotorPos>=(STEPPER_CLOCK_360_STEPS-STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2)) { /* less than half the distance */
    pos = 0;
  } else {
    pos = rotorPos-(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2);
    pos = pos/(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED) + 1;
  }
#if 1
  /* distribute color */
  int x, d, p;

  x = pos*STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED;
  d = rotorPos-x; /* difference */
  if (d<0) {  /* LED is ahead: dimm trailing */
    p = (-d*100)/(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED);
  } else { /* LED is behind: dim the one ahead */
    p = (d*100)/(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED);
  }
#endif
  /* pos is now the LED position on the ring. pos2 is for the dimmed one */
  if (dev->ledCw) {
    pos = dev->ledStartPos + pos;
  } else {
    if (pos==0) {
      pos = dev->ledStartPos;
    } else {
      pos = dev->ledStartPos + NEOSR_NOF_LED - pos;
    }
  }
#if 1
  if (d>0) { /* led pos behind */
    NEOSR_SetPixels(dev, pos, 0, 100-p, p);
  } else { /* led pos ahead */
    NEOSR_SetPixels(dev, pos, p, 100-p, 0);
  }
#else
  NEO_SetPixelRGB(dev->ledLane, pos, dev->ledRed, dev->ledGreen, dev->ledBlue);
#endif
#endif
}

void NEOSR_Init(void) {
  /* tbd */
}
