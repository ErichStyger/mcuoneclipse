/*
 * SuperDuperLedDriverOfTheWorld.c
 *
 *  Created on: 07.03.2019
 *      Author: Erich Styger
 */

#include "SuperDuperLedDriverOfTheWorld.h"
#include <string.h> /* for memset() */
#include "fsl_port.h"

typedef struct {
  bool isLowActive;
  GPIO_Type *gpio;
  PORT_Type *port;
  uint32_t pinNr;
} SDLED_Desc_t;


void SDLED_On(SDLED_Handle_t led) {
  assert(led);
  SDLED_Desc_t *desc = (SDLED_Desc_t*)led;

  if (desc->isLowActive) {
    GPIO_PortClear(desc->gpio, (1<<desc->pinNr));
  } else {
    GPIO_PortSet(desc->gpio, (1<<desc->pinNr));
  }
}

void SDLED_Off(SDLED_Handle_t led) {
  assert(led);
  SDLED_Desc_t *desc = (SDLED_Desc_t*)led;

  if (desc->isLowActive) {
    GPIO_PortSet(desc->gpio, (1<<desc->pinNr));
  } else {
    GPIO_PortClear(desc->gpio, (1<<desc->pinNr));
  }
}

void SDLED_Neg(SDLED_Handle_t led) {
  assert(led);
  GPIO_PortToggle(((SDLED_Desc_t*)led)->gpio, (1<<((SDLED_Desc_t*)led)->pinNr));
}

bool SDLED_Get(SDLED_Handle_t led) {
  assert(led);
  SDLED_Desc_t *desc = (SDLED_Desc_t*)led;

  if (desc->isLowActive) {
    return GPIO_PinRead(desc->gpio, desc->pinNr)==0;
  } else {
    return GPIO_PinRead(desc->gpio, desc->pinNr)!=0;
  }
  return false; /* just in case */
}

void SDLED_Put(SDLED_Handle_t led, bool onOff) {
  if (onOff) {
    SDLED_On(led);
  } else {
    SDLED_Off(led);
  }
}

void SDLED_GetDefaultConfig(SDLED_Config_t *config) {
  memset(config, 0, sizeof(SDLED_Config_t));
  config->gpio = NULL;
  config->port = NULL;
  config->isDefaultOn = false;
  config->isLowActive = true;
}

SDLED_Handle_t SDLED_InitLed(SDLED_Config_t *config) {
  SDLED_Desc_t *handle;
  gpio_pin_config_t pin_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 1U
  };
  PORT_SetPinMux(config->port, config->pinNr, kPORT_MuxAsGpio);
  /* Initialize GPIO functionality   */
  if (config->isDefaultOn) {
    pin_config.outputLogic = config->isLowActive ? 0 : 1;
  } else {
    pin_config.outputLogic = config->isLowActive ? 1 : 0;
  }
  GPIO_PinInit(config->gpio, config->pinNr, &pin_config);

  handle = malloc(sizeof(SDLED_Desc_t)); /* get a new device descriptor */
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(SDLED_Desc_t)); /* init all fields */
    handle->gpio = config->gpio;
    handle->port = config->port;
    handle->pinNr = config->pinNr;
    handle->isLowActive = config->isLowActive;
  }
  return handle;
}

void SDLED_Deinit(void) {
  /* nothing to do (yet) */
}

void SDLED_Init(void) {
  /* nothing to do (yet) */
}
