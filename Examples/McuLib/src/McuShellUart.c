/*!
 * Copyright (c) 2020-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief \brief Implementation of the McuShellUart module.
 */

#include "McuShellUartconfig.h"
#if McuShellUart_CONFIG_UART!=McuShellUart_CONFIG_UART_NONE
#include "McuShellUart.h"
#include "McuShell.h"
#if McuShellUart_CONFIG_USE_FREERTOS
  #include "McuRTOS.h"
#else
  #include "McuRB.h"
#endif
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/uart.h"
  #include "hardware/irq.h"
  #include "hardware/gpio.h"
#endif
#include "McuLog.h"

#if McuShellUart_CONFIG_USE_FREERTOS
  static QueueHandle_t uartRxQueue;
#else
  static McuRB_Handle_t rxRingBuffer;
#endif

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
static void McuShellUart_SendChar(unsigned char ch) {
  McuShellUart_CONFIG_UART_WRITE_BLOCKING(McuShellUart_CONFIG_UART_DEVICE, &ch, 1);
}

static void McuShellUart_ReadChar(uint8_t *c) {
  uint8_t ch;

#if McuShellUart_CONFIG_USE_FREERTOS
  if (xQueueReceive(uartRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
#else
  if (McuRB_Get(rxRingBuffer, &ch)!=ERR_OK) {
    *c = '\0'; /* nothing received */
  } else {
    *c = ch; /* return received character */
  }
#endif
}

static bool McuShellUart_CharPresent(void) {
#if McuShellUart_CONFIG_USE_FREERTOS
  return uxQueueMessagesWaiting(uartRxQueue)!=0;
#else
  return McuRB_NofElements(rxRingBuffer)!=0;
#endif
}

McuShell_ConstStdIOType McuShellUart_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)McuShellUart_ReadChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)McuShellUart_SendChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)McuShellUart_SendChar,
    .keyPressed = McuShellUart_CharPresent, /* if input is not empty */
  #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
};

uint8_t McuShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/

#if McuLib_CONFIG_CPU_IS_RPxxxx
  /* nothing needed */
#else
void McuShellUart_CONFIG_UART_IRQ_HANDLER(void) {
  uint8_t data;
  uint32_t flags;
#if McuShellUart_CONFIG_USE_FREERTOS
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif
  uint8_t count;

  flags = McuShellUart_CONFIG_UART_GET_FLAGS(McuShellUart_CONFIG_UART_DEVICE);
#if McuShellUart_CONFIG_HAS_FIFO
  if (flags&kUART_RxFifoOverflowFlag) {
    count = 0; /* statement to allow debugger to set a breakpoint here */
  }
#endif
  /* If new data arrived. */
  if (flags&McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS) {
  #if McuShellUart_CONFIG_HAS_FIFO
    count = McuShellUart_CONFIG_UART_DEVICE->RCFIFO;
  #else
    count = 1;
  #endif
    while(count!=0) {
      data = McuShellUart_CONFIG_UART_READ_BYTE(McuShellUart_CONFIG_UART_DEVICE);
  #if McuShellUart_CONFIG_USE_FREERTOS
      (void)xQueueSendFromISR(uartRxQueue, &data, &xHigherPriorityTaskWoken);
  #else
      McuRB_Put(rxRingBuffer, &data);
  #endif
      count--;
    }
  }
  McuShellUART_CONFIG_CLEAR_STATUS_FLAGS(McuShellUart_CONFIG_UART_DEVICE, flags|McuShellUART_CONFIG_CLEAR_EXTRA_STATUS_FLAGS);
#if McuShellUart_CONFIG_USE_FREERTOS
  if (xHigherPriorityTaskWoken != pdFALSE) {
    vPortYieldFromISR();
  }
#endif
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && ((McuLib_CONFIG_CORTEX_M==4) || (McuLib_CONFIG_CORTEX_M==7))
  /* ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping exception return operation might vector to incorrect interrupt.
  * For Cortex-M7, if core speed much faster than peripheral register write speed, the peripheral interrupt flags may be still set after exiting ISR, this results to
  * the same error similar with errata 83869. */
  __DSB();
#endif
}
#endif

void McuShellUart_MuxUartPins(int uart) {
  switch(uart) {
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
    case McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4: /* PTC3, PTC4 */
      CLOCK_EnableClock(kCLOCK_PortC);

      /* PORTC3 (pin 46) is configured as LPUART0_RX */
      PORT_SetPinMux(PORTC, 3U, kPORT_MuxAlt7);
      PORTC->PCR[3] = ((PORTC->PCR[3] &
                        /* Mask bits to zero which are setting */
                        (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                       /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                        * corresponding PE field is set. */
                       | (uint32_t)(kPORT_PullUp));

      /* PORTC4 (pin 49) is configured as LPUART0_TX */
      PORT_SetPinMux(PORTC, 4U, kPORT_MuxAlt7);
      PORTC->PCR[4] = ((PORTC->PCR[4] &
                        /* Mask bits to zero which are setting */
                        (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                       /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                        * corresponding PE field is set. */
                       | (uint32_t)(kPORT_PullUp));
      break;

    case McuShellUart_CONFIG_UART_K22FN512_UART0_B16_B17: /* PTB16, PTB17 */
      CLOCK_EnableClock(kCLOCK_PortB);

      /* PORTB16 (pin 39) is configured as UART0_RX */
      PORT_SetPinMux(PORTB, 16, kPORT_MuxAlt3);
      PORTB->PCR[16] = ((PORTB->PCR[16] &
                         /* Mask bits to zero which are setting */
                         (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                        /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                         * corresponding PE field is set. */
                        | (uint32_t)(kPORT_PullUp));


      /* PORTB17 (pin 40) is configured as UART0_TX */
      PORT_SetPinMux(PORTB, 17, kPORT_MuxAlt3);
      PORTB->PCR[17] = ((PORTB->PCR[17] &
                          /* Mask bits to zero which are setting */
                          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                         /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                          * corresponding PE field is set. */
                         | (uint32_t)(kPORT_PullUp));

      #define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

      SIM->SOPT5 = ((SIM->SOPT5 &
                     /* Mask bits to zero which are setting */
                     (~(SIM_SOPT5_UART0TXSRC_MASK)))
                    /* UART 0 transmit data source select: UART0_TX pin. */
                    | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
      break;

    case McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0:
      CLOCK_EnableClock(kCLOCK_PortE);

      /* PORTE0 (pin 1) is configured as UART1_TX */
      PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);
      PORTE->PCR[0] = ((PORTE->PCR[0] &
                         /* Mask bits to zero which are setting */
                         (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                        /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                         * corresponding PE field is set. */
                        | (uint32_t)(kPORT_PullUp));

      /* PORTE1 (pin 2) is configured as UART1_RX */
      PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);
      PORTE->PCR[1] = ((PORTE->PCR[1] &
                         /* Mask bits to zero which are setting */
                         (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                        /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                         * corresponding PE field is set. */
                        | (uint32_t)(kPORT_PullUp));

       #define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */
       SIM->SOPT5 = ((SIM->SOPT5 &
                      /* Mask bits to zero which are setting */
                      (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART1TXSRC_MASK)))
                     /* UART 1 transmit data source select: UART1_TX pin. */
                     | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
      break;
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FX

    #define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */
    #define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

    case McuShellUart_CONFIG_UART_K22FX512_UART0_A1_A2:
      /* PORTA1 (pin 27) is configured as UART0_RX */
      PORT_SetPinMux(PORTA, 1U, kPORT_MuxAlt2);

      /* PORTA2 (pin 28) is configured as UART0_TX */
      PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt2);

      SIM->SOPT5 = ((SIM->SOPT5 &
                     /* Mask bits to zero which are setting */
                     (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART1TXSRC_MASK)))
                    /* UART 0 transmit data source select: UART0_TX pin. */
                    | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
      break;

    case McuShellUart_CONFIG_UART_K22FX512_UART1_E1_E0:
      CLOCK_EnableClock(kCLOCK_PortE);
      /* PORTE0 (pin 1) is configured as UART1_TX */
      PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);
      PORTE->PCR[0] = ((PORTE->PCR[0] &
                        /* Mask bits to zero which are setting */
                        (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                       /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                        * corresponding Port Pull Enable field is set. */
                       | (uint32_t)(kPORT_PullUp));

      /* PORTE1 (pin 2) is configured as UART1_RX */
      PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);
      PORTE->PCR[1] = ((PORTE->PCR[1] &
                        /* Mask bits to zero which are setting */
                        (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                       /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                        * corresponding Port Pull Enable field is set. */
                       | (uint32_t)(kPORT_PullUp));
      SIM->SOPT5 = ((SIM->SOPT5 &
                     /* Mask bits to zero which are setting */
                     (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART1TXSRC_MASK)))
                    /* UART 1 transmit data source select: UART1_TX pin. */
                    | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
      break;
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K64FN1M_UART0_B16_B17
    case McuShellUart_CONFIG_UART_K64FN1M_UART0_B16_B17:
      /* UART0 Rx and Tx */
      /* PORTB16 (pin 62) is configured as UART0_RX */
      PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

      #define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

      /* PORTB17 (pin 63) is configured as UART0_TX */
      PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt3);
      SIM->SOPT5 = ((SIM->SOPT5 &
                     /* Mask bits to zero which are setting */
                     (~(SIM_SOPT5_UART0TXSRC_MASK)))

                    /* UART 0 transmit data source select: UART0_TX pin. */
                    | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
      break;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
    case McuShellUart_CONFIG_UART_RP2040_UART1_GPIO4_GPIO5:
      gpio_set_function(McuShellUart_CONFIG_UART_TX_PIN, GPIO_FUNC_UART);
      gpio_set_function(McuShellUart_CONFIG_UART_RX_PIN, GPIO_FUNC_UART);
      break;
#endif /* McuLib_CONFIG_CPU_VARIANT_NXP_K22FN */
    default:
      for(;;) { /* error */ }
  } /* switch */
}

#if McuShellUart_CONFIG_DO_PIN_MUXING
static void InitUartMuxing(void) {
#if McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_LPC845_USART0
  /* Enables clock for switch matrix.: enable */
  CLOCK_EnableClock(kCLOCK_Swm);
  /* USART0_TXD connect to P0_25 */
  SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P0_25);
  /* USART0_RXD connect to P0_24 */
  SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P0_24);
  /* Disable clock for switch matrix. */
  CLOCK_DisableClock(kCLOCK_Swm);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FX512_UART0
  #define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */
  #define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

  /* PORTA1 (pin 27) is configured as UART0_RX */
  PORT_SetPinMux(PORTA, 1U, kPORT_MuxAlt2);
  /* PORTA2 (pin 28) is configured as UART0_TX */
  PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt2);

  /* PORTE0 (pin 1) is configured as UART1_TX */
  PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

  PORTE->PCR[0] = ((PORTE->PCR[0] &
                    /* Mask bits to zero which are setting */
                    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                   /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                    * corresponding Port Pull Enable field is set. */
                   | (uint32_t)(kPORT_PullUp));

  /* PORTE1 (pin 2) is configured as UART1_RX */
  PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);

  PORTE->PCR[1] = ((PORTE->PCR[1] &
                    /* Mask bits to zero which are setting */
                    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                   /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                    * corresponding Port Pull Enable field is set. */
                   | (uint32_t)(kPORT_PullUp));

  SIM->SOPT5 = ((SIM->SOPT5 &
                 /* Mask bits to zero which are setting */
                 (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART1TXSRC_MASK)))

                /* UART 0 transmit data source select: UART0_TX pin. */
                | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)

                /* UART 1 transmit data source select: UART1_TX pin. */
                | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
  McuShellUart_MuxUartPins(McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART0_B16_B17
  McuShellUart_MuxUartPins(McuShellUart_CONFIG_UART_K22FN512_UART0_B16_B17);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0
  McuShellUart_MuxUartPins(McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K64FN1M_UART0_B16_B17
  McuShellUart_MuxUartPins(McuShellUart_CONFIG_UART_K64FN1M_UART0_B16_B17);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_LPC55S16_USART0
  #define IOCON_PIO_FUNC1 0x01u
  #define IOCON_PIO_INV_DI 0x00u
  #define IOCON_PIO_MODE_INACT 0x00u
  #define IOCON_PIO_SLEW_STANDARD 0x00u
  #define IOCON_PIO_OPENDRAIN_DI 0x00u
  #define IOCON_PIO_DIGITAL_EN 0x0100u
  #define PIO0_3_FUNC_ALT1 0x01u
  #define PIO0_3_DIGIMODE_DIGITAL 0x01u

  const uint32_t port0_pin29_config = (/* Pin is configured as FC0_RXD_SDA_MOSI_DATA */
                                       IOCON_PIO_FUNC1 |
                                       /* No addition pin function */
                                       IOCON_PIO_MODE_INACT |
                                       /* Standard mode, output slew rate control is enabled */
                                       IOCON_PIO_SLEW_STANDARD |
                                       /* Input function is not inverted */
                                       IOCON_PIO_INV_DI |
                                       /* Enables digital function */
                                       IOCON_PIO_DIGITAL_EN |
                                       /* Open drain is disabled */
                                       IOCON_PIO_OPENDRAIN_DI);
  /* PORT0 PIN29 (coords: 92) is configured as FC0_RXD_SDA_MOSI_DATA */
  IOCON_PinMuxSet(IOCON, 0U, 29U, port0_pin29_config);

  IOCON->PIO[0][3] = ((IOCON->PIO[0][3] &
                       /* Mask bits to zero which are setting */
                       (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                      /* Selects pin function.
                       * : PORT03 (pin 83) is configured as FC3_RXD_SDA_MOSI_DATA. */
                      | IOCON_PIO_FUNC(PIO0_3_FUNC_ALT1)

                      /* Select Digital mode.
                       * : Enable Digital mode.
                       * Digital input is enabled. */
                      | IOCON_PIO_DIGIMODE(PIO0_3_DIGIMODE_DIGITAL));

  const uint32_t port0_pin30_config = (/* Pin is configured as FC0_TXD_SCL_MISO_WS */
                                       IOCON_PIO_FUNC1 |
                                       /* No addition pin function */
                                       IOCON_PIO_MODE_INACT |
                                       /* Standard mode, output slew rate control is enabled */
                                       IOCON_PIO_SLEW_STANDARD |
                                       /* Input function is not inverted */
                                       IOCON_PIO_INV_DI |
                                       /* Enables digital function */
                                       IOCON_PIO_DIGITAL_EN |
                                       /* Open drain is disabled */
                                       IOCON_PIO_OPENDRAIN_DI);
  /* PORT0 PIN30 (coords: 94) is configured as FC0_TXD_SCL_MISO_WS */
  IOCON_PinMuxSet(IOCON, 0U, 30U, port0_pin30_config);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_LPC55S16_USART2
  #define PIO0_27_FUNC_ALT1 0x01u
  #define PIO1_24_FUNC_ALT1 0x01u
  #define PIO0_27_DIGIMODE_DIGITAL 0x01u
  #define PIO1_24_DIGIMODE_DIGITAL 0x01u

  IOCON->PIO[0][27] = ((IOCON->PIO[0][27] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                       /* Selects pin function.
                        * : PORT027 (pin 27) is configured as FC2_TXD_SCL_MISO_WS. */
                       | IOCON_PIO_FUNC(PIO0_27_FUNC_ALT1)

                       /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                       | IOCON_PIO_DIGIMODE(PIO0_27_DIGIMODE_DIGITAL));

  IOCON->PIO[1][24] = ((IOCON->PIO[1][24] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                       /* Selects pin function.
                        * : PORT124 (pin 3) is configured as FC2_RXD_SDA_MOSI_DATA. */
                       | IOCON_PIO_FUNC(PIO1_24_FUNC_ALT1)

                       /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                       | IOCON_PIO_DIGIMODE(PIO1_24_DIGIMODE_DIGITAL));
#endif
}
#endif /* McuShellUart_CONFIG_DO_PIN_MUXING */

static void InitUart(void) {
#if McuLib_CONFIG_CPU_IS_RPxxxx
  /* nothing needed */
#else
  McuShellUart_CONFIG_UART_CONFIG_STRUCT config;
  status_t status;

#if McuShellUart_CONFIG_DO_PIN_MUXING
  InitUartMuxing(); /* NOTE: Clocking of the UART needs still to be done in the clocks tool for the MCUXpresso SDK! */
#endif
  McuShellUart_CONFIG_UART_SET_UART_CLOCK();
  McuShellUart_CONFIG_UART_GET_DEFAULT_CONFIG(&config);
  config.baudRate_Bps = McuShellUart_CONFIG_UART_BAUDRATE;
  config.enableRx     = true;
  config.enableTx     = true;

  /* Initialize the USART with configuration. */
  status = McuShellUart_CONFIG_UART_INIT(McuShellUart_CONFIG_UART_DEVICE, &config, CLOCK_GetFreq(McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT));
  if (status!=kStatus_Success) {
    McuLog_error("failed initializing UART");
    for(;;) {/* error */}
  }
  McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS(McuShellUart_CONFIG_UART_DEVICE, McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS);
#if McuShellUart_CONFIG_USE_FREERTOS
  NVIC_SetPriority(McuShellUart_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
#endif
  EnableIRQ(McuShellUart_CONFIG_UART_IRQ_NUMBER);
#endif
}

void McuShellUart_Deinit(void) {
#if McuShellUart_CONFIG_USE_FREERTOS
  vQueueDelete(uartRxQueue);
  uartRxQueue = NULL;
#else
  McuRB_DeinitRB(rxRingBuffer);
  rxRingBuffer = NULL;
#endif
}

void McuShellUart_Init(void) {
#if McuShellUart_CONFIG_USE_FREERTOS
  uartRxQueue = xQueueCreate(McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (uartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(uartRxQueue, "UartRxQueue");
#else
  McuRB_Config_t config;

  McuRB_GetDefaultconfig(&config);
  config.elementSize = sizeof(uint8_t);
  config.nofElements = McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH;
  rxRingBuffer = McuRB_InitRB(&config);
  if (rxRingBuffer==NULL) {
    for(;;) {/* error */}
  }
#endif
  InitUart();
}

#endif /* McuShellUart_CONFIG_UART!=McuShellUart_CONFIG_UART_NONE*/
