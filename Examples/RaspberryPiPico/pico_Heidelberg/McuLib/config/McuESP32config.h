/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUESP32CONFIG_H_
#define MCUESP32CONFIG_H_

#ifndef McuESP32_CONFIG_USE_USB_CDC
  #define McuESP32_CONFIG_USE_USB_CDC (0)
  /*!< 1: using USB CDC gateway for programming; 0: do not use USB CDC */
#endif

#ifndef McuESP32_CONFIG_USE_CTRL_PINS
  #define McuESP32_CONFIG_USE_CTRL_PINS  (0)
    /*!< 1: Using RST and BL signals to load software; 0: only using the UART */
#endif

#ifndef McuESP32_CONFIG_VERBOSE_CONTROL_SIGNALS
  #define McuESP32_CONFIG_VERBOSE_CONTROL_SIGNALS   (0 && McuESP32_CONFIG_USE_CTRL_PINS)
    /* if status of control signals shall be printed on McuLog channel */
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
  /* control signal pin definition */
  #ifndef McuESP32_CONFIG_EN_GPIO
    #define McuESP32_CONFIG_EN_GPIO  GPIOA
  #endif
  #ifndef McuESP32_CONFIG_EN_PORT
    #define McuESP32_CONFIG_EN_PORT  PORTA
  #endif
  #ifndef McuESP32_CONFIG_EN_PIN
    #define McuESP32_CONFIG_EN_PIN   12
  #endif

  #ifndef McuESP32_CONFIG_RST_GPIO
    #define McuESP32_CONFIG_RST_GPIO  GPIOA
  #endif
  #ifndef McuESP32_CONFIG_RST_PORT
    #define McuESP32_CONFIG_RST_PORT  PORTA
  #endif
  #ifndef McuESP32_CONFIG_RST_PIN
    #define McuESP32_CONFIG_RST_PIN   5
  #endif
#endif

#include "McuShellUartconfig.h"

/* UART used with ESP32: assign one of the McuShell UART to enable it */
#ifndef McuESP32_CONFIG_SHELL_UART
  #define McuESP32_CONFIG_SHELL_UART      McuShellUart_CONFIG_UART_NONE
#endif

/* UART connection to the ESP32 */
#if   (McuESP32_CONFIG_SHELL_UART==McuShellUart_CONFIG_UART_K22FX512_UART1_E1_E0)  \
   || (McuESP32_CONFIG_SHELL_UART==McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0)
  #include "fsl_uart.h"
  #define McuESP32_CONFIG_UART_DEVICE                   UART1
  #define McuESP32_CONFIG_UART_SET_UART_CLOCK()         /* nothing needed */
  #define McuESP32_CONFIG_UART_WRITE_BLOCKING           UART_WriteBlocking
  #define McuESP32_CONFIG_UART_GET_FLAGS                UART_GetStatusFlags
  #define McuESP32_CONFIG_UART_HW_RX_READY_FLAGS        (kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)
  #define McuESP32_CONFIG_UART_READ_BYTE                UART_ReadByte
  #define McuESP32_CONFIG_UART_CONFIG_STRUCT            uart_config_t
  #define McuESP32_CONFIG_UART_GET_DEFAULT_CONFIG       UART_GetDefaultConfig
  #define McuESP32_CONFIG_UART_ENABLE_INTERRUPTS        UART_EnableInterrupts
  #define McuESP32_CONFIG_UART_ENABLE_INTERRUPT_FLAGS   (kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable)
  #define McuESP32_CONFIG_UART_IRQ_NUMBER               UART1_RX_TX_IRQn
  #define McuESP32_CONFIG_UART_INIT                     UART_Init
  #define McuESP32_CONFIG_UART_GET_CLOCK_FREQ_SELECT    kCLOCK_CoreSysClk
  #define McuESP32_CONFIG_UART_IRQ_HANDLER              UART1_RX_TX_IRQHandler
  #define McuESP32_CONFIG_UART_BAUDRATE                 115200
#endif

#endif /* MCUESP32CONFIG_H_ */
