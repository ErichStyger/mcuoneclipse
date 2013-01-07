/*
 * portTicks.h
 *
 *  Interface header file to the Processor Expert Tick counter.
 *  This file is used to access the interface, especially for performance
 *  counters (e.g. for Percepio Trace).
 *  That way the a module can interface this wrapper header file instead
 *  of one of the standard FreeRTOS header files.
 *
 *  Created on: 05.07.2012
 *      Author: Erich Styger
 */

#ifndef PORTTICKS_H_
#define PORTTICKS_H_

%if (CPUfamily = "Kinetis")

void vOnCounterRestart(void);
  /* RTOS tick handler */
%endif

%ifdef TickCntr %- non-LDD version
/* support for trace and access to tick counter */
#include "%@TickCntr@'ModuleName'.h"

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
#define HWTC_DIVISOR 2
%else
#define HWTC_DIVISOR 1
%endif

#define HWTC_COUNT (uxGetTickCounterValue())


#endif /* PORTTICKS_H_ */
