/* Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved. */
/* << EST */
#include "FreeRTOSConfig.h"
#if !defined(configUSE_HEAP_SCHEME) || (configUSE_HEAP_SCHEME==3 && configSUPPORT_DYNAMIC_ALLOCATION==1)

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
 * Implementation of pvPortMalloc() and vPortFree() that relies on the
 * compilers own malloc() and free() implementations.
 *
 * This file can only be used if the linker is configured to to generate
 * a heap memory area.
 *
 * See heap_1.c, heap_2.c and heap_4.c for alternative implementations, and the
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

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
static bool firstMalloc = true;
#endif
/*-----------------------------------------------------------*/

void * pvPortMallocExt( size_t xWantedSize, unsigned int heapTag) /* << EST */
{
    void * pvReturn;

    vTaskSuspendAll();
    {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
    	if (firstMalloc) {
    	  firstMalloc = false;
		  SEGGER_SYSVIEW_HeapDefine(ucHeap, ucHeap, sizeof(ucHeap), sizeof(BlockLink_t));
		  SEGGER_SYSVIEW_NameResource((uint32_t)ucHeap, "heap3");
    	}
#endif
        pvReturn = malloc( xWantedSize );
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
            #if 1 /* << EST: Using configuration macro name for hook */
			extern void configUSE_MALLOC_FAILED_HOOK_NAME( void );
			configUSE_MALLOC_FAILED_HOOK_NAME();
			#else
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
    if( pv != NULL )
    {
        vTaskSuspendAll();
        {
            free( pv );
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
            SEGGER_SYSVIEW_HeapFree(ucHeap, pv);
#else
            traceFREE( pv, 0 );
#endif
        }
        ( void ) xTaskResumeAll();
    }
}
/*-----------------------------------------------------------*/
#if 1 /* << EST */
void vPortInitializeHeap(void) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_SEGGER_SYSTEM_VIEWER_HEAP_EVENTS /* << EST */
  firstMalloc = true;
#endif
}
#endif

#endif /* configUSE_HEAP_SCHEME==3 */ /* << EST */


