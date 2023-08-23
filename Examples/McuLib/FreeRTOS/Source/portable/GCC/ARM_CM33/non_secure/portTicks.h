/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

#ifndef PORTTICKS_H_
#define PORTTICKS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Interface header file to the Processor Expert Tick counter.
 *  This file is used to access the interface, especially for performance
 *  counters (e.g. for Percepio Trace).
 *  That way the a module can interface this wrapper header file instead
 *  of one of the standard FreeRTOS header files.
 */
#include "McuLib.h" /* include SDK and API used */

#include "FreeRTOSConfig.h"
#include "portmacro.h"

#if !McuLib_CONFIG_PEX_SDK_USED
  extern uint32_t SystemCoreClock; /* in Kinetis SDK, this contains the system core clock speed */
#endif

/*!
 * \brief Return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time
 * \return Tick counter value. The value is reset at tick interrupt time.
 * */
uint32_t uxGetTickCounterValue(void);

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

#if configUSE_PERCEPIO_TRACE_HOOKS /* using Percepio Trace */
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
#endif /* configUSE_PERCEPIO_TRACE_HOOKS */

#ifdef __cplusplus
}
#endif

#endif /* PORTTICKS_H_ */

