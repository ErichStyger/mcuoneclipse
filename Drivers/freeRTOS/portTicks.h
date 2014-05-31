/*
    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

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
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

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

%ifdef TickCntr %- non-LDD version
/* support for trace and access to tick counter */
#include "%@TickCntr@'ModuleName'.h"
#include "portmacro.h"

/*!
 * \brief Return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time
 * \return Tick counter value. The value is reset at tick interrupt time.
 * */
portLONG uxGetTickCounterValue(void);

#ifdef %@TickCntr@'ModuleName'%.DOWN_COUNTER
  #define FREERTOS_HWTC_DOWN_COUNTER     1
  #define FREERTOS_HWTC_PERIOD           %@TickCntr@'ModuleName'%.PERIOD_VALUE_HIGH /* counter is decrementing from this value to zero */
#else
  #define FREERTOS_HWTC_DOWN_COUNTER     0
  #define FREERTOS_HWTC_PERIOD           %@TickCntr@'ModuleName'%.PERIOD_VALUE_HIGH /* counter is incrementing from zero to this value */
#endif

%endif %-TickCntr
%-----------------------------------------------------------------------------
%- Kinetis version using LDD
%-----------------------------------------------------------------------------
%ifdef TickTimerLDD %- LDD version
/* support for trace and access to tick counter */
#include "%@TickTimerLDD@'ModuleName'.h"

/*!
 * \brief Return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time
 * \return Tick counter value. The value is reset at tick interrupt time.
 * */
portLONG uxGetTickCounterValue(void);

#if %@TickTimerLDD@'ModuleName'%.COUNTER_DIR == DIR_DOWN
  #define FREERTOS_HWTC_DOWN_COUNTER     1
  #define FREERTOS_HWTC_PERIOD           %@TickTimerLDD@'ModuleName'%.PERIOD_TICKS /* counter is decrementing from this value to zero */
#else
  #define FREERTOS_HWTC_DOWN_COUNTER     0
  #define FREERTOS_HWTC_PERIOD           %@TickTimerLDD@'ModuleName'%.PERIOD_TICKS /* counter is incrementing from zero to this value */
#endif

%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
%if defined(UseManualClockValues) & UseManualClockValues='yes'  %- have provided manual clock values: no need for Cpu.h
%else
#include "%ProcessorModule.h" /* include CPU module because of dependency to CPU clock rate */
%endif
#include "FreeRTOSConfig.h"
#include "portmacro.h"

#if configPEX_KINETIS_SDK
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
%endif %-TickTimerLDD

/* tick information for Percepio Trace */

/* undefine previous values, where dummy anyway: make sure this header file is included last! */
#undef HWTC_COUNT_DIRECTION
#undef HWTC_PERIOD
#undef HWTC_DIVISOR
#undef HWTC_COUNT

#if FREERTOS_HWTC_DOWN_COUNTER
  #define HWTC_COUNT_DIRECTION  DIRECTION_DECREMENTING
  #define HWTC_PERIOD           FREERTOS_HWTC_PERIOD /* counter is decrementing from this value to zero */
#else
  #define HWTC_COUNT_DIRECTION  DIRECTION_INCREMENTING
  #define HWTC_PERIOD           FREERTOS_HWTC_PERIOD /* counter is incrementing from zero to this value */
#endif
%if %CPUfamily="Kinetis"
#if configSYSTICK_USE_LOW_POWER_TIMER
  #define HWTC_DIVISOR 1 /* divisor for slow counter tick value */
#else
  #define HWTC_DIVISOR 2 /* divisor for fast counter tick value */
#endif
%else
#define HWTC_DIVISOR 1
%endif

#define HWTC_COUNT (uxGetTickCounterValue())

#if configUSE_TICKLESS_IDLE == 1
extern volatile uint8_t portTickCntr; /* used to find out if we woke up by the tick interrupt */
#endif

#endif /* PORTTICKS_H_ */
