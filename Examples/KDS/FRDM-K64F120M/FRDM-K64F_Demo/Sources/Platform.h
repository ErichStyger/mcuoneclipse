/*
 * Platform.h
 *
 *  Created on: 14.02.2014
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Cpu.h"
#include "FreeRTOSConfig.h"

/* for now on the same SPI bus */
#define configSD  (defined(PEcfg_SD) && PEcfg_SD==1)
#define configRF  (defined(PEcfg_RF) && PEcfg_RF==1)

#define PL_HAS_BLUETOOTH      (1)
#define PL_HAS_SHELL          (1)
#define PL_HAS_RTOS           (1)
#define PL_HAS_KEYS           (1)
#define PL_HAS_ACCELEROMETER  (1)
#define PL_HAS_RADIO          (1 && configRF)
#define PL_HAS_RSTDIO         (1 && PL_HAS_RADIO)
#define PL_HAS_SD_CARD        (1 && configSD)
#define PL_HAS_DEBUG_PRINT    (1)
#define PL_HAS_RTOS_TRACE     (configUSE_TRACE_HOOKS)
#define PL_HAS_MINI_INI       (1 && PL_HAS_SD_CARD)
#define PL_HAS_FLOPPY         (1)

#endif /* PLATFORM_H_ */
