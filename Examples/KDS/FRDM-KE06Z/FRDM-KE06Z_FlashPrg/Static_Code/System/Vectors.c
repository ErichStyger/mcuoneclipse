/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MKE06Z128VLK4
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
**     Method      :  UnhandledInterrupt (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_NMI (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Hard_Fault (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved4 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved4 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved4);
PE_ISR(Unhandled_ivINT_Reserved4)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved5 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved5 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved5);
PE_ISR(Unhandled_ivINT_Reserved5)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved6 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved6 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved6);
PE_ISR(Unhandled_ivINT_Reserved6)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved7 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved8 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved9 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved10 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_SVCall (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved12 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved12 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved12);
PE_ISR(Unhandled_ivINT_Reserved12)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved13 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_PendableSrvReq (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_SysTick (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_Reserved16 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved16 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved16);
PE_ISR(Unhandled_ivINT_Reserved16)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved17 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved17 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved17);
PE_ISR(Unhandled_ivINT_Reserved17)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved18 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved18 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved18);
PE_ISR(Unhandled_ivINT_Reserved18)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved19 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved19 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved19);
PE_ISR(Unhandled_ivINT_Reserved19)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved20 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved20 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved20);
PE_ISR(Unhandled_ivINT_Reserved20)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTMRE (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_FTMRE interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_FTMRE);
PE_ISR(Unhandled_ivINT_FTMRE)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_LVD_LLW (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_LVD_LLW interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_LVD_LLW);
PE_ISR(Unhandled_ivINT_LVD_LLW)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_IRQ (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_IRQ interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_IRQ);
PE_ISR(Unhandled_ivINT_IRQ)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_I2C0 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_I2C1 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_SPI0 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_SPI1 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_UART0 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_UART0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART0);
PE_ISR(Unhandled_ivINT_UART0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART1 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_UART1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART1);
PE_ISR(Unhandled_ivINT_UART1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_UART2 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_UART2 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_UART2);
PE_ISR(Unhandled_ivINT_UART2)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ADC0 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_ACMP0 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_ACMP0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ACMP0);
PE_ISR(Unhandled_ivINT_ACMP0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_FTM0 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_FTM1 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_FTM2 (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_RTC (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_ACMP1 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_ACMP1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ACMP1);
PE_ISR(Unhandled_ivINT_ACMP1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT_CH0 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT_CH0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT_CH0);
PE_ISR(Unhandled_ivINT_PIT_CH0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_PIT_CH1 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_PIT_CH1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PIT_CH1);
PE_ISR(Unhandled_ivINT_PIT_CH1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_KBI0 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_KBI0 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_KBI0);
PE_ISR(Unhandled_ivINT_KBI0)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_KBI1 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_KBI1 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_KBI1);
PE_ISR(Unhandled_ivINT_KBI1)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_Reserved42 (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_Reserved42 interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_Reserved42);
PE_ISR(Unhandled_ivINT_Reserved42)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_ICS (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_ICS interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_ICS);
PE_ISR(Unhandled_ivINT_ICS)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_WDOG_EWM (component MKE06Z128LK4)
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
**     Method      :  Unhandled_ivINT_PWT (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_PWT interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_PWT);
PE_ISR(Unhandled_ivINT_PWT)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_MSCAN_RX (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_MSCAN_RX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_MSCAN_RX);
PE_ISR(Unhandled_ivINT_MSCAN_RX)
{
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Unhandled_ivINT_MSCAN_TX (component MKE06Z128LK4)
**
**     Description :
**         This ISR services the unhandled ivINT_MSCAN_TX interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Unhandled_ivINT_MSCAN_TX);
PE_ISR(Unhandled_ivINT_MSCAN_TX)
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
  VECTOR_4,                            /* 0x04 ivINT_Reserved4 */
  VECTOR_5,                            /* 0x05 ivINT_Reserved5 */
  VECTOR_6,                            /* 0x06 ivINT_Reserved6 */
  VECTOR_7,                            /* 0x07 ivINT_Reserved7 */
  VECTOR_8,                            /* 0x08 ivINT_Reserved8 */
  VECTOR_9,                            /* 0x09 ivINT_Reserved9 */
  VECTOR_10,                           /* 0x0A ivINT_Reserved10 */
  VECTOR_11,                           /* 0x0B ivINT_SVCall */
  VECTOR_12,                           /* 0x0C ivINT_Reserved12 */
  VECTOR_13,                           /* 0x0D ivINT_Reserved13 */
  VECTOR_14,                           /* 0x0E ivINT_PendableSrvReq */
  VECTOR_15,                           /* 0x0F ivINT_SysTick */
  VECTOR_16,                           /* 0x10 ivINT_Reserved16 */
  VECTOR_17,                           /* 0x11 ivINT_Reserved17 */
  VECTOR_18,                           /* 0x12 ivINT_Reserved18 */
  VECTOR_19,                           /* 0x13 ivINT_Reserved19 */
  VECTOR_20,                           /* 0x14 ivINT_Reserved20 */
  VECTOR_21,                           /* 0x15 ivINT_FTMRE */
  VECTOR_22,                           /* 0x16 ivINT_LVD_LLW */
  VECTOR_23,                           /* 0x17 ivINT_IRQ */
  VECTOR_24,                           /* 0x18 ivINT_I2C0 */
  VECTOR_25,                           /* 0x19 ivINT_I2C1 */
  VECTOR_26,                           /* 0x1A ivINT_SPI0 */
  VECTOR_27,                           /* 0x1B ivINT_SPI1 */
  VECTOR_28,                           /* 0x1C ivINT_UART0 */
  VECTOR_29,                           /* 0x1D ivINT_UART1 */
  VECTOR_30,                           /* 0x1E ivINT_UART2 */
  VECTOR_31,                           /* 0x1F ivINT_ADC0 */
  VECTOR_32,                           /* 0x20 ivINT_ACMP0 */
  VECTOR_33,                           /* 0x21 ivINT_FTM0 */
  VECTOR_34,                           /* 0x22 ivINT_FTM1 */
  VECTOR_35,                           /* 0x23 ivINT_FTM2 */
  VECTOR_36,                           /* 0x24 ivINT_RTC */
  VECTOR_37,                           /* 0x25 ivINT_ACMP1 */
  VECTOR_38,                           /* 0x26 ivINT_PIT_CH0 */
  VECTOR_39,                           /* 0x27 ivINT_PIT_CH1 */
  VECTOR_40,                           /* 0x28 ivINT_KBI0 */
  VECTOR_41,                           /* 0x29 ivINT_KBI1 */
  VECTOR_42,                           /* 0x2A ivINT_Reserved42 */
  VECTOR_43,                           /* 0x2B ivINT_ICS */
  VECTOR_44,                           /* 0x2C ivINT_WDOG_EWM */
  VECTOR_45,                           /* 0x2D ivINT_PWT */
  VECTOR_46,                           /* 0x2E ivINT_MSCAN_RX */
  VECTOR_47                            /* 0x2F ivINT_MSCAN_TX */
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