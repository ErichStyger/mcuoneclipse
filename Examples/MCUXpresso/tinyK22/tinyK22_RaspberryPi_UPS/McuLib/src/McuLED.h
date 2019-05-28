/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for LEDs
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LED_H_
#define LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "fsl_gpio.h"
#include "McuLibconfig.h"
#include "McuLEDconfig.h"

typedef void *McuLED_Handle_t;

typedef struct {
  bool isLowActive;
  bool isOnInit;
  GPIO_Type *gpio;
#if McuLib_CONFIG_CPU_IS_KINETIS
  PORT_Type *port;
#elif McuLib_CONFIG_CPU_IS_LPC
  uint32_t port;
#endif
  uint32_t pin;
} McuLED_Config_t;

void McuLED_GetDefaultConfig(McuLED_Config_t *config);

McuLED_Handle_t McuLED_InitLed(McuLED_Config_t *config);

McuLED_Handle_t McuLED_DeinitLed(McuLED_Handle_t led);

void McuLED_On(McuLED_Handle_t led);
void McuLED_Off(McuLED_Handle_t led);
void McuLED_Neg(McuLED_Handle_t led);
bool McuLED_Get(McuLED_Handle_t led);
void McuLED_Set(McuLED_Handle_t led, bool isOn);

/* driver intitialization */
void McuLED_Init(void);

/* driver deinitialization */
void McuLED_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCULED_H_ */
