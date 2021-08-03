/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"

/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define SYSVIEW_APP_NAME                            "FreeRTOS on FRDM-K66F"
#define SYSVIEW_DEVICE_NAME                         "NXP K66FN2M"

/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START

#endif /* INCLUDEMCULIBCONFIG_H_ */
