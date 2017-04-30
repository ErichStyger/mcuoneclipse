/*
 * Console.c
 *
 *  Created on: 22.01.2017
 *      Author: Erich Styger
 */

#include "Console.h"
#include "ConsoleRx.h"

#define CONSOLE_USE_LPUART   0  /* LPUART or debug console */
#define CONSOLE_USE_UART     1

#if CONSOLE_USE_LPUART
  #include "fsl_lpuart.h"
#elif CONSOLE_USE_UART
  #include "fsl_uart.h"
#elif CONSOLE_USE_LPUART
  #include <fsl_debug_console.h>
#endif
#include "fsl_clock.h"
#include "CLS1.h"

#define FULL_BLOCK  1

#define CONSOLE_UART                UART0
#define CONSOLE_UART_RX_TX_IRQn     UART0_RX_TX_IRQn

#if 0
#define UART_RING_BUFFER_SIZE   64
static uint8_t ConsoleRingBuffer[UART_RING_BUFFER_SIZE];
volatile uint16_t txIndex; /* Index of the data to send out. */
volatile uint16_t rxIndex; /* Index of the memory to save new arrived data. */
#endif

void UART0_RX_TX_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;

  flags = UART_GetStatusFlags(CONSOLE_UART);
  /* If new data arrived. */
  if (flags&(kUART_RxDataRegFullFlag | kUART_RxOverrunFlag)) {
    data = UART_ReadByte(CONSOLE_UART);

    (void)ConsoleRx_Put(data);
#if 0
    /* If ring buffer is not full, add data to ring buffer. */
    if (((rxIndex + 1) % UART_RING_BUFFER_SIZE) != txIndex) {
      ConsoleRingBuffer[rxIndex] = data;
      rxIndex++;
      rxIndex %= UART_RING_BUFFER_SIZE;
    }
#endif
  }
}

static bool HasInput(void) {
#if CONSOLE_USE_LPUART
  return TRUE;
#elif CONSOLE_USE_UART
  return ConsoleRx_NofElements()>0;
#elif CONSOLE_USE_LPUART
  uint32_t flags;

  flags = UART_GetStatusFlags(CONSOLE_UART);
  if (flags&(kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)) {
    return TRUE;
  }
  return FALSE;
#endif
#if 0
   uint32_t flags;

  flags = LPUART_GetStatusFlags(LPUART0);
  if (flags&kLPUART_RxDataRegFullFlag) {
    return TRUE;
  } else {
    return FALSE;
  }
#endif
}

static void ReadChar(uint8_t *p) {
#if FULL_BLOCK
#if CONSOLE_USE_LPUART
  status_t status;

  status = LPUART_ReadBlocking(LPUART0, p, 1); /* get char */
  if (status!=kStatus_Success) {
    *p = '\0'; /* error case */
  }
#elif CONSOLE_USE_UART
  if (ConsoleRx_Get(p)!=ERR_OK) {
    *p = '\0'; /* no input */
  }
#elif CONSOLE_USE_LPUART
  int ch;

  if (HasInput()) {
    ch = DbgConsole_Getchar(); /* blocking! */
    if (ch==-1) {
      *p = '\0'; /* error case */
    } else {
      *p = ch;
    }
  } else {
    *p = '\0'; /* no input */
  }
#endif
#else
  uint32_t flags;
  status_t status;

  flags = LPUART_GetStatusFlags(LPUART0);
  if (flags&kLPUART_RxDataRegFullFlag) { /* data received */
    status = LPUART_ReadBlocking(LPUART0, p, 1); /* get char */
    if (status!=kStatus_Success) {
      *p = '\0'; /* error case */
    }
  } else {
    *p = '\0';
  }
#endif
}

static void WriteChar(uint8_t ch) {
#if CONSOLE_USE_LPUART
  LPUART_WriteBlocking(LPUART0, (const uint8_t*)&ch, sizeof(ch));
#elif CONSOLE_USE_UART
  UART_WriteBlocking(CONSOLE_UART, (const uint8_t *)&ch, sizeof(ch));
#else
  (void)DbgConsole_Putchar(ch);
#endif
}

static CLS1_ConstStdIOType stdio = {
  .stdIn = ReadChar,
  .stdOut = WriteChar,
  .stdErr = WriteChar,
  .keyPressed = HasInput
};

uint8_t CONSOLE_SendChar(uint8_t ch) {
  WriteChar(ch);
  return ERR_OK;
}

CLS1_ConstStdIOType *CONSOLE_GetStdio(void) {
  return &stdio;
}

void CONSOLE_Init(void) {
#if CONSOLE_USE_LPUART
  LPUART_SetBaudRate(LPUART0, 38400, CLOCK_GetPeriphClkFreq());
#elif CONSOLE_USE_UART
  uart_config_t config;

  ConsoleRx_Init();
  UART_GetDefaultConfig(&config);
  config.baudRate_Bps = 38400;
  config.enableTx = true;
  config.enableRx = true;

  UART_Init(CONSOLE_UART, &config, CLOCK_GetCoreSysClkFreq());
  //UART_WriteBlocking(CONSOLE_UART, (const uint8_t *)"hello world!\r\n", sizeof("hello world!\r\n")-1);

  /* Enable RX interrupt. */
  UART_EnableInterrupts(CONSOLE_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
  EnableIRQ(CONSOLE_UART_RX_TX_IRQn);
#else
  DbgConsole_Init((uint32_t)UART0, 38400, DEBUG_CONSOLE_DEVICE_TYPE_UART, CLOCK_GetCoreSysClkFreq());
#endif
}

