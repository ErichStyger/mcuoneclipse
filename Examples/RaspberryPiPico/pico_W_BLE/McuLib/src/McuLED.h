/*
 * Copyright (c) 2019-2021, Erich Styger
 * All rights reserved.
 *
 * Driver for LEDs
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuLED_H_
#define McuLED_H_

#include <stdbool.h>
#include "McuLibconfig.h"
#include "McuLEDconfig.h"
#include "McuGPIO.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct McuLED_Dummy_s { int dummy; } McuLED_Dummy_s; /*!< using a pointer to a struct instead a pointer to void for handle, used for handle type 'safety' only */

typedef McuLED_Dummy_s *McuLED_Handle_t; /*!< LED handle type */

typedef struct {
  bool isLowActive;
  bool isOnInit;
  McuGPIO_HwPin_t hw;
} McuLED_Config_t;

void McuLED_GetDefaultConfig(McuLED_Config_t *config);

McuLED_Handle_t McuLED_InitLed(McuLED_Config_t *config);

McuLED_Handle_t McuLED_DeinitLed(McuLED_Handle_t led);

void McuLED_On(McuLED_Handle_t led);
void McuLED_Off(McuLED_Handle_t led);
void McuLED_Toggle(McuLED_Handle_t led);
bool McuLED_Get(McuLED_Handle_t led);
void McuLED_Set(McuLED_Handle_t led, bool isOn);

/* driver initialization */
void McuLED_Init(void);

/* driver deinitialization */
void McuLED_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuLED_H_ */
