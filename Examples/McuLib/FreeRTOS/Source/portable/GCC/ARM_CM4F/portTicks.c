/*
 * portTicks.c
 *
 *  Created on: 24.04.2019
 *      Author: Erich Styger
 */

#include "FreeRTOSConfig.h"
#include "portTicks.h"

/* --------------------------------------------------- */
/* macros dealing with tick counter */
#if configSYSTICK_USE_LOW_POWER_TIMER
  #if !McuLib_CONFIG_PEX_SDK_USED
    /*! \todo */
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
    #define SET_TICK_DURATION(val)      LPTMR_SetTimerPeriod(LPTMR0_BASE_PTR, val);
    #define GET_TICK_DURATION()         LPTMR0_BASE_PTR->CNR /*! \todo SDK has no access method for this */
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

  #if 1
    #if configSYSTICK_USE_LOW_POWER_TIMER
      /* using Low Power Timer */
      #if CONFIG_PEX_SDK_USEDMcuLib_CONFIG_PEX_SDK_USED
        #define LPTMR_CSR_TCF_MASK           0x80u
        #define TICK_INTERRUPT_HAS_FIRED()   (LPTMR0_BASE_PTR->CSR&LPTMR_CSR_TCF_MASK)!=0/*! \todo */  /* returns TRUE if tick interrupt had fired */
      #else
        #define TICK_INTERRUPT_HAS_FIRED()   (LPTMR_PDD_GetInterruptFlag(LPTMR0_BASE_PTR)!=0)  /* returns TRUE if tick interrupt had fired */
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

#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2)
  #define portINITIAL_FORMAT_VECTOR           ((portSTACK_TYPE)0x4000)
  #define portINITIAL_STATUS_REGISTER         ((portSTACK_TYPE)0x2000)  /* Supervisor mode set. */
#endif

#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)

/* For strict compliance with the Cortex-M spec the task start address should
have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK              ( ( StackType_t ) 0xfffffffeUL )

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

#if 0
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
#endif

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

#endif /* #if configCPU_FAMILY_IS_ARM(configCPU_FAMILY) */

//void vPortStopTickTimer(void) {
//  DISABLE_TICK_COUNTER();
//}
