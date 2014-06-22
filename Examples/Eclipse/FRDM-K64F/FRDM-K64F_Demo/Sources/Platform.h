/*
 * Platform.h
 *
 *  Created on: 14.02.2014
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* for now on the same SPI bus */
#define configSD  0
#define configRF  1

#define PL_HAS_BLUETOOTH      (1)
#define PL_HAS_SHELL          (1)
#define PL_HAS_RTOS           (1)
#define PL_HAS_KEYS           (1)
#define PL_HAS_ACCELEROMETER  (1)
#define PL_HAS_RADIO          (1 && configRF)
#define PL_HAS_RSTDIO         (1 && PL_HAS_RADIO)
#define PL_HAS_SD_CARD        (1 && !configRF)
#define PL_HAS_DEBUG_PRINT    (1)
#define PL_HAS_RTOS_TRACE     (1)
#define PL_HAS_MINI_INI       (1 && PL_HAS_SD_CARD)

#endif /* PLATFORM_H_ */
