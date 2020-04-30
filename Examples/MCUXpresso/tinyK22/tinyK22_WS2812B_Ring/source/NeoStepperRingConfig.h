/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOSTEPPERRINGCONFIG_H_
#define NEOSTEPPERRINGCONFIG_H_

#include "McuLibconfig.h"

#define NEOSR_NOF_RING_LED        (40)  /* number of LEDs in ring */

#ifndef NEOSR_CONFIG_USE_FREERTOS_HEAP
  #define NEOSR_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifndef NEOSR_CONFIG_USE_GAMMA_CORRECTION
  #define NEOSR_CONFIG_USE_GAMMA_CORRECTION   (0)
    /*!< 1: use gamma correction, 0: do not use gamma correction */
#endif


#endif /* NEOSTEPPERRINGCONFIG_H_ */
