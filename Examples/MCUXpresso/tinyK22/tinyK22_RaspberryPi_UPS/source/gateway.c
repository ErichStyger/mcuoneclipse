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

/* OpenSDA UART */
#define BOARD_LPUART_BAUDRATE  (115200)
#define BOARD_LPUART_DEVICE    LPUART0
#define BOARD_LPUART_CLK_FREQ  CLOCK_GetFreq(kCLOCK_PllFllSelClk)

static McuRB_Handle_t LpuartRingBuffer;
static McuRB_Handle_t UartRingBuffer;

void LPUART0_IRQHandler(void) {
  uint8_t data;
  uint32_t flags;

  flags = LPUART_GetStatusFlags(BOARD_LPUART_DEVICE);
  /* If new data arrived. */
  if (flags&(kLPUART_RxDataRegFullFlag|kLPUART_RxOverrunFlag)) {
    data = LPUART_ReadByte(BOARD_LPUART_DEVICE);
    (void)McuRB_Put(LpuartRingBuffer, &data);
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

  flags = UART_GetStatusFlags(UART0);
  /* If new data arrived. */
  if (flags&(kUART_RxDataRegFullFlag|kUART_RxOverrunFlag)) {
    data = UART_ReadByte(UART0);
    (void)McuRB_Put(UartRingBuffer, &data);
  }
  __DSB();
}

static void LPUartWriteStringBlocking(const unsigned char *str) {
  LPUART_WriteBlocking(BOARD_LPUART_DEVICE, str, strlen((char*)str));
}

void GW_WriteToHost(const unsigned char *str) {
  LPUartWriteStringBlocking(str);
}
/*********************************************************************************************************/
static uint32_t nofRx, nofTx;
#define RINGBUFFER_SIZE  1024

void GATEWAY_Process(void) {
  uint8_t chRx;

  /* check Rx from host */
  if (McuRB_Get(LpuartRingBuffer, &chRx)==0) {
    UART_WriteBlocking(UART0, &chRx, 1); /* send to Raspberry Pi */
    nofRx++;
  }
  /* check Rx from Raspberry */
  if (McuRB_Get(UartRingBuffer, &chRx)==0) {
    LPUART_WriteBlocking(LPUART0, &chRx, 1); /* send to host */
    nofTx++;
  }
}

uint32_t GATEWAY_GetNofRx(void) {
  return nofRx;
}

uint32_t GATEWAY_GetNofTx(void) {
  return nofTx;
}

static void UartTask(void *pv) {
  (void)pv; /* not used */
  for(;;) {
    if (McuRB_NofElements(LpuartRingBuffer)>0 || McuRB_NofElements(UartRingBuffer)>0) {
      GATEWAY_Process();
    } else {
      vTaskDelay(pdMS_TO_TICKS(20));
    }
  }
}

void GATEWAY_Init(void) {
  McuRB_Config_t rbConfig;

  McuRB_GetDefaultconfig(&rbConfig);
  rbConfig.nofElements = RINGBUFFER_SIZE;
  LpuartRingBuffer = McuRB_InitRB(&rbConfig);
  UartRingBuffer = McuRB_InitRB(&rbConfig);

  /* initialize LPUART to host */
  Init_LPUART();
  LPUART_EnableInterrupts(BOARD_LPUART_DEVICE, kLPUART_RxDataRegFullInterruptEnable|kLPUART_RxOverrunFlag);
  EnableIRQ(LPUART0_IRQn);
  LPUartWriteStringBlocking((unsigned char*)"\r\n********************************\r\n");
  LPUartWriteStringBlocking((unsigned char*)"* UART gateway to Raspberry Pi *\r\n");
  LPUartWriteStringBlocking((unsigned char*)"********************************\r\n");

  /* init UART0 to Raspberry */
  Init_UART();
  UART_EnableInterrupts(UART0, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
  EnableIRQ(UART0_RX_TX_IRQn);

  nofRx = 0;
  nofTx = 0;

  if (xTaskCreate(
      UartTask,  /* pointer to the task */
      "Uart", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
}

void GATEWAY_Deinit(void) {
  LpuartRingBuffer = McuRB_DeinitRB(LpuartRingBuffer);
  UartRingBuffer = McuRB_DeinitRB(UartRingBuffer);
}

#endif /* PL_CONFIG_USE_GATEWAY */
