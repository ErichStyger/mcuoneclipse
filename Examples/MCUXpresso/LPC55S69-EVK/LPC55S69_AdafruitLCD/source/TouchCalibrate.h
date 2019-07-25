/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TOUCHCALIBRATE_H_
#define TOUCHCALIBRATE_H_

#include <stdbool.h>

void TouchCalib_CreateView(void);

#include "LittlevGL/lvgl/lvgl.h"
void TouchCalib_set_cal_data(lv_point_t points[4]);
void TouchCalib_Calibrate(uint16_t *x, uint16_t *y);
bool TouchCalib_IsCalibrated(void);
void TouchCalib_SetCalibrated(bool isCalibrated);

#endif /* TOUCHCALIBRATE_H_ */
