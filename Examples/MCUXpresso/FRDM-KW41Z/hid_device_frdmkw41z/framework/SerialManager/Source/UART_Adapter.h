/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __UART_ADAPTER_H__
#define __UART_ADAPTER_H__

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#ifndef gUartIsrPrio_c
#define gUartIsrPrio_c (0x40)
#endif


/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
typedef struct uartState_tag uartState_t;

typedef void (*uartCallback_t)(uartState_t* state);

struct uartState_tag {
    uartCallback_t txCb;
    uartCallback_t rxCb;
    uint32_t txCbParam;
    uint32_t rxCbParam;
    uint8_t *pTxData;
    uint8_t *pRxData;
    volatile uint32_t txSize;
    volatile uint32_t rxSize;
};

enum uartStatus_tag {
    gUartSuccess_c,
    gUartInvalidParameter_c,
    gUartBusy_c
};

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
uint32_t UART_Initialize(uint32_t instance, uartState_t *pState);
uint32_t UART_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t UART_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t UART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t UART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t UART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t UART_IsTxActive(uint32_t instance);
uint32_t UART_EnableLowPowerWakeup(uint32_t instance);
uint32_t UART_DisableLowPowerWakeup(uint32_t instance);
uint32_t UART_IsWakeupSource(uint32_t instance);

uint32_t LPUART_Initialize(uint32_t instance, uartState_t *pState);
uint32_t LPUART_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t LPUART_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPUART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPUART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPUART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPUART_IsTxActive(uint32_t instance);
uint32_t LPUART_EnableLowPowerWakeup(uint32_t instance);
uint32_t LPUART_DisableLowPowerWakeup(uint32_t instance);
uint32_t LPUART_IsWakeupSource(uint32_t instance);

uint32_t LPSCI_Initialize(uint32_t instance, uartState_t *pState);
uint32_t LPSCI_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t LPSCI_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPSCI_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPSCI_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPSCI_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPSCI_IsTxActive(uint32_t instance);
uint32_t LPSCI_EnableLowPowerWakeup(uint32_t instance);
uint32_t LPSCI_DisableLowPowerWakeup(uint32_t instance);
uint32_t LPSCI_IsWakeupSource(uint32_t instance);

#endif /* __UART_ADAPTER_H__ */