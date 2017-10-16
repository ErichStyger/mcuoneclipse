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
#include "MsgQueue.h"

#define GATEWAY_ENABLE_GPS_RX      (1) /* 1 to enable Rx from GPS */
#define GATEWAY_ENABLE_GPS_TX      (1) /* 1 to enable Tx to GPS) */
#define GATEWAY_ENABLE_CDC_TO_GPS  (1 && GATEWAY_ENABLE_GPS_TX) /* 1 to enable data forwarding from USB CDC to GPS */
#define GATEWAY_ENABLE_GPS_TO_CDC  (1 && GATEWAY_ENABLE_GPS_RX) /* 1 to enable data forwarding from GPS to USB CDC */

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

static void UART_ChangeBaudRate(UART_MyDeviceDesc *device, uint32_t baudrate) {
  status_t res;
  uint32_t mask;

  /* abort any ongoing transfers */
  mask = UART_GetEnabledInterrupts(device->uart);

  UART_DisableInterrupts(device->uart, kUART_AllInterruptsEnable); /* disable all UART interrupts */
  UART_TransferAbortReceive(device->uart, device->sdk_handle);
  UART_TransferAbortSend(device->uart, device->sdk_handle);
  device->rxBufferEmpty = true;
  device->txBufferFull = false;
  device->txOnGoing = false;
  device->rxOnGoing = false;

  res = UART_SetBaudRate(device->uart, baudrate*2, CLOCK_GetFreq(SYS_CLK)); /*!!!!! Why baudrate*2???? */
  if (res!=kStatus_Success) {
    DbgConsole_Printf("Failed setting new baud rate %d!\n", baudrate);
  }
  UART_EnableInterrupts(device->uart, mask); /* restore interrupts */
}

static void InitUART(uart_handle_t *sdkHandle, UART_MyDeviceDesc *device) {
  uart_config_t config; /* user configuration */

  /* initialize user data descriptor */
  device->uart = UART2;
  device->sdk_handle = sdkHandle;
  device->rxBufferEmpty = true;
  device->txBufferFull = false;
  device->txOnGoing = false;
  device->rxOnGoing = false;
  device->nofRxOverrunErrors = 0;
  device->nofRxRingBufferOverrunErrors = 0;

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
  config.baudRate_Bps = 9600; /* default and initial baud rate */
  config.enableTx = true;
  config.enableRx = true;
  UART_Init(device->uart, &config, CLOCK_GetFreq(SYS_CLK)/2); /* really not clear to me why I have to divide the clock here??? */

  UART_TransferCreateHandle(device->uart, device->sdk_handle, UART_UserCallback, device);
  UART_TransferStartRingBuffer(device->uart, device->sdk_handle, rxRingBuffer, sizeof(rxRingBuffer));
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
#if GATEWAY_ENABLE_GPS_RX
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
#if GATEWAY_ENABLE_GPS_TO_CDC
          MSG_SendCharUart2Usb(rxTransfer.data[i]); /* forward to USB CDC */
#endif
        }
        /* initiate a new transfer */
        myDevice.rxBufferEmpty = true; /* ready to get new data */
        status = UART_TransferReceiveNonBlocking(myDevice.uart, myDevice.sdk_handle, &rxTransfer, &receivedBytes);
        /* stay inside while loop as long as we get more data */
      }
   }
#endif
#if GATEWAY_ENABLE_GPS_TX
    if ((counterMs%1000)==0) { /* every second */
      if (!myDevice.txOnGoing) {
        switchBaudCntr++;
        if (switchBaudCntr==10) { /* every 10 seconds */
          DbgConsole_Printf("Request change to 9600...\n");
          UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), (uint8_t*)"baud 9600\n");
          vTaskDelay(pdMS_TO_TICKS(50)); /* wait some time to allow UART to send out data */
          UART_ChangeBaudRate(&myDevice, 9600); /* now change my own baud rate */
        } else if (switchBaudCntr==20) {
          DbgConsole_Printf("Request change to 38400...\n");
          UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), (uint8_t*)"baud 38400\n");
          vTaskDelay(pdMS_TO_TICKS(50)); /* wait some to allow UART to send out data */
          UART_ChangeBaudRate(&myDevice, 38400);
        } else if (switchBaudCntr==30) {
          UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), (uint8_t*)"baud 115200\n");
          vTaskDelay(pdMS_TO_TICKS(50)); /* wait some to allow UART to send out data */
          UART_ChangeBaudRate(&myDevice, 115200);
          //switchBaudCntr = 0; /* reset */
        } else {
          DbgConsole_Printf("Send hello message: \"hello to the GPS\"\n");
          UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), (uint8_t*)"hello to the GPS\n");
        }
      }
    }
#endif
#if GATEWAY_ENABLE_CDC_TO_GPS
    /* get data from USB CDC queue and forward to UART/GPS */
    if (!myDevice.txOnGoing && MSG_NofElementsUsb2Uart()>0) {
      uint8_t localBuf[sizeof(txBuf)]; /* shall not be larger than txBuf, otherwise we will loose data */

      MSG_GetStringUsb2Uart(localBuf, sizeof(localBuf));
      UartSendStr(&myDevice, &txTransfer, txBuf, sizeof(txBuf), localBuf); /* send to GPS */
      DbgConsole_Printf("%s", localBuf); /* copy on debug console */
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(50));
    counterMs += 50;
  } /* for */
}

void GW_Init(void) {
  MSG_Init();
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
