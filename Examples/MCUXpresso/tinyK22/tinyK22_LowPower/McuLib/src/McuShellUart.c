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

static void InitUart(void) {
  /* NOTE: Muxing of the UART pins and clocking of the UART needs to be done in the Pins/clocks tool! */
  McuShellUart_CONFIG_UART_CONFIG_STRUCT config;
  status_t status;

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
