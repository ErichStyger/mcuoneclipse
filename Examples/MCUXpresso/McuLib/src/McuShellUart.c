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
#error "NYI"
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART0
#error "NYI"
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_UART1
#error "NYI"
#elif McuShellUart_CONFIG_UART==McuShellUart_CONFIG_UART_K22FN512_LPUART0
  /* PORTC3 (pin 46) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, 3U, kPORT_MuxAlt7);

  /* PORTC4 (pin 49) is configured as LPUART0_TX */
  PORT_SetPinMux(PORTC, 4U, kPORT_MuxAlt7);
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
