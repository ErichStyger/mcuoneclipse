/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuA3967config.h"
#include "McuA3967.h"
#include "McuGPIO.h"
#include <assert.h>
#include <string.h> /* for memset */
#include <stdlib.h> /* for malloc() and free() */
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuA3967_Config_t defaultConfig =
{
  .rst = { /* reset pin */
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
  McuGPIO_Handle_t reset;
} McuA3967_Stepper_t;


void McuA3967_GetDefaultConfig(McuA3967_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

McuA3967_Handle_t McuA3967_InitHandle(McuA3967_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuGPIO_Handle_t gpio;
  McuA3967_Stepper_t *handle;

  assert(config!=NULL);
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  handle = (McuA3967_Stepper_t*)pvPortMalloc(sizeof(McuA3967_Stepper_t)); /* get a new device descriptor */
#else
  handle = (McuA3967_Stepper_t*)malloc(sizeof(McuA3967_Stepper_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle==NULL) {
    return NULL; /* error case */
  }
  memset(handle, 0, sizeof(McuA3967_Stepper_t)); /* init all fields */

  /* reset pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* reset it output only */
  gpio_config.isLowOnInit = true; /* disabled/LOW by default */
  gpio_config.hw.gpio = config->rst.gpio;
  gpio_config.hw.port = config->rst.port;
  gpio_config.hw.pin  = config->rst.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->reset = gpio;
  return (McuA3967_Handle_t)handle;
}

McuA3967_Handle_t McuA3967_DeinitHandle(McuA3967_Handle_t stepper){
  assert(stepper!=NULL);
  McuGPIO_DeinitGPIO(((McuA3967_Stepper_t*)stepper)->reset);
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  vPortFree(stepper);
#else
  free(stepper);
#endif
  return NULL;
}

void McuA3967_Deinit(void) {
  /* nothing to do */
}

void McuA3967_Init(void){
  /* nothing to do */
}
