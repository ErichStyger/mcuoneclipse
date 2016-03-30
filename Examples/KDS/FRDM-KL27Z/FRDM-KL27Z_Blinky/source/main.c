/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_lpuart.h"

static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

static uint8_t txbuff[] = "Lpuart polling example\r\nBoard will send back received characters\r\n";
#define DEMO_LPUART LPUART0
#define DEMO_LPUART_CLKSRC kCLOCK_McgIrc48MClk

static void InitLPUART(void) {
  lpuart_config_t config;

   CLOCK_SetLpuart0Clock(1U);
  /*
   * config.baudRate_Bps = 38400U;
   * config.parityMode = kLPUART_ParityDisabled;
   * config.stopBitCount = kLPUART_OneStopBit;
   * config.txFifoWatermark = 0;
   * config.rxFifoWatermark = 0;
   * config.enableTx = false;
   * config.enableRx = false;
   */
  LPUART_GetDefaultConfig(&config);
  config.baudRate_Bps = 38400;
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(DEMO_LPUART, &config, CLOCK_GetFreq(DEMO_LPUART_CLKSRC));
}

bool writable(LPUART_Type *base) {
  return (LPUART_GetStatusFlags(base)&LPUART_STAT_TDRE_MASK)!=0;
}

bool readable(LPUART_Type *base) {
  return (LPUART_GetStatusFlags(base)&LPUART_STAT_RDRF_MASK)!=0;
}

/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
#if 0
  BOARD_InitDebugConsole();
#else
  InitLPUART();
  LPUART_WriteBlocking(DEMO_LPUART, txbuff, sizeof(txbuff) - 1);
#endif

  /* Add your code here */
  for(;;) {
    if (readable(DEMO_LPUART)) {
      uint8_t ch;

      LPUART_ReadBlocking(DEMO_LPUART, &ch, 1);
      if (writable(DEMO_LPUART)) {
        LPUART_WriteBlocking(DEMO_LPUART, &ch, 1);
      }
    }

    GPIO_ClearPinsOutput(GPIOA, 1<<13u); /* blue led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOA, 1<<13u); /* blue led off */
    delay(1000000);

    GPIO_ClearPinsOutput(GPIOB, 1<<18u); /* red led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOB, 1<<18u); /* red led off */
    delay(500000);

    GPIO_ClearPinsOutput(GPIOB, 1<<19u); /* green led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOB, 1<<19u); /* green led off */
    delay(1000000);
  }
  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}
