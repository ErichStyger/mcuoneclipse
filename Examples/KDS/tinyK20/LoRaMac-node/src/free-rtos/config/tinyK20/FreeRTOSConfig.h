/*
 FreeRTOS V8.2.0 - Copyright (C) 2015 Real Time Engineers Ltd.
 All rights reserved

 VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

 This file is part of the FreeRTOS distribution.

 FreeRTOS is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

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
#define configGENERATE_STATIC_SOURCES             1 /* 1: it will create 'static' sources to be used without Processor Expert; 0: Processor Expert code generated */
#define configPEX_KINETIS_SDK                     0 /* 1: project is a Kinetis SDK Processor Expert project; 0: No Kinetis Processor Expert project */

#define configGENERATE_RUN_TIME_STATS             0 /* 1: generate runtime statistics; 0: no runtime statistics */
#define configUSE_PREEMPTION                      1 /* 1: pre-emptive mode; 0: cooperative mode */
#define configUSE_IDLE_HOOK                       1 /* 1: use Idle hook; 0: no Idle hook */
#define configUSE_TICK_HOOK                       0 /* 1: use Tick hook; 0: no Tick hook */
#define configUSE_MALLOC_FAILED_HOOK              0 /* 1: use MallocFailed hook; 0: no MallocFailed hook */
#define configTICK_RATE_HZ                        ((TickType_t)1000) /* frequency of tick interrupt */
#define configSYSTICK_USE_LOW_POWER_TIMER         0 /* If using Kinetis Low Power Timer (LPTMR) instead of SysTick timer */
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ    1 /* 1 kHz LPO timer. Set to 1 if not used */
#if configPEX_KINETIS_SDK
/* The SDK variable SystemCoreClock contains the current clock speed */
#define configCPU_CLOCK_HZ                        SystemCoreClock /* CPU clock frequency */
#define configBUS_CLOCK_HZ                        SystemCoreClock /* Bus clock frequency */
#else
/* Adjusted CPU clock to compensate for reference clock skew */
#if defined(NODE_A)
#define configCPU_CLOCK_HZ                        47928000U /* CPU clock frequency */
#elif defined(NODE_B)
#define configCPU_CLOCK_HZ                        47914000U /* CPU clock frequency */
#elif defined(NODE_C)
#define configCPU_CLOCK_HZ                        47905000U /* CPU clock frequency */
#elif defined(NODE_D)
#define configCPU_CLOCK_HZ                        47905000U /* CPU clock frequency */
#elif defined(NODE_E)
#define configCPU_CLOCK_HZ                        47924000U /* CPU clock frequency */
#endif
#define configBUS_CLOCK_HZ                        48000000U /* Bus clock frequency */
#endif /* configPEX_KINETIS_SDK */
#define configSYSTICK_USE_CORE_CLOCK              1 /* System Tick is using core clock  */
#define configSYSTICK_CLOCK_DIVIDER               1 /* no divider */
#define configSYSTICK_CLOCK_HZ                    ((configCPU_CLOCK_HZ)/configSYSTICK_CLOCK_DIVIDER) /* frequency of system tick counter */
#define configMINIMAL_STACK_SIZE                  ((unsigned portSHORT)200) /* stack size in addressable stack units */
/*----------------------------------------------------------*/
/* Heap Memory */
#define configFRTOS_MEMORY_SCHEME                 2 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc) or 4 (coalesc blocks) */
#define configTOTAL_HEAP_SIZE                     ((size_t)(0x2000)) /* size of heap in bytes */
#define configUSE_HEAP_SECTION_NAME               1 /* set to 1 if a custom section name (configHEAP_SECTION_NAME_STRING) shall be used, 0 otherwise */
#if configUSE_HEAP_SECTION_NAME
#define configHEAP_SECTION_NAME_STRING            ".m_data_20000000" /* heap section name (use e.g. ".m_data_20000000" for gcc and "m_data_20000000" for IAR). Check your linker file for the name used. */
#endif
/*----------------------------------------------------------*/
#define configMAX_TASK_NAME_LEN                   12 /* task name length */
#define configUSE_TRACE_FACILITY                  1
#define configUSE_TRACE_HOOKS                     0 /* not using Percepio Trace hooks */
#define configUSE_STATS_FORMATTING_FUNCTIONS      (configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS)
#define configUSE_16_BIT_TICKS                    0
#define configIDLE_SHOULD_YIELD                   1
#define configUSE_CO_ROUTINES                     0
#define configUSE_MUTEXES                         1
#define configCHECK_FOR_STACK_OVERFLOW            1 /* 0 is disabling stack overflow. Set it to 1 for Method1 or 2 for Method2 */
#define configUSE_RECURSIVE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE                 0
#define configUSE_QUEUE_SETS                      0
#define configUSE_COUNTING_SEMAPHORES             1
#define configUSE_APPLICATION_TASK_TAG            0
/* Tickless Idle Mode ----------------------------------------------------------*/
#define configUSE_TICKLESS_IDLE                   0 /* set to 1 for tickless idle mode, 0 otherwise */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP     2 /* number of ticks must be larger than this to enter tickless idle mode */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK     0 /* set to 1 to enable application hook, zero otherwise */
#define configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME xEnterTicklessIdle /* function name of decision hook */

#define configMAX_PRIORITIES                      ((unsigned portBASE_TYPE)6)
#define configMAX_CO_ROUTINE_PRIORITIES           2

/* Software timer definitions. */
#define configUSE_TIMERS                          1
#define configTIMER_TASK_PRIORITY                 ( configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                  8
#define configTIMER_TASK_STACK_DEPTH              ( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
 to exclude the API function. */
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
#define INCLUDE_xTaskGetCurrentTaskHandle         0
#define INCLUDE_xTaskGetIdleTaskHandle            0
#define INCLUDE_eTaskGetState                     0
#define INCLUDE_pcTaskGetTaskName                 0
#define INCLUDE_xEventGroupSetBitFromISR          1
#define INCLUDE_xTimerPendFunctionCall            1
/* -------------------------------------------------------------------- */
/* Macros to identify the compiler used: */
#define configCOMPILER_ARM_GCC               1 /* GNU ARM gcc compiler */
#define configCOMPILER_ARM_IAR               2 /* IAR ARM compiler */
#define configCOMPILER_ARM_FSL               3 /* Legacy Freescale ARM compiler */
#define configCOMPILER_ARM_KEIL              4 /* ARM/Keil compiler */
#define configCOMPILER_S08_FSL               5 /* Freescale HCS08 compiler */
#define configCOMPILER_S12_FSL               6 /* Freescale HCS12(X) compiler */
#define configCOMPILER_CF1_FSL               7 /* Freescale ColdFire V1 compiler */
#define configCOMPILER_CF2_FSL               8 /* Freescale ColdFire V2 compiler */
#define configCOMPILER_DSC_FSL               9 /* Freescale DSC compiler */

#define configCOMPILER                            configCOMPILER_ARM_GCC
/* -------------------------------------------------------------------- */
/* CPU family identification */
#define configCPU_FAMILY_S08                 1  /* S08 core */
#define configCPU_FAMILY_S12                 2  /* S12(X) core */
#define configCPU_FAMILY_CF1                 3  /* ColdFire V1 core */
#define configCPU_FAMILY_CF2                 4  /* ColdFire V2 core */
#define configCPU_FAMILY_DSC                 5  /* 56800/DSC */
#define configCPU_FAMILY_ARM_M0P             6  /* ARM Cortex-M0+ */
#define configCPU_FAMILY_ARM_M4              7  /* ARM Cortex-M4 */
#define configCPU_FAMILY_ARM_M4F             8  /* ARM Cortex-M4F (with floating point unit) */
/* Macros to identify set of core families */
#define configCPU_FAMILY_IS_ARM_M4(fam)      (((fam)==configCPU_FAMILY_ARM_M4)  || ((fam)==configCPU_FAMILY_ARM_M4F))
#define configCPU_FAMILY_IS_ARM(fam)         (((fam)==configCPU_FAMILY_ARM_M0P) || configCPU_FAMILY_IS_ARM_M4(fam))

#define configCPU_FAMILY                          configCPU_FAMILY_ARM_M4
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

