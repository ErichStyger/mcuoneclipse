/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MK64FN1M0VLL12
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "HF1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "CLS1.h"
#include "BT1.h"
#include "Serial1.h"
#include "ASerialLdd1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "FX1.h"
#include "GI2C1.h"
#include "I2C.h"
#include "FAT1.h"
#include "MINI1.h"
#include "TmDt1.h"
#include "FATM1.h"
#include "SS1.h"
#include "CD2.h"
#include "SM2.h"
#include "TMOUT1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd8.h"
#include "Inhr2.h"
#include "BitIoLdd9.h"
#include "TRG1.h"
#include "KIN1.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "WAIT1.h"
#include "SYS1.h"
#include "Step0.h"
#include "BitIoLdd17.h"
#include "Dir0.h"
#include "BitIoLdd16.h"
#include "Step1.h"
#include "BitIoLdd19.h"
#include "Dir1.h"
#include "BitIoLdd20.h"
#include "Step2.h"
#include "BitIoLdd22.h"
#include "Dir2.h"
#include "BitIoLdd23.h"
#include "Step3.h"
#include "BitIoLdd24.h"
#include "Dir3.h"
#include "BitIoLdd21.h"
#include "Step4.h"
#include "BitIoLdd26.h"
#include "Dir4.h"
#include "BitIoLdd25.h"
#include "Step5.h"
#include "BitIoLdd18.h"
#include "Dir5.h"
#include "BitIoLdd15.h"
#include "Step6.h"
#include "BitIoLdd28.h"
#include "Dir6.h"
#include "BitIoLdd27.h"
#include "Step7.h"
#include "BitIoLdd30.h"
#include "Dir7.h"
#include "BitIoLdd29.h"
#include "PTRC1.h"
#include "RTT1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PEX_VECTOR_TABLE                                   0x01U     /* Vector table is managed by PEx */ 

#if 1
extern void _vStackTop(void);
extern void ResetISR(void);
#endif

/* Vector                 Address                                  No.  Pri  Name                           Description */
#if 0
#define VECTOR_SP_MAIN    &__SP_INIT                            /* 0x00 -    ivINT_Initial_Stack_Pointer    used by PE */
#define VECTOR_1          (tIsrFunc)&__thumb_startup            /* 0x01 -    ivINT_Initial_Program_Counter  used by PE */
#else
#define VECTOR_SP_MAIN    &_vStackTop                            /* 0x00 -    ivINT_Initial_Stack_Pointer    used by PE */
#define VECTOR_1          (tIsrFunc)&ResetISR            /* 0x01 -    ivINT_Initial_Program_Counter  used by PE */
#endif
#define VECTOR_2          (tIsrFunc)&Cpu_INT_NMIInterrupt       /* 0x02 -2   ivINT_NMI                      used by PE */
#define VECTOR_3          (tIsrFunc)&HF1_HardFaultHandler       /* 0x03 -1   ivINT_Hard_Fault               used by PE */
#define VECTOR_4          (tIsrFunc)&Unhandled_ivINT_Mem_Manage_Fault /* 0x04 - ivINT_Mem_Manage_Fault      unused by PE */
#define VECTOR_5          (tIsrFunc)&Unhandled_ivINT_Bus_Fault  /* 0x05 -    ivINT_Bus_Fault                unused by PE */
#define VECTOR_6          (tIsrFunc)&Unhandled_ivINT_Usage_Fault /* 0x06 -   ivINT_Usage_Fault              unused by PE */
#define VECTOR_7          (tIsrFunc)&Unhandled_ivINT_Reserved7  /* 0x07 -    ivINT_Reserved7                unused by PE */
#define VECTOR_8          (tIsrFunc)&Unhandled_ivINT_Reserved8  /* 0x08 -    ivINT_Reserved8                unused by PE */
#define VECTOR_9          (tIsrFunc)&Unhandled_ivINT_Reserved9  /* 0x09 -    ivINT_Reserved9                unused by PE */
#define VECTOR_10         (tIsrFunc)&Unhandled_ivINT_Reserved10 /* 0x0A -    ivINT_Reserved10               unused by PE */
#define VECTOR_11         (tIsrFunc)&vPortSVCHandler            /* 0x0B -    ivINT_SVCall                   used by PE */
#define VECTOR_12         (tIsrFunc)&Unhandled_ivINT_DebugMonitor /* 0x0C -  ivINT_DebugMonitor             unused by PE */
#define VECTOR_13         (tIsrFunc)&Unhandled_ivINT_Reserved13 /* 0x0D -    ivINT_Reserved13               unused by PE */
#define VECTOR_14         (tIsrFunc)&vPortPendSVHandler         /* 0x0E -    ivINT_PendableSrvReq           used by PE */
#define VECTOR_15         (tIsrFunc)&vPortTickHandler           /* 0x0F -    ivINT_SysTick                  used by PE */
#define VECTOR_16         (tIsrFunc)&Unhandled_ivINT_DMA0       /* 0x10 -    ivINT_DMA0                     unused by PE */
#define VECTOR_17         (tIsrFunc)&Unhandled_ivINT_DMA1       /* 0x11 -    ivINT_DMA1                     unused by PE */
#define VECTOR_18         (tIsrFunc)&Unhandled_ivINT_DMA2       /* 0x12 -    ivINT_DMA2                     unused by PE */
#define VECTOR_19         (tIsrFunc)&Unhandled_ivINT_DMA3       /* 0x13 -    ivINT_DMA3                     unused by PE */
#define VECTOR_20         (tIsrFunc)&Unhandled_ivINT_DMA4       /* 0x14 -    ivINT_DMA4                     unused by PE */
#define VECTOR_21         (tIsrFunc)&Unhandled_ivINT_DMA5       /* 0x15 -    ivINT_DMA5                     unused by PE */
#define VECTOR_22         (tIsrFunc)&Unhandled_ivINT_DMA6       /* 0x16 -    ivINT_DMA6                     unused by PE */
#define VECTOR_23         (tIsrFunc)&Unhandled_ivINT_DMA7       /* 0x17 -    ivINT_DMA7                     unused by PE */
#define VECTOR_24         (tIsrFunc)&Unhandled_ivINT_DMA8       /* 0x18 -    ivINT_DMA8                     unused by PE */
#define VECTOR_25         (tIsrFunc)&Unhandled_ivINT_DMA9       /* 0x19 -    ivINT_DMA9                     unused by PE */
#define VECTOR_26         (tIsrFunc)&Unhandled_ivINT_DMA10      /* 0x1A -    ivINT_DMA10                    unused by PE */
#define VECTOR_27         (tIsrFunc)&Unhandled_ivINT_DMA11      /* 0x1B -    ivINT_DMA11                    unused by PE */
#define VECTOR_28         (tIsrFunc)&Unhandled_ivINT_DMA12      /* 0x1C -    ivINT_DMA12                    unused by PE */
#define VECTOR_29         (tIsrFunc)&Unhandled_ivINT_DMA13      /* 0x1D -    ivINT_DMA13                    unused by PE */
#define VECTOR_30         (tIsrFunc)&Unhandled_ivINT_DMA14      /* 0x1E -    ivINT_DMA14                    unused by PE */
#define VECTOR_31         (tIsrFunc)&Unhandled_ivINT_DMA15      /* 0x1F -    ivINT_DMA15                    unused by PE */
#define VECTOR_32         (tIsrFunc)&Unhandled_ivINT_DMA_Error  /* 0x20 -    ivINT_DMA_Error                unused by PE */
#define VECTOR_33         (tIsrFunc)&Unhandled_ivINT_MCM        /* 0x21 -    ivINT_MCM                      unused by PE */
#define VECTOR_34         (tIsrFunc)&Unhandled_ivINT_FTFE       /* 0x22 -    ivINT_FTFE                     unused by PE */
#define VECTOR_35         (tIsrFunc)&Unhandled_ivINT_Read_Collision /* 0x23 - ivINT_Read_Collision          unused by PE */
#define VECTOR_36         (tIsrFunc)&Unhandled_ivINT_LVD_LVW    /* 0x24 -    ivINT_LVD_LVW                  unused by PE */
#define VECTOR_37         (tIsrFunc)&Unhandled_ivINT_LLWU       /* 0x25 -    ivINT_LLWU                     unused by PE */
#define VECTOR_38         (tIsrFunc)&Unhandled_ivINT_WDOG_EWM   /* 0x26 -    ivINT_WDOG_EWM                 unused by PE */
#define VECTOR_39         (tIsrFunc)&Unhandled_ivINT_RNG        /* 0x27 -    ivINT_RNG                      unused by PE */
#define VECTOR_40         (tIsrFunc)&I2C_Interrupt              /* 0x28 112  ivINT_I2C0                     used by PE */
#define VECTOR_41         (tIsrFunc)&Unhandled_ivINT_I2C1       /* 0x29 -    ivINT_I2C1                     unused by PE */
#define VECTOR_42         (tIsrFunc)&Unhandled_ivINT_SPI0       /* 0x2A -    ivINT_SPI0                     unused by PE */
#define VECTOR_43         (tIsrFunc)&SM2_Interrupt              /* 0x2B 112  ivINT_SPI1                     used by PE */
#define VECTOR_44         (tIsrFunc)&Unhandled_ivINT_I2S0_Tx    /* 0x2C -    ivINT_I2S0_Tx                  unused by PE */
#define VECTOR_45         (tIsrFunc)&Unhandled_ivINT_I2S0_Rx    /* 0x2D -    ivINT_I2S0_Rx                  unused by PE */
#define VECTOR_46         (tIsrFunc)&Unhandled_ivINT_UART0_LON  /* 0x2E -    ivINT_UART0_LON                unused by PE */
#define VECTOR_47         (tIsrFunc)&ASerialLdd2_Interrupt      /* 0x2F 112  ivINT_UART0_RX_TX              used by PE */
#define VECTOR_48         (tIsrFunc)&ASerialLdd2_Interrupt      /* 0x30 112  ivINT_UART0_ERR                used by PE */
#define VECTOR_49         (tIsrFunc)&Unhandled_ivINT_UART1_RX_TX /* 0x31 -   ivINT_UART1_RX_TX              unused by PE */
#define VECTOR_50         (tIsrFunc)&Unhandled_ivINT_UART1_ERR  /* 0x32 -    ivINT_UART1_ERR                unused by PE */
#define VECTOR_51         (tIsrFunc)&Unhandled_ivINT_UART2_RX_TX /* 0x33 -   ivINT_UART2_RX_TX              unused by PE */
#define VECTOR_52         (tIsrFunc)&Unhandled_ivINT_UART2_ERR  /* 0x34 -    ivINT_UART2_ERR                unused by PE */
#define VECTOR_53         (tIsrFunc)&Unhandled_ivINT_UART3_RX_TX /* 0x35 -   ivINT_UART3_RX_TX              unused by PE */
#define VECTOR_54         (tIsrFunc)&Unhandled_ivINT_UART3_ERR  /* 0x36 -    ivINT_UART3_ERR                unused by PE */
#define VECTOR_55         (tIsrFunc)&Unhandled_ivINT_ADC0       /* 0x37 -    ivINT_ADC0                     unused by PE */
#define VECTOR_56         (tIsrFunc)&Unhandled_ivINT_CMP0       /* 0x38 -    ivINT_CMP0                     unused by PE */
#define VECTOR_57         (tIsrFunc)&Unhandled_ivINT_CMP1       /* 0x39 -    ivINT_CMP1                     unused by PE */
#define VECTOR_58         (tIsrFunc)&TU1_Interrupt              /* 0x3A 0    ivINT_FTM0                     used by PE */
#define VECTOR_59         (tIsrFunc)&Unhandled_ivINT_FTM1       /* 0x3B -    ivINT_FTM1                     unused by PE */
#define VECTOR_60         (tIsrFunc)&Unhandled_ivINT_FTM2       /* 0x3C -    ivINT_FTM2                     unused by PE */
#define VECTOR_61         (tIsrFunc)&Unhandled_ivINT_CMT        /* 0x3D -    ivINT_CMT                      unused by PE */
#define VECTOR_62         (tIsrFunc)&Unhandled_ivINT_RTC        /* 0x3E -    ivINT_RTC                      unused by PE */
#define VECTOR_63         (tIsrFunc)&Unhandled_ivINT_RTC_Seconds /* 0x3F -   ivINT_RTC_Seconds              unused by PE */
#define VECTOR_64         (tIsrFunc)&Unhandled_ivINT_PIT0       /* 0x40 -    ivINT_PIT0                     unused by PE */
#define VECTOR_65         (tIsrFunc)&Unhandled_ivINT_PIT1       /* 0x41 -    ivINT_PIT1                     unused by PE */
#define VECTOR_66         (tIsrFunc)&Unhandled_ivINT_PIT2       /* 0x42 -    ivINT_PIT2                     unused by PE */
#define VECTOR_67         (tIsrFunc)&Unhandled_ivINT_PIT3       /* 0x43 -    ivINT_PIT3                     unused by PE */
#define VECTOR_68         (tIsrFunc)&Unhandled_ivINT_PDB0       /* 0x44 -    ivINT_PDB0                     unused by PE */
#define VECTOR_69         (tIsrFunc)&USB_ISR                    /* 0x45 0    ivINT_USB0                     used by PE */
#define VECTOR_70         (tIsrFunc)&Unhandled_ivINT_USBDCD     /* 0x46 -    ivINT_USBDCD                   unused by PE */
#define VECTOR_71         (tIsrFunc)&Unhandled_ivINT_Reserved71 /* 0x47 -    ivINT_Reserved71               unused by PE */
#define VECTOR_72         (tIsrFunc)&Unhandled_ivINT_DAC0       /* 0x48 -    ivINT_DAC0                     unused by PE */
#define VECTOR_73         (tIsrFunc)&Unhandled_ivINT_MCG        /* 0x49 -    ivINT_MCG                      unused by PE */
#define VECTOR_74         (tIsrFunc)&Unhandled_ivINT_LPTMR0     /* 0x4A -    ivINT_LPTMR0                   unused by PE */
#define VECTOR_75         (tIsrFunc)&Unhandled_ivINT_PORTA      /* 0x4B -    ivINT_PORTA                    unused by PE */
#define VECTOR_76         (tIsrFunc)&Unhandled_ivINT_PORTB      /* 0x4C -    ivINT_PORTB                    unused by PE */
#define VECTOR_77         (tIsrFunc)&Unhandled_ivINT_PORTC      /* 0x4D -    ivINT_PORTC                    unused by PE */
#define VECTOR_78         (tIsrFunc)&Unhandled_ivINT_PORTD      /* 0x4E -    ivINT_PORTD                    unused by PE */
#define VECTOR_79         (tIsrFunc)&Unhandled_ivINT_PORTE      /* 0x4F -    ivINT_PORTE                    unused by PE */
#define VECTOR_80         (tIsrFunc)&Unhandled_ivINT_SWI        /* 0x50 -    ivINT_SWI                      unused by PE */
#define VECTOR_81         (tIsrFunc)&Unhandled_ivINT_SPI2       /* 0x51 -    ivINT_SPI2                     unused by PE */
#define VECTOR_82         (tIsrFunc)&ASerialLdd1_Interrupt      /* 0x52 112  ivINT_UART4_RX_TX              used by PE */
#define VECTOR_83         (tIsrFunc)&ASerialLdd1_Interrupt      /* 0x53 112  ivINT_UART4_ERR                used by PE */
#define VECTOR_84         (tIsrFunc)&Unhandled_ivINT_UART5_RX_TX /* 0x54 -   ivINT_UART5_RX_TX              unused by PE */
#define VECTOR_85         (tIsrFunc)&Unhandled_ivINT_UART5_ERR  /* 0x55 -    ivINT_UART5_ERR                unused by PE */
#define VECTOR_86         (tIsrFunc)&Unhandled_ivINT_CMP2       /* 0x56 -    ivINT_CMP2                     unused by PE */
#define VECTOR_87         (tIsrFunc)&Unhandled_ivINT_FTM3       /* 0x57 -    ivINT_FTM3                     unused by PE */
#define VECTOR_88         (tIsrFunc)&Unhandled_ivINT_Reserved88 /* 0x58 -    ivINT_Reserved88               unused by PE */
#define VECTOR_89         (tIsrFunc)&Unhandled_ivINT_ADC1       /* 0x59 -    ivINT_ADC1                     unused by PE */
#define VECTOR_90         (tIsrFunc)&Unhandled_ivINT_I2C2       /* 0x5A -    ivINT_I2C2                     unused by PE */
#define VECTOR_91         (tIsrFunc)&Unhandled_ivINT_CAN0_ORed_Message_buffer /* 0x5B - ivINT_CAN0_ORed_Message_buffer unused by PE */
#define VECTOR_92         (tIsrFunc)&Unhandled_ivINT_CAN0_Bus_Off /* 0x5C -  ivINT_CAN0_Bus_Off             unused by PE */
#define VECTOR_93         (tIsrFunc)&Unhandled_ivINT_CAN0_Error /* 0x5D -    ivINT_CAN0_Error               unused by PE */
#define VECTOR_94         (tIsrFunc)&Unhandled_ivINT_CAN0_Tx_Warning /* 0x5E - ivINT_CAN0_Tx_Warning        unused by PE */
#define VECTOR_95         (tIsrFunc)&Unhandled_ivINT_CAN0_Rx_Warning /* 0x5F - ivINT_CAN0_Rx_Warning        unused by PE */
#define VECTOR_96         (tIsrFunc)&Unhandled_ivINT_CAN0_Wake_Up /* 0x60 -  ivINT_CAN0_Wake_Up             unused by PE */
#define VECTOR_97         (tIsrFunc)&Unhandled_ivINT_SDHC       /* 0x61 -    ivINT_SDHC                     unused by PE */
#define VECTOR_98         (tIsrFunc)&Unhandled_ivINT_ENET_1588_Timer /* 0x62 - ivINT_ENET_1588_Timer        unused by PE */
#define VECTOR_99         (tIsrFunc)&Unhandled_ivINT_ENET_Transmit /* 0x63 - ivINT_ENET_Transmit            unused by PE */
#define VECTOR_100        (tIsrFunc)&Unhandled_ivINT_ENET_Receive /* 0x64 -  ivINT_ENET_Receive             unused by PE */
#define VECTOR_101        (tIsrFunc)&Unhandled_ivINT_ENET_Error /* 0x65 -    ivINT_ENET_Error               unused by PE */
  
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
