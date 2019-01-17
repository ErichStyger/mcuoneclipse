/*!
 * \file
 * \brief Debugger helper file, included by FreeRTOS task.c
 * This file provides information about the RTOS which can be used by the debugger.
 */
/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* freertos_tasks_c_additions.h Rev. 1.2 */
#ifndef FREERTOS_TASKS_C_ADDITIONS_H
#define FREERTOS_TASKS_C_ADDITIONS_H

#if !defined(__HIWARE__)
  #include <stdint.h>
#endif

#define FREERTOS_DEBUG_CONFIG_MAJOR_VERSION 1
#define FREERTOS_DEBUG_CONFIG_MINOR_VERSION 1

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
#ifndef configUSE_HEAP_SCHEME
  #define configUSE_HEAP_SCHEME 3 /* configUSE_HEAP_SCHEME is a custom define by the McuOnEclipse port. if missing, default to scheme 3 */
#endif
#if ((configUSE_HEAP_SCHEME > 6) || (configUSE_HEAP_SCHEME < 1))
  #error "Invalid configUSE_HEAP_SCHEME setting!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The following struct contains RTOS version information
 * plus offsets into the TCB block to locate elements in the TCB.
 */
extern const uint8_t FreeRTOSDebugConfig[];

/* NOTES!!
 * IAR documentation is confusing. It suggests the data must be statically
 * linked, and the #pragma placed immediately before the symbol definition.
 * The IAR supplied examples violate both "rules", so this is a best guess.
 */
#if defined(__GNUC__)
  const uint8_t FreeRTOSDebugConfig[] __attribute__((section(".rodata"))) =
#elif defined(__CC_ARM)
  const uint8_t FreeRTOSDebugConfig[] __attribute__((used)) =
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma required=FreeRTOSDebugConfig
  const uint8_t FreeRTOSDebugConfig[] =
#else
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
  0 /* pad to 32-bit boundary */
};

#ifdef __cplusplus
}
#endif

#endif /* FREERTOS_TASKS_C_ADDITIONS_H */
