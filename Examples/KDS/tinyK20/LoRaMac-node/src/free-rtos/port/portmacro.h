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

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOSConfig.h"
#if configGENERATE_STATIC_SOURCES || configPEX_KINETIS_SDK
  #include <stdint.h>
#else
  #include "PE_Types.h" /* for int8_t, etc */
#endif
/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */
#if (configCOMPILER==configCOMPILER_S12_FSL) || (configCOMPILER==configCOMPILER_S08_FSL)
  /* disabling some warnings as the RTOS sources are not that clean... */
  #pragma MESSAGE DISABLE C5909 /* assignment in condition */
  #pragma MESSAGE DISABLE C2705 /* possible loss of data */
  #pragma MESSAGE DISABLE C5905 /* multiplication with one */
  #pragma MESSAGE DISABLE C5904 /* division by one */
  #pragma MESSAGE DISABLE C5660 /* removed dead code */
  #pragma MESSAGE DISABLE C5917 /* removed dead assignment */
  #pragma MESSAGE DISABLE C4001 /* condition always FALSE */
#endif
#if configCOMPILER==configCOMPILER_S12_FSL
  #pragma MESSAGE DISABLE C12053 /* SP change not in debug information */
  #pragma MESSAGE DISABLE C12056 /* SP debug information incorrect */
#endif

/* Type definitions. */
#define portCHAR               char
#define portFLOAT              float
#define portDOUBLE             double
#define portLONG               long
#define portSHORT              short
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY) || (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portSTACK_TYPE       unsigned long
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portSTACK_TYPE       unsigned char
#endif
typedef portSTACK_TYPE StackType_t;
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY) || (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portBASE_TYPE        long
  typedef long BaseType_t;
  typedef unsigned long UBaseType_t;
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portBASE_TYPE        char
  typedef signed char BaseType_t;
  typedef unsigned char UBaseType_t;
#endif

#if( configUSE_16_BIT_TICKS == 1 )
  typedef uint16_t TickType_t;
  #define portMAX_DELAY      (TickType_t)0xffff
#else
  typedef uint32_t TickType_t;
  #define portMAX_DELAY      (TickType_t)0xffffffff
#endif
/*-----------------------------------------------------------*/
/* Hardware specifics. */
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2)
  #define portBYTE_ALIGNMENT     4
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  #define portBYTE_ALIGNMENT     8
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portBYTE_ALIGNMENT     1
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portBYTE_ALIGNMENT     4
  #define portSTACK_GROWTH       1 /* stack grows from LOW to HIGH */
#endif

#define portTICK_PERIOD_MS      ((TickType_t)1000/configTICK_RATE_HZ)
/*-----------------------------------------------------------*/
/* Critical section management. */
unsigned portLONG ulPortSetIPL(unsigned portLONG);

/* If set to 1, then this port uses the critical nesting count from the TCB rather than
maintaining a separate value and then saving this value in the task stack. */
#define portCRITICAL_NESTING_IN_TCB    0


extern uint32_t ulPortSetInterruptMask();
extern void vPortClearInterruptMask( uint32_t ulNewMaskValue );


#if configCOMPILER==configCOMPILER_DSC_FSL
  /* for DSC, there is a possible skew after enable/disable Interrupts. */
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() \
      asm(nop); asm(nop); asm(nop); asm(nop); asm(nop); asm(nop);
#else
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() /* nothing special needed */
#endif

#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
  #if (configCOMPILER==configCOMPILER_ARM_KEIL)
    __asm uint32_t ulPortSetInterruptMask(void);
    __asm void vPortClearInterruptMask(uint32_t ulNewMask);

    #define portSET_INTERRUPT_MASK()            ulPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK()          vPortClearInterruptMask(0)
  #elif (configCOMPILER==configCOMPILER_ARM_GCC)
    #define portSET_INTERRUPT_MASK()             ulPortSetInterruptMask()
    #define portSET_INTERRUPT_MASK_FROM_ISR()    ulPortSetInterruptMask()
  #elif configCOMPILER==configCOMPILER_ARM_IAR
    void vPortSetInterruptMask(void); /* prototype, implemented in portasm.s */
    void vPortClearInterruptMask(void); /* prototype, implemented in portasm.s */
    #define portSET_INTERRUPT_MASK()    vPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK()  vPortClearInterruptMask()
  #endif
#else /* Cortex-M0+ */
  #if configCOMPILER==configCOMPILER_ARM_KEIL
    #define portSET_INTERRUPT_MASK()              __disable_irq()
    #define portCLEAR_INTERRUPT_MASK()            __enable_irq()
  #else /* IAR, CW ARM or GNU ARM gcc */
    #define portSET_INTERRUPT_MASK()              ulPortSetInterruptMask()
    #define portSET_INTERRUPT_MASK_FROM_ISR()     ulPortSetInterruptMask()
  #endif
#endif

#define portCLEAR_INTERRUPT_MASK()           vPortClearInterruptMask(0)
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortClearInterruptMask(x)

extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);

#if configCOMPILER==configCOMPILER_ARM_KEIL
  #define portDISABLE_ALL_INTERRUPTS()   __disable_irq()
#else /* IAR, CW ARM or GNU ARM gcc */
  #define portDISABLE_ALL_INTERRUPTS()   __asm volatile("cpsid i")
#endif
#define portDISABLE_INTERRUPTS()   portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()    portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()       vPortEnterCritical()
#define portEXIT_CRITICAL()        vPortExitCritical()

/* There are an uneven number of items on the initial stack, so
portALIGNMENT_ASSERT_pxCurrentTCB() will trigger false positive asserts. */
#define portALIGNMENT_ASSERT_pxCurrentTCB (void)
/*-----------------------------------------------------------*/
/* Scheduler utilities. */

extern void vPortYieldFromISR(void);
#define portYIELD()                             vPortYieldFromISR()
#define portEND_SWITCHING_ISR(xSwitchRequired)  if(xSwitchRequired) vPortYieldFromISR()
/*-----------------------------------------------------------*/

/* Architecture specific optimizations. */
#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Generic helper function. */
    __attribute__( ( always_inline ) ) static inline unsigned char ucPortCountLeadingZeros( unsigned long ulBitmap )
    {
      uint8_t ucReturn;

        __asm volatile ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );
        return ucReturn;
    }

    /* Check the configuration. */
    #if( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

    /* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    /*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - ucPortCountLeadingZeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#ifdef configASSERT
#if 0 /* NYI */ && configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* ARM M4(F) core */
  void vPortValidateInterruptPriority( void );
  #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()     vPortValidateInterruptPriority()
#else
  #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()
#endif
#endif

/*-----------------------------------------------------------*/
/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
  extern void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime);
  #define portSUPPRESS_TICKS_AND_SLEEP(xExpectedIdleTime) vPortSuppressTicksAndSleep(xExpectedIdleTime)
#endif
/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)   void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters)         void vFunction(void *pvParameters)
/*-----------------------------------------------------------*/
void vPortStartFirstTask(void);
  /* starts the first task, called from xPortStartScheduler() */

void vPortYieldHandler(void);
  /* handler for the SWI interrupt */

#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
  void vPortEnableVFP(void);
    /* enables floating point support in the CPU */
#endif


/* Prototypes for interrupt service handlers */
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
  void SVC_Handler(void); /* SVC interrupt handler */
  void PendSV_Handler(void); /* PendSV interrupt handler */
  void SysTick_Handler(void); /* Systick interrupt handler */
#else
  void vPortSVCHandler(void); /* SVC interrupt handler */
  void vPortPendSVHandler(void); /* PendSV interrupt handler */
  void vPortTickHandler(void); /* Systick interrupt handler */
#endif

#if configUSE_TICKLESS_IDLE_DECISION_HOOK /* << EST */
BaseType_t configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME(void); /* return pdTRUE if RTOS can enter tickless idle mode, pdFALSE otherwise */
#endif

void prvTaskExitError(void);
  /* handler to catch task exit errors */


#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

