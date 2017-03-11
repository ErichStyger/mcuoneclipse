/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

	***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
	***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
	the FAQ page "My application does not run, what could be wrong?".  Have you
	defined configASSERT()?

	http://www.FreeRTOS.org/support - In return for receiving this top quality
	embedded software for free we request you assist our global community by
	participating in the support forum.

	http://www.FreeRTOS.org/training - Investing in training allows your team to
	be as productive as possible as early as possible.  Now you can receive
	FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
	Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "MCUC1.h" /* SDK and API used */
#include "FRTOS1config.h" /* configuration */

#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1 /* include additional header file to help with debugging in GDB */
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
#define configGENERATE_RUN_TIME_STATS_USE_TICKS   1 /* 1: Use the RTOS tick counter as runtime counter. 0: use extra timer */
#define configGENERATE_RUN_TIME_STATS             1 /* 1: generate runtime statistics; 0: no runtime statistics */
#if configGENERATE_RUN_TIME_STATS
  #if configGENERATE_RUN_TIME_STATS_USE_TICKS
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   /* nothing */ /* default: use Tick counter as runtime counter */
    #define portGET_RUN_TIME_COUNTER_VALUE()           xTaskGetTickCountFromISR() /* default: use Tick counter as runtime counter */
  #else /* use dedicated timer */
    extern uint32_t FRTOS1_AppGetRuntimeCounterValueFromISR(void);
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   FRTOS1_AppConfigureTimerForRuntimeStats()
    #define portGET_RUN_TIME_COUNTER_VALUE()           FRTOS1_AppGetRuntimeCounterValueFromISR()
  #endif
#else /* no runtime stats, use empty macros */
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()     /* nothing */
  #define portGET_RUN_TIME_COUNTER_VALUE()             /* nothing */
#endif
#define configUSE_PREEMPTION                      1 /* 1: pre-emptive mode; 0: cooperative mode */
#define configUSE_TIME_SLICING                    1 /* 1: use time slicing; 0: don't time slice at tick interrupt time */
#define configUSE_IDLE_HOOK                       1 /* 1: use Idle hook; 0: no Idle hook */
#define configUSE_IDLE_HOOK_NAME                  FRTOS1_vApplicationIdleHook
#define configUSE_TICK_HOOK                       1 /* 1: use Tick hook; 0: no Tick hook */
#define configUSE_TICK_HOOK_NAME                  FRTOS1_vApplicationTickHook
#define configUSE_MALLOC_FAILED_HOOK              1 /* 1: use MallocFailed hook; 0: no MallocFailed hook */
#define configUSE_MALLOC_FAILED_HOOK_NAME         FRTOS1_vApplicationMallocFailedHook
#define configTICK_RATE_HZ                        ((TickType_t)100) /* frequency of tick interrupt */
#define configSYSTICK_USE_LOW_POWER_TIMER         0 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ    1 /* 1 kHz LPO timer. Set to 1 if not used */
#if MCUC1_CONFIG_NXP_SDK_USED
/* The SDK variable SystemCoreClock contains the current clock speed */
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
#define configMINIMAL_STACK_SIZE                  (150) /* stack size in addressable stack units */
/*----------------------------------------------------------*/
/* Heap Memory */
#define configUSE_HEAP_SCHEME                     4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks) */
#define configFRTOS_MEMORY_SCHEME   configUSE_HEAP_SCHEME /* for backwards compatible only with legacy name */
#define configTOTAL_HEAP_SIZE                     ((size_t)(8192)) /* size of heap in bytes */
#define configUSE_HEAP_SECTION_NAME               0 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
#if configUSE_HEAP_SECTION_NAME
#define configHEAP_SECTION_NAME_STRING            ".m_data_20000000" /* heap section name (use e.g. ".m_data_20000000" for gcc and "m_data_20000000" for IAR). Check your linker file for the name used. */
#endif
#define configAPPLICATION_ALLOCATED_HEAP          0 /* set to one if application is defining heap ucHeap[] variable, 0 otherwise */
#define configSUPPORT_DYNAMIC_ALLOCATION          1 /* 1: make dynamic allocation functions for RTOS available. 0: only static functions are allowed */
#define configSUPPORT_STATIC_ALLOCATION           0 /* 1: make static allocation functions for RTOS available. 0: only dynamic functions are allowed */
/*----------------------------------------------------------*/
#define configMAX_TASK_NAME_LEN                   12 /* task name length in bytes */
#define configUSE_TRACE_FACILITY                  1 /* 1: include additional structure members and functions to assist with execution visualization and tracing, 0: no runtime stats/trace */
#define configUSE_TRACE_HOOKS                     0 /* 1: Percepio Trace hooks, 0: not using Percepio Trace hooks */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS      0 /* 1: Segger System Viewer hooks, 0: not using Segger System Viewer hooks */
#define configUSE_STATS_FORMATTING_FUNCTIONS      (configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS)
#define configUSE_16_BIT_TICKS                    0 /* 1: use 16bit tick counter type, 0: use 32bit tick counter type */
#define configIDLE_SHOULD_YIELD                   1 /* 1: the IDEL task will yield as soon as possible. 0: The IDLE task waits until preemption. */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   (1 && configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)) /* 1: the scheduler uses an optimized task selection as defined by the port (if available). 0: normal task selection is used */
#define configUSE_CO_ROUTINES                     0
#define configUSE_MUTEXES                         1
#define configCHECK_FOR_STACK_OVERFLOW            1 /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */
#define configCHECK_FOR_STACK_OVERFLOW_NAME       FRTOS1_vApplicationStackOverflowHook
#define configUSE_RECURSIVE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE                 5
#define configUSE_QUEUE_SETS                      0
#define configUSE_COUNTING_SEMAPHORES             1
#define configUSE_APPLICATION_TASK_TAG            0
/* Tickless Idle Mode ----------------------------------------------------------*/
#define configUSE_TICKLESS_IDLE                   0 /* set to 1 for tickless idle mode, 0 otherwise */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP     2 /* number of ticks must be larger than this to enter tickless idle mode */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK     0 /* set to 1 to enable application hook, zero otherwise */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME xEnterTicklessIdle /* function name of decision hook */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS   0 /* number of tread local storage pointers, 0 to disable functionality */

#define configMAX_PRIORITIES                      6
#define configMAX_CO_ROUTINE_PRIORITIES           2

#define configTASK_RETURN_ADDRESS   0             /* return address of task is zero */

#define configRECORD_STACK_HIGH_ADDRESS           1  /* 1: record stack high address for the debugger, 0: do not record stack high address */

/* Software timer definitions. */
#define configUSE_TIMERS                          0 /* set to 1 to enable software timers */
#define configTIMER_TASK_PRIORITY                 (configMAX_PRIORITIES-1U)
#define configTIMER_QUEUE_LENGTH                  10U
#define configTIMER_TASK_STACK_DEPTH              (configMINIMAL_STACK_SIZE)
#define INCLUDE_xEventGroupSetBitFromISR          0
#define INCLUDE_xTimerPendFunctionCall            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK        0 /* 1: use application specific vApplicationDaemonTaskStartupHook(), 0: do not use hook */

/* Set configUSE_TASK_FPU_SUPPORT to 0 to omit floating point support even
if floating point hardware is otherwise supported by the FreeRTOS port in use.
This constant is not supported by all FreeRTOS ports that include floating
point support. */
#define configUSE_TASK_FPU_SUPPORT                1

/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function. */
#define INCLUDE_vTaskEndScheduler                 0
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       0
#define INCLUDE_vTaskCleanUpResources             1
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_uxTaskGetStackHighWaterMark       1
#define INCLUDE_xTaskGetSchedulerState            1
#define INCLUDE_xQueueGetMutexHolder              1
#define INCLUDE_xTaskGetHandle                    1
#define INCLUDE_xTaskAbortDelay                   0
#define INCLUDE_xTaskGetCurrentTaskHandle         1
#define INCLUDE_xTaskGetIdleTaskHandle            1
#define INCLUDE_xTaskResumeFromISR                1
#define INCLUDE_eTaskGetState                     0
#define INCLUDE_pcTaskGetTaskName                 1
/* -------------------------------------------------------------------- */
#define INCLUDE_pxTaskGetStackStart               (1 && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS)
/* -------------------------------------------------------------------- */
/* Cortex-M specific definitions. */
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
  #define configPRIO_BITS                         4 /* 4 bits/16 priority levels on ARM Cortex M4 (Kinetis K Family) */
#else
  #define configPRIO_BITS                         2 /* 2 bits/4 priority levels on ARM Cortex M0+ (Kinetis L Family) */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority" function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   3

/* The highest interrupt priority that can be used by any interrupt service
   routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
   INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
   PRIORITY THAN THIS! (higher priorities are lower numeric values on an ARM Cortex-M). */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 1

/* Interrupt priorities used by the kernel port layer itself.  These are generic
   to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY           (configLIBRARY_LOWEST_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY      (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT(x) if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }

#endif /* FREERTOS_CONFIG_H */

