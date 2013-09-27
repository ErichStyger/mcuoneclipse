%if %Compiler == "GNUC"  %- GNU gcc
/* file is intentionally empty as not needed with %Compiler for this FreeRTOS port */
%elif %Compiler=="ARM_CC" %- Keil ARM
	AREA ARMEex, CODE, READONLY
dummy    ; dummy label, will not be used
	nop  ; just doing a nop
	END  ; mark end of file
%else
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF") | (CPUfamily = "Kinetis")
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
%endif
%if (CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
/*
 * Purpose: Lowest level routines for all ColdFire processors.
 *
 * Notes:
 *
 * ulPortSetIPL() and mcf5xxx_wr_cacr() copied with permission from FreeScale
 * supplied source files.
 */

    .global ulPortSetIPL
    .global _ulPortSetIPL
    .global mcf5xxx_wr_cacrx
    .global _mcf5xxx_wr_cacrx
    .global vPortYieldISR
    .global _vPortYieldISR
    .global vPortStartFirstTask
    .global _vPortStartFirstTask
    .extern _pxCurrentTCB
    .extern _vPortYieldHandler

    .text

.macro portSAVE_CONTEXT
  lea.l                (-60, sp), sp
  movem.l              d0-a6, (sp)
  move.l               _pxCurrentTCB, a0
  move.l               sp, (a0)
  .endm

.macro portRESTORE_CONTEXT
  move.l               _pxCurrentTCB, a0
  move.l               (a0), sp
  movem.l              (sp), d0-a6
  lea.l                (60, sp), sp
  rte
  .endm
/********************************************************************/
/*
 * This routines changes the IPL to the value passed into the routine.
 * It also returns the old IPL value back.
 * Calling convention from C:
 *   old_ipl = asm_set_ipl(new_ipl);
 */
ulPortSetIPL:
_ulPortSetIPL:
  link    A6,#-8
  movem.l D6-D7,(SP)

  move.w  SR,D7           /* current sr    */

  move.l  D7,D6           /* prepare return value  */
  andi.l  #0x0700,D6      /* mask out IPL  */
  lsr.l   #8,D6           /* IPL   */

  andi.l  #0x07,D0        /* least significant three bits  */
  lsl.l   #8,D0           /* move over to make mask    */

  andi.l  #0x0000F8FF,D7  /* zero out current IPL  */
  or.l    D0,D7           /* place new IPL in sr   */
  move.w  D7,SR

  move.l  D6, D0          /* Return value in D0 */
  movem.l (SP),D6-D7
  lea     8(SP),SP
  unlk    A6
  rts
/********************************************************************/
mcf5xxx_wr_cacrx:
_mcf5xxx_wr_cacrx:
  move.l  4(sp),d0
  .long   0x4e7b0002  /* movec d0,cacr   */
  nop
  rts
/********************************************************************/
/* Yield interrupt. */
_vPortYieldISR:
vPortYieldISR:
  portSAVE_CONTEXT
  jsr _vPortYieldHandler
  portRESTORE_CONTEXT
/********************************************************************/
vPortStartFirstTask:
_vPortStartFirstTask:
  portRESTORE_CONTEXT
  .end
%-*****************************************************************************************************
%elif (CPUfamily = "Kinetis")
#include "FreeRTOSConfig.h"

/* For backward compatibility, ensure configKERNEL_INTERRUPT_PRIORITY is
   defined.  The value zero should also ensure backward compatibility.
   FreeRTOS.org versions prior to V4.3.0 did not include this definition. */
#ifndef configKERNEL_INTERRUPT_PRIORITY
  #define configKERNEL_INTERRUPT_PRIORITY 0
#endif

#define VECTOR_TABLE_OFFSET_REG     0xE000ED08 /* Vector Table Offset Register (VTOR) */
%if %M4FFloatingPointSupport='yes'
#define COPROCESSOR_ACCESS_REGISTER 0xE000ED88 /* Coprocessor Access Register (CPACR) */
%endif

%if (%Compiler = "IARARM") %- /* IAR ARM */
  RSEG    CODE:CODE(2)
  thumb

  EXTERN vPortYieldFromISR
  EXTERN pxCurrentTCB
  EXTERN vTaskSwitchContext
  EXTERN xTaskIncrementTick

  PUBLIC vOnCounterRestart
  PUBLIC vSetMSP
  PUBLIC vPortPendSVHandler
  PUBLIC vPortSetInterruptMask
  PUBLIC vPortClearInterruptMask
  PUBLIC vPortSVCHandler
  PUBLIC vPortStartFirstTask

/* macros to identify CPU: 0 for M0+ and 4 for M4 */
%if %CPUDB_prph_has_feature(CPU,ARM_CORTEX_M0P) = 'yes' %- Note: for IAR this is defined in portasm.s too!
#define FREERTOS_CPU_CORTEX_M                                    %>>0 /* Cortex M0+ core */
%else
#define FREERTOS_CPU_CORTEX_M                                    %>>4 /* Cortex M4 core */
%endif

%else %- /* Freescale ARM */
  .text, code

  .extern vPortYieldFromISR
  .extern pxCurrentTCB
  .extern vTaskSwitchContext
  .extern xTaskIncrementTick

  .global vSetMSP
  .global vPortPendSVHandler
  .global vPortSetInterruptMask
  .global vPortClearInterruptMask
  .global vPortSVCHandler
  .global vPortStartFirstTask
  .global vOnCounterRestart
%if %M4FFloatingPointSupport='yes'
  .global vPortEnableVFP
%endif
%endif %- /* IAR or CW */
/*-----------------------------------------------------------*/
vOnCounterRestart:
%if (%Compiler = "IARARM")
  /* caller did this:
     push {r7,LR}
     bl vOnCounterRestart
     pop {r0,pc} */
  pop {r0, r7} /* restore r7 and lr into r0 and r7, which were pushed in caller */
  push {r0, r7}
%else
  %if %CompilerOptimizationLevel='0'
  /* Compiler optimization level 0 */
  pop {lr,r3} /* remove stacked registers from the caller routine */
  %else
  /* Compiler optimization level 1, 2, 3 or 4 */
  push {lr} /* need to save link register, it will be overwritten below */
  %endif
%endif
%if %UsePreemption='yes'
  /* If using preemption, also force a context switch. */
  bl vPortYieldFromISR
%endif
  bl vPortSetInterruptMask /* disable interrupts */
  bl xTaskIncrementTick    /* increment tick count, might schedule a task */
  bl vPortClearInterruptMask /* enable interrupts again */
%if (%Compiler = "IARARM")
  pop {r7,pc}  /* start exit sequence from interrupt: r7 and lr where pushed above */
  nop
%else
  %if %CompilerOptimizationLevel='0'
  /* Compiler optimization level 0 */
  pop {lr,r4} /* start exit sequence from interrupt: r4 and lr where pushed in the ISR */
  %else
  /* Compiler optimization level 1, 2, 3 or 4 */
  pop {lr}    /* restore pushed lr register */
  %endif
  bx lr
  nop
%endif
/*-----------------------------------------------------------*/
vSetMSP:
  msr msp, r0
  bx lr
  nop
/*-----------------------------------------------------------*/
%if (%Compiler = "IARARM")
vPortPendSVHandler:
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
    mrs r0, psp
    ldr  r3, pxCurrentTCBConst  /* Get the location of the current TCB. */
    ldr  r2, [r3]
%if %M4FFloatingPointSupport='yes'
    tst r14, #0x10              /* Is the task using the FPU context?  If so, push high vfp registers. */
    it eq
    vstmdbeq r0!, {s16-s31}

    stmdb r0!, {r4-r11, r14}    /* save remaining core registers */
%else
    stmdb r0!, {r4-r11}         /* Save the core registers. */
%endif
    str r0, [r2]                /* Save the new top of stack into the first member of the TCB. */
    stmdb sp!, {r3, r14}
    mov r0, %%0
    msr basepri, r0
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0
    ldmia sp!, {r3, r14}
    ldr r1, [r3]                /* The first item in pxCurrentTCB is the task top of stack. */
    ldr r0, [r1]
%if %M4FFloatingPointSupport='yes'
    ldmia r0!, {r4-r11, r14}   /* Pop the core registers */
    tst r14, #0x10             /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
    it eq
    vldmiaeq r0!, {s16-s31}
%else
    ldmia r0!, {r4-r11}        /* Pop the core registers. */
%endif
    msr psp, r0
    bx r14
    nop
#else /* Cortex M0+ */
    mrs r0, psp

    ldr r3, =pxCurrentTCB
    ldr r2, [r3]

    subs r0, r0, #32           /* Make space for the remaining low registers. */
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
    adds r0, r0, #16           /* Move to the high registers. */
    ldmia r0!, {r4-r7}         /* Pop the high registers. */
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7

    msr psp, r0                /* Remember the new top of stack for the task. */

    subs r0, r0, #32           /* Go back for the low registers that are not automatically restored. */
    ldmia r0!, {r4-r7}         /* Pop low registers.  */

    bx r3
    nop
#endif

%else %- FSL ARM Compiler */
vPortPendSVHandler:
%if (defined(PEversionDecimal) && (PEversionDecimal >=0 '1282')) %- this is only supported with MCU 10.3
%else %- up to MCU10.2
  %if %CompilerOptimizationLevel='0'
  /* Compiler optimization level 0 */
  pop {lr,r3}  /* remove stack frame for the call from Cpu.c to Events.c */
  pop {lr,r3}  /* remove stack frame for the call from Events.c to here */
  %else
  /* Compiler optimization level 1, 2, 3 or 4: nothing special to do */
  %endif
%endif %- MCU10.3
  mrs r0, psp

  /* Get the location of the current TCB */
  ldr r3, =pxCurrentTCB
  ldr r2, [r3] /* r2 points now to top-of-stack of the current task */

  /* Save the core registers */
%if %M4FFloatingPointSupport='yes'
  /* Is the task using the FPU context?  If so, push high vfp registers. */
  tst r14, #0x10
  it eq
  vstmdbeq r0!, {s16-s31}

  stmdb r0!, {r4-r11, r14} /* save remaining core registers */
%else
  stmdb r0!, {r4-r11} /* save remaining core registers */
%endif

  /* Save the new top of stack into the first member of the TCB */
  str r0, [r2]

  stmdb sp!, {r3, r14}
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr basepri, r0
  bl vTaskSwitchContext
  mov r0, #0
  msr basepri, r0
  ldmia sp!, {r3, r14}

  /* The first item in pxCurrentTCB is the task top of stack. */
  ldr r1, [r3]
  ldr r0, [r1] /* r0 points now to the top-of-stack of the new task */

  /* Pop the registers. */
%if %M4FFloatingPointSupport='yes'
  ldmia r0!, {r4-r11, r14} /* Pop the core registers */
  /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
  tst r14, #0x10
  it eq
  vldmiaeq r0!, {s16-s31}
%else
  ldmia r0!, {r4-r11} /* Pop the core registers */
%endif

  msr psp, r0
  bx r14
  nop
%endif %- FSL ARM Compiler */
/*-----------------------------------------------------------*/
vPortSetInterruptMask:
%if (%Compiler = "IARARM")
#if 0
  push {r0}
  movs r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
/* \todo: !!! IAR does not allow msr BASEPRI, r0 in vPortSetInterruptMask()? */
  msr BASEPRI, r0
  pop {r0}
#else
  cpsid i  /* disable interrupts */
#endif
  bx r14
  nop
%else %- FSL ARM
  push {r0}
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr BASEPRI, r0
  pop {r0}
  bx r14
  nop
%endif
/*-----------------------------------------------------------*/
vPortClearInterruptMask:
%if (%Compiler = "IARARM")
#if 0
  push {r0}
  movs r0, #0
/* \todo: !!! IAR does not allow msr BASEPRI, r0 in vPortSetInterruptMask()? */
  msr BASEPRI, R0
  pop {r0}
#else
  cpsie i   /* enable interrupts */
#endif
  bx r14
  nop
%else %- FSL ARM
  push {r0}
  mov r0, #0
  msr BASEPRI, R0
  pop {r0}
  bx r14
  nop
%endif
/*-----------------------------------------------------------*/
%if (%Compiler = "IARARM")
vPortSVCHandler:
  /* \todo Check stack!!! */
#if FREERTOS_CPU_CORTEX_M==4 /* Cortex M4 */
    ldr r3, pxCurrentTCBConst2  /* Restore the context. */
    ldr r1, [r3]                /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    ldr r0, [r1]                /* The first item in pxCurrentTCB is the task top of stack. */
    /* pop the core registers */
    %if %M4FFloatingPointSupport='yes'
    ldmia r0!, {r4-r11, r14}
    %else
    ldmia r0!, {r4-r11}
    %endif
    msr psp, r0
    mov r0, #0
    msr basepri, r0
    %if %M4FFloatingPointSupport='no'
    orr r14, r14, #13
    %endif
    bx r14
    nop
#else /* Cortex M0+ */
    ldr r3, =pxCurrentTCB       /* Restore the context. */
    ldr r1, [r3]                /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    ldr r0, [r1]                /* The first item in pxCurrentTCB is the task top of stack. */
    adds r0, r0, #16            /* Move to the high registers. */
    ldmia r0!, {r4-r7}          /* Pop the high registers. */
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7

    msr psp, r0                 /* Remember the new top of stack for the task. */

    subs r0, r0, #32            /* Go back for the low registers that are not automatically restored. */
    ldmia r0!, {r4-r7}          /* Pop low registers.  */
    mov r1, r14                 /* OR R14 with 0x0d. */
    movs r0, #0x0d
    orrs r1, r0
    bx r1
    nop
#endif
%else
vPortSVCHandler:
%if (defined(PEversionDecimal) && (PEversionDecimal >=0 '1282')) %- this is only supported with MCU 10.3
%else %- up to MCU10.2
%if %CompilerOptimizationLevel='0'
  /* compiler optimization level 0 */
  pop {lr,r3}  /* remove stack frame for the call from Cpu.c to Events.c */
  pop {lr,r3}  /* remove stack frame for the call from Events.c to here */
%else
  /* Compiler optimization level 1, 2, 3 or 4: nothing special to do */
%endif
%endif %- MCU10.3
  ldr r3, =pxCurrentTCB
  ldr r1, [r3]
  ldr r0, [r1] /* r0 points now to top-of-stack of the new task */

  /* pop the core registers */
%if %M4FFloatingPointSupport='yes'
  ldmia r0!, {r4-r11, r14}
%else
  ldmia r0!, {r4-r11}
%endif
  msr psp, r0
  mov r0, #0
  msr basepri, r0
%if %M4FFloatingPointSupport='no'
  orr r14, r14, #13
%endif
  bx r14
  nop
%endif %- compiler
/*-----------------------------------------------------------*/
vPortStartFirstTask:
  /* Use the Vector Table Offset Register to locate the stack. */
  ldr r0, =VECTOR_TABLE_OFFSET_REG  /* (VTOR) 0xE000ED08 */
  ldr r0, [r0]
  ldr r0, [r0]
  /* Set the msp back to the start of the stack. */
  msr msp, r0
  cpsie i /* globally enable interrupts */
  /* Call SVC to start the first task. */
  svc 0
  nop
/*-----------------------------------------------------------*/
%if %M4FFloatingPointSupport='yes'
vPortEnableVFP:
  /* The FPU enable bits are in the CPACR. */
  ldr.w r0, =COPROCESSOR_ACCESS_REGISTER /* CAPCR, 0xE000ED88 */
  ldr r1, [r0]  /* read CAPR */

  /* Enable CP10 and CP11 coprocessors, then save back. */
  orr r1, r1, #(0xf<<20)
  str r1, [r0]   /* wait for store to complete */

  bx  r14
  nop
/*-----------------------------------------------------------*/
%endif
%if (%Compiler = "IARARM")
  END
%endif
%else
; file is intentionally empty as not needed for this FreeRTOS port
%endif
%endif %- %Compiler = "GNUC"

