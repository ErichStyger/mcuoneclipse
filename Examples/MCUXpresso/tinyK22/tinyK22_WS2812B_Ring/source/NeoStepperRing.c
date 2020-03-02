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
  .ledStartPos = 0
};

typedef struct {
  int pos; /* stepper motor position */
  bool ledCw;      /* clock-wise */
  int ledLane;     /* LED lane */
  int ledStartPos; /* LED starting position in lane */
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

void NEOSR_SetRotorPixel(NEOSR_Handle_t device) {
  int32_t pos;
  NEOSR_Device_t *dev = (NEOSR_Device_t*)device;

  pos = dev->pos;
  if (pos<0) {
    pos = -pos;
    pos %= NEOSR_NOF_360-1;
    pos = NEOSR_NOF_360-pos;
  }
  /* pos is now positive */
  pos %= NEOSR_NOF_360-1;
  if (pos<(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2) || pos>=(STEPPER_CLOCK_360_STEPS-STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2)) { /* less than half the distance */
    pos = 0;
  } else {
    pos -= (STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED/2);
    pos = pos/(STEPPER_CLOCK_360_STEPS/NEOSR_NOF_LED) + 1;
  }
  /* pos is now the LED position on the ring */
  if (dev->ledCw) {
    pos = dev->ledStartPos + pos;
  } else {
    if (pos==0) {
      pos = dev->ledStartPos;
    } else {
      pos = dev->ledStartPos + NEOSR_NOF_LED - pos;
    }
  }
  NEO_SetPixelRGB(dev->ledLane, pos, 0x00, 0xff/8, 0x00);
}

void NEOSR_Init(void) {
  /* tbd */
}
