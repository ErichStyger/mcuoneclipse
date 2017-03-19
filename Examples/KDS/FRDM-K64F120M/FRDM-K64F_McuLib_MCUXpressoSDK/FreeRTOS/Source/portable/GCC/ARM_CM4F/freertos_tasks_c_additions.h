/*!
 * \file
 * \brief Debugger helper file, included by FreeRTOS task.c
 * This file provides information about the RTOS which can be used by the debugger.
 */
#if !defined(__HIWARE__)
  #include <stdint.h>
#endif

#if (configUSE_TRACE_FACILITY == 0)
  #error "configUSE_TRACE_FACILITY must be enabled"
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
#if ((configUSE_HEAP_SCHEME > 5) || (configUSE_HEAP_SCHEME < 1))
  #error "Invalid configUSE_HEAP_SCHEME setting!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The following struct contains RTOS version information
 * plus offsets into the TCB block to locate elements in the TCB.
 */
extern const uint8_t FreeRTOSDebugConfig[];
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
  0 // pad to 32-bit boundary
};

#ifdef __cplusplus
}
#endif


