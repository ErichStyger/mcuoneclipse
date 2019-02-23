/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MK64FN1M0VLL12
**      Version     : 1.00
**      Abstract    :
**
** 
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Vectors_Config.h                                                  
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup Vectors_Config_module Vectors_Config module documentation
**  @{
*/         

#include "PE_Types.h"
#include "Init_Config.h"
#include "Vectors_Config.h"

#if PEX_VECTOR_TABLE /* Is Vector table handled by Processor Expert? */
  
/*
** ===================================================================
**     Method      :  UnhandledInterrupt (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled common interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(UnhandledInterrupt);
PE_ISR(UnhandledInterrupt)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_NMI (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_NMI interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_NMI);
PE_ISR(Unhandled_ivINT_NMI)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Hard_Fault (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Hard_Fault interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Hard_Fault);
PE_ISR(Unhandled_ivINT_Hard_Fault)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Mem_Manage_Fault (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Mem_Manage_Fault 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Mem_Manage_Fault);
PE_ISR(Unhandled_ivINT_Mem_Manage_Fault)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Bus_Fault (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Bus_Fault interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Bus_Fault);
PE_ISR(Unhandled_ivINT_Bus_Fault)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Usage_Fault (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Usage_Fault interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Usage_Fault);
PE_ISR(Unhandled_ivINT_Usage_Fault)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved7 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved7 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved7);
PE_ISR(Unhandled_ivINT_Reserved7)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved8 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved8 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved8);
PE_ISR(Unhandled_ivINT_Reserved8)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved9 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved9 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved9);
PE_ISR(Unhandled_ivINT_Reserved9)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved10 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved10 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved10);
PE_ISR(Unhandled_ivINT_Reserved10)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SVCall (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SVCall interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SVCall);
PE_ISR(Unhandled_ivINT_SVCall)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DebugMonitor (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DebugMonitor interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DebugMonitor);
PE_ISR(Unhandled_ivINT_DebugMonitor)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved13 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved13 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved13);
PE_ISR(Unhandled_ivINT_Reserved13)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PendableSrvReq (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PendableSrvReq interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PendableSrvReq);
PE_ISR(Unhandled_ivINT_PendableSrvReq)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SysTick (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SysTick interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SysTick);
PE_ISR(Unhandled_ivINT_SysTick)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA0);
PE_ISR(Unhandled_ivINT_DMA0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA1);
PE_ISR(Unhandled_ivINT_DMA1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA2);
PE_ISR(Unhandled_ivINT_DMA2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA3 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA3 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA3);
PE_ISR(Unhandled_ivINT_DMA3)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA4 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA4 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA4);
PE_ISR(Unhandled_ivINT_DMA4)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA5 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA5 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA5);
PE_ISR(Unhandled_ivINT_DMA5)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA6 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA6 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA6);
PE_ISR(Unhandled_ivINT_DMA6)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA7 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA7 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA7);
PE_ISR(Unhandled_ivINT_DMA7)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA8 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA8 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA8);
PE_ISR(Unhandled_ivINT_DMA8)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA9 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA9 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA9);
PE_ISR(Unhandled_ivINT_DMA9)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA10 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA10 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA10);
PE_ISR(Unhandled_ivINT_DMA10)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA11 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA11 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA11);
PE_ISR(Unhandled_ivINT_DMA11)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA12 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA12 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA12);
PE_ISR(Unhandled_ivINT_DMA12)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA13 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA13 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA13);
PE_ISR(Unhandled_ivINT_DMA13)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA14 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA14 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA14);
PE_ISR(Unhandled_ivINT_DMA14)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA15 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA15 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA15);
PE_ISR(Unhandled_ivINT_DMA15)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DMA_Error (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DMA_Error interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DMA_Error);
PE_ISR(Unhandled_ivINT_DMA_Error)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_MCM (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_MCM interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_MCM);
PE_ISR(Unhandled_ivINT_MCM)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTFE (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_FTFE interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTFE);
PE_ISR(Unhandled_ivINT_FTFE)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Read_Collision (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Read_Collision interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Read_Collision);
PE_ISR(Unhandled_ivINT_Read_Collision)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_LVD_LVW (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_LVD_LVW interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_LVD_LVW);
PE_ISR(Unhandled_ivINT_LVD_LVW)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_LLWU (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_LLWU interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_LLWU);
PE_ISR(Unhandled_ivINT_LLWU)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_WDOG_EWM (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_WDOG_EWM interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_WDOG_EWM);
PE_ISR(Unhandled_ivINT_WDOG_EWM)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_RNG (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_RNG interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_RNG);
PE_ISR(Unhandled_ivINT_RNG)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2C0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_I2C0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_I2C0);
PE_ISR(Unhandled_ivINT_I2C0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2C1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_I2C1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_I2C1);
PE_ISR(Unhandled_ivINT_I2C1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SPI0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SPI0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SPI0);
PE_ISR(Unhandled_ivINT_SPI0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SPI1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SPI1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SPI1);
PE_ISR(Unhandled_ivINT_SPI1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2S0_Tx (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_I2S0_Tx interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_I2S0_Tx);
PE_ISR(Unhandled_ivINT_I2S0_Tx)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2S0_Rx (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_I2S0_Rx interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_I2S0_Rx);
PE_ISR(Unhandled_ivINT_I2S0_Rx)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART0_LON (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART0_LON interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART0_LON);
PE_ISR(Unhandled_ivINT_UART0_LON)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART0_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART0_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART0_RX_TX);
PE_ISR(Unhandled_ivINT_UART0_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART0_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART0_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART0_ERR);
PE_ISR(Unhandled_ivINT_UART0_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART1_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART1_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART1_RX_TX);
PE_ISR(Unhandled_ivINT_UART1_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART1_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART1_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART1_ERR);
PE_ISR(Unhandled_ivINT_UART1_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART2_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART2_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART2_RX_TX);
PE_ISR(Unhandled_ivINT_UART2_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART2_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART2_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART2_ERR);
PE_ISR(Unhandled_ivINT_UART2_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART3_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART3_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART3_RX_TX);
PE_ISR(Unhandled_ivINT_UART3_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART3_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART3_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART3_ERR);
PE_ISR(Unhandled_ivINT_UART3_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ADC0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ADC0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ADC0);
PE_ISR(Unhandled_ivINT_ADC0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CMP0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CMP0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CMP0);
PE_ISR(Unhandled_ivINT_CMP0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CMP1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CMP1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CMP1);
PE_ISR(Unhandled_ivINT_CMP1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTM0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_FTM0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTM0);
PE_ISR(Unhandled_ivINT_FTM0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTM1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_FTM1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTM1);
PE_ISR(Unhandled_ivINT_FTM1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTM2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_FTM2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTM2);
PE_ISR(Unhandled_ivINT_FTM2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CMT (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CMT interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CMT);
PE_ISR(Unhandled_ivINT_CMT)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_RTC (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_RTC interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_RTC);
PE_ISR(Unhandled_ivINT_RTC)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_RTC_Seconds (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_RTC_Seconds interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_RTC_Seconds);
PE_ISR(Unhandled_ivINT_RTC_Seconds)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT0);
PE_ISR(Unhandled_ivINT_PIT0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT1);
PE_ISR(Unhandled_ivINT_PIT1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT2);
PE_ISR(Unhandled_ivINT_PIT2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT3 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT3 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT3);
PE_ISR(Unhandled_ivINT_PIT3)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PDB0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PDB0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PDB0);
PE_ISR(Unhandled_ivINT_PDB0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_USB0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_USB0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_USB0);
PE_ISR(Unhandled_ivINT_USB0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_USBDCD (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_USBDCD interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_USBDCD);
PE_ISR(Unhandled_ivINT_USBDCD)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved71 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved71 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved71);
PE_ISR(Unhandled_ivINT_Reserved71)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_DAC0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_DAC0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_DAC0);
PE_ISR(Unhandled_ivINT_DAC0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_MCG (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_MCG interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_MCG);
PE_ISR(Unhandled_ivINT_MCG)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_LPTMR0 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_LPTMR0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_LPTMR0);
PE_ISR(Unhandled_ivINT_LPTMR0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PORTA (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PORTA interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PORTA);
PE_ISR(Unhandled_ivINT_PORTA)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PORTB (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PORTB interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PORTB);
PE_ISR(Unhandled_ivINT_PORTB)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PORTC (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PORTC interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PORTC);
PE_ISR(Unhandled_ivINT_PORTC)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PORTD (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PORTD interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PORTD);
PE_ISR(Unhandled_ivINT_PORTD)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PORTE (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_PORTE interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PORTE);
PE_ISR(Unhandled_ivINT_PORTE)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SWI (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SWI interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SWI);
PE_ISR(Unhandled_ivINT_SWI)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SPI2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SPI2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SPI2);
PE_ISR(Unhandled_ivINT_SPI2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART4_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART4_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART4_RX_TX);
PE_ISR(Unhandled_ivINT_UART4_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART4_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART4_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART4_ERR);
PE_ISR(Unhandled_ivINT_UART4_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART5_RX_TX (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART5_RX_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART5_RX_TX);
PE_ISR(Unhandled_ivINT_UART5_RX_TX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART5_ERR (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_UART5_ERR interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART5_ERR);
PE_ISR(Unhandled_ivINT_UART5_ERR)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CMP2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CMP2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CMP2);
PE_ISR(Unhandled_ivINT_CMP2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTM3 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_FTM3 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTM3);
PE_ISR(Unhandled_ivINT_FTM3)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved88 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved88 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved88);
PE_ISR(Unhandled_ivINT_Reserved88)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ADC1 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ADC1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ADC1);
PE_ISR(Unhandled_ivINT_ADC1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2C2 (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_I2C2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_I2C2);
PE_ISR(Unhandled_ivINT_I2C2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_ORed_Message_buffer (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_ORed_Message_buffer 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_ORed_Message_buffer);
PE_ISR(Unhandled_ivINT_CAN0_ORed_Message_buffer)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_Bus_Off (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_Bus_Off interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_Bus_Off);
PE_ISR(Unhandled_ivINT_CAN0_Bus_Off)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_Error (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_Error interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_Error);
PE_ISR(Unhandled_ivINT_CAN0_Error)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_Tx_Warning (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_Tx_Warning 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_Tx_Warning);
PE_ISR(Unhandled_ivINT_CAN0_Tx_Warning)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_Rx_Warning (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_Rx_Warning 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_Rx_Warning);
PE_ISR(Unhandled_ivINT_CAN0_Rx_Warning)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_CAN0_Wake_Up (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_CAN0_Wake_Up interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_CAN0_Wake_Up);
PE_ISR(Unhandled_ivINT_CAN0_Wake_Up)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_SDHC (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_SDHC interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_SDHC);
PE_ISR(Unhandled_ivINT_SDHC)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ENET_1588_Timer (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ENET_1588_Timer 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ENET_1588_Timer);
PE_ISR(Unhandled_ivINT_ENET_1588_Timer)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ENET_Transmit (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ENET_Transmit interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ENET_Transmit);
PE_ISR(Unhandled_ivINT_ENET_Transmit)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ENET_Receive (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ENET_Receive interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ENET_Receive);
PE_ISR(Unhandled_ivINT_ENET_Receive)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ENET_Error (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the unhandled ivINT_ENET_Error interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ENET_Error);
PE_ISR(Unhandled_ivINT_ENET_Error)
{
  PE_DEBUGHALT();
}


/* ISR prototype */
#if defined(__IAR_SYSTEMS_ICC__)
#ifdef __cplusplus
extern "C" void __iar_program_start( void );
#else
extern void __iar_program_start( void );
#endif

/* Referencing segment CSTACK in order to correctly initialize interrupt vector table. */
#pragma language=extended
#pragma segment="CSTACK"

/*lint -esym(765,__vector_table) Disable MISRA rule (8.10) checking for symbols (__vector_table). Definition of the interrupt vector table placed by linker on a predefined location. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */
/*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. Need to disable due to usage of @ operator in IAR compiler */

const tVectorTable __vector_table @ ".intvec" = {

#elif defined(__CWCC__)
#ifdef __cplusplus
extern "C" void __thumb_startup( void );
#else
extern void __thumb_startup( void );
#endif

extern uint32_t __SP_INIT[];

/* Pragma to place the interrupt vector table on correct location defined in linker file. */
#pragma define_section vectortable ".vectortable" ".vectortable" ".vectortable" far_abs R

/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */

__declspec(vectortable) const tVectorTable __vect_table = { /* Interrupt vector table */

#elif defined(__GNUC__)
#ifdef __cplusplus
extern "C" void __thumb_startup( void );
#else
extern void __thumb_startup( void );
#endif

extern uint32_t __SP_INIT;

/*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */

__attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */

#elif defined(__CC_ARM)
#ifdef __cplusplus
extern "C" void __thumb_startup( void );
#else
extern void __thumb_startup( void );
#endif

extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Limit;

/*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */

__attribute__ ((section (".vectortable"))) const tVectorTable __vect_table __attribute__((used)) = { /* Interrupt vector table */

#else /* defined(compiler ID) */
  #error Unsupported compiler
#endif /* defined(compiler ID) */

  /* ISR address                          No.  Name */
  VECTOR_SP_MAIN,                      /* 0x00 ivINT_Initial_Stack_Pointer */
  {
  VECTOR_1,                            /* 0x01 ivINT_Initial_Program_Counter */
  VECTOR_2,                            /* 0x02 ivINT_NMI */
  VECTOR_3,                            /* 0x03 ivINT_Hard_Fault */
  VECTOR_4,                            /* 0x04 ivINT_Mem_Manage_Fault */
  VECTOR_5,                            /* 0x05 ivINT_Bus_Fault */
  VECTOR_6,                            /* 0x06 ivINT_Usage_Fault */
  VECTOR_7,                            /* 0x07 ivINT_Reserved7 */
  VECTOR_8,                            /* 0x08 ivINT_Reserved8 */
  VECTOR_9,                            /* 0x09 ivINT_Reserved9 */
  VECTOR_10,                           /* 0x0A ivINT_Reserved10 */
  VECTOR_11,                           /* 0x0B ivINT_SVCall */
  VECTOR_12,                           /* 0x0C ivINT_DebugMonitor */
  VECTOR_13,                           /* 0x0D ivINT_Reserved13 */
  VECTOR_14,                           /* 0x0E ivINT_PendableSrvReq */
  VECTOR_15,                           /* 0x0F ivINT_SysTick */
  VECTOR_16,                           /* 0x10 ivINT_DMA0 */
  VECTOR_17,                           /* 0x11 ivINT_DMA1 */
  VECTOR_18,                           /* 0x12 ivINT_DMA2 */
  VECTOR_19,                           /* 0x13 ivINT_DMA3 */
  VECTOR_20,                           /* 0x14 ivINT_DMA4 */
  VECTOR_21,                           /* 0x15 ivINT_DMA5 */
  VECTOR_22,                           /* 0x16 ivINT_DMA6 */
  VECTOR_23,                           /* 0x17 ivINT_DMA7 */
  VECTOR_24,                           /* 0x18 ivINT_DMA8 */
  VECTOR_25,                           /* 0x19 ivINT_DMA9 */
  VECTOR_26,                           /* 0x1A ivINT_DMA10 */
  VECTOR_27,                           /* 0x1B ivINT_DMA11 */
  VECTOR_28,                           /* 0x1C ivINT_DMA12 */
  VECTOR_29,                           /* 0x1D ivINT_DMA13 */
  VECTOR_30,                           /* 0x1E ivINT_DMA14 */
  VECTOR_31,                           /* 0x1F ivINT_DMA15 */
  VECTOR_32,                           /* 0x20 ivINT_DMA_Error */
  VECTOR_33,                           /* 0x21 ivINT_MCM */
  VECTOR_34,                           /* 0x22 ivINT_FTFE */
  VECTOR_35,                           /* 0x23 ivINT_Read_Collision */
  VECTOR_36,                           /* 0x24 ivINT_LVD_LVW */
  VECTOR_37,                           /* 0x25 ivINT_LLWU */
  VECTOR_38,                           /* 0x26 ivINT_WDOG_EWM */
  VECTOR_39,                           /* 0x27 ivINT_RNG */
  VECTOR_40,                           /* 0x28 ivINT_I2C0 */
  VECTOR_41,                           /* 0x29 ivINT_I2C1 */
  VECTOR_42,                           /* 0x2A ivINT_SPI0 */
  VECTOR_43,                           /* 0x2B ivINT_SPI1 */
  VECTOR_44,                           /* 0x2C ivINT_I2S0_Tx */
  VECTOR_45,                           /* 0x2D ivINT_I2S0_Rx */
  VECTOR_46,                           /* 0x2E ivINT_UART0_LON */
  VECTOR_47,                           /* 0x2F ivINT_UART0_RX_TX */
  VECTOR_48,                           /* 0x30 ivINT_UART0_ERR */
  VECTOR_49,                           /* 0x31 ivINT_UART1_RX_TX */
  VECTOR_50,                           /* 0x32 ivINT_UART1_ERR */
  VECTOR_51,                           /* 0x33 ivINT_UART2_RX_TX */
  VECTOR_52,                           /* 0x34 ivINT_UART2_ERR */
  VECTOR_53,                           /* 0x35 ivINT_UART3_RX_TX */
  VECTOR_54,                           /* 0x36 ivINT_UART3_ERR */
  VECTOR_55,                           /* 0x37 ivINT_ADC0 */
  VECTOR_56,                           /* 0x38 ivINT_CMP0 */
  VECTOR_57,                           /* 0x39 ivINT_CMP1 */
  VECTOR_58,                           /* 0x3A ivINT_FTM0 */
  VECTOR_59,                           /* 0x3B ivINT_FTM1 */
  VECTOR_60,                           /* 0x3C ivINT_FTM2 */
  VECTOR_61,                           /* 0x3D ivINT_CMT */
  VECTOR_62,                           /* 0x3E ivINT_RTC */
  VECTOR_63,                           /* 0x3F ivINT_RTC_Seconds */
  VECTOR_64,                           /* 0x40 ivINT_PIT0 */
  VECTOR_65,                           /* 0x41 ivINT_PIT1 */
  VECTOR_66,                           /* 0x42 ivINT_PIT2 */
  VECTOR_67,                           /* 0x43 ivINT_PIT3 */
  VECTOR_68,                           /* 0x44 ivINT_PDB0 */
  VECTOR_69,                           /* 0x45 ivINT_USB0 */
  VECTOR_70,                           /* 0x46 ivINT_USBDCD */
  VECTOR_71,                           /* 0x47 ivINT_Reserved71 */
  VECTOR_72,                           /* 0x48 ivINT_DAC0 */
  VECTOR_73,                           /* 0x49 ivINT_MCG */
  VECTOR_74,                           /* 0x4A ivINT_LPTMR0 */
  VECTOR_75,                           /* 0x4B ivINT_PORTA */
  VECTOR_76,                           /* 0x4C ivINT_PORTB */
  VECTOR_77,                           /* 0x4D ivINT_PORTC */
  VECTOR_78,                           /* 0x4E ivINT_PORTD */
  VECTOR_79,                           /* 0x4F ivINT_PORTE */
  VECTOR_80,                           /* 0x50 ivINT_SWI */
  VECTOR_81,                           /* 0x51 ivINT_SPI2 */
  VECTOR_82,                           /* 0x52 ivINT_UART4_RX_TX */
  VECTOR_83,                           /* 0x53 ivINT_UART4_ERR */
  VECTOR_84,                           /* 0x54 ivINT_UART5_RX_TX */
  VECTOR_85,                           /* 0x55 ivINT_UART5_ERR */
  VECTOR_86,                           /* 0x56 ivINT_CMP2 */
  VECTOR_87,                           /* 0x57 ivINT_FTM3 */
  VECTOR_88,                           /* 0x58 ivINT_Reserved88 */
  VECTOR_89,                           /* 0x59 ivINT_ADC1 */
  VECTOR_90,                           /* 0x5A ivINT_I2C2 */
  VECTOR_91,                           /* 0x5B ivINT_CAN0_ORed_Message_buffer */
  VECTOR_92,                           /* 0x5C ivINT_CAN0_Bus_Off */
  VECTOR_93,                           /* 0x5D ivINT_CAN0_Error */
  VECTOR_94,                           /* 0x5E ivINT_CAN0_Tx_Warning */
  VECTOR_95,                           /* 0x5F ivINT_CAN0_Rx_Warning */
  VECTOR_96,                           /* 0x60 ivINT_CAN0_Wake_Up */
  VECTOR_97,                           /* 0x61 ivINT_SDHC */
  VECTOR_98,                           /* 0x62 ivINT_ENET_1588_Timer */
  VECTOR_99,                           /* 0x63 ivINT_ENET_Transmit */
  VECTOR_100,                          /* 0x64 ivINT_ENET_Receive */
  VECTOR_101                           /* 0x65 ivINT_ENET_Error */
  }
};
#if defined(__IAR_SYSTEMS_ICC__)  
/*lint -restore Enable MISRA rule (11.4,2.1,1.1) checking. */
#else
/*lint -restore Enable MISRA rule (11.4) checking. */
#endif

#endif /* PEX_VECTOR_TABLE */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file is a part of Processor Expert static initialization
**     library for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
