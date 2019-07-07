/*
 * Platform.h
 *
 *  Created on: 13.04.2019
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL             (0)
#define PL_CONFIG_USE_USB_CDC           (0)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
