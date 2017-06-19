
#if !defined(__HIWARE__)
#include <stdint.h>
#endif

#if (configUSE_TRACE_FACILITY == 0)
  #error "configUSE_TRACE_FACILITY must be enabled"
#endif

#define FREERTOS_DEBUG_CONFIG_MAJOR_VERSION 1
#define FREERTOS_DEBUG_CONFIG_MINOR_VERSION 1

// NOTE!!
// Default to a FreeRTOS version which didn't include these macros. FreeRTOS 
// v7.5.3 is used here.
#ifndef tskKERNEL_VERSION_BUILD
  #define tskKERNEL_VERSION_BUILD 3
#endif
#ifndef tskKERNEL_VERSION_MINOR
  #define tskKERNEL_VERSION_MINOR 5
#endif
#ifndef tskKERNEL_VERSION_MAJOR
  #define tskKERNEL_VERSION_MAJOR 7
#endif
// NOTE!!
// The configUSE_HEAP_SCHEME macro describes the heap scheme using a value
// 1 - 5 which corresponds to the following schemes:
//
// heap_1 - the very simplest, does not permit memory to be freed
// heap_2 - permits memory to be freed, but not does coalescence adjacent free
//          blocks.
// heap_3 - simply wraps the standard malloc() and free() for thread safety
// heap_4 - coalesces adjacent free blocks to avoid fragmentation. Includes
//          absolute address placement option
// heap_5 - as per heap_4, with the ability to span the heap across
//          multiple non-adjacent memory areas
#ifndef configUSE_HEAP_SCHEME
  #define configUSE_HEAP_SCHEME 3 // thread safe malloc
#endif
#if ((configUSE_HEAP_SCHEME > 5) || (configUSE_HEAP_SCHEME < 1))
  #error "Invalid configUSE_HEAP_SCHEME setting!"
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern const uint8_t FreeRTOSDebugConfig[];
// NOTES!!
// IAR documentation is confusing. It suggests the data must be statically 
// linked, and the #pragma placed immediately before the symbol definition. 
// The IAR supplied examples violate both "rules", so this is a best guess. 
//
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


