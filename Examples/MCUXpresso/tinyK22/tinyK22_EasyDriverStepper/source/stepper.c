/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Stepper.h"
#include "McuA3967.h"

#define PINS_STEPPER1_RST_GPIO       GPIOB
#define PINS_STEPPER1_RST_PORT       PORTB
#define PINS_STEPPER1_RST_PIN        18U

static McuA3967_Handle_t stepper;

void STEPPER_Deinit(void){
}

void STEPPER_Init(void) {
  McuA3967_Config_t config;

  McuA3967_GetDefaultConfig(&config);
  config.rst.gpio = PINS_STEPPER1_RST_GPIO;
  config.rst.port = PINS_STEPPER1_RST_PORT;
  config.rst.pin = PINS_STEPPER1_RST_PIN;
  stepper = McuA3967_InitHandle(&config);
}


