/*
 * Copyright (c) 2021-2023 Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef CYCLES_H_
#define CYCLES_H_

#include "platform.h"
#include <stdint.h>
#include "fsl_common.h"

/*! global variables used for efficient access */
extern uint32_t CCounter_startCounter, CCounter_stopCounter;

#if PL_CONFIG_IS_TINY
  #define CCOUNTER_GetCycleCounter()  (*((volatile uint32_t*)0xE0001004))
  /*!< macro to access hardware cycle counter */

  /*! Macros to start/stop measurement */
  #define CCOUNTER_START()  CCounter_startCounter=CCOUNTER_GetCycleCounter()
  #define CCOUNTER_STOP()   CCounter_stopCounter=CCOUNTER_GetCycleCounter()
#elif PL_CONFIG_IS_LPC
  #include "fsl_ctimer.h"

  #define CTIMER                  CTIMER0         /* Timer 0 */
  #define CT_TIMER_GET_VALUE()    CTIMER_GetTimerCountValue(CTIMER)
  #define CT_TIMER_RESET()        CTIMER_Reset(CTIMER)

  #define CTIMER            CTIMER0         /* Timer 0 */
  #define CTIMER_MAT_OUT    kCTIMER_Match_1 /* Match output 1 */
  #define CTIMER_CLK_FREQ   CLOCK_GetFreq(kCLOCK_CoreSysClk)

  /*! Macros to start/stop measurement */
  #define CCOUNTER_START()  CCounter_startCounter=0; CT_TIMER_RESET()
  #define CCOUNTER_STOP()   CCounter_stopCounter=CT_TIMER_GET_VALUE()
#endif

/*!
 * \brief Helper routine to print time spent between start and stop
 * \param msg Pointer to message text to print
 */
void Cycles_LogTime(const char *msg);

/*! \brief run several cycle and time counting tests */
void Cycles_Test(void);

/*! \brief Module de-initialization */
void Cycles_Deinit(void);

/*! \brief Module initialization */
void Cycles_Init(void);

#endif /* CYCLES_H_ */
