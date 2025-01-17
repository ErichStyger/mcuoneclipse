/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
#define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
#define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (0)
/* ---------------------------------------------------------------------------------------*/
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "Semihosting Shell"
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_LINKSERVER
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                 (0)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/

#endif /* INCLUDEMCULIBCONFIG_H_ */
