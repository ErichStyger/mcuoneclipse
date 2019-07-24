/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TOUCHCALIBRATE_H_
#define TOUCHCALIBRATE_H_

void TouchCalib_CreateView(void);

#include "LittlevGL/lvgl/lvgl.h"
void TouchCalib_set_cal_data(lv_point_t points[4]);

#endif /* TOUCHCALIBRATE_H_ */
