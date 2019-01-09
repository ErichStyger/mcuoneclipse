/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MK22FN512VDC12
**      Version     : 1.00
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
*/         
/*!
**  @addtogroup Vectors_Config_module Vectors_Config module documentation
**  @{
*/         

#ifndef __Vectors_Config_H
#define __Vectors_Config_H

/* MODULE Vectors_Config.h */
  
#include "Cpu.h"
#include "Pins1.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PEX_VECTOR_TABLE                                   0x01U     /* Vector table is managed by PEx */ 

/* Vector                 Address                                  No.  Pri  Name                          Description */
#define VECTOR_SP_MAIN    &__SP_INIT                            /* 0x00 -    ivINT_Initial_Stack_Pointer   used by PE */
#define VECTOR_1          (tIsrFunc)&__thumb_startup            /* 0x01 -    ivINT_Initial_Program_Counter used by PE */
#define VECTOR_2          (tIsrFunc)&Cpu_INT_NMIInterrupt       /* 0x02 -2   ivINT_NMI                     used by PE */
#define VECTOR_3          (tIsrFunc)&UnhandledInterrupt         /* 0x03 -1   ivINT_Hard_Fault              unused by PE */
#define VECTOR_4          (tIsrFunc)&UnhandledInterrupt         /* 0x04 -    ivINT_Mem_Manage_Fault        unused by PE */
#define VECTOR_5          (tIsrFunc)&UnhandledInterrupt         /* 0x05 -    ivINT_Bus_Fault               unused by PE */
#define VECTOR_6          (tIsrFunc)&UnhandledInterrupt         /* 0x06 -    ivINT_Usage_Fault             unused by PE */
#define VECTOR_7          (tIsrFunc)&UnhandledInterrupt         /* 0x07 -    ivINT_Reserved7               unused by PE */
#define VECTOR_8          (tIsrFunc)&UnhandledInterrupt         /* 0x08 -    ivINT_Reserved8               unused by PE */
#define VECTOR_9          (tIsrFunc)&UnhandledInterrupt         /* 0x09 -    ivINT_Reserved9               unused by PE */
#define VECTOR_10         (tIsrFunc)&UnhandledInterrupt         /* 0x0A -    ivINT_Reserved10              unused by PE */
#define VECTOR_11         (tIsrFunc)&UnhandledInterrupt         /* 0x0B -    ivINT_SVCall                  unused by PE */
#define VECTOR_12         (tIsrFunc)&UnhandledInterrupt         /* 0x0C -    ivINT_DebugMonitor            unused by PE */
#define VECTOR_13         (tIsrFunc)&UnhandledInterrupt         /* 0x0D -    ivINT_Reserved13              unused by PE */
#define VECTOR_14         (tIsrFunc)&UnhandledInterrupt         /* 0x0E -    ivINT_PendableSrvReq          unused by PE */
#define VECTOR_15         (tIsrFunc)&UnhandledInterrupt         /* 0x0F -    ivINT_SysTick                 unused by PE */
#define VECTOR_16         (tIsrFunc)&UnhandledInterrupt         /* 0x10 -    ivINT_DMA0                    unused by PE */
#define VECTOR_17         (tIsrFunc)&UnhandledInterrupt         /* 0x11 -    ivINT_DMA1                    unused by PE */
#define VECTOR_18         (tIsrFunc)&UnhandledInterrupt         /* 0x12 -    ivINT_DMA2                    unused by PE */
#define VECTOR_19         (tIsrFunc)&UnhandledInterrupt         /* 0x13 -    ivINT_DMA3                    unused by PE */
#define VECTOR_20         (tIsrFunc)&UnhandledInterrupt         /* 0x14 -    ivINT_DMA4                    unused by PE */
#define VECTOR_21         (tIsrFunc)&UnhandledInterrupt         /* 0x15 -    ivINT_DMA5                    unused by PE */
#define VECTOR_22         (tIsrFunc)&UnhandledInterrupt         /* 0x16 -    ivINT_DMA6                    unused by PE */
#define VECTOR_23         (tIsrFunc)&UnhandledInterrupt         /* 0x17 -    ivINT_DMA7                    unused by PE */
#define VECTOR_24         (tIsrFunc)&UnhandledInterrupt         /* 0x18 -    ivINT_DMA8                    unused by PE */
#define VECTOR_25         (tIsrFunc)&UnhandledInterrupt         /* 0x19 -    ivINT_DMA9                    unused by PE */
#define VECTOR_26         (tIsrFunc)&UnhandledInterrupt         /* 0x1A -    ivINT_DMA10                   unused by PE */
#define VECTOR_27         (tIsrFunc)&UnhandledInterrupt         /* 0x1B -    ivINT_DMA11                   unused by PE */
#define VECTOR_28         (tIsrFunc)&UnhandledInterrupt         /* 0x1C -    ivINT_DMA12                   unused by PE */
#define VECTOR_29         (tIsrFunc)&UnhandledInterrupt         /* 0x1D -    ivINT_DMA13                   unused by PE */
#define VECTOR_30         (tIsrFunc)&UnhandledInterrupt         /* 0x1E -    ivINT_DMA14                   unused by PE */
#define VECTOR_31         (tIsrFunc)&UnhandledInterrupt         /* 0x1F -    ivINT_DMA15                   unused by PE */
#define VECTOR_32         (tIsrFunc)&UnhandledInterrupt         /* 0x20 -    ivINT_DMA_Error               unused by PE */
#define VECTOR_33         (tIsrFunc)&UnhandledInterrupt         /* 0x21 -    ivINT_MCM                     unused by PE */
#define VECTOR_34         (tIsrFunc)&UnhandledInterrupt         /* 0x22 -    ivINT_FTF                     unused by PE */
#define VECTOR_35         (tIsrFunc)&UnhandledInterrupt         /* 0x23 -    ivINT_Read_Collision          unused by PE */
#define VECTOR_36         (tIsrFunc)&UnhandledInterrupt         /* 0x24 -    ivINT_LVD_LVW                 unused by PE */
#define VECTOR_37         (tIsrFunc)&UnhandledInterrupt         /* 0x25 -    ivINT_LLWU                    unused by PE */
#define VECTOR_38         (tIsrFunc)&UnhandledInterrupt         /* 0x26 -    ivINT_WDOG_EWM                unused by PE */
#define VECTOR_39         (tIsrFunc)&UnhandledInterrupt         /* 0x27 -    ivINT_RNG                     unused by PE */
#define VECTOR_40         (tIsrFunc)&UnhandledInterrupt         /* 0x28 -    ivINT_I2C0                    unused by PE */
#define VECTOR_41         (tIsrFunc)&UnhandledInterrupt         /* 0x29 -    ivINT_I2C1                    unused by PE */
#define VECTOR_42         (tIsrFunc)&UnhandledInterrupt         /* 0x2A -    ivINT_SPI0                    unused by PE */
#define VECTOR_43         (tIsrFunc)&UnhandledInterrupt         /* 0x2B -    ivINT_SPI1                    unused by PE */
#define VECTOR_44         (tIsrFunc)&UnhandledInterrupt         /* 0x2C -    ivINT_I2S0_Tx                 unused by PE */
#define VECTOR_45         (tIsrFunc)&UnhandledInterrupt         /* 0x2D -    ivINT_I2S0_Rx                 unused by PE */
#define VECTOR_46         (tIsrFunc)&UnhandledInterrupt         /* 0x2E -    ivINT_LPUART0                 unused by PE */
#define VECTOR_47         (tIsrFunc)&UnhandledInterrupt         /* 0x2F -    ivINT_UART0_RX_TX             unused by PE */
#define VECTOR_48         (tIsrFunc)&UnhandledInterrupt         /* 0x30 -    ivINT_UART0_ERR               unused by PE */
#define VECTOR_49         (tIsrFunc)&UnhandledInterrupt         /* 0x31 -    ivINT_UART1_RX_TX             unused by PE */
#define VECTOR_50         (tIsrFunc)&UnhandledInterrupt         /* 0x32 -    ivINT_UART1_ERR               unused by PE */
#define VECTOR_51         (tIsrFunc)&UnhandledInterrupt         /* 0x33 -    ivINT_UART2_RX_TX             unused by PE */
#define VECTOR_52         (tIsrFunc)&UnhandledInterrupt         /* 0x34 -    ivINT_UART2_ERR               unused by PE */
#define VECTOR_53         (tIsrFunc)&UnhandledInterrupt         /* 0x35 -    ivINT_Reserved53              unused by PE */
#define VECTOR_54         (tIsrFunc)&UnhandledInterrupt         /* 0x36 -    ivINT_Reserved54              unused by PE */
#define VECTOR_55         (tIsrFunc)&UnhandledInterrupt         /* 0x37 -    ivINT_ADC0                    unused by PE */
#define VECTOR_56         (tIsrFunc)&UnhandledInterrupt         /* 0x38 -    ivINT_CMP0                    unused by PE */
#define VECTOR_57         (tIsrFunc)&UnhandledInterrupt         /* 0x39 -    ivINT_CMP1                    unused by PE */
#define VECTOR_58         (tIsrFunc)&UnhandledInterrupt         /* 0x3A -    ivINT_FTM0                    unused by PE */
#define VECTOR_59         (tIsrFunc)&UnhandledInterrupt         /* 0x3B -    ivINT_FTM1                    unused by PE */
#define VECTOR_60         (tIsrFunc)&UnhandledInterrupt         /* 0x3C -    ivINT_FTM2                    unused by PE */
#define VECTOR_61         (tIsrFunc)&UnhandledInterrupt         /* 0x3D -    ivINT_Reserved61              unused by PE */
#define VECTOR_62         (tIsrFunc)&UnhandledInterrupt         /* 0x3E -    ivINT_RTC                     unused by PE */
#define VECTOR_63         (tIsrFunc)&UnhandledInterrupt         /* 0x3F -    ivINT_RTC_Seconds             unused by PE */
#define VECTOR_64         (tIsrFunc)&UnhandledInterrupt         /* 0x40 -    ivINT_PIT0                    unused by PE */
#define VECTOR_65         (tIsrFunc)&UnhandledInterrupt         /* 0x41 -    ivINT_PIT1                    unused by PE */
#define VECTOR_66         (tIsrFunc)&UnhandledInterrupt         /* 0x42 -    ivINT_PIT2                    unused by PE */
#define VECTOR_67         (tIsrFunc)&UnhandledInterrupt         /* 0x43 -    ivINT_PIT3                    unused by PE */
#define VECTOR_68         (tIsrFunc)&UnhandledInterrupt         /* 0x44 -    ivINT_PDB0                    unused by PE */
#define VECTOR_69         (tIsrFunc)&UnhandledInterrupt         /* 0x45 -    ivINT_USB0                    unused by PE */
#define VECTOR_70         (tIsrFunc)&UnhandledInterrupt         /* 0x46 -    ivINT_Reserved70              unused by PE */
#define VECTOR_71         (tIsrFunc)&UnhandledInterrupt         /* 0x47 -    ivINT_Reserved71              unused by PE */
#define VECTOR_72         (tIsrFunc)&UnhandledInterrupt         /* 0x48 -    ivINT_DAC0                    unused by PE */
#define VECTOR_73         (tIsrFunc)&UnhandledInterrupt         /* 0x49 -    ivINT_MCG                     unused by PE */
#define VECTOR_74         (tIsrFunc)&UnhandledInterrupt         /* 0x4A -    ivINT_LPTMR0                  unused by PE */
#define VECTOR_75         (tIsrFunc)&UnhandledInterrupt         /* 0x4B -    ivINT_PORTA                   unused by PE */
#define VECTOR_76         (tIsrFunc)&UnhandledInterrupt         /* 0x4C -    ivINT_PORTB                   unused by PE */
#define VECTOR_77         (tIsrFunc)&UnhandledInterrupt         /* 0x4D -    ivINT_PORTC                   unused by PE */
#define VECTOR_78         (tIsrFunc)&UnhandledInterrupt         /* 0x4E -    ivINT_PORTD                   unused by PE */
#define VECTOR_79         (tIsrFunc)&UnhandledInterrupt         /* 0x4F -    ivINT_PORTE                   unused by PE */
#define VECTOR_80         (tIsrFunc)&UnhandledInterrupt         /* 0x50 -    ivINT_SWI                     unused by PE */
#define VECTOR_81         (tIsrFunc)&UnhandledInterrupt         /* 0x51 -    ivINT_Reserved81              unused by PE */
#define VECTOR_82         (tIsrFunc)&UnhandledInterrupt         /* 0x52 -    ivINT_Reserved82              unused by PE */
#define VECTOR_83         (tIsrFunc)&UnhandledInterrupt         /* 0x53 -    ivINT_Reserved83              unused by PE */
#define VECTOR_84         (tIsrFunc)&UnhandledInterrupt         /* 0x54 -    ivINT_Reserved84              unused by PE */
#define VECTOR_85         (tIsrFunc)&UnhandledInterrupt         /* 0x55 -    ivINT_Reserved85              unused by PE */
#define VECTOR_86         (tIsrFunc)&UnhandledInterrupt         /* 0x56 -    ivINT_Reserved86              unused by PE */
#define VECTOR_87         (tIsrFunc)&UnhandledInterrupt         /* 0x57 -    ivINT_FTM3                    unused by PE */
#define VECTOR_88         (tIsrFunc)&UnhandledInterrupt         /* 0x58 -    ivINT_DAC1                    unused by PE */
#define VECTOR_89         (tIsrFunc)&UnhandledInterrupt         /* 0x59 -    ivINT_ADC1                    unused by PE */
#define VECTOR_90         (tIsrFunc)&UnhandledInterrupt         /* 0x5A -    ivINT_Reserved90              unused by PE */
#define VECTOR_91         (tIsrFunc)&UnhandledInterrupt         /* 0x5B -    ivINT_Reserved91              unused by PE */
#define VECTOR_92         (tIsrFunc)&UnhandledInterrupt         /* 0x5C -    ivINT_Reserved92              unused by PE */
#define VECTOR_93         (tIsrFunc)&UnhandledInterrupt         /* 0x5D -    ivINT_Reserved93              unused by PE */
#define VECTOR_94         (tIsrFunc)&UnhandledInterrupt         /* 0x5E -    ivINT_Reserved94              unused by PE */
#define VECTOR_95         (tIsrFunc)&UnhandledInterrupt         /* 0x5F -    ivINT_Reserved95              unused by PE */
#define VECTOR_96         (tIsrFunc)&UnhandledInterrupt         /* 0x60 -    ivINT_Reserved96              unused by PE */
#define VECTOR_97         (tIsrFunc)&UnhandledInterrupt         /* 0x61 -    ivINT_Reserved97              unused by PE */
#define VECTOR_98         (tIsrFunc)&UnhandledInterrupt         /* 0x62 -    ivINT_Reserved98              unused by PE */
#define VECTOR_99         (tIsrFunc)&UnhandledInterrupt         /* 0x63 -    ivINT_Reserved99              unused by PE */
#define VECTOR_100        (tIsrFunc)&UnhandledInterrupt         /* 0x64 -    ivINT_Reserved100             unused by PE */
#define VECTOR_101        (tIsrFunc)&UnhandledInterrupt         /* 0x65 -    ivINT_Reserved101             unused by PE */
  
#ifdef __cplusplus
}
#endif

/* END Vectors_Config.h */

#endif /* __Vectors_Config_H */

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
