/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "rs485Uart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"

#if !RS485Uart_CONFIG_USE_HW_OE_RTS
#include "McuGPIO.h"

/* RTS pin to enable Tx mode on transceiver (HIGH active) */
#define RS485_TX_EN_GPIO       GPIOC
#define RS485_TX_EN_PORT       PORTC
#define RS485_TX_EN_PIN        2U

static McuGPIO_Handle_t RS485_TxEn;

void RS485Uart_GPIO_RxEnable(void) {
  McuGPIO_SetLow(RS485_TxEn);
}

void RS485Uart_GPIO_TxEnable(void) {
  McuGPIO_SetHigh(RS485_TxEn);
}

static void RS485Uart_GPIO_Deinit(void) {
  RS485_TxEn = McuGPIO_DeinitGPIO(RS485_TxEn);
}

static void RS485Uart_GPIO_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);

  config.hw.gpio  = RS485_TX_EN_GPIO;
  config.hw.port  = RS485_TX_EN_PORT;
  config.hw.pin   = RS485_TX_EN_PIN;
  config.isInput = false;
  config.isHighOnInit = false; /* Tx disabled */
  RS485_TxEn = McuGPIO_InitGPIO(&config);

  RS485_GPIO_RxEnable();
}
#endif /* RS485Uart_CONFIG_USE_HW_OE_RTS */

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
  static unsigned char RS485Uart_SendCharbuf[McuShell_DEFAULT_SHELL_BUFFER_SIZE] = ""; /* only sending after a '\n', to send things as a block for faster transmission */
  static size_t index = 0;

  RS485Uart_SendCharbuf[index++] = ch;
  if (ch=='\n' || index==sizeof(RS485Uart_SendCharbuf)-1) {
    RS485Uart_SendCharbuf[index] = '\0'; /* terminate buffer */
    RS485Uart_SendString(RS485Uart_SendCharbuf);
    RS485Uart_SendCharbuf[0] = '\0';
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
  BaseType_t xHigherPriorityTaskWoken1 = false, xHigherPriorityTaskWoken2 = false;
  static unsigned char prevChar = '\n';
  static bool responseLine = false;
  uint8_t count;

  flags = RS485Uart_CONFIG_UART_GET_FLAGS(RS485Uart_CONFIG_UART_DEVICE);
#if RS485Uart_CONFIG_HAS_FIFO
  if (flags&kUART_RxFifoOverflowFlag) {
    count = 0; /* statement to allow debugger to set a breakpoint here */
  }
#endif
  /* new data arrived. */
  if (flags&RS485Uart_CONFIG_UART_HW_RX_READY_FLAGS) {
#if RS485Uart_CONFIG_HAS_FIFO
    count = RS485Uart_CONFIG_UART_DEVICE->RCFIFO;
#else
    count = 1;
#endif
    while(count!=0) {
      data = RS485Uart_CONFIG_UART_READ_BYTE(RS485Uart_CONFIG_UART_DEVICE);
      if (data!=0) { /* data==0 could happen especially after power-up, ignore it */
        /* only store into RS485UartResponseQueue if we have a line starting with '@' */
        if (prevChar=='\n' && data=='@') {
          responseLine = true;
        }
        if (responseLine) {
          (void)xQueueSendFromISR(RS485UartResponseQueue, &data, &xHigherPriorityTaskWoken1);
        }
        prevChar = data;
        if (responseLine && data=='\n') { /* end of line while on response line */
          responseLine = false;
        }
        (void)xQueueSendFromISR(RS485UartRxQueue, &data, &xHigherPriorityTaskWoken2);
      }
      count--;
    }
  }
#if McuLib_CONFIG_CPU_IS_KINETIS
  flags |= kUART_RxOverrunFlag|kUART_RxFifoOverflowFlag; /* always clear these flags, as they might been set? Not clearing them will not generate future interrupts */
#endif
  RS485Uart_CONFIG_CLEAR_STATUS_FLAGS(RS485Uart_CONFIG_UART_DEVICE, flags);
  if (xHigherPriorityTaskWoken1 != pdFALSE || xHigherPriorityTaskWoken2 != pdFALSE) {
    vPortYieldFromISR();
  }
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
#if McuLib_CONFIG_CPU_IS_KINETIS
  config.enableRxRTS  = true; /* using RTS pin to control the transceiver */
  config.enableTxCTS  = false;
#endif
  /* Initialize the USART with configuration. */
  RS485Uart_CONFIG_UART_INIT(RS485Uart_CONFIG_UART_DEVICE, &config, CLOCK_GetFreq(RS485Uart_CONFIG_UART_GET_CLOCK_FREQ_SELECT));
#if RS485Uart_CONFIG_USE_HW_OE_RTS
  #if McuLib_CONFIG_CPU_IS_KINETIS /* Kinetis K22FN512 */
  RS485Uart_CONFIG_UART_DEVICE->MODEM |= UART_MODEM_TXRTSPOL(1); /* TXRTSPOL: 1: transmitter RTS polarity is active high */
  RS485Uart_CONFIG_UART_DEVICE->MODEM |= UART_MODEM_TXRTSE(1);   /* TXRTSE: Transmitter request-to-send enable, 1: RTS asserted before start bit is transmitted and deasserted after stop bit */
  #elif McuLib_CONFIG_CPU_IS_LPC /* LPC845 */
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OESEL(1); /* if enabled, use RTS signal for RS-485 transceiver */
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OEPOL(1); /* 1: the output enable signal is high active */
  RS485Uart_CONFIG_UART_DEVICE->CFG |= USART_CFG_OETA(1); /* output enable turnaround time: if set, the output enable signal remains asserted for 1 char time after the end of the last bit */
  #endif
#endif
#if RS485Uart_CONFIG_HAS_FIFO
  UART_EnableRxFIFO(RS485Uart_CONFIG_UART_DEVICE, true); /* enable UART Rx FIFO */
#endif
  RS485Uart_CONFIG_UART_ENABLE_INTERRUPTS(RS485Uart_CONFIG_UART_DEVICE,
		  RS485Uart_CONFIG_UART_ENABLE_INTERRUPT_FLAGS
		  );
  NVIC_SetPriority(RS485Uart_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY); /* required as we are using FreeRTOS API calls */
  EnableIRQ(RS485Uart_CONFIG_UART_IRQ_NUMBER);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[16];
  uint32_t flags;

  McuShell_SendStatusStr((unsigned char*)"uart485", (unsigned char*)"RS-485 UART settings\r\n", io->stdOut);
  flags = RS485Uart_CONFIG_UART_GET_FLAGS(RS485Uart_CONFIG_UART_DEVICE);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), flags);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  flags", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"uart485", (unsigned char*)"Group of RS-458 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  clear <flags>", (unsigned char*)"Clear UART ISR flags\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RS485Uart_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "uart485 help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "uart485 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "uart485 clear ", sizeof("uart485 clear ")-1)==0) {
    int32_t flags;
#if McuLib_CONFIG_CPU_IS_KINETIS
    status_t status;
#endif
    const unsigned char *p;

    *handled = true;
    p = cmd + sizeof("uart485 clear ")-1;
    if (McuUtility_xatoi(&p, &flags)==ERR_OK) {
#if McuLib_CONFIG_CPU_IS_KINETIS
      status = RS485Uart_CONFIG_CLEAR_STATUS_FLAGS(RS485Uart_CONFIG_UART_DEVICE, flags);
      McuShell_SendStr((unsigned char*)"status: ", io->stdOut);
      McuShell_SendNum32u(status, io->stdOut);
      McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
#else
      RS485Uart_CONFIG_CLEAR_STATUS_FLAGS(RS485Uart_CONFIG_UART_DEVICE, flags);
#endif
      return ERR_OK;
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

void RS485Uart_Deinit(void) {
  vQueueDelete(RS485UartRxQueue);
  RS485UartRxQueue = NULL;
  vQueueDelete(RS485UartResponseQueue);
  RS485UartResponseQueue = NULL;
#if !RS485Uart_CONFIG_USE_HW_OE_RTS
  RS485Uart_GPIO_Deinit();
#endif
}

void RS485Uart_Init(void) {
  InitUart();
  RS485UartRxQueue = xQueueCreate(RS485Uart_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartRxQueue, "RS485UartRxQueue");

  RS485UartResponseQueue = xQueueCreate(RS485Uart_CONFIG_UART_RESPONSE_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartResponseQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartResponseQueue, "RS485UartResponseQueue");
}

