/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RS485UARTCONFIG_H_
#define RS485UARTCONFIG_H_

#include "platform.h"

#define RS485Uart_CONFIG_USE_HW_OE_RTS  (1)  /* 1: Use e.g. on LPC845 OESEL (Output Enable Selection) feature. Note that the pin has to be configured in the PinMuxing as RTS! */

/* UART configuration items */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #include "fsl_usart.h"
#if PL_CONFIG_IS_CLIENT
  #define RS485Uart_CONFIG_UART_DEVICE                   USART0
  #define RS485Uart_CONFIG_UART_SET_UART_CLOCK()         CLOCK_Select(kUART0_Clk_From_MainClk) /* Select the main clock as source clock of USART0. */
  #define RS485Uart_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define RS485Uart_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxReady|kUSART_HardwareOverrunFlag)
  #define RS485Uart_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define RS485Uart_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define RS485Uart_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable)
  #define RS485Uart_CONFIG_UART_IRQ_NUMBER               USART0_IRQn
  #define RS485Uart_CONFIG_UART_INIT                     USART_Init
  #define RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define RS485Uart_CONFIG_UART_IRQ_HANDLER              USART0_IRQHandler
  #define RS485Uart_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags
#elif PL_CONFIG_IS_MASTER
  #define RS485Uart_CONFIG_UART_DEVICE                   USART1
  #define RS485Uart_CONFIG_UART_SET_UART_CLOCK()         CLOCK_Select(kUART1_Clk_From_MainClk) /* Select the main clock as source clock of USART0. */
  #define RS485Uart_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define RS485Uart_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxReady|kUSART_HardwareOverrunFlag)
  #define RS485Uart_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define RS485Uart_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define RS485Uart_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable)
  #define RS485Uart_CONFIG_UART_IRQ_NUMBER               USART1_IRQn
  #define RS485Uart_CONFIG_UART_INIT                     USART_Init
  #define RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define RS485Uart_CONFIG_UART_IRQ_HANDLER              USART1_IRQHandler
  #define RS485Uart_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags
#endif
#elif McuLib_CONFIG_CPU_IS_KINETIS

#if 0 /* K22FX512 */
  #include "fsl_uart.h"
  #define RS485Uart_CONFIG_UART_DEVICE                   UART0
  #define RS485Uart_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define RS485Uart_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define RS485Uart_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define RS485Uart_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define RS485Uart_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define RS485Uart_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define RS485Uart_CONFIG_UART_IRQ_NUMBER               UART0_RX_TX_IRQn
  #define RS485Uart_CONFIG_UART_INIT                     UART_Init
  #define RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define RS485Uart_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define RS485Uart_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif 1 /* K22FN512 */
  #include "fsl_uart.h"
  #define RS485Uart_CONFIG_UART_DEVICE                   UART0
  #define RS485Uart_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define RS485Uart_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define RS485Uart_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define RS485Uart_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define RS485Uart_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define RS485Uart_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define RS485Uart_CONFIG_UART_IRQ_NUMBER               UART0_RX_TX_IRQn
  #define RS485Uart_CONFIG_UART_INIT                     UART_Init
  #define RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_PllFllSelClk
  #define RS485Uart_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define RS485Uart_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#endif

#else
  /* you have to put your config here */
#endif

#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #define RS485Uart_CONFIG_HAS_FIFO  (0)
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define RS485Uart_CONFIG_HAS_FIFO  (1)  /* UART0 on Kinetis has FIFO which needs to be disabled in the code */
#endif

#ifndef RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH
  #if PL_CONFIG_IS_MASTER
    #define RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH        (3*1024)
  #elif PL_CONFIG_IS_CLIENT
    #define RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH        (128)
  #endif
  #define RS485Uart_CONFIG_UART_RESPONSE_QUEUE_LENGTH    (128)
#endif

#ifndef RS485Uart_CONFIG_UART_BAUDRATE
  #define RS485Uart_CONFIG_UART_BAUDRATE           115200
#endif

#endif /* RS485UARTCONFIG_H_ */
