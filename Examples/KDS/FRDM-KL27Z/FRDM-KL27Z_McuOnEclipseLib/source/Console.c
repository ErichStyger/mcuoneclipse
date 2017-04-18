/*
 * Console.c
 *
 *  Created on: 22.01.2017
 *      Author: Erich Styger
 */


#include "Console.h"
#include "fsl_lpuart.h"
#include "CLS1.h"

#define FULL_BLOCK  1

static void ReadChar(uint8_t *p) {
#if FULL_BLOCK
  status_t status;

  status = LPUART_ReadBlocking(LPUART0, p, 1); /* get char */
  if (status!=kStatus_Success) {
    *p = '\0'; /* error case */
  }
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
  LPUART_WriteBlocking(LPUART0, (const uint8_t*)&ch, sizeof(ch));
}

static bool HasInput(void) {
 // uint32_t flags;

  return TRUE;
#if 0
  flags = LPUART_GetStatusFlags(LPUART0);
  if (flags&kLPUART_RxDataRegFullFlag) {
    return TRUE;
  } else {
    return FALSE;
  }
#endif
}

static CLS1_ConstStdIOType stdio = {
  .stdIn = ReadChar,
  .stdOut = WriteChar,
  .stdErr = WriteChar,
  .keyPressed = HasInput
};

void CONSOLE_Init(void) {
  LPUART_SetBaudRate(LPUART0, 38400, CLOCK_GetPeriphClkFreq());
  CLS1_SetStdio(&stdio);
}

