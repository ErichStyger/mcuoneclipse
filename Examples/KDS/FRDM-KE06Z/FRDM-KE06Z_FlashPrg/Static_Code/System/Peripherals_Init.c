/** ###################################################################
**      Filename    : Peripherals_Init.c
**      Processor   : MKE06Z128VLK4
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

#ifdef ACMP0_AUTOINIT
  ACMP0_Init();
#endif /* ACMP0_AUTOINIT */
#ifdef ACMP1_AUTOINIT
  ACMP1_Init();
#endif /* ACMP1_AUTOINIT */
#ifdef ADC_AUTOINIT
  ADC_Init();
#endif /* ADC_AUTOINIT */
#ifdef CRC_AUTOINIT
  CRC_Init();
#endif /* CRC_AUTOINIT */
#ifdef DAC6b0_AUTOINIT
  DAC6b0_Init();
#endif /* DAC6b0_AUTOINIT */
#ifdef DAC6b1_AUTOINIT
  DAC6b1_Init();
#endif /* DAC6b1_AUTOINIT */
#ifdef FTM0_AUTOINIT
  FTM0_Init();
#endif /* FTM0_AUTOINIT */
#ifdef FTM1_AUTOINIT
  FTM1_Init();
#endif /* FTM1_AUTOINIT */
#ifdef FTM2_AUTOINIT
  FTM2_Init();
#endif /* FTM2_AUTOINIT */
#ifdef FTMRE_AUTOINIT
  FTMRE_Init();
#endif /* FTMRE_AUTOINIT */
#ifdef GPIOA_AUTOINIT
  GPIOA_Init();
#endif /* GPIOA_AUTOINIT */
#ifdef GPIOB_AUTOINIT
  GPIOB_Init();
#endif /* GPIOB_AUTOINIT */
#ifdef GPIOC_AUTOINIT
  GPIOC_Init();
#endif /* GPIOC_AUTOINIT */
#ifdef I2C0_AUTOINIT
  I2C0_Init();
#endif /* I2C0_AUTOINIT */
#ifdef I2C1_AUTOINIT
  I2C1_Init();
#endif /* I2C1_AUTOINIT */
#ifdef IRQ_AUTOINIT
  IRQ_Init();
#endif /* IRQ_AUTOINIT */
#ifdef KBI0_AUTOINIT
  KBI0_Init();
#endif /* KBI0_AUTOINIT */
#ifdef KBI1_AUTOINIT
  KBI1_Init();
#endif /* KBI1_AUTOINIT */
#ifdef MSCAN_AUTOINIT
  MSCAN_Init();
#endif /* MSCAN_AUTOINIT */
#ifdef PIT_AUTOINIT
  PIT_Init();
#endif /* PIT_AUTOINIT */
#ifdef PORT_AUTOINIT
  PORT_Init();
#endif /* PORT_AUTOINIT */
#ifdef PWT_AUTOINIT
  PWT_Init();
#endif /* PWT_AUTOINIT */
#ifdef RTC_AUTOINIT
  RTC_Init();
#endif /* RTC_AUTOINIT */
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