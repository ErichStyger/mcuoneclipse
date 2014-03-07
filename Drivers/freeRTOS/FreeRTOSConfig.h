/*
    FreeRTOS V8.0.0 - Copyright (C) 2013 Real Time Engineers Ltd.

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
%if defined(StaticSourcesEnabled) & %StaticSourcesEnabled='yes'
#define configGENERATE_STATIC_SOURCES                            %>50 1 /* if set to one, it will create 'static' sources to be used without Processor Expert */
%else
#define configGENERATE_STATIC_SOURCES                            %>50 0 /* if set to one, it will create 'static' sources to be used without Processor Expert */
%endif
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
#define configTICK_RATE_HZ                                       %>50 ((TickType_t)%TickRateHz) /* frequency of tick interrupt */
%if defined(useARMLowPowerTimer) & useARMLowPowerTimer='yes'
#define configSYSTICK_USE_LOW_POWER_TIMER                        %>50 1 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ                   %>50 1000 /* 1 kHz LPO */
%else
#define configSYSTICK_USE_LOW_POWER_TIMER                        %>50 0 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ                   %>50 1 /* dummy value */
%endif
%if defined(configCPU_CLOCK_HZ)
#define configCPU_CLOCK_HZ                                       %>50 %configCPU_CLOCK_HZ
%else
#define configCPU_CLOCK_HZ                                       %>50 CPU_CORE_CLK_HZ /* CPU core clock defined in %ProcessorModule.h */
%endif
%if defined(configBUS_CLOCK_HZ)
#define configBUS_CLOCK_HZ                                       %>50 %configBUS_CLOCK_HZ
%else
#define configBUS_CLOCK_HZ                                       %>50 CPU_BUS_CLK_HZ /* CPU bus clock defined in %ProcessorModule.h */
%endif
%if defined(useARMSysTickUseCoreClock) & useARMSysTickUseCoreClock='no'
#define configSYSTICK_USE_CORE_CLOCK                             %>50 0 /* System Tick is using external reference clock clock  */
%else
#define configSYSTICK_USE_CORE_CLOCK                             %>50 1 /* System Tick is using core clock  */
%endif
%if defined(useARMSysTickUseCoreClock) & useARMSysTickUseCoreClock='no'
#define configSYSTICK_CLOCK_DIVIDER                              %>50 16 /* Kinetis L is using fixed divider by 16 */
%else
#define configSYSTICK_CLOCK_DIVIDER                              %>50 1 /* no divider */
%endif
%if defined(TickTimerLDD)
#define configSYSTICK_CLOCK_HZ                                   %>50 %@TickTimerLDD@'ModuleName'%.CNT_INP_FREQ_U_0 /* frequency of system tick counter */
%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
#define configSYSTICK_CLOCK_HZ                                   %>50 ((configCPU_CLOCK_HZ)/configSYSTICK_CLOCK_DIVIDER) /* frequency of system tick counter */
%elif defined(TickCntr)
#define configSYSTICK_CLOCK_HZ                                   %>50 %@TickCntr@'ModuleName'%.COUNTER_INPUT_CLOCK_HZ /* frequency of system tick counter */
%else
#define configSYSTICK_CLOCK_HZ                                   %>50 configBUS_CLOCK_HZ /* frequency of system tick counter */
%endif
#define configMINIMAL_STACK_SIZE                                 %>50 ((unsigned portSHORT)%MinimalStackSize)
/*----------------------------------------------------------*/
/* Heap Memory */
%if MemoryScheme = "Scheme1"
#define configFRTOS_MEMORY_SCHEME                 %>50 1 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc) or 4 (coalesc blocks) */
%elif MemoryScheme = "Scheme2"
#define configFRTOS_MEMORY_SCHEME                 %>50 2 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc) or 4 (coalesc blocks) */
%elif MemoryScheme = "Scheme3"
#define configFRTOS_MEMORY_SCHEME                 %>50 3 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc) or 4 (coalesc blocks) */
%elif MemoryScheme = "Scheme4"
#define configFRTOS_MEMORY_SCHEME                 %>50 4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc) or 4 (coalesc blocks) */
%endif
#define configTOTAL_HEAP_SIZE                                    %>50 ((size_t)(%TotalHeapSize)) /* size of heap in bytes */
%if defined(HeapSectionName)
#define configUSE_HEAP_SECTION_NAME                              %>50 1 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
%else
#define configUSE_HEAP_SECTION_NAME                              %>50 0 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
%endif
#if configUSE_HEAP_SECTION_NAME
%if defined(HeapSectionName)
#define configHEAP_SECTION_NAME_STRING   %>50 "%HeapSectionName" /* heap section name (use e.g. ".m_data_20000000" for gcc and "m_data_20000000" for IAR). Check your linker file for the name used. */
%else
#define configHEAP_SECTION_NAME_STRING  %>50 ".m_data_20000000" /* heap section name (use e.g. ".m_data_20000000" for gcc and "m_data_20000000" for IAR). Check your linker file for the name used. */
%endif
#endif
/*----------------------------------------------------------*/
#define configMAX_TASK_NAME_LEN                                  %>50 %TaskNameLength /* task name length */
%if %UseTraceFacility='yes'
#define configUSE_TRACE_FACILITY                                 %>50 1
%else
#define configUSE_TRACE_FACILITY                                 %>50 0
%endif
#define configUSE_STATS_FORMATTING_FUNCTIONS                     %>50 (configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS)
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
#define configCHECK_FOR_STACK_OVERFLOW                           %>50 %StackOverflowCheckingMethodNumber /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */
%else
#define configCHECK_FOR_STACK_OVERFLOW                           %>50 0 /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */  
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
%if %useQueueSets='yes'
#define configUSE_QUEUE_SETS                                     %>50 1
%else
#define configUSE_QUEUE_SETS                                     %>50 0
%endif
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
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP                    %>50 %ExpectedIdleTimeBeforeSleep
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
/* -------------------------------------------------------------------- */
/* Macros to identify the compiler used: */
#define configCOMPILER_ARM_GCC     %>45 1 /* GNU ARM gcc compiler */
#define configCOMPILER_ARM_IAR     %>45 2 /* IAR ARM compiler */
#define configCOMPILER_ARM_FSL     %>45 3 /* Legacy Freescale ARM compiler */
#define configCOMPILER_ARM_KEIL    %>45 4 /* ARM/Keil compiler */
#define configCOMPILER_S08_FSL     %>45 5 /* Freescale HCS08 compiler */
#define configCOMPILER_S12_FSL     %>45 6 /* Freescale HCS12(X) compiler */
#define configCOMPILER_CF1_FSL     %>45 7 /* Freescale ColdFire V1 compiler */
#define configCOMPILER_CF2_FSL     %>45 8 /* Freescale ColdFire V2 compiler */
#define configCOMPILER_DSC_FSL     %>45 9 /* Freescale DSC compiler */

%if (%configCOMPILER='automatic')
%if (%Compiler = "IARARM")
#define configCOMPILER        %>50 configCOMPILER_ARM_IAR
%elif (%Compiler = "GNUC")
#define configCOMPILER        %>50 configCOMPILER_ARM_GCC
%elif (%Compiler = "CodeWarriorARM")
#define configCOMPILER        %>50 configCOMPILER_ARM_FSL
%elif (%Compiler = "ARM_CC")
#define configCOMPILER        %>50 configCOMPILER_ARM_KEIL
%elif (%Compiler = "MetrowerksHC08CC") | (%Compiler = "MetrowerksHCS08CC")
#define configCOMPILER        %>50 configCOMPILER_S08_FSL
%elif (%Compiler = "MetrowerksHC12CC") | (%Compiler = "MetrowerksHC12XCC")
#define configCOMPILER        %>50 configCOMPILER_S12_FSL
%elif (%Compiler = "CodeWarriorColdFireV1")
#define configCOMPILER        %>50 configCOMPILER_CF1_FSL
%elif (%Compiler = "CodeWarriorMCF")
#define configCOMPILER        %>50 configCOMPILER_CF2_FSL
%elif (%Compiler = "MetrowerksDSP")
#define configCOMPILER        %>50 configCOMPILER_DSC_FSL
%else
#define configCOMPILER        %>50 0
#error "unknown compiler %Compiler?"
%endif
%else %- non-automatic compiler selection
#define configCOMPILER        %>50 %configCompiler
%endif
/* -------------------------------------------------------------------- */
/* CPU family identification */
#define configCPU_FAMILY_S08          %>45 1  /* S08 core */
#define configCPU_FAMILY_S12          %>45 2  /* S12(X) core */
#define configCPU_FAMILY_CF1          %>45 3  /* ColdFire V1 core */
#define configCPU_FAMILY_CF2          %>45 4  /* ColdFire V2 core */
#define configCPU_FAMILY_DSC          %>45 5  /* 56800/DSC */
#define configCPU_FAMILY_ARM_M0P      %>45 6  /* ARM Cortex-M0+ */
#define configCPU_FAMILY_ARM_M4       %>45 7  /* ARM Cortex-M4 */
#define configCPU_FAMILY_ARM_M4F      %>45 8  /* ARM Cortex-M4F (with floating point unit) */
/* Macros to identify set of core families */
#define configCPU_FAMILY_IS_ARM_M4(fam)   %>45 (((fam)==configCPU_FAMILY_ARM_M4)  || ((fam)==configCPU_FAMILY_ARM_M4F))
#define configCPU_FAMILY_IS_ARM(fam)      %>45 (((fam)==configCPU_FAMILY_ARM_M0P) || configCPU_FAMILY_IS_ARM_M4(fam))

%if (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#define configCPU_FAMILY  %>50 configCPU_FAMILY_S08
%elif (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
#define configCPU_FAMILY  %>50 configCPU_FAMILY_S12
%elif (CPUfamily = "ColdFireV1")
#define configCPU_FAMILY  %>50 configCPU_FAMILY_CF1
%elif (CPUfamily = "MCF")
#define configCPU_FAMILY  %>50 configCPU_FAMILY_CF2
%elif (CPUfamily = "56800")
#define configCPU_FAMILY  %>50 configCPU_FAMILY_DSC  
%elif (CPUfamily = "Kinetis")
%if %CPUDB_prph_has_feature(CPU,ARM_CORTEX_M0P) = 'yes' %- Note: for IAR this is defined in portasm.s too!
#define configCPU_FAMILY  %>50 configCPU_FAMILY_ARM_M0P
%else %-M4 or M4F
 %if %CPUDB_prph_has_feature(CPU, FPU) = 'no'
#define configCPU_FAMILY  %>50 configCPU_FAMILY_ARM_M4
 %else
#define configCPU_FAMILY  %>50 configCPU_FAMILY_ARM_M4F
 %endif
%endif
%else
#define configCPU_FAMILY  %>50 0
#error "Unknown CPU family %CPUfamily?"
%endif
/* -------------------------------------------------------------------- */
%if (CPUfamily = "ColdFireV1")
/* It is not advisable to change these values on a ColdFire V1 core. */
%endif
%if (CPUfamily = "MCF")
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    %>50 %ColdFireV2LibraryLowestInterruptPriority /* RTOS disables interrupts with this level and below. Interrupts above this level (higher numbers) shall *not* call RTOS routines */
%elif (CPUfamily = "ColdFireV1") | (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    %>50 7
%elif (CPUfamily = "Kinetis")
/* Cortex-M specific definitions. */
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
  #define configPRIO_BITS                         %>50 4 /* 4 bits/16 priority levels on ARM Cortex M4 (Kinetis K Family) */
#else
  #define configPRIO_BITS                         %>50 2 /* 2 bits/4 priority levels on ARM Cortex M0+ (Kinetis L Family) */
#endif

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
