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
#include "fsl_lpsci_hal.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

void UartMcuInit(Uart_t *obj, uint8_t uartId, PinNames tx, PinNames rx)
{
    obj->UartId = uartId;

    GpioInit(&obj->Tx, tx, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);
    GpioInit(&obj->Rx, rx, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);

    /*! Only UART0 can be driven by an other clock source than the bus clock */
    if (uartId == 0) {
        /* Enable clock for UART0 */
        CLOCK_SYS_EnableLpsciClock(obj->UartId);

        /* Select different clock source for LPSCI. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
        CLOCK_SYS_SetLpsciSrc(uartId, kClockLpsciSrcMcgIrClk);
#else
        CLOCK_SYS_SetLpsciSrc(uartId, kClockLpsciSrcPllFllSel);
#endif
        /* Initialize LPSCI to a known state. */
        LPSCI_HAL_Init (g_lpsciBase);
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

    if (obj->UartId == UART_0) {
        uartSourceClock = CLOCK_SYS_GetLpsciFreq(obj->UartId);

        lpsci_parity_mode_t parityMode;
        if (parity == NO_PARITY)
            parityMode = kLpsciParityDisabled;
        else if (parity == EVEN_PARITY)
            parityMode = kLpsciParityEven;
        else if (parity == ODD_PARITY)
            parityMode = kLpsciParityOdd;
        else
            parityMode = kLpsciParityDisabled;

        lpsci_stop_bit_count_t stopBitCnt;
        if (stopBits == UART_1_STOP_BIT)
            stopBitCnt = kLpsciOneStopBit;
        else if (stopBits == UART_2_STOP_BIT)
            stopBitCnt = kLpsciTwoStopBit;
        else
            stopBitCnt = kLpsciOneStopBit;

        /* Initialize LPSCI baud rate, bit count, parity and stop bit. */
        LPSCI_HAL_SetBaudRate(g_lpsciBase, uartSourceClock, baudrate);
        LPSCI_HAL_SetBitCountPerChar(g_lpsciBase, (lpsci_bit_count_per_char_t) wordLength);
        LPSCI_HAL_SetParityMode(g_lpsciBase, parityMode);
#if FSL_FEATURE_LPSCI_HAS_STOP_BIT_CONFIG_SUPPORT
        LPSCI_HAL_SetStopBitCount(g_lpsciBase, stopBitCnt);
#endif

        /* Enable interrupt for UART0 */
        INT_SYS_EnableIRQ (g_lpsciIrqId);

        /* Finally, enable the LPSCI transmitter and receiver*/
        if (mode == TX_ONLY) {
            LPSCI_HAL_EnableTransmitter (g_lpsciBase);
        } else if (mode == RX_ONLY) {
            LPSCI_HAL_SetIntMode(g_lpsciBase, kLpsciIntRxDataRegFull, true); /* Enable receiver interrupt */
            LPSCI_HAL_EnableReceiver (g_lpsciBase);
        } else {
            LPSCI_HAL_EnableTransmitter (g_lpsciBase);
            LPSCI_HAL_SetIntMode(g_lpsciBase, kLpsciIntRxDataRegFull, true); /* Enable receiver interrupt */
            LPSCI_HAL_EnableReceiver(g_lpsciBase);
        }
    } else {
        /* UART clock source is either system or bus clock depending on instance */
        uartSourceClock = CLOCK_SYS_GetUartFreq(obj->UartId);

        /* Disable receiver & transmitter before config procedure */
        UART_HAL_DisableTransmitter (g_uartBase[obj->UartId]);
        UART_HAL_DisableReceiver(g_uartBase[obj->UartId]);

        uart_parity_mode_t parityMode;
        if (parity == NO_PARITY)
            parityMode = kUartParityDisabled;
        else if (parity == EVEN_PARITY)
            parityMode = kUartParityEven;
        else if (parity == ODD_PARITY)
            parityMode = kUartParityOdd;
        else
            parityMode = kUartParityDisabled;

        uart_stop_bit_count_t stopBitCnt;
        if (stopBits == UART_1_STOP_BIT)
            stopBitCnt = kUartOneStopBit;
        else if (stopBits == UART_2_STOP_BIT)
            stopBitCnt = kUartTwoStopBit;
        else
            stopBitCnt = kUartOneStopBit;

        /* Initialize UART baud rate, bit count, parity and stop bit. */
        UART_HAL_SetBaudRate(g_uartBase[obj->UartId], uartSourceClock, baudrate);
        UART_HAL_SetBitCountPerChar(g_uartBase[obj->UartId],
                (uart_bit_count_per_char_t) wordLength);
        UART_HAL_SetParityMode(g_uartBase[obj->UartId], parityMode);
#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
        UART_HAL_SetStopBitCount(g_uartBase[obj->UartId], stopBitCnt);
#endif

        /* Enable interrupt for UART1/UART2 */
        INT_SYS_EnableIRQ (g_uartIrqId[obj->UartId]);

        /* Finally, enable the UART transmitter and receiver*/
        if (mode == TX_ONLY) {
            UART_HAL_EnableTransmitter(g_uartBase[obj->UartId]);
        } else if (mode == RX_ONLY) {
            UART_HAL_SetIntMode(g_uartBase[obj->UartId], kUartIntRxDataRegFull, true); /* Enable receiver interrupt */
            UART_HAL_EnableReceiver(g_uartBase[obj->UartId]);
        } else {
            UART_HAL_EnableTransmitter(g_uartBase[obj->UartId]);
            UART_HAL_SetIntMode(g_uartBase[obj->UartId], kUartIntRxDataRegFull, true); /* Enable receiver interrupt */
            UART_HAL_EnableReceiver(g_uartBase[obj->UartId]);
        }
    }
}

void UartMcuDeInit(Uart_t *obj)
{
    if (obj->UartId == UART_0) {
        /* Wait until the data is completely shifted out of shift register */
        while (!(UART0_BRD_S1_TC(g_lpsciBase))) {
        }

        /* Disable the interrupt */
        INT_SYS_DisableIRQ (g_lpsciIrqId);

        /* Disable TX and RX */
        LPSCI_HAL_DisableTransmitter (g_lpsciBase);
        LPSCI_HAL_DisableReceiver(g_lpsciBase);

        /* Gate LPSCI module clock */
        CLOCK_SYS_DisableLpsciClock(obj->UartId);
    } else {
        /* Wait until the data is completely shifted out of shift register */
        while (!(UART_BRD_S1_TC(g_uartBase[obj->UartId]))) {
        }

        /* Disable the interrupt */
        INT_SYS_DisableIRQ (g_uartIrqId[obj->UartId]);

        /* Disable TX and RX */
        UART_HAL_DisableTransmitter (g_uartBase[obj->UartId]);
        UART_HAL_DisableReceiver(g_uartBase[obj->UartId]);

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
        if (obj->UartId == UART_0) {
            LPSCI_HAL_SetIntMode(g_lpsciBase, kLpsciIntTxDataRegEmpty, true);
        } else {
            UART_HAL_SetIntMode(g_uartBase[obj->UartId], kUartIntTxDataRegEmpty, true);
        }
        return 0; // OK
    }
    return 1; // Busy
}

uint8_t UartMcuGetChar(Uart_t *obj, uint8_t *data)
{
    if (IsFifoEmpty(&obj->FifoRx) == false) {
        INT_SYS_DisableIRQGlobal();
        *data = FifoPop(&obj->FifoRx);
        INT_SYS_EnableIRQGlobal();
        return 0;
    }
    return 1;
}

/*!
 * UART0 IRQ handler
 */
void UART0_IRQHandler(void)
{
    uint8_t data;

    /* Transmission finished */
    if (LPSCI_HAL_GetStatusFlag(g_lpsciBase, kLpsciTxDataRegEmpty)
            && LPSCI_HAL_GetStatusFlag(g_lpsciBase, kLpsciTxComplete)) {
        if (!IsFifoEmpty(&Uart0.FifoTx)) {
            data = FifoPop(&Uart0.FifoTx);
            //  Write one byte to the transmit data register
            LPSCI_HAL_Putchar(g_lpsciBase, data);
        } else {
            // Disable the UART0 Transmit interrupt
            LPSCI_HAL_SetIntMode(g_lpsciBase, kLpsciIntTxDataRegEmpty, false);
        }
        if (Uart0.IrqNotify != NULL) {
            Uart0.IrqNotify(UART_NOTIFY_TX);
        }
    }

    /* Data received */
    if (LPSCI_HAL_GetStatusFlag(g_lpsciBase, kLpsciRxOverrun)) {
        /* Clear the flag, OR the rxDataRegFull will not be set any more */
        LPSCI_HAL_ClearStatusFlag(g_lpsciBase, kLpsciRxOverrun);
    }

    if (LPSCI_HAL_GetStatusFlag(g_lpsciBase, kLpsciRxDataRegFull)) {
        LPSCI_HAL_Getchar(g_lpsciBase, &data);
        if (IsFifoFull(&Uart0.FifoRx) == false) {
            // Read one byte from the receive data register
            FifoPush(&Uart0.FifoRx, data);
        }
        if (Uart0.IrqNotify != NULL) {
            Uart0.IrqNotify(UART_NOTIFY_RX);
        }
    }
}

/*!
 * UART1 IRQ handler
 */
void UART1_IRQHandler(void)
{
    uint8_t data;

    /* Transmission finished */
    if (UART_HAL_GetStatusFlag(UART1, kUartTxDataRegEmpty)
            && UART_HAL_GetStatusFlag(UART1, kUartTxComplete)) {
        if (!IsFifoEmpty(&Uart1.FifoTx)) {
            data = FifoPop(&Uart1.FifoTx);
            //  Write one byte to the transmit data register
            UART_HAL_Putchar(UART1, data);
        } else {
            // Disable the UART0 Transmit interrupt
            UART_HAL_SetIntMode(UART1, kUartIntTxDataRegEmpty, false);
        }
        if (Uart1.IrqNotify != NULL) {
            Uart1.IrqNotify(UART_NOTIFY_TX);
        }
    }

    /* Data received */
    if (UART_HAL_GetStatusFlag(UART1, kUartRxOverrun)) {
        data = UART0_D;
    }

    if (UART_HAL_GetStatusFlag(UART1, kUartRxDataRegFull)) {
        UART_HAL_Getchar(UART1, &data);
        if (IsFifoFull(&Uart1.FifoRx) == false) {
            // Read one byte from the receive data register
            FifoPush(&Uart1.FifoRx, data);
        }
        if (Uart1.IrqNotify != NULL) {
            Uart1.IrqNotify(UART_NOTIFY_RX);
        }
    }
}

/*!
 * UART2 IRQ handler
 */
void UART2_IRQHandler(void)
{
    uint8_t data;

    /* Transmission finished */
    if (UART_HAL_GetStatusFlag(UART2, kUartTxDataRegEmpty)
            && UART_HAL_GetStatusFlag(UART2, kUartTxComplete)) {
        if (!IsFifoEmpty(&Uart2.FifoTx)) {
            data = FifoPop(&Uart2.FifoTx);
            //  Write one byte to the transmit data register
            UART_HAL_Putchar(UART2, data);
        } else {
            // Disable the UART0 Transmit interrupt
            UART_HAL_SetIntMode(UART2, kUartIntTxDataRegEmpty, false);
        }
        if (Uart1.IrqNotify != NULL) {
            Uart1.IrqNotify(UART_NOTIFY_TX);
        }
    }

    /* Data received */
    if (UART_HAL_GetStatusFlag(UART2, kUartRxOverrun)) {
        UART_HAL_Getchar(UART2, &data);
    }

    if (UART_HAL_GetStatusFlag(UART2, kUartRxDataRegFull)) {
        UART_HAL_Getchar(UART2, &data);
        if (IsFifoFull(&Uart2.FifoRx) == false) {
            // Read one byte from the receive data register
            FifoPush(&Uart2.FifoRx, data);
        }
        if (Uart2.IrqNotify != NULL) {
            Uart2.IrqNotify(UART_NOTIFY_RX);
        }
    }
}
