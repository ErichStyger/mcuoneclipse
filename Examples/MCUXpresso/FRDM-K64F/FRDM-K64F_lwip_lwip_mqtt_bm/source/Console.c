/*
 * Console.c
 *
 *  Created on: 22.01.2017
 *      Author: Erich Styger
 */

#include "Console.h"

#define CONSOLE_USE_LPUART   0  /* LPUART or debug console */

#if CONSOLE_USE_LPUART
  #include "fsl_lpuart.h"
#else
  #include "fsl_debug_console.h"
  #include "fsl_uart.h"
#endif
#include "fsl_clock.h"
#include "CLS1.h"

#define FULL_BLOCK  1

static bool HasInput(void) {
#if CONSOLE_USE_LPUART
  return TRUE;
#else
  uint32_t flags;

  flags = UART_GetStatusFlags(UART0);
  if (flags&kUART_RxDataRegFullFlag) {
    return TRUE;
  }
  return FALSE;
#endif
  #if 0
  // uint32_t flags;

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
#else
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

void CONSOLE_Init(void) {
#if CONSOLE_USE_LPUART
  LPUART_SetBaudRate(LPUART0, 38400, CLOCK_GetPeriphClkFreq());
#else
  DbgConsole_Init((uint32_t)UART0, 38400, DEBUG_CONSOLE_DEVICE_TYPE_UART, CLOCK_GetCoreSysClkFreq());
#endif
  CLS1_SetStdio(&stdio);
}

