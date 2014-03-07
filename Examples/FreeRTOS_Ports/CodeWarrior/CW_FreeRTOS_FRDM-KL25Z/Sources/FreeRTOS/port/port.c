/*
    FreeRTOS V8.0.0 - Copyright (C) 2014 Real Time Engineers Ltd. 
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

/*-----------------------------------------------------------
 * FreeRTOS for 56800EX port by Richy Ye in Jan. 2013.
 *----------------------------------------------------------*/
/* Kernel includes. */
#include "portmacro.h" /* for configCPU_FAMILY */
#include "FreeRTOS.h"
#include "task.h"
#include "portTicks.h" /* for CPU_CORE_CLK_HZ used in configSYSTICK_CLOCK_HZ */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #include "LPTMR_PDD.h"
#endif
/* --------------------------------------------------- */
/* macros dealing with tick counter */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #define ENABLE_TICK_COUNTER()       LPTMR_PDD_EnableDevice(LPTMR0_BASE_PTR, PDD_ENABLE); LPTMR_PDD_EnableInterrupt(LPTMR0_BASE_PTR)
  #define DISABLE_TICK_COUNTER()      LPTMR_PDD_EnableDevice(LPTMR0_BASE_PTR, PDD_DISABLE); LPTMR_PDD_DisableInterrupt(LPTMR0_BASE_PTR)
  #define RESET_TICK_COUNTER_VAL()    DISABLE_TICK_COUNTER()  /* CNR is reset when the LPTMR is disabled or counter register overflows */
  #define ACKNOWLEDGE_TICK_ISR()      LPTMR_PDD_ClearInterruptFlag(LPTMR0_BASE_PTR)
#else
  #define ENABLE_TICK_COUNTER()       portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT
  #define DISABLE_TICK_COUNTER()      portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT
  #define RESET_TICK_COUNTER_VAL()    portNVIC_SYSTICK_CURRENT_VALUE_REG = 0 /*portNVIC_SYSTICK_LOAD_REG*/
  #define ACKNOWLEDGE_TICK_ISR()      /* not needed */
#endif

typedef unsigned long TickCounter_t; /* enough for 24 bit Systick */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #define TICK_NOF_BITS               16
  #define COUNTS_UP                   1 /* LPTMR is counting up */
  #define SET_TICK_DURATION(val)      LPTMR_PDD_WriteCompareReg(LPTMR0_BASE_PTR, val)
  #define GET_TICK_DURATION()         LPTMR_PDD_ReadCompareReg(LPTMR0_BASE_PTR)
  #define GET_TICK_CURRENT_VAL(addr)  *(addr)=LPTMR_PDD_ReadCounterReg(LPTMR0_BASE_PTR)
#else
  #define TICK_NOF_BITS               24
  #define COUNTS_UP                   0 /* SysTick is counting down to zero */
  #define SET_TICK_DURATION(val)      portNVIC_SYSTICK_LOAD_REG = val
  #define GET_TICK_DURATION()         portNVIC_SYSTICK_LOAD_REG
  #define GET_TICK_CURRENT_VAL(addr)  *(addr)=portNVIC_SYSTICK_CURRENT_VALUE_REG
#endif

#if configSYSTICK_USE_LOW_POWER_TIMER
  #define TIMER_COUNTS_FOR_ONE_TICK     (configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ/configTICK_RATE_HZ)
#else
  #define TIMER_COUNTS_FOR_ONE_TICK     (configSYSTICK_CLOCK_HZ/configTICK_RATE_HZ)
#endif

#if configUSE_TICKLESS_IDLE == 1
#define UL_TIMER_COUNTS_FOR_ONE_TICK  ((TickCounter_t)(TIMER_COUNTS_FOR_ONE_TICK))

#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  #define TICKLESS_DISABLE_INTERRUPTS()  __asm volatile("cpsid i") /* disable interrupts. Note that the wfi (wait for interrupt) instruction later will still be able to wait for interrupts! */
  #define TICKLESS_ENABLE_INTERRUPTS()   __asm volatile("cpsie i") /* re-enable interrupts. */
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define TICKLESS_DISABLE_INTERRUPTS()  __asm("sei"); /* disable interrupts */
  #define TICKLESS_ENABLE_INTERRUPTS()   __asm("cli"); /* re-enable interrupts */
#else
  #define TICKLESS_DISABLE_INTERRUPTS()  portDISABLE_INTERRUPTS() /* this disables interrupts! Make sure they are re-enabled in vOnPreSleepProcessing()! */
  #define TICKLESS_ENABLE_INTERRUPTS()   portENABLE_INTERRUPTS()  /* re-enable interrupts */
#endif

  #if 1
    #if configSYSTICK_USE_LOW_POWER_TIMER
      /* using Low Power Timer */
      #define TICK_INTERRUPT_HAS_FIRED()   (LPTMR_PDD_GetInterruptFlag(LPTMR0_BASE_PTR)!=0)  /* returns TRUE if tick interrupt had fired */
      #define TICK_INTERRUPT_FLAG_RESET()  /* not needed */
      #define TICK_INTERRUPT_FLAG_SET()    /* not needed */
    #else
      /* using directly SysTick Timer */
      #define TICK_INTERRUPT_HAS_FIRED()   ((portNVIC_SYSTICK_CTRL_REG&portNVIC_SYSTICK_COUNT_FLAG_BIT)!=0)  /* returns TRUE if tick interrupt had fired */
      #define TICK_INTERRUPT_FLAG_RESET()  /* not needed */
      #define TICK_INTERRUPT_FLAG_SET()    /* not needed */
    #endif
  #else 
    /* using global variable to find out if interrupt has fired */
    volatile uint8_t portTickCntr; /* used to find out if we woke up by the tick interrupt */
    #define TICK_INTERRUPT_HAS_FIRED()   (portTickCntr!=0)  /* returns TRUE if tick interrupt had fired */
    #define TICK_INTERRUPT_FLAG_RESET()  portTickCntr=0
    #define TICK_INTERRUPT_FLAG_SET()    portTickCntr=1
  #endif
#endif /* configUSE_TICKLESS_IDLE == 1 */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * resolution of the tick timer.
 */
#if configUSE_TICKLESS_IDLE == 1
  static TickCounter_t xMaximumPossibleSuppressedTicks = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the tick timer is stopped (low
 * power functionality only.
 */
#if configUSE_TICKLESS_IDLE == 1
  static TickCounter_t ulStoppedTimerCompensation = 0;
  #define configSTOPPED_TIMER_COMPENSATION    45UL  /* number of ticks to compensate */
#endif /* configUSE_TICKLESS_IDLE */

#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2)
  #define portINITIAL_FORMAT_VECTOR           ((portSTACK_TYPE)0x4000)
  #define portINITIAL_STATUS_REGISTER         ((portSTACK_TYPE)0x2000)  /* Supervisor mode set. */
#endif

#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
/* Constants required to manipulate the core.
 * SysTick register: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0662b/CIAGECDD.html
 * Registers first... 
 */
#define portNVIC_SYSTICK_CTRL_REG           (*((volatile unsigned long *)0xe000e010)) /* SYST_CSR, SysTick Control and Status Register */
#define portNVIC_SYSTICK_LOAD_REG           (*((volatile unsigned long *)0xe000e014)) /* SYST_RVR, SysTick reload value register */
#define portNVIC_SYSTICK_CURRENT_VALUE_REG  (*((volatile unsigned long *)0xe000e018)) /* SYST_CVR, SysTick current value register */
#define portNVIC_SYSTICK_CALIB_VALUE_REG    (*((volatile unsigned long *)0xe000e01C)) /* SYST_CALIB, SysTick calibration value register */
/* ...then bits in the registers. */
#define portNVIC_SYSTICK_COUNT_FLAG_BIT     (1UL<<16UL) /* returns 1 if timer counted to 0 since the last read of the register */
#if configSYSTICK_USE_CORE_CLOCK
  #define portNVIC_SYSTICK_CLK_BIT          (1UL<<2UL) /* clock source. 1: core clock, 0: external reference clock */
#else
  #define portNVIC_SYSTICK_CLK_BIT          (0UL<<2UL) /* clock source. 1: core clock, 0: external reference clock */
#endif
#define portNVIC_SYSTICK_INT_BIT            (1UL<<1UL)  /* SysTick interrupt enable bit */
#define portNVIC_SYSTICK_ENABLE_BIT         (1UL<<0UL)  /* SysTick enable bit */

/* Constants required to manipulate the NVIC: */
#define portNVIC_INT_CTRL                   ((volatile unsigned long*)0xe000ed04) /* interrupt control and state register (ICSR) */
#define portNVIC_PENDSVSET_BIT              (1UL<<28UL) /* bit 28 in portNVIC_INT_CTRL (PENDSVSET), see http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Cihfaaha.html */
#define portNVIC_PENDSVCLEAR_BIT            (1UL<<27UL) /* bit 27 in portNVIC_INT_CTRL (PENDSVCLR) */
#define portNVIC_PEND_SYSTICK_SET_BIT       (1UL<<26UL) /* bit 26 in portNVIC_INT_CTRL (PENDSTSET) */
#define portNVIC_PEND_SYSTICK_CLEAR_BIT     (1UL<<25UL) /* bit 25 in portNVIC_INT_CTRL (PENDSTCLR) */

#define portNVIC_SYSPRI2                    ((volatile unsigned long*)0xe000ed1c) /* system handler priority register 2 (SHPR2), used for SVCall priority, http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0662b/CIAGECDD.html */
#define portNVIC_SVCALL_PRI                 (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<24) /* priority of SVCall interrupt (in portNVIC_SYSPRI2) */

#define portNVIC_SYSPRI3                    ((volatile unsigned long*)0xe000ed20) /* system handler priority register 3 (SHPR3), used for SysTick and PendSV priority, http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0662b/CIAGECDD.html */
#define portNVIC_SYSTICK_PRI                (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<24) /* priority of SysTick interrupt (in portNVIC_SYSPRI3) */
#define portNVIC_PENDSV_PRI                 (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<16) /* priority of PendableService interrupt (in portNVIC_SYSPRI3) */

#define portNVIC_SYSPRI7                    ((volatile unsigned long*)0xe000e41c) /* system handler priority register 7, PRI_28 is LPTMR */
#define portNVIC_LP_TIMER_PRI               (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<0) /* priority of SysTick interrupt (in portNVIC_SYSPRI3) */

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR         (0x01000000)
#define portINITIAL_EXEC_RETURN  (0xfffffffd)

#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
  /* Constants required to manipulate the VFP. */
  #define portFPCCR                ((volatile unsigned long *)0xe000ef34) /* Floating point context control register. */
  #define portASPEN_AND_LSPEN_BITS (0x3UL<<30UL)
#endif
#endif
/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().
   This will be set to 0 prior to the first task being started. */
/* Each task maintains its own interrupt status in the critical nesting variable. */
static unsigned portBASE_TYPE uxCriticalNesting = 0xaaaaaaaa;

/*-----------------------------------------------------------*/
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE * pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters ) {
  /* Simulate the stack frame as it would be created by a context switch interrupt. */
#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
  pxTopOfStack -= 2; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts,
                        and to ensure alignment. */
#else
  pxTopOfStack--;
#endif
  *pxTopOfStack = portINITIAL_XPSR;   /* xPSR */
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)pxCode;  /* PC */
  pxTopOfStack--;
  *pxTopOfStack = 0;  /* LR */

  /* Save code space by skipping register initialization. */
  pxTopOfStack -= 5;  /* R12, R3, R2 and R1. */
  *pxTopOfStack = (portSTACK_TYPE)pvParameters; /* R0 */

#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
  /* A save method is being used that requires each task to maintain its
     own exec return value. */
  pxTopOfStack--;
  *pxTopOfStack = portINITIAL_EXEC_RETURN;
#endif
  pxTopOfStack -= 8;  /* R11, R10, R9, R8, R7, R6, R5 and R4. */
  return pxTopOfStack;
}

/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_S08_FSL) || (configCOMPILER==configCOMPILER_S12_FSL)
#if (configCOMPILER==configCOMPILER_S08_FSL)
  #pragma MESSAGE DISABLE C1404 /* return expected */
  #pragma MESSAGE DISABLE C20000 /* dead code detected */
  #pragma NO_RETURN
  #pragma CODE_SEG __NEAR_SEG NON_BANKED
#elif (configCOMPILER==configCOMPILER_S12_FSL)
  #pragma MESSAGE DISABLE C1404 /* return expected */
  #pragma NO_RETURN
#endif

static portBASE_TYPE xBankedStartScheduler(void) {
  /* Restore the context of the first task. */
  portRESTORE_CONTEXT(); /* Simulate the end of an interrupt to start the scheduler off. */
  /* Should not get here! */
  return pdFALSE;
}

#if (configCOMPILER==configCOMPILER_S08_FSL)
  #pragma CODE_SEG DEFAULT
  #pragma MESSAGE DEFAULT C1404 /* return expected */
  #pragma MESSAGE DEFAULT C20000 /* dead code detected */
#elif (configCOMPILER==configCOMPILER_S12_FSL)
  #pragma MESSAGE DEFAULT C1404 /* return expected */
#endif
#endif
/*-----------------------------------------------------------*/
#if configUSE_TICKLESS_IDLE == 1
__attribute__((weak)) void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime) {
  unsigned long ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickIncrements;
  TickCounter_t tmp; /* because of how we get the current tick counter */
  bool tickISRfired;

  /* Make sure the tick timer reload value does not overflow the counter. */
  if(xExpectedIdleTime>xMaximumPossibleSuppressedTicks) {
    xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
  }

  /* Stop the tick timer momentarily. The time the counter is stopped for
   * is accounted for as best it can be, but using the tickless mode will
   * inevitably result in some tiny drift of the time maintained by the
   * kernel with respect to calendar time. 
   */
  DISABLE_TICK_COUNTER();

  /* Calculate the reload value required to wait xExpectedIdleTime
   * tick periods. -1 is used because this code will execute part way
   * through one of the tick periods. 
   */
  GET_TICK_CURRENT_VAL(&tmp);
  ulReloadValue = tmp+(UL_TIMER_COUNTS_FOR_ONE_TICK*(xExpectedIdleTime-1UL));
  if (ulReloadValue>ulStoppedTimerCompensation) {
    ulReloadValue -= ulStoppedTimerCompensation;
  }

  /* Enter a critical section but don't use the taskENTER_CRITICAL()
   * method as that will mask interrupts that should exit sleep mode. 
   */
  TICKLESS_DISABLE_INTERRUPTS();
  
  /* If a context switch is pending or a task is waiting for the scheduler
   * to be unsuspended then abandon the low power entry. 
   */
  if (eTaskConfirmSleepModeStatus()==eAbortSleep) {
    ENABLE_TICK_COUNTER(); /* Restart SysTick. */
    TICKLESS_ENABLE_INTERRUPTS();
  } else {
#if configUSE_LP_TIMER
    DisableDevice();
    ClearInterruptFlag();
    WriteCompareReg(xExpectedIdleTime-1);
    EnableDevice(); /* start timer */
#else
    SET_TICK_DURATION(ulReloadValue); /* Set the new reload value. */
    RESET_TICK_COUNTER_VAL(); /* Reset the counter. */
    ENABLE_TICK_COUNTER(); /* Restart tick timer. */
    TICK_INTERRUPT_FLAG_RESET(); /* reset flag so we know later if it has fired */
#endif

    /* Sleep until something happens. configPRE_SLEEP_PROCESSING() can
     * set its parameter to 0 to indicate that its implementation contains
     * its own wait for interrupt or wait for event instruction, and so wfi
     * should not be executed again.  However, the original expected idle
     * time variable must remain unmodified, so a copy is taken.
     */
    
     /* CPU *HAS TO WAIT* in the sequence below for an interrupt. If vOnPreSleepProcessing() is not used, a default implementation is provided */
    /* default wait/sleep code */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
    /* ----------------------------------------------------------------------------
     * Here the CPU *HAS TO BE* low power mode, waiting to wake up by an interrupt 
     * ----------------------------------------------------------------------------*/
    /* Stop tick counter. Again, the time the tick counter is stopped for is
     * accounted for as best it can be, but using the tickless mode will
     * inevitably result in some tiny drift of the time maintained by the
     * kernel with respect to calendar time. 
     */
    tickISRfired = TICK_INTERRUPT_HAS_FIRED(); /* need to check Interrupt flag here, as might be modified below */
    DISABLE_TICK_COUNTER();
    TICKLESS_ENABLE_INTERRUPTS();/* Re-enable interrupts */
    if (tickISRfired) {
      /* The tick interrupt has already executed, and the timer
       * count reloaded with the modulo/match value.
       * Reset the counter register with whatever remains of
       * this tick period. 
       */
      GET_TICK_CURRENT_VAL(&tmp);
#if COUNTS_UP
      SET_TICK_DURATION((UL_TIMER_COUNTS_FOR_ONE_TICK-1UL)-tmp);
#else
      SET_TICK_DURATION((UL_TIMER_COUNTS_FOR_ONE_TICK-1UL)-(ulReloadValue-tmp));
#endif
      /* The tick interrupt handler will already have pended the tick
       * processing in the kernel.  As the pending tick will be
       * processed as soon as this function exits, the tick value
       * maintained by the tick is stepped forward by one less than the
       * time spent waiting.
       */
      ulCompleteTickPeriods = xExpectedIdleTime-1UL;
    } else {
      /* Something other than the tick interrupt ended the sleep.
       * Work out how long the sleep lasted rounded to complete tick
       * periods (not the ulReload value which accounted for part ticks). 
       */
      GET_TICK_CURRENT_VAL(&tmp);
      ulCompletedSysTickIncrements = (xExpectedIdleTime*UL_TIMER_COUNTS_FOR_ONE_TICK)-tmp;

      /* How many complete tick periods passed while the processor was waiting? */
      ulCompleteTickPeriods = ulCompletedSysTickIncrements/UL_TIMER_COUNTS_FOR_ONE_TICK;

      /* The reload value is set to whatever fraction of a single tick period remains. */
      SET_TICK_DURATION(((ulCompleteTickPeriods+1)*UL_TIMER_COUNTS_FOR_ONE_TICK)-ulCompletedSysTickIncrements);
    }

    /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
       again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
       value.  The critical section is used to ensure the tick interrupt
       can only execute once in the case that the reload register is near
       zero. 
     */
    RESET_TICK_COUNTER_VAL();
    portENTER_CRITICAL();
    {
      ENABLE_TICK_COUNTER();
      vTaskStepTick(ulCompleteTickPeriods);
      SET_TICK_DURATION(UL_TIMER_COUNTS_FOR_ONE_TICK-1UL);
    }
    portEXIT_CRITICAL();
  }
}
#endif /* #if configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/
void vPortInitTickTimer(void) {
#if configUSE_TICKLESS_IDLE == 1
{
#if TICK_NOF_BITS==32
  xMaximumPossibleSuppressedTicks = 0xffffffffUL/TIMER_COUNTS_FOR_ONE_TICK; /* 32bit timer register */
#elif TICK_NOF_BITS==24
  xMaximumPossibleSuppressedTicks = 0xffffffUL/TIMER_COUNTS_FOR_ONE_TICK; /* 24bit timer register */
#elif TICK_NOF_BITS==16
  xMaximumPossibleSuppressedTicks = 0xffffUL/TIMER_COUNTS_FOR_ONE_TICK; /* 16bit timer register */
#elif TICK_NOF_BITS==8
  xMaximumPossibleSuppressedTicks = 0xffUL/TIMER_COUNTS_FOR_ONE_TICK; /* 8bit timer register */
#else
  error "unknown configuration!"
#endif
#if configSYSTICK_USE_LOW_POWER_TIMER
  ulStoppedTimerCompensation = configSTOPPED_TIMER_COMPENSATION/(configCPU_CLOCK_HZ/configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ);
#else
  ulStoppedTimerCompensation = configSTOPPED_TIMER_COMPENSATION/(configCPU_CLOCK_HZ/configSYSTICK_CLOCK_HZ);
#endif
}
#endif /* configUSE_TICKLESS_IDLE */
#if configSYSTICK_USE_LOW_POWER_TIMER
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK; /* enable clock: SIM_SCGC5: LPTMR=1 */

  /* LPTMR0_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TCF=1,TIE=0,TPS=0,TPP=0,TFC=0,TMS=0,TEN=0 */
  LPTMR0_CSR = (LPTMR_CSR_TCF_MASK | LPTMR_CSR_TPS(0x00)); /* Clear control register */
  /* LPTMR0_PSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,PRESCALE=0,PBYP=1,PCS=1 */
  LPTMR0_PSR = LPTMR_PSR_PRESCALE(0x00) | /* prescaler value */
               LPTMR_PSR_PBYP_MASK | /* prescaler bypass */
               LPTMR_PSR_PCS(0x01);    /* Clock source */
  /*
   *           PBYP PCS
   * ERCLK32    1   10
   * LPO_1kHz   1   01
   * ERCLK      0   00
   * IRCLK      1   00
   */
  *(portNVIC_SYSPRI7) |= portNVIC_LP_TIMER_PRI; /* set priority of low power timer interrupt */
  /* NVIC_ISER: SETENA|=0x10000000 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x10000000);     /* 0xE000E100 <= 0x10000000 */                              

  /* LPTMR0_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TCF=0,TIE=0,TPS=0,TPP=0,TFC=0,TMS=0,TEN=1 */
  LPTMR0_CSR = (LPTMR_CSR_TPS(0x00) | LPTMR_CSR_TEN_MASK); /* Set up control register */
#else /* use normal SysTick Counter */
  *(portNVIC_SYSPRI3) |= portNVIC_SYSTICK_PRI; /* set priority of SysTick interrupt */
#endif
  /* Configure timer to interrupt at the requested rate. */
  SET_TICK_DURATION(TIMER_COUNTS_FOR_ONE_TICK-1UL);
  RESET_TICK_COUNTER_VAL();
  ENABLE_TICK_COUNTER();
}
/*-----------------------------------------------------------*/
void vPortStartTickTimer(void) {
  ENABLE_TICK_COUNTER();
}
/*-----------------------------------------------------------*/
void vPortStopTickTimer(void) {
  DISABLE_TICK_COUNTER();
}
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL) || (configCOMPILER==configCOMPILER_ARM_GCC)
#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
void vPortEnableVFP(void) {
  /* The FPU enable bits are in the CPACR. */
  __asm volatile (
    "  ldr.w r0, =0xE000ED88  \n" /* CAPCR, 0xE000ED88 */
    "  ldr r1, [r0]           \n" /* read CAPR */
    /* Enable CP10 and CP11 coprocessors, then save back. */
    "  orr r1, r1, #(0xf<<20) \n" /* wait for store to complete */
    : /* no output */
    : /* no input */
    : "r0","r1" /* clobber */
  );
}
#endif /* configCPU_FAMILY_ARM_M4F */
#endif /* GNU or Keil */
/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler(void) {
  /* Make PendSV, SVCall and SysTick the lowest priority interrupts. SysTick priority will be set in vPortInitTickTimer(). */
#if 0 /* do NOT set the SVCall priority */
  /* why: execution of an SVC instruction at a priority equal or higher than SVCall can cause a hard fault (at least on Cortex-M4),
  see https://community.freescale.com/thread/302511 */
  *(portNVIC_SYSPRI2) |= portNVIC_SVCALL_PRI; /* set priority of SVCall interrupt */
#endif
  *(portNVIC_SYSPRI3) |= portNVIC_PENDSV_PRI; /* set priority of PendSV interrupt */
  uxCriticalNesting = 0; /* Initialize the critical nesting count ready for the first task. */
  vPortInitTickTimer(); /* initialize tick timer */
  vPortStartTickTimer(); /* start tick timer */
#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
  vPortEnableVFP(); /* Ensure the VFP is enabled - it should be anyway */
  *(portFPCCR) |= portASPEN_AND_LSPEN_BITS; /* Lazy register save always */
#endif
  vPortStartFirstTask(); /* Start the first task. */
  /* Should not get here, unless you call vTaskEndScheduler()! */
  return pdFALSE;
}
/*-----------------------------------------------------------*/
void vPortEnterCritical(void) {
/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
  portDISABLE_INTERRUPTS();
  portPOST_ENABLE_DISABLE_INTERRUPTS();
  uxCriticalNesting++;
  __asm volatile("dsb");
  __asm volatile("isb");
}
/*-----------------------------------------------------------*/
void vPortExitCritical(void) {
 /* Interrupts are disabled so we can access the nesting count directly.  If the
  * nesting is found to be 0 (no nesting) then we are leaving the critical
  * section and interrupts can be re-enabled.
  */
  uxCriticalNesting--;
  if (uxCriticalNesting == 0)  {
    portENABLE_INTERRUPTS();
    portPOST_ENABLE_DISABLE_INTERRUPTS();
  }
}
/*-----------------------------------------------------------*/
void vPortYieldFromISR(void) {
  /* Set a PendSV to request a context switch. */
  *(portNVIC_INT_CTRL) = portNVIC_PENDSVSET_BIT;
  /* Barriers are normally not required but do ensure the code is completely
  within the specified behavior for the architecture. */
  __asm volatile("dsb");
  __asm volatile("isb");
}
/*-----------------------------------------------------------*/
/* return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time */
portLONG uxGetTickCounterValue(void) {
  portLONG val;
  
  GET_TICK_CURRENT_VAL(&val);
  return val;
}
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
void vPortTickHandler(void) {
  /* this is how we get here:
    RTOSTICKLDD1_Interrupt:
    push {r4, lr}
    ...                                       RTOSTICKLDD1_OnCounterRestart
    bl RTOSTICKLDD1_OnCounterRestart     ->   push {r4,lr}
    pop {r4, lr}                              mov r4,r0
                                              bl vPortTickHandler
                                              pop {r4,pc}
  */
#if configUSE_TICKLESS_IDLE == 1
  TICK_INTERRUPT_FLAG_SET();
#endif
  portSET_INTERRUPT_MASK();   /* disable interrupts */
  if (xTaskIncrementTick()!=pdFALSE) { /* increment tick count */
    taskYIELD();
  }
  portCLEAR_INTERRUPT_MASK(); /* enable interrupts again */
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
void vPortTickHandler(void) {
  ACKNOWLEDGE_TICK_ISR();
#if configUSE_TICKLESS_IDLE == 1
  TICK_INTERRUPT_FLAG_SET();
#endif
  portSET_INTERRUPT_MASK();   /* disable interrupts */
  if (xTaskIncrementTick()!=pdFALSE) { /* increment tick count */
    taskYIELD();
  }
  portCLEAR_INTERRUPT_MASK(); /* enable interrupts again */
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_DSC_FSL)
void vPortStartFirstTask(void) {
  /* Restore the context of the first task to run. */
  portRESTORE_CONTEXT();
  /* Simulate the end of the yield function. */
  __asm(rts);
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
__asm void vPortStartFirstTask(void) {
  /* Use the NVIC offset register to locate the stack. */
  ldr r0, =0xE000ED08
  ldr r0, [r0]
  ldr r0, [r0]
  /* Set the msp back to the start of the stack. */
  msr msp, r0
  /* Globally enable interrupts. */
  cpsie i
  /* Call SVC to start the first task. */
  svc 0
  nop
  nop
  nop
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
void vPortStartFirstTask(void) {
  __asm volatile (
    " ldr r0, =0xE000ED08 \n" /* Use the NVIC offset register to locate the stack. */
    " ldr r0, [r0]        \n" /* load address of vector table */
    " ldr r0, [r0]        \n" /* load first entry of vector table which is the reset stack pointer */
    " msr msp, r0         \n" /* Set the msp back to the start of the stack. */
    " cpsie i             \n" /* Globally enable interrupts. */
    " svc 0               \n" /* System call to start first task. */
    " nop                 \n"
  );
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
__asm void vPortSVCHandler(void) {
  EXTERN pxCurrentTCB

  /* Get the location of the current TCB. */
  ldr r3, =pxCurrentTCB
  ldr r1, [r3]
  ldr r0, [r1]
  /* Pop the core registers. */
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
  ldmia r0!, {r4-r11, r14} /* \todo: r14, check http://sourceforge.net/p/freertos/discussion/382005/thread/a9406af1/?limit=25#3bc7 */
#else
  ldmia r0!, {r4-r11}
#endif
  msr psp, r0
  mov r0, #0
  msr basepri, r0
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
#else
  orr r14, r14, #13
#endif
  bx r14
  nop
}
/*-----------------------------------------------------------*/
#else /* Cortex M0+ */
__asm void vPortSVCHandler(void) {
  EXTERN pxCurrentTCB

  /* Get the location of the current TCB. */
  ldr r3, =pxCurrentTCB  /* Restore the context. */
  ldr r1, [r3]          /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
  ldr r0, [r1]          /* The first item in pxCurrentTCB is the task top of stack. */
  adds r0, #16          /* Move to the high registers. */
  ldmia r0!, {r4-r7}    /* Pop the high registers. */
  mov r8, r4 
  mov r9, r5 
  mov r10, r6
  mov r11, r7

  msr psp, r0           /* Remember the new top of stack for the task. */

  subs r0, #32          /* Go back for the low registers that are not automatically restored. */
  ldmia r0!, {r4-r7}    /* Pop low registers.  */
  mov r1, r14           /* OR R14 with 0x0d. */
  movs r0, #0x0d
  orrs r1, r0
  bx r1
  nop
}
#endif
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
__attribute__ ((naked)) void vPortSVCHandler(void) {
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
__asm volatile (
    " ldr r3, pxCurrentTCBConst2 \n" /* Restore the context. */
    " ldr r1, [r3]               \n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    " ldr r0, [r1]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    /* pop the core registers */
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
    " ldmia r0!, {r4-r11, r14}   \n"
#else
    " ldmia r0!, {r4-r11}        \n"
#endif
    " msr psp, r0                \n"
    " mov r0, #0                 \n"
    " msr basepri, r0            \n"
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
#else
    " orr r14, r14, #13          \n"
#endif
    " bx r14                     \n"
    "                            \n"
    " .align 2                   \n"
    "pxCurrentTCBConst2: .word pxCurrentTCB \n"
  );
#else /* Cortex M0+ */
  __asm volatile (
    " ldr r3, pxCurrentTCBConst2 \n" /* Restore the context. */
    " ldr r1, [r3]               \n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    " ldr r0, [r1]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    " add r0, r0, #16            \n" /* Move to the high registers. */
    " ldmia r0!, {r4-r7}         \n" /* Pop the high registers. */
    " mov r8, r4                 \n"
    " mov r9, r5                 \n"
    " mov r10, r6                \n"
    " mov r11, r7                \n"
    "                            \n"
    " msr psp, r0                \n" /* Remember the new top of stack for the task. */
    "                            \n"
    " sub r0, r0, #32            \n" /* Go back for the low registers that are not automatically restored. */
    " ldmia r0!, {r4-r7}         \n" /* Pop low registers.  */
    " mov r1, r14                \n" /* OR R14 with 0x0d. */
    " movs r0, #0x0d             \n"
    " orr r1, r0                 \n"
    " bx r1                      \n"
    "                            \n"
    ".align 2                    \n"
    "pxCurrentTCBConst2: .word pxCurrentTCB \n"
  );
#endif
}
/*-----------------------------------------------------------*/
#endif
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
__asm void vPortPendSVHandler(void) {
  EXTERN pxCurrentTCB

  mrs r0, psp
  ldr  r3, =pxCurrentTCB     /* Get the location of the current TCB. */
  ldr  r2, [r3]
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
  tst r14, #0x10             /* Is the task using the FPU context?  If so, push high vfp registers. */
  it eq
  vstmdbeq r0!, {s16-s31}

  stmdb r0!, {r4-r11, r14}   /* save remaining core registers */
#else
  stmdb r0!, {r4-r11}        /* Save the core registers. */
#endif
  str r0, [r2]               /* Save the new top of stack into the first member of the TCB. */
  stmdb sp!, {r3, r14}
  mov r0, %0
  msr basepri, r0
  bl vTaskSwitchContext
  mov r0, #0
  msr basepri, r0
  ldmia sp!, {r3, r14}
  ldr r1, [r3]               /* The first item in pxCurrentTCB is the task top of stack. */
  ldr r0, [r1]
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
  ldmia r0!, {r4-r11, r14}   /* Pop the core registers */
  tst r14, #0x10             /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
  it eq
  vldmiaeq r0!, {s16-s31}
#else
  ldmia r0!, {r4-r11}        /* Pop the core registers. */
#endif
  msr psp, r0
  bx r14
  nop
}
#else /* Cortex M0+ */
__asm void vPortPendSVHandler(void) {
  EXTERN pxCurrentTCB
  EXTERN vTaskSwitchContext
	
  mrs r0, psp
	
  ldr r3, =pxCurrentTCB       /* Get the location of the current TCB. */
  ldr r2, [r3]

  subs r0, #32               /* Make space for the remaining low registers. */
  str r0, [r2]               /* Save the new top of stack. */
  stmia r0!, {r4-r7}         /* Store the low registers that are not saved automatically. */
  mov r4, r8                 /* Store the high registers. */
  mov r5, r9
  mov r6, r10
  mov r7, r11
  stmia r0!, {r4-r7}

  push {r3, r14}
  cpsid i
  bl vTaskSwitchContext
  cpsie i
  pop {r2, r3}               /* lr goes in r3. r2 now holds tcb pointer. */

  ldr r1, [r2]
  ldr r0, [r1]               /* The first item in pxCurrentTCB is the task top of stack. */
  adds r0, #16               /* Move to the high registers. */
  ldmia r0!, {r4-r7}         /* Pop the high registers. */
  mov r8, r4
  mov r9, r5
  mov r10, r6
  mov r11, r7

  msr psp, r0                /* Remember the new top of stack for the task. */

  subs r0, #32               /* Go back for the low registers that are not automatically restored. */
  ldmia r0!, {r4-r7}         /* Pop low registers.  */

  bx r3
  nop
}
#endif
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
__attribute__ ((naked)) void vPortPendSVHandler(void) {
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
  __asm volatile (
    " mrs r0, psp                \n"
    " ldr  r3, pxCurrentTCBConst \n" /* Get the location of the current TCB. */
    " ldr  r2, [r3]              \n"
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
    " tst r14, #0x10             \n" /* Is the task using the FPU context?  If so, push high vfp registers. */
    " it eq                      \n"
    " vstmdbeq r0!, {s16-s31}    \n"

    " stmdb r0!, {r4-r11, r14}   \n" /* save remaining core registers */
#else
    " stmdb r0!, {r4-r11}        \n" /* Save the core registers. */
#endif
    " str r0, [r2]               \n" /* Save the new top of stack into the first member of the TCB. */
    " stmdb sp!, {r3, r14}       \n"
    " mov r0, %0                 \n"
    " msr basepri, r0            \n"
    " bl vTaskSwitchContext      \n"
    " mov r0, #0                 \n"
    " msr basepri, r0            \n"
    " ldmia sp!, {r3, r14}       \n"
    " ldr r1, [r3]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    " ldr r0, [r1]               \n"
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
    " ldmia r0!, {r4-r11, r14}   \n" /* Pop the core registers */
    " tst r14, #0x10             \n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
    " it eq                      \n"
    " vldmiaeq r0!, {s16-s31}    \n"
#else
    " ldmia r0!, {r4-r11}        \n" /* Pop the core registers. */
#endif
    " msr psp, r0                \n"
    " bx r14                     \n"
    "                            \n"
    " .align 2                   \n"
    "pxCurrentTCBConst: .word pxCurrentTCB  \n"
    ::"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY)
  );
#else /* Cortex M0+ */
  __asm volatile (
    " mrs r0, psp                \n"
    "                            \n"
    " ldr r3, pxCurrentTCBConst  \n" /* Get the location of the current TCB. */
    " ldr r2, [r3]   \n"
    "                            \n"
    " sub r0, r0, #32            \n" /* Make space for the remaining low registers. */
    " str r0, [r2]               \n" /* Save the new top of stack. */
    " stmia r0!, {r4-r7}         \n" /* Store the low registers that are not saved automatically. */
    " mov r4, r8                 \n" /* Store the high registers. */
    " mov r5, r9                 \n"
    " mov r6, r10                \n"
    " mov r7, r11                \n"
    " stmia r0!, {r4-r7}         \n"
    "                            \n"
    " push {r3, r14}             \n"
    " cpsid i                    \n"
    " bl vTaskSwitchContext      \n"
    " cpsie i                    \n"
    " pop {r2, r3}               \n" /* lr goes in r3. r2 now holds tcb pointer. */
    "                            \n"
    " ldr r1, [r2]               \n"
    " ldr r0, [r1]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    " add r0, r0, #16            \n" /* Move to the high registers. */
    " ldmia r0!, {r4-r7}         \n" /* Pop the high registers. */
    " mov r8, r4                 \n"
    " mov r9, r5                 \n"
    " mov r10, r6                \n"
    " mov r11, r7                \n"
    "                            \n"
    " msr psp, r0                \n" /* Remember the new top of stack for the task. */
    "                            \n"
    " sub r0, r0, #32            \n" /* Go back for the low registers that are not automatically restored. */
    " ldmia r0!, {r4-r7}         \n" /* Pop low registers.  */
    "                            \n"
    " bx r3                      \n"
    "                            \n"
    ".align 2                    \n"
    "pxCurrentTCBConst: .word pxCurrentTCB"
  );
#endif
}
#endif
/*-----------------------------------------------------------*/

