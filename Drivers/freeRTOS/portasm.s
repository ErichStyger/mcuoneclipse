%if ((%configCOMPILER='automatic') & (%Compiler == "GNUC")) | (%configCOMPILER='configCOMPILER_ARM_GCC')
/* file is intentionally empty as not needed for this FreeRTOS port */
%endif %- ARM gcc compiler
%---------------------------------------------------------------------------------------
%if ((%configCOMPILER='automatic') & (%Compiler=="ARM_CC")) | (%configCOMPILER='configCOMPILER_ARM_KEIL')
	AREA ARMEex, CODE, READONLY
dummy    ; dummy label, will not be used
	nop  ; just doing a nop
	END  ; mark end of file
%endif %- Keil ARM Compiler
%---------------------------------------------------------------------------------------
%if ((%configCOMPILER='automatic') & ((%Compiler="CodeWarriorColdFireV1")|(%Compiler="CodeWarriorMCF"))) | ((%configCOMPILER='configCOMPILER_CF1_FSL')|(%configCOMPILER='configCOMPILER_CF2_FSL'))
/*
 * CodeWarrior V1 and V2 Compiler
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
%endif %- Coldfire V1 and V2
%-*****************************************************************************************************
%if ((%configCOMPILER='automatic') & (%Compiler="configCOMPILER_ARM_IAR")) | (%configCOMPILER='configCOMPILER_ARM_IAR')
/* IAR ARM Compiler */
#include "FreeRTOSConfig.h"

#define VECTOR_TABLE_OFFSET_REG     0xE000ED08 /* Vector Table Offset Register (VTOR) */
%if %M4FFloatingPointSupport='yes'
#define COPROCESSOR_ACCESS_REGISTER 0xE000ED88 /* Coprocessor Access Register (CPACR) */
%endif

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
/*-----------------------------------------------------------*/
vOnCounterRestart:
  /* caller did this:
     push {r7,LR}
     bl vOnCounterRestart
     pop {r0,pc} */
  pop {r0, r7} /* restore r7 and lr into r0 and r7, which were pushed in caller */
  push {r0, r7}
%if %UsePreemption='yes'
  /* If using preemption, also force a context switch. */
  bl vPortYieldFromISR
%endif
  bl vPortSetInterruptMask /* disable interrupts */
  bl xTaskIncrementTick    /* increment tick count, might schedule a task */
  bl vPortClearInterruptMask /* enable interrupts again */

  pop {r7,pc}  /* start exit sequence from interrupt: r7 and lr where pushed above */
  nop
/*-----------------------------------------------------------*/
vSetMSP:
  msr msp, r0
  bx lr
  nop
/*-----------------------------------------------------------*/
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
/*-----------------------------------------------------------*/
vPortSetInterruptMask:
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
/*-----------------------------------------------------------*/
vPortClearInterruptMask:
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
/*-----------------------------------------------------------*/
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
  END
%endif %- IAR aRM
%-*****************************************************************************************************
%if ((%configCOMPILER='automatic') & (%Compiler="configCOMPILER_ARM_FSL")) | (%configCOMPILER='configCOMPILER_ARM_FSL')
/* legacy Freescale ARM compiler */
#include "FreeRTOSConfig.h"

#define VECTOR_TABLE_OFFSET_REG     0xE000ED08 /* Vector Table Offset Register (VTOR) */
%if %M4FFloatingPointSupport='yes'
#define COPROCESSOR_ACCESS_REGISTER 0xE000ED88 /* Coprocessor Access Register (CPACR) */
%endif

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
/*-----------------------------------------------------------*/
vOnCounterRestart:
  %if %CompilerOptimizationLevel='0'
  /* Compiler optimization level 0 */
  pop {lr,r3} /* remove stacked registers from the caller routine */
  %else
  /* Compiler optimization level 1, 2, 3 or 4 */
  push {lr} /* need to save link register, it will be overwritten below */
  %endif
%if %UsePreemption='yes'
  /* If using preemption, also force a context switch. */
  bl vPortYieldFromISR
%endif
  bl vPortSetInterruptMask /* disable interrupts */
  bl xTaskIncrementTick    /* increment tick count, might schedule a task */
  bl vPortClearInterruptMask /* enable interrupts again */
  %if %CompilerOptimizationLevel='0'
  /* Compiler optimization level 0 */
  pop {lr,r4} /* start exit sequence from interrupt: r4 and lr where pushed in the ISR */
  %else
  /* Compiler optimization level 1, 2, 3 or 4 */
  pop {lr}    /* restore pushed lr register */
  %endif
  bx lr
  nop
/*-----------------------------------------------------------*/
vSetMSP:
  msr msp, r0
  bx lr
  nop
/*-----------------------------------------------------------*/
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
/*-----------------------------------------------------------*/
vPortSetInterruptMask:
  push {r0}
  mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
  msr BASEPRI, r0
  pop {r0}
  bx r14
  nop
/*-----------------------------------------------------------*/
vPortClearInterruptMask:
  push {r0}
  mov r0, #0
  msr BASEPRI, R0
  pop {r0}
  bx r14
  nop
/*-----------------------------------------------------------*/
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

%endif %- legacy FSL ARM Compiler


