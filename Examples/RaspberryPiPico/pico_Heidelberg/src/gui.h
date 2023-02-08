/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUI_H_
#define GUI_H_

typedef enum Gui_Event_e {
  Gui_Event_Battery_Charge_Changed,
  Gui_Event_USB_Connection_Changed,
} Gui_Event_e;

void GUI_SendEvent(Gui_Event_e event);

void GUI_NotifyUserAction(void);

void GUI_Init(void);

#endif /* GUI_H_ */
