/*
 * ShellUart.c
 *
 *  Created on: 31.07.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "ShellUart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "fsl_usart.h"

#define RX_UART_QUEUE_LENGTH  (64)
static QueueHandle_t uartRxQueue;

#define SHELL_UART_DEVICE    USART0
#define SHELL_UART_BAUDRATE  38400

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
static void ShellUart_SendChar(unsigned char ch) {
  USART_WriteBlocking(SHELL_UART_DEVICE, &ch, 1);
}

static void ShellUart_ReadChar(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(uartRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool ShellUart_ChartPresent(void) {
  return uxQueueMessagesWaiting(uartRxQueue)!=0;
}

McuShell_ConstStdIOType ShellUart_stdio = {
    (McuShell_StdIO_In_FctType)ShellUart_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)ShellUart_SendChar,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)ShellUart_SendChar,  /* stderr */
    ShellUart_ChartPresent /* if input is not empty */
  };

uint8_t ShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/
static uint32_t nofOverruns = 0;

void USART0_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = USART_GetStatusFlags(SHELL_UART_DEVICE);
  if (flags&kUSART_HardwareOverrunFlag) {
    nofOverruns++; /* just for the statistics */
    /* Clear rx error state. */
    USART_ClearStatusFlags(SHELL_UART_DEVICE, kUSART_HardwareOverrunFlag);
  }
  /* If new data arrived. */
  if (flags&kUSART_RxReady) {
    data = USART_ReadByte(SHELL_UART_DEVICE);
    (void)xQueueSendFromISR(uartRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  __DSB();
}

static void InitUart(void) {
  usart_config_t config;

  /* Select the main clock as source clock of USART0. */
  CLOCK_Select(kUART0_Clk_From_MainClk);

  /* Default config by using USART_GetDefaultConfig():
   * config.baudRate_Bps = 9600U;
   * config.parityMode = kUSART_ParityDisabled;
   * config.stopBitCount = kUSART_OneStopBit;
   * config.bitCountPerChar = kUSART_8BitsPerChar;
   * config.loopback = false;
   * config.enableRx = false;
   * config.enableTx = false;
   * config.syncMode = kUSART_SyncModeDisabled;
   */
  USART_GetDefaultConfig(&config);
  config.baudRate_Bps = SHELL_UART_BAUDRATE;
  config.enableRx     = true;
  config.enableTx     = true;

  /* Initialize the USART with configuration. */
  USART_Init(SHELL_UART_DEVICE, &config, CLOCK_GetFreq(kCLOCK_MainClk));
  USART_EnableInterrupts(SHELL_UART_DEVICE, kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable);
  EnableIRQ(USART0_IRQn);
  NVIC_SetPriority(USART0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
}

void ShellUart_Deinit(void) {
  vQueueDelete(uartRxQueue);
  uartRxQueue = NULL;
}

void ShellUart_Init(void) {
  InitUart();
  uartRxQueue = xQueueCreate(RX_UART_QUEUE_LENGTH, sizeof(uint8_t));
  if (uartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(uartRxQueue, "UartRxQueue");
}

