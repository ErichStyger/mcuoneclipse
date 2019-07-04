/*
 * Platform.h
 *
 *  Created on: 13.04.2019
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_I2C               (1)
#define PL_CONFIG_USE_HW_I2C            (0 && PL_CONFIG_USE_I2C) /* otherwise uses bit-banging */
#define PL_CONFIG_USE_FT6206            (1 && PL_CONFIG_USE_I2C) /* capacitive touch controller */
#define PL_CONFIG_USE_GUI               (1)
#define PL_CONFIG_USE_SHELL             (1)
#define PL_CONFIG_USE_USB_CDC           (0)
#define PL_CONFIG_USE_GUI_KEY_NAV       (0)
#define PL_CONFIG_USE_GUI_TOUCH_NAV     (0)
#define PL_CONFIG_USE_GUI_KEYPAD_NAV    (0)
#define PL_CONFIG_USE_GUI_SCREEN_SAVER  (0) /* turn off if idle */
#define PL_CONFIG_USE_TOASTER           (0 && PL_CONFIG_USE_GUI_SCREEN_SAVER)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
