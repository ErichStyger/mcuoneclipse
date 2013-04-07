/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


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
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/* include inherited beans */
%ifdef InhrSymbolList
  %for var from InhrSymbolList
#include "%@%var@ModuleName.h"
  %endfor
%endif

/* Kernel includes. */
#include "%'ModuleName'.h" /* for FREERTOS_CPU_CORTEX_M */
#include "FreeRTOS.h"
#include "task.h"

%--------------------------------------------------------------
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
#define portINITIAL_FORMAT_VECTOR           ((portSTACK_TYPE)0x4000)

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER         ((portSTACK_TYPE)0x2000)
%endif
%--------------------------------------------------------------
%if (CPUfamily = "Kinetis")
/* Constants required to manipulate the NVIC. */
#define portNVIC_INT_CTRL        ((volatile unsigned long*)0xe000ed04) /* interrupt control and state register (ICSR) */
#define portNVIC_SYSPRI3         ((volatile unsigned long*)0xe000ed20) /* system handler priority register 3 (SHPR3), used for SysTick and PendSV priority */
#define portNVIC_PENDSVSET       0x10000000 /* bit 28 in portNVIC_INT_CTRL (PENDSVSET), see http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Cihfaaha.html */
#define portNVIC_PENDSV_PRI      (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<16) /* priority of PendableService interrupt */
#define portNVIC_SYSTICK_PRI     (((unsigned long)configKERNEL_INTERRUPT_PRIORITY)<<24) /* priority of SysTick interrupt */

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR         (0x01000000)
#define portINITIAL_EXEC_RETURN  (0xfffffffd)
%if %M4FFloatingPointSupport='yes'

/* Constants required to manipulate the VFP. */
#define portFPCCR                ((volatile unsigned long *)0xe000ef34) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS (0x3UL<<30UL)
%endif
static LDD_TDeviceData *RTOS_TickDevice;
%endif
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

%ifdef vTaskEndScheduler
#include <setjmp.h>
static jmp_buf xJumpBuf; /* Used to restore the original context when the scheduler is ended. */
%endif
/*-----------------------------------------------------------*/
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE * pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters ) {
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  unsigned portLONG ulOriginalA5;

  __asm{ MOVE.L A5, ulOriginalA5 };
  *pxTopOfStack = (portSTACK_TYPE) 0xDEADBEEF;
  pxTopOfStack--;

  /* Exception stack frame starts with the return address. */
  *pxTopOfStack = (portSTACK_TYPE) pxCode;
  pxTopOfStack--;

  *pxTopOfStack = (portINITIAL_FORMAT_VECTOR<<16UL) | ( portINITIAL_STATUS_REGISTER );
  pxTopOfStack--;

  *pxTopOfStack = ( portSTACK_TYPE ) 0x0; /*FP*/
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
%if %M4FFloatingPointSupport='yes'
  pxTopOfStack -= 2; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts,
                        and to ensure alignment. */
%else
  pxTopOfStack--;
%endif
  *pxTopOfStack = portINITIAL_XPSR;   /* xPSR */
  pxTopOfStack--;
  *pxTopOfStack = (portSTACK_TYPE)pxCode;  /* PC */
  pxTopOfStack--;
  *pxTopOfStack = 0;  /* LR */

  /* Save code space by skipping register initialization. */
  pxTopOfStack -= 5;  /* R12, R3, R2 and R1. */
  *pxTopOfStack = (portSTACK_TYPE)pvParameters; /* R0 */

%if %M4FFloatingPointSupport='yes'
  /* A save method is being used that requires each task to maintain its
     own exec return value. */
  pxTopOfStack--;
  *pxTopOfStack = portINITIAL_EXEC_RETURN;
%endif
  pxTopOfStack -= 8;  /* R11, R10, R9, R8, R7, R6, R5 and R4. */
  return pxTopOfStack;
%elif (CPUfamily = "56800")
  /* stack layout is set up as below (same as for an interrupt):
    PC  (Low memory)
    SR
    Optional alignment word
    SP
    Y
    R0
    A2
    B2
    X0
    N3
    M01
    OMR
    C2
    D2
    A10
    B10
    N
    R1
    R2
    R3
    LA
    LA2
    LC2
    LC
    HWS
    HWS
    PC of DispatchRestore
    OSTCBCur->OSTCBStkPtr --> SR of DispatchRestore (High memory)
  */
  *pxTopOfStack = (portSTACK_TYPE)0x0; /* PC */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* SR */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* alignment word */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* SP */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* Y */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* R0 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* A2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* B2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* X0 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* N3 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* M01 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* OMR */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* C2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* D2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* A10 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* B10 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* N */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* R1 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* R2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* R3 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* LA2 */
  pxTopOfStack++;
  *pxTopOfStack = (portSTACK_TYPE)0xDEAD; /* LC2 */
  pxTopOfStack++;

  /* Parameter in A0. */
  //*(pxTopOfStack + 8) = (portSTACK_TYPE)pvParameters;

  return pxTopOfStack;
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
}
%if (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
/*-----------------------------------------------------------*/
%if (%Compiler = "MetrowerksHC08CC") | (%Compiler = "MetrowerksHCS08CC")
#pragma MESSAGE DISABLE C1404 /* return expected */
#pragma MESSAGE DISABLE C20000 /* dead code detected */
#pragma NO_RETURN
#pragma CODE_SEG __NEAR_SEG NON_BANKED
%elif (%Compiler = "MetrowerksHC12CC") | (%Compiler = "MetrowerksHC12XCC")
#pragma MESSAGE DISABLE C1404 /* return expected */
#pragma NO_RETURN
%endif
static portBASE_TYPE xBankedStartScheduler(void) {
  /* Restore the context of the first task. */
  portRESTORE_CONTEXT(); /* Simulate the end of an interrupt to start the scheduler off. */
  /* Should not get here! */
  return pdFALSE;
}
%if (%Compiler = "MetrowerksHC08CC") | (%Compiler = "MetrowerksHCS08CC")
#pragma CODE_SEG DEFAULT
#pragma MESSAGE DEFAULT C1404 /* return expected */
#pragma MESSAGE DEFAULT C20000 /* dead code detected */
%elif (%Compiler = "MetrowerksHC12CC") | (%Compiler = "MetrowerksHC12XCC")
#pragma MESSAGE DEFAULT C1404 /* return expected */
%endif
%endif
/*-----------------------------------------------------------*/
void vPortInitTickTimer(void) {
%ifdef TickTimerLDD
  RTOS_TickDevice = %@TickTimerLDD@'ModuleName'%.Init(NULL);     %>40/* initialize the tick timer */
%else
  /* nothing special to do */
%endif
}
/*-----------------------------------------------------------*/
void vPortStartTickTimer(void) {
%ifdef TickCntr
  (void)%@TickCntr@'ModuleName'%.Reset();   %>40/* reset the tick counter */
  (void)%@TickCntr@'ModuleName'%.Enable();  %>40/* start the tick timer */
%endif
%ifdef TickTimerLDD
  (void)%@TickTimerLDD@'ModuleName'%.Enable(RTOS_TickDevice);   %>40/* start the tick timer */
%endif
}
/*-----------------------------------------------------------*/
void vPortStopTickTimer(void) {
%ifdef TickCntr
  (void)%@TickCntr@'ModuleName'%.Disable();                     %>40/* stop the tick timer */
%endif
%ifdef TickTimerLDD
  (void)%@TickTimerLDD@'ModuleName'%.Disable(RTOS_TickDevice);   %>40/* stop the tick timer */
%endif
}
/*-----------------------------------------------------------*/
%if (CPUfamily = "Kinetis") & %Compiler == "GNUC" & %M4FFloatingPointSupport='yes'
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
%endif
portBASE_TYPE xPortStartScheduler(void) {
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  uxCriticalNesting = 0;
  vPortStartTickTimer();
%ifdef vTaskEndScheduler
  if(setjmp(xJumpBuf) != 0 ) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
%endif
  /* Kick off the scheduler by setting up the context of the first task. */
  vPortStartFirstTask();     %>40/* start the first task executing. Note that we will not return here */
  return pdFALSE;
%elif (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
  /* xPortStartScheduler() does not start the scheduler directly because
     the header file containing the xPortStartScheduler() prototype is part
     of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     Instead it simply calls the locally defined xBankedStartScheduler() -
     which does use the CODE_SEG pragma. */
  vPortStartTickTimer();
%ifdef vTaskEndScheduler
  if(setjmp(xJumpBuf) != 0 ) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
%endif
  return xBankedStartScheduler();
%elif (CPUfamily = "Kinetis")
  /* Make PendSV and SysTick the lowest priority interrupts. */
  /* Overwrite PendSV priority as set inside the CPU component: it needs to have the lowest priority! */
  *(portNVIC_SYSPRI3) |= portNVIC_PENDSV_PRI; /* set priority of PendSV interrupt */
  uxCriticalNesting = 0; /* Initialize the critical nesting count ready for the first task. */
  /* overwrite SysTick priority is set inside the FreeRTOS component */
  *(portNVIC_SYSPRI3) |= portNVIC_SYSTICK_PRI; /* set priority of SysTick interrupt */
  vPortStartTickTimer();
%if %M4FFloatingPointSupport='yes'
  /* Ensure the VFP is enabled - it should be anyway. */
  vPortEnableVFP();
  /* Lazy register save always. */
  *(portFPCCR) |= portASPEN_AND_LSPEN_BITS;
%endif
  vPortStartFirstTask(); /* Start the first task. */
  /* Should not get here, unless you call vTaskEndScheduler()! */
  return pdFALSE;
%elif (CPUfamily = "56800")
  uxCriticalNesting = 0;
  vPortStartTickTimer();
%ifdef vTaskEndScheduler
  if(setjmp(xJumpBuf) != 0 ) {
    /* here we will get in case of call to vTaskEndScheduler() */
    return pdFALSE;
  }
%endif
  /* Kick off the scheduler by setting up the context of the first task. */
  vPortStartFirstTask();     %>40/* start the first task executing. Note that we will not return here */
  return pdFALSE;
%else
  %warning "unsupported target %CPUfamily!"
  #error "unsupported target %CPUfamily!"
%endif
}
%ifdef vTaskEndScheduler
/*-----------------------------------------------------------*/
void vPortEndScheduler(void) {
  vPortStopTickTimer();
  /* Jump back to the processor state prior to starting the
     scheduler.  This means we are not going to be using a
     task stack frame so the task can be deleted. */
  longjmp(xJumpBuf, 1);
}
%endif
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
  uxCriticalNesting++;
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
  *(portNVIC_INT_CTRL) = portNVIC_PENDSVSET;
}
/*-----------------------------------------------------------*/
%endif
%if (CPUfamily = "56800")
#if defined(vPortYieldISR_FAST_INT)
#pragma interrupt fast
#elif defined(vPortYieldISR_VECT_TABLE_ISR_FAST_INT)
#pragma define_section interrupt_fast "interrupt_fast.text"  RX
#pragma section interrupt_fast begin
#pragma interrupt fast
#else
#pragma interrupt
#endif
void vPortYieldISR(void)
{
  // Your interrupt code
}
#if defined(vPortYieldISR_VECT_TABLE_ISR_FAST_INT)
#pragma section interrupt_fast end
#endif
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
%endif
%if (CPUfamily = "Kinetis") & (%Compiler = "GNUC")
__attribute__ ((naked)) void vOnCounterRestart(void) {
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
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
  /* If using preemption, also force a context switch. */
  #if configUSE_PREEMPTION == 1
  *(portNVIC_INT_CTRL) = portNVIC_PENDSVSET;
  #endif
  portSET_INTERRUPT_MASK();   /* disable interrupts */
  vTaskIncrementTick(); /* increment tick count, might schedule a task */
  portCLEAR_INTERRUPT_MASK(); /* enable interrupts again */
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
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
}
/*-----------------------------------------------------------*/
void vPortStartFirstTask(void) {
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
  __asm volatile (
    " ldr r0, =0xE000ED08 \n" /* Use the NVIC offset register to locate the stack. */
    " ldr r0, [r0]        \n"
    " ldr r0, [r0]        \n"
    " msr msp, r0         \n" /* Set the msp back to the start of the stack. */
    " cpsie i             \n" /* Globally enable interrupts. */
    " svc 0               \n" /* System call to start first task. */
    " nop                 \n"
  );
#else /* Cortex M0+ */
  __asm volatile(
    " movs r0, #0x00      \n" /* Locate the top of stack. */
    " ldr r0, [r0]        \n"
    " msr msp, r0         \n" /* Set the msp back to the start of the stack. */
    " cpsie i             \n" /* Globally enable interrupts. */
    " svc 0               \n" /* System call to start first task. */
    " nop                 \n"
  );
#endif
}
/*-----------------------------------------------------------*/
__attribute__ ((naked)) void vPortSVCHandler(void) {
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
__asm volatile (
    " ldr r3, pxCurrentTCBConst2 \n" /* Restore the context. */
    " ldr r1, [r3]               \n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    " ldr r0, [r1]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
    /* pop the core registers */
    %if %M4FFloatingPointSupport='yes'
    " ldmia r0!, {r4-r11, r14}   \n"
    %else
    " ldmia r0!, {r4-r11}        \n"
    %endif
    " msr psp, r0                \n"
    " mov r0, #0                 \n"
    " msr basepri, r0            \n"
    %if %M4FFloatingPointSupport='no'
    " orr r14, r14, #13          \n"
    %endif
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
__attribute__ ((naked)) void vPortPendSVHandler(void) {
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
  __asm volatile (
    " mrs r0, psp                \n"
    " ldr  r3, pxCurrentTCBConst \n" /* Get the location of the current TCB. */
    " ldr  r2, [r3]              \n"
%if %M4FFloatingPointSupport='yes'
    " tst r14, #0x10             \n" /* Is the task using the FPU context?  If so, push high vfp registers. */
    " it eq                      \n"
    " vstmdbeq r0!, {s16-s31}    \n"

    " stmdb r0!, {r4-r11, r14}   \n" /* save remaining core registers */
%else
    " stmdb r0!, {r4-r11}        \n" /* Save the core registers. */
%endif
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
%if %M4FFloatingPointSupport='yes'
    " ldmia r0!, {r4-r11, r14}   \n" /* Pop the core registers */
    " tst r14, #0x10             \n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
    " it eq                      \n"
    " vldmiaeq r0!, {s16-s31}    \n"
%else
    " ldmia r0!, {r4-r11}        \n" /* Pop the core registers. */
%endif
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
    " bx r3	                     \n"
    "                            \n"
    ".align 2                    \n"
    "pxCurrentTCBConst: .word pxCurrentTCB"
  );
#endif
}
%endif
