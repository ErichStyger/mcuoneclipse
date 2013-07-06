/*
    FreeRTOS V7.4.2 - Copyright (C) 2013 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.

    >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License
    and the FreeRTOS license exception along with FreeRTOS; if not it can be
    viewed here: http://www.freertos.org/a00114.html and also obtained by
    writing to Real Time Engineers Ltd., contact details for whom are available
    on the FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, books, training, latest versions, 
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, and our new
    fully thread aware and reentrant UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High 
    Integrity Systems, who sell the code with commercial support, 
    indemnification and middleware, under the OpenRTOS brand.
    
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety 
    engineered and independently SIL3 certified version for use in safety and 
    mission critical applications that require provable dependability.
*/
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

%if (CPUfamily = "ColdFireV1") | (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#include <hidef.h>
%endif
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
%if %CollectRuntimeStatisticsGroup='yes'
#define configGENERATE_RUN_TIME_STATS                            %>50 1
%if defined(RuntimeCntr)
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()                 %>50 {%'ModuleName'%.RunTimeCounter = 0; (void)%@RuntimeCntr@'ModuleName'%.Enable();}
#define portGET_RUN_TIME_COUNTER_VALUE()                         %>50 %'ModuleName'%.RunTimeCounter
%elif defined(RuntimeCntrLDD)
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()                 %>50 {%'ModuleName'%.RunTimeCounter = 0; %'ModuleName'%.RunTimeCounterHandle = %@RuntimeCntrLDD@'ModuleName'%.Init(NULL); (void)%@RuntimeCntrLDD@'ModuleName'%.Enable(%'ModuleName'%.RunTimeCounterHandle);}
#define portGET_RUN_TIME_COUNTER_VALUE()                         %>50 %'ModuleName'%.RunTimeCounter
%endif
%else
#define configGENERATE_RUN_TIME_STATS                            %>50 0
%endif
%-
%if UsePreemption = 'yes'
#define configUSE_PREEMPTION                                     %>50 1
%else
#define configUSE_PREEMPTION                                     %>50 0
%endif
%ifdef vApplicationIdleHook
#define configUSE_IDLE_HOOK                                      %>50 1
%else
#define configUSE_IDLE_HOOK                                      %>50 0
%endif
%ifdef vApplicationTickHook
#define configUSE_TICK_HOOK                                      %>50 1
%else
#define configUSE_TICK_HOOK                                      %>50 0
%endif
%ifdef vApplicationMallocFailedHook
#define configUSE_MALLOC_FAILED_HOOK                             %>50 1
%else
#define configUSE_MALLOC_FAILED_HOOK                             %>50 0
%endif
#define configCPU_CLOCK_HZ                                       %>50 CPU_BUS_CLK_HZ
#define configTICK_RATE_HZ                                       %>50 ((portTickType)%TickRateHz)
#define configMINIMAL_STACK_SIZE                                 %>50 ((unsigned portSHORT)%MinimalStackSize)
#define configTOTAL_HEAP_SIZE                                    %>50 ((size_t)(%TotalHeapSize))
#define configMAX_TASK_NAME_LEN                                  %>50 %TaskNameLength
%if %UseTraceFacility='yes'
#define configUSE_TRACE_FACILITY                                 %>50 1
%else
#define configUSE_TRACE_FACILITY                                 %>50 0
%endif
%if %Use16bitTicks='yes'
#define configUSE_16_BIT_TICKS                                   %>50 1
%else
#define configUSE_16_BIT_TICKS                                   %>50 0
%endif
%if %IdleShouldYield='yes'
#define configIDLE_SHOULD_YIELD                                  %>50 1
%else
#define configIDLE_SHOULD_YIELD                                  %>50 0
%endif
%if %UseCoroutines='yes'
#define configUSE_CO_ROUTINES                                    %>50 1
%else
#define configUSE_CO_ROUTINES                                    %>50 0
%endif
%if %UseMutexes='yes'
#define configUSE_MUTEXES                                        %>50 1
%else
#define configUSE_MUTEXES                                        %>50 0
%endif
%-
%ifdef vApplicationStackOverflowHook
#define configCHECK_FOR_STACK_OVERFLOW                           %>50 %StackOverflowCheckingMethodNumber
%else
#define configCHECK_FOR_STACK_OVERFLOW                           %>50 0
%endif
%-
%if %UseRecursiveMutexes='yes'
#define configUSE_RECURSIVE_MUTEXES                              %>50 1
%else
#define configUSE_RECURSIVE_MUTEXES                              %>50 0
%endif
%-
#define configQUEUE_REGISTRY_SIZE                                %>50 %QueueRegistrySize
%-
%if defined(xSemaphoreCreateCounting)
#define configUSE_COUNTING_SEMAPHORES                            %>50 1
%else
#define configUSE_COUNTING_SEMAPHORES                            %>50 0
%endif
%if %UseApplicationTaskTags='yes'
#define configUSE_APPLICATION_TASK_TAG                           %>50 1
%else
#define configUSE_APPLICATION_TASK_TAG                           %>50 0
%endif
%-
%if %TicklessIdleModeEnabled='yes'
#define configUSE_TICKLESS_IDLE                                  %>50 1
%else
#define configUSE_TICKLESS_IDLE                                  %>50 0
%endif

#define configMAX_PRIORITIES                                     %>50 ((unsigned portBASE_TYPE)%MaxPriority)
#define configMAX_CO_ROUTINE_PRIORITIES                          %>50 %MaxCoroutinePriorities

/* Software timer definitions. */
%if %TimersEnabled='yes'
#define configUSE_TIMERS                                         %>50 1
#define configTIMER_TASK_PRIORITY                                %>50 %TimerTaskPriority
#define configTIMER_QUEUE_LENGTH                                 %>50 %TimerTaskQueueLength
#define configTIMER_TASK_STACK_DEPTH                             %>50 %TimerTaskStackDepth
%else
#define configUSE_TIMERS                                         %>50 0
#define configTIMER_TASK_PRIORITY                                %>50 0
#define configTIMER_QUEUE_LENGTH                                 %>50 0
#define configTIMER_TASK_STACK_DEPTH                             %>50 0
%endif

/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function. */
%- --------------------------------------------------------------------
%ifdef vTaskPrioritySet
#define INCLUDE_vTaskPrioritySet                                 %>50 1
%else
#define INCLUDE_vTaskPrioritySet                                 %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef uxTaskPriorityGet
#define INCLUDE_uxTaskPriorityGet                                %>50 1
%else
#define INCLUDE_uxTaskPriorityGet                                %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef vTaskDelete
#define INCLUDE_vTaskDelete                                      %>50 1
%else
#define INCLUDE_vTaskDelete                                      %>50 0
%endif
%- --------------------------------------------------------------------
%if CleanupResources='yes'
#define INCLUDE_vTaskCleanUpResources                            %>50 1
%else
#define INCLUDE_vTaskCleanUpResources                            %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef vTaskSuspend
#define INCLUDE_vTaskSuspend                                     %>50 1
%else
#define INCLUDE_vTaskSuspend                                     %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef vTaskDelayUntil
#define INCLUDE_vTaskDelayUntil                                  %>50 1
%else
#define INCLUDE_vTaskDelayUntil                                  %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef vTaskDelay
#define INCLUDE_vTaskDelay                                       %>50 1
%else
#define INCLUDE_vTaskDelay                                       %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef uxTaskGetStackHighWaterMark
#define INCLUDE_uxTaskGetStackHighWaterMark                      %>50 1
%else
#define INCLUDE_uxTaskGetStackHighWaterMark                      %>50 0
%endif
%- --------------------------------------------------------------------
%ifdef xTaskGetSchedulerState
#define INCLUDE_xTaskGetSchedulerState                           %>50 1
%else
#define INCLUDE_xTaskGetSchedulerState                           %>50 0
%endif
%- --------------------------------------------------------------------
%if defined(xSemaphoreGetMutexHolder)
#define INCLUDE_xQueueGetMutexHolder                             %>50 1
%else
#define INCLUDE_xQueueGetMutexHolder                             %>50 0
%endif
%- --------------------------------------------------------------------
%if defined(xTaskGetCurrentTaskHandle)
#define INCLUDE_xTaskGetCurrentTaskHandle                        %>50 1
%else
#define INCLUDE_xTaskGetCurrentTaskHandle                        %>50 0
%endif
%- --------------------------------------------------------------------
%if defined(xTaskGetIdleTaskHandle)
#define INCLUDE_xTaskGetIdleTaskHandle                           %>50 1
%else
#define INCLUDE_xTaskGetIdleTaskHandle                           %>50 0
%endif
%- --------------------------------------------------------------------
%if defined(eTaskGetState)
#define INCLUDE_eTaskGetState                                    %>50 1
%else
#define INCLUDE_eTaskGetState                                    %>50 0
%endif
%- --------------------------------------------------------------------
%if defined(pcTaskGetTaskName)
#define INCLUDE_pcTaskGetTaskName                                %>50 1
%else
#define INCLUDE_pcTaskGetTaskName                                %>50 0
%endif
%- --------------------------------------------------------------------

/* Memory Scheme Identification */
%if MemoryScheme = "Scheme1"
#define FRTOS_MEMORY_SCHEME                 %>50 1 /* memory scheme 1 */
%elif MemoryScheme = "Scheme2"
#define FRTOS_MEMORY_SCHEME                 %>50 2 /* memory scheme 2 */
%elif MemoryScheme = "Scheme3"
#define FRTOS_MEMORY_SCHEME                 %>50 3 /* memory scheme 3 */
%elif MemoryScheme = "Scheme4"
#define FRTOS_MEMORY_SCHEME                 %>50 4 /* memory scheme 4 */
%endif

%- --------------------------------------------------------------------
/* CommandInterpreter configuration. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE                        %>50 %CommandIntMaxOutputSize
%- --------------------------------------------------------------------

%if (CPUfamily = "ColdFireV1")
/* It is not advisable to change these values on a ColdFire V1 core. */
%endif
%if (CPUfamily = "MCF")
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    %>50 %ColdFireV2LibraryLowestInterruptPriority /* RTOS disables interrupts with this level and below. Interrupts above this level (higher numbers) shall *not* call RTOS routines */
%elif (CPUfamily = "ColdFireV1") | (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    %>50 7
%elif (CPUfamily = "Kinetis")
/* Cortex-M specific definitions. */
%if ARMFamilyType="M4"
#define configPRIO_BITS                         %>50 4 /* 16 priority levels on ARM Cortex M4 (Kinetis K Family) */
%elif ARMFamilyType="M4F"
#define configPRIO_BITS                         %>50 4 /* 16 priority levels on ARM Cortex M4F (Kinetis K Family) */
%elif ARMFamilyType="M0+"
#define configPRIO_BITS                         %>50 2 /* 4 priority levels on ARM Cortex M0+ (Kinetis L Family) */
%elif
#error "Unknown Cortex CPU! */
%endif

/* The lowest interrupt priority that can be used in a call to a "set priority" function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   %>50 %KinetisLibraryLowestInterruptPriority

/* The highest interrupt priority that can be used by any interrupt service
   routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
   INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
   PRIORITY THAN THIS! (higher priorities are lower numeric values on an ARM Cortex-M). */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  %>50 %KinetisLibraryMaxInterruptPriority

/* Interrupt priorities used by the kernel port layer itself.  These are generic
   to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY              %>50 (configLIBRARY_LOWEST_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY         %>50 (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT(x) if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }
%-
%endif
%- --------------------------------------------------------------------

#endif /* FREERTOS_CONFIG_H */
