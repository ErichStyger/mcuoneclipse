/*
 * Platform.h
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_LCD    	(1) /* using LCD or not */
#define PL_CONFIG_USE_I2C    	(1) /* having I2C available: need to turn this on for accelerometer and touch on LCD */
#define PL_CONFIG_USE_GUI    	(1 && PL_CONFIG_USE_LCD) /* if using GUI on LCD */
#define PL_CONFIG_USE_TOUCH  	(1 && PL_CONFIG_USE_LCD && PL_CONFIG_USE_I2C) /* if using touch sensor on LCD */
#define PL_CONFIG_USE_ACCEL  	(0 && PL_CONFIG_USE_I2C) /* accelerometer demo */

/* GUI Demos */
#define PL_CONFIG_USE_GUI_SYSMON 	(1 && PL_CONFIG_USE_GUI) /* SysMon Demo */
#define PL_CONFIG_USE_GUI_DEMO  	(1 && PL_CONFIG_USE_GUI) /* GUI Demo */
#define PL_CONFIG_USE_GUI_HARDWARE  (1 && PL_CONFIG_USE_GUI) /* Hardware Demo */
#define PL_CONFIG_USE_GUI_ANIMATION (1 && PL_CONFIG_USE_GUI) /* Animation Demo */

#define PL_CONFIG_EYE_DEMO   		(0 && PL_CONFIG_USE_LCD && !PL_CONFIG_USE_GUI) /* blinky eyes demo */

#define PL_CONFIG_USE_LCD_DOUBLE_BUFFER  (0)  /* 1: use a double buffer and swap it for the LCD device. Uses more memory. 0: do not use double buffer for display */

#if PL_CONFIG_EYE_DEMO && PL_CONFIG_USE_GUI
  #error "only one or the other option is supported right now"
#endif

#endif /* PLATFORM_H_ */
