/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


//         AREA   Crt0, CODE, READONLY      ; name this block of code
        .syntax unified
        .arch armv7-m
        
        .section .Reset_Handler, "a"
        .align 2
        .globl Reset_Handler
        .text
        .thumb
        .thumb_func

        .extern SystemInit
        .extern init_data_bss
        .extern main
        .extern __StackTop
        .extern init_interrupts

        .extern __isr_vector


#define SCS_BASE            (0xE000E000)                            /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00)                    /*!< System Control Block Base Address */
#define SCB_VTOR_OFFSET     (0x00000008)

Reset_Handler:

        // Mask interrupts
        cpsid   i

        // Set VTOR register in SCB first thing we do.
        ldr     r0,=__isr_vector
        ldr     r1,=SCB_BASE
        str     r0,[r1, #SCB_VTOR_OFFSET]

        // Init the rest of the registers
        ldr     r2,=0
        ldr     r3,=0
        ldr     r4,=0
        ldr     r5,=0
        ldr     r6,=0
        ldr     r7,=0
        mov     r8,r7
        mov     r9,r7
        mov     r10,r7
        mov     r11,r7
        mov     r12,r7

        // Initialize the stack pointer
        ldr     r0,=__StackTop
        mov     r13,r0

        // Call the CMSIS system init routine
        ldr     r0,=SystemInit
        blx     r0

        // Init .data and .bss sections
        ldr     r0,=init_data_bss
        blx     r0

        // Init interrupts
        ldr     r0,=init_interrupts
        blx     r0

        // Unmask interrupts
        cpsie   i

        // Set argc and argv to NULL before calling main().
        ldr     r0,=0
        ldr     r1,=0
        ldr     r2,=main
        blx     r2

__done:
        b       __done



       .end

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
