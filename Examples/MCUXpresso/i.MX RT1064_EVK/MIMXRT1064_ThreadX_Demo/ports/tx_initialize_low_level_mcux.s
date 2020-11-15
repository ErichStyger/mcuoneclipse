/*
 * Copyright 2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

    .global     _tx_initialize_unused_memory
    .global     _tx_timer_interrupt
    .global     _pvHeapLimit
    .global     systick_cycles

    .text 32
    .align 4
    .syntax unified

    .global  _tx_initialize_low_level
    .thumb_func
_tx_initialize_low_level:
    /* Set base of available memory to end of non-initialised RAM area. */
    LDR     r0, =_tx_initialize_unused_memory
    LDR     r1, =_pvHeapLimit
    ADD     r1, r1, #4
    STR     r1, [r0]

    /* Enable the cycle count register.  */
    LDR     r0, =0xE0001000
    LDR     r1, [r0]
    ORR     r1, r1, #1
    STR     r1, [r0]

    /* Configure SysTick. */
    MOV     r0, #0xE000E000
    LDR     r1, =systick_cycles
    LDR     r1, [r1]
    STR     r1, [r0, #0x14]
    MOV     r1, #0x7
    STR     r1, [r0, #0x10]

    /* Configure handler priorities.  */
    LDR     r1, =0x00000000
    STR     r1, [r0, #0xD18]

    LDR     r1, =0xFF000000
    STR     r1, [r0, #0xD1C]

    LDR     r1, =0x40FF0000
    STR     r1, [r0, #0xD20]

    BX      lr

/* System Tick timer interrupt handler. */
    .global  SysTick_Handler
    .thumb_func
SysTick_Handler:
    PUSH    {r0, lr}
    BL      _tx_timer_interrupt
    POP     {r0, lr}
    BX      LR
