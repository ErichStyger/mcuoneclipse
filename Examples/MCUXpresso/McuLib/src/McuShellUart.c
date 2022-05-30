/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuShellUartconfig.h"
#if McuShellUart_CONFIG_UART!=McuShellUart_CONFIG_UART_NONE
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTOS.h"

static QueueHandle_t uartRxQueue;

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
static void McuShellUart_SendChar(unsigned char ch) {
  McuShellUart_CONFIG_UART_WRITE_BLOCKING(McuShellUart_CONFIG_UART_DEVICE, &ch, 1);
}

static void McuShellUart_ReadChar(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(uartRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool McuShellUart_CharPresent(void) {
  return uxQueueMessagesWaiting(uartRxQueue)!=0;
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
void McuShellUart_CONFIG_UART_IRQ_HANDLER(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = McuShellUart_CONFIG_UART_GET_FLAGS(McuShellUart_CONFIG_UART_DEVICE);
  /* If new data arrived. */
  if (flags&McuShellUart_CONFIG_UART_HW_RX_READY_FLAGS) {
    data = McuShellUart_CONFIG_UART_READ_BYTE(McuShellUart_CONFIG_UART_DEVICE);
    (void)xQueueSendFromISR(uartRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  McuShellUART_CONFIG_CLEAR_STATUS_FLAGS(McuShellUart_CONFIG_UART_DEVICE, flags);
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && ((McuLib_CONFIG_CORTEX_M==4) || (McuLib_CONFIG_CORTEX_M==7))
  /* ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping exception return operation might vector to incorrect interrupt.
  * For Cortex-M7, if core speed much faster than peripheral register write speed, the peripheral interrupt flags may be still set after exiting ISR, this results to
  * the same error similar with errata 83869. */
  __DSB();
#endif
}

#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
void McuShellUart_Mux(int uart) {
  switch(uart) {
    case McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4: /* PTC3, PTC4 */
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
      /* Port B Clock Gate Control: Clock enabled */
      CLOCK_EnableClock(kCLOCK_PortB);
      /* PORTB16 (pin 39) is configured as UART0_RX */
      PORT_SetPinMux(PORTB, 16, kPORT_MuxAlt3);
      /* PORTB17 (pin 40) is configured as UART0_TX */
      PORT_SetPinMux(PORTB, 17, kPORT_MuxAlt3);

      #define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

      SIM->SOPT5 = ((SIM->SOPT5 &
                     /* Mask bits to zero which are setting */
                     (~(SIM_SOPT5_UART0TXSRC_MASK)))
                    /* UART 0 transmit data source select: UART0_TX pin. */
                    | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
      break;
    case McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0:
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
    default:
      for(;;) { /* error */ }
  } /* switch */
}
#endif /* McuLib_CONFIG_CPU_VARIANT_NXP_K22FN */

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
  McuShellUart_Mux(McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART0_B16_B17
  McuShellUart_Mux(McuShellUart_CONFIG_UART_K22FN512_UART0_B16_B17);
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0
  McuShellUart_Mux(McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0);
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
    for(;;) {/* error */}
  }
  McuShellUart_CONFIG_UART_ENABLE_INTERRUPTS(McuShellUart_CONFIG_UART_DEVICE, McuShellUart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS);
  NVIC_SetPriority(McuShellUart_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(McuShellUart_CONFIG_UART_IRQ_NUMBER);
}

void McuShellUart_Deinit(void) {
  vQueueDelete(uartRxQueue);
  uartRxQueue = NULL;
}

void McuShellUart_Init(void) {
  uartRxQueue = xQueueCreate(McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (uartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(uartRxQueue, "UartRxQueue");
  InitUart();
}

#endif /* McuShellUart_CONFIG_UART!=McuShellUart_CONFIG_UART_NONE*/
