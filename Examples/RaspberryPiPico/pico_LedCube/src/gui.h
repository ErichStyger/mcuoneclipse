/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUI_H_
#define GUI_H_

#include "gui_config.h"

typedef enum Gui_Event_e {
  Gui_Event_Battery_Charge_Changed,
  Gui_Event_USB_Connection_Changed,
  Gui_Event_HomePower_Changed,
  Gui_Event_SolarPower_Changed,
  Gui_Event_CarPower_Changed,
  Gui_Event_LightColor_Changed,
  Gui_Event_LightBrightness_Changed,
  Gui_Event_LightOnOff_Changed,
#if PL_CONFIG_USE_OLED_CLOCK
  Gui_Event_Clock_Changed,

  Gui_Event_Hour_Changed,
  Gui_Event_Minute_Changed,

  Gui_Event_Day_Changed,
  Gui_Event_Month_Changed,
  Gui_Event_Year_Changed,
#endif
#if GUI_CONFIG_USE_SENSOR
  Gui_Event_Sensor_Changed,
#endif
  Gui_Event_Road_Changed,
} Gui_Event_e;

void GUI_SendEvent(Gui_Event_e event);

void GUI_Suspend(void);
void GUI_Resume(void);

void GUI_NotifyUserAction(void);

void GUI_Init(void);

#endif /* GUI_H_ */
