/*
 * FreeRTOS Kernel V11.0.0
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


#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOSConfig.h"
#include "projdefs.h" /* for pdFALSE, pdTRUE */

void vPortStopTickTimer(void);
/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */
#ifdef __GNUC__ /* << EST: 'used' attribute need for LTO (Link Time Optimization) */
  #define portDONT_DISCARD      __attribute__( ( used ) )
#else
  #define portDONT_DISCARD      /* nothing */
#endif

#ifndef configENABLE_FPU
    #error configENABLE_FPU must be defined in FreeRTOSConfig.h.  Set configENABLE_FPU to 1 to enable the FPU or 0 to disable the FPU.
#endif /* configENABLE_FPU */

#ifndef configENABLE_MPU
    #error configENABLE_MPU must be defined in FreeRTOSConfig.h.  Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#endif /* configENABLE_MPU */

#ifndef configENABLE_TRUSTZONE
    #error configENABLE_TRUSTZONE must be defined in FreeRTOSConfig.h.  Set configENABLE_TRUSTZONE to 1 to enable TrustZone or 0 to disable TrustZone.
#endif /* configENABLE_TRUSTZONE */

#if (configCOMPILER==configCOMPILER_S12_FSL) || (configCOMPILER==configCOMPILER_S08_FSL)
  /* disabling some warnings as the RTOS sources are not that clean... */
  #pragma MESSAGE DISABLE C5909 /* assignment in condition */
  #pragma MESSAGE DISABLE C2705 /* possible loss of data */
  #pragma MESSAGE DISABLE C5905 /* multiplication with one */
  #pragma MESSAGE DISABLE C5904 /* division by one */
  #pragma MESSAGE DISABLE C5660 /* removed dead code */
  #pragma MESSAGE DISABLE C5917 /* removed dead assignment */
  #pragma MESSAGE DISABLE C4001 /* condition always FALSE */
#endif
#if configCOMPILER==configCOMPILER_S12_FSL
  #pragma MESSAGE DISABLE C12053 /* SP change not in debug information */
  #pragma MESSAGE DISABLE C12056 /* SP debug information incorrect */
#endif

/* Type definitions. */
#define portCHAR               char
#define portFLOAT              float
#define portDOUBLE             double
#define portLONG               long
#define portSHORT              short
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY) || (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portSTACK_TYPE       unsigned long
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portSTACK_TYPE       unsigned char
#endif
typedef portSTACK_TYPE StackType_t;

#define portUSE_CUSTOM_BASE_TYPE  0  /* 1: use custom base type */

#if portUSE_CUSTOM_BASE_TYPE
  #define portBASE_TYPE          char /* custom port base type */
  typedef portBASE_TYPE BaseType_t;
  typedef unsigned portBASE_TYPE UBaseType_t;
#elif (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY) || (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portBASE_TYPE        long
  typedef long BaseType_t;
  typedef unsigned long UBaseType_t;
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portBASE_TYPE        char
  typedef signed char BaseType_t;
  typedef unsigned char UBaseType_t;
#endif

#if( configUSE_16_BIT_TICKS == 1 )
  typedef uint16_t TickType_t;
  #define portMAX_DELAY      (TickType_t)0xffff
#else
  typedef uint32_t TickType_t;
  #define portMAX_DELAY      (TickType_t)0xffffffff

#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
  not need to be guarded with a critical section. */
  #define portTICK_TYPE_IS_ATOMIC 1
#endif /* 32bit architecture */

#endif

#if( configENABLE_TRUSTZONE == 1 )
    extern void vPortAllocateSecureContext( uint32_t ulSecureStackSize );
    extern void vPortFreeSecureContext( uint32_t *pulTCB ) /* PRIVILEGED_FUNCTION */;
#endif /* configENABLE_TRUSTZONE */

#if( configENABLE_MPU == 1 )
    extern BaseType_t xIsPrivileged( void ) /* __attribute__ (( naked )) */;
    extern void vResetPrivilege( void ) /* __attribute__ (( naked )) */;
#endif /* configENABLE_MPU */

/**
 * @brief MPU specific constants.
 */
#if( configENABLE_MPU == 1 )
    #define portUSING_MPU_WRAPPERS              1
    #define portPRIVILEGE_BIT                   ( 0x80000000UL )
#else
    #define portPRIVILEGE_BIT                   ( 0x0UL )
#endif /* configENABLE_MPU */

#if configENABLE_MPU
/*-----------------------------------------------------------*/
/* MPU specific constants. */

#define portMPU_REGION_READ_WRITE				( 0x03UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY		( 0x05UL << 24UL )
#define portMPU_REGION_READ_ONLY				( 0x06UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE	( 0x01UL << 24UL )
#define portMPU_REGION_CACHEABLE_BUFFERABLE		( 0x07UL << 16UL )
#define portMPU_REGION_EXECUTE_NEVER			( 0x01UL << 28UL )

#define portUNPRIVILEGED_FLASH_REGION		( 0UL )
#define portPRIVILEGED_FLASH_REGION			( 1UL )
#define portPRIVILEGED_RAM_REGION			( 2UL )
#define portGENERAL_PERIPHERALS_REGION		( 3UL )
#define portSTACK_REGION					( 4UL )
#define portFIRST_CONFIGURABLE_REGION	    ( 5UL )
#define portLAST_CONFIGURABLE_REGION		( 7UL )
#define portNUM_CONFIGURABLE_REGIONS		( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define portTOTAL_NUM_REGIONS				( portNUM_CONFIGURABLE_REGIONS + 1 ) /* Plus one to make space for the stack region. */

#define portSWITCH_TO_USER_MODE() __asm volatile ( " mrs r0, control \n orr r0, #1 \n msr control, r0 " :::"r0" )

typedef struct MPU_REGION_REGISTERS
{
	uint32_t ulRegionBaseAddress;
	uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

/* Plus 1 to create space for the stack region. */
typedef struct MPU_SETTINGS
{
	xMPU_REGION_REGISTERS xRegion[ portTOTAL_NUM_REGIONS ];
} xMPU_SETTINGS;
#endif /* configENABLE_MPU */

#if configENABLE_MPU /* check values for LPC55xx! */
/* Devices Region. */
#define portDEVICE_REGION_START_ADDRESS                     ( 0x50000000 )
#define portDEVICE_REGION_END_ADDRESS                       ( 0x5FFFFFFF )

/* Device memory attributes used in MPU_MAIR registers.
 *
 * 8-bit values encoded as follows:
 *  Bit[7:4] - 0000 - Device Memory
 *  Bit[3:2] - 00 --> Device-nGnRnE
 *              01 --> Device-nGnRE
 *              10 --> Device-nGRE
 *              11 --> Device-GRE
 *  Bit[1:0] - 00, Reserved.
 */
#define portMPU_DEVICE_MEMORY_nGnRnE                        ( 0x00 ) /* 0000 0000 */
#define portMPU_DEVICE_MEMORY_nGnRE                         ( 0x04 ) /* 0000 0100 */
#define portMPU_DEVICE_MEMORY_nGRE                          ( 0x08 ) /* 0000 1000 */
#define portMPU_DEVICE_MEMORY_GRE                           ( 0x0C ) /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#define portMPU_NORMAL_MEMORY_NON_CACHEABLE                 ( 0x44 ) /* Non-cacheable. */
#define portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE          ( 0xFF ) /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#define portMPU_REGION_NON_SHAREABLE                        ( 0UL << 3UL )
#define portMPU_REGION_INNER_SHAREABLE                      ( 1UL << 3UL )
#define portMPU_REGION_OUTER_SHAREABLE                      ( 2UL << 3UL )

#define portMPU_REGION_PRIVILEGED_READ_WRITE                ( 0UL << 1UL )
#define portMPU_REGION_READ_WRITE                           ( 1UL << 1UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY                 ( 2UL << 1UL )
#define portMPU_REGION_READ_ONLY                            ( 3UL << 1UL )

#define portMPU_REGION_EXECUTE_NEVER                        ( 1UL )

/*-----------------------------------------------------------*/

/**
 * @brief Settings to define an MPU region.
 */
typedef struct MPURegionSettings
{
    uint32_t ulRBAR;    /**< RBAR for the region. */
    uint32_t ulRLAR;    /**< RLAR for the region. */
} MPURegionSettings_t;

/**
 * @brief MPU settings as stored in the TCB.
 */
typedef struct MPU_SETTINGS
{
    uint32_t ulMAIR0;   /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
    MPURegionSettings_t xRegionsSettings[ portTOTAL_NUM_REGIONS ]; /**< Settings for 4 per task regions. */
} xMPU_SETTINGS;

/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#define portSVC_ALLOCATE_SECURE_CONTEXT                     0
#define portSVC_FREE_SECURE_CONTEXT                         1
#define portSVC_START_SCHEDULER                             2
#define portSVC_RAISE_PRIVILEGE                             3
/*-----------------------------------------------------------*/

#endif /* configENABLE_MPU */

/*-----------------------------------------------------------*/
/* Hardware specifics. */
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2)
  #define portBYTE_ALIGNMENT     4
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  #define portBYTE_ALIGNMENT     8
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portBYTE_ALIGNMENT     1
  #define portSTACK_GROWTH       -1 /* stack grows from HIGH to LOW */
#elif (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portBYTE_ALIGNMENT     4
  #define portSTACK_GROWTH       1 /* stack grows from LOW to HIGH */
#endif

#define portTICK_PERIOD_MS      ((TickType_t)1000/configTICK_RATE_HZ)
/*-----------------------------------------------------------*/
/* Critical section management. */
unsigned long ulPortSetIPL(unsigned portLONG);

/* If set to 1, then this port uses the critical nesting count from the TCB rather than
maintaining a separate value and then saving this value in the task stack. */
#define portCRITICAL_NESTING_IN_TCB    0


extern unsigned portBASE_TYPE uxPortSetInterruptMaskFromISR(void);
extern void vPortClearInterruptMaskFromISR(unsigned portBASE_TYPE);


#if configCOMPILER==configCOMPILER_DSC_FSL
  /* for DSC, there is a possible skew after enable/disable Interrupts. */
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() \
  	asm(nop); asm(nop); asm(nop); asm(nop); asm(nop); asm(nop);
#else
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() /* nothing special needed */
#endif

#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) /* Cortex M4/M7/M33 */
  #if (configCOMPILER==configCOMPILER_ARM_KEIL)
    __asm uint32_t ulPortSetInterruptMask(void);
    __asm void vPortClearInterruptMask(uint32_t ulNewMask);

    #define portSET_INTERRUPT_MASK()            ulPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK()          vPortClearInterruptMask(0)
  #elif (configCOMPILER==configCOMPILER_ARM_GCC)
    /*
     * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without affecting other
     * registers.  r0 is clobbered.
     */
    #define portSET_INTERRUPT_MASK()  \
      __asm volatile               \
      (                            \
        "  mov r0, %0 \n"         \
        "  msr basepri, r0 \n"     \
        : /* no output operands */ \
        :"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY) /* input */\
        :"r0" /* clobber */    \
      )
    /*
     * Set basepri back to 0 without affecting other registers.
     * r0 is clobbered.
     */
    #define portCLEAR_INTERRUPT_MASK() \
      __asm volatile             \
      (                          \
         "  mov r0, #0      \n"  \
         "  msr basepri, r0 \n"  \
         : /* no output */       \
         : /* no input */        \
         :"r0" /* clobber */     \
      )
  #elif (configCOMPILER==configCOMPILER_ARM_IAR) /* IAR */ || (configCOMPILER==configCOMPILER_ARM_FSL) /* legacy FSL ARM Compiler */
    void vPortSetInterruptMask(void); /* prototype, implemented in portasm.s */
    void vPortClearInterruptMask(void); /* prototype, implemented in portasm.s */
    #define portSET_INTERRUPT_MASK()    vPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK()  vPortClearInterruptMask()
  #else
    #error "unknown compiler?"
  #endif
#elif configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY) /* Cortex-M0+ */
  #if configCOMPILER==configCOMPILER_ARM_KEIL
    #define portSET_INTERRUPT_MASK()              __disable_irq()
    #define portCLEAR_INTERRUPT_MASK()            __enable_irq()
  #else /* IAR, CW ARM or GNU ARM gcc */
    #define portSET_INTERRUPT_MASK()              __asm volatile("cpsid i")
    #define portCLEAR_INTERRUPT_MASK()            __asm volatile("cpsie i")
  #endif
#endif

/* Critical section management. */
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#define portSET_INTERRUPT_MASK_FROM_ISR()     0;portSET_INTERRUPT_MASK()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)  portCLEAR_INTERRUPT_MASK();(void)x
#define portDISABLE_INTERRUPTS()              portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()               portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()                  vPortEnterCritical()
#define portEXIT_CRITICAL()                   vPortExitCritical()
#if configCOMPILER==configCOMPILER_ARM_KEIL
  #define portDISABLE_ALL_INTERRUPTS()   __disable_irq()
  #define portENABLE_ALL_INTERRUPTS()    __enable_irq()
#else /* IAR, CW ARM or GNU ARM gcc */
  #define portDISABLE_ALL_INTERRUPTS()   __asm volatile("cpsid i")
  #define portENABLE_ALL_INTERRUPTS()    __asm volatile("cpsie i")
#endif

/* There are an uneven number of items on the initial stack, so
portALIGNMENT_ASSERT_pxCurrentTCB() will trigger false positive asserts. */
#define portALIGNMENT_ASSERT_pxCurrentTCB (void)

#if( configENABLE_TRUSTZONE == 1 )
    /**
     * @brief Allocate a secure context for the task.
     *
     * Tasks are not created with a secure context. Any task that is going to call
     * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
     * secure context before it calls any secure function.
     *
     * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
     */
    #define portALLOCATE_SECURE_CONTEXT( ulSecureStackSize )    vPortAllocateSecureContext( ulSecureStackSize )

    /**
     * @brief Called when a task is deleted to delete the task's secure context,
     * if it has one.
     *
     * @param[in] pxTCB The TCB of the task being deleted.
     */
    #define portCLEAN_UP_TCB( pxTCB )                           vPortFreeSecureContext( ( uint32_t * ) pxTCB )
#else
    #define portALLOCATE_SECURE_CONTEXT( ulSecureStackSize )
    #define portCLEAN_UP_TCB( pxTCB )
#endif /* configENABLE_TRUSTZONE */

/*-----------------------------------------------------------*/

#if( configENABLE_MPU == 1 )
    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #define portIS_PRIVILEGED()                                 xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #define portRAISE_PRIVILEGE()                               __asm volatile ( "svc %0 \n" :: "i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #define portRESET_PRIVILEGE()                               vResetPrivilege()
#else
    #define portIS_PRIVILEGED()
    #define portRAISE_PRIVILEGE()
    #define portRESET_PRIVILEGE()
#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/
/* Scheduler utilities. */

extern void vPortYieldFromISR(void);
#define portYIELD()                             vPortYieldFromISR()
#define portEND_SWITCHING_ISR(xSwitchRequired) { if( xSwitchRequired != pdFALSE ) { traceISR_EXIT_TO_SCHEDULER(); portYIELD(); } else { traceISR_EXIT(); } }
#define portYIELD_FROM_ISR(x)                   portEND_SWITCHING_ISR(x)
/*-----------------------------------------------------------*/

/* Architecture specific optimizations. */
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)
  #if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
	/* Generic helper function. */
    #if (configCOMPILER==configCOMPILER_ARM_GCC)
      __attribute__((always_inline)) static inline unsigned char ucPortCountLeadingZeros(unsigned long ulBitmap)
	  {
	    uint8_t ucReturn;

	    __asm volatile ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );
	    return ucReturn;
	  }
    #endif
	/* Check the configuration. */
	#if( configMAX_PRIORITIES > 32 )
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif

	/* Store/clear the ready priorities in a bit map. */
	#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
	#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

	/*-----------------------------------------------------------*/
  #if (configCOMPILER==configCOMPILER_ARM_GCC)
    #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) ucPortCountLeadingZeros( ( uxReadyPriorities ) ) )
  #elif (configCOMPILER==configCOMPILER_ARM_KEIL)
    #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )
  #elif (configCOMPILER==configCOMPILER_ARM_IAR)
    #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( ( uint32_t ) __CLZ( ( uxReadyPriorities ) ) ) )
  #endif

  #endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
#endif /* configCPU_FAMILY_IS_ARM_M4_M7 */
/*-----------------------------------------------------------*/

#ifdef configASSERT
#if configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY) /* ARM M4/M7(F) core */
  void vPortValidateInterruptPriority( void );
  #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID() 	vPortValidateInterruptPriority()
#else
  #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()
#endif
#endif

/*-----------------------------------------------------------*/
/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
  extern void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime);
  #define portSUPPRESS_TICKS_AND_SLEEP(xExpectedIdleTime) vPortSuppressTicksAndSleep(xExpectedIdleTime)
#endif
/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)   void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters)         void vFunction(void *pvParameters)
/*-----------------------------------------------------------*/
void vPortStartFirstTask(void);
  /* starts the first task, called from xPortStartScheduler() */

void vPortYieldHandler(void);
  /* handler for the SWI interrupt */

#if configENABLE_FPU /* has floating point unit */
  void vPortEnableVFP(void);
    /* enables floating point support in the CPU */
#endif

/* Prototypes for interrupt service handlers */
#if !MCUC1_CONFIG_PEX_SDK_USED /* the SDK expects different interrupt handler names */
  void SVC_Handler(void); /* SVC interrupt handler */
  void PendSV_Handler(void); /* PendSV interrupt handler */
  void SysTick_Handler(void); /* Systick interrupt handler */
#else
  void vPortSVCHandler(void); /* SVC interrupt handler */
  void vPortPendSVHandler(void); /* PendSV interrupt handler */
  void vPortTickHandler(void); /* Systick interrupt handler */
#endif

#if (configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY) || configCPU_FAMILY_IS_ARM_M4_M7(configCPU_FAMILY)) && (configCOMPILER==configCOMPILER_ARM_GCC)
  #define portINLINE  __inline

  #ifndef portFORCE_INLINE
    #define portFORCE_INLINE inline __attribute__(( always_inline))
  #endif

  #if configENABLE_MPU
	  /* Set the privilege level to user mode if xRunningPrivileged is false. */
	  portFORCE_INLINE static void vPortResetPrivilege( BaseType_t xRunningPrivileged )
	  {
		if( xRunningPrivileged != pdTRUE )
		{
			__asm volatile ( " mrs r0, control 	\n" \
							 " orr r0, #1 		\n" \
							 " msr control, r0	\n"	\
							 :::"r0" );
		}
	  }
  #endif

	portFORCE_INLINE static BaseType_t xPortIsInsideInterrupt( void )
	{
	  uint32_t ulCurrentInterrupt;
	  BaseType_t xReturn;

	  /* Obtain the number of the currently executing interrupt. */
	  __asm volatile( "mrs %0, ipsr" : "=r"( ulCurrentInterrupt ) );

	  if( ulCurrentInterrupt == 0 )
	  {
		xReturn = pdFALSE;
	  }
	  else
	  {
		xReturn = pdTRUE;
	  }

	  return xReturn;
	}

	/*-----------------------------------------------------------*/

	portFORCE_INLINE static void vPortRaiseBASEPRI( void )
	{
	uint32_t ulNewBASEPRI;

	  __asm volatile
	  (
		" mov %0, %1                        \n" \
		" msr basepri, %0                     \n" \
		" isb                           \n" \
		" dsb                           \n" \
		:"=r" (ulNewBASEPRI) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY )
	  );
	}

	/*-----------------------------------------------------------*/

	portFORCE_INLINE static uint32_t ulPortRaiseBASEPRI( void )
	{
	uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

	  __asm volatile
	  (
		" mrs %0, basepri                     \n" \
		" mov %1, %2                        \n" \
		" msr basepri,                      \n" \
		" isb                           \n" \
		" dsb                           \n" \
		:"=r" (ulOriginalBASEPRI), "=r" (ulNewBASEPRI) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY )
	  );

	  /* This return will not be reached but is necessary to prevent compiler
	  warnings. */
	  return ulOriginalBASEPRI;
	}
	/*-----------------------------------------------------------*/

	portFORCE_INLINE static void vPortSetBASEPRI( uint32_t ulNewMaskValue )
	{
	  __asm volatile
	  (
		" msr basepri, %0 " :: "r" ( ulNewMaskValue )
	  );
	}
	/*-----------------------------------------------------------*/
#endif

/* << EST needed for PICO-W lwIP, IPSR would be available on M4 too */
#define portCHECK_IF_IN_ISR() ({                          \
        uint32_t ulIPSR;                                  \
       __asm volatile ("mrs %0, IPSR" : "=r" (ulIPSR)::); \
       ((uint8_t)ulIPSR)>0;})

#if configUSE_TICKLESS_IDLE_DECISION_HOOK /* << EST */
  BaseType_t configUSE_TICKLESS_IDLE_DECISION_HOOK_NAME(void); /* return pdTRUE if RTOS can enter tickless idle mode, pdFALSE otherwise */
#endif

void prvTaskExitError(void);
  /* handler to catch task exit errors */

#if !configGENERATE_RUN_TIME_STATS_USE_TICKS
  extern void FRTOS1_AppConfigureTimerForRuntimeStats(void);
  extern uint32_t FRTOS1_AppGetRuntimeCounterValueFromISR(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

