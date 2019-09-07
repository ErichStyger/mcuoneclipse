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

typedef struct {
  int32_t pos;
  McuGPIO_Handle_t dir;
  McuGPIO_Handle_t step;
} X12_Motor;

typedef struct {
  McuGPIO_Handle_t reset;
  X12_Motor m[4];
} X12_Device;

static X12_Device device;

void X12_Deinit(void) {
  /* \todo */
}

void X12_Reset(X12_Device *dev) {
  McuGPIO_SetLow(dev->reset);
  McuWait_Waitms(1);
  McuGPIO_SetHigh(dev->reset); /* reset is low active */
  McuWait_Waitus(10);
}

void X12_SetForward(X12_Motor *m) {
  McuGPIO_SetHigh(m->dir);
  McuWait_Waitus(10);
}

void X12_SetBackward(X12_Motor *m) {
  McuGPIO_SetLow(m->dir);
  McuWait_Waitus(10);
}

void X12_Step(X12_Motor *m) {
  McuGPIO_SetHigh(m->step);
  McuWait_Waitus(10);
  McuGPIO_SetLow(m->step);
  McuWait_Waitus(100);
}

void X12_Test(void) {
  int i;

  X12_Reset(&device);
  for(;;) {
    X12_SetForward(&device.m[0]);
    for(i=0; i<3000; i++) {
      X12_Step(&device.m[0]);
    }
    McuWait_Waitms(10);
    X12_SetBackward(&device.m[0]);
    McuWait_Waitms(1);
    for(i=0; i<4000; i++) {
      X12_Step(&device.m[0]);
    }
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
  device.reset = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  gpio_config.hw.gpio = X12_A_DIR_GPIO;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  gpio_config.hw.port = X12_A_DIR_PORT;
#endif
  gpio_config.hw.pin  = X12_A_DIR_PIN;
  device.m[0].dir = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  gpio_config.hw.gpio = X12_A_STEP_GPIO;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  gpio_config.hw.port = X12_A_STEP_PORT;
#endif
  gpio_config.hw.pin  = X12_A_STEP_PIN;
  device.m[0].step = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

  X12_Test();
}
