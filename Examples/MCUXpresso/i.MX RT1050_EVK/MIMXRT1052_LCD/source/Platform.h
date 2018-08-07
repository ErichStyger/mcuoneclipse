/*
 * Platform.h
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_EYE_DEMO   (0)
#define PL_CONFIG_USE_LCD    (1)
#define PL_CONFIG_USE_TOUCH  (1 && PL_CONFIG_USE_LCD)
#define PL_CONFIG_USE_GUI    (1 && PL_CONFIG_USE_LCD)
#define PL_CONFIG_USE_ACCEL  (1)

#if PL_CONFIG_EYE_DEMO && PL_CONFIG_USE_GUI
#error "only one or the other option is supported right now"
#endif

#endif /* PLATFORM_H_ */
