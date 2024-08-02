/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* freertos_tasks_c_additions.h Rev. 1.4 */
#ifndef FREERTOS_TASKS_C_ADDITIONS_H
#define FREERTOS_TASKS_C_ADDITIONS_H

#include <stdint.h>
#if !defined(__HIWARE__) /* << EST */
  #include <stdint.h>
#endif

#if (configUSE_TRACE_FACILITY == 0)
#error "configUSE_TRACE_FACILITY must be enabled"
#endif

#define FREERTOS_DEBUG_CONFIG_MAJOR_VERSION 1
#define FREERTOS_DEBUG_CONFIG_MINOR_VERSION 2

/* NOTE!!
 * Default to a FreeRTOS version which didn't include these macros. FreeRTOS
 * v7.5.3 is used here.
 */
#ifndef tskKERNEL_VERSION_BUILD
#define tskKERNEL_VERSION_BUILD 3
#endif
#ifndef tskKERNEL_VERSION_MINOR
#define tskKERNEL_VERSION_MINOR 5
#endif
#ifndef tskKERNEL_VERSION_MAJOR
#define tskKERNEL_VERSION_MAJOR 7
#endif

/* NOTE!!
 * The configFRTOS_MEMORY_SCHEME macro describes the heap scheme using a value
 * 1 - 5 which corresponds to the following schemes:
 *
 * heap_1 - the very simplest, does not permit memory to be freed
 * heap_2 - permits memory to be freed, but not does coalescence adjacent free
 *          blocks.
 * heap_3 - simply wraps the standard malloc() and free() for thread safety
 * heap_4 - coalesces adjacent free blocks to avoid fragmentation. Includes
 *          absolute address placement option
 * heap_5 - as per heap_4, with the ability to span the heap across
 *          multiple nonOadjacent memory areas
 * heap_6 - reentrant newlib implementation
 */
#ifndef configUSE_HEAP_SCHEME
  #define configUSE_HEAP_SCHEME 3 /* thread safe malloc */
#endif

#if ((configUSE_HEAP_SCHEME > 6) || (configUSE_HEAP_SCHEME < 1))  /* <<EST Using up to 6 schemes */
#error "Invalid configFRTOS_MEMORY_SCHEME setting!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t FreeRTOSDebugConfig[];

/* NOTES!!
 * IAR documentation is confusing. It suggests the data must be statically
 * linked, and the #pragma placed immediately before the symbol definition.
 * The IAR supplied examples violate both "rules", so this is a best guess.
 */


#if (tskKERNEL_VERSION_MAJOR >= 10) && (tskKERNEL_VERSION_MINOR >= 2)
// Need the portARCH_NAME define
#ifndef portARCH_NAME
#define portARCH_NAME NULL
#endif
#if defined(__GNUC__)
char *const portArch_Name __attribute__((section(".rodata"))) = portARCH_NAME;
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
char *const portArch_Name __attribute__((used)) = portARCH_NAME;
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma required=portArch_Name
char *const portArch_Name = portARCH_NAME;
#endif
#else
char *const portArch_Name = NULL;
#endif	// tskKERNEL_VERSION_MAJOR

#if defined(__GNUC__)
  const uint8_t FreeRTOSDebugConfig[] __attribute__((used)) __attribute__((section(".rodata"))) __attribute__((aligned(4)))  = /* needs to be 32bit aligned for LinkServer FreeRTOS thread awareness, otherwise problem with GDB. */
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
  const uint8_t FreeRTOSDebugConfig[] __attribute__((used)) =
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma required=FreeRTOSDebugConfig
  const uint8_t FreeRTOSDebugConfig[] =
#else /* << EST generic compiler */
  const uint8_t FreeRTOSDebugConfig[] =
#endif
{
    FREERTOS_DEBUG_CONFIG_MAJOR_VERSION,
    FREERTOS_DEBUG_CONFIG_MINOR_VERSION,
    tskKERNEL_VERSION_MAJOR,
    tskKERNEL_VERSION_MINOR,
    tskKERNEL_VERSION_BUILD,
    configUSE_HEAP_SCHEME,
    offsetof(struct tskTaskControlBlock, pxTopOfStack),
#if (tskKERNEL_VERSION_MAJOR > 8)
    offsetof(struct tskTaskControlBlock, xStateListItem),
#else
    offsetof(struct tskTaskControlBlock, xGenericListItem),
#endif
    offsetof(struct tskTaskControlBlock, xEventListItem),
    offsetof(struct tskTaskControlBlock, pxStack),
    offsetof(struct tskTaskControlBlock, pcTaskName),
    offsetof(struct tskTaskControlBlock, uxTCBNumber),
    offsetof(struct tskTaskControlBlock, uxTaskNumber),
    configMAX_TASK_NAME_LEN,
    configMAX_PRIORITIES,
#if (tskKERNEL_VERSION_MAJOR >= 10) && (tskKERNEL_VERSION_MINOR >= 2)
    configENABLE_MPU,
    configENABLE_FPU,
    configENABLE_TRUSTZONE,
	  configRUN_FREERTOS_SECURE_ONLY,
	  0, 			// 32-bit align
	  0, 0, 0, 0	// padding
#else
	  0			// pad to 32-bit boundary
#endif
};

#ifdef __cplusplus
}
#endif

#endif // FREERTOS_TASKS_C_ADDITIONS_H

