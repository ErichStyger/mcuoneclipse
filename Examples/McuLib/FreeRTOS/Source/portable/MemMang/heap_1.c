/* Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved. */
/* << EST */
#include "FreeRTOSConfig.h"
#if !defined(configUSE_HEAP_SCHEME) || (configUSE_HEAP_SCHEME==1 && configSUPPORT_DYNAMIC_ALLOCATION==1)
/*
 * FreeRTOS Kernel V11.0.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


/*
 * The simplest possible implementation of pvPortMalloc().  Note that this
 * implementation does NOT allow allocated memory to be freed again.
 *
 * See heap_2.c, heap_3.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
 */
#include <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "task.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
  #include "SEGGER_SYSVIEW_Conf.h"
  #include "SEGGER_SYSVIEW.h"
#endif

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#if ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error This file must not be used if configSUPPORT_DYNAMIC_ALLOCATION is 0
#endif

/* A few bytes might be lost to byte aligning the heap start address. */
#define configADJUSTED_HEAP_SIZE    ( configTOTAL_HEAP_SIZE - portBYTE_ALIGNMENT )

/* Allocate the memory for the heap. */
#if ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    extern uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#elif configUSE_HEAP_SECTION_NAME && configCOMPILER==configCOMPILER_ARM_IAR /* << EST */
  #pragma language=extended
  #pragma location = configHEAP_SECTION_NAME_STRING
  static uint8_t ucHeap[configTOTAL_HEAP_SIZE] @ configHEAP_SECTION_NAME_STRING; 
#elif configUSE_HEAP_SECTION_NAME /* << EST */
  static uint8_t __attribute__((section (configHEAP_SECTION_NAME_STRING))) ucHeap[configTOTAL_HEAP_SIZE];
#else
    static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
static size_t xNextFreeByte = ( size_t ) 0;

/*-----------------------------------------------------------*/
static uint8_t *pucAlignedHeap = NULL; /* << EST: make it global, so it can be re-initialized */

void * pvPortMallocExt( size_t xWantedSize, unsigned int heapTag) /* << EST */
{
    void * pvReturn = NULL;
//static uint8_t *pucAlignedHeap = NULL; /* << EST: make it global so it can be re-initialized */

    /* Ensure that blocks are always aligned. */
    #if ( portBYTE_ALIGNMENT != 1 )
    {
        if( xWantedSize & portBYTE_ALIGNMENT_MASK )
        {
            /* Byte alignment required. Check for overflow. */
            if( ( xWantedSize + ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) ) ) > xWantedSize )
            {
                xWantedSize += ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) );
            }
            else
            {
                xWantedSize = 0;
            }
        }
    }
    #endif /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        if( pucAlignedHeap == NULL )
        {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
  SEGGER_SYSVIEW_HeapDefine(ucHeap, ucHeap, sizeof(ucHeap), 0);
  SEGGER_SYSVIEW_NameResource((uint32_t)ucHeap, "heap1");
#endif
            /* Ensure the heap starts on a correctly aligned boundary. */
            pucAlignedHeap = ( uint8_t * ) ( ( ( portPOINTER_SIZE_TYPE ) & ucHeap[ portBYTE_ALIGNMENT - 1 ] ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
        }

        /* Check there is enough room left for the allocation and. */
        if( ( xWantedSize > 0 ) &&                                /* valid size */
            ( ( xNextFreeByte + xWantedSize ) < configADJUSTED_HEAP_SIZE ) &&
            ( ( xNextFreeByte + xWantedSize ) > xNextFreeByte ) ) /* Check for overflow. */
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = pucAlignedHeap + xNextFreeByte;
            xNextFreeByte += xWantedSize;
        }

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
        if (heapTag!=(unsigned)-1) {
            SEGGER_SYSVIEW_HeapAllocEx(ucHeap, pvReturn, xWantedSize, heapTag);
        } else {
            SEGGER_SYSVIEW_HeapAlloc(ucHeap, pvReturn, xWantedSize);
        }
#else
        traceMALLOC( pvReturn, xWantedSize );
#endif
    }
    ( void ) xTaskResumeAll();

    #if ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        if( pvReturn == NULL )
        {
	#if 1/* << EST: Using configuration macro name for hook */
    extern void configUSE_MALLOC_FAILED_HOOK_NAME( void );
	configUSE_MALLOC_FAILED_HOOK_NAME();
	#else /* << EST */
	vApplicationMallocFailedHook();
	#endif
        }
    }
    #endif

    return pvReturn;
}
/*-----------------------------------------------------------*/

void *pvPortMalloc(size_t xWantedSize) { /* << EST */
  return pvPortMallocExt(xWantedSize, -1);
}
/*-----------------------------------------------------------*/

void vPortFree( void * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( void ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == NULL );
}
/*-----------------------------------------------------------*/

void vPortInitialiseBlocks( void )
{
    /* Only required when static memory is not cleared. */
    xNextFreeByte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( void )
{
    return( configADJUSTED_HEAP_SIZE - xNextFreeByte );
}
/*-----------------------------------------------------------*/

#if 1 /* << EST */
void vPortInitializeHeap(void) {
  xNextFreeByte = 0;
  pucAlignedHeap = NULL;
}
#endif
#endif /* configUSE_HEAP_SCHEME==1 */ /* << EST */

