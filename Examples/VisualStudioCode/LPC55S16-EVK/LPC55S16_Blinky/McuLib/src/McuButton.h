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

typedef struct McuButton_Dummy_s { int dummy; } McuButton_Dummy_s; /*!< using a pointer to a struct instead a pointer to void for handle, used for handle type 'safety' only */

typedef McuButton_Dummy_s *McuBtn_Handle_t; /*!< Button handle type */

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

void McuBtn_GetPinStatusString(McuBtn_Handle_t btn, unsigned char *buf, size_t bufSize);

void McuBtn_Deinit(void);

void McuBtn_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUBUTTON_H_ */
