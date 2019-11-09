/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSHELLUARTCONFIG_H_
#define MCUSHELLUARTCONFIG_H_

/* UART configuration items */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #include "fsl_usart.h"
  #define McuShellUart_CONFIG_UART_DEVICE                   USART0
  #define McuShellUart_CONFIG_UART_SET_UART_CLOCK()         CLOCK_Select(kUART0_Clk_From_MainClk) /* Select the main clock as source clock of USART0. */
  #define McuShellUart_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define McuShellUart_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxReady|kUSART_HardwareOverrunFlag)
  #define McuShellUart_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define McuShellUart_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable)
  #define McuShellUart_CONFIG_UART_IRQ_NUMBER               USART0_IRQn
  #define McuShellUart_CONFIG_UART_INIT                     USART_Init
  #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              USART0_IRQHandler
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FX512 */
  #include "fsl_uart.h"
  #define McuShellUart_CONFIG_UART_DEVICE                   UART0
  #define McuShellUart_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuShellUart_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuShellUart_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuShellUart_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuShellUart_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define McuShellUart_CONFIG_UART_IRQ_NUMBER               UART0_RX_TX_IRQn
  #define McuShellUart_CONFIG_UART_INIT                     UART_Init
  #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
#else
  /* you have to put your config here */
#endif

#ifndef McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH
  #define McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH    (64)
#endif

#ifndef McuShellUart_CONFIG_UART_BAUDRATE
  #define McuShellUart_CONFIG_UART_BAUDRATE           38400
#endif

#endif /* MCUSHELLUARTCONFIG_H_ */
