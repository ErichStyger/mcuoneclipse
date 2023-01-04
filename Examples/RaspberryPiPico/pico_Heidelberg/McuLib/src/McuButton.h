/*
 * McuButton.h
 *
 * Copyright (c) 2019-2021, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUBUTTON_H_
#define MCUBUTTON_H_

#include "McuButtonconfig.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuLib.h"
#include "McuGPIO.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *McuBtn_Handle_t;

typedef struct {
  bool isLowActive;      /* default: true */
  McuGPIO_HwPin_t hw;
} McuBtn_Config_t;

void McuBtn_GetDefaultConfig(McuBtn_Config_t *config);

McuBtn_Handle_t McuBtn_InitButton(McuBtn_Config_t *config);

McuBtn_Handle_t McuBtn_DeinitButton(McuBtn_Handle_t button);

void McuBtn_DisablePullResistor(McuBtn_Handle_t btn);
void McuBtn_EnablePullResistor(McuBtn_Handle_t btn);

bool McuBtn_IsOn(McuBtn_Handle_t btn);

void McuBtn_Deinit(void);

void McuBtn_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUBUTTON_H_ */
