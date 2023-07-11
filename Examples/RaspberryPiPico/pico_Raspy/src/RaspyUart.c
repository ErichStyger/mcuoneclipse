/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_UART
#include "RaspyUart.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuShell.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdlib.h"
#endif

#if PL_CONFIG_USE_USB_CDC
static void cdc_StdIOReadChar(uint8_t *c) {
  int res;

  res = getchar_timeout_us(500);
  if (res==-1) { /* no character present */
    *c = '\0';
  } else {
    *c = (uint8_t)res; /* return character */
  }
}

bool cdc_StdIOKeyPressed(void) {
  return true; /* hack, don't know if there is any other way? */
}

void cdc_StdIOSendChar(uint8_t ch) {
  putchar_raw(ch);
}

/* default standard I/O struct */
static McuShell_ConstStdIOType cdc_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)cdc_StdIOReadChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)cdc_StdIOSendChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)cdc_StdIOSendChar,
    .keyPressed = cdc_StdIOKeyPressed, /* if input is not empty */
  #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
  };
static uint8_t cdc_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
#endif

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 4
#define UART_RX_PIN 5

static QueueHandle_t uartRxQueue;  /* Rx from Raspy */
#define Raspy_UART_RX_QUEUE_LENGTH                 (4096)
static QueueHandle_t uartTxQueue;  /* Tx to Raspy */
#define Raspy_UART_TX_QUEUE_LENGTH                 (4096)

/* RX interrupt handler */
void on_uart_rx(void) {
  BaseType_t xHigherPriorityTaskWoken;
  while (uart_is_readable(UART_ID)) {
    uint8_t ch = uart_getc(UART_ID);
    (void)xQueueSendFromISR(uartRxQueue, &ch, &xHigherPriorityTaskWoken);
  }
}

static void initUart(void) {
  uart_init(UART_ID, 2400); /* Set up our UART with a basic baud rate. */

  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // Actually, we want a different speed
  // The call will return the actual baud rate selected, which will be as close as
  // possible to that requested
  int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

  // Set UART flow control CTS/RTS, we don't want these, so turn them off
  uart_set_hw_flow(UART_ID, false, false);

  // Set our data format
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

  // Turn off FIFO's - we want to do this character by character
  uart_set_fifo_enabled(UART_ID, false);

  // Set up a RX interrupt
  // We need to set up the handler first
  // Select correct interrupt for the UART we are using
  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

  // And set up and enable the interrupt handlers
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);

  // Now enable the UART to send interrupts - RX only
  uart_set_irq_enables(UART_ID, true, false);
}

static void UartPutc(unsigned char ch) {
  if (uart_is_writable(UART_ID)) {
    uart_putc(UART_ID, ch);
  }
}

static void UsbRxTask(void *pv) {
  BaseType_t res;
  unsigned char ch;
  bool workToDo;

  (void)pv; /* not used */
  for(;;) {
    workToDo = false;
    do {
      res = xQueueReceive(uartTxQueue, &ch, 0); /* poll queue */
      if (res==pdPASS) { /* write data to Raspy over UART */
        workToDo = true;
        UartPutc(ch);
      }
    } while(workToDo);
    /* check if we have data from USB CDC */
    while (cdc_StdIOKeyPressed()) { /* check USB CDC data stream */
      cdc_StdIOReadChar(&ch); /* read byte */
      if (ch!='\0') {
        workToDo = true;
        UartPutc(ch);
      } else {
        break; /* get out of loop, as no more data */
      }
    }
    if (!workToDo) { /* only delay if we are not busy */
      vTaskDelay(pdMS_TO_TICKS(5));
    }
  } /* for */
}

static void UartRxTask(void *pv) {
  unsigned char ch;
  BaseType_t res;

  (void)pv; /* not used */
  for(;;) {
    res = xQueueReceive(uartRxQueue, &ch, portMAX_DELAY);
    if (res==pdPASS) { /* forward to host over USB-CDC */
  #if PL_CONFIG_USE_USB_CDC
      cdc_StdIOSendChar(ch);
  #endif
    } else {
      McuLog_fatal("UartRxTask queue failed");
    }
  }
}

void RaspyUart_Init(void) {
  initUart();
  if (xTaskCreate(
      UartRxTask,  /* pointer to the task */
      "UartRx", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(
      UsbRxTask,  /* pointer to the task */
      "UsbRx", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  uartRxQueue = xQueueCreate(Raspy_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
   if (uartRxQueue==NULL) {
     McuLog_fatal("not able to create Rx queue");
     for(;;){} /* out of memory? */
   }
   vQueueAddToRegistry(uartRxQueue, "UartRxQueue");

   uartTxQueue = xQueueCreate(Raspy_UART_TX_QUEUE_LENGTH, sizeof(uint8_t));
   if (uartTxQueue==NULL) {
     McuLog_fatal("not able to create Tx queue");
     for(;;){} /* out of memory? */
   }
   vQueueAddToRegistry(uartTxQueue, "UartTxQueue");
}

#endif /* PL_CONFIG_USE_UART */
