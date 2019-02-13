/*
 * Copyright 2016-2018 NXP
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
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * @file    MK22FN512xxx12_Project_Test.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"
#include <ctype.h> /* for isupper() */

#include "fsl_lpuart.h"

#define USE_UART_POLLING         (0)
#define USE_UART_INTERRUPT       (1 && !USE_UART_POLLING)
#define USE_UART_ISR_RINGBUFFER  (0 && !USE_UART_POLLING)

#define BOARD_LUART_BAUDRATE   (115200)
#define BOARD_LPUART_DEVICE    LPUART0
#define BOARD_LPUART_CLK_FREQ  CLOCK_GetFreq(kCLOCK_PllFllSelClk)

static void delay(void) {
  volatile int i = 1000000;
  while(i>0) {
    __asm("nop");
    i--;
  }
}

static void InitUart(void) {
  lpuart_config_t config;

  CLOCK_SetLpuartClock(1U); /* 1: MCGFLLCLK , or MCGPLLCLK , or IRC48M clock as selected by SOPT2[PLLFLLSEL]. */
  /*
   * config.baudRate_Bps = 115200U;
   * config.parityMode = kLPUART_ParityDisabled;
   * config.stopBitCount = kLPUART_OneStopBit;
   * config.txFifoWatermark = 0;
   * config.rxFifoWatermark = 0;
   * config.enableTx = false;
   * config.enableRx = false;
   */
  LPUART_GetDefaultConfig(&config);
  config.baudRate_Bps = BOARD_LUART_BAUDRATE;
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(BOARD_LPUART_DEVICE, &config, BOARD_LPUART_CLK_FREQ);
}

static void UartWriteString(const unsigned char *str) {
  LPUART_WriteBlocking(BOARD_LPUART_DEVICE, str, strlen((char*)str));
}

#if USE_UART_ISR_RINGBUFFER
  #define RX_RING_BUFFER_SIZE 20U
  #define ECHO_BUFFER_SIZE 8U

  /* LPUART user callback */
  void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

  static lpuart_handle_t g_lpuartHandle;
  static uint8_t g_tipString[] = "LPUART RX ring buffer example\r\nSend back received data\r\nEcho every 8 types\r\n";
  static uint8_t g_rxRingBuffer[RX_RING_BUFFER_SIZE] = {0}; /* RX ring buffer. */

  static uint8_t g_rxBuffer[ECHO_BUFFER_SIZE] = {'\0'}; /* Buffer for receive data to echo. */
  static uint8_t g_txBuffer[ECHO_BUFFER_SIZE] = {'\0'}; /* Buffer for send data to echo. */
  static volatile bool rxBufferEmpty = true;
  static volatile bool txBufferFull = false;
  static volatile bool txOnGoing = false;
  static volatile bool rxOnGoing = false;

  /* LPUART user callback */
  void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData) {
    if (kStatus_LPUART_TxIdle == status) {
      txBufferFull = false;
      txOnGoing = false;
    }
    if (kStatus_LPUART_RxIdle == status) {
      rxBufferEmpty = false;
      rxOnGoing = false;
    }
  }

  static void DoUartInterruptRingbuffer(void) {
    lpuart_config_t config;
    lpuart_transfer_t xfer;
    lpuart_transfer_t sendXfer;
    lpuart_transfer_t receiveXfer;
    size_t receivedBytes = 0U;
    int i;

    CLOCK_SetLpuartClock(1U);
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kLPUART_ParityDisabled;
     * config.stopBitCount = kLPUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(BOARD_LPUART_DEVICE, &config, BOARD_LPUART_CLK_FREQ);
    LPUART_TransferCreateHandle(BOARD_LPUART_DEVICE, &g_lpuartHandle, LPUART_UserCallback, NULL);
    LPUART_TransferStartRingBuffer(BOARD_LPUART_DEVICE, &g_lpuartHandle, g_rxRingBuffer, sizeof(g_rxRingBuffer));

    /* Send g_tipString out. */
    xfer.data = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing = true;
    LPUART_TransferSendNonBlocking(BOARD_LPUART_DEVICE, &g_lpuartHandle, &xfer);

    /* Wait send finished */
    while (txOnGoing) {
      __NOP();
    }

    /* Start to echo. */
    sendXfer.data = g_txBuffer;
    sendXfer.dataSize = ECHO_BUFFER_SIZE;
    receiveXfer.data = g_rxBuffer;
    receiveXfer.dataSize = ECHO_BUFFER_SIZE;
    for(;;) {
        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!rxBufferEmpty) && (!txBufferFull)) {
            memcpy(g_txBuffer, g_rxBuffer, ECHO_BUFFER_SIZE);
            rxBufferEmpty = true;
            txBufferFull = true;
        }
        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!rxOnGoing) && rxBufferEmpty) {
            rxOnGoing = true;
            LPUART_TransferReceiveNonBlocking(BOARD_LPUART_DEVICE, &g_lpuartHandle, &receiveXfer, &receivedBytes);
            if (ECHO_BUFFER_SIZE == receivedBytes) {
                rxBufferEmpty = false;
                rxOnGoing = false;
            }
        }
        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull) {
            txOnGoing = true;
            LPUART_TransferSendNonBlocking(BOARD_LPUART_DEVICE, &g_lpuartHandle, &sendXfer);
        }
        /* Delay some time, simulate the app is processing other things, input data save to ring buffer. */
        i = 0x10U;
        while (i--) {
            __NOP();
        }
    }
  }
#endif

#if USE_UART_INTERRUPT
  /*
    Ring buffer for data input and output, in this example, input data are saved
    to ring buffer in IRQ handler. The main function polls the ring buffer status,
    if there are new data, then send them out.
    Ring buffer full: (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) == txIndex)
    Ring buffer empty: (rxIndex == txIndex)
  */
  #define UART_RING_BUFFER_SIZE  (16)
  static uint8_t uartRingBuffer[UART_RING_BUFFER_SIZE];
  static volatile uint16_t txIndex; /* Index of the data to send out. */
  static volatile uint16_t rxIndex; /* Index of the memory to save new arrived data. */

  void LPUART0_IRQHandler(void) {
      uint8_t data;

      /* If new data arrived. */
      if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(BOARD_LPUART_DEVICE)) {
          data = LPUART_ReadByte(BOARD_LPUART_DEVICE);
          /* If ring buffer is not full, add data to ring buffer. */
          if (((rxIndex + 1) % UART_RING_BUFFER_SIZE) != txIndex) {
            uartRingBuffer[rxIndex] = data;
            rxIndex++;
            rxIndex %= UART_RING_BUFFER_SIZE;
          }
      }
      /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
        exception return operation might vector to incorrect interrupt */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
      __DSB();
  #endif
  }

  static void DoUartInterrupt(void) {
    InitUart();
    UartWriteString((unsigned char*)"Lpuart functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n");
    /* Enable RX interrupt. */
    LPUART_EnableInterrupts(BOARD_LPUART_DEVICE, kLPUART_RxDataRegFullInterruptEnable);
    EnableIRQ(LPUART0_IRQn);

    for(;;) {
        /* Send data only when LPUART TX register is empty and ring buffer has data to send out. */
        while ((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(BOARD_LPUART_DEVICE)) && (rxIndex != txIndex)) {
          uint8_t ch;

          ch = uartRingBuffer[txIndex];
          if (isupper(ch)) {
            ch = tolower(ch);
          } else {
            ch = toupper(ch);
          }
          LPUART_WriteByte(BOARD_LPUART_DEVICE, ch);
          txIndex++;
          txIndex %= UART_RING_BUFFER_SIZE;
        }
    }
  }
#endif /* USE_UART_INTERRUPT */

#if USE_UART_POLLING
static void DoUartPolling(void) {
  InitUart();
#if 0
  for(int i=0; i<10; i++) {
    GPIO_PortToggle(BOARD_LEDBLUE_GPIO, 1<<BOARD_LEDBLUE_PIN);
    delay();
  }
#endif
  UartWriteString((unsigned char*)"Lpuart polling example\r\ntinyK22 will send back received characters\r\n");
  for(;;) { /* echo application */
    uint8_t ch;

    GPIO_PortToggle(BOARD_LEDBLUE_GPIO, 1<<BOARD_LEDBLUE_PIN);
    LPUART_ReadBlocking(BOARD_LPUART_DEVICE, &ch, 1);
    if (isupper(ch)) {
      ch = tolower(ch);
    } else {
      ch = toupper(ch);
    }
    LPUART_WriteBlocking(BOARD_LPUART_DEVICE, &ch, 1);
  }
}
#endif
/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    BOARD_InitDebugConsole(); /* Init FSL debug console. Used for printf() */
    PRINTF("Hello World\n");
    delay();
#if USE_UART_POLLING
    DoUartPolling();
#elif USE_UART_INTERRUPT
    DoUartInterrupt();
#elif USE_UART_ISR_RINGBUFFER
    DoUartInterruptRingbuffer();
#endif
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
    }
    return 0 ;
}
