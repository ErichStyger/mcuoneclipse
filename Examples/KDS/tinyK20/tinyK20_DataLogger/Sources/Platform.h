/*
 * Platform.h
 *
 *  Created on: 08.08.2015
 *      Author: tastyger
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_


#define PL_USE_HW_RTC                   0
#define PL_USE_USB_CDC                  0 /* note: does not work with 100 MHz PLL! */
#define PL_CONFIG_HAS_EXTRA_SEGGER_RTT  0 /* extra channel for RTT */
#define PL_CONFIG_HAS_LOGGER            1

#endif /* SOURCES_PLATFORM_H_ */
