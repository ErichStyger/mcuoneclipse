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

#ifndef PORTTICKS_H_
#define PORTTICKS_H_

/*
 *  Interface header file to the Processor Expert Tick counter.
 *  This file is used to access the interface, especially for performance
 *  counters (e.g. for Percepio Trace).
 *  That way the a module can interface this wrapper header file instead
 *  of one of the standard FreeRTOS header files.
 */
#include "MCUC1.h" /* include SDK and API used */

#if MCUC1_CONFIG_SDK_VERSION_USED == MCUC1_CONFIG_SDK_PROCESSOR_EXPERT
  #include "Cpu.h" /* include CPU module because of dependency to CPU clock rate */
#endif
#include "FreeRTOSConfig.h"
#include "portmacro.h"

#if MCUC1_CONFIG_NXP_SDK_USED
  extern uint32_t SystemCoreClock; /* in Kinetis SDK, this contains the system core clock speed */
#endif

/*!
 * \brief Return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time
 * \return Tick counter value. The value is reset at tick interrupt time.
 * */
portLONG uxGetTickCounterValue(void);

#if configSYSTICK_USE_LOW_POWER_TIMER
  #define FREERTOS_HWTC_DOWN_COUNTER     0 /* LPTM is counting up */
  #define FREERTOS_HWTC_PERIOD           ((1000/configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ)-1UL) /* counter is incrementing from zero to this value */
#else
  #define FREERTOS_HWTC_DOWN_COUNTER     1 /* SysTick is counting down */
  #define FREERTOS_HWTC_PERIOD           ((configCPU_CLOCK_HZ/configTICK_RATE_HZ)-1UL) /* counter is decrementing from this value to zero */
#endif

#if configUSE_TICKLESS_IDLE == 1
  extern volatile uint8_t portTickCntr; /* used to find out if we woke up by the tick interrupt */
#endif

#define FREERTOS_HWTC_FREQ_HZ            configTICK_RATE_HZ

#if configUSE_TRACE_HOOKS /* using Percepio Trace */
#if (TRC_CFG_HARDWARE_PORT == TRC_HARDWARE_PORT_PROCESSOR_EXPERT)
  /* tick information for Percepio Trace */

  /* undefine previous values, where dummy anyway: make sure this header file is included last! */
  #undef TRC_HWTC_COUNT_DIRECTION
  #undef TRC_HWTC_PERIOD
  #undef TRC_HWTC_DIVISOR
  #undef TRC_HWTC_COUNT

  #if FREERTOS_HWTC_DOWN_COUNTER
    #define TRC_HWTC_COUNT_DIRECTION  DIRECTION_DECREMENTING
    #define TRC_HWTC_PERIOD           FREERTOS_HWTC_PERIOD /* counter is decrementing from this value to zero */
  #else
    #define TRC_HWTC_COUNT_DIRECTION  DIRECTION_INCREMENTING
    #define TRC_HWTC_PERIOD           FREERTOS_HWTC_PERIOD /* counter is incrementing from zero to this value */
  #endif

  #if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
    #if configSYSTICK_USE_LOW_POWER_TIMER
      #define TRC_HWTC_DIVISOR 1 /* divisor for slow counter tick value */
    #else
      #define TRC_HWTC_DIVISOR 2 /* divisor for fast counter tick value */
    #endif
  #else
    #define TRC_HWTC_DIVISOR 1
  #endif

  #define TRC_HWTC_COUNT              (uxGetTickCounterValue())
  #define TRC_HWTC_TYPE               TRC_FREE_RUNNING_32BIT_INCR
  #define TRC_IRQ_PRIORITY_ORDER      0  /* 0: lower IRQ prios mean higher priority, 1: otherwise */
  #define TRC_HWTC_FREQ_HZ            FREERTOS_HWTC_FREQ_HZ
#endif
#endif /* configUSE_TRACE_HOOKS */

#endif /* PORTTICKS_H_ */

