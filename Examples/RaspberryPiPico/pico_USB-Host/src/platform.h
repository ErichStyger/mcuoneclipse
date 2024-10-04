/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PL_CONFIG_USE_PICO_W            (0) /* if using Pico W board */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_UNIT_TESTS        (1 && defined(ENABLE_UNIT_TESTS) && ENABLE_UNIT_TESTS==1) /* if using unit tests. ENABLE_UNIT_TESTS is set by the CMake file */
#if PL_CONFIG_USE_UNIT_TESTS && !defined(UNITY_OUTPUT_CHAR)
   #error "needs to be defined in IncludeMcuLibConfig.h!"
#endif

/* platform configuration macros: set to 1 to enable functionality */
#define PL_CONFIG_USE_SHELL             (1)
#define PL_CONFIG_USE_LEDS              (0) /* if using LEDs */
#define PL_CONFIG_USE_USB_CDC           (1) /* if using USB CDC */
#define PL_CONFIG_USE_SEMIHOSTING       (0) /* if using semihosting for standard I/O */
#define PL_CONFIG_USE_RTT               (0 || PL_CONFIG_USE_UNIT_TESTS) /* if using SEGGER RTT, needed for unit testing */

#define PL_CONFIG_USE_GCOV              (0 && McuRdimon_CONFIG_IS_ENABLED) /* if using gcov */
#define PL_CONFIG_USE_GPROF             (0) /* GNU gprof profiling */

#define PL_CONFIG_USE_USB_HOST          (0)

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* PLATFORM_H_ */
