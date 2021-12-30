/*!
 * \file      uart-board.c
 *
 * \brief     Target board UART driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "board.h"
#include "uart-board.h"
#include "board-config.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_usart.h"

#define BOARD_DEFAULT_BAUDRATE	115200

typedef struct {
	UartId_t id;
	USART_Type *type;
	uint32_t srcClk;
	const IRQn_Type irqn;
	const uint32_t interruptEnable;
	const uint32_t interruptFlags;
	void (*IrqNotify)(UartNotifyId_t id);
} lpcUartHandle_t;

/**
  * Local Usart Handles
  * DO NOT CHANGE => If you need to change Usart settings, change it in board-config.h
  */
#if(LPC_NUMBER_OF_USARTS > 0)
static lpcUartHandle_t UsartHandle0 = {
	.id = UART_1,
	.type = LPC_USART1_TYPE,
	.irqn = LPC_USART1_IRQn,
	.interruptEnable = LPC_USART1_IRQ_ENABLE,
	.interruptFlags = LPC_USART1_IRQ_FLAGS
};
#endif
#if(LPC_NUMBER_OF_USARTS > 1)
static lpcUartHandle_t UsartHandle1 = {
	.id = UART_2,
	.type = LPC_USART2_TYPE,
	.irqn = LPC_USART2_IRQn,
	.interruptEnable = LPC_USART2_IRQ_ENABLE,
	.interruptFlags = LPC_USART2_IRQ_FLAGS
};
#endif

static void MapUartIdToHandle(UartId_t uartId, lpcUartHandle_t **handle);

/**
  * CAUTION:
  * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
  * You can also use the pin configuration tool of NXP.
  * This init function doesn't care about the handovered pins
  */
void UartMcuInit(Uart_t *obj, UartId_t uartId, PinNames tx, PinNames rx) {
	usart_config_t config;
	lpcUartHandle_t *handle;

	obj->UartId = uartId;
	MapUartIdToHandle(uartId, &handle);

#if(LPC_NUMBER_OF_USARTS > 0)
	if(handle == &UsartHandle0){
		handle->srcClk = LPC_USART1_CLK_FRQ;
	}
#endif
#if(LPC_NUMBER_OF_USARTS > 1)
	if(handle == &UsartHandle1){
		handle->srcClk = LPC_USART2_CLK_FRQ;
	}
#endif

	USART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEFAULT_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;

	USART_Init(handle->type, &config, handle->srcClk);

	/* Enable interrupts if there is a callback function */
	if (obj->IrqNotify != NULL) {
		handle->IrqNotify = obj->IrqNotify;
		USART_EnableInterrupts(handle->type, handle->interruptEnable);
		EnableIRQ(handle->irqn);
	}
}

void UartMcuConfig(Uart_t *obj, UartMode_t mode, uint32_t baudrate,
		WordLength_t wordLength, StopBits_t stopBits, Parity_t parity,
		FlowCtrl_t flowCtrl) {
	usart_config_t config;
	lpcUartHandle_t *handle;

	MapUartIdToHandle(obj->UartId, &handle);

	USART_GetDefaultConfig(&config);
	config.baudRate_Bps = baudrate;
	if (mode == TX_ONLY) {
		config.enableTx = true;
		config.enableRx = false;
	} else if (mode == RX_ONLY) {
		config.enableTx = false;
		config.enableRx = true;
	} else if (mode == RX_TX) {
		config.enableTx = true;
		config.enableRx = true;
	}

	if (parity == NO_PARITY) {
		config.parityMode = kUSART_ParityDisabled;
	} else if (parity == EVEN_PARITY) {
		config.parityMode = kUSART_ParityEven;
	} else {
		config.parityMode = kUSART_ParityOdd;
	}

	USART_Init(handle->type, &config, handle->srcClk);

	/* Enable interrupts if there is a callback function */
	if (obj->IrqNotify != NULL) {
		handle->IrqNotify = obj->IrqNotify;
		USART_EnableInterrupts(handle->type, handle->interruptEnable);
		EnableIRQ(handle->irqn);
	}
}

void UartMcuDeInit(Uart_t *obj) {
	lpcUartHandle_t *handle;
	MapUartIdToHandle(obj->UartId, &handle);

	/* Disable interrupts if there is a callback function */
	if (handle->IrqNotify != NULL) {
		USART_DisableInterrupts(handle->type, handle->interruptEnable);
		DisableIRQ(handle->irqn);
	}
	USART_Deinit(handle->type);
}

uint8_t UartMcuPutChar(Uart_t *obj, uint8_t data) {
	lpcUartHandle_t *handle;
	MapUartIdToHandle(obj->UartId, &handle);

	USART_WriteBlocking(handle->type, &data, sizeof(uint8_t));
	return 0; /* If blocking write returns, it was successful anyway */
}

uint8_t UartMcuGetChar(Uart_t *obj, uint8_t *data) {
	lpcUartHandle_t *handle;
	MapUartIdToHandle(obj->UartId, &handle);

	if (!(handle->interruptFlags & USART_GetStatusFlags(handle->type))) {
		return 1;
	}
	*data = USART_ReadByte(handle->type);
	return 0; /* If blocking write returns, it was successful anyway */
}

uint8_t UartMcuPutBuffer(Uart_t *obj, uint8_t *buffer, uint16_t size) {
	lpcUartHandle_t *handle;
	MapUartIdToHandle(obj->UartId, &handle);

	USART_WriteBlocking(handle->type, buffer, size);
	return 0; /* If blocking write returns, it was successful anyway */
}

uint8_t UartMcuGetBuffer(Uart_t *obj, uint8_t *buffer, uint16_t size,
		uint16_t *nbReadBytes) {
	lpcUartHandle_t *handle;
	MapUartIdToHandle(obj->UartId, &handle);

	*nbReadBytes = size;

	return USART_ReadBlocking(handle->type, buffer, size);
}

/**
  * Since the LoRaMac-node stack's Uart enum (UartId_t) goes from Uart1 to Uart2,
  * but the LPC series offers several Usarts on different pin settings, a short mapping
  * is required. This method sets the pointer "handle" to the corresponding handle of the given
  * uartId defined above.
  */
static void MapUartIdToHandle(UartId_t uartId, lpcUartHandle_t **handle) {

#if(LPC_NUMBER_OF_USARTS > 0)
	if(UsartHandle0.id == uartId){
		*handle = &UsartHandle0;
	}
#endif
#if(LPC_NUMBER_OF_USARTS > 1)
	if(UsartHandle1.id == uartId){
		*handle = &UsartHandle1;
	}
#endif
}

#if(LPC_NUMBER_OF_USARTS > 0)
void LPC_USART1_IRQ_HANDLER(void) {
	uint32_t irqs = USART_GetStatusFlags(UsartHandle0.type);
	if (UsartHandle0.interruptFlags & irqs) {
		if (UsartHandle0.IrqNotify != NULL) {
			if(irqs & kUSART_RxFifoNotEmptyFlag){
				UsartHandle0.IrqNotify(UART_NOTIFY_RX);
			}
			if(irqs & kUSART_TxFifoEmptyFlag){
				UsartHandle0.IrqNotify(UART_NOTIFY_TX);
			}
		}
	}
}

#endif
#if(LPC_NUMBER_OF_USARTS > 1)
void LPC_USART2_IRQ_HANDLER(void) {
	uint32_t irqs = USART_GetStatusFlags(UsartHandle1.type);
	if (UsartHandle1.interruptFlags & irqs) {
		if (UsartHandle1.IrqNotify != NULL) {
			if(irqs & kUSART_RxFifoNotEmptyFlag){
				UsartHandle1.IrqNotify(UART_NOTIFY_RX);
			}
			if(irqs & kUSART_TxFifoEmptyFlag){
				UsartHandle1.IrqNotify(UART_NOTIFY_TX);
			}
		}
	}
}
#endif
