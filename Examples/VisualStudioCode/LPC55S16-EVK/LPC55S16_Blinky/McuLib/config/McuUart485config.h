/*
 * Copyright (c) 2020-2023, Erich Styger
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

#ifndef McuUart485_CONFIG_USE_MODBUS
  #define McuUart485_CONFIG_USE_MODBUS  (0)
    /*!< if using the Modbus protocol */
#endif

#ifndef McuUart485_CONFIG_USE_LOGGER
  #define McuUart485_CONFIG_USE_LOGGER  (0)
    /*!< if using a logger in the interrupt RX routine. 0: disabled; 1: enabled */
#endif

#ifndef McuUart485_CONFIG_LOGGER_CALLBACK_NAME
  #define McuUart485_CONFIG_LOGGER_CALLBACK_NAME  McuRTT_SendChar
    /*!< function name to be called to write a char from the logger inside the Rx interrupt */
#endif
extern uint8_t McuUart485_CONFIG_LOGGER_CALLBACK_NAME(uint8_t ch); /* prototype of logger function callback */

#if McuUart485_CONFIG_USE_RS_485
/* UART configuration items */
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #include "fsl_usart.h"

  #ifndef McuUart485_CONFIG_UART_PARITY
    #define McuUart485_CONFIG_UART_PARITY                 kUSART_ParityDisabled /* or kUSART_ParityEven or kUSART_ParityOdd */
  #endif

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

#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
  /* using FlexComm1, on LPC55S69-EVK this is on pin 40 (Rx, FC1_RXD_SDA_MOSI_DATA, PIO1_10) and pin 93 (Rx, FC1_TXD_SCL_MISO_WS, PIO1_11) */
  #include "fsl_usart.h"

  #ifndef McuUart485_CONFIG_UART_PARITY
    #define McuUart485_CONFIG_UART_PARITY                 kUSART_ParityDisabled /* or kUSART_ParityEven or kUSART_ParityOdd */
  #endif

  #define McuUart485_CONFIG_UART_DEVICE                   USART1
  #define McuUart485_CONFIG_UART_SET_UART_CLOCK()         CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1)
  #define McuUart485_CONFIG_UART_WRITE_BLOCKING           USART_WriteBlocking
  #define McuUart485_CONFIG_UART_GET_FLAGS                USART_GetStatusFlags
  #define McuUart485_CONFIG_UART_HW_RX_READY_FLAGS        (kUSART_RxFifoNotEmptyFlag | kUSART_RxError)
  #define McuUart485_CONFIG_UART_READ_BYTE                USART_ReadByte
  #define McuUart485_CONFIG_UART_CONFIG_STRUCT            usart_config_t
  #define McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG       USART_GetDefaultConfig
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPTS        USART_EnableInterrupts
  #define McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable)
  #define McuUart485_CONFIG_UART_IRQ_NUMBER               FLEXCOMM1_IRQn
  #define McuUart485_CONFIG_UART_INIT                     USART_Init
  #define McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_Fro12M
  #define McuUart485_CONFIG_UART_IRQ_HANDLER              FLEXCOMM1_IRQHandler
  #define McuUart485_CONFIG_CLEAR_STATUS_FLAGS            USART_ClearStatusFlags

#elif McuLib_CONFIG_CPU_IS_KINETIS
  #ifndef McuUart485_CONFIG_UART_PARITY
    #define McuUart485_CONFIG_UART_PARITY                 kUART_ParityDisabled /* or kUART_ParityEven or kUART_ParityOdd */
  #endif

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
  #ifndef McuUart485_CONFIG_UART_DEVICE
    #define McuUart485_CONFIG_UART_DEVICE                    UART_NUM_2
  #endif
  #ifndef McuUart485_CONFIG_TXD_PIN
    #define McuUart485_CONFIG_TXD_PIN                        GPIO_NUM_4
  #endif
  #ifndef McuUart485_CONFIG_RXD_PIN
    #define McuUart485_CONFIG_RXD_PIN                        GPIO_NUM_5
  #endif
  #ifndef McuUart485_CONFIG_RTS_PIN
    #define McuUart485_CONFIG_RTS_PIN                        GPIO_NUM_23 /* RTS, ~RE for RS485, managed by UART */
  #endif
  #ifndef McuUart485_CONFIG_CTS_PIN
    #define McuUart485_CONFIG_CTS_PIN                       (/*GPIO_NUM_26*//*not used*/) /* CTS, DE for RS485, but not used! RE/DE must be wired together on the hardware */
  #endif

#elif McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/uart.h"
  #ifndef McuUart485_CONFIG_UART_DEVICE
    #define McuUart485_CONFIG_UART_DEVICE                   uart1
  #endif
  #ifndef McuUart485_CONFIG_TXD_PIN
    #define McuUart485_CONFIG_TXD_PIN                       (4u)
  #endif
  #ifndef McuUart485_CONFIG_RXD_PIN
    #define McuUart485_CONFIG_RXD_PIN                       (5u)
  #endif
  #ifndef McuUart485_CONFIG_RTS_PIN
    #define McuUart485_CONFIG_RTS_PIN                       (3u) /* RTS, ~RE for RS485 */
  #endif
  #ifndef McuUart485_CONFIG_CTS_PIN
    #define McuUart485_CONFIG_CTS_PIN                       (3u) /* CTS, DE for RS485! */
  #endif
  #ifndef McuUart485_CONFIG_UART_WRITE_BLOCKING
    #define McuUart485_CONFIG_UART_WRITE_BLOCKING           uart_write_blocking
  #endif
  #ifndef McuUart485_CONFIG_UART_PARITY
    #define McuUart485_CONFIG_UART_PARITY                   UART_PARITY_NONE /* UART_PARITY_NONE, UART_PARITY_EVEN, UART_PARITY_ODD */
  #endif
  #ifndef McuUart485_CONFIG_UART_READ_BYTE
    #define McuUart485_CONFIG_UART_READ_BYTE                uart_getc
  #endif
#else
  /* you have to put your configuration here */
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
  #if McuLib_CONFIG_CPU_IS_KINETIS
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (1)  /* 1: Use e.g. on LPC845 OESEL (Output Enable Selection) feature. Note that the pin has to be configured in the PinMuxing as RTS! */
  #elif McuLib_CONFIG_CPU_IS_ESP32
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (1)  /* on ESP32, the transceiver is controlled by the UART directly with the RTS pin */
  #elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (1)  /* 1: Use e.g. on LPC845 OESEL (Output Enable Selection) feature. Note that the pin has to be configured in the PinMuxing as RTS! */
  #elif McuLib_CONFIG_CPU_IS_LPC55xx
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (0)  /* if using the RTS function of the UART or not */
  #elif McuLib_CONFIG_CPU_IS_RPxxxx
    #define McuUart485_CONFIG_USE_HW_OE_RTS  (0)  /* on RP2040, need to control RE/DE pin manually */
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
  #elif McuLib_CONFIG_CPU_IS_LPC55xx
    /* default: pin 92 on LPC55S69-EVK, routed as FC1_I2C_SCL */
    #ifndef McuUart485_CONFIG_TX_EN_GPIO
      #define McuUart485_CONFIG_TX_EN_GPIO       GPIO
    #endif
    #ifndef McuUart485_CONFIG_TX_EN_PORT
      #define McuUart485_CONFIG_TX_EN_PORT       0
    #endif
    #ifndef McuUart485_CONFIG_TX_EN_PIN
      #define McuUart485_CONFIG_TX_EN_PIN        14U
    #endif
  #elif McuLib_CONFIG_CPU_IS_ESP32 /* default for ESP32 */
    #ifndef McuUart485_CONFIG_RE_PIN
      #define McuUart485_CONFIG_RE_PIN           (McuUart485_CONFIG_CTS_PIN) /* ~DE_ESP32 pin: DE (Data Enable) is low active */
    #endif
  #elif McuLib_CONFIG_CPU_IS_RPxxxx
    #ifndef McuUart485_CONFIG_RE_PIN
      #define McuUart485_CONFIG_TX_EN_PIN        (McuUart485_CONFIG_CTS_PIN) /* ~DE_ESP32 pin: DE (Data Enable) is low active */
    #endif
  #endif
#endif
#endif /* McuUart485_CONFIG_USE_RS_485 */

#endif /* MCUUART485CONFIG_H_ */
