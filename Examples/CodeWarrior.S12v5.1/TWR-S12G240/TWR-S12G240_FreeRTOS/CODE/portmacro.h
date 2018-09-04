/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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


#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOSConfig.h"
#include "projdefs.h" /* for pdFALSE, pdTRUE */
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
#endif

#include "Cpu.h"

#if configUSE_MPU_SUPPORT
/*-----------------------------------------------------------*/
/* MPU specific constants. */
#define portUSING_MPU_WRAPPERS          1
#define portPRIVILEGE_BIT                       ( 0x80000000UL )

#define portMPU_REGION_READ_WRITE                               ( 0x03UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY             ( 0x05UL << 24UL )
#define portMPU_REGION_READ_ONLY                                ( 0x06UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE    ( 0x01UL << 24UL )
#define portMPU_REGION_CACHEABLE_BUFFERABLE             ( 0x07UL << 16UL )
#define portMPU_REGION_EXECUTE_NEVER                    ( 0x01UL << 28UL )

#define portUNPRIVILEGED_FLASH_REGION           ( 0UL )
#define portPRIVILEGED_FLASH_REGION                     ( 1UL )
#define portPRIVILEGED_RAM_REGION                       ( 2UL )
#define portGENERAL_PERIPHERALS_REGION          ( 3UL )
#define portSTACK_REGION                                        ( 4UL )
#define portFIRST_CONFIGURABLE_REGION       ( 5UL )
#define portLAST_CONFIGURABLE_REGION            ( 7UL )
#define portNUM_CONFIGURABLE_REGIONS            ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define portTOTAL_NUM_REGIONS                           ( portNUM_CONFIGURABLE_REGIONS + 1 ) /* Plus one to make space for the stack region. */

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
#endif /* configUSE_MPU_SUPPORT */

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
unsigned portLONG ulPortSetIPL(unsigned portLONG);

/* If set to 1, then this port uses the critical nesting count from the TCB rather than
maintaining a separate value and then saving this value in the task stack. */
#define portCRITICAL_NESTING_IN_TCB    0

extern volatile unsigned portBASE_TYPE uxCriticalNesting;

extern unsigned portBASE_TYPE uxPortSetInterruptMaskFromISR(void);
extern void vPortClearInterruptMaskFromISR(unsigned portBASE_TYPE);

/* Interrupts are always disabled in the ISR, thus nothing to do here to prevent further interrupts */
#define portSET_INTERRUPT_MASK_FROM_ISR()                          0 /* no information needs to be stored */
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedStatusRegister)   (void)uxSavedStatusRegister

#if configCOMPILER==configCOMPILER_DSC_FSL
  /* for DSC, there is a possible skew after enable/disable Interrupts. */
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() \
        asm(nop); asm(nop); asm(nop); asm(nop); asm(nop); asm(nop);
#else
  #define portPOST_ENABLE_DISABLE_INTERRUPTS() /* nothing special needed */
#endif

extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
#define portDISABLE_ALL_INTERRUPTS()         __asm("cli")
#define portENABLE_INTERRUPTS()              __asm("cli")
#define portDISABLE_INTERRUPTS()             __asm("sei")
#define portENTER_CRITICAL()                 vPortEnterCritical()
#define portEXIT_CRITICAL()                  vPortExitCritical()
/*-----------------------------------------------------------*/
/* Scheduler utilities. */
#define portNOP()          __asm("nop")

/* force a context switch with the SWI instruction. */
#define portYIELD() __asm("swi")
#define portEND_SWITCHING_ISR(xSwitchRequired) \
  if (xSwitchRequired != pdFALSE) { \
    portYIELD(); \
  }
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

/* Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#define portTASK_SWITCH_FROM_ISR() \
    portSAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    portRESTORE_CONTEXT();

void vPortStartFirstTask(void);
  /* starts the first task, called from xPortStartScheduler() */

void vPortYieldHandler(void);
  /* handler for the SWI interrupt */

#if configCPU_FAMILY_IS_ARM_FPU(configCPU_FAMILY) /* has floating point unit */
  void vPortEnableVFP(void);
    /* enables floating point support in the CPU */
#endif


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

