/**
 * \file uart-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board UART driver implementation
 *
 */

#include "board.h"
#include "uart-board.h"
#include "fsl_uart_hal.h"
#include "fsl_lpuart_hal.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

void UartMcuInit(Uart_t *obj, uint8_t uartId, PinNames tx, PinNames rx)
{
    obj->UartId = uartId;

    GpioInit(&obj->Tx, tx, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);
    GpioInit(&obj->Rx, rx, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);

    /*! Only UART0 can be driven by an other clock source than the bus clock */
    if (obj->UartId == LPUART) {
        /* Enable clock for UART0 */
        CLOCK_SYS_EnableLpuartClock(0);

        /* Select different clock source for LPSCI. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
        CLOCK_SYS_SetLpuartSrc(0, kClockLpuartSrcMcgIrClk);
#else
        CLOCK_SYS_SetLpuartSrc(0, kClockLpuartSrcPllFllSel);
#endif
        /* Initialize LPSCI to a known state. */
        LPUART_HAL_Init (g_lpuartBase[0]);
    } else {
        /* Enable clock for UART1/UART2 */
        CLOCK_SYS_EnableUartClock(obj->UartId);
        UART_HAL_Init (g_uartBase[obj->UartId]);
    }
}

void UartMcuConfig(Uart_t *obj, UartMode_t mode, uint32_t baudrate, WordLength_t wordLength,
        StopBits_t stopBits, Parity_t parity, FlowCtrl_t flowCtrl)
{
    uint32_t uartSourceClock;

    if (obj->UartId == LPUART) {
        LPUART_Type *base = g_lpuartBase[0];
        IRQn_Type irq = g_lpuartIrqId[0];

        uartSourceClock = CLOCK_SYS_GetLpuartFreq(0);

        lpuart_parity_mode_t parityMode;
        if (parity == NO_PARITY)
            parityMode = kLpuartParityDisabled;
        else if (parity == EVEN_PARITY)
            parityMode = kLpuartParityEven;
        else if (parity == ODD_PARITY)
            parityMode = kLpuartParityOdd;
        else
            parityMode = kLpuartParityDisabled;

        lpuart_stop_bit_count_t stopBitCnt;
        if (stopBits == UART_1_STOP_BIT)
            stopBitCnt = kLpuartOneStopBit;
        else if (stopBits == UART_2_STOP_BIT)
            stopBitCnt = kLpuartTwoStopBit;
        else
            stopBitCnt = kLpuartOneStopBit;

        lpuart_bit_count_per_char_t bitCntPerCh;
        if (wordLength == UART_8_BIT)
            bitCntPerCh = kLpuart8BitsPerChar;
        else if (wordLength == UART_9_BIT)
            bitCntPerCh = kLpuart9BitsPerChar;
        else
            bitCntPerCh = kLpuart8BitsPerChar;

        /* Initialize LPSCI baud rate, bit count, parity and stop bit. */
        LPUART_HAL_SetBaudRate(base, uartSourceClock, baudrate);
        LPUART_HAL_SetBitCountPerChar(base, bitCntPerCh);
        LPUART_HAL_SetParityMode(base, parityMode);
#if FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT
        LPUART_HAL_SetStopBitCount(base, stopBitCnt);
#endif

        /* Enable interrupt for LPUART0 */
        INT_SYS_EnableIRQ(irq);

        /* Finally, enable the LPSCI transmitter and receiver*/
        if (mode == TX_ONLY) {
            LPUART_HAL_SetTransmitterCmd(base, true);
        } else if (mode == RX_ONLY) {
            LPUART_HAL_SetIntMode(base, kLpuartIntRxDataRegFull, true); /* Enable receiver interrupt */
            LPUART_HAL_SetReceiverCmd(base, true);
        } else {
            LPUART_HAL_SetTransmitterCmd(base, true);
            LPUART_HAL_SetIntMode(base, kLpuartIntRxDataRegFull, true); /* Enable receiver interrupt */
            LPUART_HAL_SetReceiverCmd(base, true);
        }
    } else {
        UART_Type *base = g_uartBase[obj->UartId];
        IRQn_Type irq = g_uartIrqId[obj->UartId];

        /* UART clock source is either system or bus clock depending on instance */
        uartSourceClock = CLOCK_SYS_GetUartFreq(obj->UartId);

        /* Disable receiver & transmitter before config procedure */
        UART_HAL_DisableTransmitter(base);
        UART_HAL_DisableReceiver(base);

        uart_parity_mode_t parityMode;
        if (parity == NO_PARITY)
            parityMode = kUartParityDisabled;
        else if (parity == EVEN_PARITY)
            parityMode = kUartParityEven;
        else if (parity == ODD_PARITY)
            parityMode = kUartParityOdd;
        else
            parityMode = kUartParityDisabled;

#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
        uart_stop_bit_count_t stopBitCnt;
        if (stopBits == UART_1_STOP_BIT) stopBitCnt = kUartOneStopBit;
        else if (stopBits == UART_2_STOP_BIT) stopBitCnt = kUartTwoStopBit;
        else stopBitCnt = kUartOneStopBit;
#endif

        /* Initialize UART baud rate, bit count, parity and stop bit. */
        UART_HAL_SetBaudRate(base, uartSourceClock, baudrate);
        UART_HAL_SetBitCountPerChar(base, (uart_bit_count_per_char_t) wordLength);
        UART_HAL_SetParityMode(base, parityMode);
#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
        UART_HAL_SetStopBitCount(base, stopBitCnt);
#endif

        /* Enable interrupt for UART1/UART2 */
        INT_SYS_EnableIRQ(irq);

        /* Finally, enable the UART transmitter and receiver*/
        if (mode == TX_ONLY) {
            UART_HAL_EnableTransmitter(base);
        } else if (mode == RX_ONLY) {
            UART_HAL_SetIntMode(base, kUartIntRxDataRegFull, true); /* Enable receiver interrupt */
            UART_HAL_EnableReceiver(base);
        } else {
            UART_HAL_EnableTransmitter(base);
            UART_HAL_SetIntMode(base, kUartIntRxDataRegFull, true); /* Enable receiver interrupt */
            UART_HAL_EnableReceiver(base);
        }
    }
}

void UartMcuDeInit(Uart_t *obj)
{
    if (obj->UartId == LPUART) {
        LPUART_Type *base = g_lpuartBase[0];
        IRQn_Type irq = g_lpuartIrqId[0];
        /* Wait until the data is completely shifted out of shift register */
        while (!LPUART_BRD_STAT_TC(base)) {
        }

        /* Disable the interrupt */
        INT_SYS_DisableIRQ(irq);

        /* Disable TX and RX */
        LPUART_HAL_SetTransmitterCmd(base, false);
        LPUART_HAL_SetReceiverCmd(base, false);

        /* Gate LPSCI module clock */
        CLOCK_SYS_DisableLpuartClock(0);
    } else {
        UART_Type *base = g_uartBase[obj->UartId];
        IRQn_Type irq = g_uartIrqId[obj->UartId];

        /* Wait until the data is completely shifted out of shift register */
        while (!(UART_BRD_S1_TC(base))) {
        }

        /* Disable the interrupt */
        INT_SYS_DisableIRQ(irq);

        /* Disable TX and RX */
        UART_HAL_DisableTransmitter(base);
        UART_HAL_DisableReceiver(base);

        /* Gate UART module clock */
        CLOCK_SYS_DisableUartClock(obj->UartId);
    }
}

uint8_t UartMcuPutChar(Uart_t *obj, uint8_t data)
{
    if (IsFifoFull(&obj->FifoTx) == false) {
        INT_SYS_DisableIRQGlobal();
        FifoPush(&obj->FifoTx, data);
        INT_SYS_EnableIRQGlobal();
        // Enable the UART Transmit interrupt
        if (obj->UartId == LPUART) {
            LPUART_HAL_SetIntMode(g_lpuartBase[0], kLpuartIntTxDataRegEmpty, true);
        } else {
            UART_HAL_SetIntMode(g_uartBase[obj->UartId], kUartIntTxDataRegEmpty, true);
        }
        return ERR_OK;   // OK
    }
    return ERR_TXFULL;   // Busy
}

uint8_t UartMcuGetChar(Uart_t *obj, uint8_t *data)
{
    if (IsFifoEmpty(&obj->FifoRx) == false) {
        INT_SYS_DisableIRQGlobal();
        *data = FifoPop(&obj->FifoRx);
        INT_SYS_EnableIRQGlobal();
        return ERR_OK;
    }
    return ERR_RXEMPTY;
}

void UartInterruptHandler(Uart_t *obj)
{
    uint8_t data;

    if (obj == NULL) return;

    /* Transmission finished */
    if (UART_HAL_GetStatusFlag(g_uartBase[obj->UartId], kUartTxDataRegEmpty)
            && UART_HAL_GetStatusFlag(g_uartBase[obj->UartId], kUartTxComplete)) {
        if (!IsFifoEmpty(&obj->FifoTx)) {
            data = FifoPop(&obj->FifoTx);
            //  Write one byte to the transmit data register
            UART_HAL_Putchar(g_uartBase[obj->UartId], data);
        } else {
            // Disable the UART0 Transmit interrupt
            UART_HAL_SetIntMode(g_uartBase[obj->UartId], kUartIntTxDataRegEmpty, false);
        }
        if (obj->IrqNotify != NULL) {
            obj->IrqNotify(UART_NOTIFY_TX);
        }
    }

    /* Data received */
    if (UART_HAL_GetStatusFlag(g_uartBase[obj->UartId], kUartRxOverrun)) {
        data = UART_D_REG(g_uartBase[obj->UartId]);
    }

    if (UART_HAL_GetStatusFlag(g_uartBase[obj->UartId], kUartRxDataRegFull)) {
        UART_HAL_Getchar(g_uartBase[obj->UartId], &data);
        if (IsFifoFull(&obj->FifoRx) == false) {
            // Read one byte from the receive data register
            FifoPush(&obj->FifoRx, data);
        }
        if (obj->IrqNotify != NULL) {
            obj->IrqNotify(UART_NOTIFY_RX);
        }
    }
}

/*!
 * LPUART IRQ Handler
 */
void LPUART0_IRQHandler(void)
{
    uint8_t data;
    LPUART_Type *base = g_lpuartBase[0];
    /* Transmission finished */
    if (LPUART_HAL_GetStatusFlag(base, kLpuartTxDataRegEmpty)
            && LPUART_HAL_GetStatusFlag(base, kLpuartTxComplete)) {
        if (!IsFifoEmpty(&Lpuart.FifoTx)) {
            data = FifoPop(&Lpuart.FifoTx);
            //  Write one byte to the transmit data register
            LPUART_HAL_Putchar(base, data);
        } else {
            // Disable the UART0 Transmit interrupt
            LPUART_HAL_SetIntMode(base, kLpuartIntTxDataRegEmpty, false);
        }
        if (Lpuart.IrqNotify != NULL) {
            Lpuart.IrqNotify(UART_NOTIFY_TX);
        }
    }

    /* Data received */
    if (LPUART_HAL_GetStatusFlag(base, kLpuartRxOverrun)) {
        /* Clear the flag, OR the rxDataRegFull will not be set any more */
        LPUART_HAL_ClearStatusFlag(base, kLpuartRxOverrun);
    }

    if (LPUART_HAL_GetStatusFlag(base, kLpuartRxDataRegFull)) {
        LPUART_HAL_Getchar(base, &data);
        if (IsFifoFull(&Lpuart.FifoRx) == false) {
            // Read one byte from the receive data register
            FifoPush(&Lpuart.FifoRx, data);
        }
        if (Lpuart.IrqNotify != NULL) {
            Lpuart.IrqNotify(UART_NOTIFY_RX);
        }
    }
}

/*!
 * UART0 IRQ handler
 */
void UART0_RX_TX_IRQHandler(void)
{
    UartInterruptHandler (&Uart0);
}

/*!
 * UART1 IRQ handler
 */
void UART1_RX_TX_IRQHandler(void)
{
    UartInterruptHandler (&Uart1);
}

/*!
 * UART2 IRQ handler
 */
void UART2_RX_TX_IRQHandler(void)
{
    UartInterruptHandler (&Uart2);
}
