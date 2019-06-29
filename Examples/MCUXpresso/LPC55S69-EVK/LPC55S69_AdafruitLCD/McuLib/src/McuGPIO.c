/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for GPIO pins
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLibconfig.h"
#include "McuGPIO.h"
#include "fsl_gpio.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#endif
#include <stddef.h>
#include <string.h> /* for memset */
#include <assert.h>
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuGPIO_Config_t defaultConfig =
{
    .isInput = true,
    .isLowOnInit = true,
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
  bool isInput;
  McuGPIO_HwPin_t hw;
} McuGPIO_t;

void McuGPIO_GetDefaultConfig(McuGPIO_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

McuGPIO_Handle_t McuGPIO_InitGPIO(McuGPIO_Config_t *config) {
  gpio_pin_config_t pin_config; /* config for the SDK */
  McuGPIO_t *handle;

  assert(config!=NULL);
  memset(&pin_config, 0, sizeof(pin_config)); /* init all fields */
  if (config->isInput) {
    pin_config.pinDirection = kGPIO_DigitalInput;
  } else {
    pin_config.pinDirection = kGPIO_DigitalOutput;
  }
  pin_config.outputLogic = !config->isLowOnInit;
#if McuLib_CONFIG_CPU_IS_KINETIS
  GPIO_PinInit(config->hw.gpio, config->hw.pin, &pin_config);
  PORT_SetPinMux(config->hw.port, config->hw.pin, kPORT_MuxAsGpio);
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PinInit(config->hw.gpio, config->hw.port, config->hw.pin, &pin_config);
#endif

#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  handle = (McuGPIO_t*)pvPortMalloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#else
  handle = (McuGPIO_t*)malloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuGPIO_t)); /* init all fields */
    handle->isInput = config->isInput;
    handle->hw.gpio = config->hw.gpio;
    handle->hw.pin = config->hw.pin;
    handle->hw.port = config->hw.port;
  }
  return handle;
}

McuGPIO_Handle_t McuGPIO_DeinitGPIO(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  vPortFree(gpio);
#else
  free(gpio);
#endif
  return NULL;
}

void McuGPIO_Low(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  GPIO_PortClear(pin->hw.gpio, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortClear(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#endif
}

void McuGPIO_High(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  GPIO_PortSet(pin->hw.gpio, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortSet(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#endif
}

void McuGPIO_Neg(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  GPIO_PortToggle(pin->hw.gpio, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortToggle(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#endif
}

void McuGPIO_Set(McuGPIO_Handle_t gpio, bool toLow) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  if (toLow) {
#if McuLib_CONFIG_CPU_IS_KINETIS
    GPIO_PortClear(pin->hw.gpio, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_LPC
    GPIO_PortClear(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#endif
  } else {
#if McuLib_CONFIG_CPU_IS_KINETIS
    GPIO_PortSet(pin->hw.gpio, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_LPC
    GPIO_PortSet(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#endif
  }
}

bool McuGPIO_Get(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  if (pin->isInput) {
#if McuLib_CONFIG_CPU_IS_KINETIS
    return GPIO_PinRead(pin->hw.gpio, pin->hw.pin)!=0;
#elif McuLib_CONFIG_CPU_IS_LPC
    return GPIO_PinRead(pin->hw.gpio, pin->hw.port, pin->hw.pin)!=0;
#endif
  }
  return false;
}

void McuGPIO_Init(void) {
  /* nothing to do */
}

void McuGPIO_Deinit(void) {
  /* nothing to do */
}
