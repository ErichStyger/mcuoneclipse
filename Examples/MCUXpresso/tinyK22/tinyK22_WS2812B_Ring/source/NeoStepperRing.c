/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "NeoStepperRingConfig.h"
#include "NeoStepperRing.h"
#include "stepper.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NEOSR_NOF_LED   (40)  /* number of LEDs in ring */
#define NEOSR_NOF_360   (STEPPER_CLOCK_360_STEPS) /* number of steps for 360 degree */

/* default configuration, used for initializing the config */
static const NEOSR_Config_t defaultConfig =
{
  .dummy = 0,
};

typedef struct {
  int pos;
} NEOSR_Device_t;

void NEOSR_GetDefaultConfig(NEOSR_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

NEOSR_Handle_t NEOSR_DeinitDevice(NEOSR_Handle_t device) {
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  vPortFree(device);
#else
  free(device);
#endif
  return NULL;
}

NEOSR_Handle_t NEOSR_InitDevice(NEOSR_Config_t *config) {
  NEOSR_Device_t *handle;

#if MCULED_CONFIG_USE_FREERTOS_HEAP
  handle = (McuLED_t*)pvPortMalloc(sizeof(McuLED_t)); /* get a new device descriptor */
#else
  handle = (NEOSR_Device_t*)malloc(sizeof(NEOSR_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(NEOSR_Device_t)); /* init all fields */
    handle->pos = 0;
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

void NEOSR_Init(void) {
  /* tbd */
}
