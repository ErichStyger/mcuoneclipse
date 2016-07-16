/**
 * \file uart-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board UART driver implementation
 *
 */

#ifndef __UART_MCU_H__
#define __UART_MCU_H__

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Table of base addresses for UART instances. */
UART_Type * const g_uartBase[UART_INSTANCE_COUNT] = UART_BASE_PTRS;

/* Table of base addresses for LPSCI (UART0) instances. */
UART0_Type * const g_lpsciBase = UART0_BASE_PTRS;

/* Table to save uart IRQ enum numbers defined in CMSIS files. */
const IRQn_Type g_uartIrqId[UART_INSTANCE_COUNT] = UART_RX_TX_IRQS;

/* Table to save lspci IRQ enum numbers defined in CMSIS files. */
const IRQn_Type g_lpsciIrqId = UART0_RX_TX_IRQS;

typedef enum {
    UART_0, UART_1, UART_2, UART_USB_CDC = 255,
} UartId_t;

/*!
 * \brief Initializes the UART object and MCU peripheral
 *
 * \param [IN] obj  UART object
 * \param [IN] tx   UART Tx pin name to be used
 * \param [IN] rx   UART Rx pin name to be used
 */
void UartMcuInit(Uart_t *obj, uint8_t uartId, PinNames tx, PinNames rx);

/*!
 * \brief Initializes the UART object and MCU peripheral
 *
 * \param [IN] obj          UART object
 * \param [IN] mode         Mode of operation for the UART
 * \param [IN] baudrate     UART baudrate
 * \param [IN] wordLength   packet length
 * \param [IN] stopBits     stop bits setup
 * \param [IN] parity       packet parity
 * \param [IN] flowCtrl     UART flow control
 */
void UartMcuConfig(Uart_t *obj, UartMode_t mode, uint32_t baudrate, WordLength_t wordLength,
        StopBits_t stopBits, Parity_t parity, FlowCtrl_t flowCtrl);

/*!
 * \brief DeInitializes the UART object and MCU peripheral
 *
 * \param [IN] obj  UART object
 */
void UartMcuDeInit(Uart_t *obj);

/*!
 * \brief Sends a character to the UART
 *
 * \param [IN] obj   UART object
 * \param [IN] data  Character to be sent
 * \retval status    [0: OK, 1: Busy]
 */
uint8_t UartMcuPutChar(Uart_t *obj, uint8_t data);

/*!
 * \brief Gets a character from the UART
 *
 * \param [IN] obj   UART object
 * \param [IN] data  Received character
 * \retval status    [0: OK, 1: Busy]
 */
uint8_t UartMcuGetChar(Uart_t *obj, uint8_t *data);

#endif // __UART_MCU_H__
