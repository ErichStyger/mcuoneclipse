/*
    FreeRTOS V7.5.0 - Copyright (C) 2013 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.

    >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License
    and the FreeRTOS license exception along with FreeRTOS; if not it can be
    viewed here: http://www.freertos.org/a00114.html and also obtained by
    writing to Real Time Engineers Ltd., contact details for whom are available
    on the FreeRTOS WEB site.

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
    including FreeRTOS+Trace - an indispensable productivity tool, and our new
    fully thread aware and reentrant UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High 
    Integrity Systems, who sell the code with commercial support, 
    indemnification and middleware, under the OpenRTOS brand.
    
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety 
    engineered and independently SIL3 certified version for use in safety and 
    mission critical applications that require provable dependability.
*/
#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOSConfig.h"

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */
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
%if defined(Custom_portBASE_TYPE) & Custom_portBASE_TYPE='yes'
#define portBASE_TYPE          %portBASE_TYPE /* custom type as specified in properties */
%else
#if (configCPU_FAMILY==configCPU_FAMILY_CF1) || (configCPU_FAMILY==configCPU_FAMILY_CF2) || configCPU_FAMILY_IS_ARM(configCPU_FAMILY) || (configCPU_FAMILY==configCPU_FAMILY_DSC)
  #define portBASE_TYPE        long
#elif (configCPU_FAMILY==configCPU_FAMILY_S08) || (configCPU_FAMILY==configCPU_FAMILY_S12)
  #define portBASE_TYPE        char
#endif
%endif

#if( configUSE_16_BIT_TICKS == 1 )
  typedef unsigned portSHORT portTickType;
  #define portMAX_DELAY      (portTickType)0xffff
#else
  typedef unsigned portLONG portTickType;
  #define portMAX_DELAY      (portTickType)0xffffffff
#endif
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF") | (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
%- not for Kinetis, as causing problems with include order :-(

#include "%ProcessorModule.h"
%endif
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

#define portTICK_RATE_MS       ((portTickType)1000/configTICK_RATE_HZ)
/*-----------------------------------------------------------*/
/* Critical section management. */
unsigned portLONG ulPortSetIPL(unsigned portLONG);

/* If set to 1, then this port uses the critical nesting count from the TCB rather than
maintaining a separate value and then saving this value in the task stack. */
#define portCRITICAL_NESTING_IN_TCB    0

%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
extern unsigned portLONG uxCriticalNesting;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
extern volatile unsigned portBASE_TYPE uxCriticalNesting;
%elif (CPUfamily = "Kinetis")
%elif (CPUfamily = "56800")
%else
  #error "undefined target %CPUfamily!"
%endif

extern unsigned portBASE_TYPE uxPortSetInterruptMaskFromISR(void);
extern void vPortClearInterruptMaskFromISR(unsigned portBASE_TYPE);

%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
#define portSET_INTERRUPT_MASK_FROM_ISR() \
  ulPortSetIPL(configMAX_SYSCALL_INTERRUPT_PRIORITY)
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedStatusRegister) \
  (void)ulPortSetIPL(uxSavedStatusRegister)
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
/* Interrupts are always disabled in the ISR, thus nothing to do here to prevent further interrupts */
#define portSET_INTERRUPT_MASK_FROM_ISR()                          0 /* no information needs to be stored */
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedStatusRegister)   (void)uxSavedStatusRegister
%elif (CPUfamily = "Kinetis")
%elif (CPUfamily = "56800")
%else
  #error "undefined target %CPUfamily!"
%endif

#if configCOMPILER==configCOMPILER_DSC_FSL
  /* for DSC, there is a possible skew after enable/disable Interrupts. */
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() \
  	asm(nop); asm(nop); asm(nop); asm(nop); asm(nop); asm(nop);
#else
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() /* nothing special needed */
#endif

%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#define portDISABLE_ALL_INTERRUPTS()         (void)ulPortSetIPL(7)
#define portDISABLE_INTERRUPTS()             (void)ulPortSetIPL(configMAX_SYSCALL_INTERRUPT_PRIORITY)
#define portENABLE_INTERRUPTS()              (void)ulPortSetIPL(0)
#define portENTER_CRITICAL()                 vPortEnterCritical()
#define portEXIT_CRITICAL()                  vPortExitCritical()
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#define portDISABLE_ALL_INTERRUPTS()         __asm("cli")
#define portENABLE_INTERRUPTS()              __asm("cli")
#define portDISABLE_INTERRUPTS()             __asm("sei")
#define portENTER_CRITICAL()                 vPortEnterCritical()
#define portEXIT_CRITICAL()                  vPortExitCritical()
%elif (CPUfamily = "Kinetis") & ((%Compiler == "GNUC")|(%Compiler = "ARM_CC"))
/* macro to identify CPU: 0 for M0+ and 4 for M4 */
#define portDISABLE_ALL_INTERRUPTS()         __asm volatile("cpsid i")

#if configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY) /* Cortex M4 */
/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */
#define portSET_INTERRUPT_MASK()  \
  __asm volatile            \
  (                         \
    "  mov r0, %%0 \n" \
    "  msr basepri, r0 \n"  \
    : /* no output operands */ \
    :"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY) /* input */\
    :"r0" /* clobber */    \
  )
/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.
 */
#define portCLEAR_INTERRUPT_MASK() \
  __asm volatile            \
  (                         \
    "  mov r0, #0      \n"  \
    "  msr basepri, r0 \n"  \
    : /* no output */       \
    : /* no input */        \
    :"r0" /* clobber */     \
  )
#else
#define portSET_INTERRUPT_MASK()              __asm volatile("cpsid i")
#define portCLEAR_INTERRUPT_MASK()            __asm volatile("cpsie i")
#endif

#define portSET_INTERRUPT_MASK_FROM_ISR()     0;portSET_INTERRUPT_MASK()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)  portCLEAR_INTERRUPT_MASK();(void)x

extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);

#define portDISABLE_ALL_INTERRUPTS()   __asm volatile("cpsid i")
#define portDISABLE_INTERRUPTS()   portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()    portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()       vPortEnterCritical()
#define portEXIT_CRITICAL()        vPortExitCritical()

/* There are an uneven number of items on the initial stack, so
portALIGNMENT_ASSERT_pxCurrentTCB() will trigger false positive asserts. */
#define portALIGNMENT_ASSERT_pxCurrentTCB (void)

%elif (CPUfamily = "Kinetis")
extern void vPortSetInterruptMask(void);
extern void vPortClearInterruptMask(void);
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#if configCOMPILER==configCOMPILER_IAR
/* \todo: !!! IAR does not allow msr BASEPRI, r0 in vPortSetInterruptMask()? */
#define portDISABLE_ALL_INTERRUPTS()         __asm volatile( "cpsid i" )
#define portDISABLE_INTERRUPTS()             __asm volatile( "cpsid i" )
#define portENABLE_INTERRUPTS()              __asm volatile( "cpsie i" )
#else
#define portDISABLE_ALL_INTERRUPTS()         __asm volatile( "cpsid i" )
#define portDISABLE_INTERRUPTS()             vPortSetInterruptMask()
#define portENABLE_INTERRUPTS()              vPortClearInterruptMask()
#endif
#define portENTER_CRITICAL()                 vPortEnterCritical()
#define portEXIT_CRITICAL()                  vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()    0;vPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortClearInterruptMask();(void)x
%elif (CPUfamily = "56800")
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#define portENABLE_INTERRUPTS()              __asm(bfclr #0x0300,SR) /* Enable interrupts of level 0,1,2,3 */
#define portDISABLE_INTERRUPTS()             __asm(bfset #0x0300,SR) /* Disable interrupts, only level 3 allowed */
#define portENTER_CRITICAL()                 vPortEnterCritical()
#define portEXIT_CRITICAL()                  vPortExitCritical()
%else
  #error "undefined target %CPUfamily!"
%endif
/*-----------------------------------------------------------*/
/* Scheduler utilities. */
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF") | (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
#define portNOP()          __asm("nop")
%elif (CPUfamily = "Kinetis")
%elif (CPUfamily = "56800")
#define portNOP()          __asm(nop)
%endif

%if (CPUfamily = "ColdFireV1")
/* Context switches are requested using the force register. */
#define portCF_INTC_VALUE \
%if FreeRTOSColdFireCPU='MCF51CN' | FreeRTOSColdFireCPU='MCF51JM' | FreeRTOSColdFireCPU='MCF51MM' | FreeRTOSColdFireCPU='MCF51ME'
 /* Setting for MCF51CN, JM, MM and ME families */ \
 %if ColdFireSWI='VL1swi'
  0x3E /* INTC_FRC[LVL1] (VL1swi) set */
 %elif ColdFireSWI='VL2swi'
  0x3D /* INTC_FRC[LVL1] (VL2swi) set */
 %elif ColdFireSWI='VL3swi'
  0x3C /* INTC_FRC[LVL1] (VL3swi) set */
 %elif ColdFireSWI='VL4swi'
  0x3B /* INTC_FRC[LVL1] (VL4swi) set */
 %elif ColdFireSWI='VL5swi'
  0x3A /* INTC_FRC[LVL1] (VL5swi) set */
 %elif ColdFireSWI='VL6swi'
  0x39 /* INTC_FRC[LVL1] (VL6swi) set */
 %elif ColdFireSWI='VL7swi'
  0x38 /* INTC_FRC[LVL1] (VL7swi) set */
 %else
  #error "unknown ColdFireSWI setting in embedded component properties!"
 %endif
%elif FreeRTOSColdFireCPU='MCF51QE'
 /* Setting for MCF51QE */ \
 %if ColdFireSWI='VL1swi'
  0x26 /* INTC_FRC[LVL1] (VL1swi) set */
 %elif ColdFireSWI='VL2swi'
  0x25 /* INTC_FRC[LVL1] (VL2swi) set */
 %elif ColdFireSWI='VL3swi'
  0x24 /* INTC_FRC[LVL1] (VL3swi) set */
 %elif ColdFireSWI='VL4swi'
  0x23 /* INTC_FRC[LVL1] (VL4swi) set */
 %elif ColdFireSWI='VL5swi'
  0x22 /* INTC_FRC[LVL1] (VL5swi) set */
 %elif ColdFireSWI='VL6swi'
  0x21 /* INTC_FRC[LVL1] (VL6swi) set */
 %elif ColdFireSWI='VL7swi'
  0x20 /* INTC_FRC[LVL1] (VL7swi) set */
 %else
  #error "unknown ColdFireSWI setting in embedded component properties!"
 %endif
%else
  #error "unknown ColdFire CPU setting in embedded component properties!"
%endif

#define portYIELD() \
  INTC_SFRC = portCF_INTC_VALUE; /* INTC_FRC[LVLx] (VLxswi) set */ \
  portNOP(); portNOP(); portNOP(); portNOP(); portNOP() /* do some nop's to give the machine a chance to raise the interrupt */
#define portEND_SWITCHING_ISR(xSwitchRequired) \
  if (xSwitchRequired != pdFALSE) { \
    portYIELD();                    \
  }
%elif (CPUfamily = "MCF")
/* Note this will overwrite all other bits in the force register, it is done this way for speed. */
#define configYIELD_INTERRUPT_VECTOR  %ColdFireV2SWInumber
#define portYIELD() \
  INTFRCL0 = (1UL<<configYIELD_INTERRUPT_VECTOR);  /* Interrupt force register. We are using the high word of the 64bit mask. */ \
  portNOP(); portNOP() /* do some nops to give the machine a chance to raise the interrupt */
#define portEND_SWITCHING_ISR(xSwitchRequired) \
  if (xSwitchRequired != pdFALSE) { \
    portYIELD();                    \
  }
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
/* force a context switch with the SWI instruction. */
#define portYIELD() __asm("swi")
#define portEND_SWITCHING_ISR(xSwitchRequired) \
  if (xSwitchRequired != pdFALSE) { \
    portYIELD(); \
  }
%elif (CPUfamily = "Kinetis")
extern void vPortYieldFromISR(void);
#define portYIELD()                             vPortYieldFromISR()
#define portEND_SWITCHING_ISR(xSwitchRequired)  if(xSwitchRequired) vPortYieldFromISR()
/*-----------------------------------------------------------*/

/* Architecture specific optimizations. */
#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

	/* Generic helper function. */
	__attribute__( ( always_inline ) ) static inline unsigned char ucPortCountLeadingZeros( unsigned long ulBitmap )
	{
	unsigned char ucReturn;

		__asm volatile ( "clz %%0, %%1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );
		return ucReturn;
	}

	/* Check the configuration. */
	#if( configMAX_PRIORITIES > 32 )
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif

	/* Store/clear the ready priorities in a bit map. */
	#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
	#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

	/*-----------------------------------------------------------*/

	#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - ucPortCountLeadingZeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

%elif (CPUfamily = "56800")
extern void vPortYield(void);
#define portYIELD() do {\
                        vPortYield();\
                        asm(nop);\
                        asm(nop);\
                        asm(nop);\
                        asm(nop);\
                        asm(nop);\
                        asm(nop);\
                      } while (0)
#define portEND_SWITCHING_ISR(xSwitchRequired) \
  if (xSwitchRequired != pdFALSE) { \
    portYIELD(); \
  }
%else
  #error "unsupported target!" %CPUfamily
%endif
/*-----------------------------------------------------------*/
/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
  extern void vPortSuppressTicksAndSleep(portTickType xExpectedIdleTime);
  #define portSUPPRESS_TICKS_AND_SLEEP(xExpectedIdleTime) vPortSuppressTicksAndSleep(xExpectedIdleTime)
#endif
/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)   void vFunction(void *pvParameters) __attribute__((noreturn))
#define portTASK_FUNCTION(vFunction, pvParameters)         void vFunction(void *pvParameters)
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X") | (CPUfamily = "Kinetis")
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)   void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters)         void vFunction(void *pvParameters)
%elif (CPUfamily = "56800")
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)   void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters)         void vFunction(void *pvParameters)
%else
  #error "unsupported target!" %CPUfamily
%endif
/*-----------------------------------------------------------*/
%if (CPUfamily = "HCS08") | (CPUfamily = "HC08")
/*
 * These macros are very simple as the processor automatically saves and
 * restores its registers as interrupts are entered and exited.  In
 * addition to the (automatically stacked) registers we also stack the
 * critical nesting count. Each task maintains its own critical nesting
 * count as it is legitimate for a task to yield from within a critical
 * section.  If the banked memory model is being used then the PPAGE
 * register is also stored as part of the tasks context.
 * Stack layout:
 *   PC.low
 *   PC.high
 *   X
 *   A
 *   CCR      <- this is the stack pushed by the interrupt
 *   H        <- this is stacked by the compiler inside ISR!
 *   PAGE     <- Only for banked model
 *   nesting  <- critical nesting count
 */

#ifdef __BANKED__
  #include "IO_Map.h" /* needed for _PPAGE */
  /* Load the stack pointer for the task, then pull the critical nesting
   * count and PPAGE register from the stack.  The remains of the
   * context are restored by the RTI instruction.
   */
  #define portRESTORE_CONTEXT()      \
    {                                  \
    extern volatile void *pxCurrentTCB; \
    __asm("LDHX pxCurrentTCB");      \
    __asm("LDHX 0,X");               \
    __asm("TXS");                    \
    __asm("PULA");                   \
    __asm("STA uxCriticalNesting");  \
    __asm("PULA"); /* get PPAGE */   \
    __asm("STA _PPAGE"); /* store */ \
    __asm("PULH");                   \
    __asm("RTI");                    \
  }
  /* By the time this macro is called the processor has already stacked the
   * registers.  Simply stack the nesting count and PPAGE value, then save
   * the task stack pointer.
   */
  #define portSAVE_CONTEXT() \
  { \
    extern volatile void *pxCurrentTCB; \
    __asm("LDA _PPAGE"); /* save PPAGE */ \
    __asm("PSHA");                  \
    __asm("LDA uxCriticalNesting"); \
    __asm("PSHA");                  \
    __asm("TSX"); /* get SP and store in TCB */  \
    __asm("PSHX");                  \
    __asm("PSHH");                  \
    __asm("LDHX pxCurrentTCB");     \
    __asm("PULA");                  \
    __asm("STA 0,X");               \
    __asm("PULA");                  \
    __asm("STA 1,X");               \
  }
#else
  /* These macros are as per the BANKED versions above, but without saving
   * and restoring the PPAGE register.
   */
  #define portRESTORE_CONTEXT()    \
  {  \
    extern volatile void *pxCurrentTCB; \
    __asm("LDHX pxCurrentTCB");    \
    __asm("LDHX 0,X");             \
    __asm("TXS");                  \
    __asm("PULA");                 \
    __asm("STA uxCriticalNesting") \
    __asm("PULH")                  \
    __asm("RTI");                  \
  }

  #define portSAVE_CONTEXT()        \
  { \
    extern volatile void *pxCurrentTCB; \
    __asm("LDA uxCriticalNesting"); \
    __asm("PSHA");                  \
    __asm("TSX"); /* get SP and store in TCB */  \
    __asm("PSHX");                  \
    __asm("PSHH");                  \
    __asm("LDHX pxCurrentTCB");     \
    __asm("PULA");                  \
    __asm("STA 0,X");               \
    __asm("PULA");                  \
    __asm("STA 1,X");               \
  }
#endif
%elif (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
/*
 * These macros are very simple as the processor automatically saves and
 * restores its registers as interrupts are entered and exited.  In
 * addition to the (automatically stacked) registers we also stack the
 * critical nesting count.  Each task maintains its own critical nesting
 * count as it is legitimate for a task to yield from within a critical
 * section.  If the banked memory model is being used then the PPAGE
 * register is also stored as part of the tasks context.
 */
#ifdef __BANKED__
  /* Load the stack pointer for the task, then pull the critical nesting
   * count and PPAGE register from the stack.  The remains of the
   * context are restored by the RTI instruction.
   */
#ifdef __HCS12X__
  #define portRESTORE_CONTEXT() \
  {                             \
    extern volatile void *pxCurrentTCB;\
    extern volatile unsigned portBASE_TYPE uxCriticalNesting;  \
    __asm("ldx pxCurrentTCB");       \
    __asm("lds 0,x");                \
    __asm("pula");                   \
    __asm("staa uxCriticalNesting"); \
    __asm("pula");                   \
    __asm("staa _RPAGE");            \
    __asm("pula");                   \
    __asm("staa _GPAGE");            \
    __asm("pula");                   \
    __asm("staa _EPAGE");            \
    __asm("pula");                   \
    __asm("staa _PPAGE");            \
    __asm("rti"); \
  }
#else
  #define portRESTORE_CONTEXT() \
  {                             \
    extern volatile void *pxCurrentTCB;\
    extern volatile unsigned portBASE_TYPE uxCriticalNesting;  \
    __asm("ldx pxCurrentTCB");       \
    __asm("lds 0,x");                \
    __asm("pula");                   \
    __asm("staa uxCriticalNesting"); \
    __asm("pula");                   \
    __asm("staa _PPAGE");            \
    __asm("rti"); \
  }
#endif
  /* By the time this macro is called the processor has already stacked the
    * registers.  Simply stack the nesting count and PPAGE value, then save
    * the task stack pointer.
    */
#ifdef __HCS12X__
  #define portSAVE_CONTEXT() \
  {                          \
    extern volatile void *pxCurrentTCB; \
    extern volatile unsigned portBASE_TYPE uxCriticalNesting; \
    __asm("ldaa _PPAGE");           \
    __asm("psha");                  \
    __asm("ldaa _EPAGE");           \
    __asm("psha");                  \
    __asm("ldaa _GPAGE");           \
    __asm("psha");                  \
    __asm("ldaa _RPAGE");           \
    __asm("psha");                  \
    __asm("ldaa uxCriticalNesting");\
    __asm("psha");                  \
    __asm("ldx pxCurrentTCB");      \
    __asm("sts 0,x");               \
  }
#else
  #define portSAVE_CONTEXT() \
  {                          \
    extern volatile void *pxCurrentTCB; \
    extern volatile unsigned portBASE_TYPE uxCriticalNesting; \
    __asm("ldaa _PPAGE");           \
    __asm("psha");                  \
    __asm("ldaa uxCriticalNesting");\
    __asm("psha");                  \
    __asm("ldx pxCurrentTCB");      \
    __asm("sts 0,x");               \
  }
#endif

#else
  /* These macros are as per the BANKED versions above, but without saving
   * and restoring the PPAGE register.
   */
  #define portRESTORE_CONTEXT() \
  {                             \
    extern volatile void *pxCurrentTCB; \
    extern volatile unsigned portBASE_TYPE uxCriticalNesting;  \
    __asm("ldx pxCurrentTCB");  \
    __asm("lds 0,x");           \
    __asm("pula");              \
    __asm("staa uxCriticalNesting"); \
    __asm("rti") \
  }

  #define portSAVE_CONTEXT()  \
  {                           \
    extern volatile void * pxCurrentTCB; \
    extern volatile unsigned portBASE_TYPE uxCriticalNesting; \
    __asm("ldaa uxCriticalNesting"); \
    __asm("psha");                   \
    __asm("ldx pxCurrentTCB");       \
    __asm("sts 0,x");                \
  }
#endif
%endif
%if (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")

/* Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#define portTASK_SWITCH_FROM_ISR() \
    portSAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    portRESTORE_CONTEXT();

%endif
void vPortStartFirstTask(void);
  /* starts the first task, called from xPortStartScheduler() */

void vPortYieldHandler(void);
  /* handler for the SWI interrupt */

#if configCPU_FAMILY==configCPU_FAMILY_ARM_M4F /* floating point unit */
  void vPortEnableVFP(void);
    /* enables floating point support in the CPU */
#endif

%if (CPUfamily = "Kinetis")

/* Prototypes for interrupt service handlers */
void vPortSVCHandler(void); /* SVC interrupt handler */
void vPortPendSVHandler(void); /* PendSV interrupt handler */
void vPortTickHandler(void); /* Systick interrupt handler */
%endif

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */
