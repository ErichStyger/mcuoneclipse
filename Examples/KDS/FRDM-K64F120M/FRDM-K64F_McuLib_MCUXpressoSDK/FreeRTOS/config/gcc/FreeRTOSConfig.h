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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "MCUC1.h" /* SDK and API used */
#include "FRTOS1config.h" /* extra configuration settings not part of the original FreeRTOS ports */

#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H           1 /* 1: include additional header file at the end of task.c to help with debugging in GDB in combination with configUSE_TRACE_FACILITY; 0: no extra file included. */
#define configENABLE_BACKWARD_COMPATIBILITY                 0 /* 1: enable backward compatibility mode, using old names in kernel. 0: use new kernel structure names (recommended) */
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
#ifndef configGENERATE_RUN_TIME_STATS_USE_TICKS
  #define configGENERATE_RUN_TIME_STATS_USE_TICKS 1 /* 1: Use the RTOS tick counter as runtime counter. 0: use extra timer */
#endif
#ifndef configGENERATE_RUN_TIME_STATS
  #define configGENERATE_RUN_TIME_STATS           1 /* 1: generate runtime statistics; 0: no runtime statistics */
#endif
#if configGENERATE_RUN_TIME_STATS
  #if configGENERATE_RUN_TIME_STATS_USE_TICKS
    #ifndef portCONFIGURE_TIMER_FOR_RUN_TIME_STATS
      #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() /* nothing */ /* default: use Tick counter as runtime counter */
   #endif
   #ifndef portGET_RUN_TIME_COUNTER_VALUE
     #define portGET_RUN_TIME_COUNTER_VALUE()          xTaskGetTickCountFromISR() /* default: use Tick counter as runtime counter */
    #endif
  #else /* use dedicated timer */
    #ifndef portCONFIGURE_TIMER_FOR_RUN_TIME_STATS
      extern void FRTOS1_AppConfigureTimerForRuntimeStats(void);
      #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() FRTOS1_AppConfigureTimerForRuntimeStats()
    #endif
    #ifndef portGET_RUN_TIME_COUNTER_VALUE
      extern uint32_t FRTOS1_AppGetRuntimeCounterValueFromISR(void);
      #define portGET_RUN_TIME_COUNTER_VALUE()         FRTOS1_AppGetRuntimeCounterValueFromISR()
    #endif
  #endif
#else /* no runtime stats, use empty macros */
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()     /* nothing */
  #define portGET_RUN_TIME_COUNTER_VALUE()             /* nothing */
#endif
#ifndef configUSE_PREEMPTION
  #define configUSE_PREEMPTION                    1 /* 1: pre-emptive mode; 0: cooperative mode */
#endif
#ifndef configUSE_TIME_SLICING
  #define configUSE_TIME_SLICING                  1 /* 1: use time slicing; 0: don't time slice at tick interrupt time */
#endif
#ifndef configUSE_IDLE_HOOK
  #define configUSE_IDLE_HOOK                     1 /* 1: use Idle hook; 0: no Idle hook */
#endif
#ifndef configUSE_IDLE_HOOK_NAME
  #define configUSE_IDLE_HOOK_NAME                FRTOS1_vApplicationIdleHook
#endif
#ifndef configUSE_TICK_HOOK
  #define configUSE_TICK_HOOK                     1 /* 1: use Tick hook; 0: no Tick hook */
#endif
#ifndef configUSE_TICK_HOOK_NAME
  #define configUSE_TICK_HOOK_NAME                FRTOS1_vApplicationTickHook
#endif
#ifndef configUSE_MALLOC_FAILED_HOOK
  #define configUSE_MALLOC_FAILED_HOOK            1 /* 1: use MallocFailed hook; 0: no MallocFailed hook */
#endif
#ifndef configUSE_MALLOC_FAILED_HOOK_NAME
  #define configUSE_MALLOC_FAILED_HOOK_NAME       FRTOS1_vApplicationMallocFailedHook
#endif
#ifndef configTICK_RATE_HZ
  #define configTICK_RATE_HZ                      (100) /* frequency of tick interrupt */
#endif
#define portTICK_RATE_MS                          (1000/configTICK_RATE_HZ) /* needed for legacy drivers and modules like lwIP */
#ifndef configSYSTICK_USE_LOW_POWER_TIMER
  #define configSYSTICK_USE_LOW_POWER_TIMER       0 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#endif
#ifndef configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ
  #define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ  1000 /* Frequency of low power timer */
#endif
#if MCUC1_CONFIG_NXP_SDK_USED \
    || MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_GENERIC \
    || MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_NORDIC_NRF5 \
    || MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_RPI_PICO
/* The CMSIS variable SystemCoreClock contains the current clock speed */
  extern uint32_t SystemCoreClock;
  #define configCPU_CLOCK_HZ                      SystemCoreClock /* CPU clock frequency */
  #define configBUS_CLOCK_HZ                      SystemCoreClock /* Bus clock frequency */
#else
  #define configCPU_CLOCK_HZ                      CPU_CORE_CLK_HZ /* CPU clock frequency */
  #define configBUS_CLOCK_HZ                      CPU_BUS_CLK_HZ /* Bus clock frequency */
#endif /* #if MCUC1_CONFIG_NXP_SDK_USED */
#define configSYSTICK_USE_CORE_CLOCK              1 /* System Tick is using core clock  */
#define configSYSTICK_CLOCK_DIVIDER               1 /* no divider */
#define configSYSTICK_CLOCK_HZ                    ((configCPU_CLOCK_HZ)/configSYSTICK_CLOCK_DIVIDER) /* frequency of system tick counter */
#ifndef configMINIMAL_STACK_SIZE
  #define configMINIMAL_STACK_SIZE                (200) /* stack size in addressable stack units */
#endif

#ifndef configNUMBER_OF_CORES
  #define configNUMBER_OF_CORES                   (1) /* number of cores for the kernel */
#endif

#ifndef configUSE_MINI_LIST_ITEM
	#define configUSE_MINI_LIST_ITEM (1)
	/*!< MiniListItem_t is used for start and end marker nodes in a FreeRTOS list and ListItem_t is used for all other nodes in a FreeRTOS list.
	 * When configUSE_MINI_LIST_ITEM is set to 0, MiniListItem_t and ListItem_t are both the same. When configUSE_MINI_LIST_ITEM is set to 1,
	 * MiniListItem_t contains 3 fewer fields than ListItem_t which saves some RAM at the cost of violating strict aliasing rules which some compilers
	 * depend on for optimization. If left undefined, configUSE_MINI_LIST_ITEM defaults to 1 for backward compatibility.
	 */
#endif
/*----------------------------------------------------------*/
/* Heap Memory */
#ifndef configUSE_HEAP_SCHEME
  #define configUSE_HEAP_SCHEME                   4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#endif /* configUSE_HEAP_SCHEME */
#define configFRTOS_MEMORY_SCHEME                 configUSE_HEAP_SCHEME /* for backwards compatible only with legacy name */
#ifndef configTOTAL_HEAP_SIZE
  #define configTOTAL_HEAP_SIZE                   (16384) /* size of heap in bytes */
#endif /* configTOTAL_HEAP_SIZE */
#ifndef configUSE_HEAP_SECTION_NAME
  #define configUSE_HEAP_SECTION_NAME             0 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
#endif
#ifndef configHEAP_SECTION_NAME_STRING
  #define configHEAP_SECTION_NAME_STRING          ".m_data_20000000" /* heap section name (use e.g. ".m_data_20000000" for KDS/gcc, ".bss.$SRAM_LOWER.FreeRTOS" for MCUXpresso or "m_data_20000000" for IAR). Check your linker file for the name used. */
#endif
#define configAPPLICATION_ALLOCATED_HEAP          0 /* set to one if application is defining heap ucHeap[] variable, 0 otherwise */
#ifndef configSUPPORT_DYNAMIC_ALLOCATION
  #define configSUPPORT_DYNAMIC_ALLOCATION        1 /* 1: make dynamic allocation functions for RTOS available. 0: only static functions are allowed */
#endif
#ifndef configSUPPORT_STATIC_ALLOCATION
  #define configSUPPORT_STATIC_ALLOCATION         0 /* 1: make static allocation functions for RTOS available. 0: only dynamic functions are allowed */
#endif
#define configUSE_NEWLIB_REENTRANT                (configUSE_HEAP_SCHEME==6) /* 1: a newlib reent structure will be allocated for each task; 0: no such reentr structure used */
/*----------------------------------------------------------*/
#ifndef configMAX_TASK_NAME_LEN
  #define configMAX_TASK_NAME_LEN                 12 /* task name length in bytes */
#endif
#ifndef configUSE_TRACE_FACILITY
  #define configUSE_TRACE_FACILITY                1 /* 1: include additional structure members and functions to assist with execution visualization and tracing, 0: no runtime stats/trace */
#endif
#ifndef configUSE_STATS_FORMATTING_FUNCTIONS
  #define configUSE_STATS_FORMATTING_FUNCTIONS    (configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS)
#endif
#define configUSE_16_BIT_TICKS                    0 /* 1: use 16bit tick counter type, 0: use 32bit tick counter type */
#ifndef configIDLE_SHOULD_YIELD
  #define configIDLE_SHOULD_YIELD                 1 /* 1: the IDEL task will yield as soon as possible. 0: The IDLE task waits until preemption. */
#endif
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
  #define configUSE_PORT_OPTIMISED_TASK_SELECTION (0 && configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)) /* 1: the scheduler uses an optimized task selection as defined by the port (if available). 0: normal task selection is used */
#endif
#ifndef configUSE_CO_ROUTINES
  #define configUSE_CO_ROUTINES                   0
#endif
#ifndef configUSE_MUTEXES
  #define configUSE_MUTEXES                       1
#endif
#ifndef configCHECK_FOR_STACK_OVERFLOW
  #define configCHECK_FOR_STACK_OVERFLOW          1 /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */
#endif
#ifndef configCHECK_FOR_STACK_OVERFLOW_NAME
  #define configCHECK_FOR_STACK_OVERFLOW_NAME     FRTOS1_vApplicationStackOverflowHook
#endif
#ifndef configUSE_RECURSIVE_MUTEXES
  #define configUSE_RECURSIVE_MUTEXES             1
#endif
#ifndef configQUEUE_REGISTRY_SIZE
  #define configQUEUE_REGISTRY_SIZE               5
#endif
#ifndef configUSE_QUEUE_SETS
  #define configUSE_QUEUE_SETS                    0
#endif
#ifndef configUSE_COUNTING_SEMAPHORES
  #define configUSE_COUNTING_SEMAPHORES           1
#endif
#ifndef configUSE_APPLICATION_TASK_TAG
  #define configUSE_APPLICATION_TASK_TAG          0
#endif
#ifndef configUSE_TASK_NOTIFICATIONS
  #define configUSE_TASK_NOTIFICATIONS            1
#endif
/* Tickless Idle Mode ----------------------------------------------------------*/
#ifndef configUSE_TICKLESS_IDLE
  #define configUSE_TICKLESS_IDLE                 1 /* set to 1 for tickless idle mode, 0 otherwise */
#endif
#ifndef configEXPECTED_IDLE_TIME_BEFORE_SLEEP
  #define configEXPECTED_IDLE_TIME_BEFORE_SLEEP   2 /* number of ticks must be larger than this to enter tickless idle mode */
#endif
#ifndef configUSE_TICKLESS_IDLE_DECISION_HOOK
  #define configUSE_TICKLESS_IDLE_DECISION_HOOK   1 /* set to 1 to enable application hook, zero otherwise */
#endif
#ifndef configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME
  #define configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME xEnterTicklessIdle /* function name of decision hook */
#endif
#ifndef configNUM_THREAD_LOCAL_STORAGE_POINTERS
  #define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0 /* number of tread local storage pointers, 0 to disable functionality */
#endif

#ifndef configMAX_PRIORITIES
  #define configMAX_PRIORITIES                    6 /* task priorities can be from 0 up to this value-1 */
#endif
#define configMAX_CO_ROUTINE_PRIORITIES           2 /* co-routine priorities can be from 0 up to this value-1 */

/* the following needs to be defined (present) or not (not present)! */
#define configTASK_RETURN_ADDRESS                 0 /* return address of task is zero */

#ifndef configRECORD_STACK_HIGH_ADDRESS
  #define configRECORD_STACK_HIGH_ADDRESS         1  /* 1: record stack high address for the debugger, 0: do not record stack high address */
#endif

/* Software timer definitions. */
#ifndef configUSE_TIMERS
  #define configUSE_TIMERS                        0 /* set to 1 to enable software timers */
#endif
#ifndef configTIMER_TASK_PRIORITY
  #define configUSE_TIMERS                        0 /* set to 1 to enable software timers */
#endif
#ifndef configTIMER_QUEUE_LENGTH
  #define configTIMER_QUEUE_LENGTH                10U /* size of queue for the timer task */
#endif
#ifndef configTIMER_TASK_STACK_DEPTH
  #define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE)
#endif
#ifndef INCLUDE_xEventGroupSetBitFromISR
  #define INCLUDE_xEventGroupSetBitFromISR        0 /* 1: function is included; 0: do not include function */
#endif
#ifndef INCLUDE_xTimerPendFunctionCall
  #define INCLUDE_xTimerPendFunctionCall          0 /* 1: function is included; 0: do not include function */
#endif
#ifndef configUSE_DAEMON_TASK_STARTUP_HOOK
  #define configUSE_DAEMON_TASK_STARTUP_HOOK      0 /* 1: use application specific vApplicationDaemonTaskStartupHook(), 0: do not use hook */
#endif

/* Set configUSE_TASK_FPU_SUPPORT to 0 to omit floating point support even
if floating point hardware is otherwise supported by the FreeRTOS port in use.
This constant is not supported by all FreeRTOS ports that include floating
point support. */
#ifndef configUSE_TASK_FPU_SUPPORT
  #define configUSE_TASK_FPU_SUPPORT              1
#endif
/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function. */
#ifndef INCLUDE_vTaskEndScheduler
  #define INCLUDE_vTaskEndScheduler               0
#endif
#ifndef INCLUDE_vTaskPrioritySet
  #define INCLUDE_vTaskPrioritySet                1
#endif
#ifndef INCLUDE_uxTaskPriorityGet
  #define INCLUDE_uxTaskPriorityGet               1
#endif
#ifndef INCLUDE_vTaskDelete
  #define INCLUDE_vTaskDelete                     0
#endif
#ifndef INCLUDE_vTaskCleanUpResources
  #define INCLUDE_vTaskCleanUpResources           1
#endif
#ifndef INCLUDE_vTaskSuspend
  #define INCLUDE_vTaskSuspend                    1
#endif
#ifndef INCLUDE_vTaskDelayUntil
  #define INCLUDE_vTaskDelayUntil                 1
#endif
#ifndef INCLUDE_vTaskDelay
  #define INCLUDE_vTaskDelay                      1
#endif
#ifndef INCLUDE_uxTaskGetStackHighWaterMark
  #define INCLUDE_uxTaskGetStackHighWaterMark     1
#endif
#ifndef INCLUDE_xTaskGetSchedulerState
  #define INCLUDE_xTaskGetSchedulerState          1
#endif
#ifndef INCLUDE_xQueueGetMutexHolder
  #define INCLUDE_xQueueGetMutexHolder            1
#endif
#ifndef INCLUDE_xTaskGetHandle
  #define INCLUDE_xTaskGetHandle                  1
#endif
#ifndef INCLUDE_xTaskAbortDelay
  #define INCLUDE_xTaskAbortDelay                 0
#endif
#ifndef INCLUDE_xTaskGetCurrentTaskHandle
  #define INCLUDE_xTaskGetCurrentTaskHandle       1
#endif
#ifndef INCLUDE_xTaskGetIdleTaskHandle
  #define INCLUDE_xTaskGetIdleTaskHandle          1
#endif
#ifndef INCLUDE_xTaskResumeFromISR
  #define INCLUDE_xTaskResumeFromISR              1
#endif
#ifndef INCLUDE_eTaskGetState
  #define INCLUDE_eTaskGetState                   0
#endif
#ifndef INCLUDE_pcTaskGetTaskName
  #define INCLUDE_pcTaskGetTaskName               1
#endif
/* -------------------------------------------------------------------- */
#ifndef INCLUDE_pxTaskGetStackStart
  #define INCLUDE_pxTaskGetStackStart             (1 && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS)
#endif
/* -------------------------------------------------------------------- */
#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  /* Cortex-M specific definitions. */
  #if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
    #define configPRIO_BITS                       4 /* 4 bits/16 priority levels on ARM Cortex M4 (Kinetis K Family) */
  #else
    #define configPRIO_BITS                       2 /* 2 bits/4 priority levels on ARM Cortex M0+ (Kinetis L Family) */
  #endif

  /* The lowest interrupt priority that can be used in a call to a "set priority" function. */
  #define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15

  /* The highest interrupt priority that can be used by any interrupt service
     routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
     INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
     PRIORITY THAN THIS! (higher priorities are lower numeric values on an ARM Cortex-M). */
  #define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

  /* Interrupt priorities used by the kernel port layer itself.  These are generic
     to all Cortex-M ports, and do not rely on any particular library functions. */
  #define configKERNEL_INTERRUPT_PRIORITY         (configLIBRARY_LOWEST_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))

  /* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
  See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
  #define configMAX_SYSCALL_INTERRUPT_PRIORITY    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))
#elif MCUC1_CONFIG_CPU_IS_RISC_V
  #define configKERNEL_INTERRUPT_PRIORITY         (7)
#endif

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#ifndef configASSERT
  #define configASSERT(x) if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }
  #if 0 /* version for RISC-V with a debug break: */
    #define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); __asm volatile( "ebreak" ); for( ;; ); }
  #endif
#endif

/* RISC-V only: If the target chip includes a Core Local Interrupter (CLINT) then set configCLINT_BASE_ADDRESS to the CLINT base address.
  Otherwise set configCLINT_BASE_ADDRESS to 0.
 */
#define configCLINT_BASE_ADDRESS   0x0

/*---------------------------------------------------------------------------------------*/
/* MPU and TrustZone settings */
#ifndef configENABLE_FPU
  #define configENABLE_FPU        (0)
#endif /* configENABLE_FPU */

#ifndef configENABLE_MPU
  #define configENABLE_MPU        (0)
#endif /* configENABLE_MPU */

#ifndef configENABLE_TRUSTZONE
  #define configENABLE_TRUSTZONE  (0)
#endif /* configENABLE_TRUSTZONE */
/*---------------------------------------------------------------------------------------*/

/* custom include file: */
/* #include "CustomFreeRTOSSettings.h */


#endif /* FREERTOS_CONFIG_H */


