/*
 * Copyright (c) 2019-2021, Erich Styger
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
#if McuLib_CONFIG_NXP_SDK_USED
  #include "fsl_gpio.h"
#elif McuLib_CONFIG_CPU_IS_STM32
  #include "stm32f3xx_hal.h"
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_ESP32
  #include "driver/gpio.h"
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
  #if McuLib_CONFIG_NXP_SDK_USED && !McuLib_CONFIG_IS_KINETIS_KE
      .gpio = NULL,
  #elif McuLib_CONFIG_CPU_IS_STM32
      .gpio = NULL,
  #endif
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
  #if McuLib_CONFIG_CPU_IS_ESP32
    .pin = GPIO_NUM_NC,
  #else
    .pin = 0,
  #endif
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
  memcpy(&gpio_config.hw, &config->hw, sizeof(gpio_config.hw)); /* copy hardware information */
  if (config->isLowActive) {
    gpio_config.isHighOnInit = !config->isOnInit;
  } else {
    gpio_config.isHighOnInit = config->isOnInit;
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
