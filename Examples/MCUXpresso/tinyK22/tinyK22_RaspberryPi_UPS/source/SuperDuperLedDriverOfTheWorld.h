/*
 * SuperDuperLedDriverOfTheWorld.h
 *
 *  Created on: 07.03.2019
 *      Author: Erich Styger
 */

#ifndef SUPERDUPERLEDDRIVEROFTHEWORLD_H_
#define SUPERDUPERLEDDRIVEROFTHEWORLD_H_

#include <stdbool.h>
#include <stdint.h>
#include "fsl_gpio.h"

typedef void *SDLED_Handle_t;

typedef struct {
  bool isDefaultOn;
  bool isLowActive;
  GPIO_Type *gpio;
  PORT_Type *port;
  uint32_t pinNr;
} SDLED_Config_t;

void SDLED_On(SDLED_Handle_t led);
void SDLED_Off(SDLED_Handle_t led);
void SDLED_Neg(SDLED_Handle_t led);
bool SDLED_Get(SDLED_Handle_t led);
void SDLED_Put(SDLED_Handle_t led, bool onOff);

void SDLED_GetDefaultConfig(SDLED_Config_t *config);

SDLED_Handle_t SDLED_InitLed(SDLED_Config_t *config);

void SDLED_Deinit(void);
void SDLED_Init(void);


#endif /* SUPERDUPERLEDDRIVEROFTHEWORLD_H_ */
