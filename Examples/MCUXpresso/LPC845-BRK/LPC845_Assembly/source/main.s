/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* ----------- Main ------------------------------*/
.text
.global main
main:
  nop
  b main

/* ----------- Reset ------------------------------*/
.text
.global ResetISR,
.section .text

ResetISR:
  nop  @ just do something....
  b main

/* ----------- Interrupt Handlers ------------------------------*/
isr_default:
  b isr_default

M0_NMI_Handler:
  b M0_NMI_Handler

M0_HardFault_Handler:
  b M0_HardFault_Handler

isr_handler:
  @ Handle the interrupt here
  bx lr  @ Return from the interrupt

/* ----------- Vector table ------------------------------*/
.section .isr_vector, "a"
.align 4

.global vector_table
.global M0_NMI_Handler, M0_HardFault_Handler
.global __valid_user_code_checksum /* LPC ROM Library function */
.type vector_table, %object

vector_table:
   .word top_of_stack   @ Entry 0: Initial stack pointer
   .word ResetISR  @ Entry 0: Reset
   .word M0_NMI_Handler  @ Entry 1: NMI
   .word M0_HardFault_Handler  @ Entry 2: HardFault
   .word 0  @ Entry 3: ...
   .word 0  @ Entry 4: ...
   .word 0  @ Entry 5: ...
   .word __valid_user_code_checksum @ Entry 6: ...
   .word 0
   .word 0
   .word 0
   .word isr_default @ SVC
   .word 0
   .word 0
   .word isr_default @ PendSV
   .word isr_default @ SysTick
   @ Chip level
   .word isr_default @  SPI0_IRQHandler,             // 16: SPI0 interrupt
   .word isr_default @  SPI1_IRQHandler,             // 17: SPI1 interrupt
   .word isr_default @  DAC0_IRQHandler,             // 18: DAC0 interrupt
   .word isr_default @  USART0_IRQHandler,           // 19: USART0 interrupt
   .word isr_default @  USART1_IRQHandler,           // 20: USART1 interrupt
   .word isr_default @  USART2_IRQHandler,           // 21: USART2 interrupt
   .word isr_default @  Reserved22_IRQHandler,       // 22: Reserved interrupt
   .word isr_default @  I2C1_IRQHandler,             // 23: I2C1 interrupt
   .word isr_default @  I2C0_IRQHandler,             // 24: I2C0 interrupt
   .word isr_default @  SCT0_IRQHandler,             // 25: State configurable timer interrupt
   .word isr_default @  MRT0_IRQHandler,             // 26: Multi-rate timer interrupt
   .word isr_default @  CMP_CAPT_IRQHandler,         // 27: Analog comparator interrupt or Capacitive Touch interrupt
   .word isr_default @  WDT_IRQHandler,              // 28: Windowed watchdog timer interrupt
   .word isr_default @  BOD_IRQHandler,              // 29: BOD interrupts
   .word isr_default @  FLASH_IRQHandler,            // 30: flash interrupt
   .word isr_default @  WKT_IRQHandler,              // 31: Self-wake-up timer interrupt
   .word isr_default @  ADC0_SEQA_IRQHandler,        // 32: ADC0 sequence A completion.
   .word isr_default @  ADC0_SEQB_IRQHandler,        // 33: ADC0 sequence B completion.
   .word isr_default @  ADC0_THCMP_IRQHandler,       // 34: ADC0 threshold compare and error.
   .word isr_default @  ADC0_OVR_IRQHandler,         // 35: ADC0 overrun
   .word isr_default @  DMA0_IRQHandler,             // 36: DMA0 interrupt
   .word isr_default @  I2C2_IRQHandler,             // 37: I2C2 interrupt
   .word isr_default @  I2C3_IRQHandler,             // 38: I2C3 interrupt
   .word isr_default @  CTIMER0_IRQHandler,          // 39: Timer interrupt
   .word isr_default @  PIN_INT0_IRQHandler,         // 40: Pin interrupt 0 or pattern match engine slice 0 interrupt
   .word isr_default @  PIN_INT1_IRQHandler,         // 41: Pin interrupt 1 or pattern match engine slice 1 interrupt
   .word isr_default @  PIN_INT2_IRQHandler,         // 42: Pin interrupt 2 or pattern match engine slice 2 interrupt
   .word isr_default @  PIN_INT3_IRQHandler,         // 43: Pin interrupt 3 or pattern match engine slice 3 interrupt
   .word isr_default @  PIN_INT4_IRQHandler,         // 44: Pin interrupt 4 or pattern match engine slice 4 interrupt
   .word isr_default @  PIN_INT5_DAC1_IRQHandler,    // 45: Pin interrupt 5 or pattern match engine slice 5 interrupt or DAC1 interrupt
   .word isr_default @  PIN_INT6_USART3_IRQHandler,  // 46: Pin interrupt 6 or pattern match engine slice 6 interrupt or UART3 interrupt
   .word isr_default @  PIN_INT7_USART4_IRQHandler,  // 47: Pin interrupt 7 or pattern match engine slice 7 interrupt or UART4 interrupt

/* ----------- Stack (MSP) ------------------------------*/
 .section .stack
.align 4

top_of_stack:
    .word 0x10000000+0x3fe0     @ Set the initial stack pointer to the end of the RAM

/* ------------------------------------
 * Variable to store CRP value in. Will be placed automatically by the linker when "Enable Code Read Protect" selected. */
.global CRP_WORD
.section .crp
  .align 4
  .equ CRP_WORD, 0xffffffff
