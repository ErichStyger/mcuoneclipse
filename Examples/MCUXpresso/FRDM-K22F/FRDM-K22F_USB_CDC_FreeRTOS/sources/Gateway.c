/*
 * Gateway.c
 *
 *  Created on: 12.10.2017
 *      Author: Erich Styger
 */


#include "Gateway.h"
#include "FreeRTOS.h"
#include "task.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"

#define UART_USED    UART2  /* UART for GPS */
#define UART_USE_TX  (1) /* 1 to enable */

static uint8_t rxRingBuffer[128]; /* ring buffer for rx data */

/*! \todo move them off the global scope */
static volatile bool rxBufferEmpty = true;
static volatile bool txBufferFull = false;
static volatile bool txOnGoing = false;
static volatile bool rxOnGoing = false;

static uart_config_t user_config; /* user configuration */
static uart_handle_t g_uartHandle; /* UART device handle struct */

static void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData) {
  static unsigned int nofRxOverrunErrors = 0;
  static unsigned int nofRxRingBufferOverrunErrors = 0;

  (void)userData; /* not used */
  if (status==kStatus_UART_RxHardwareOverrun) {
    nofRxOverrunErrors++;
    UART_ClearStatusFlags(UART_USED, kUART_RxOverrunFlag); /* clear error */
  }
  if (status==kStatus_UART_TxIdle) { /* hardware finished Tx */
      txBufferFull = false; /* indicate that Tx buffer is ready for new data */
      txOnGoing = false; /* reset Tx flag */
  }
  if (status==kStatus_UART_RxIdle)   { /* hardware finished Rx */
      rxBufferEmpty = false; /* indicate that we have something in the Rx buffer */
      rxOnGoing = false; /* reset Rx flag */
  }
  if (status==kStatus_UART_RxRingBufferOverrun) { /* overrun of ring buffer */
    nofRxRingBufferOverrunErrors++;
    UART_TransferAbortReceive(UART_USED, handle); /* abort the current transfer */
  }
}

static void InitUART(void) {
  rxBufferEmpty = true;
  txBufferFull = false;
  txOnGoing = false;
  rxOnGoing = false;
 /*
   * user_config.baudRate_Bps = 38400;
   * user_config.parityMode = kUART_ParityDisabled;
   * user_config.stopBitCount = kUART_OneStopBit;
   * user_config.txFifoWatermark = 0;
   * user_config.rxFifoWatermark = 1;
   * user_config.enableTx = false;
   * user_config.enableRx = false;
   */
  UART_GetDefaultConfig(&user_config);
  user_config.baudRate_Bps = 38400;
  user_config.enableTx = true;
  user_config.enableRx = true;

  UART_Init(UART_USED, &user_config, CLOCK_GetFreq(SYS_CLK)/2);
  UART_TransferCreateHandle(UART_USED, &g_uartHandle, UART_UserCallback, NULL);
  UART_TransferStartRingBuffer(UART_USED, &g_uartHandle, rxRingBuffer, sizeof(rxRingBuffer));
}

static void UartTask(void *pvParams) {
  int i=0; /* counter */
 // uint8_t data;
  status_t status;
  uint32_t receivedBytes;

  (void)pvParams; /* not used parameter */
  DbgConsole_Printf("Starting UartTask\r\n");

  /* local receive buffer */
  uart_transfer_t rxTransfer; /* buffer descriptor for Rx data from the UART */
  uint8_t rxBuf; /* buffer memory, single character */
  uart_transfer_t txTransfer; /* buffer descriptor for tx data to UART */
  uint8_t txBuf[32];

  /* setup local rx buffer */
  rxTransfer.data = &rxBuf;
  rxTransfer.dataSize = sizeof(rxBuf); /* this is the number of bytes we want to receive (one only) in one transaction. */
                                       /* Note that we only get a notification from the lower layer if we receive all the bytes. */

  txTransfer.data = &txBuf[0];
  txTransfer.dataSize = sizeof(txBuf);

  for(;;) {
#if 0
    if (!rxOnGoing) { /* call UART_TransferReceiveNonBlocking() only if there is no other transfer pending */
       if (rxBufferEmpty) { /* start new transfer and receive new data into buffer */
        rxOnGoing = true;
        /* get first byte */
        status = UART_TransferReceiveNonBlocking(UART_USED, &g_uartHandle, &rxTransfer, &receivedBytes); /* this enables the UART interrupts and triggers receiving data */
      //  while(rxOnGoing) { /* poll until we have received something */
      //    vTaskDelay(pdMS_TO_TICKS(2)); /* wait */ /* call back should be called from UART ISR with kStatus_UART_RxIdle to reset flag */
      //  }
       } else { /* get the data from previous transfer which has been placed in rxTransfer buffer */
         receivedBytes = rxTransfer.dataSize; /* must be one byte, as buffer size was one */
       }
       while (receivedBytes>0) { /* get all the bytes from the buffer */
         /* print the data received to the debug console */
          for(i=0;i<rxTransfer.dataSize;i++) {
            DbgConsole_Putchar(rxTransfer.data[i]);
          }
          rxBufferEmpty = true; /* ready to get new data */
          /* get next byte, start new transaction */
          status = UART_TransferReceiveNonBlocking(UART_USED, &g_uartHandle, &rxTransfer, &receivedBytes);
        }
    }
#endif
    i++;
    vTaskDelay(pdMS_TO_TICKS(500));
#if UART_USE_TX
    if (!rxOnGoing) {
      /* send data to the GPS UART */
      strcpy((char*)txTransfer.data, "hello\r\n");
      txOnGoing = true;
      UART_TransferSendNonBlocking(UART_USED, &g_uartHandle, &txTransfer);
    }
#endif
  }
}


void GW_Init(void) {
  InitUART();
  if (xTaskCreate(UartTask,                         /* pointer to the task                      */
                  "UartTask",                       /* task name for kernel awareness debugging */
                  1024L/sizeof(portSTACK_TYPE),  /* task stack size                          */
                  NULL,                      /* optional task startup argument           */
                  5,                               /* initial priority                         */
                  NULL /* optional task handle to create           */
                  ) != pdPASS)
  {
      for(;;) {}
  }
}
