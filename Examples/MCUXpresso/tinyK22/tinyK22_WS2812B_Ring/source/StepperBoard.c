/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "StepperBoardConfig.h"
#include "StepperBoard.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>
#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

typedef struct {
  uint8_t addr;
  bool enabled;
} STEPBOARD_Device_t;

/* default configuration, used for initializing the config */
static const STEPBOARD_Config_t defaultConfig =
{
  .addr = 0x0, .enabled = true
};

void STEPBOARD_GetDefaultConfig(STEPBOARD_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

STEPBOARD_Handle_t STEPBOARD_InitDevice(STEPBOARD_Config_t *config) {
  STEPBOARD_Device_t *handle;

#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  handle = (STEPBOARD_Device_t*)pvPortMalloc(sizeof(STEPBOARD_Device_t)); /* get a new device descriptor */
#else
  handle = (STEPBOARD_Device_t*)malloc(sizeof(STEPBOARD_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(STEPBOARD_Device_t)); /* init all fields */
    handle->addr = config->addr;
    handle->enabled = config->enabled;
  }
  return handle;
}

uint8_t STEPBOARD_GetAddress(STEPBOARD_Handle_t device) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)device;
  return handle->addr;
}

bool STEPBOARD_IsEnabled(STEPBOARD_Handle_t device) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)device;
  return handle->enabled;
}

STEPBOARD_Handle_t STEPBOARD_DeinitDevice(STEPBOARD_Handle_t device) {
#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  vPortFree(device);
#else
  free(device);
#endif
  return NULL;
}

void STEPBOARD_Deinit(void) {
}

void STEPBOARD_Init(void) {
}
