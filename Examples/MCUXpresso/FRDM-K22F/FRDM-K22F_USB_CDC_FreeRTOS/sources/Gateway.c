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
#include "McuUtility.h"

#define UART_ENABLE_GPS_RX  (1) /* 1 to enable Rx emulation (Rx from GPS) */
#define UART_ENABLE_GPS_TX  (1) /* 1 to enable Tx emulation (Tx to GPS) */

static uint8_t rxRingBuffer[512]; /* ring buffer for rx data */

typedef struct {
  UART_Type *uart; /* pointer to UART hardware used */
  uart_handle_t *sdk_handle; /* SDK UART device handle */
  /* following fields are used for communication handshaking with the user callback */
  bool rxBufferEmpty;
  bool txBufferFull;
  bool txOnGoing;
  bool rxOnGoing;
  int nofRxOverrunErrors;
  int nofRxRingBufferOverrunErrors;
} UART_MyDeviceDesc;

static void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData) {
  UART_MyDeviceDesc *device = (UART_MyDeviceDesc*)userData;

  if (userData==NULL || handle->userData!=userData) {
    return; /* something is really wrong here? */
  }
  if (status==kStatus_UART_RxHardwareOverrun) {
    device->nofRxOverrunErrors++;
    UART_ClearStatusFlags(device->uart, kUART_RxOverrunFlag); /* clear error */
    device->rxOnGoing = FALSE;
  }
  if (status==kStatus_UART_RxRingBufferOverrun) { /* overrun of ring buffer */
    device->nofRxRingBufferOverrunErrors++;
    UART_TransferAbortReceive(device->uart, handle); /* abort the current transfer */
    device->rxOnGoing = FALSE;
  }
  if (status==kStatus_UART_TxIdle) { /* hardware finished Tx */
    device->txBufferFull = false; /* indicate that Tx buffer is ready for new data */
    device->txOnGoing = false; /* reset Tx flag */
  }
  if (status==kStatus_UART_RxIdle)   { /* hardware finished Rx */
    device->rxBufferEmpty = false; /* indicate that we have something in the Rx buffer */
    device->rxOnGoing = false; /* reset Rx flag */
  }
}

static void InitUART(uart_handle_t *sdkHandle, UART_MyDeviceDesc *userData) {
  uart_config_t config; /* user configuration */

  /* initialize user data descriptor */
  userData->uart = UART2;
  userData->sdk_handle = sdkHandle;
  userData->rxBufferEmpty = true;
  userData->txBufferFull = false;
  userData->txOnGoing = false;
  userData->rxOnGoing = false;
  userData->nofRxOverrunErrors = 0;
  userData->nofRxRingBufferOverrunErrors = 0;

  /* configure the UART */
  UART_GetDefaultConfig(&config); /* get default config */
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
  config.baudRate_Bps = 38400;
  config.enableTx = true;
  config.enableRx = true;
  UART_Init(userData->uart, &config, CLOCK_GetFreq(SYS_CLK)/2);

  UART_TransferCreateHandle(userData->uart, userData->sdk_handle, UART_UserCallback, userData);
  UART_TransferStartRingBuffer(userData->uart, userData->sdk_handle, rxRingBuffer, sizeof(rxRingBuffer));
}

static void UartSendStr(UART_MyDeviceDesc *device, uart_transfer_t *txTransfer, uint8_t *txBuf, size_t txBufSize, const uint8_t *str) {
  McuUtility_strcpy(txBuf, txBufSize, str); /* copy string into buffer */
  /* setup transfer descriptor */
  txTransfer->data = txBuf; /* pointer to data */
  txTransfer->dataSize = McuUtility_strlen((char*)txBuf); /* number of bytes */
  device->txOnGoing = true; /* flag will be reset by callback */
  UART_TransferSendNonBlocking(device->uart, device->sdk_handle, txTransfer);
}

static void UartTask(void *pvParams) {
  static UART_MyDeviceDesc myDevice; /* user data structure, used for status */
  static uart_handle_t sdkUartHandle; /* SDK UART device handle struct */
  status_t status;
  uint32_t receivedBytes;
  uint32_t counterMs = 0;
  uint32_t switchBaudCntr = 0;

  (void)pvParams; /* not used parameter */
  DbgConsole_Printf("------------------------\nStarting UartTask\n------------------------\n");

  /* local receive buffer */
  uart_transfer_t rxTransfer; /* buffer descriptor for Rx data from the UART */
  uint8_t rxBuf; /* buffer memory for rx, single character */
  uart_transfer_t txTransfer; /* buffer descriptor for tx data to UART */
  uint8_t txBuf[32];

  /* setup local rx buffer */
  rxTransfer.data = &rxBuf;
  rxTransfer.dataSize = sizeof(rxBuf); /* this is the number of bytes we want to receive (one only) in one transaction. */
                                       /* Note that we only get a notification from the lower layer if we receive all the bytes. */

  txTransfer.data = &txBuf[0];
  txTransfer.dataSize = sizeof(txBuf);

  InitUART(&sdkUartHandle, &myDevice);
  for(;;) {
#if UART_ENABLE_GPS_RX
    if (!myDevice.rxOnGoing) { /* call UART_TransferReceiveNonBlocking() only if there is no other transfer pending */
      /* check if we have something already in the Rx buffer */
      if (myDevice.rxBufferEmpty) {
        /* buffer is empty: start new transfer and receive new data into buffer */
        myDevice.rxOnGoing = true;
        /* start transaction for a single byte */
         status = UART_TransferReceiveNonBlocking(myDevice.uart, myDevice.sdk_handle, &rxTransfer, &receivedBytes); /* this enables the UART interrupts and triggers receiving data */
         if (status==kStatus_UART_RxBusy) {
           UART_TransferAbortReceive(myDevice.uart, myDevice.sdk_handle); /* abort the current transfer */
           myDevice.rxOnGoing = FALSE;
         }
      } else {
         /* rxBuffer is full. Get the number of bytes stored in the transfer buffer */
         receivedBytes = rxTransfer.dataSize;
      }
      while (receivedBytes>0) { /* handle the received data, if any */
        /* print the data received to the debug console */
        for(int i=0;i<rxTransfer.dataSize;i++) {
          DbgConsole_Putchar(rxTransfer.data[i]);
        }
        /* initiate a new transfer */
        myDevice.rxBufferEmpty = true; /* ready to get new data */
        status = UART_TransferReceiveNonBlocking(myDevice.uart, myDevice.sdk_handle, &rxTransfer, &receivedBytes);
        /* stay inside while loop as long as we get more data */
      }
   }
#endif
#if UART_ENABLE_GPS_TX
    if ((counterMs%1000)==0) { /* every second */
      if (!myDevice.txOnGoing) {
        switchBaudCntr++;
#if 0
        if (switchBaudCntr==10) {
          /* send data to the GPS UART */
           DbgConsole_Printf("Tx to GPS...\n");
           McuUtility_strcpy(txBuf, sizeof(txBuf), (uint8_t*)"baud 34800\n");
           /* setup transfer */
           txTransfer.data = &txBuf[0];
           txTransfer.dataSize = McuUtility_strlen((char*)txBuf);
           myDevice.txOnGoing = true; /* flag will be reset by callback */
           UART_TransferSendNonBlocking(myDevice.uart, &g_uartHandle, &txTransfer);
        } else if (switchBaudCntr==20) {
          /* send data to the GPS UART */
           DbgConsole_Printf("Tx to GPS...\n");
           McuUtility_strcpy(txBuf, sizeof(txBuf), (uint8_t*)"baud 115200\n");
           /* setup transfer */
           txTransfer.data = &txBuf[0];
           txTransfer.dataSize = McuUtility_strlen((char*)txBuf);
           myDevice.txOnGoing = true; /* flag will be reset by callback */
           UART_TransferSendNonBlocking(myDevice.uart, &g_uartHandle, &txTransfer);
           switchBaudCntr = 0; /* reset */
        } else {
#endif
          /* send data to the GPS UART */
          DbgConsole_Printf("Tx to GPS...\n");
          McuUtility_strcpy(txBuf, sizeof(txBuf), (uint8_t*)"hello to the GPS\n");
          /* setup transfer */
          txTransfer.data = &txBuf[0];
          txTransfer.dataSize = McuUtility_strlen((char*)txBuf);
          myDevice.txOnGoing = true; /* flag will be reset by callback */
          UART_TransferSendNonBlocking(myDevice.uart, myDevice.sdk_handle, &txTransfer);
 //       }
      }
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(50));
    counterMs += 50;
  } /* for */
}

void GW_Init(void) {
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
