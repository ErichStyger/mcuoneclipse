/*
 * Copyright (c) 2021-2023 Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_DO_CYCLE_COUNTING
#include "cycles.h"
#include "fsl_common.h"
#include "benchmark.h"
#if BENCHMARK_USE_STDLIB
  #include <stdio.h>
#else
  #include "McuSemihost.h"
#endif

#if PL_CONFIG_IS_TINY
  /*! \todo determine overhead for measurements */
  #define CCOUNTER_OVERHEAD (10) /* overhead measuring the cycles, empirical value */
#elif PL_CONFIG_IS_LPC
  #define CCOUNTER_OVERHEAD (28) /* overhead measuring the cycles, empirical value */
#endif

uint32_t CCounter_startCounter, CCounter_stopCounter;

#if PL_CONFIG_IS_LPC
/* the LPC845 is a Cortex M0+ and has no hardware cycle counter: therefore we use a normal freerunning timer to measure the time spent */

static void InitTimer(void) {
  ctimer_config_t config;
  ctimer_match_config_t matchConfig;

  CTIMER_GetDefaultConfig(&config);
  CTIMER_Init(CTIMER, &config);
  matchConfig.enableCounterReset = false;
  matchConfig.enableCounterStop  = false;
  matchConfig.matchValue         = CTIMER_CLK_FREQ;
  matchConfig.outControl         = kCTIMER_Output_NoAction;
  matchConfig.outPinInitState    = false;
  matchConfig.enableInterrupt    = false;
  CTIMER_SetupMatch(CTIMER, CTIMER_MAT_OUT, &matchConfig);
  CTIMER_StartTimer(CTIMER);
}
#endif /* PL_CONFIG_IS_LPC */

void Cycles_LogTime(const char *msg) {
  uint32_t cycles;
  int32_t delta;
  uint32_t us;

  delta = (int32_t)CCounter_stopCounter-(int32_t)CCounter_startCounter;
  if (delta<0) {
    cycles = -delta;
  } else {
    cycles = delta;
  }
  /* count in overhead */
  if (cycles>CCOUNTER_OVERHEAD) {
    cycles -= CCOUNTER_OVERHEAD;
  } else {
    cycles = 0;
  }
  us = COUNT_TO_USEC(cycles, SystemCoreClock);
#if BENCHMARK_USE_STDLIB
  printf
#else
  McuSemihost_printf
#endif
  ("%s: delta: %ld, overhead: %d cycles: %lu; time: %lu us\n", msg, delta, CCOUNTER_OVERHEAD, cycles, us);
}

#if PL_CONFIG_IS_LPC
static void setFlashWaitStates(uint8_t nofWaits) {
  /* Configures the FLASHCFG with the FLASHTIM (Flash memory access time) at address 0x40040010.
  * By default the LPC845 sets it to 0x2 which is 3 system clock access time.
  * NOTE: e.g. for 30 MHz FRO a zero wait might create a HardFault: use 1 instead
  * */
  uint32_t val;

  val = (FLASH_CTRL->FLASHCFG) & ~FLASH_CTRL_FLASHCFG_FLASHTIM_MASK; /* must write back all other bits exactly as read! */
  switch(nofWaits) {
    default:
    case 0:
    val |= 0x0;   /* 1 system clock access time */
    break;
    case 1:
    val |= 0x1;   /* 2 system clock access time */
    break;
    case 2:
    val |= 0x2;   /* 3 system clock access time */
    break;
  }
  /* write back settings */
  FLASH_CTRL->FLASHCFG = val;
}
#endif

void Cycles_Deinit(void) {
  /* nothing to do */
}

static void Cycles_Test_NOP(void) {
  /*! \todo Check execution time for a NOP instruction */
  CCOUNTER_START();
  /* K22 code:
   * ldr r3, #CounterReg
   * ldr r3, [r3, #0]                (1, because loaded during instruction)
   * ldr r2, #CCounter_startCounter  (2)
   * str r3, [r2, #0]                (2)
   */
  /* LPC845 code:
   * ldr r3, #CCounter_startCounter ; load addresss of variable
   * movs r2, #0                    ; load value to store
   * str r2, [r3, #0]               ; CCounter_startCounter=0;
   * ldr r3, [pc,40]                ; load device address CTIMER
   * movs r0, r3                    ; reg-reg move
   * bl CTIMER_Reset                ; CTIMER_Reset(CTIMER)
   */
  __asm volatile("nop");
  /* nop                             (1) */
  CCOUNTER_STOP();
  /* K22 code:
   * ldr r3, #CounterReg             (2)
   * ldr r3, [0,r3]                  (1, because loaded during instruction)
   * ldr r2, &CCounter_stopCounter
   * str r3, [0,r2]
   */
  Cycles_LogTime("nop test");
}

void Cycles_Init(void) {
  CCounter_startCounter = CCounter_stopCounter = 0;
#if PL_CONFIG_IS_TINY
  /* note: HW cycle counter only exists on M3 or higher. Without debugger attached, need to initialize counter */
  #define McuArmTools_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define McuArmTools_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */
  McuArmTools_DEMCR |= McuArmTools_TRCENA_BIT;
#elif PL_CONFIG_IS_LPC
  InitTimer(); /* initialize timer on LPC */
  setFlashWaitStates(0); /* set FLASH wait states to zero */
#endif
  Cycles_Test_NOP(); /* testing only */
}

#endif /* PL_CONFIG_DO_CYCLE_COUNTING */
