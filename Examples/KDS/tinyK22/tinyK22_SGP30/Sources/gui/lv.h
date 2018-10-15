/*
 * lv.h
 *
 *  Created on: 02.08.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_LV_H_
#define SOURCES_LV_H_


#include "lvgl/lvgl.h"

/* push button bits */
#define LV_MASK_PRESSED (1<<15)
#define LV_MASK_RELEASED (1<<14)
#define LV_MASK_PRESSED_LONG (1<<13)
#define LV_MASK_RELEASED_LONG (1<<12)

#define LV_BUTTON_SW0  (1)
#define LV_BUTTON_SW1  (2)


lv_indev_t * LV_GetInputDevice(void);

void LV_Task(void);

void LV_Init(void);


#endif /* SOURCES_LV_H_ */
