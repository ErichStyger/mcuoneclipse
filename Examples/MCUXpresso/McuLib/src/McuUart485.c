/*
 * Copyright (c) 2020-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuUart485.h"
#if McuUart485_CONFIG_USE_RS_485
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuGPIO.h"
#include <ctype.h> /* for isprint() */

#if McuLib_CONFIG_CPU_IS_ESP32
  #include "esp_system.h"
  #include "driver/uart.h"
#endif

#if !McuUart485_CONFIG_USE_HW_OE_RTS

static McuGPIO_Handle_t RS485_TxEn; /* LOW: Rx, HIGH: Tx */

void McuUart485_GPIO_RxEnable(void) {
  McuGPIO_SetLow(RS485_TxEn);
#if McuLib_CONFIG_CPU_IS_RPxxxx
  uart_get_hw(McuUart485_CONFIG_UART_DEVICE)->cr |= UART_UARTCR_RXE_BITS; /* enable receiver for half duplex communication */
#endif
}

void McuUart485_GPIO_TxEnable(void) {
#if McuLib_CONFIG_CPU_IS_RPxxxx
  uart_get_hw(McuUart485_CONFIG_UART_DEVICE)->cr &= ~UART_UARTCR_RXE_BITS; /* disable receiver for half duplex communication */
#endif
  McuGPIO_SetHigh(RS485_TxEn);
}

static void McuUart485_GPIO_Deinit(void) {
  RS485_TxEn = McuGPIO_DeinitGPIO(RS485_TxEn);
}

static void McuUart485_GPIO_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
#if McuLib_CONFIG_CPU_IS_ESP32
  config.hw.pin = McuUart485_CONFIG_TX_EN_GPIO;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  config.hw.pin   = McuUart485_CONFIG_TX_EN_PIN;
#else
  config.hw.gpio  = McuUart485_CONFIG_TX_EN_GPIO;
  config.hw.port  = McuUart485_CONFIG_TX_EN_PORT;
  config.hw.pin   = McuUart485_CONFIG_TX_EN_PIN;
#endif
  config.isInput = false;
  config.isHighOnInit = false; /* Tx disabled */
  RS485_TxEn = McuGPIO_InitGPIO(&config);

  McuUart485_GPIO_RxEnable();
}
#endif /* McuUart485_CONFIG_USE_HW_OE_RTS */
/* -------------------------------------------------------------------------------------- */
static QueueHandle_t RS485UartRxQueue; /* queue of the received bytes */
#if !McuUart485_CONFIG_USE_MODBUS /* shell response queue only used in non-Modbus mode */
  static QueueHandle_t RS485UartResponseQueue; /* queue for the OK or NOK response */
#endif
#if McuUart485_CONFIG_USE_LOGGER
  static bool McuUart485_doLogging = false; /* if logging is turned on or off */
#endif

void McuUart485_ClearRxQueue(void) {
  xQueueReset(RS485UartRxQueue);
}

#if !McuUart485_CONFIG_USE_MODBUS
void McuUart485_ClearResponseQueue(void) {
  xQueueReset(RS485UartResponseQueue);
}
#endif

uint8_t McuUart485_GetRxQueueByte(unsigned char *data, TickType_t ticksToWait) {
  if (xQueueReceive(RS485UartRxQueue, data, ticksToWait)==pdPASS ) {
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}

uint8_t McuUart485_GetRxQueueChar(void) {
  uint8_t ch;

  if (xQueueReceive(RS485UartRxQueue, &ch, 0)==pdPASS ) {
    /* return received character */
  } else {
    ch = '\0'; /* nothing received */
  }
  return ch;
}

#if !McuUart485_CONFIG_USE_MODBUS
uint8_t McuUart485_GetResponseQueueChar(void) {
  uint8_t ch;

  if (xQueueReceive(RS485UartResponseQueue, &ch, 0)==pdPASS ) {
    /* return received character */
  } else {
    ch = '\0'; /* nothing received */
  }
  return ch;
}
#endif
/* -------------------------------------------------------------------------------------- */

#if McuLib_CONFIG_CPU_IS_ESP32

#define RS485_ESP_BUF_SIZE          (4*1024)  /* buffer for the UART task. The UART driver uses twice of this */

#if 0 /* not used */
void RS485_SendStr(char *str) {
  size_t len = strlen(str);

  uart_write_bytes(McuUart485_CONFIG_UART_DEVICE, str, len);
}

void RS485_SendChar(char ch) {
  uart_write_bytes(McuUart485_CONFIG_UART_DEVICE, &ch, 1);
}
#endif

/* On the ESP32 we are using a task. On other architectures this would be handled by an interrupt */
static void rs485uart_task(void *arg) {
  static unsigned char data[RS485_ESP_BUF_SIZE]; /* Rx buffer for UART */
  unsigned char prevChar = '\n';
  bool responseLine = false;
  BaseType_t res;

  McuLog_trace("UART start receive loop.\r\n");
  for(;;) {
    /* Read data from UART */
    int len = uart_read_bytes(McuUart485_CONFIG_UART_DEVICE, data, sizeof(data)-1, pdMS_TO_TICKS(100));
    #if 0 /* for debugging only */
    if (len>0) {
      data[len] = '\0';
      McuLog_trace("rx: %d", len);
    }
    #endif
    /* send to Rx Queue */
    for(int i=0; i<len; i++) { /* handle received bytes */
      if (prevChar=='\n' && data[i]=='@') { /* do we have potentially a response for us on the bus? */
        responseLine = true;
      }
      if (responseLine) {
        res = xQueueSend(RS485UartResponseQueue, &data[i], pdMS_TO_TICKS(10));
        if (res!=pdPASS) {
          McuLog_error("failed sending data to response queue");
        }
      }
      prevChar = data[i];
      if (responseLine && data[i]=='\n') { /* end of line while on response line */
        responseLine = false;
      }
      res = xQueueSend(RS485UartRxQueue, &data[i], pdMS_TO_TICKS(20));
      if (res!=pdPASS) {
        McuLog_error("failed sending data to rx queue");
      }
    }
  } /* for */
}

#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
void McuUart485_SendBlock(unsigned char *data, size_t dataSize) {
#if McuLib_CONFIG_CPU_IS_ESP32
  uart_write_bytes(McuUart485_CONFIG_UART_DEVICE, data, dataSize);
#else
  #if !McuUart485_CONFIG_USE_HW_OE_RTS
  McuUart485_GPIO_TxEnable();
  #endif
  McuUart485_CONFIG_UART_WRITE_BLOCKING(McuUart485_CONFIG_UART_DEVICE, data, dataSize);
  #if !McuUart485_CONFIG_USE_HW_OE_RTS
  #if McuLib_CONFIG_CPU_IS_RPxxxx
  uart_tx_wait_blocking(McuUart485_CONFIG_UART_DEVICE); /* wait until all bytes are sent */
  #endif
  McuUart485_GPIO_RxEnable();
  #endif
#endif
}

void McuUart485_SendString(unsigned char *str) {
  McuUart485_SendBlock(str, strlen((char*)str));
}

static void McuUart485_SendChar(unsigned char ch) {
  static unsigned char McuUart485_SendCharbuf[McuShell_DEFAULT_SHELL_BUFFER_SIZE] = ""; /* only sending after a '\n', to send things as a block for faster transmission */
  static size_t index = 0;

  McuUart485_SendCharbuf[index++] = ch;
  if (ch=='\n' || index==sizeof(McuUart485_SendCharbuf)-1) {
    McuUart485_SendCharbuf[index] = '\0'; /* terminate buffer */
    McuUart485_SendString(McuUart485_SendCharbuf);
    McuUart485_SendCharbuf[0] = '\0';
    index = 0;
  }
}

static void McuUart485_ReadChar(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(RS485UartRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool McuUart485_CharPresent(void) {
  return uxQueueMessagesWaiting(RS485UartRxQueue)!=0;
}

McuShell_ConstStdIOType McuUart485_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)McuUart485_ReadChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)McuUart485_SendChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)McuUart485_SendChar,
    .keyPressed = McuUart485_CharPresent, /* if input is not empty */
  #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
 };

uint8_t McuUart485_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_RPxxxx
void McuUart485_CONFIG_UART_IRQ_HANDLER(void) {
  uint8_t data;
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC /* no flags for RPxxxx */
  uint32_t flags;
#endif
  BaseType_t xHigherPriorityTaskWoken1 = false, xHigherPriorityTaskWoken2 = false;
#if !McuUart485_CONFIG_USE_MODBUS
  static unsigned char prevChar = '\n';
  static bool responseLine = false;
#endif
  uint8_t count;

#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC /* no flags for RPxxxx */
  flags = McuUart485_CONFIG_UART_GET_FLAGS(McuUart485_CONFIG_UART_DEVICE);
#endif
#if McuUart485_CONFIG_HAS_FIFO
  if (flags&kUART_RxFifoOverflowFlag) {
    count = 0; /* statement to allow debugger to set a breakpoint here */
  }
#endif
  /* new data arrived. */
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC /* no flags for RPxxxx */
  if (flags&McuUart485_CONFIG_UART_HW_RX_READY_FLAGS) {
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  while (uart_is_readable(McuUart485_CONFIG_UART_DEVICE)) { /* check if we have data available */
#endif

#if McuUart485_CONFIG_HAS_FIFO
    count = McuUart485_CONFIG_UART_DEVICE->RCFIFO;
#else
    count = 1;
#endif
    while(count!=0) {
      data = McuUart485_CONFIG_UART_READ_BYTE(McuUart485_CONFIG_UART_DEVICE);
    #if !McuUart485_CONFIG_USE_MODBUS
      if (data!=0) { /* data==0 could happen especially after power-up, ignore it if we are in shell/non-Modbus mode */
    #endif
    #if !McuUart485_CONFIG_USE_MODBUS
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
      #endif
        (void)xQueueSendFromISR(RS485UartRxQueue, &data, &xHigherPriorityTaskWoken2);
      #if McuUart485_CONFIG_USE_LOGGER
        if (McuUart485_doLogging) {
          extern uint8_t McuRTT_SendChar(uint8_t ch);
          unsigned char buf[3];
          buf[0] = '\0';
          McuUtility_strcatNum8Hex(buf, sizeof(buf), data);
          (void)McuUart485_CONFIG_LOGGER_CALLBACK_NAME(buf[0]);
          (void)McuUart485_CONFIG_LOGGER_CALLBACK_NAME(buf[1]);
          if (isprint(data)) {
            (void)McuUart485_CONFIG_LOGGER_CALLBACK_NAME((unsigned char)' ');
            (void)McuUart485_CONFIG_LOGGER_CALLBACK_NAME(data);
          }
          (void)McuUart485_CONFIG_LOGGER_CALLBACK_NAME((unsigned char)'\n');
        }
      #endif
    #if !McuUart485_CONFIG_USE_MODBUS
      } /* if data != 0 */
    #endif
      count--;
    } /* while count != 0 */
  }
#if McuLib_CONFIG_CPU_IS_KINETIS
  flags |= kUART_RxOverrunFlag|kUART_RxFifoOverflowFlag; /* always clear these flags, as they might been set? Not clearing them will not generate future interrupts */
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC /* no clearing needed for RPxxxx */
  McuUart485_CONFIG_CLEAR_STATUS_FLAGS(McuUart485_CONFIG_UART_DEVICE, flags);
#endif
  if (xHigherPriorityTaskWoken1 != pdFALSE || xHigherPriorityTaskWoken2 != pdFALSE) {
    vPortYieldFromISR();
  }
  #if McuLib_CONFIG_CORTEX_M==4
    __DSB(); /* ARM Cortex-M4 errata Notice 838869: dsb required because "Store immediate overlapping exception return operation might vector to incorrect interrupt" */
  #endif
}
#endif

static void InitUart(void) {
#if !McuUart485_CONFIG_USE_HW_OE_RTS
  McuUart485_GPIO_Init();
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  /* NOTE: Muxing of the UART pins needs to be done in the Pins tool! */
  McuUart485_CONFIG_UART_CONFIG_STRUCT config;
  status_t res;

  McuUart485_CONFIG_UART_SET_UART_CLOCK();
  McuUart485_CONFIG_UART_GET_DEFAULT_CONFIG(&config);
  config.baudRate_Bps = McuUart485_CONFIG_UART_BAUDRATE;
  config.parityMode   = McuUart485_CONFIG_UART_PARITY;
  config.enableRx     = true;
  config.enableTx     = true;
#if McuLib_CONFIG_CPU_IS_KINETIS
  config.enableRxRTS  = true; /* using RTS pin to control the transceiver */
  config.enableTxCTS  = false;
#endif
  /* Initialize the USART with configuration. */
  res = McuUart485_CONFIG_UART_INIT(McuUart485_CONFIG_UART_DEVICE, &config, CLOCK_GetFreq(McuUart485_CONFIG_UART_GET_CLOCK_FREQ_SELECT));
  if (res!=kStatus_Success) {
    McuLog_fatal("failed initializing UART");
    for(;;) {}
  }
#if McuUart485_CONFIG_USE_HW_OE_RTS
  #if McuLib_CONFIG_CPU_IS_KINETIS /* Kinetis K22FN512 */
  McuUart485_CONFIG_UART_DEVICE->MODEM |= UART_MODEM_TXRTSPOL(1); /* TXRTSPOL: 1: transmitter RTS polarity is active high */
  McuUart485_CONFIG_UART_DEVICE->MODEM |= UART_MODEM_TXRTSE(1);   /* TXRTSE: Transmitter request-to-send enable, 1: RTS asserted before start bit is transmitted and deasserted after stop bit */
  #elif McuLib_CONFIG_CPU_IS_LPC /* LPC845 or LPC55S69 */
  McuUart485_CONFIG_UART_DEVICE->CFG |= USART_CFG_OESEL(1); /* if enabled, use RTS signal for RS-485 transceiver */
  McuUart485_CONFIG_UART_DEVICE->CFG |= USART_CFG_OEPOL(1); /* 1: the output enable signal is high active */
  McuUart485_CONFIG_UART_DEVICE->CFG |= USART_CFG_OETA(1); /* output enable turnaround time: if set, the output enable signal remains asserted for 1 char time after the end of the last bit */
  #endif
#endif
#if McuUart485_CONFIG_HAS_FIFO
  UART_EnableRxFIFO(McuUart485_CONFIG_UART_DEVICE, true); /* enable UART Rx FIFO */
#endif
  McuUart485_CONFIG_UART_ENABLE_INTERRUPTS(McuUart485_CONFIG_UART_DEVICE,
		  McuUart485_CONFIG_UART_ENABLE_INTERRUPT_FLAGS
		  );
  NVIC_SetPriority(McuUart485_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY); /* required as we are using FreeRTOS API calls */
  EnableIRQ(McuUart485_CONFIG_UART_IRQ_NUMBER);
#elif McuLib_CONFIG_CPU_IS_ESP32
  // Timeout threshold for UART = number of symbols (~10 tics) with unchanged state on receive pin
  #define UART_CONFIG_READ_TOUT          (3) // 3.5T * 8 = 28 ticks, TOUT=3 -> ~24..33 ticks

  uart_config_t uart_config = {
      .baud_rate = McuUart485_CONFIG_UART_BAUDRATE,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, /* UART_HW_FLOWCTRL_CTS */ /*UART_HW_FLOWCTRL_RTS,*/ /* UART_HW_FLOWCTRL_CTS_RTS, */
      .rx_flow_ctrl_thresh = 122,
      .source_clk = UART_SCLK_APB,
 };

  McuLog_trace("UART set pins, mode and install driver.");

  /* Install UART driver (we don't need an event queue here) */
  ESP_ERROR_CHECK(uart_driver_install(
      McuUart485_CONFIG_UART_DEVICE, /* usart device */
      RS485_ESP_BUF_SIZE*2, /* RX Buffer */
      RS485_ESP_BUF_SIZE*2, /* TX Buffer */
      0, /* event queue size */
      NULL, /* event queue handle */
      0 /* interrupt alloc flags */
     )
   );

  /* Configure UART parameters */
  ESP_ERROR_CHECK(uart_param_config(McuUart485_CONFIG_UART_DEVICE, &uart_config));

  /* RE (Receiver Enable, IO23) shall be HIGH during Tx, RE (Low Active, IO26) shall be LOW during Tx */
  ESP_ERROR_CHECK(uart_set_pin(McuUart485_CONFIG_UART_DEVICE,
      McuUart485_CONFIG_TXD_PIN, /* TX pin */
      McuUart485_CONFIG_RXD_PIN, /* RX pin */
      McuUart485_CONFIG_RTS_PIN, /* RTS pin */
      UART_PIN_NO_CHANGE         /* CTS pin */
   ));

  /* Set RS485 half duplex mode */
  ESP_ERROR_CHECK(uart_set_mode(McuUart485_CONFIG_UART_DEVICE, UART_MODE_RS485_HALF_DUPLEX));

  // Set read timeout of UART TOUT feature
  ESP_ERROR_CHECK(uart_set_rx_timeout(McuUart485_CONFIG_UART_DEVICE, UART_CONFIG_READ_TOUT));
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  uart_init(McuUart485_CONFIG_UART_DEVICE, McuUart485_CONFIG_UART_BAUDRATE);
  gpio_set_function(McuUart485_CONFIG_TXD_PIN, GPIO_FUNC_UART);
  gpio_set_function(McuUart485_CONFIG_RXD_PIN, GPIO_FUNC_UART);
  uart_set_fifo_enabled(McuUart485_CONFIG_UART_DEVICE, false);
  uart_set_format(McuUart485_CONFIG_UART_DEVICE, 8, 1, McuUart485_CONFIG_UART_PARITY);
  uart_set_hw_flow(McuUart485_CONFIG_UART_DEVICE, false, false); /* disable flow control, cannot use CTS/RTS */
  uart_set_translate_crlf(McuUart485_CONFIG_UART_DEVICE, false); /* do not translate */
  /* setup interrupt */
  int UART_IRQ = McuUart485_CONFIG_UART_DEVICE == uart0 ? UART0_IRQ : UART1_IRQ; /* find out which UART is used */
  irq_set_exclusive_handler(UART_IRQ, McuUart485_CONFIG_UART_IRQ_HANDLER /* on_uart_rx*/); /* setup IRQ handler */
  irq_set_enabled(UART_IRQ, true); /* enable interrupt */
  irq_set_priority(UART_IRQ, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY); /* required as we are using FreeRTOS API calls */
  uart_set_irq_enables(McuUart485_CONFIG_UART_DEVICE, true, false); /* enable UART interrupt output, Rx only */
#else
  #error "need to initialize UART!"
#endif
}

#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
static void DecodeUARTFlags(uint32_t flags, const McuShell_StdIOType *io) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  if (flags&kUART_TxDataRegEmptyFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_TxDataRegEmptyFlag\r\n", io->stdOut);
  }
  if (flags&kUART_TransmissionCompleteFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_TransmissionCompleteFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxDataRegFullFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxDataRegFullFlag\r\n", io->stdOut);
  }
  if (flags&kUART_IdleLineFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_IdleLineFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxOverrunFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxOverrunFlag\r\n", io->stdOut);
  }
  if (flags&kUART_NoiseErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_NoiseErrorFlag\r\n", io->stdOut);
  }
  if (flags&kUART_FramingErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_FramingErrorFlag\r\n", io->stdOut);
  }
  if (flags&kUART_ParityErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_ParityErrorFlag\r\n", io->stdOut);
  }
#if defined(FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
  if (flags&kUART_LinBreakFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_LinBreakFlag\r\n", io->stdOut);
  }
#endif
  if (flags&kUART_RxActiveEdgeFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxActiveEdgeFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxActiveFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxActiveFlag\r\n", io->stdOut);
  }
#if defined(FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS) && FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
  if (flags&kUART_NoiseErrorInRxDataRegFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_NoiseErrorInRxDataRegFlag\r\n", io->stdOut);
  }
  if (flags&kUART_ParityErrorInRxDataRegFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_ParityErrorInRxDataRegFlag\r\n", io->stdOut);
  }
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
  if (flags&kUART_TxFifoEmptyFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_TxFifoEmptyFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxFifoEmptyFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxFifoEmptyFlag\r\n", io->stdOut);
  }
  if (flags&kUART_TxFifoOverflowFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_TxFifoOverflowFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxFifoOverflowFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxFifoOverflowFlag\r\n", io->stdOut);
  }
  if (flags&kUART_RxFifoOverflowFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUART_RxFifoOverflowFlag\r\n", io->stdOut);
  }
#endif
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  if (flags&kUSART_RxReady) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_RxReady\r\n", io->stdOut);
  }
  if (flags&kUSART_RxIdleFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_RxIdleFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_TxReady) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_TxReady\r\n", io->stdOut);
  }
  if (flags&kUSART_TxIdleFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_TxIdleFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_CtsState) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_CtsState\r\n", io->stdOut);
  }
  if (flags&kUSART_DeltaCtsFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_DeltaCtsFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_TxDisableFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_TxDisableFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_HardwareOverrunFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_HardwareOverrunFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_RxBreakFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_RxBreakFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_RxStartFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_RxStartFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_FramErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_FramErrorFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_ParityErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_ParityErrorFlag\r\n", io->stdOut);
  }
  if (flags&kUSART_RxNoiseFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_RxNoiseFlag\r\n", io->stdOut);
  }
  #if defined(FSL_FEATURE_USART_HAS_ABERR_CHECK) && FSL_FEATURE_USART_HAS_ABERR_CHECK
  if (flags&kUSART_AutoBaudErrorFlag) {
    McuShell_SendStatusStr((unsigned char*)"", (unsigned char*)"kUSART_AutoBaudErrorFlag\r\n", io->stdOut);
  }
  #endif
#endif
}
#endif

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[96];

  McuShell_SendStatusStr((unsigned char*)"McuUart485", (unsigned char*)"RS-485 UART settings\r\n", io->stdOut);
#if McuUart485_CONFIG_USE_LOGGER
  McuShell_SendStatusStr((unsigned char*)"  logging", McuUart485_doLogging?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
  McuShell_SendStatusStr((unsigned char*)"  HW TxEn", McuUart485_CONFIG_USE_HW_OE_RTS?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  uint32_t flags;

#if !McuUart485_CONFIG_USE_HW_OE_RTS
   McuGPIO_GetPinStatusString(RS485_TxEn, buf, sizeof(buf));
   McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
   McuShell_SendStatusStr((unsigned char*)"  TxEn", buf, io->stdOut);
#endif
  flags = McuUart485_CONFIG_UART_GET_FLAGS(McuUart485_CONFIG_UART_DEVICE);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), flags);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  flags", buf, io->stdOut);
  DecodeUARTFlags(flags, io) ;
#endif

  McuUtility_Num32uToStr(buf, sizeof(buf), McuUart485_CONFIG_UART_BAUDRATE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  baud", buf, io->stdOut);

#if McuLib_CONFIG_CPU_IS_ESP32
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"buffer: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), RS485_ESP_BUF_SIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" bytes\r\n");
  McuShell_SendStatusStr((unsigned char*)"  uart", buf, io->stdOut);
#endif

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Rx: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), McuUart485_CONFIG_UART_RX_QUEUE_LENGTH);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", Response: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), McuUart485_CONFIG_UART_RESPONSE_QUEUE_LENGTH);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  queues", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuUart485", (unsigned char*)"Group of RS-485 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  McuShell_SendHelpStr((unsigned char*)"  clear <flags>", (unsigned char*)"Clear UART ISR flags\r\n", io->stdOut);
#endif
  McuShell_SendHelpStr((unsigned char*)"  log on|off", (unsigned char*)"Turn logging on or off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuUart485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuUart485 help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuUart485 status")==0)) {
    *handled = true;
    return PrintStatus(io);
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
  } else if (McuUtility_strncmp((char*)cmd, "McuUart485 clear ", sizeof("McuUart485 clear ")-1)==0) {
    int32_t flags;
  #if McuLib_CONFIG_CPU_IS_KINETIS
    status_t status;
  #endif
    const unsigned char *p;

    *handled = true;
    p = cmd + sizeof("McuUart485 clear ")-1;
    if (McuUtility_xatoi(&p, &flags)==ERR_OK) {
  #if McuLib_CONFIG_CPU_IS_KINETIS
      status = McuUart485_CONFIG_CLEAR_STATUS_FLAGS(McuUart485_CONFIG_UART_DEVICE, flags);
      McuShell_SendStr((unsigned char*)"status: ", io->stdOut);
      McuShell_SendNum32u(status, io->stdOut);
      McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  #elif McuLib_CONFIG_CPU_IS_LPC
      McuUart485_CONFIG_CLEAR_STATUS_FLAGS(McuUart485_CONFIG_UART_DEVICE, flags);
  #endif
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuUart485_CONFIG_USE_LOGGER
  } else if (McuUtility_strcmp((char*)cmd, "McuUart485 log on")==0) {
    *handled = TRUE;
    McuUart485_doLogging = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "McuUart485 log off")==0) {
    *handled = TRUE;
    McuUart485_doLogging = false;
    return ERR_OK;
#endif
  }
  return ERR_OK;
}

void McuUart485_Deinit(void) {
  vQueueDelete(RS485UartRxQueue);
  RS485UartRxQueue = NULL;
#if !McuUart485_CONFIG_USE_MODBUS
  vQueueDelete(RS485UartResponseQueue);
  RS485UartResponseQueue = NULL;
#endif
#if !McuUart485_CONFIG_USE_HW_OE_RTS
  McuUart485_GPIO_Deinit();
#endif
}

void McuUart485_Init(void) {
  InitUart();
  RS485UartRxQueue = xQueueCreate(McuUart485_CONFIG_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartRxQueue==NULL) {
    McuLog_fatal("failed creating RS-485 Rx queue");
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartRxQueue, "RS485UartRxQueue");
#if !McuUart485_CONFIG_USE_MODBUS
  RS485UartResponseQueue = xQueueCreate(McuUart485_CONFIG_UART_RESPONSE_QUEUE_LENGTH, sizeof(uint8_t));
  if (RS485UartResponseQueue==NULL) {
    McuLog_fatal("failed creating RS-485 response queue");
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(RS485UartResponseQueue, "RS485UartResponseQueue");
#endif
#if McuLib_CONFIG_CPU_IS_ESP32
  BaseType_t res;

  res = xTaskCreate(rs485uart_task, "rs485uart", (4*1024)/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+3, NULL);
  if (res==pdPASS) {
    McuLog_trace("created rs485-uart task");
  } else {
    McuLog_fatal("failed creating res485-uart task!");
  }
#endif
}

#endif /* #ifdef McuUart485_CONFIG_UART_DEVICE  */
