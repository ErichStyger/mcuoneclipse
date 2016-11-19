/*
 * Platform.h
 *
 *  Created on: 14.02.2014
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* for now on the same SPI bus */
#include "Cpu.h"

#define configSD  defined(PEcfg_SD) && (PEcfg_SD==1)
#define configRF  defined(PEcfg_RF) && (PEcfg_RF==1)

#define PL_HAS_BLUETOOTH      (1)
#define PL_HAS_SHELL          (1)
#define PL_HAS_RTOS           (1)
#define PL_HAS_KEYS           (1)
#define PL_HAS_ACCELEROMETER  (1)
#define PL_HAS_RADIO          (1 && configRF)
#define PL_HAS_RSTDIO         (1 && PL_HAS_RADIO)
#define PL_HAS_SD_CARD        (1 && !configRF)
#define PL_HAS_DEBUG_PRINT    (1)
#define PL_HAS_RTOS_TRACE     (0)
#define PL_HAS_MINI_INI       (1 && PL_HAS_SD_CARD)

#endif /* PLATFORM_H_ */
