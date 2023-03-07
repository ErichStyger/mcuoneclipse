/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED      McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_KINETIS        (1)  /* NXP Kinetis family */
#define McuLib_CONFIG_CPU_IS_LPC            (0)  /* LPC family */
#define McuLib_CONFIG_CORTEX_M              (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT           McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
//#define McuSemihost_CONFIG_DEBUG_CONNECTION          McuSemihost_DEBUG_CONNECTION_GENERIC
#define McuSemihost_CONFIG_DEBUG_CONNECTION          McuSemihost_DEBUG_CONNECTION_LINKSERVER
//#define McuSemihost_CONFIG_DEBUG_CONNECTION          McuSemihost_DEBUG_CONNECTION_SEGGER
//#define McuSemihost_CONFIG_DEBUG_CONNECTION          McuSemihost_DEBUG_CONNECTION_PEMICRO
//#define McuSemihost_CONFIG_DEBUG_CONNECTION          McuSemihost_DEBUG_CONNECTION_PYOCD

#define McuSemihost_CONFIG_INIT_STDIO_HANDLES   (1)

#endif /* INCLUDEMCULIBCONFIG_H_ */
