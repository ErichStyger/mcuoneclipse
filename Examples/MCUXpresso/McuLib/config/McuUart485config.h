/*
 * Copyright (c) 2020-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUUART485CONFIG_H_
#define MCUUART485CONFIG_H_

#include "McuLib.h"

#ifndef McuUart485_CONFIG_USE_RS_485
  #define McuUart485_CONFIG_USE_RS_485  (0)
    /*!< by default, this module is disabled */
#endif

#if McuUart485_CONFIG_USE_RS_485
/* UART configuration items */
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #include "fsl_usart.h"
  #define McuUart485_CONFIG_UART_DEVICE                   USART1
  #define McuUart485_CONFIG_UART_SET_UART_CLOCK()         CLOCK_Select(kUART1_Clk_From_MainClk) /* Select the main clock as source clock of USART0. */
  #define McuUart485_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define McuUart485_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define McuUart485_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxReady|kUSART_HardwareOverrunFlag)
  #define McuUart485_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define McuUart485_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable)
  #define McuUart485_CONFIG_UART_IRQ_NUMBER               USART1_IRQn
  #define McuUart485_CONFIG_UART_INIT                     USART_Init
  #define McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define McuUart485_CONFIG_UART_IRQ_HANDLER              USART1_IRQHandler
  #define McuUart485_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags
#elif McuLib_CONFIG_CPU_IS_KINETIS

#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FX
  #include "fsl_uart.h"
  #define McuUart485_CONFIG_UART_DEVICE                   UART0
  #define McuUart485_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuUart485_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuUart485_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuUart485_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuUart485_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuUart485_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define McuUart485_CONFIG_UART_IRQ_NUMBER               UART0_RX_TX_IRQn
  #define McuUart485_CONFIG_UART_INIT                     UART_Init
  #define McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_MainClk
  #define McuUart485_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define McuUart485_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
  #include "fsl_uart.h"
  #define McuUart485_CONFIG_UART_DEVICE                   UART1
  #define McuUart485_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuUart485_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuUart485_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuUart485_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuUart485_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuUart485_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable | kUART_RxFifoOverflowInterruptEnable)
  #define McuUart485_CONFIG_UART_IRQ_NUMBER               UART1_RX_TX_IRQn
  #define McuUart485_CONFIG_UART_INIT                     UART_Init
  #define McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_McgFllClk
  #define McuUart485_CONFIG_UART_IRQ_HANDLER              UART1_RX_TX_IRQHandler
  #define McuUart485_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
  #include "fsl_uart.h"
  #define McuUart485_CONFIG_UART_DEVICE                   UART0
  #define McuUart485_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuUart485_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuUart485_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuUart485_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuUart485_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuUart485_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable | kUART_RxFifoOverflowInterruptEnable)
  #define McuUart485_CONFIG_UART_IRQ_NUMBER               UART0_RX_TX_IRQn
  #define McuUart485_CONFIG_UART_INIT                     UART_Init
  #define McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_PllFllSelClk
  #define McuUart485_CONFIG_UART_IRQ_HANDLER              UART0_RX_TX_IRQHandler
  #define McuUart485_CONFIG_CLEAR_STATUS_FLAGS            UART_ClearStatusFlags
#endif

#elif McuLib_CONFIG_CPU_IS_ESP32
 #include "driver/uart.h"
 #define McuUart485_CONFIG_UART_DEVICE                    UART_NUM_2
 #define McuUart485_CONFIG_TXD_PIN                        GPIO_NUM_4
 #define McuUart485_CONFIG_RXD_PIN                        GPIO_NUM_5
 #define McuUart485_CONFIG_RTS_PIN                       (GPIO_NUM_26) /* RTS for RS485 Half-Duplex Mode manages DE/~RE */
 #define McuUart485_CONFIG_ECHO_TEST_CTS                 (UART_PIN_NO_CHANGE) /* CTS (~RE) is always on to detect collisions */

#else
  /* you have to put your config here */
#endif

#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #define McuUart485_CONFIG_HAS_FIFO  (0)  /* no FIFO support on LPC845 */
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define McuUart485_CONFIG_HAS_FIFO  (1)  /* UART0 on Kinetis has FIFO */
#elif McuLib_CONFIG_CPU_IS_ESP32
  #define McuUart485_CONFIG_HAS_FIFO  (0)  /* no FIFO support on ESP32 */
#endif

#ifndef McuUart485_CONFIG_UART_RX_QUEUE_LENGTH
  #define McuUart485_CONFIG_UART_RX_QUEUE_LENGTH         (3*1024)
    /*!< Queue length to buffer incoming data and messages */
#endif

#ifndef McuUart485_CONFIG_UART_RESPONSE_QUEUE_LENGTH
  #define McuUart485_CONFIG_UART_RESPONSE_QUEUE_LENGTH   (96)
    /*!< Queue length to check the OK from the other side */
#endif

#ifndef McuUart485_CONFIG_UART_BAUDRATE
  #define McuUart485_CONFIG_UART_BAUDRATE           115200
#endif

#ifndef McuUart485_CONFIG_USE_HW_OE_RTS
  #if McuLib_CONFIG_CPU_IS_KINETIS || (McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845)
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (1)  /* 1: Use e.g. on LPC845 OESEL (Output Enable Selection) feature. Note that the pin has to be configured in the PinMuxing as RTS! */
  #elif McuLib_CONFIG_CPU_IS_ESP32
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (0)
  #endif
#endif

#if !McuUart485_CONFIG_USE_HW_OE_RTS
  /* RTS pin to enable Tx mode on transceiver (HIGH active) */
  #if McuLib_CONFIG_CPU_IS_KINETIS /* default for Kinetis */
    #ifndef McuUart485_CONFIG_TX_EN_GPIO
      #define McuUart485_CONFIG_TX_EN_GPIO       GPIOC
    #endif
    #ifndef McuUart485_CONFIG_TX_EN_PORT
      #define McuUart485_CONFIG_TX_EN_PORT       PORTC
    #endif
    #ifndef McuUart485_CONFIG_TX_EN_PIN
      #define McuUart485_CONFIG_TX_EN_PIN        2U
    #endif
  #elif McuLib_CONFIG_CPU_IS_ESP32 /* default for ESP32 */
    #ifndef McuUart485_CONFIG_RE_PIN
      #define McuUart485_CONFIG_RE_PIN           (GPIO_NUM_23) /* ~RE_ESP32 pin: IO23, RE (Receiver Enable) is low active */
    #endif
  #endif
#endif
#endif /* McuUart485_CONFIG_USE_RS_485 */

#endif /* MCUUART485CONFIG_H_ */
