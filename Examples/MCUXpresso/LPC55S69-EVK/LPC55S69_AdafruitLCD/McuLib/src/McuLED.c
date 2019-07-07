/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for LEDs
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLibconfig.h"
#include "McuLEDconfig.h"
#include "McuLED.h"
#include "McuGPIO.h"
#include "fsl_gpio.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#endif
#include <stddef.h>
#include <string.h> /* for memset */
#include <stdlib.h> /* for malloc() and free() */
#include <assert.h>
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuLED_Config_t defaultConfig =
{
    .isLowActive = false,
    .isOnInit = false,
    .hw = {
      .gpio = NULL,
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    }
};

typedef struct {
  McuGPIO_Handle_t gpio;
  bool isLowActive;
} McuLED_t;

void McuLED_GetDefaultConfig(McuLED_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

McuLED_Handle_t McuLED_InitLed(McuLED_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuGPIO_Handle_t gpio;
  McuLED_t *handle;

  assert(config!=NULL);
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* LED is output only */
  gpio_config.hw.gpio = config->hw.gpio;
  gpio_config.hw.port = config->hw.port;
  gpio_config.hw.pin  = config->hw.pin;
  if (config->isLowActive) {
    gpio_config.isLowOnInit = config->isOnInit;
  } else {
    gpio_config.isLowOnInit = !config->isOnInit;
  }
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  handle = (McuLED_t*)pvPortMalloc(sizeof(McuLED_t)); /* get a new device descriptor */
#else
  handle = (McuLED_t*)malloc(sizeof(McuLED_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuLED_t)); /* init all fields */
    handle->gpio = gpio;
    handle->isLowActive = config->isLowActive;
  }
	return handle;
}

McuLED_Handle_t McuLED_DeinitLed(McuLED_Handle_t led) {
  assert(led!=NULL);
  McuGPIO_DeinitGPIO(((McuLED_t*)led)->gpio);
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  vPortFree(led);
#else
  free(led);
#endif
  return NULL;
}

void McuLED_On(McuLED_Handle_t led) {
  assert(led!=NULL);
  McuLED_t *desc = (McuLED_t*)led;

  if (desc->isLowActive) {
    McuGPIO_SetLow(desc->gpio);
  } else {
    McuGPIO_SetHigh(desc->gpio);
  }
}

void McuLED_Off(McuLED_Handle_t led) {
  assert(led!=NULL);
  McuLED_t *desc = (McuLED_t*)led;

  if (desc->isLowActive) {
    McuGPIO_SetHigh(desc->gpio);
  } else {
    McuGPIO_SetLow(desc->gpio);
  }
}

void McuLED_Toggle(McuLED_Handle_t led) {
  assert(led!=NULL);
  McuLED_t *desc = (McuLED_t*)led;

  McuGPIO_Toggle(desc->gpio);
}

bool McuLED_Get(McuLED_Handle_t led) {
  assert(led!=NULL);
  McuLED_t *desc = (McuLED_t*)led;

  if (desc->isLowActive) {
    return !McuGPIO_IsHigh(desc->gpio);
  } else {
    return McuGPIO_IsHigh(desc->gpio);
 }
}

void McuLED_Set(McuLED_Handle_t led, bool isOn) {
  if (isOn) {
    McuLED_On(led);
  } else {
    McuLED_Off(led);
  }
}

void McuLED_Init(void) {
  /* nothing to do */
}

void McuLED_Deinit(void) {
  /* nothing to do */
}
