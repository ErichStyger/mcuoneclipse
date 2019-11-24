/*
 * McuRBconfig.h
 *
 *  Created on: 21.04.2019
 *      Author: Erich Styger
 */

#ifndef MCURBCONFIG_H_
#define MCURBCONFIG_H_

#include "McuLibconfig.h"

#ifndef MCURB_CONFIG_USE_FREERTOS_HEAP
  #define MCURB_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#endif /* MCURBCONFIG_H_ */
