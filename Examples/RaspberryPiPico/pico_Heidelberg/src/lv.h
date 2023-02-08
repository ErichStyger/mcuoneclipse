/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_LV_H_
#define SOURCES_LV_H_

#include "LittlevGL/lvgl/lvgl.h"

/* button masks */
#define LV_BTN_MASK_CENTER    (1<<0)
#define LV_BTN_MASK_RIGHT     (1<<1)
#define LV_BTN_MASK_DOWN      (1<<2)
#define LV_BTN_MASK_UP        (1<<3)
#define LV_BTN_MASK_LEFT      (1<<4)
#define LV_BTN_MASK_PREV      (1<<5)
#define LV_BTN_MASK_NEXT      (1<<6)

/* push button event mask bits. Must be outside of button masks above! */
#define LV_MASK_PRESSED       (1<<15)
#define LV_MASK_RELEASED      (1<<14)
#define LV_MASK_PRESSED_LONG  (1<<13)
#define LV_MASK_RELEASED_LONG (1<<12)

lv_indev_t *LV_GetInputDevice(void);

void LV_ButtonEvent(uint8_t key, uint16_t eventMask);

void LV_ClearButtonEventQueue(void);

void LV_Task(void);

void LV_Init(void);

#endif /* SOURCES_LV_H_ */
