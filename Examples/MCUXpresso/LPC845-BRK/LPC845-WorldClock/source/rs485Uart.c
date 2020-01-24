/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "rs485Uart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"

static QueueHandle_t RS485UartRxQueue; /* queue for the shell */
static QueueHandle_t RS485UartResponseQueue; /* queue for the OK or NOK response */

void RS458Uart_ClearResponseQueue(void) {
  xQueueReset(RS485UartResponseQueue);
}

uint8_t RS458Uart_GetResponseQueueChar(void) {
  uint8_t ch;

  if (xQueueReceive(RS485UartResponseQueue, &ch, 0)==pdPASS ) {
    /* return received character */
  } else {
    ch = '\0'; /* nothing received */
  }
  return ch;
}

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
void RS485Uart_SendBlock(unsigned char *data, size_t dataSize) {
  RS485Uart_CONFIG_UART_WRITE_BLOCKING(RS485Uart_CONFIG_UART_DEVICE, data, dataSize);
}

void RS485Uart_SendString(unsigned char *str) {
  RS485Uart_SendBlock(str, strlen((char*)str));
}

static void RS485Uart_SendChar(unsigned char ch) {
  static unsigned char buf[64] = ""; /* only sending after a '\n', to send things as a block for faster transmission */
  static size_t index = 0;

  buf[index++] = ch;
  if (ch=='\n' || index==sizeof(buf)-1) {
    buf[index] = '\0'; /* terminate buffer */
    RS485Uart_SendString(buf);
    buf[0] = '\0';
    index = 0;
  }
}

static void RS485Uart_ReadChar(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(RS485UartRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool RS485Uart_CharPresent(void) {
  return uxQueueMessagesWaiting(RS485UartRxQueue)!=0;
}

McuShell_ConstStdIOType RS485Uart_stdio = {
    (McuShell_StdIO_In_FctType)RS485Uart_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)RS485Uart_SendChar,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)RS485Uart_SendChar,  /* stderr */
    RS485Uart_CharPresent /* if input is not empty */
  };

uint8_t RS485Uart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/
void RS485Uart_CONFIG_UART_IRQ_HANDLER(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = RS485Uart_CONFIG_UART_GET_FLAGS(RS485Uart_CONFIG_UART_DEVICE);
  /* If new data arrived. */
  if (flags&RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS) {
    data = RS485Uart_CONFIG_UART_READ_BYTE(RS485Uart_CONFIG_UART_DEVICE);
    (void)xQueueSendFromISR(RS485UartResponseQueue, &data, &xHigherPriorityTaskWoken);
    (void)xQueueSendFromISR(RS485UartRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  USART_ClearStatusFlags(RS485Uart_CONFIG_UART_DEVICE, flags);
  __DSB();
}

static void InitUart(void) {
  /* NOTE: Muxing of the UART pins needs to be done in the Pins tool! */
  RS485Uart_CONFIG_UART_CONFIG_STRUCT config;

  RS485Uart_CONFIG_UART_SET_UART_CLOCK();
  RS485Uart_CONFIG_UART_GET_DEFAULT_CONFIG(&config);
  config.baudRate_Bps = RS485Uart_CONFIG_UART_BAUDRATE;
  config.enableRx     = true;
  config.enableTx     = true;

  /* Initialize the USART with configuration. */
  RS485Uart_CONFIG_UART_INIT(RS485Uart_CONFIG_UART_DEVICE, &config, CLOCK_GetFreq(RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT));
#if RS485Uart_CONFIG_USE_HW_OE_RTS
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OESEL(1); /* if enabled, use RTS signal for RS-485 transceiver */
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OEPOL(1); /* 1: the output enable signal is high active */
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OETA(1); /* output enable turnaround time: if set, the output enable signal remains asserted for 1 char time after the end of the last bit */
#endif
  RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS(RS485Uart_CONFIG_UART_DEVICE, RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS);
  NVIC_SetPriority(RS485Uart_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(RS485Uart_CONFIG_UART_IRQ_NUMBER);
}

void RS485Uart_Deinit(void) {
  vQueueDelete(RS485UartRxQueue);
  RS485UartRxQueue = NULL;
  vQueueDelete(RS485UartResponseQueue);
  RS485UartResponseQueue = NULL;
}

void RS485Uart_Init(void) {
  InitUart();
  RS485UartRxQueue = xQueueCreate(RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartRxQueue, "RS485UartRxQueue");
  RS485UartResponseQueue = xQueueCreate(RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartResponseQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartResponseQueue, "RS485UartRxQueue");
}

