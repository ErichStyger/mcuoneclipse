/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "IncludeMcuLibConfig.h"

#define PL_CONFIG_USE_PICO_W            (0)
 /* if using Pico W board */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */

/* platform configuration macros: set to 1 to enable functionality */
#define PL_CONFIG_USE_LEDS              (1) /* if using LEDs */
#define PL_CONFIG_USE_UART              (0) /* if using UART for stdandard I/O */
#define PL_CONFIG_USE_USB_CDC           (0) /* if using USB-CDC for standard I/O */
#define PL_CONFIG_USE_SEMIHOSTING       (1) /* if using semihosting for standard I/O */

/*! \brief Module and platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
