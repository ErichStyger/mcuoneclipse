/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdbool.h>
#include <stdint.h>

bool TOUCH_HasMoreData(void);
uint8_t TOUCH_Poll(bool *pressed, uint16_t *x, uint16_t *y);
bool TOUCH_IsPressed(void);
void TOUCH_Deinit(void);
void TOUCH_Init(void);

#endif /* TOUCH_H_ */
