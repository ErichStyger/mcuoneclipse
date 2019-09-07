/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "platform.h"
#include "McuLib.h"
#include "X12.h"
#include "McuGPIO.h"
#include "McuWait.h"

/* sensor for hour */
#define X12_A_STEP_GPIO      GPIO
#define X12_A_STEP_PORT      0U
#define X12_A_STEP_PIN       16U

#define X12_A_DIR_GPIO       GPIO
#define X12_A_DIR_PORT       0U
#define X12_A_DIR_PIN        17U

#define X12_RESET_GPIO       GPIO
#define X12_RESET_PORT       0U
#define X12_RESET_PIN        18U

static McuGPIO_Handle_t reset, aDir, aStep;

void X12_Deinit(void) {
  /* \todo */
}

void X12_Reset(void) {
  McuGPIO_SetLow(reset);
  McuWait_Waitms(1);
  McuGPIO_SetHigh(reset); /* reset is low active */
}

void X12_SetForward(McuGPIO_Handle_t m) {
  McuGPIO_SetHigh(m);
}

void X12_Step(McuGPIO_Handle_t m) {
  McuGPIO_SetHigh(m);
  McuWait_Waitus(10);
  McuGPIO_SetLow(m);
}

void X12_Test(void) {
  int i;

  X12_Reset();
  X12_SetForward(aDir);
  for(i=0; i<100; i++) {
    X12_Step(aStep);
    McuWait_Waitms(10);
  }
}

void X12_Init(void) {
  McuGPIO_Config_t gpio_config;

  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false;
  gpio_config.hw.gpio = X12_RESET_GPIO;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  gpio_config.hw.port = X12_RESET_PORT;
#endif
  gpio_config.hw.pin  = X12_RESET_PIN;
  gpio_config.isHighOnInit = false; /* there is an external pull-down for the reset pin too */
  reset = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  gpio_config.hw.gpio = X12_A_DIR_GPIO;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  gpio_config.hw.port = X12_A_DIR_PORT;
#endif
  aDir = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  gpio_config.hw.gpio = X12_A_STEP_GPIO;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  gpio_config.hw.port = X12_A_STEP_PORT;
#endif
  aStep = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  X12_Test();
}
