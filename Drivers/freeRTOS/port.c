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

/*-----------------------------------------------------------
 * FreeRTOS for 56800EX port by Richy Ye in Jan. 2013.
 *----------------------------------------------------------*/
/* Kernel includes. */
#include "portmacro.h" /* for configCPU_FAMILY */
#include "FreeRTOS.h"
#include "task.h"
#include "portTicks.h" /* for CPU_CORE_CLK_HZ used in configSYSTICK_CLOCK_HZ */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #include "LPTMR_PDD.h" /* PDD interface to low power timer */
  #include "SIM_PDD.h"   /* PDD interface to system integration module */
#endif
/* --------------------------------------------------- */
/* macros dealing with tick counter */
%if (CPUfamily = "Kinetis")
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
%elif defined(TickCntr)
#define ENABLE_TICK_COUNTER()       (void)%@TickCntr@'ModuleName'%.Enable()
#define DISABLE_TICK_COUNTER()      (void)%@TickCntr@'ModuleName'%.Disable()
%if defined(TickCntr) & defined(@TickCntr@Reset)
#define RESET_TICK_COUNTER_VAL()    (void)%@TickCntr@'ModuleName'%.Reset()
%else
#define RESET_TICK_COUNTER_VAL()    /* WARNING: not possible to reset tick timer! */
%endif
%elif defined(TickTimerLDD)
#define ENABLE_TICK_COUNTER()       (void)%@TickTimerLDD@'ModuleName'%.Enable(RTOS_TickDevice)
#define DISABLE_TICK_COUNTER()      (void)%@TickTimerLDD@'ModuleName'%.Disable(RTOS_TickDevice)
#define RESET_TICK_COUNTER_VAL()    portNVIC_SYSTICK_CURRENT_VALUE_REG = 0 /*portNVIC_SYSTICK_LOAD_REG*/
%endif

%if (CPUfamily = "Kinetis")
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
%elif defined(TickCntr)
#define TICK_NOF_BITS               16
#define COUNTS_UP                   %@TickCntr@'ModuleName'%.UP_COUNTER
typedef %@TickCntr@'ModuleName'%.TTimerValue TickCounter_t; /* for holding counter */
#if configUSE_TICKLESS_IDLE == 1
static TickCounter_t currTickDuration; /* holds the modulo counter/tick duration as no API to get it from the FreeCntr component */
#endif
#define SET_TICK_DURATION(val)      (void)%@TickCntr@'ModuleName'%.SetCompare(val); currTickDuration=val
#define GET_TICK_DURATION()         currTickDuration
#define GET_TICK_CURRENT_VAL(addr)  (void)%@TickCntr@'ModuleName'%.GetCounterValue(addr)
%endif

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

%if defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
  #if 1
%else
  #if 0
%endif
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
%if defined(StoppedTimerCompensation)
  #define configSTOPPED_TIMER_COMPENSATION    %'StoppedTimerCompensation'UL  /* number of ticks to compensate, as defined in properties */
%else
  #define configSTOPPED_TIMER_COMPENSATION    45UL  /* number of ticks to compensate */
%endif
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
#define portNVIC_LP_TIMER_PRI               (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<0) /* priority of low power timer interrupt */

#if configSYSTICK_USE_LOW_POWER_TIMER
#define IRQn_Type int
#define __NVIC_PRIO_BITS          configPRIO_BITS
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
/** \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
#if (configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY))
typedef struct
{
  __IO uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  __O  uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_Type;
#else /* M0+ */
typedef struct
{
  __IO uint32_t ISER[1];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[31];
  __IO uint32_t ICER[1];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register          */
       uint32_t RSERVED1[31];
  __IO uint32_t ISPR[1];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register           */
       uint32_t RESERVED2[31];
  __IO uint32_t ICPR[1];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register         */
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  __IO uint32_t IP[8];                   /*!< Offset: 0x300 (R/W)  Interrupt Priority Register              */
}  NVIC_Type;
#endif

/* Memory mapping of Cortex-M0+ Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address                 */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct          */

/* Interrupt Priorities are WORD accessible only under ARMv6M                   */
/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  (((uint32_t)(IRQn)       )    &  0x03) * 8 )
#define _IP_IDX(IRQn)            (   ((uint32_t)(IRQn)            >>    2)     )

/** \brief  Set Interrupt Priority
    The function sets the priority of an interrupt.
    \note The priority cannot be set for every core interrupt.
    \param [in]      IRQn  Interrupt number.
    \param [in]  priority  Priority to set.
 */
static void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) {
  IRQn -= 16; /* PEx starts numbers with zero, while system interrupts would be negative */
#if (configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY))
  NVIC->IP[(uint32_t)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);   /* set Priority for device specific Interrupts  */
#else /* M0+ */
  NVIC->IP[_IP_IDX(IRQn)] = (NVIC->IP[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
      (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)); /* set Priority for device specific Interrupts  */
#endif
}

/** \brief  Enable External Interrupt
    The function enables a device-specific interrupt in the NVIC interrupt controller.
    \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
static void NVIC_EnableIRQ(IRQn_Type IRQn) {
  IRQn -= 16; /* PEx starts numbers with zero, while system interrupts would be negative */
#if (configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY))
  NVIC->ISER[(uint32_t)((int32_t)IRQn) >> 5] = (uint32_t)(1 << ((uint32_t)((int32_t)IRQn) & (uint32_t)0x1F)); /* enable interrupt */
#else /* M0+ */
  NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* enable interrupt */
#endif
}
#endif /* configSYSTICK_USE_LOW_POWER_TIMER */

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR         (0x01000000)
#define portINITIAL_EXEC_RETURN  (0xfffffffd)

/* Let the user override the pre-loading of the initial LR with the address of
   prvTaskExitError() in case is messes up unwinding of the stack in the
   debugger. */
#ifdef configTASK_RETURN_ADDRESS
  #define portTASK_RETURN_ADDRESS	configTASK_RETURN_ADDRESS
#else
  #define portTASK_RETURN_ADDRESS	prvTaskExitError
#endif

#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
  /* Constants required to manipulate the VFP. */
  #define portFPCCR                ((volatile unsigned long *)0xe000ef34) /* Floating point context control register. */
  #define portASPEN_AND_LSPEN_BITS (0x3UL<<30UL)
#endif
%-
%if defined(TickTimerLDD)
static LDD_TDeviceData *RTOS_TickDevice;
%endif
#endif
%--------------------------------------------------------------
/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().
   This will be set to 0 prior to the first task being started. */
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
unsigned portLONG uxCriticalNesting = 0x9999UL;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X") | (CPUfamily = "56800")
volatile unsigned portBASE_TYPE uxCriticalNesting;
%elif (CPUfamily = "Kinetis")
/* Each task maintains its own interrupt status in the critical nesting variable. */
static unsigned portBASE_TYPE uxCriticalNesting = 0xaaaaaaaa;
%else
  #error "undefined target %CPUfamily!"
%endif

#define configUSE_TASK_END_SCHEDULER   1

#if configUSE_TASK_END_SCHEDULER
#include <setjmp.h>
static jmp_buf xJumpBuf; /* Used to restore the original context when the scheduler is ended. */
#endif
/*-----------------------------------------------------------*/
static void prvTaskExitError(void) {
	/* A function that implements a task must not exit or attempt to return to
	its caller as there is nothing to return to.  If a task wants to exit it
	should instead call vTaskDelete( NULL ).

	Artificially force an assert() to be triggered if configASSERT() is
	defined, then stop here so application writers can catch the error. */
	configASSERT(uxCriticalNesting == ~0UL);
	portDISABLE_INTERRUPTS();
	for(;;);
}
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL) && configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
__asm uint32_t ulPortSetInterruptMask(void) {
  PRESERVE8

  mrs r0, basepri
  mov r1, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r1
  bx r14
}
#endif /* (configCOMPILER==configCOMPILER_ARM_KEIL) */
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL) && configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
__asm void vPortClearInterruptMask(uint32_t ulNewMask) {
  PRESERVE8

  msr basepri, r0
  bx r14
}
#endif /* (configCOMPILER==configCOMPILER_ARM_KEIL) */
/*-----------------------------------------------------------*/
%if (CPUfamily = "56800")
/* We require the address of the pxCurrentTCB variable, but don't want to know any details of its type. */
typedef void tskTCB;
extern tskTCB *volatile pxCurrentTCB;

#define portSAVE_CONTEXT()  do {\
    __asm(ADDA  #<2,SP);  /* SP is always long aligned */\
    __asm(BFTSTL  #$0001,SP);\
    __asm(BCC     NOADDASAVE);\
    __asm(ADDA    #<1,SP);\
    __asm(NOADDASAVE:);\
    __asm(MOVE.L  SR, X:(SP)+);\
    __asm(BFSET   #0x0300,SR);  /* Disable interrupt */\
    __asm(MOVE.L  R0, X:(SP)+);\
    __asm(MOVE.L  R1, X:(SP)+);\
    __asm(MOVE.L  R2, X:(SP)+);\
    __asm(MOVE.L  R3, X:(SP)+);\
    __asm(MOVE.L  R4, X:(SP)+);\
    __asm(MOVE.L  R5, X:(SP)+);\
    __asm(MOVE.L  N, X:(SP)+);\
    __asm(MOVE.L  N3, X:(SP)+);\
    __asm(MOVE.L  LC2,X:(SP)+);\
    __asm(MOVE.L  LA2,X:(SP)+);\
    __asm(MOVE.L  LC,X:(SP)+);\
    __asm(MOVE.L  LA,X:(SP)+);\
    __asm(MOVE.L  A2,X:(SP)+);\
    __asm(MOVE.L  A10,X:(SP)+);\
    __asm(MOVE.L  B2,X:(SP)+);\
    __asm(MOVE.L  B10,X:(SP)+);\
    __asm(MOVE.L  C2,X:(SP)+);\
    __asm(MOVE.L  C10,X:(SP)+);\
    __asm(MOVE.L  D2,X:(SP)+);\
    __asm(MOVE.L  D10,X:(SP)+);\
    __asm(MOVE.L  X0,X:(SP)+);\
    __asm(MOVE.L  Y,X:(SP)+);\
    __asm(MOVE.L  OMR,X:(SP)+);\
    __asm(BFCLR #0x01B0,OMR); /* Ensure CM = 0 */\
    __asm(MOVE.L  M01,X:(SP)+);\
    __asm(BFSET #0xFFFF,M01); /* Set M01 for linear addressing */\
    __asm(MOVE.L  HWS,X:(SP)+);\
    __asm(MOVE.L  HWS,X:(SP)+);\
    __asm(MOVE.L  uxCriticalNesting,A);\
    __asm(MOVE.L  A10,X:(SP)+); /* Save the critical nesting counter */\
    __asm(MOVE.L  pxCurrentTCB,R0);\
    __asm(TFRA  SP,R1); /* Save the new top of stack into the TCB */\
    __asm(MOVE.L  R1,X:(R0));\
    } while(0)

#define portRESTORE_CONTEXT()  do {\
    __asm(MOVE.L  pxCurrentTCB,R0); /* Restore the stack pointer for the task */\
    __asm(MOVE.L  X:(R0),R1);\
    __asm(BFTSTL  #$0001,R1);\
    __asm(BCC     NOADDARESTORE);\
    __asm(ADDA    #<1,R1);\
    __asm(NOADDARESTORE:);\
    __asm(TFRA  R1,SP);\
    __asm(SUBA  #<2,SP);\
    __asm(MOVE.L  X:(SP)-,A);\
    __asm(MOVE.L  A10,uxCriticalNesting); /* Restore the critical nesting counter */\
    __asm(MOVE.L  X:(SP)-,HWS);\
    __asm(MOVE.L  X:(SP)-,HWS);\
    __asm(MOVE.L  X:(SP)-,M01);\
    __asm(MOVE.L  X:(SP)-,OMR);\
    __asm(MOVE.L  X:(SP)-,Y);\
    __asm(MOVE.L  X:(SP)-,X0);\
    __asm(MOVE.L  X:(SP)-,D);\
    __asm(MOVE.L  X:(SP)-,D2);\
    __asm(MOVE.L  X:(SP)-,C);\
    __asm(MOVE.L  X:(SP)-,C2);\
    __asm(MOVE.L  X:(SP)-,B);\
    __asm(MOVE.L  X:(SP)-,B2);\
    __asm(MOVE.L  X:(SP)-,A);\
    __asm(MOVE.L  X:(SP)-,A2);\
    __asm(MOVE.L  X:(SP)-,LA);\
    __asm(MOVE.L  X:(SP)-,LC);\
    __asm(MOVE.L  X:(SP)-,LA2);\
    __asm(MOVE.L  X:(SP)-,LC2);\
    __asm(MOVE.L  X:(SP)-,N3);\
    __asm(MOVE.L  X:(SP)-,N);\
    __asm(MOVE.L  X:(SP)-,R5);\
    __asm(MOVE.L  X:(SP)-,R4);\
    __asm(MOVE.L  X:(SP)-,R3);\
    __asm(MOVE.L  X:(SP)-,R2);\
    __asm(MOVE.L  X:(SP)-,R1);\
    __asm(MOVE.L  X:(SP)-,R0);\
    __asm(MOVE.L  X:(SP)-,SR);\
    } while(0)

%endif %- (CPUfamily = "56800")
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE * pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters ) {
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  unsigned portLONG ulOriginalA5;

  __asm{ MOVE.L A5, ulOriginalA5 };
  *pxTopOfStack = (portSTACK_TYPE)0xDEADBEEF;
  pxTopOfStack--;

  /* Exception stack frame starts with the return address. */
  *pxTopOfStack = (portSTACK_TYPE)pxCode;
  pxTopOfStack--;

  *pxTopOfStack = (portINITIAL_FORMAT_VECTOR<<16UL) | ( portINITIAL_STATUS_REGISTER );
  pxTopOfStack--;

  *pxTopOfStack = (portSTACK_TYPE)0x0; /*FP*/
  pxTopOfStack -= 14; /* A5 to D0. */

  /* Parameter in A0. */
  *(pxTopOfStack + 8) = (portSTACK_TYPE)pvParameters;

  /* A5 must be maintained as it is reserved by the compiler. */
  *(pxTopOfStack + 13) = ulOriginalA5;

  return pxTopOfStack;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08")
  /*
  Place a few bytes of known values on the bottom of the stack.
  This can be uncommented to provide useful stack markers when debugging.
  *pxTopOfStack = (portSTACK_TYPE)0x11;
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)0x22;
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)0x33;
  pxTopOfStack--;
  */

  /* Setup the initial stack of the task.  The stack is set exactly as
  expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
  expected by the HCS08 RTI instruction.

  When compiling with the -Cs08 options the value of pvParameters needs to show up in the
  H:X registers, but the RTI does not restore H.  We'll push it onto the stack here, and
  later in restoreContext we'll pull it out just before the RTI call. */

  /* The address of the task function is placed in the stack byte at a time. */
#ifdef __BANKED__
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+2);
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+1);
  pxTopOfStack--;
#else
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+1);
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+0);
  pxTopOfStack--;
#endif
  /* Next are all the registers that form part of the task context. */

  /* X register: We need this even though we pull H:X out of the stack during restore since RTI will overwrite the X reg. */
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pvParameters))+1);
  pxTopOfStack--;

  /* A register contains parameter high byte. */
  *pxTopOfStack = (portSTACK_TYPE) 0xdd;
  pxTopOfStack--;

  /* CCR: Note that when the task starts interrupts will be enabled since "I" bit of CCR is cleared */
  *pxTopOfStack = (portSTACK_TYPE) 0x00;
  pxTopOfStack--;

  /* H register: This is not part of RTI setup, but we will store the H reg just before the call to RTI. */
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pvParameters))+0);
  pxTopOfStack--;

#ifdef __BANKED__
  /* The page of the task. */
  *pxTopOfStack = (portSTACK_TYPE) *(((portSTACK_TYPE*)(&pxCode))+0);
  pxTopOfStack--;
#endif

  /* Finally the critical nesting depth is initialized with 0 (not within a critical section). */
  *pxTopOfStack = (portSTACK_TYPE) 0x00;

  return pxTopOfStack;
%elif (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
  /*Place a few bytes of known values on the bottom of the stack.
    This can be uncommented to provide useful stack markers when debugging.
    *pxTopOfStack = (portSTACK_TYPE)0x11;
    pxTopOfStack--;
    *pxTopOfStack = (portSTACK_TYPE)0x22;
    pxTopOfStack--;
    *pxTopOfStack = (portSTACK_TYPE)0x33;
    pxTopOfStack--;
  */

  /* Setup the initial stack of the task.  The stack is set exactly as
     expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
     expected by the HCS12 RTI instruction. */

  /* The address of the task function is placed in the stack byte at a time. */
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+1);
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pxCode))+0);
  pxTopOfStack--;

  /* Next are all the registers that form part of the task context. */
  /* Y register */
  *pxTopOfStack = (portSTACK_TYPE)0xff;
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)0xee;
  pxTopOfStack--;

  /* X register */
  *pxTopOfStack = (portSTACK_TYPE)0xdd;
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)0xcc;
  pxTopOfStack--;

  /* A register contains parameter high byte. */
  *pxTopOfStack = (portSTACK_TYPE) *(((portSTACK_TYPE*)(&pvParameters))+0);
  pxTopOfStack--;

  /* B register contains parameter low byte. */
  *pxTopOfStack = (portSTACK_TYPE)*(((portSTACK_TYPE*)(&pvParameters))+1);
  pxTopOfStack--;

#ifdef __HCS12X__
  /* CCR (12-bit): Note that when the task starts interrupts will be enabled since I" bit of CCR is cleared */
  *pxTopOfStack = (portSTACK_TYPE)0xC0;
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)0x00;
  pxTopOfStack--;
#else
  /* CCR(8-bit): Note that when the task starts interrupts will be enabled since "I" bit of CCR is cleared */
  *pxTopOfStack = (portSTACK_TYPE)0x40; /* have the X bit still masked */
  pxTopOfStack--;
#endif

#ifdef __BANKED__
  #ifdef __HCS12X__
    *pxTopOfStack = (portSTACK_TYPE) *(((portSTACK_TYPE*)(&pxCode))+2);  /* PPage of task created */
    pxTopOfStack--;
    *pxTopOfStack = EPAGE;
    pxTopOfStack--;
    *pxTopOfStack = GPAGE;
    pxTopOfStack--;
    *pxTopOfStack = RPAGE;
    pxTopOfStack--;
  #else
    /* The page of the task. */
    *pxTopOfStack = (portSTACK_TYPE)((int)pxCode);
    pxTopOfStack--;
  #endif
#endif

  /* Finally the critical nesting depth is initialised with 0 (not within a critical section). */
  *pxTopOfStack = (portSTACK_TYPE)0x00;

  return pxTopOfStack;

%elif (CPUfamily = "Kinetis")
  /* Simulate the stack frame as it would be created by a context switch interrupt. */
  pxTopOfStack--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts,
                        and to ensure alignment. */
  *pxTopOfStack = portINITIAL_XPSR;   /* xPSR */
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)pxCode;  /* PC */
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)portTASK_RETURN_ADDRESS;  /* LR */

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
%elif (CPUfamily = "56800")
  #define portINITIAL_SR	0x00UL
  unsigned short usCode;
  portBASE_TYPE i;

  const portSTACK_TYPE xInitialStack[] = 
  {
	0x03030303UL,	/* R3 */
	0x04040404UL, /* R4 */
	0x05050505UL, /* R5 */
	0x06060606UL, /* N */
	0x07070707UL, /* N3 */
	0x08080808UL, /* LC2 */
	0x09090909UL, /* LA2 */
	0x0A0A0A0AUL, /* LC */
	0x0B0B0B0BUL, /* LA */
	0x0E0E0E0EUL, /* A2 */
	0x0F0F0F0FUL, /* A10 */
	0x11111111UL, /* B2 */
	0x22222222UL, /* B10 */
	0x33333333UL, /* C2 */
	0x44444444UL, /* C10 */
	0x55555555UL, /* D2 */
	0x66666666UL, /* D10 */
	0x77777777UL, /* X0 */
	0x88888888UL /* Y */
  };

  /* Setup the stack as if a yield had occurred. Save the program counter. */
  *pxTopOfStack = ( portSTACK_TYPE ) pxCode;
  pxTopOfStack++;
	
  /* Status register with interrupts enabled. */
  *pxTopOfStack = portINITIAL_SR;
  pxTopOfStack++;

  /* Address register R0 */
  *pxTopOfStack = 0x0000000UL;
  pxTopOfStack++;
	
  /* Address register R1 */
  *pxTopOfStack = 0x01010101UL; 
  pxTopOfStack++;

  /* Parameters are passed in R2. */
  *pxTopOfStack = ( portSTACK_TYPE ) pvParameters;
  pxTopOfStack++;

  for( i = 0; i < ( sizeof( xInitialStack ) / sizeof( portSTACK_TYPE ) ); i++ )
  {
    *pxTopOfStack = xInitialStack[ i ];
    pxTopOfStack++;
  }

  /* Operation mode register */
  __asm(MOVE.W OMR,usCode);
  *pxTopOfStack = ( portSTACK_TYPE ) usCode;
  pxTopOfStack++;
	
  /* Modulo register */
  __asm(MOVE.W M01,usCode);
  *pxTopOfStack = ( portSTACK_TYPE ) usCode;
  pxTopOfStack++;
	
  /* Hardware stack register 1 */
  *pxTopOfStack = 0x0C0C0C0CUL;
  pxTopOfStack++;
	
  /* Hardware stack register 0 */
  *pxTopOfStack = 0x0D0D0D0DUL;
  pxTopOfStack++;

  /* Finally the critical nesting depth. */
  *pxTopOfStack = 0x00000000UL;
  pxTopOfStack++;

  return pxTopOfStack;
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
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
%if defined(vOnPreSleepProcessing)
void %vOnPreSleepProcessing(TickType_t expectedIdleTicks); /* prototype */

%endif
%if defined(vOnPostSleepProcessing)
void %vOnPostSleepProcessing(TickType_t expectedIdleTicks); /* prototype */

%endif
%if ((%Compiler == "GNUC")|(%Compiler = "ARM_CC"))
__attribute__((weak)) void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime) {
%else
void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime) {
%endif
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
%if defined(vOnPreSleepProcessing)
    %vOnPreSleepProcessing(xExpectedIdleTime); /* go into low power mode. Re-enable interrupts as needed! */
%else
    /* default wait/sleep code */
  %if (CPUfamily = "Kinetis")
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
  %elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
    __asm("cli"); /* re-enable interrupts */
    __asm("wait");
  %else
    #error "unsupported CPU family! vOnPreSleepProcessing() event and go into sleep mode there!"
  %endif    
%endif
    /* ----------------------------------------------------------------------------
     * Here the CPU *HAS TO BE* low power mode, waiting to wake up by an interrupt 
     * ----------------------------------------------------------------------------*/
%if defined(vOnPostSleepProcessing)
    %vOnPostSleepProcessing(xExpectedIdleTime); /* process post-low power actions */
%endif
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
%ifdef TickTimerLDD
  RTOS_TickDevice = %@TickTimerLDD@'ModuleName'%.Init(NULL);     %>40/* initialize the tick timer */
  RESET_TICK_COUNTER_VAL();
  /* overwrite SysTick priority is set inside the FreeRTOS component */
  *(portNVIC_SYSPRI3) |= portNVIC_SYSTICK_PRI; /* set priority of SysTick interrupt */
%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
#if configSYSTICK_USE_LOW_POWER_TIMER
  /* SIM_SCGx: enable clock to LPTMR */
  SIM_PDD_SetClockGate(SIM_BASE_PTR, SIM_PDD_CLOCK_GATE_LPTMR0, PDD_ENABLE);

  /* LPTRM0_CSR: clear TCF (Timer compare Flag) with writing a one to it */
  LPTMR_PDD_ClearInterruptFlag(LPTMR0_BASE_PTR);
  
  /* LPTMR_PSR: configure prescaler, bypass and clock source */
  /*           PBYP PCS
   * ERCLK32    1   10
   * LPO_1kHz   1   01
   * ERCLK      0   00
   * IRCLK      1   00
   */
  LPTMR_PDD_SelectPrescalerSource(LPTMR0_BASE_PTR, LPTMR_PDD_SOURCE_LPO1KHZ);
  LPTMR_PDD_EnablePrescalerBypass(LPTMR0_BASE_PTR, LPTMR_PDD_BYPASS_ENABLED);

  /* set timer interrupt priority in IP[] and enable it in ISER[] */
  NVIC_SetPriority(LDD_ivIndex_INT_LPTimer, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
  NVIC_EnableIRQ(LDD_ivIndex_INT_LPTimer); /* enable IRQ in NVIC_ISER[] */
#else /* use normal SysTick Counter */
  *(portNVIC_SYSPRI3) |= portNVIC_SYSTICK_PRI; /* set priority of SysTick interrupt */
#endif
  /* Configure timer to interrupt at the requested rate. */
  SET_TICK_DURATION(TIMER_COUNTS_FOR_ONE_TICK-1UL);
  RESET_TICK_COUNTER_VAL();
  ENABLE_TICK_COUNTER();
%endif
}
/*-----------------------------------------------------------*/
void vPortStartTickTimer(void) {
%ifdef TickCntr
%if defined(TickCntr) & defined(@TickCntr@Reset)
  (void)%@TickCntr@'ModuleName'%.Reset();   %>40/* reset the tick counter */
%else
  /* Warning: not possible to reset timer! */
%endif
  (void)%@TickCntr@'ModuleName'%.Enable();  %>40/* start the tick timer */
%endif
%ifdef TickTimerLDD
  (void)%@TickTimerLDD@'ModuleName'%.Enable(RTOS_TickDevice);   %>40/* start the tick timer */
%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
  ENABLE_TICK_COUNTER();
%endif
}
/*-----------------------------------------------------------*/
void vPortStopTickTimer(void) {
%ifdef TickCntr
  (void)%@TickCntr@'ModuleName'%.Disable();                     %>40/* stop the tick timer */
%endif
%ifdef TickTimerLDD
  (void)%@TickTimerLDD@'ModuleName'%.Disable(RTOS_TickDevice);   %>40/* stop the tick timer */
%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
  DISABLE_TICK_COUNTER();
%endif
}
/*-----------------------------------------------------------*/
#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
#if (configCOMPILER==configCOMPILER_ARM_GCC)
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
#elif (configCOMPILER==configCOMPILER_ARM_KEIL)
__asm void vPortEnableVFP(void) {
	PRESERVE8

	/* The FPU enable bits are in the CPACR. */
	ldr.w r0, =0xE000ED88
	ldr	r1, [r0]

	/* Enable CP10 and CP11 coprocessors, then save back. */
	orr	r1, r1, #( 0xf << 20 )
	str r1, [r0]
	bx	r14
	nop
}
#endif /* GNU or Keil */
#endif /* configCPU_FAMILY_ARM_M4F */
/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler(void) {
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  uxCriticalNesting = 0;
  vPortInitTickTimer();
  vPortStartTickTimer();
#if configUSE_TASK_END_SCHEDULER
  if (setjmp(xJumpBuf)!=0) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
#endif
  /* Kick off the scheduler by setting up the context of the first task. */
  vPortStartFirstTask();     %>40/* start the first task executing. Note that we will not return here */
  return pdFALSE;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
  /* xPortStartScheduler() does not start the scheduler directly because
     the header file containing the xPortStartScheduler() prototype is part
     of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     Instead it simply calls the locally defined xBankedStartScheduler() -
     which does use the CODE_SEG pragma. */
  vPortInitTickTimer();
  vPortStartTickTimer();
#if configUSE_TASK_END_SCHEDULER
  if(setjmp(xJumpBuf) != 0 ) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
#endif
  return xBankedStartScheduler();
%elif (CPUfamily = "Kinetis")
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
#if configUSE_TASK_END_SCHEDULER
    if(setjmp(xJumpBuf) != 0 ) {
      /* here we will get in case of call to vTaskEndScheduler() */
      return pdFALSE;
    }
#endif
  vPortStartFirstTask(); /* Start the first task. */
  /* Should not get here, unless you call vTaskEndScheduler()! */
  return pdFALSE;
%elif (CPUfamily = "56800")
  uxCriticalNesting = 0; /* initialize critical nesting count */
  vPortInitTickTimer(); /* initialize tick timer */
  vPortStartTickTimer(); /* start tick timer */
#if configUSE_TASK_END_SCHEDULER
  if(setjmp(xJumpBuf) != 0 ) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
#endif
  /* Kick off the scheduler by setting up the context of the first task. */
  vPortStartFirstTask();     %>40/* start the first task executing. Note that we will not return here */
  return pdFALSE;
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
}
/*-----------------------------------------------------------*/
void vPortEndScheduler(void) {
  vPortStopTickTimer();
  /* Jump back to the processor state prior to starting the
     scheduler.  This means we are not going to be using a
     task stack frame so the task can be deleted. */
#if configUSE_TASK_END_SCHEDULER
  longjmp(xJumpBuf, 1);
#else
  for(;;){} /* wait here */
#endif
}
/*-----------------------------------------------------------*/
void vPortEnterCritical(void) {
/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  if (uxCriticalNesting == 0) {
    /* Guard against context switches being pended simultaneously with a
       critical section being entered. */
    do {
      portDISABLE_INTERRUPTS();
%if (CPUfamily = "ColdFireV1")
      if (INTC_FRC == 0UL) {
        break;
      }
%elif (CPUfamily = "MCF")
      if (INTFRCH0 == 0UL) { /* interrupt force register high */
        break;
      }
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
      portENABLE_INTERRUPTS();
    } while(1);
  }
  uxCriticalNesting++;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X") | (CPUfamily = "Kinetis") | (CPUfamily = "56800")
  portDISABLE_INTERRUPTS();
  portPOST_ENABLE_DISABLE_INTERRUPTS();
  uxCriticalNesting++;
  %if (CPUfamily = "Kinetis")
  %if %Compiler="CodeWarriorARM" %- not supported by Freescale ARM compiler
  %else
  __asm volatile("dsb");
  __asm volatile("isb");
  %endif
  %endif
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
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
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
/*-----------------------------------------------------------*/
void vPortYieldHandler(void) {
  unsigned portLONG ulSavedInterruptMask;

  ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
  {
     /* Note this will clear all forced interrupts - this is done for speed. */
%if (CPUfamily = "ColdFireV1")
     INTC_CFRC = portCF_INTC_VALUE;
%elif (CPUfamily = "MCF")
     INTFRCL0 = 0; /* interrupt force register low */
%else
  #error "unsupported target %CPUfamily!"
%endif
     vTaskSwitchContext();
  }
  portCLEAR_INTERRUPT_MASK_FROM_ISR(ulSavedInterruptMask);
}
%endif
%if (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
/*-----------------------------------------------------------*/
%if (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#ifdef __BANKED__ /* in banked memory model, interrupt service routines are in nonbanked area */
  #pragma CODE_SEG __NEAR_SEG NON_BANKED
#endif
%elif (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
#pragma CODE_SEG __NEAR_SEG NON_BANKED
%endif
__interrupt void vPortYieldISR(void) {
  portTASK_SWITCH_FROM_ISR();
}

%if (CPUfamily = "HCS08") | (CPUfamily = "HC08")
#ifdef __BANKED__ /* switch back to default memory segment */
  #pragma CODE_SEG DEFAULT
#endif
%elif (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
#pragma CODE_SEG DEFAULT
%endif
%endif
/*-----------------------------------------------------------*/
%if (CPUfamily = "Kinetis")
void vPortYieldFromISR(void) {
  /* Set a PendSV to request a context switch. */
  *(portNVIC_INT_CTRL) = portNVIC_PENDSVSET_BIT;
  /* Barriers are normally not required but do ensure the code is completely
  within the specified behavior for the architecture. */
  %if %Compiler="CodeWarriorARM" %- not supported by Freescale ARM compiler
  %else
  __asm volatile("dsb");
  __asm volatile("isb");
  %endif
}
/*-----------------------------------------------------------*/
%endif
%if (CPUfamily = "56800")
void vPortYield(void) {
  portSAVE_CONTEXT();
  vTaskSwitchContext();
  portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/
%endif
%ifdef TickCntr
#include "portTicks.h"
/* return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time */
portLONG uxGetTickCounterValue(void) {
  %@TickCntr@'ModuleName'%.TTimerValue val;

  (void)%@TickCntr@'ModuleName'%.GetCounterValue(&val);
  return (portLONG)val;
}
/*-----------------------------------------------------------*/
%endif
%ifdef TickTimerLDD
/* return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time */
portLONG uxGetTickCounterValue(void) {
  return (portLONG)%@TickTimerLDD@'ModuleName'%.GetCounterValue(RTOS_TickDevice);
}
/*-----------------------------------------------------------*/
%elif defined(useARMSysTickTimer) & useARMSysTickTimer='yes'
/* return the tick raw counter value. It is assumed that the counter register has been reset at the last tick time */
portLONG uxGetTickCounterValue(void) {
  portLONG val;
  
  GET_TICK_CURRENT_VAL(&val);
  return val;
}
/*-----------------------------------------------------------*/
%endif
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
void SysTick_Handler(void) {
#else
void vPortTickHandler(void) {
#endif
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
%if defined(useARMSysTickTimer) && useARMSysTickTimer='yes'
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
void SysTick_Handler(void) {
#else
void vPortTickHandler(void) {
#endif
%else
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
  __attribute__ ((naked)) void SysTick_Handler(void) {
#else
__attribute__ ((naked)) void vPortTickHandler(void) {
#endif
%endif
%if defined(useARMSysTickTimer) && useARMSysTickTimer='no'
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
  #if __OPTIMIZE_SIZE__ || __OPTIMIZE__
    /*
              RTOSTICKLDD1_Interrupt:
    249       {
    0000102c:   cpy r0,sp
    0000102e:   bic r1,r0,#0x7
    00001032:   cpy sp,r1
    00001034:   push {r0,lr}  <===
    ...
    00001046:   bl RTOSTICKLDD1_OnCounterRestart (0x90c); 0x0000090c
    ....
    */
    /* nothing needed, as SP and LR are already on the stack */
  #else
  /* Code in RTOSTICKLDD1_Interrupt():
   0:	4668      	mov	r0, sp
   2:	f020 0107 	bic.w	r1, r0, #7
   6:	468d      	mov	sp, r1
   8:	b581      	push	{r0, r7, lr}   <=============
   a:	b083      	sub	sp, #12        <=============
   c:	af00      	add	r7, sp, #0
  ...
  38:	f7ff fffe 	bl	0 <RTOSTICKLDD1_OnCounterRestart>
  3c:	f107 070c 	add.w	r7, r7, #12     <============
  40:	46bd      	mov	sp, r7
  42:	e8bd 4081 	ldmia.w	sp!, {r0, r7, lr} <===========
  46:	4685      	mov	sp, r0
  48:	4770      	bx	lr
  */
  __asm volatile (
    " add sp,sp,#12   \n" /* remove space allocated in RTOSTICKLDD1_Interrupt() */
    " pop {r0,r7,lr}  \n" /* these were pushed in RTOSTICKLDD1_Interrupt() */
    " push {r4,lr}    \n"
  );
  #endif
#else /* Cortex M0+ */
  #if __OPTIMIZE_SIZE__ || __OPTIMIZE__
  /*
PE_ISR(RTOSTICKLDD1_Interrupt)
{
   0:	b508      	push	{r3, lr}  <<================
    RTOSTICKLDD1_TDeviceDataPtr DeviceDataPrv = INT_SysTick__BAREBOARD_RTOS_ISRPARAM;
   2:	4b05      	ldr	r3, [pc, #20]	; (18 <RTOSTICKLDD1_Interrupt+0x18>)
  SysTick_PDD_ClearInterruptFlag(SysTick_BASE_PTR); // Clear interrupt flag
   4:	4905      	ldr	r1, [pc, #20]	; (1c <RTOSTICKLDD1_Interrupt+0x1c>)
  RTOSTICKLDD1_TDeviceDataPtr DeviceDataPrv = INT_SysTick__BAREBOARD_RTOS_ISRPARAM;
   6:	681a      	ldr	r2, [r3, #0]
  SysTick_PDD_ClearInterruptFlag(SysTick_BASE_PTR); // Clear interrupt flag
   8:	4b05      	ldr	r3, [pc, #20]	; (20 <RTOSTICKLDD1_Interrupt+0x20>)
   a:	6818      	ldr	r0, [r3, #0]
   c:	4001      	ands	r1, r0
   e:	6019      	str	r1, [r3, #0]
  RTOSTICKLDD1_OnCounterRestart(DeviceDataPrv->UserDataPtr); // Invoke OnCounterRestart event
  10:	6810      	ldr	r0, [r2, #0]
  12:	f7ff fffe 	bl	0 <RTOSTICKLDD1_OnCounterRestart>
   */
  /* nothing needed, as r3 and LR are already on the stack */
  #else
  /*
    //PE_ISR(RTOSTICKLDD1_Interrupt):
     0:	b580      	push	{r7, lr} <<===================
     2:	b082      	sub	sp, #8      <<====================
     4:	af00      	add	r7, sp, #0
    RTOSTICKLDD1_TDeviceDataPtr DeviceDataPrv = INT_SysTick__BAREBOARD_RTOS_ISRPARAM;
     6:	4b09      	ldr	r3, [pc, #36]	; (2c <RTOSTICKLDD1_Interrupt+0x2c>)
     8:	681b      	ldr	r3, [r3, #0]
     a:	607b      	str	r3, [r7, #4]

    SysTick_PDD_ClearInterruptFlag(SysTick_BASE_PTR); // Clear interrupt flag
     c:	4b08      	ldr	r3, [pc, #32]	; (30 <RTOSTICKLDD1_Interrupt+0x30>)
     e:	4a08      	ldr	r2, [pc, #32]	; (30 <RTOSTICKLDD1_Interrupt+0x30>)
    10:	6812      	ldr	r2, [r2, #0]
    12:	1c11      	adds	r1, r2, #0
    14:	4a07      	ldr	r2, [pc, #28]	; (34 <RTOSTICKLDD1_Interrupt+0x34>)
    16:	400a      	ands	r2, r1
    18:	601a      	str	r2, [r3, #0]
    RTOSTICKLDD1_OnCounterRestart(DeviceDataPrv->UserDataPtr); // Invoke OnCounterRestart event
    1a:	687b      	ldr	r3, [r7, #4]
    1c:	681b      	ldr	r3, [r3, #0]
    1e:	1c18      	adds	r0, r3, #0
    20:	f7ff fffe 	bl	0 <RTOSTICKLDD1_OnCounterRestart>
   */
  __asm volatile (
    " add sp,#8       \n" /* remove space allocated in RTOSTICKLDD1_Interrupt() */
    " pop {r0, r7}    \n" /* restore r7 and lr into r0 and r7, which were pushed in RTOSTICKLDD1_Interrupt() */
    " push {r0, r7}   \n"
  );
  #endif
#endif
%endif -% useARMSysTickTimer='no'
  ACKNOWLEDGE_TICK_ISR();
#if configUSE_TICKLESS_IDLE == 1
  TICK_INTERRUPT_FLAG_SET();
#endif
  portSET_INTERRUPT_MASK();   /* disable interrupts */
  if (xTaskIncrementTick()!=pdFALSE) { /* increment tick count */
    taskYIELD();
  }
  portCLEAR_INTERRUPT_MASK(); /* enable interrupts again */
%if defined(useARMSysTickTimer) && useARMSysTickTimer='no'
#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
  #if __OPTIMIZE_SIZE__ || __OPTIMIZE__
  __asm volatile (
    " pop {r0,lr}  \n" /* start exit sequence from interrupt: sp and lr where pushed */
    " mov sp, r0   \n"
    " bx lr        \n"
    " nop          \n"
  );
  #else
  __asm volatile (
    " pop {r4,lr}  \n" /* start exit sequence from interrupt: r4 and lr where pushed above */
    " bx lr        \n"
    " nop          \n"
  );
  #endif
#else /* Cortex M0+ */
#if __OPTIMIZE_SIZE__ || __OPTIMIZE__
  __asm volatile (
    " pop {r3,pc}                \n" /* start exit sequence from interrupt: r3 and lr where pushed above */
  );
#else
  __asm volatile (
    " pop {r7,pc}                \n" /* start exit sequence from interrupt: r7 and lr where pushed above */
  );
#endif
#endif
%endif %- useARMSysTickTimer='no'
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
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__asm void SVC_Handler(void) {
#else
__asm void vPortSVCHandler(void) {
#endif
  PRESERVE8
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
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r0
#if (configCPU_FAMILY==configCPU_FAMILY_ARM_M4F)
#else
  orr r14, r14, #13
#endif
  bx r14
}
/*-----------------------------------------------------------*/
#else /* Cortex M0+ */
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__asm void SVC_Handler(void) {
#else
__asm void vPortSVCHandler(void) {
#endif
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
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__attribute__ ((naked)) void SVC_Handler(void) {
#else
__attribute__ ((naked)) void vPortSVCHandler(void) {
#endif
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
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__asm void PendSV_Handler(void) {
#else
__asm void vPortPendSVHandler(void) {
#endif
  PRESERVE8
  EXTERN pxCurrentTCB
  EXTERN vTaskSwitchContext

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
  mov r0, #0
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
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__asm void PendSV_Handler(void) {
#else
__asm void vPortPendSVHandler(void) {
#endif
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
#if configPEX_KINETIS_SDK /* the SDK expects different interrupt handler names */
__attribute__ ((naked)) void PendSV_Handler(void) {
#else
__attribute__ ((naked)) void vPortPendSVHandler(void) {
#endif
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
    " mov r0, %%0                 \n"
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
