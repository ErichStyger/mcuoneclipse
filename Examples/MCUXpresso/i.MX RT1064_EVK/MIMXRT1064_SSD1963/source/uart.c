/*
 * uart.c
 *
 *  Created on: 11.01.2019
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "uart.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "MsgQueue.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"

typedef struct {
  LPUART_Type *uart; /* pointer to UART hardware used */
  lpuart_handle_t *sdk_handle; /* SDK UART device handle */
  /* following fields are used for communication handshaking with the user callback */
  bool rxBufferEmpty;
  bool txBufferFull;
  bool txOnGoing;
  bool rxOnGoing;
  int nofRxOverrunErrors;
  int nofRxRingBufferOverrunErrors;
} UART_MyDeviceDesc;

static uint8_t rxRingBuffer[512]; /* ring buffer for UART rx data */

static void UART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData) {
  UART_MyDeviceDesc *device = (UART_MyDeviceDesc*)userData;

  if (userData==NULL || handle->userData!=userData) {
    return; /* something is really wrong here? */
  }
  if (status==kStatus_LPUART_RxHardwareOverrun) {
    device->nofRxOverrunErrors++;
    LPUART_ClearStatusFlags(device->uart, kLPUART_RxOverrunFlag); /* clear error */
    device->rxOnGoing = FALSE;
  }
  if (status==kStatus_LPUART_RxRingBufferOverrun) { /* overrun of ring buffer */
    device->nofRxRingBufferOverrunErrors++;
    LPUART_TransferAbortReceive(device->uart, handle); /* abort the current transfer */
    device->rxOnGoing = FALSE;
  }
  if (status==kStatus_LPUART_TxIdle) { /* hardware finished Tx */
    device->txBufferFull = false; /* indicate that Tx buffer is ready for new data */
    device->txOnGoing = false; /* reset Tx flag */
  }
  if (status==kStatus_LPUART_RxIdle)   { /* hardware finished Rx */
    device->rxBufferEmpty = false; /* indicate that we have something in the Rx buffer */
    device->rxOnGoing = false; /* reset Rx flag */
  }
}

static void InitUART(lpuart_handle_t *sdkHandle, UART_MyDeviceDesc *device) {
  lpuart_config_t config; /* user configuration */

  /* initialize user data descriptor */
  device->uart = LPUART1;
  device->sdk_handle = sdkHandle;
  device->rxBufferEmpty = true;
  device->txBufferFull = false;
  device->txOnGoing = false;
  device->rxOnGoing = false;
  device->nofRxOverrunErrors = 0;
  device->nofRxRingBufferOverrunErrors = 0;

  /* configure the UART */
  LPUART_GetDefaultConfig(&config); /* get default config */
  /* default config has the following values:
   * config.baudRate_Bps = 38400;
   * config.parityMode = kUART_ParityDisabled;
   * config.stopBitCount = kUART_OneStopBit;
   * config.txFifoWatermark = 0;
   * config.rxFifoWatermark = 1;
   * config.enableTx = false;
   * config.enableRx = false;
   */
  /* overwrite config with our special values */
  config.baudRate_Bps = 38400; /* default and initial baud rate */
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(device->uart, &config, BOARD_DebugConsoleSrcFreq()); /* really not clear to me why I have to divide the clock here??? */

  LPUART_TransferCreateHandle(device->uart, device->sdk_handle, UART_UserCallback, device);
  LPUART_TransferStartRingBuffer(device->uart, device->sdk_handle, rxRingBuffer, sizeof(rxRingBuffer));
}

static void UartSendStr(UART_MyDeviceDesc *device, lpuart_transfer_t *txTransfer, uint8_t *txBuf, size_t txBufSize, const uint8_t *str) {
  McuUtility_strcpy(txBuf, txBufSize, str); /* copy string into buffer */
  /* setup transfer descriptor */
  txTransfer->data = txBuf; /* pointer to data */
  txTransfer->dataSize = McuUtility_strlen((char*)txBuf); /* number of bytes */
  device->txOnGoing = true; /* flag will be reset by callback */
  LPUART_TransferSendNonBlocking(device->uart, device->sdk_handle, txTransfer);
}

static void UartTask(void *pvParams) {
  static UART_MyDeviceDesc myDevice; /* user data structure, used for status */
  static lpuart_handle_t sdkUartHandle; /* SDK UART device handle struct */
  status_t status;
  uint32_t receivedBytes;

  (void)pvParams; /* not used parameter */

  /* local receive buffer */
  lpuart_transfer_t rxTransfer; /* buffer descriptor for Rx data from the UART */
  uint8_t rxBuf; /* buffer memory for rx, single character */
  lpuart_transfer_t txTransfer; /* buffer descriptor for tx data to UART */
  uint8_t txBuf[48];

  /* setup local rx buffer */
  rxTransfer.data = &rxBuf;
  rxTransfer.dataSize = sizeof(rxBuf); /* this is the number of bytes we want to receive (one only) in one transaction. */
                                       /* Note that we only get a notification from the lower layer if we receive all the bytes. */
  txTransfer.data = &txBuf[0];
  txTransfer.dataSize = sizeof(txBuf);

  InitUART(&sdkUartHandle, &myDevice);
  for(;;) {
    if (!myDevice.rxOnGoing) { /* call UART_TransferReceiveNonBlocking() only if there is no other transfer pending */
      /* check if we have something already in the Rx buffer */
      if (myDevice.rxBufferEmpty) {
        /* buffer is empty: start new transfer and receive new data into buffer */
        myDevice.rxOnGoing = true;
        /* start transaction for a single byte */
        status = LPUART_TransferReceiveNonBlocking(myDevice.uart, myDevice.sdk_handle, &rxTransfer, &receivedBytes); /* this enables the UART interrupts and triggers receiving data */
        if (status==kStatus_LPUART_RxBusy) {
          LPUART_TransferAbortReceive(myDevice.uart, myDevice.sdk_handle); /* abort the current transfer */
          myDevice.rxOnGoing = FALSE;
        }
      } else {
        /* rxBuffer is full. Get the number of bytes stored in the transfer buffer */
        receivedBytes = rxTransfer.dataSize;
      }
      while (receivedBytes>0) { /* handle the received data, if any */
        /* put the data into the Rx queue */
        for(int i=0;i<rxTransfer.dataSize;i++) {
          MSG_SendCharRxQueue(rxTransfer.data[i]);
        }
        /* initiate a new transfer */
        myDevice.rxBufferEmpty = true; /* ready to get new data */
        status = LPUART_TransferReceiveNonBlocking(myDevice.uart, myDevice.sdk_handle, &rxTransfer, &receivedBytes);
        /* stay inside while loop as long as we get more data */
      }
    }
    /* get data from the Tx queue and send it to the UART */
    if (!myDevice.txOnGoing && MSG_NofElementsTxQueue()>0) {
      uint8_t localBuf[sizeof(txBuf)]; /* shall not be larger than txBuf, otherwise we will loose data */

      MSG_GetStringTxQueue(localBuf, sizeof(localBuf));
      UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), localBuf); /* send to GPS */
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  } /* for */
}

void UART_Init(void) {
  MSG_Init();
  if (xTaskCreate(UartTask,      /* pointer to the task                      */
          "UartTask",            /* task name for kernel awareness debugging */
          500/sizeof(portSTACK_TYPE),  /* task stack size                          */
          NULL,                      /* optional task startup argument           */
          tskIDLE_PRIORITY+1,       /* initial priority                         */
          NULL /* optional task handle to create           */
          ) != pdPASS)
  {
      for(;;) {}
  }
}

