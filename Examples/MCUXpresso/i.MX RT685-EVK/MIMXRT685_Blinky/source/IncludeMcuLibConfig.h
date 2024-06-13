/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)
#define McuLib_CONFIG_CPU_IS_LPC        (0)
#define McuLib_CONFIG_CPU_IS_IMXRT      (0) /* \todo */

/* ------------------- RTOS ---------------------------*/
#define configTOTAL_HEAP_SIZE                 (16*1024)
#define McuLib_CONFIG_SDK_USE_FREERTOS        (0)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS  (0)


#endif /* INCLUDEMCULIBCONFIG_H_ */

