/*
 * FreeRTOS Kernel V10.5.1
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
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
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*-----------------------------------------------------------
 * FreeRTOS for 56800EX port by Richy Ye in Jan. 2013.
 *----------------------------------------------------------*/
/* Scheduler includes. */
#include "FreeRTOS.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS

#include "portmacro.h" /* for configCPU_FAMILY */
#include "task.h"
#include "portTicks.h" /* for CPU_CORE_CLK_HZ used in configSYSTICK_CLOCK_HZ */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #if McuLib_CONFIG_NXP_SDK_2_0_USED
    #include "fsl_lptmr.h" /* SDK low power timer interface */
  #elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
    #include "LPTMR_PDD.h" /* PDD interface to low power timer */
    #include "SIM_PDD.h"   /* PDD interface to system integration module */
  #endif
#endif

#include "McuLib.h" /* include SDK and API used */
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M

#if( configENABLE_TRUSTZONE == 1 )
  /* Secure components includes. */
  #include "secure_context.h"
  #include "secure_init.h"
#endif /* configENABLE_TRUSTZONE */

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/**
 * The FreeRTOS Cortex M33 port can be configured to run on the Secure Side only
 * i.e. the processor boots as secure and never jumps to the non-secure side.
 * The Trust Zone support in the port must be disabled in order to run FreeRTOS
 * on the secure side. The following are the valid configuration seetings:
 *
 * 1. Run FreeRTOS on the Secure Side:
 *    configRUN_FREERTOS_SECURE_ONLY = 1 and configENABLE_TRUSTZONE = 0
 *
 * 2. Run FreeRTOS on the Non-Secure Side with Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 1
 *
 * 3. Run FreeRTOS on the Non-Secure Side only i.e. no Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 0
 */
#if( ( configRUN_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
  #error TrustZone needs to be disabled in order to run FreeRTOS on the Secure Side.
#endif

#endif /*  McuLib_CONFIG_CPU_IS_ARM_CORTEX_M */
/* --------------------------------------------------- */
/* Let the user override the pre-loading of the initial LR with the address of
   prvTaskExitError() in case is messes up unwinding of the stack in the
   debugger. */
#ifdef configTASK_RETURN_ADDRESS
  #define portTASK_RETURN_ADDRESS   configTASK_RETURN_ADDRESS
#else
  #define portTASK_RETURN_ADDRESS   prvTaskExitError
#endif
/* --------------------------------------------------- */
/* macros dealing with tick counter */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #if !McuLib_CONFIG_PEX_SDK_USED
    #define LPTMR0_BASE_PTR             LPTMR0  /* low power timer address base */
    #define configLOW_POWER_TIMER_VECTOR_NUMBER   LPTMR0_IRQn /* low power timer IRQ number */
    #define ENABLE_TICK_COUNTER()       LPTMR_StartTimer(LPTMR0_BASE_PTR); LPTMR_EnableInterrupts(LPTMR0_BASE_PTR, kLPTMR_TimerInterruptEnable)
    #define DISABLE_TICK_COUNTER()      LPTMR_StopTimer(LPTMR0_BASE_PTR)
    #define RESET_TICK_COUNTER_VAL()    LPTMR_StopTimer(LPTMR0_BASE_PTR); LPTMR_DisableInterrupts(LPTMR0_BASE_PTR, kLPTMR_TimerInterruptEnable)
    #define ACKNOWLEDGE_TICK_ISR()      LPTMR_ClearStatusFlags(LPTMR0_BASE_PTR, kLPTMR_TimerCompareFlag);
  #elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
    #define ENABLE_TICK_COUNTER()       LPTMR_PDD_EnableDevice(LPTMR0_BASE_PTR, PDD_ENABLE); LPTMR_PDD_EnableInterrupt(LPTMR0_BASE_PTR)
    #define DISABLE_TICK_COUNTER()      LPTMR_PDD_EnableDevice(LPTMR0_BASE_PTR, PDD_DISABLE); LPTMR_PDD_DisableInterrupt(LPTMR0_BASE_PTR)
    #define RESET_TICK_COUNTER_VAL()    DISABLE_TICK_COUNTER()  /* CNR is reset when the LPTMR is disabled or counter register overflows */
    #define ACKNOWLEDGE_TICK_ISR()      LPTMR_PDD_ClearInterruptFlag(LPTMR0_BASE_PTR)
    #if defined(LDD_ivIndex_INT_LPTimer) /* Earlier version of Processor Expert use this vector name */
      #define configLOW_POWER_TIMER_VECTOR_NUMBER   LDD_ivIndex_INT_LPTimer
    #elif defined(LDD_ivIndex_INT_LPTMR0) /* Newer versions (Processor Expert for Kinetis v3.0.1 uses this name */
      #define configLOW_POWER_TIMER_VECTOR_NUMBER   LDD_ivIndex_INT_LPTMR0
    #else
      #error "Unknown Low Power Timer Interrupt Number?"
    #endif
  #endif
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
  #if !McuLib_CONFIG_PEX_SDK_USED
    #define SET_TICK_DURATION(val)      LPTMR_SetTimerPeriod(LPTMR0_BASE_PTR, val+1) /* new SDK V2.8 requires a value >0 */
    #define GET_TICK_DURATION()         LPTMR0_BASE_PTR->CMR /*!< SDK has no access method for getting the counter modulo register */
    #define GET_TICK_CURRENT_VAL(addr)  *(addr)=LPTMR_GetCurrentTimerCount(LPTMR0_BASE_PTR)
  #else
    #define SET_TICK_DURATION(val)      LPTMR_PDD_WriteCompareReg(LPTMR0_BASE_PTR, val)
    #define GET_TICK_DURATION()         LPTMR_PDD_ReadCompareReg(LPTMR0_BASE_PTR)
    #define GET_TICK_CURRENT_VAL(addr)  *(addr)=LPTMR_PDD_ReadCounterReg(LPTMR0_BASE_PTR)
  #endif
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

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configCPU_FAMILY==configCPU_FAMILY_ARM_M0P
  unsigned int SEGGER_SYSVIEW_TickCnt; /* tick counter for Segger SystemViewer */
#endif

#if configUSE_TICKLESS_IDLE
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

  #if 1 /* using ARM SysTick Timer */
    #if configSYSTICK_USE_LOW_POWER_TIMER
      /* using Low Power Timer */
      #if McuLib_CONFIG_PEX_SDK_USED
        #define LPTMR_CSR_TCF_MASK           0x80u
        #define TICK_INTERRUPT_HAS_FIRED()   (LPTMR0_BASE_PTR->CSR&LPTMR_CSR_TCF_MASK)!=0 /* returns TRUE if tick interrupt had fired */
      #else
        #define TICK_INTERRUPT_HAS_FIRED()   ((LPTMR_GetStatusFlags(LPTMR0_BASE_PTR)&kLPTMR_TimerCompareFlag)!=0) /* returns TRUE if tick interrupt had fired */
      #endif
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
 * power functionality only).
 */
#if configUSE_TICKLESS_IDLE == 1
  static TickCounter_t ulStoppedTimerCompensation = 0; /* number of timer ticks to compensate */
  #define configSTOPPED_TIMER_COMPENSATION    45UL  /* number of CPU cycles to compensate. ulStoppedTimerCompensation will contain the number of timer ticks. */
#endif /* configUSE_TICKLESS_IDLE */

/* Flag indicating that the tick counter interval needs to be restored back to
 * the normal setting. Used when woken up from a low power mode using the LPTMR.
 */
#if configUSE_TICKLESS_IDLE && configSYSTICK_USE_LOW_POWER_TIMER
  static uint8_t restoreTickInterval = 0; /* used to flag in tick ISR that compare register needs to be reloaded */
#endif

#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2)
  #define portINITIAL_FORMAT_VECTOR           ((portSTACK_TYPE)0x4000)
  #define portINITIAL_STATUS_REGISTER         ((portSTACK_TYPE)0x2000)  /* Supervisor mode set. */
#endif

#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)

/* For strict compliance with the Cortex-M spec the task start address should
have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK				( ( StackType_t ) 0xfffffffeUL )

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

#if configSYSTICK_USE_LOW_POWER_TIMER && McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
#define IRQn_Type int
#define __NVIC_PRIO_BITS          configPRIO_BITS
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
/** \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
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
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
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
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  NVIC->ISER[(uint32_t)((int32_t)IRQn) >> 5] = (uint32_t)(1 << ((uint32_t)((int32_t)IRQn) & (uint32_t)0x1F)); /* enable interrupt */
#else /* M0+ */
  NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* enable interrupt */
#endif
}
#endif /* configSYSTICK_USE_LOW_POWER_TIMER */

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                       (0x01000000)
#define portINITIAL_EXEC_RETURN                (0xfffffffd)
#define portINITIAL_CONTROL_IF_UNPRIVILEGED    (0x03)
#define portINITIAL_CONTROL_IF_PRIVILEGED      (0x02)

#if configENABLE_FPU
  /* Constants required to manipulate the VFP. */
  #define portFPCCR                ((volatile unsigned long *)0xe000ef34) /* Floating point context control register. */
  #define portASPEN_AND_LSPEN_BITS (0x3UL<<30UL)
#endif
#endif
/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().
   This will be set to 0 prior to the first task being started. */
/* Each task maintains its own interrupt status in the critical nesting variable. */
static unsigned portBASE_TYPE uxCriticalNesting = 0xaaaaaaaa;

#if INCLUDE_vTaskEndScheduler
#include <setjmp.h>
static jmp_buf xJumpBuf; /* Used to restore the original context when the scheduler is ended. */
#endif
/*-----------------------------------------------------------*/
void prvTaskExitError(void) {
  /* A function that implements a task must not exit or attempt to return to
  its caller as there is nothing to return to.  If a task wants to exit it
  should instead call vTaskDelete( NULL ).

  Artificially force an assert() to be triggered if configASSERT() is
  defined, then stop here so application writers can catch the error. */
  configASSERT(uxCriticalNesting == ~0UL);
  portDISABLE_INTERRUPTS();
  for(;;) {
    /* wait here */
  }
}
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL) && (configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)  || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY)) /* ARM M4(F)/M7/M33 core */
__asm uint32_t ulPortSetInterruptMask(void) {
  PRESERVE8

  mrs r0, basepri
  mov r1, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r1
  bx r14
}
#endif /* (configCOMPILER==configCOMPILER_ARM_KEIL) */
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL) && (configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */)
__asm void vPortClearInterruptMask(uint32_t ulNewMask) {
  PRESERVE8

  msr basepri, r0
  bx r14
}
#endif /* (configCOMPILER==configCOMPILER_ARM_KEIL) */
/*-----------------------------------------------------------*/
#if configENABLE_MPU
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters, BaseType_t xRunPrivileged) {
#else
StackType_t *pxPortInitialiseStack(portSTACK_TYPE *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters) {
#endif
  /* Simulate the stack frame as it would be created by a context switch interrupt. */
  pxTopOfStack--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts, and to ensure alignment. */
  *pxTopOfStack = portINITIAL_XPSR;   /* xPSR */
  pxTopOfStack--;
#if configENABLE_MPU
  *pxTopOfStack = ((StackType_t)pxCode)&portSTART_ADDRESS_MASK;  /* PC */
#else
  *pxTopOfStack = ((StackType_t)pxCode);  /* PC */
#endif
  pxTopOfStack--;
  *pxTopOfStack = (StackType_t)portTASK_RETURN_ADDRESS;  /* LR */

  /* Save code space by skipping register initialization. */
  pxTopOfStack -= 5;  /* R12, R3, R2 and R1. */
  *pxTopOfStack = (portSTACK_TYPE)pvParameters; /* R0 */

#if configENABLE_FPU /* has floating point unit */
  /* A save method is being used that requires each task to maintain its
     own exec return value. */
  pxTopOfStack--;
  *pxTopOfStack = portINITIAL_EXEC_RETURN;
#endif
#if configENABLE_MPU
  pxTopOfStack -= 9;  /* R11, R10, R9, R8, R7, R6, R5 and R4 plus privilege level */
  if (xRunPrivileged == pdTRUE) {
    *pxTopOfStack = portINITIAL_CONTROL_IF_PRIVILEGED;
  } else {
    *pxTopOfStack = portINITIAL_CONTROL_IF_UNPRIVILEGED;
  }
#else
  pxTopOfStack -= 8;  /* R11, R10, R9, R8, R7, R6, R5 and R4. */
#endif
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
void McuRTOS_vOnPreSleepProcessing(TickType_t expectedIdleTicks); /* prototype */

void McuRTOS_vOnPostSleepProcessing(TickType_t expectedIdleTicks); /* prototype */

#if (configCOMPILER==configCOMPILER_ARM_GCC) || (configCOMPILER==configCOMPILER_ARM_KEIL)
__attribute__((weak))
#endif
void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime) {
  unsigned long ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickIncrements;
  TickCounter_t tmp; /* because of how we get the current tick counter */
  bool tickISRfired;
  uint32_t tickDuration;
  
#if configSYSTICK_USE_LOW_POWER_TIMER
  /* if we wait for the tick interrupt, do not enter low power again below */
  if (restoreTickInterval!=0) {
    McuRTOS_vOnPreSleepProcessing(xExpectedIdleTime); /* go into low power mode. Re-enable interrupts as needed! */
#if 0 /* default example code */
    /* default wait/sleep code */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#endif
    return;
  }
#endif

  /* Make sure the tick timer reload value does not overflow the counter. */
  if(xExpectedIdleTime > xMaximumPossibleSuppressedTicks) {
    xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
  }

  /* Stop the tick timer momentarily. The time the counter is stopped for
   * is accounted for as best it can be, but using the tickless mode will
   * inevitably result in some tiny drift of the time maintained by the
   * kernel with respect to calendar time. 
   */
#if configSYSTICK_USE_LOW_POWER_TIMER
  /* disabling the LPTMR does reset the timer register! So I need to get the value first, then disable the timer: */
  GET_TICK_CURRENT_VAL(&tmp);
  DISABLE_TICK_COUNTER();
#else /* using normal timer or SysTick */
  DISABLE_TICK_COUNTER();
  GET_TICK_CURRENT_VAL(&tmp);
#endif
  /* Calculate the reload value required to wait xExpectedIdleTime
   * tick periods. This code will execute part way through one
   * of the tick periods.
   */
  /* -1UL is used because this code will execute part way through one of the tick periods */
#if COUNTS_UP
  ulReloadValue = (UL_TIMER_COUNTS_FOR_ONE_TICK*xExpectedIdleTime);
  #if configSYSTICK_USE_LOW_POWER_TIMER
  if (ulReloadValue > 0) { /* make sure it does not underflow */
    ulReloadValue -= 1UL; /* LPTMR: interrupt will happen at match of compare register && increment, thus minus 1 */
  }
  #endif
  if (tmp!=0 && ulReloadValue>=tmp) { /* make sure it does not underflow */
    ulReloadValue -= tmp; /* take into account what we already executed in the current tick period */
  }
#else
  ulReloadValue = tmp+(UL_TIMER_COUNTS_FOR_ONE_TICK*(xExpectedIdleTime-1UL));
#endif
  if (ulStoppedTimerCompensation!=0 && ulReloadValue>ulStoppedTimerCompensation) {
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
     /* Must restore the duration before re-enabling the timers */
#if COUNTS_UP
    #if configSYSTICK_USE_LOW_POWER_TIMER
    tickDuration = UL_TIMER_COUNTS_FOR_ONE_TICK-1UL; /* LPTMR: interrupt will happen at match of compare register && increment, thus minus 1 */
    #else
    tickDuration = UL_TIMER_COUNTS_FOR_ONE_TICK;
    #endif
    if (tmp!=0 && tickDuration >= tmp) { /* make sure it does not underflow */
      tickDuration -= tmp; /* take into account what we already executed in the current tick period */
    }
#else
    tickDuration = tmp;
#endif
    SET_TICK_DURATION(tickDuration);
    ENABLE_TICK_COUNTER(); /* Restart tick timer. */
    TICKLESS_ENABLE_INTERRUPTS();
  } else {
    SET_TICK_DURATION(ulReloadValue); /* Set the new reload value. */
    RESET_TICK_COUNTER_VAL(); /* Reset the counter. */
    ENABLE_TICK_COUNTER(); /* Restart tick timer. */
    TICK_INTERRUPT_FLAG_RESET(); /* reset flag so we know later if it has fired */

    /* Sleep until something happens. configPRE_SLEEP_PROCESSING() can
     * set its parameter to 0 to indicate that its implementation contains
     * its own wait for interrupt or wait for event instruction, and so wfi
     * should not be executed again.  However, the original expected idle
     * time variable must remain unmodified, so a copy is taken.
     */

     /* CPU *HAS TO WAIT* in the sequence below for an interrupt. If vOnPreSleepProcessing() is not used, a default implementation is provided */
    McuRTOS_vOnPreSleepProcessing(xExpectedIdleTime); /* go into low power mode. Re-enable interrupts as needed! */
#if 0 /* example/default code */
    /* default wait/sleep code */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#endif
    /* ----------------------------------------------------------------------------
     * Here the CPU *HAS TO BE* in a low power mode, waiting to wake up by an interrupt 
     * ----------------------------------------------------------------------------*/
    McuRTOS_vOnPostSleepProcessing(xExpectedIdleTime); /* process post-low power actions */
    /* Stop tick counter. Again, the time the tick counter is stopped for is
     * accounted for as best it can be, but using the tickless mode will
     * inevitably result in some tiny drift of the time maintained by the
     * kernel with respect to calendar time. 
     */
    tickISRfired = (bool)TICK_INTERRUPT_HAS_FIRED(); /* need to check Interrupt flag here, as might be modified below */
#if configSYSTICK_USE_LOW_POWER_TIMER
    /* disabling the LPTMR does reset the timer register! So I need to get the value first, then disable the timer: */
    GET_TICK_CURRENT_VAL(&tmp);
    DISABLE_TICK_COUNTER();
#else
    DISABLE_TICK_COUNTER();
    GET_TICK_CURRENT_VAL(&tmp);
#endif
    TICKLESS_ENABLE_INTERRUPTS();/* Re-enable interrupts */
    if (tickISRfired) {
      /* The tick interrupt has already executed, and the timer
       * count reloaded with the modulo/match value.
       * Reset the counter register with whatever remains of
       * this tick period. 
       */
#if COUNTS_UP
    #if configSYSTICK_USE_LOW_POWER_TIMER
      tickDuration = (UL_TIMER_COUNTS_FOR_ONE_TICK-1UL); /* LPTMR: interrupt will happen at match of compare register && increment, thus minus 1 */
    #else
      tickDuration = UL_TIMER_COUNTS_FOR_ONE_TICK;
    #endif
      if (tickDuration >= tmp) { /* make sure it does not underflow */
        tickDuration -= tmp;
      }
      if (tickDuration > 1) {
        /*! Need to rethink this one! */
        //tickDuration -= 1; /* decrement by one, to compensate for one timer tick, as we are already part way through it */
      } else {
        /* Not enough time to setup for the next tick, so skip it and setup for the
         * next. Make sure to count the tick we skipped.
         */
        tickDuration += (UL_TIMER_COUNTS_FOR_ONE_TICK - 1UL);
        vTaskStepTick(1);
      }
#else
      tickDuration = (UL_TIMER_COUNTS_FOR_ONE_TICK-1UL)-(ulReloadValue-tmp);
#endif
      SET_TICK_DURATION(tickDuration);
      /* The tick interrupt handler will already have pended the tick
       * processing in the kernel.  As the pending tick will be
       * processed as soon as this function exits, the tick value
       * maintained by the tick is stepped forward by one less than the
       * time spent waiting.
       */
      ulCompleteTickPeriods = xExpectedIdleTime-1UL; /* -1 because we already added a completed tick from the tick interrupt */
    } else {
      /* Something other than the tick interrupt ended the sleep.
       * Work out how long the sleep lasted rounded to complete tick
       * periods (not the ulReload value which accounted for part ticks). 
       */
#if COUNTS_UP
      ulCompletedSysTickIncrements = tmp;
      /* How many complete tick periods passed while the processor was waiting? */
      ulCompleteTickPeriods = ulCompletedSysTickIncrements/UL_TIMER_COUNTS_FOR_ONE_TICK;
      /* The reload value is set to whatever fraction of a single tick period remains. */
      tickDuration = (((ulCompleteTickPeriods+1)*UL_TIMER_COUNTS_FOR_ONE_TICK)-1)-ulCompletedSysTickIncrements;
      if (tickDuration > 1) {
        tickDuration -= 1; /* decrement by one, to compensate for one timer tick, as we are already part way through it */
      } else {
         /* Not enough time to setup for the next tick, so skip it and setup for the
          * next. Make sure to count the tick we skipped.
          */
         tickDuration += (UL_TIMER_COUNTS_FOR_ONE_TICK - 1UL);
         if (tickDuration > 1) { /* check for underflow */
           tickDuration -= 1;
         }
         vTaskStepTick(1);
      }
#else
      ulCompletedSysTickIncrements = (xExpectedIdleTime*UL_TIMER_COUNTS_FOR_ONE_TICK)-tmp;
      /* How many complete tick periods passed while the processor was waiting? */
      ulCompleteTickPeriods = ulCompletedSysTickIncrements/UL_TIMER_COUNTS_FOR_ONE_TICK;
      /* The reload value is set to whatever fraction of a single tick period remains. */
      tickDuration = ((ulCompleteTickPeriods+1)*UL_TIMER_COUNTS_FOR_ONE_TICK)-ulCompletedSysTickIncrements;
#endif
      SET_TICK_DURATION(tickDuration);
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
      if (ulCompleteTickPeriods>0) {
        vTaskStepTick(ulCompleteTickPeriods);
      }
#if configSYSTICK_USE_LOW_POWER_TIMER
      /* The compare register of the LPTMR should not be modified when the
       * timer is running, so wait for the next tick interrupt to change it.
       */
      if (tickDuration != (UL_TIMER_COUNTS_FOR_ONE_TICK-1UL)) { /* minus one because of LPTMR way to trigger interrupts */
        if (tickISRfired) {
          /* The pending tick interrupt will be immediately processed after
           * exiting this function so we need to delay the change of the tick
           * duration until the one after that.
           */
          restoreTickInterval = 2;
        } else {
          /* Notify the tick interrupt that the tick duration needs to be
           * changed back to the normal setting.
           */
          restoreTickInterval = 1;
        }
      } else {
        /* If the duration is the standard full tick, then there's no reason
         * to stop and restart LPTMR in the tick interrupt.
         */
        restoreTickInterval = 0;
      }
#else
      /* The systick has a load register that will automatically be used
       * when the counter counts down to zero.
       */
      SET_TICK_DURATION(UL_TIMER_COUNTS_FOR_ONE_TICK-1UL);
#endif
    }
    portEXIT_CRITICAL();
  }
}
#endif /* #if configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/
static void vPortInitTickTimer(void) {
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
  /* SIM_SCGx: enable clock to LPTMR */
#if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
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
#elif McuLib_CONFIG_NXP_SDK_2_0_USED
  {
    lptmr_config_t config;

    LPTMR_GetDefaultConfig(&config);
    LPTMR_Init(LPTMR0_BASE_PTR, &config);
  }
#endif
  /* set timer interrupt priority in IP[] and enable it in ISER[] */
  NVIC_SetPriority(configLOW_POWER_TIMER_VECTOR_NUMBER, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
  NVIC_EnableIRQ(configLOW_POWER_TIMER_VECTOR_NUMBER); /* enable IRQ in NVIC_ISER[] */
#else /* use normal SysTick Counter */
  *(portNVIC_SYSPRI3) |= portNVIC_SYSTICK_PRI; /* set priority of SysTick interrupt */
#endif
  /* Configure timer to interrupt at the requested rate. */
  DISABLE_TICK_COUNTER(); /* disable the timer, just in case it is already running */
  SET_TICK_DURATION(TIMER_COUNTS_FOR_ONE_TICK-1UL); /* set tick period */
  RESET_TICK_COUNTER_VAL(); /* reset counter so it starts properly */
  ENABLE_TICK_COUNTER(); /* let it run */
}
/*-----------------------------------------------------------*/
static void vPortStartTickTimer(void) {
  ENABLE_TICK_COUNTER();
}
/*-----------------------------------------------------------*/
void vPortStopTickTimer(void) {
  DISABLE_TICK_COUNTER();
}
/*-----------------------------------------------------------*/
#if configENABLE_FPU /* has floating point unit */
void vPortEnableVFP(void) {
#if 1 /* configLTO_HELPER: using implementation in C which is portable */
  #define CPACR_REG_MEM   ((volatile int*)0xE000ED88)  /* location of the CPACR register */

  *CPACR_REG_MEM |= (0xf<<20); /* Enable CP10 and CP11 coprocessors */
#else /* below is the original assembly code which fails with -flto because of the constant load  */
  __asm volatile
  (
    " ldr.w r0, =0xE000ED88   \n" /* The FPU enable bits are in the CPACR. */
    " ldr r1, [r0]        \n"
    " orr r1, r1, #( 0xf << 20 )  \n" /* Enable CP10 and CP11 coprocessors, then save back. */
    " str r1, [r0]        \n"
    " bx r14            "
  );
#endif
}
#endif /* M4/M7 */
/*-----------------------------------------------------------*/
/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#if (configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */) && (configASSERT_DEFINED == 1)
  /* Constants required to check the validity of an interrupt priority. */
  #define portFIRST_USER_INTERRUPT_NUMBER   ( 16 )
  #define portNVIC_IP_REGISTERS_OFFSET_16   ( 0xE000E3F0 )
  #define portAIRCR_REG           ( * ( ( volatile uint32_t * ) 0xE000ED0C ) )
  #define portMAX_8_BIT_VALUE         ( ( uint8_t ) 0xff )
  #define portTOP_BIT_OF_BYTE         ( ( uint8_t ) 0x80 )
  #define portMAX_PRIGROUP_BITS       ( ( uint8_t ) 7 )
  #define portPRIORITY_GROUP_MASK       ( 0x07UL << 8UL )
  #define portPRIGROUP_SHIFT          ( 8UL )

  static uint8_t ucMaxSysCallPriority = 0;
  static uint32_t ulMaxPRIGROUPValue = 0;
  static const volatile uint8_t * const pcInterruptPriorityRegisters = ( const volatile uint8_t * const ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

BaseType_t xPortStartScheduler(void) {
  /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
  See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
  configASSERT( configMAX_SYSCALL_INTERRUPT_PRIORITY );

#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  #if( configASSERT_DEFINED == 1 )
  {
    volatile uint32_t ulOriginalPriority;
    volatile uint8_t * const pucFirstUserPriorityRegister = ( volatile uint8_t * const ) ( portNVIC_IP_REGISTERS_OFFSET_16 + portFIRST_USER_INTERRUPT_NUMBER );
    volatile uint8_t ucMaxPriorityValue;

    /* Determine the maximum priority from which ISR safe FreeRTOS API
    functions can be called.  ISR safe functions are those that end in
    "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
    ensure interrupt entry is as fast and simple as possible.

    Save the interrupt priority value that is about to be clobbered. */
    ulOriginalPriority = *pucFirstUserPriorityRegister;

    /* Determine the number of priority bits available.  First write to all
    possible bits. */
    *pucFirstUserPriorityRegister = portMAX_8_BIT_VALUE;

    /* Read the value back to see how many bits stuck. */
    ucMaxPriorityValue = *pucFirstUserPriorityRegister;

    /* Use the same mask on the maximum system call priority. */
    ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & ucMaxPriorityValue;

    /* Calculate the maximum acceptable priority group value for the number
    of bits read back. */
    ulMaxPRIGROUPValue = portMAX_PRIGROUP_BITS;
    while( ( ucMaxPriorityValue & portTOP_BIT_OF_BYTE ) == portTOP_BIT_OF_BYTE )
    {
      ulMaxPRIGROUPValue--;
      ucMaxPriorityValue <<= ( uint8_t ) 0x01;
    }

    /* Shift the priority group value back to its position within the AIRCR
    register. */
    ulMaxPRIGROUPValue <<= portPRIGROUP_SHIFT;
    ulMaxPRIGROUPValue &= portPRIORITY_GROUP_MASK;

    /* Restore the clobbered interrupt priority register to its original
    value. */
    *pucFirstUserPriorityRegister = ulOriginalPriority;
  }
  #endif /* conifgASSERT_DEFINED */
#endif /* configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) */ /* ARM M4(F)/M7 core */

#if configCPU_FAMILY==configCPU_FAMILY_ARM_M7F
  /* Constants used to detect a Cortex-M7 r0p1 core, which should use the ARM_CM7 r0p1 port. */
  #define portCPUID (*((volatile uint32_t*)0xE000ed00))
  #define portCORTEX_M7_r0p0_ID (0x410FC270UL)
  #define portCORTEX_M7_r0p1_ID (0x410FC271UL) /* this one will require a special port! Writing to the BASEPRIO is not taking effect immediately, even with memory barrier instructions. Workaround: globally disable interrupts before writing to BASEPRIO, then write, then use memory barrier. */
  #define portCORTEX_M7_r0p2_ID (0x410FC272UL) /* is present on the TWR-KV57F220M */

  configASSERT(portCPUID!=portCORTEX_M7_r0p1_ID); /* this one will require a special port! */
#endif

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
#if configENABLE_FPU /* has floating point unit */
  vPortEnableVFP(); /* Ensure the VFP is enabled - it should be anyway */
  *(portFPCCR) |= portASPEN_AND_LSPEN_BITS; /* Lazy register save always */
#endif
#if INCLUDE_vTaskEndScheduler
    if(setjmp(xJumpBuf) != 0 ) {
      /* here we will get in case of a call to vTaskEndScheduler() */
    #if 0 /* not needed any more with GCC12? On RP2040 and GCC12 this is not needed and harmful. */
      __asm volatile(
        " movs r0, #0         \n" /* Reset CONTROL register and switch back to the MSP stack. */
        " msr CONTROL, r0     \n"
        " dsb                 \n"
        " isb                 \n"
      );
      #endif
      return pdFALSE;
    }
#endif
  vPortStartFirstTask(); /* Start the first task. */
  /* Should not get here! */
  return pdFALSE;
}
/*-----------------------------------------------------------*/
void vPortEndScheduler(void) {
  vPortStopTickTimer();
  vPortInitializeHeap();
  uxCriticalNesting = 0xaaaaaaaa;
  /* Jump back to the processor state prior to starting the
     scheduler.  This means we are not going to be using a
     task stack frame so the task can be deleted. */
#if INCLUDE_vTaskEndScheduler
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
  portDISABLE_INTERRUPTS();
  portPOST_ENABLE_DISABLE_INTERRUPTS();
  uxCriticalNesting++;
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  /* This is not the interrupt safe version of the enter critical function so
  assert() if it is being called from an interrupt context.  Only API
  functions that end in "FromISR" can be used in an interrupt.  Only assert if
  the critical nesting count is 1 to protect against recursive calls if the
  assert function also uses a critical section. */
  if( uxCriticalNesting == 1 )
  {
    /* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
    #define portVECTACTIVE_MASK         (0xFFUL)

    configASSERT(((*portNVIC_INT_CTRL) & portVECTACTIVE_MASK)==0);
  }
#endif
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
    uint32_t uxGetTickCounterValue(void) {
  long val;
  
  GET_TICK_CURRENT_VAL(&val);
  return val;
}
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
#if configSYSTICK_USE_LOW_POWER_TIMER
void LPTMR0_IRQHandler(void) { /* low power timer */
#else
void SysTick_Handler(void) { /* normal SysTick */
#endif
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
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configCPU_FAMILY==configCPU_FAMILY_ARM_M0P
  SEGGER_SYSVIEW_TickCnt++; /* tick counter for Segger SystemViewer */
#endif
#if configUSE_TICKLESS_IDLE == 1
  TICK_INTERRUPT_FLAG_SET();
#endif
  portDISABLE_INTERRUPTS();   /* disable interrupts */
#if (configUSE_TICKLESS_IDLE == 1) && configSYSTICK_USE_LOW_POWER_TIMER
  if (restoreTickInterval > 0) { /* we got interrupted during tickless mode and non-standard compare value: reload normal compare value */
    if (restoreTickInterval == 1) {
      DISABLE_TICK_COUNTER();
      SET_TICK_DURATION(UL_TIMER_COUNTS_FOR_ONE_TICK-1UL);
      ENABLE_TICK_COUNTER();
    }
    restoreTickInterval -= 1;
  }
#endif
  if (xTaskIncrementTick()!=pdFALSE) { /* increment tick count */
    taskYIELD();
  }
  portENABLE_INTERRUPTS(); /* enable interrupts again */
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
void isr_systick(void) {
#elif !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
#if configSYSTICK_USE_LOW_POWER_TIMER
void LPTMR0_IRQHandler(void) { /* low power timer */
#else
void SysTick_Handler(void) { /* normal SysTick */
#endif
#else
void vPortTickHandler(void) {
#endif
  ACKNOWLEDGE_TICK_ISR();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configCPU_FAMILY==configCPU_FAMILY_ARM_M0P
  SEGGER_SYSVIEW_TickCnt++; /* tick counter for Segger SystemViewer */
#endif
#if configUSE_TICKLESS_IDLE == 1
  TICK_INTERRUPT_FLAG_SET();
#endif
  /* The SysTick runs at the lowest interrupt priority, so when this interrupt
    executes all interrupts must be unmasked.  There is therefore no need to
    save and then restore the interrupt mask value as its value is already
    known. */
  portDISABLE_INTERRUPTS();   /* disable interrupts */
  traceISR_ENTER();
#if (configUSE_TICKLESS_IDLE == 1) && configSYSTICK_USE_LOW_POWER_TIMER
  if (restoreTickInterval > 0) { /* we got interrupted during tickless mode and non-standard compare value: reload normal compare value */
    if (restoreTickInterval == 1) {
      DISABLE_TICK_COUNTER();
      SET_TICK_DURATION(UL_TIMER_COUNTS_FOR_ONE_TICK-1UL);
      ENABLE_TICK_COUNTER();
    }
    restoreTickInterval -= 1;
  }
#endif
  if (xTaskIncrementTick()!=pdFALSE) { /* increment tick count */
    traceISR_EXIT_TO_SCHEDULER();
    taskYIELD();
  } else {
    traceISR_EXIT();
  }
  portENABLE_INTERRUPTS(); /* re-enable interrupts */
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
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)  || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  /* Use the NVIC offset register to locate the stack. */
#if configRESET_MSP && !INCLUDE_vTaskEndScheduler
  ldr r0, =0xE000ED08
  ldr r0, [r0]
  ldr r0, [r0]
  /* Set the msp back to the start of the stack. */
  msr msp, r0
#endif
  /* Globally enable interrupts. */
  cpsie i
  /* Call SVC to start the first task. */
  svc 0
  nop
  nop
  nop
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Cortex M0+ */
  /* With the latest FreeRTOS, the port for M0+ does not use the SVC instruction
   * and does not need vPortSVCHandler() any more.
   */
  extern pxCurrentTCB;

  PRESERVE8

  /* The MSP stack is not reset as, unlike on M3/4 parts, there is no vector
  table offset register that can be used to locate the initial stack value.
  Not all M0 parts have the application vector table at address 0. */

  ldr r3, =pxCurrentTCB /* Obtain location of pxCurrentTCB. */
  ldr r1, [r3]
  ldr r0, [r1]      /* The first item in pxCurrentTCB is the task top of stack. */
  adds r0, #32      /* Discard everything up to r0. */
  msr psp, r0       /* This is now the new top of stack to use in the task. */
  movs r0, #2       /* Switch to the psp stack. */
  msr CONTROL, r0
  isb
  pop {r0-r5}       /* Pop the registers that are saved automatically. */
  mov lr, r5        /* lr is now in r5. */
  pop {r3}        /* The return address is now in r3. */
  pop {r2}        /* Pop and discard the XPSR. */
  cpsie i         /* The first task has its context and interrupts can be enabled. */
  bx r3         /* Finally, jump to the user defined task code. */

  ALIGN
#endif
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
/* Need the 'noinline', as latest gcc with -O3 tries to inline it, and gives error message: "Error: symbol `pxCurrentTCBConst2' is already defined" */
__attribute__((noinline))
void vPortStartFirstTask(void) {
#if configUSE_TOP_USED_PRIORITY || configLTO_HELPER
  /* only needed for openOCD or Segger FreeRTOS thread awareness. It needs the symbol uxTopUsedPriority present after linking */
  {
    extern const int uxTopUsedPriority;
    __attribute__((__unused__)) volatile uint8_t dummy_value_for_openocd;
    dummy_value_for_openocd = uxTopUsedPriority;
  }
#endif
#if( configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H == 1 && configUSE_TRACE_FACILITY==1)
  /* reference FreeRTOSDebugConfig, otherwise it might get removed by the linker or optimizations */
  {
    extern volatile const uint8_t FreeRTOSDebugConfig[]; /* need to make it volatile, otherwise -O1 might remove it, with issue for LinkServer Thread Awareness */
    if (FreeRTOSDebugConfig[0]==0) { /* just use it, so the linker cannot remove FreeRTOSDebugConfig[] */
      for(;;); /* FreeRTOSDebugConfig[0] should always be non-zero, so this should never happen! */
    }
  }
#endif
#if configHEAP_SCHEME_IDENTIFICATION
  extern const uint8_t freeRTOSMemoryScheme; /* constant for NXP Kernel Awareness to indicate heap scheme */
  if (freeRTOSMemoryScheme>100) { /* reference/use variable so it does not get optimized by the linker */
    for(;;);
  }
#endif
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)  || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  __asm volatile (
#if configRESET_MSP && !INCLUDE_vTaskEndScheduler
#if configLTO_HELPER /* with -flto, we cannot load the constant directly, otherwise we get "Error: offset out of range" with "lto-wrapper failed" */
    " mov r0, #0xE0000000  \n" /* build the constant 0xE000ED08. First load the upper 16 bits */
    " mov r1, #0xED00      \n" /* next load part of the lower 16 bit */
    " orr r0, r1           \n" /* and or it into R0. Now we have 0xE000ED00 in R0 */
    " mov r1, #0x08        \n" /* next load the lowest 8 bit */
    " orr r0, r1           \n" /* and or it into R0. Now we have 0xE000ED08 in R0 */
#else
    " ldr r0, =0xE000ED08 \n" /* Use the NVIC offset register to locate the stack. */
#endif
    " ldr r0, [r0]        \n" /* load address of vector table */
    " ldr r0, [r0]        \n" /* load first entry of vector table which is the reset stack pointer */
    " msr msp, r0         \n" /* Set the msp back to the start of the stack. */
#endif
    " cpsie i             \n" /* Globally enable interrupts. */
    " svc 0               \n" /* System call to start first task. */
    " nop                 \n"
  );
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Cortex M0+ */
  /* With the latest FreeRTOS, the port for M0+ does not use the SVC instruction
   * and does not need vPortSVCHandler() any more.
   */
  /* The MSP stack is not reset as, unlike on M3/4 parts, there is no vector
  table offset register that can be used to locate the initial stack value.
  Not all M0 parts have the application vector table at address 0. */
  __asm volatile(
    " ldr r2, pxCurrentTCBConst2  \n" /* Obtain location of pxCurrentTCB. */
    " ldr r3, [r2]        \n"
    " ldr r0, [r3]        \n" /* The first item in pxCurrentTCB is the task top of stack. */
    " add r0, #32         \n" /* Discard everything up to r0. */
    " msr psp, r0         \n" /* This is now the new top of stack to use in the task. */
    " movs r0, #2         \n" /* Switch to the psp stack. */
    " msr CONTROL, r0     \n"
    " isb                 \n"
    " pop {r0-r5}         \n" /* Pop the registers that are saved automatically. */
    " mov lr, r5          \n" /* lr is now in r5. */
    " pop {r3}            \n" /* Return address is now in r3. */
    " pop {r2}            \n" /* Pop and discard XPSR. */
    " cpsie i             \n" /* The first task has its context and interrupts can be enabled. */
    " bx r3               \n" /* Finally, jump to the user defined task code. */
    "                     \n"
    " .align 4            \n"
    "pxCurrentTCBConst2: .word pxCurrentTCB"
          );
#endif
}
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)  || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
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
#if configENABLE_FPU
  ldmia r0!, {r4-r11, r14} /* r14, check http://sourceforge.net/p/freertos/discussion/382005/thread/a9406af1/?limit=25#3bc7 */
#else
  ldmia r0!, {r4-r11}
#endif
  msr psp, r0
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r0
#if configENABLE_FPU
#else
  orr r14, r14, #13
#endif
  bx r14
}
/*-----------------------------------------------------------*/
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Cortex M0+ and Keil */
#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
__asm void SVC_Handler(void) {
#else
__asm void vPortSVCHandler(void) {
#endif
  /* This function is no longer used, but retained for backward
  compatibility. */
}
#endif
#endif
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
__attribute__((naked)) void isr_svcall(void) {
#elif !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
__attribute__ ((naked)) void SVC_Handler(void) {
#else
__attribute__ ((naked)) void vPortSVCHandler(void) {
#endif
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
__asm volatile (
    " ldr r3, pxCurrentTCBConst2 \n" /* Restore the context. */
    " ldr r1, [r3]               \n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    " ldr r0, [r1]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    /* pop the core registers */
#if configENABLE_FPU
    " ldmia r0!, {r4-r11, r14}   \n"
#else
    " ldmia r0!, {r4-r11}        \n"
#endif
    " msr psp, r0                \n"
    " mov r0, #0                 \n"
    " msr basepri, r0            \n"
#if configENABLE_FPU
#else
    " orr r14, r14, #13          \n"
#endif
    " bx r14                     \n"
    "                            \n"
    " .align 2                   \n"
    "pxCurrentTCBConst2: .word pxCurrentTCB \n"
  );
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Cortex M0+ */
  /* This function is no longer used, but retained for backward
   compatibility. */
#endif
}
#endif /* (configCOMPILER==configCOMPILER_ARM_GCC) */
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_KEIL)
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
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
#if configENABLE_FPU
  tst r14, #0x10             /* Is the task using the FPU context?  If so, push high vfp registers. */
  it eq
  vstmdbeq r0!, {s16-s31}

  stmdb r0!, {r4-r11, r14}   /* save remaining core registers */
#else
  stmdb r0!, {r4-r11}        /* Save the core registers. */
#endif
  str r0, [r2]               /* Save the new top of stack into the first member of the TCB. */
  stmdb sp!, {r3, r14}
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r0
  bl vTaskSwitchContext
  mov r0, #0
  msr basepri, r0
  ldmia sp!, {r3, r14}
  ldr r1, [r3]               /* The first item in pxCurrentTCB is the task top of stack. */
  ldr r0, [r1]
#if configENABLE_FPU
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
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Keil: Cortex M0+ */
#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
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
#endif /* (configCOMPILER==configCOMPILER_ARM_KEIL) */
/*-----------------------------------------------------------*/
#if (configCOMPILER==configCOMPILER_ARM_GCC)
#if configGDB_HELPER
/* prototypes to avoid compiler warnings */
__attribute__ ((naked, used)) void vPortPendSVHandler_native(void);
__attribute__ ((naked, used)) void PendSV_Handler_jumper(void);

__attribute__ ((naked, used)) void vPortPendSVHandler_native(void) {
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
__attribute__((naked, used)) void isr_pendsv(void) {
#elif !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
__attribute__ ((naked, used)) void PendSV_Handler(void) {
#else
__attribute__ ((naked, used)) void vPortPendSVHandler(void) {
#endif
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  __asm volatile (
    " mrs r0, psp                \n"
    " ldr  r3, pxCurrentTCBConst \n" /* Get the location of the current TCB. */
    " ldr  r2, [r3]              \n"
#if configENABLE_FPU
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
#if configENABLE_FPU
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
    " ldr r2, [r3]               \n"
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

#if configGDB_HELPER /* if GDB debug helper is enabled */
/* Credits to:
 * - Artem Pisarneko for his initial contribution
 * - Prasana for the PendSVHandler updates
 * - Geoffrey Wossum for the Cortex-M4 contribution
 */

/* Switch control variable:
 * 0 - no hook installed (normal execution),
 * 1 - hook installation performed,
 * 2 - following hooked switches
 */
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
int volatile dbgPendSVHookState = 0;
/* Requested target task handle variable */
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
void *volatile dbgPendingTaskHandle;

#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
const int volatile dbgFreeRTOSConfig_suspend_value = INCLUDE_vTaskSuspend;
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
const int volatile dbgFreeRTOSConfig_delete_value = INCLUDE_vTaskDelete;

__attribute__ ((naked, used)) void PendSV_Handler_jumper(void) {
  __asm volatile("b vPortPendSVHandler_native \n");
}

#if !McuLib_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
__attribute__ ((naked)) void PendSV_Handler(void) {
#else
__attribute__ ((naked)) void vPortPendSVHandler(void) {
#endif
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */
  __asm volatile (
#if configGDB_HELPER
    " ldr r1, _dbgPendSVHookState    \n" /* Check hook installed */
    " ldr r0, [r1]                   \n"
    " cmp r0, #0                     \n"
    " beq PendSV_Handler_jumper      \n" /* if no hook installed then jump to native handler, else proceed... */
    " cmp r0, #1                     \n" /* check whether hook triggered for the first time...  */
    " bne dbg_switch_to_pending_task \n" /* if not so, then jump to switching right now, otherwise current task context must be saved first...  */
    " mov r0, #2                     \n" /* mark hook after triggered for the first time */
    " str r0, [r1]                   \n"
#endif /* configGDB_HELPER */
    " mrs r0, psp                \n"
    " ldr  r3, pxCurrentTCBConstG \n" /* Get the location of the current TCB. */
    " ldr  r2, [r3]              \n"
#if configENABLE_FPU
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
#if configGDB_HELPER
    "dbg_switch_to_pending_task:     \n"
    " ldr r3, _dbgPendingTaskHandle  \n" /* --> Load task handle going to switch to <-- */
#endif /* configGDB_HELPER */
    " ldr r1, [r3]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    " ldr r0, [r1]               \n"
#if configENABLE_FPU
    " ldmia r0!, {r4-r11, r14}   \n" /* Pop the core registers */
    " tst r14, #0x10             \n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
    " it eq                      \n"
    " vldmiaeq r0!, {s16-s31}    \n"
#else
    " ldmia r0!, {r4-r11}        \n" /* Pop the core registers. */
#endif
    " msr psp, r0                \n"
#if configGDB_HELPER
    " bkpt                       \n" /* <-- here debugger stops and steps out to target task context */
#endif /* configGDB_HELPER */
    " bx r14                     \n"
    "                            \n"
    " .align 2                   \n"
    "pxCurrentTCBConstG: .word pxCurrentTCB  \n"
#if configGDB_HELPER
    "_dbgPendSVHookState: .word dbgPendSVHookState     \n"
    "_dbgPendingTaskHandle: .word dbgPendingTaskHandle \n"
    ".word dbgFreeRTOSConfig_suspend_value             \n" /* force keep these symbols from cutting away by linker garbage collector */
    ".word dbgFreeRTOSConfig_delete_value              \n"
#endif
      ::"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY)
  );
#else /* Cortex M0+ */
  __asm volatile (
    " mrs r0, psp                \n"
    "                            \n"
    " ldr r3, pxCurrentTCBConstG  \n" /* Get the location of the current TCB. */
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
    "pxCurrentTCBConstG: .word pxCurrentTCB"
  );
#endif
}

#endif /* configGDB_HELPER */

#endif /* (configCOMPILER==configCOMPILER_ARM_GCC) */
/*-----------------------------------------------------------*/
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* ARM M4(F)/M7/M33 core */

#if configCOMPILER==configCOMPILER_ARM_KEIL
__asm uint32_t vPortGetIPSR(void) {
  PRESERVE8

  mrs r0, ipsr
  bx r14
}
#endif

#if( configASSERT_DEFINED == 1 )
  void vPortValidateInterruptPriority( void )
  {
  uint32_t ulCurrentInterrupt;
  uint8_t ucCurrentPriority;

    /* Obtain the number of the currently executing interrupt. */
  #if configCOMPILER==configCOMPILER_ARM_KEIL
    ulCurrentInterrupt = vPortGetIPSR();
  #else
    __asm volatile( "mrs %0, ipsr" : "=r"( ulCurrentInterrupt ) );
  #endif

    /* Is the interrupt number a user defined interrupt? */
    if( ulCurrentInterrupt >= portFIRST_USER_INTERRUPT_NUMBER )
    {
      /* Look up the interrupt's priority. */
      ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];

      /* The following assertion will fail if a service routine (ISR) for
      an interrupt that has been assigned a priority above
      configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
      function.  ISR safe FreeRTOS API functions must *only* be called
      from interrupts that have been assigned a priority at or below
      configMAX_SYSCALL_INTERRUPT_PRIORITY.

      Numerically low interrupt priority numbers represent logically high
      interrupt priorities, therefore the priority of the interrupt must
      be set to a value equal to or numerically *higher* than
      configMAX_SYSCALL_INTERRUPT_PRIORITY.

      Interrupts that use the FreeRTOS API must not be left at their
      default priority of zero as that is the highest possible priority,
      which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
      and therefore also guaranteed to be invalid.

      FreeRTOS maintains separate thread and ISR API functions to ensure
      interrupt entry is as fast and simple as possible.

      The following links provide detailed information:
      http://www.freertos.org/RTOS-Cortex-M3-M4.html
      http://www.freertos.org/FAQHelp.html */
      configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
    }

    /* Priority grouping:  The interrupt controller (NVIC) allows the bits
    that define each interrupt's priority to be split between bits that
    define the interrupt's pre-emption priority bits and bits that define
    the interrupt's sub-priority.  For simplicity all bits must be defined
    to be pre-emption priority bits.  The following assertion will fail if
    this is not the case (if some bits represent a sub-priority).

    If the application only uses CMSIS libraries for interrupt
    configuration then the correct setting can be achieved on all Cortex-M
    devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
    scheduler.  Note however that some vendor specific peripheral libraries
    assume a non-zero priority group setting, in which cases using a value
    of zero will result in unpredicable behaviour. */
    configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
  }

#endif /* configASSERT_DEFINED */

#endif /* ARM M4(F) core */ 

#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */

