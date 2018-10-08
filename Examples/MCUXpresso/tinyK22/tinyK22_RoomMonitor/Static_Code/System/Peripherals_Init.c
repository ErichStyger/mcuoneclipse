/** ###################################################################
**      Filename    : Peripherals_Init.c
**      Processor   : MK22FN512VLH12
**      Version     : 1.0
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
** @file Peripherals_Init.c                                                  
** @version 01.00
*/         
/*!
**  @addtogroup Peripherals_Init_module Peripherals_Init module documentation
**  @{
*/         

/* MODULE Peripherals_Init.c */

#include "Peripherals_Init.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void Peripherals_Init(void)
{
#ifdef NVIC_AUTOINIT
  NVIC_Init();
#endif /* NVIC_AUTOINIT */
#ifdef SIM_AUTOINIT
  SIM_Init();
#endif /* SIM_AUTOINIT */

#ifdef MCM_AUTOINIT
  MCM_Init();
#endif /* MCM_AUTOINIT */
#ifdef PMC_AUTOINIT
  PMC_Init();
#endif /* PMC_AUTOINIT */
#ifdef PORTA_AUTOINIT
  PORTA_Init();
#endif /* PORTA_AUTOINIT */
#ifdef PORTB_AUTOINIT
  PORTB_Init();
#endif /* PORTB_AUTOINIT */
#ifdef PORTC_AUTOINIT
  PORTC_Init();
#endif /* PORTC_AUTOINIT */
#ifdef PORTD_AUTOINIT
  PORTD_Init();
#endif /* PORTD_AUTOINIT */
#ifdef PORTE_AUTOINIT
  PORTE_Init();
#endif /* PORTE_AUTOINIT */

#ifdef ADC0_AUTOINIT
  ADC0_Init();
#endif /* ADC0_AUTOINIT */
#ifdef ADC1_AUTOINIT
  ADC1_Init();
#endif /* ADC1_AUTOINIT */
#ifdef AIPS0_AUTOINIT
  AIPS0_Init();
#endif /* AIPS0_AUTOINIT */
#ifdef CMP0_AUTOINIT
  CMP0_Init();
#endif /* CMP0_AUTOINIT */
#ifdef CMP1_AUTOINIT
  CMP1_Init();
#endif /* CMP1_AUTOINIT */
#ifdef CRC_AUTOINIT
  CRC_Init();
#endif /* CRC_AUTOINIT */
#ifdef DAC0_AUTOINIT
  DAC0_Init();
#endif /* DAC0_AUTOINIT */
#ifdef DAC1_AUTOINIT
  DAC1_Init();
#endif /* DAC1_AUTOINIT */
#ifdef DMAMUX_AUTOINIT
  DMAMUX_Init();
#endif /* DMAMUX_AUTOINIT */
#ifdef DMA_AUTOINIT
  DMA_Init();
#endif /* DMA_AUTOINIT */
#ifdef EWM_AUTOINIT
  EWM_Init();
#endif /* EWM_AUTOINIT */
#ifdef FB_AUTOINIT
  FB_Init();
#endif /* FB_AUTOINIT */
#ifdef FMC_AUTOINIT
  FMC_Init();
#endif /* FMC_AUTOINIT */
#ifdef FTFA_AUTOINIT
  FTFA_Init();
#endif /* FTFA_AUTOINIT */
#ifdef FTM0_AUTOINIT
  FTM0_Init();
#endif /* FTM0_AUTOINIT */
#ifdef FTM1_AUTOINIT
  FTM1_Init();
#endif /* FTM1_AUTOINIT */
#ifdef FTM2_AUTOINIT
  FTM2_Init();
#endif /* FTM2_AUTOINIT */
#ifdef FTM3_AUTOINIT
  FTM3_Init();
#endif /* FTM3_AUTOINIT */
#ifdef I2C0_AUTOINIT
  I2C0_Init();
#endif /* I2C0_AUTOINIT */
#ifdef I2C1_AUTOINIT
  I2C1_Init();
#endif /* I2C1_AUTOINIT */
#ifdef I2S0_AUTOINIT
  I2S0_Init();
#endif /* I2S0_AUTOINIT */
#ifdef LLWU_AUTOINIT
  LLWU_Init();
#endif /* LLWU_AUTOINIT */
#ifdef LPTMR0_AUTOINIT
  LPTMR0_Init();
#endif /* LPTMR0_AUTOINIT */
#ifdef LPUART0_AUTOINIT
  LPUART0_Init();
#endif /* LPUART0_AUTOINIT */
#ifdef PDB0_AUTOINIT
  PDB0_Init();
#endif /* PDB0_AUTOINIT */
#ifdef PIT_AUTOINIT
  PIT_Init();
#endif /* PIT_AUTOINIT */
#ifdef PTA_AUTOINIT
  PTA_Init();
#endif /* PTA_AUTOINIT */
#ifdef PTB_AUTOINIT
  PTB_Init();
#endif /* PTB_AUTOINIT */
#ifdef PTC_AUTOINIT
  PTC_Init();
#endif /* PTC_AUTOINIT */
#ifdef PTD_AUTOINIT
  PTD_Init();
#endif /* PTD_AUTOINIT */
#ifdef PTE_AUTOINIT
  PTE_Init();
#endif /* PTE_AUTOINIT */
#ifdef RCM_AUTOINIT
  RCM_Init();
#endif /* RCM_AUTOINIT */
#ifdef RNG_AUTOINIT
  RNG_Init();
#endif /* RNG_AUTOINIT */
#ifdef RTC_AUTOINIT
  RTC_Init();
#endif /* RTC_AUTOINIT */
#ifdef SMC_AUTOINIT
  SMC_Init();
#endif /* SMC_AUTOINIT */
#ifdef SPI0_AUTOINIT
  SPI0_Init();
#endif /* SPI0_AUTOINIT */
#ifdef SPI1_AUTOINIT
  SPI1_Init();
#endif /* SPI1_AUTOINIT */
#ifdef SystemControl_AUTOINIT
  SystemControl_Init();
#endif /* SystemControl_AUTOINIT */
#ifdef SysTick_AUTOINIT
  SysTick_Init();
#endif /* SysTick_AUTOINIT */
#ifdef UART0_AUTOINIT
  UART0_Init();
#endif /* UART0_AUTOINIT */
#ifdef UART1_AUTOINIT
  UART1_Init();
#endif /* UART1_AUTOINIT */
#ifdef UART2_AUTOINIT
  UART2_Init();
#endif /* UART2_AUTOINIT */
#ifdef USB0_AUTOINIT
  USB0_Init();
#endif /* USB0_AUTOINIT */
#ifdef VREF_AUTOINIT
  VREF_Init();
#endif /* VREF_AUTOINIT */
#ifdef WDOG_AUTOINIT
  WDOG_Init();
#endif /* WDOG_AUTOINIT */
}

#ifdef __cplusplus
}
#endif

/* END Peripherals_Init.h */

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
