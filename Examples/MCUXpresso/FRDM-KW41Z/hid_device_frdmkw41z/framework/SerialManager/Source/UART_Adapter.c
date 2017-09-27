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


#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_os_abstraction.h"
#include "UART_Adapter.h"
#include "pin_mux.h"
#include "board.h"

#if FSL_FEATURE_SOC_UART_COUNT
#include "fsl_uart.h"
#endif

#if FSL_FEATURE_SOC_LPUART_COUNT
#include "fsl_lpuart.h"
#endif

#if FSL_FEATURE_SOC_LPSCI_COUNT
#include "fsl_lpsci.h"
#endif


/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
#if FSL_FEATURE_SOC_LPUART_COUNT
static LPUART_Type * mLpuartBase[] = LPUART_BASE_PTRS;
static IRQn_Type mLpuartIrqs[] = LPUART_RX_TX_IRQS;
static uartState_t * pLpuartStates[FSL_FEATURE_SOC_LPUART_COUNT];
static void LPUART_ISR(void);
#endif

#if FSL_FEATURE_SOC_UART_COUNT
static UART_Type * mUartBase[] = UART_BASE_PTRS;
static IRQn_Type mUartIrqs[] = UART_RX_TX_IRQS;
static uartState_t * pUartStates[FSL_FEATURE_SOC_UART_COUNT];
static void UART_ISR(void);
#endif

#if FSL_FEATURE_SOC_LPSCI_COUNT
static UART0_Type * mLpsciBase[] = UART0_BASE_PTRS;
static IRQn_Type mLpsciIrqs[] = UART0_RX_TX_IRQS;
static uartState_t * pLpsciStates[FSL_FEATURE_SOC_LPSCI_COUNT];
static void LPSCI_ISR(void);
#endif


/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/************************************************************************************/
/*                                     LPUART                                       */
/************************************************************************************/
uint32_t LPUART_Initialize(uint32_t instance, uartState_t *pState)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    LPUART_Type * base;
    lpuart_config_t config;
    
    if( (instance >= FSL_FEATURE_SOC_LPUART_COUNT) || (NULL == pState) )
    {
        status = gUartInvalidParameter_c;
    }
   else
   {
       base = mLpuartBase[instance];
       pLpuartStates[instance] = pState;
       pState->rxCbParam = 0;
       pState->txCbParam = 0;
       pState->pRxData = NULL;
       pState->pTxData = NULL;
       pState->rxSize = 0;
       pState->txSize = 0;
       
       configure_lpuart_pins(instance);
       LPUART_GetDefaultConfig(&config);
       config.enableRx = 1;
       config.enableTx = 1;
       LPUART_Init(base, &config, BOARD_GetLpuartClock(instance));
       LPUART_EnableInterrupts(base, kLPUART_RxDataRegFullInterruptEnable);
       OSA_InstallIntHandler(mLpuartIrqs[instance], LPUART_ISR);
       NVIC_SetPriority(mLpuartIrqs[instance], gUartIsrPrio_c >> (8 - __NVIC_PRIO_BITS));
       NVIC_EnableIRQ(mLpuartIrqs[instance]);
   }
#endif    
    return status;
}

/************************************************************************************/
uint32_t LPUART_SetBaudrate(uint32_t instance, uint32_t baudrate)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( instance >= FSL_FEATURE_SOC_LPUART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        LPUART_SetBaudRate(mLpuartBase[instance], baudrate, BOARD_GetLpuartClock(instance));
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_SendData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    LPUART_Type * base;
    
    if( (instance >= FSL_FEATURE_SOC_LPUART_COUNT) || (0 == size) || (NULL == pData) )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mLpuartBase[instance];
        
        OSA_InterruptDisable();
        if( pLpuartStates[instance]->txSize )
        {
            OSA_InterruptEnable();
            status = gUartBusy_c;
        }
        else
        {
            while( !(kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(base)) ) {}
            
            LPUART_WriteByte(base, *pData);
            pLpuartStates[instance]->pTxData = pData+1;
            pLpuartStates[instance]->txSize = size-1;
            OSA_InterruptEnable();
            
            LPUART_ClearStatusFlags(base, kLPUART_TxDataRegEmptyFlag);
            LPUART_EnableInterrupts(base, kLPUART_TxDataRegEmptyInterruptEnable);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( (instance >= FSL_FEATURE_SOC_LPUART_COUNT)  || (0 == size) || (NULL == pData) )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        OSA_InterruptDisable();
        if( pLpuartStates[instance]->rxSize )
        {
            status = gUartBusy_c;
        }
        else
        {
            pLpuartStates[instance]->rxSize = size;
            pLpuartStates[instance]->pRxData = pData;
        }
        OSA_InterruptEnable();
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t  LPUART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( instance >= FSL_FEATURE_SOC_LPUART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pLpuartStates[instance]->rxCb = cb;
        pLpuartStates[instance]->rxCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t  LPUART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( instance >= FSL_FEATURE_SOC_LPUART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pLpuartStates[instance]->txCb = cb;
        pLpuartStates[instance]->txCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_IsTxActive(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( instance < FSL_FEATURE_SOC_LPUART_COUNT )
    {
        if( pLpuartStates[instance]->txSize )
        {
            status = 1;
        }
        else
        {
            status = !(LPUART_GetStatusFlags(mLpuartBase[instance]) & kLPUART_TransmissionCompleteFlag);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_EnableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    status = LPUART_DisableLowPowerWakeup(instance);
    if( gUartSuccess_c == status )
    {
        LPUART_EnableInterrupts(mLpuartBase[instance], kLPUART_RxActiveEdgeInterruptEnable);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_DisableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPUART_COUNT
    LPUART_Type * base;
    
    if( instance >= FSL_FEATURE_SOC_LPUART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mLpuartBase[instance];
        LPUART_DisableInterrupts(base, kLPUART_RxActiveEdgeInterruptEnable);
        LPUART_ClearStatusFlags(base, kLPUART_RxActiveEdgeFlag);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPUART_IsWakeupSource(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_LPUART_COUNT
    if( instance < FSL_FEATURE_SOC_LPUART_COUNT )
    {
        status = !!(LPUART_GetStatusFlags(mLpuartBase[instance]) & kLPUART_RxActiveEdgeFlag);
    }
#endif
    return status;
}

/************************************************************************************/
/*                                      UART                                        */
/************************************************************************************/
uint32_t UART_Initialize(uint32_t instance, uartState_t *pState)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    UART_Type * base;
    uart_config_t config;
    
    if( (instance >= FSL_FEATURE_SOC_UART_COUNT) || (NULL == pState) )
    {
        status = gUartInvalidParameter_c;
    }
   else
   {
       base = mUartBase[instance];
       pUartStates[instance] = pState;
       pState->rxCbParam = 0;
       pState->txCbParam = 0;
       pState->pRxData = NULL;
       pState->pTxData = NULL;
       pState->rxSize = 0;
       pState->txSize = 0;
       
       configure_uart_pins(instance);
       UART_GetDefaultConfig(&config);
       config.enableRx = 1;
       config.enableTx = 1;
       UART_Init(base, &config, BOARD_GetUartClock(instance));
       UART_EnableInterrupts(base, kUART_RxDataRegFullInterruptEnable);
       OSA_InstallIntHandler(mUartIrqs[instance], UART_ISR);
       NVIC_SetPriority(mUartIrqs[instance], gUartIsrPrio_c >> (8 - __NVIC_PRIO_BITS));
       NVIC_EnableIRQ(mUartIrqs[instance]);
   }
#endif    
    return status;
}

/************************************************************************************/
uint32_t UART_SetBaudrate(uint32_t instance, uint32_t baudrate)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance >= FSL_FEATURE_SOC_UART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        UART_SetBaudRate(mUartBase[instance], baudrate, BOARD_GetUartClock(instance));
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_SendData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    UART_Type * base;
    
    if( instance >= FSL_FEATURE_SOC_UART_COUNT || !size || !pData )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mUartBase[instance];
        
        OSA_InterruptDisable();
        if( pUartStates[instance]->txSize )
        {
            OSA_InterruptEnable();
            status = gUartBusy_c;
        }
        else
        {
            while( !(kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(base)) ) {}
            
            pUartStates[instance]->txSize = size-1;
            pUartStates[instance]->pTxData = pData+1;
            UART_WriteByte(base, *pData);
            OSA_InterruptEnable();
            
            UART_ClearStatusFlags(base, kUART_TxDataRegEmptyFlag);
            UART_EnableInterrupts(base, kUART_TxDataRegEmptyInterruptEnable);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance >= FSL_FEATURE_SOC_UART_COUNT  || !size || !pData )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        OSA_InterruptDisable();
        if( pUartStates[instance]->rxSize )
        {
            status = gUartBusy_c;
        }
        else
        {
            pUartStates[instance]->rxSize = size;
            pUartStates[instance]->pRxData = pData;
        }
        OSA_InterruptEnable();
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance >= FSL_FEATURE_SOC_UART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pUartStates[instance]->rxCb = cb;
        pUartStates[instance]->rxCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance >= FSL_FEATURE_SOC_UART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pUartStates[instance]->txCb = cb;
        pUartStates[instance]->txCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_IsTxActive(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance < FSL_FEATURE_SOC_UART_COUNT )
    {
        if( pUartStates[instance]->txSize )
        {
            status = 1;
        }
        else
        {
            status = !(UART_GetStatusFlags(mUartBase[instance]) & kUART_TransmissionCompleteFlag);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_EnableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    status = UART_DisableLowPowerWakeup(instance);
    if( gUartSuccess_c == status )
    {
        UART_EnableInterrupts(mUartBase[instance], kUART_RxActiveEdgeInterruptEnable);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_DisableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_UART_COUNT
    UART_Type * base;
    
    if( instance >= FSL_FEATURE_SOC_UART_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mUartBase[instance];
        UART_DisableInterrupts(base, kUART_RxActiveEdgeInterruptEnable);
        UART_ClearStatusFlags(base, kUART_RxActiveEdgeFlag);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t UART_IsWakeupSource(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_UART_COUNT
    if( instance < FSL_FEATURE_SOC_UART_COUNT )
    {
        status = !!(UART_GetStatusFlags(mUartBase[instance]) & kUART_RxActiveEdgeFlag);
    }
#endif
    return status;
}
    

/************************************************************************************/
/*                                      LPSCI                                       */
/************************************************************************************/
uint32_t LPSCI_Initialize(uint32_t instance, uartState_t *pState)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    UART0_Type * base;
    lpsci_config_t config;
    
    if( (instance >= FSL_FEATURE_SOC_LPSCI_COUNT) || (NULL == pState) )
    {
        status = gUartInvalidParameter_c;
    }
   else
   {
       base = mLpsciBase[instance];
       pLpsciStates[instance] = pState;
       pState->rxCbParam = 0;
       pState->txCbParam = 0;
       pState->pRxData = NULL;
       pState->pTxData = NULL;
       pState->rxSize = 0;
       pState->txSize = 0;
       
       configure_lpsci_pins(instance);
       LPSCI_GetDefaultConfig(&config);
       config.enableRx = 1;
       config.enableTx = 1;
       LPSCI_Init(base, &config, BOARD_GetLpsciClock(instance));
       LPSCI_EnableInterrupts(base, kLPSCI_RxDataRegFullInterruptEnable);
       OSA_InstallIntHandler(mLpsciIrqs[instance], LPSCI_ISR);
       NVIC_SetPriority(mLpsciIrqs[instance], gUartIsrPrio_c >> (8 - __NVIC_PRIO_BITS));
       NVIC_EnableIRQ(mLpsciIrqs[instance]);
   }
#endif    
    return status;
}

/************************************************************************************/
uint32_t LPSCI_SetBaudrate(uint32_t instance, uint32_t baudrate)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        LPSCI_SetBaudRate(mLpsciBase[instance], baudrate, BOARD_GetLpsciClock(instance));
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_SendData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    UART0_Type * base;
    
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT || !size || !pData )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mLpsciBase[instance];
        
        OSA_InterruptDisable();
        if( pLpsciStates[instance]->txSize )
        {
            OSA_InterruptEnable();
            status = gUartBusy_c;
        }
        else
        {
            while( !(kLPSCI_TxDataRegEmptyFlag & LPSCI_GetStatusFlags(base)) ) {}
            
            pLpsciStates[instance]->txSize = size-1;
            pLpsciStates[instance]->pTxData = pData+1;
            LPSCI_WriteByte(base, *pData);
            OSA_InterruptEnable();
            
            LPSCI_ClearStatusFlags(base, kLPSCI_TxDataRegEmptyFlag);
            LPSCI_EnableInterrupts(base, kLPSCI_TxDataRegEmptyInterruptEnable);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT  || !size || !pData )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        OSA_InterruptDisable();
        if( pLpsciStates[instance]->rxSize )
        {
            status = gUartBusy_c;
        }
        else
        {
            pLpsciStates[instance]->rxSize = size;
            pLpsciStates[instance]->pRxData = pData;
        }
        OSA_InterruptEnable();
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pLpsciStates[instance]->rxCb = cb;
        pLpsciStates[instance]->rxCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        pLpsciStates[instance]->txCb = cb;
        pLpsciStates[instance]->txCbParam = cbParam;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_IsTxActive(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance < FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        if( pLpsciStates[instance]->txSize )
        {
            status = 1;
        }
        else
        {
            status = !(LPSCI_GetStatusFlags(mLpsciBase[instance]) & kLPSCI_TransmissionCompleteFlag);
        }
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_EnableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    status = LPSCI_DisableLowPowerWakeup(instance);
    if( gUartSuccess_c == status )
    {
        LPSCI_EnableInterrupts(mLpsciBase[instance], kLPSCI_RxActiveEdgeInterruptEnable);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_DisableLowPowerWakeup(uint32_t instance)
{
    uint32_t status = gUartSuccess_c;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    UART0_Type * base;
    
    if( instance >= FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        status = gUartInvalidParameter_c;
    }
    else
    {
        base = mLpsciBase[instance];
        LPSCI_DisableInterrupts(base, kLPSCI_RxActiveEdgeInterruptEnable);
        LPSCI_ClearStatusFlags(base, kLPSCI_RxActiveEdgeFlag);
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t LPSCI_IsWakeupSource(uint32_t instance)
{
    uint32_t status = 0;
#if FSL_FEATURE_SOC_LPSCI_COUNT
    if( instance < FSL_FEATURE_SOC_LPSCI_COUNT )
    {
        status = !!(LPSCI_GetStatusFlags(mLpsciBase[instance]) & kLPSCI_RxActiveEdgeFlag);
    }
#endif
    return status;
}

/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************* */
#if FSL_FEATURE_SOC_LPUART_COUNT
static void LPUART_ISR(void)
{
    uint32_t irq = __get_IPSR() - 16;
    uint32_t instance;
    uint32_t interrupts;
    LPUART_Type * base;
    uartState_t * pState;

    /* Get instance */
    for( instance=0; instance<FSL_FEATURE_SOC_LPUART_COUNT; instance++ )
    {
        if( irq == mLpuartIrqs[instance] )
        {
            break;
        }
    }
    
    base = mLpuartBase[instance];
    pState = pLpuartStates[instance];
    interrupts = LPUART_GetEnabledInterrupts(base);

    /* Check if data was received */
    if( (kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(base) )
    {
        uint8_t data = LPUART_ReadByte(base);
        LPUART_ClearStatusFlags(base, kLPUART_RxDataRegFullFlag);
        
        if( pState->rxSize )
        {
            pState->rxSize--;
        }
        
        if( pState->pRxData )
        {
            *(pState->pRxData) = data;
            pState->pRxData++;
        }

        if( (0 == pState->rxSize) && (NULL != pState->rxCb) )
        {
            pState->rxCb(pState);
        }
    }

    /* Check if data Tx has end */
    if( (kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(base)) &&
        (kLPUART_TxDataRegEmptyInterruptEnable & interrupts) )
    {
        if( pState->txSize )
        {
            pState->txSize--;
            
            LPUART_WriteByte(base, *(pState->pTxData++));
        }
        else if( 0 == pState->txSize )
        {
            LPUART_DisableInterrupts(base, kLPUART_TxDataRegEmptyInterruptEnable);

            if( NULL != pState->txCb )
            {
                pState->txCb(pState);
            }
        }
    }
    
    if( kLPUART_RxOverrunFlag & LPUART_GetStatusFlags(base) )
    {
        LPUART_ClearStatusFlags(base, kLPUART_RxOverrunFlag);
    }
}
#endif

/************************************************************************************/
#if FSL_FEATURE_SOC_UART_COUNT
static void UART_ISR(void)
{
    uint32_t irq = __get_IPSR() - 16;
    uint32_t instance;
    UART_Type * base;
    uartState_t * pState;

    /* Get instance */
    for( instance=0; instance<FSL_FEATURE_SOC_UART_COUNT; instance++ )
    {
        if( irq == mUartIrqs[instance] )
        {
            break;
        }
    }
    
    base = mUartBase[instance];
    pState = pUartStates[instance];
    /* Check if data was received */
    if( (kUART_RxDataRegFullFlag) & UART_GetStatusFlags(base) )
    {
        uint8_t data = UART_ReadByte(base);
        UART_ClearStatusFlags(base, kUART_RxDataRegFullFlag);
        
        if( pState->rxSize )
        {
            pState->rxSize--;
        }
        
        if( pState->pRxData )
        {
            *(pState->pRxData) = data;
            pState->pRxData++;
        }

        if( (0 == pState->rxSize) && (NULL != pState->rxCb) )
        {
            pState->rxCb(pState);
        }
    }
    /* Check if data Tx has end */
    if( (kUART_TxDataRegEmptyFlag) & UART_GetStatusFlags(base) &&
        (kUART_TxDataRegEmptyInterruptEnable) & UART_GetEnabledInterrupts(base) )
    {
        if( pState->txSize )
        {
            pState->txSize--;
            
            UART_WriteByte(base, *(pState->pTxData++));
        }
        else if( 0 == pState->txSize )
        {
            UART_DisableInterrupts(base, kUART_TxDataRegEmptyInterruptEnable);

            if( NULL != pState->txCb )
            {
                pState->txCb(pState);
            }
        }
    }
    
    if( kUART_RxOverrunFlag & UART_GetStatusFlags(base) )
    {
        UART_ClearStatusFlags(base, kUART_RxOverrunFlag);
    }    
}
#endif

/************************************************************************************/
#if FSL_FEATURE_SOC_LPSCI_COUNT
static void LPSCI_ISR(void)
{
    uint32_t irq = __get_IPSR() - 16;
    uint32_t instance;
    UART0_Type * base;
    uartState_t * pState;

    /* Get instance */
    for( instance=0; instance<FSL_FEATURE_SOC_LPSCI_COUNT; instance++ )
    {
        if( irq == mLpsciIrqs[instance] )
        {
            break;
        }
    }
    
    base = mLpsciBase[instance];
    pState = pLpsciStates[instance];
    /* Check if data was received */
    if( (kLPSCI_RxDataRegFullFlag) & LPSCI_GetStatusFlags(base) )
    {
        uint8_t data = LPSCI_ReadByte(base);
        LPSCI_ClearStatusFlags(base, kLPSCI_RxDataRegFullFlag);
        
        if( pState->rxSize )
        {
            pState->rxSize--;
        }
        
        if( pState->pRxData )
        {
            *(pState->pRxData) = data;
            pState->pRxData++;
        }

        if( (0 == pState->rxSize) && (NULL != pState->rxCb) )
        {
            pState->rxCb(pState);
        }
    }
    /* Check if data Tx has end */
    if( (kLPSCI_TxDataRegEmptyFlag) & LPSCI_GetStatusFlags(base) &&
        (kLPSCI_TxDataRegEmptyInterruptEnable) & LPSCI_GetEnabledInterrupts(base) )
    {
        if( pState->txSize )
        {
            pState->txSize--;
            
            LPSCI_WriteByte(base, *(pState->pTxData++));
        }
        else if( 0 == pState->txSize )
        {
            LPSCI_DisableInterrupts(base, kLPSCI_TxDataRegEmptyInterruptEnable);

            if( NULL != pState->txCb )
            {
                pState->txCb(pState);
            }
        }
    }

    if( kLPSCI_RxOverrunFlag & LPSCI_GetStatusFlags(base) )
    {
        LPSCI_ClearStatusFlags(base, kLPSCI_RxOverrunFlag);
    }
}
#endif