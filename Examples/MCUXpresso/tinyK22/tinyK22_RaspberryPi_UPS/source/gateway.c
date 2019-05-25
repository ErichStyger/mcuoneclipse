/*
 * doGateWay.c
 *
 *  Created on: 18.03.2019
 *      Author: Erich Styger
 */
#include "platform.h"
#if PL_CONFIG_USE_GATEWAY
#include "gateway.h"
#include "fsl_uart.h"
#include "fsl_lpuart.h"
#include "McuRB.h"
#include "McuRTOS.h"
#include "Shell.h"

/* OpenSDA UART */
#define BOARD_LPUART_BAUDRATE  (115200)
#define BOARD_LPUART_DEVICE    LPUART0
#define BOARD_LPUART_CLK_FREQ  CLOCK_GetFreq(kCLOCK_PllFllSelClk)

#define LINUX_RX_QUEUE_LENGTH   (512)
#define HOST_RX_QUEUE_LENGTH    (512)
static QueueHandle_t linuxRxQueue, hostRxQueue;
static bool GatewayLinuxToHostIsEnabled = true;
static bool GatewayHostToLinuxIsEnabled = true;
static TaskHandle_t txToLinuxTaskHndl, txToHostTaskHndl;
static uint32_t nofRx, nofTx;

bool GATEWAY_LinuxToHostIsEnabled(void) {
  return GatewayLinuxToHostIsEnabled;
}

void GATEWAY_SetLinuxToHostEnabled(bool isEnabled) {
  GatewayLinuxToHostIsEnabled = isEnabled;
  if (GatewayLinuxToHostIsEnabled) { /* wake up gateway tasks */
    vTaskResume(txToHostTaskHndl);
  }
}

bool GATEWAY_HostToLinuxIsEnabled(void) {
  return GatewayHostToLinuxIsEnabled;
}

void GATEWAY_SetHostToLinuxEnabled(bool isEnabled) {
  GatewayHostToLinuxIsEnabled = isEnabled;
  if (GatewayHostToLinuxIsEnabled) { /* wake up gateway tasks */
    vTaskResume(txToLinuxTaskHndl);
  }
}


void LPUART0_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = LPUART_GetStatusFlags(BOARD_LPUART_DEVICE);
  /* If new data arrived. */
  if (flags&(kLPUART_RxDataRegFullFlag|kLPUART_RxOverrunFlag)) {
    data = LPUART_ReadByte(BOARD_LPUART_DEVICE);
    (void)xQueueSendFromISR(hostRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  __DSB();
}

static void Init_LPUART(void) {
  lpuart_config_t config;

  CLOCK_SetLpuartClock(1U); /* 1: MCGFLLCLK , or MCGPLLCLK , or IRC48M clock as selected by SOPT2[PLLFLLSEL]. */
  LPUART_GetDefaultConfig(&config);
  config.baudRate_Bps = BOARD_LPUART_BAUDRATE;
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(BOARD_LPUART_DEVICE, &config, BOARD_LPUART_CLK_FREQ);
}
/*********************************************************************************************************/
static void Init_UART(void) {
  /* LPUART0 is the OpenSDA/K20 UART */
  /* UART to Raspberry Pi is using UART0 (Rx: PTD6, Tx PTD7) */
  uart_config_t config;

  UART_GetDefaultConfig(&config);
  config.baudRate_Bps = 115200;
  config.enableTx = true;
  config.enableRx = true;
  UART_Init(UART0, &config, CLOCK_GetFreq(SYS_CLK));
}

void UART0_RX_TX_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = UART_GetStatusFlags(UART0);
  /* If new data arrived. */
  if (flags&(kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)) {
    data = UART_ReadByte(UART0);
    (void)xQueueSendFromISR(linuxRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  __DSB();
}
/*********************************************************************************************************/
static void LPUartWriteStringBlocking(const unsigned char *str) { /* write to host */
  LPUART_WriteBlocking(BOARD_LPUART_DEVICE, str, strlen((char*)str));
}

void GW_WriteToHost(const unsigned char *str) {
  LPUartWriteStringBlocking(str);
}
/*********************************************************************************************************/
static void Shell_SendCharToLinux(unsigned char ch) {
  UART_WriteBlocking(UART0, &ch, 1); /* send to Raspberry Pi */
}

static void Shell_ReadCharFromLinux(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(linuxRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool Shell_CharFromLinuxPresent(void) {
  if (GatewayLinuxToHostIsEnabled) {
    return false;
  }
  return uxQueueMessagesWaiting(linuxRxQueue)!=0;
}

McuShell_ConstStdIOType GATEWAY_stdioLinuxToShell = {
    (McuShell_StdIO_In_FctType)Shell_ReadCharFromLinux, /* stdin */
    (McuShell_StdIO_OutErr_FctType)Shell_SendCharToLinux,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)Shell_SendCharToLinux,  /* stderr */
    Shell_CharFromLinuxPresent /* if input is not empty */
  };

uint8_t GATEWAY_LinuxToShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/
static void Shell_SendCharToHost(unsigned char ch) {
  LPUART_WriteBlocking(BOARD_LPUART_DEVICE, &ch, 1); /* send to host */
}

static void Shell_ReadCharFromHost(uint8_t *c) {
  uint8_t ch;

  if (xQueueReceive(hostRxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
}

static bool Shell_CharFromHostPresent(void) {
  if (GatewayHostToLinuxIsEnabled) {
    return false;
  }
  return uxQueueMessagesWaiting(hostRxQueue)!=0;
}

McuShell_ConstStdIOType GATEWAY_stdioHostToShell = {
    (McuShell_StdIO_In_FctType)Shell_ReadCharFromHost, /* stdin */
    (McuShell_StdIO_OutErr_FctType)Shell_SendCharToHost,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)Shell_SendCharToHost,  /* stderr */
    Shell_CharFromHostPresent /* if input is not empty */
  };

uint8_t GATEWAY_HostToShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/*********************************************************************************************************/
static void TxToHostTask(void *pv) {
  uint8_t chRx;
  portBASE_TYPE res;

  (void)pv; /* not used */
  for(;;) {
    if (!GatewayLinuxToHostIsEnabled) {
      vTaskSuspend(NULL); /* put myself to sleep */
    }
    res = xQueueReceive(linuxRxQueue, &chRx, portMAX_DELAY);
    if (!GatewayLinuxToHostIsEnabled) { /* were blocking, but now in non-gateway mode */
      (void)xQueueSendToFront(linuxRxQueue, &chRx, 0); /* put it back in to the queue */
    } else if (res!=errQUEUE_EMPTY) {
      LPUART_WriteBlocking(LPUART0, &chRx, 1); /* send to host */
      nofTx++;
    }
  }
}

static void TxToLinuxTask(void *pv) {
  uint8_t chRx;
  portBASE_TYPE res;

  (void)pv; /* not used */
  for(;;) {
    if (!GatewayHostToLinuxIsEnabled) {
      vTaskSuspend(NULL); /* put myself to sleep */
    }
    res = xQueueReceive(hostRxQueue, &chRx, portMAX_DELAY);
    if (!GatewayHostToLinuxIsEnabled) { /* were blocking, but now in non-gateway mode */
      (void)xQueueSendToFront(hostRxQueue, &chRx, 0); /* put it back in to the queue */
    } else if (res!=errQUEUE_EMPTY) {
      UART_WriteBlocking(UART0, &chRx, 1); /* send to Raspberry Pi */
      nofRx++;
    }
  }
}

uint32_t GATEWAY_GetNofRx(void) {
  return nofRx;
}

uint32_t GATEWAY_GetNofTx(void) {
  return nofTx;
}

void GATEWAY_Init(void) {
  GatewayHostToLinuxIsEnabled = true;
  GatewayLinuxToHostIsEnabled = true;
  /* initialize LPUART to host */
  Init_LPUART();
  LPUART_EnableInterrupts(BOARD_LPUART_DEVICE, kLPUART_RxDataRegFullInterruptEnable|kLPUART_RxOverrunFlag);
  EnableIRQ(LPUART0_IRQn);
  NVIC_SetPriority(LPUART0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

  LPUartWriteStringBlocking((unsigned char*)"\r\n********************************\r\n");
  LPUartWriteStringBlocking((unsigned char*)"* UART gateway to Raspberry Pi *\r\n");
  LPUartWriteStringBlocking((unsigned char*)"********************************\r\n");

  /* init UART0 to Raspberry */
  Init_UART();
  UART_EnableInterrupts(UART0, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
  EnableIRQ(UART0_RX_TX_IRQn);
  NVIC_SetPriority(UART0_RX_TX_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

  nofRx = 0;
  nofTx = 0;

  linuxRxQueue = xQueueCreate(LINUX_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (linuxRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(linuxRxQueue, "LinuxRxQueue");

  hostRxQueue = xQueueCreate(HOST_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (hostRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(hostRxQueue, "HostRxQueue");

  if (xTaskCreate(
      TxToHostTask,  /* pointer to the task */
      "TxToHost", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      &txToHostTaskHndl /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(
      TxToLinuxTask,  /* pointer to the task */
      "TxToLinux", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      &txToLinuxTaskHndl /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
}

void GATEWAY_Deinit(void) {
  vQueueDelete(hostRxQueue);
  hostRxQueue = NULL;

  vQueueDelete(linuxRxQueue);
  linuxRxQueue = NULL;
}

#endif /* PL_CONFIG_USE_GATEWAY */
