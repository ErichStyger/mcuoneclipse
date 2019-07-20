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

/* OpenSDA UART to Host: LPUART */
/* UART to Linux/Raspberry Pi: UART0 */
#define BOARD_LPUART_BAUDRATE  (115200)

#define LINUX_RX_QUEUE_LENGTH   (512)
#define HOST_RX_QUEUE_LENGTH    (512)
static QueueHandle_t linuxRxQueue, hostRxQueue;
static bool gatewayLinuxToHostIsEnabled = true;
static bool gatewayHostToLinuxIsEnabled = true;
static TaskHandle_t txToLinuxTaskHndl, txToHostTaskHndl;
static uint32_t nofRx, nofTx;

bool GATEWAY_LinuxToHostIsEnabled(void) {
  return gatewayLinuxToHostIsEnabled;
}

void GATEWAY_SetLinuxToHostEnabled(bool isEnabled) {
  gatewayLinuxToHostIsEnabled = isEnabled;
  if (gatewayLinuxToHostIsEnabled) { /* wake up gateway tasks */
    vTaskResume(txToHostTaskHndl);
  }
}

bool GATEWAY_HostToLinuxIsEnabled(void) {
  return gatewayHostToLinuxIsEnabled;
}

void GATEWAY_SetHostToLinuxEnabled(bool isEnabled) {
  gatewayHostToLinuxIsEnabled = isEnabled;
  if (gatewayHostToLinuxIsEnabled) { /* wake up gateway tasks */
    vTaskResume(txToLinuxTaskHndl);
  }
}

void GATEWAY_UartWriteToHostCh(unsigned char ch) {
  LPUART_WriteBlocking(LPUART0, &ch, 1);
}

void GATEWAY_UartWriteToHostStr(const unsigned char *str) {
  LPUART_WriteBlocking(LPUART0, str, strlen((char*)str));
}

void GATEWAY_UartWriteToLinuxCh(unsigned char ch) {
  UART_WriteBlocking(UART0, &ch, 1);
}

void GATEWAY_UartWriteToLinuxStr(const unsigned char *str) {
  UART_WriteBlocking(UART0, str, strlen((char*)str));
}

void LPUART0_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken;

  flags = LPUART_GetStatusFlags(LPUART0);
  /* If new data arrived. */
  if (flags&(kLPUART_RxDataRegFullFlag|kLPUART_RxOverrunFlag)) {
    data = LPUART_ReadByte(LPUART0);
    (void)xQueueSendFromISR(hostRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      vPortYieldFromISR();
    }
  }
  __DSB();
}

static void Init_LPUART(void) {
  lpuart_config_t config;

  CLOCK_SetLpuartClock(1U); /* 1: MCGFLLCLK, or MCGPLLCLK, or IRC48M clock as selected by SOPT2[PLLFLLSEL]. */
  LPUART_GetDefaultConfig(&config);
  config.baudRate_Bps = BOARD_LPUART_BAUDRATE;
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(LPUART0, &config, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
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
static void Shell_SendCharToLinux(unsigned char ch) {
  GATEWAY_UartWriteToLinuxCh(ch);
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
  if (gatewayLinuxToHostIsEnabled) {
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
  GATEWAY_UartWriteToHostCh(ch);
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
  if (gatewayHostToLinuxIsEnabled) {
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
    if (!gatewayLinuxToHostIsEnabled) {
      vTaskSuspend(NULL); /* put myself to sleep */
    }
    res = xQueueReceive(linuxRxQueue, &chRx, portMAX_DELAY);
    if (!gatewayLinuxToHostIsEnabled) { /* we were blocking, but now in non-gateway mode */
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
    if (!gatewayHostToLinuxIsEnabled) {
      vTaskSuspend(NULL); /* put myself to sleep */
    }
    res = xQueueReceive(hostRxQueue, &chRx, portMAX_DELAY);
    if (!gatewayHostToLinuxIsEnabled) { /* were blocking, but now in non-gateway mode */
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

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[16];

  McuShell_SendStatusStr((unsigned char*)"gateway", (const unsigned char*)"\r\n", io->stdOut);
  McuUtility_Num8uToStr(buf, sizeof(buf), TINYK22_HAT_VERSION);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  HW version", buf, io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  host", gatewayHostToLinuxIsEnabled?(const unsigned char*)"Host -> Linux\r\n":(const unsigned char*)"Host -> Shell\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  linux", gatewayLinuxToHostIsEnabled?(const unsigned char*)"Linux -> Host\r\n":(const unsigned char*)"Linux -> Shell\r\n", io->stdOut);
  McuUtility_Num8uToStr(buf, sizeof(buf), GATEWAY_GetNofRx());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  #Rx", buf, io->stdOut);
  McuUtility_Num8uToStr(buf, sizeof(buf), GATEWAY_GetNofTx());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  #Tx", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"gateway", (unsigned char*)"Group of gateway commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  host to (shell|linux)", (unsigned char*)"Send host traffic to shell or linux\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  linux to (shell|host)", (unsigned char*)"Send linux traffic to shell or host\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t GATEWAY_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "gateway help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "gateway status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "gateway host to linux")==0) {
    gatewayHostToLinuxIsEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "gateway host to shell")==0) {
    gatewayHostToLinuxIsEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "gateway linux to host")==0) {
    gatewayLinuxToHostIsEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "gateway linux to shell")==0) {
    gatewayLinuxToHostIsEnabled = false;
    *handled = TRUE;
  }
  return res;
}

void GATEWAY_Init(void) {
  gatewayHostToLinuxIsEnabled = true;
  gatewayLinuxToHostIsEnabled = true;
  /* initialize LPUART to host */
  Init_LPUART();
  LPUART_EnableInterrupts(LPUART0, kLPUART_RxDataRegFullInterruptEnable|kLPUART_RxOverrunFlag);
  EnableIRQ(LPUART0_IRQn);
  NVIC_SetPriority(LPUART0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

  GATEWAY_UartWriteToHostStr((unsigned char*)"\r\n********************************\r\n");
  GATEWAY_UartWriteToHostStr((unsigned char*)"* UART gateway to Raspberry Pi *\r\n");
  GATEWAY_UartWriteToHostStr((unsigned char*)"********************************\r\n");

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
      tskIDLE_PRIORITY+3,  /* initial priority */
      &txToHostTaskHndl /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(
      TxToLinuxTask,  /* pointer to the task */
      "TxToLinux", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
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
