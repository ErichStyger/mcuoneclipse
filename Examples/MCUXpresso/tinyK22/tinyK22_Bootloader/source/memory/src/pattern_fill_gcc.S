////////////////////////////////////////////////////////////////////////////////
//! \addtogroup rom_loader
//! @{
//!
//! Copyright (c) 2006-2015 Freescale Semiconductor, Inc.
//! All rights reserved.
//!
//! SPDX-License-Identifier: BSD-3-Clause
//!
//! \file    ldr_fill.asm
//! \brief   Fast ARM assembler implementation of boot fill command.
//!
////////////////////////////////////////////////////////////////////////////////

    .syntax unified
    .arch armv6-m

    .section .pattern_fill, "a"
    .align 2
    .globl pattern_fill
    .text
    .thumb
    .thumb_func
    .align 2
    .type pattern_fill, %function

// FUNCTION: int pattern_fill( u32 addr, u32 pattern, u32 byteCount, bool allowMultiword )
//           Fills memory with 32bit pattern in r1 starting at (any alignment)
//           address in r0 for a length of r2 bytes.
// Inputs:
//  r0 destination address
//  r1 32bit fill pattern
//  r2 number of bytes to fill
//  r3 pass 1 to use multiword stores
//
// Outputs:
//  r0 = 0  SUCCESS
//  r0 = 1  FAIL
//
// Registers USED:  r0 - r7

pattern_fill:

            // basic parameter checks 

            cmp     r2, #0        // anything to do?
            bne     _pass

            // fail
            movs    r0, #1        // FAIL
            bx      lr

_pass:
            // do it to it...

            push    {r4-r7}
            
            mov     r7, r3      // copy allowMultiword param to r7
            mov     r3, r0      // copy destination addres to r3

            movs    r4, #3
            ands    r3, r4    // address word aligned?
            cmp     r3, #0
            beq     do_words
            
            //rsb     r3, r3, #4
            movs    r4, #4
            subs    r3, r4, r3

            // if we are here, r3 has count of byte stores we need to do
            // to get into 32bit alignment....

do_bytes:    // store 1 byte at address in r0     
            strb   r1, [r0] //, #1
            adds   r0, #1
//            movs   r1, r1 ROR r4
            movs   r4, #8
            rors   r1, r1, r4

            // check if we are done
            subs   r2, r2, #1
            beq    done
           
            // check for need of another byte store
            subs   r3, r3, #1
            bne    do_bytes

            // at least 4 bytes left?
do_words:   cmp    r2, #4
            blt    trailing_bytes
            beq    try_4

            // 5 or more bytes...
            
            // check if multiword stores are allowed
            // if not, skip 16-, 12- and 8-byte writes
            cmp    r7, #0
            beq    try_4

            // copy pattern into extra registers
            mov    r4, r1
            mov    r5, r1
            mov    r6, r1

            // store (possibly rotated) 32bits word(s)

            // try for 16 bytes
try_16:     cmp    r2, #16
            blt    try_12
            stmia  r0!, {r1,r4,r5,r6}
            subs   r2, r2, #16
            b      try_16

            // try for 12 bytes
try_12:     cmp    r2, #12
            blt    try_8
            stmia  r0!, {r1,r4,r5}
            subs   r2, r2, #12
            b      try_12

            // try for 8 bytes
try_8:      cmp    r2, #8
            blt    try_4
            stmia  r0!, {r1,r4}
            subs   r2, r2, #8
            b      try_8

            // try for 4 bytes
try_4:      cmp    r2, #4
            blt    trailing_bytes
            str    r1, [r0] //, #4
            adds   r0, #4
            subs   r2, r2, #4
            b      try_4

trailing_bytes:  // anything left?
            cmp    r2, #0
            beq    done

            // 1-3 byte stores needed
            strb   r1, [r0] //, #1
            adds    r0, #1
//            mov    r1, r1 ROR #8
            movs    r4, #8
            rors    r1, r1, r4

            // check if we are done
            subs   r2, r2, #1
            bne    trailing_bytes

done:       pop    {r4-r7}
            movs   r0, #0   // SUCCESS
            bx     lr


            .end

// eof ldr_fill.arm
//! @}
