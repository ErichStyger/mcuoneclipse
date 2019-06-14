/*
 * McuButton.c
 *
 *  Created on: 27.05.2019
 *      Author: Erich Styger
 */

#include "McuButton.h"
#include <stdlib.h> /* memcpy */
#include <string.h> /* memset */
#include <assert.h>
#if MCUBUTTON_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuBtn_Config_t defaultConfig =
{
    .isLowActive = true,
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
  bool isLowActive;
  McuGPIO_Handle_t gpio;
} McuBtn_t;

void McuBtn_GetDefaultConfig(McuBtn_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

bool McuBtn_IsOn(McuBtn_Handle_t btn) {
  McuBtn_t *button;

  assert(btn!=NULL);
  button = (McuBtn_t*)btn;
  if (button->isLowActive) {
    return !McuGPIO_Get(button->gpio);
  } else {
    return McuGPIO_Get(button->gpio);
  }
}

McuBtn_Handle_t McuBtn_InitButton(McuBtn_Config_t *config) {
  McuBtn_t *handle;
  McuGPIO_Config_t gpioConfig;
  assert(config!=NULL);

#if MCUBUTTON_CONFIG_USE_FREERTOS_HEAP
  handle = (McuBtn_t*)pvPortMalloc(sizeof(McuBtn_t)); /* get a new device descriptor */
#else
  handle = (McuBtn_t*)malloc(sizeof(McuBtn_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuBtn_t)); /* init all fields */
    handle->isLowActive = config->isLowActive;
    /* create GPIO pin */
    McuGPIO_GetDefaultConfig(&gpioConfig);
    gpioConfig.isInput = true;
    gpioConfig.isLowOnInit = false;
    memcpy(&gpioConfig.hw, &config->hw, sizeof(gpioConfig.hw));
    handle->gpio = McuGPIO_InitGPIO(&gpioConfig);
  }
  return handle;
}

McuBtn_Handle_t McuBtn_DeinitButton(McuBtn_Handle_t button) {
  assert(button!=NULL);
#if MCUBUTTON_CONFIG_USE_FREERTOS_HEAP
  vPortFree(button);
#else
  free(button);
#endif
  return NULL;
}

void McuBtn_Deinit(void) {
}

void McuBtn_Init(void) {
}
