/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSHELLUARTCONFIG_H_
#define MCUSHELLUARTCONFIG_H_

/* supported UART implementation: */
#define McuShellUart_CONFIG_UART_NONE               (0)
#define McuShellUart_CONFIG_UART_LPC845_USART0      (1)
#define McuShellUart_CONFIG_UART_K22FX512_UART0     (2)
#define McuShellUart_CONFIG_UART_K22FN512_UART0     (3) /* PTB16 (Rx), PTB17 (Tx) */
#define McuShellUart_CONFIG_UART_K22FN512_UART1     (4)
#define McuShellUart_CONFIG_UART_K22FN512_LPUART0   (5)
#define McuShellUart_CONFIG_UART_LPC55S16_USART0    (6)

/* default UART used */
#ifndef McuShellUart_CONFIG_UART
  #define McuShellUart_CONFIG_UART      McuShellUart_CONFIG_UART_NONE
#endif

/* UART configuration items */
#if McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_NONE
  /* no UART used */
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_LPC845_USART0
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
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              USART0_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_LPC55S16_USART0
  #include "fsl_usart.h"
  #define McuShellUart_CONFIG_UART_DEVICE                   USART0
  #define McuShellUart_CONFIG_UART_SET_UART_CLOCK()         CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0)
  #define McuShellUart_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define McuShellUart_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxFifoNotEmptyFlag | kUSART_RxError)
  #define McuShellUart_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define McuShellUart_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable)
  #define McuShellUart_CONFIG_UART_IRQ_NUMBER               FLEXCOMM0_IRQn
  #define McuShellUart_CONFIG_UART_INIT                     USART_Init
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_Fro12M
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              FLEXCOMM0_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FX512_UART0
  /* UART0 on K22FX512 */
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
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_CoreSysClk
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART0
  /* UART0 on K22FN512. Mux the pins using the pins muxing tool */
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
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_CoreSysClk
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART1
  /* UART1 on K22FN512. Mux the pins using the pins muxing tool */
  #include "fsl_uart.h"
  #define McuShellUart_CONFIG_UART_DEVICE                   UART1
  #define McuShellUart_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuShellUart_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuShellUart_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuShellUart_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuShellUart_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define McuShellUart_CONFIG_UART_IRQ_NUMBER               UART1_RX_TX_IRQn
  #define McuShellUart_CONFIG_UART_INIT                     UART_Init
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_CoreSysClk
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              UART1_RX_TX_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_LPUART0
  /* LPUART on K22FN512 */
  #include "fsl_lpuart.h"
  #define McuShellUart_CONFIG_UART_DEVICE                   LPUART0
/*! LPUARTSRC - LPUART clock source select
 *  0b00..Clock disabled
 *  0b01..MCGFLLCLK , or MCGPLLCLK , or IRC48M clock as selected by SOPT2[PLLFLLSEL].
 *  0b10..OSCERCLK clock
 *  0b11..MCGIRCLK clock
 */
  #define McuShellUart_CONFIG_UART_SET_UART_CLOCK()         /*CLOCK_SetLpuartClock(1U)*/ /* do it in the clocks tool! */
  #define McuShellUart_CONFIG_UART_WRITE_BLOCKING           LPUART_WriteBlocking
  #define McuShellUart_CONFIG_UART_GET_FLAGS                LPUART_GetStatusFlags
  #define McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS        (kLPUART_RxDataRegFullFlag|kLPUART_RxOverrunFlag)
  #define McuShellUart_CONFIG_UART_READ_BYTE                LPUART_ReadByte
  #define McuShellUart_CONFIG_UART_CONFIG_STRUCT            lpuart_config_t
  #define McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG       LPUART_GetDefaultConfig
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS        LPUART_EnableInterrupts
  #define McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kLPUART_RxDataRegFullInterruptEnable)
  #define McuShellUart_CONFIG_UART_IRQ_NUMBER               LPUART0_IRQn
  #define McuShellUart_CONFIG_UART_INIT                     LPUART_Init
  #ifndef McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT
    #define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT    /* kCLOCK_Osc0ErClkUndiv */ kCLOCK_PllFllSelClk /* has to match Clocks setting! */
  #endif
  #define McuShellUart_CONFIG_UART_IRQ_HANDLER              LPUART0_IRQHandler
  #define McuShellUART_CONFIG_CLEAR_STATUS_FLAGS            LPUART_ClearStatusFlags
#else
  /* you have to put your config here */
#endif

#ifndef McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH
  #define McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH    (McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE)
#endif

#ifndef McuShellUart_CONFIG_UART_BAUDRATE
  #define McuShellUart_CONFIG_UART_BAUDRATE           115200
#endif

#endif /* MCUSHELLUARTCONFIG_H_ */
