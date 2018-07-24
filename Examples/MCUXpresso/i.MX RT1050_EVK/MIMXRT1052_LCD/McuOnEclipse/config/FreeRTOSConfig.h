/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "McuLib.h" /* SDK and API used */
#include "McuRTOSconfig.h" /* extra configuration settings not part of the original FreeRTOS ports */

#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1 /* 1: include additional header file at the end of task.c to help with debugging in GDB in combination with configUSE_TRACE_FACILITY; 0: no extra file included. */
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
    extern uint32_t McuRTOS_AppGetRuntimeCounterValueFromISR(void);
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   McuRTOS_AppConfigureTimerForRuntimeStats()
    #define portGET_RUN_TIME_COUNTER_VALUE()           McuRTOS_AppGetRuntimeCounterValueFromISR()
  #endif
#else /* no runtime stats, use empty macros */
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()     /* nothing */
  #define portGET_RUN_TIME_COUNTER_VALUE()             /* nothing */
#endif
#define configUSE_PREEMPTION                      1 /* 1: pre-emptive mode; 0: cooperative mode */
#define configUSE_TIME_SLICING                    1 /* 1: use time slicing; 0: don't time slice at tick interrupt time */
#define configUSE_IDLE_HOOK                       1 /* 1: use Idle hook; 0: no Idle hook */
#define configUSE_IDLE_HOOK_NAME                  McuRTOS_vApplicationIdleHook
#define configUSE_TICK_HOOK                       1 /* 1: use Tick hook; 0: no Tick hook */
#define configUSE_TICK_HOOK_NAME                  McuRTOS_vApplicationTickHook
#define configUSE_MALLOC_FAILED_HOOK              1 /* 1: use MallocFailed hook; 0: no MallocFailed hook */
#define configUSE_MALLOC_FAILED_HOOK_NAME         McuRTOS_vApplicationMallocFailedHook
#define configTICK_RATE_HZ                        (1000) /* frequency of tick interrupt */
#define configSYSTICK_USE_LOW_POWER_TIMER         0 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ    1 /* 1 kHz LPO timer. Set to 1 if not used */
#if McuLib_CONFIG_NXP_SDK_USED || McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_GENERIC
/* The CMSIS variable SystemCoreClock contains the current clock speed */
  extern uint32_t SystemCoreClock;
  #define configCPU_CLOCK_HZ                      SystemCoreClock /* CPU clock frequency */
  #define configBUS_CLOCK_HZ                      SystemCoreClock /* Bus clock frequency */
#else
  #define configCPU_CLOCK_HZ                      CPU_CORE_CLK_HZ /* CPU clock frequency */
  #define configBUS_CLOCK_HZ                      CPU_BUS_CLK_HZ /* Bus clock frequency */
#endif /* #if McuLib_CONFIG_NXP_SDK_USED */
#define configSYSTICK_USE_CORE_CLOCK              1 /* System Tick is using core clock  */
#define configSYSTICK_CLOCK_DIVIDER               1 /* no divider */
#define configSYSTICK_CLOCK_HZ                    ((configCPU_CLOCK_HZ)/configSYSTICK_CLOCK_DIVIDER) /* frequency of system tick counter */
#define configMINIMAL_STACK_SIZE                  (200) /* stack size in addressable stack units */
/*----------------------------------------------------------*/
/* Heap Memory */
#define configUSE_HEAP_SCHEME                     4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configFRTOS_MEMORY_SCHEME                 configUSE_HEAP_SCHEME /* for backwards compatible only with legacy name */
#define configTOTAL_HEAP_SIZE                     (8192) /* size of heap in bytes */
#define configUSE_HEAP_SECTION_NAME               0 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
#if configUSE_HEAP_SECTION_NAME
#define configHEAP_SECTION_NAME_STRING            ".m_data_20000000" /* heap section name (use e.g. ".m_data_20000000" for gcc and "m_data_20000000" for IAR). Check your linker file for the name used. */
#endif
#define configAPPLICATION_ALLOCATED_HEAP          0 /* set to one if application is defining heap ucHeap[] variable, 0 otherwise */
#define configSUPPORT_DYNAMIC_ALLOCATION          1 /* 1: make dynamic allocation functions for RTOS available. 0: only static functions are allowed */
#define configSUPPORT_STATIC_ALLOCATION           0 /* 1: make static allocation functions for RTOS available. 0: only dynamic functions are allowed */
#define configUSE_NEWLIB_REENTRANT                (configUSE_HEAP_SCHEME==6) /* 1: a newlib reent structure will be allocated for each task; 0: no such reentr structure used */
/*----------------------------------------------------------*/
#define configMAX_TASK_NAME_LEN                   12 /* task name length in bytes */
#define configUSE_TRACE_FACILITY                  1 /* 1: include additional structure members and functions to assist with execution visualization and tracing, 0: no runtime stats/trace */
#define configUSE_STATS_FORMATTING_FUNCTIONS      (configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS)
#define configUSE_16_BIT_TICKS                    0 /* 1: use 16bit tick counter type, 0: use 32bit tick counter type */
#define configIDLE_SHOULD_YIELD                   1 /* 1: the IDEL task will yield as soon as possible. 0: The IDLE task waits until preemption. */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   (0 && configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)) /* 1: the scheduler uses an optimized task selection as defined by the port (if available). 0: normal task selection is used */
#define configUSE_CO_ROUTINES                     0
#define configUSE_MUTEXES                         1
#define configCHECK_FOR_STACK_OVERFLOW            1 /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */
#define configCHECK_FOR_STACK_OVERFLOW_NAME       McuRTOS_vApplicationStackOverflowHook
#define configUSE_RECURSIVE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE                 5
#define configUSE_QUEUE_SETS                      0
#define configUSE_COUNTING_SEMAPHORES             1
#define configUSE_APPLICATION_TASK_TAG            0
/* Tickless Idle Mode ----------------------------------------------------------*/
#define configUSE_TICKLESS_IDLE                   1 /* set to 1 for tickless idle mode, 0 otherwise */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP     2 /* number of ticks must be larger than this to enter tickless idle mode */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK     0 /* set to 1 to enable application hook, zero otherwise */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME xEnterTicklessIdle /* function name of decision hook */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS   0 /* number of tread local storage pointers, 0 to disable functionality */

#define configMAX_PRIORITIES                      6 /* task priorities can be from 0 up to this value-1 */
#define configMAX_CO_ROUTINE_PRIORITIES           2 /* co-routine priorities can be from 0 up to this value-1 */

#define configTASK_RETURN_ADDRESS                 0 /* return address of task is zero */

#define configRECORD_STACK_HIGH_ADDRESS           1  /* 1: record stack high address for the debugger, 0: do not record stack high address */

/* Software timer definitions. */
#define configUSE_TIMERS                          0 /* set to 1 to enable software timers */
#define configTIMER_TASK_PRIORITY                 (configMAX_PRIORITIES-1U)
#define configTIMER_QUEUE_LENGTH                  10U /* size of queue for the timer task */
#define configTIMER_TASK_STACK_DEPTH              (configMINIMAL_STACK_SIZE)
#define INCLUDE_xEventGroupSetBitFromISR          0 /* 1: function is included; 0: do not include function */
#define INCLUDE_xTimerPendFunctionCall            0 /* 1: function is included; 0: do not include function */
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
#define INCLUDE_xTaskAbortDelay                   1
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
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

/* The highest interrupt priority that can be used by any interrupt service
   routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
   INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
   PRIORITY THAN THIS! (higher priorities are lower numeric values on an ARM Cortex-M). */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
   to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY           (configLIBRARY_LOWEST_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY      (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT(x) if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }

#endif /* FREERTOS_CONFIG_H */

