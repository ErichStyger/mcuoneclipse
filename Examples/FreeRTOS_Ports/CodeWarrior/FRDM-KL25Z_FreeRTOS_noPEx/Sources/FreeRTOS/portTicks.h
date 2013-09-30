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

void vOnCounterRestart(void);
  /* RTOS tick handler interrupt service routine */

#include "FreeRTOSConfig.h"

/*!
 * \brief Return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time
 * \return Tick counter value. The value is reset at tick interrupt time.
 * */
portLONG uxGetTickCounterValue(void);

/* SysTick is counting down */
#define FREERTOS_HWTC_DOWN_COUNTER     1
#define FREERTOS_HWTC_PERIOD           (configCPU_CLOCK_HZ/configTICK_RATE_HZ)-1UL /* counter is decrementing from this value to zero */

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
#define HWTC_DIVISOR 2

#define HWTC_COUNT (uxGetTickCounterValue())

#if configUSE_TICKLESS_IDLE == 1
extern volatile uint8_t portTickCntr; /* used to find out if we woke up by the tick interrupt */
#endif

#endif /* PORTTICKS_H_ */

