/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_MKV58F24.s                                                          */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                                    */
/*            MKV58F24                                                                    */
/*  @version: 0.3                                                                         */
/*  @date:    2016-2-29                                                                   */
/*  @build:   b160229                                                                     */
/* ---------------------------------------------------------------------------------------*/
/*                                                                                        */
/* Copyright (c) 1997 - 2016 , Freescale Semiconductor, Inc.                              */
/* All rights reserved.                                                                   */
/*                                                                                        */
/* Redistribution and use in source and binary forms, with or without modification,       */
/* are permitted provided that the following conditions are met:                          */
/*                                                                                        */
/* o Redistributions of source code must retain the above copyright notice, this list     */
/*   of conditions and the following disclaimer.                                          */
/*                                                                                        */
/* o Redistributions in binary form must reproduce the above copyright notice, this       */
/*   list of conditions and the following disclaimer in the documentation and/or          */
/*   other materials provided with the distribution.                                      */
/*                                                                                        */
/* o Neither the name of Freescale Semiconductor, Inc. nor the names of its               */
/*   contributors may be used to endorse or promote products derived from this            */
/*   software without specific prior written permission.                                  */
/*                                                                                        */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND        */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR       */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES         */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;           */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON         */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   MemManage_Handler                               /* MPU Fault Handler*/
    .long   BusFault_Handler                                /* Bus Fault Handler*/
    .long   UsageFault_Handler                              /* Usage Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   DMA0_DMA16_IRQHandler                           /* DMA channel 0/16 transfer complete*/
    .long   DMA1_DMA17_IRQHandler                           /* DMA channel 1/17 transfer complete*/
    .long   DMA2_DMA18_IRQHandler                           /* DMA channel 2/18 transfer complete*/
    .long   DMA3_DMA19_IRQHandler                           /* DMA channel 3/19 transfer complete*/
    .long   DMA4_DMA20_IRQHandler                           /* DMA channel 4/20 transfer complete*/
    .long   DMA5_DMA21_IRQHandler                           /* DMA channel 5/21 transfer complete*/
    .long   DMA6_DMA22_IRQHandler                           /* DMA channel 6/22 transfer complete*/
    .long   DMA7_DMA23_IRQHandler                           /* DMA channel 7/23 transfer complete*/
    .long   DMA8_DMA24_IRQHandler                           /* DMA channel 8/24 transfer complete*/
    .long   DMA9_DMA25_IRQHandler                           /* DMA channel 9/25 transfer complete*/
    .long   DMA10_DMA26_IRQHandler                          /* DMA channel 10/26 transfer complete*/
    .long   DMA11_DMA27_IRQHandler                          /* DMA channel 11/27 transfer complete*/
    .long   DMA12_DMA28_IRQHandler                          /* DMA channel 12/28 transfer complete*/
    .long   DMA13_DMA29_IRQHandler                          /* DMA channel 13/29 transfer complete*/
    .long   DMA14_DMA30_IRQHandler                          /* DMA channel 14/30 transfer complete*/
    .long   DMA15_DMA31_IRQHandler                          /* DMA channel 15/31 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA error interrupt channels 0-31*/
    .long   MCM_IRQHandler                                  /* MCM normal interrupt*/
    .long   FTFE_IRQHandler                                 /* FTFL command complete*/
    .long   Read_Collision_IRQHandler                       /* FTFL read collision*/
    .long   PMC_IRQHandler                                  /* PMC controller low-voltage detect, low-voltage warning*/
    .long   LLWU_IRQHandler                                 /* Low leakage wakeup*/
    .long   WDOG_EWM_IRQHandler                             /* Single interrupt vector for  WDOG and EWM*/
    .long   TRNG0_IRQHandler                                /* True randon number generator*/
    .long   I2C0_IRQHandler                                 /* Inter-integrated circuit 0*/
    .long   I2C1_IRQHandler                                 /* Inter-integrated circuit 1*/
    .long   SPI0_IRQHandler                                 /* Serial peripheral Interface 0*/
    .long   SPI1_IRQHandler                                 /* Serial peripheral Interface 1*/
    .long   UART5_RX_TX_IRQHandler                          /* UART5 receive/transmit interrupt*/
    .long   UART5_ERR_IRQHandler                            /* UART5 error interrupt*/
    .long   Reserved46_IRQHandler                           /* Reserved interrupt*/
    .long   UART0_RX_TX_IRQHandler                          /* UART0 receive/transmit interrupt*/
    .long   UART0_ERR_IRQHandler                            /* UART0 error interrupt*/
    .long   UART1_RX_TX_IRQHandler                          /* UART1 receive/transmit interrupt*/
    .long   UART1_ERR_IRQHandler                            /* UART1 error interrupt*/
    .long   UART2_RX_TX_IRQHandler                          /* UART2 receive/transmit interrupt*/
    .long   UART2_ERR_IRQHandler                            /* UART2 error interrupt*/
    .long   ADC0_IRQHandler                                 /* Analog-to-digital converter 0*/
    .long   HSADC_ERR_IRQHandler                            /* High speed analog-to-digital converter zero cross*/
    .long   HSADC0_CCA_IRQHandler                           /* High speed analog-to-digital converter 0 submodule A scan complete*/
    .long   CMP0_IRQHandler                                 /* Comparator 0*/
    .long   CMP1_IRQHandler                                 /* Comparator 1*/
    .long   FTM0_IRQHandler                                 /* FlexTimer module 0 fault, overflow and channels interrupt*/
    .long   FTM1_IRQHandler                                 /* FlexTimer module 1 fault, overflow and channels interrupt*/
    .long   UART3_RX_TX_IRQHandler                          /* UART3 receive/transmit interrupt*/
    .long   UART3_ERR_IRQHandler                            /* UART3 error interrupt*/
    .long   UART4_RX_TX_IRQHandler                          /* UART4 receive/transmit interrupt*/
    .long   UART4_ERR_IRQHandler                            /* UART4 error interrupt*/
    .long   PIT0_IRQHandler                                 /* Periodic interrupt timer channel 0*/
    .long   PIT1_IRQHandler                                 /* Periodic interrupt timer channel 1*/
    .long   PIT2_IRQHandler                                 /* Periodic interrupt timer channel 2*/
    .long   PIT3_IRQHandler                                 /* Periodic interrupt timer channel 3*/
    .long   PDB0_IRQHandler                                 /* Programmable delay block 0*/
    .long   FTM2_IRQHandler                                 /* FlexTimer module 2 fault, overflow and channels interrupt*/
    .long   XBARA_IRQHandler                                /* Inter-peripheral crossbar switch A*/
    .long   PDB1_IRQHandler                                 /* Programmable delay block 1*/
    .long   DAC0_IRQHandler                                 /* Digital-to-analog converter 0*/
    .long   MCG_IRQHandler                                  /* Multipurpose clock generator*/
    .long   LPTMR0_IRQHandler                               /* Low power timer interrupt*/
    .long   PORTA_IRQHandler                                /* Port A interrupt*/
    .long   PORTB_IRQHandler                                /* Port B interrupt*/
    .long   PORTC_IRQHandler                                /* Port C interrupt*/
    .long   PORTD_IRQHandler                                /* Port D interrupt*/
    .long   PORTE_IRQHandler                                /* Port E interrupt*/
    .long   SWI_IRQHandler                                  /* Software interrupt*/
    .long   SPI2_IRQHandler                                 /* Serial peripheral Interface 2*/
    .long   ENC_COMPARE_IRQHandler                          /* ENC Compare*/
    .long   ENC_HOME_IRQHandler                             /* ENC Home*/
    .long   ENC_WDOG_SAB_IRQHandler                         /* ENC Wdog/SAB*/
    .long   ENC_INDEX_IRQHandler                            /* ENC Index/Roll over/Roll Under*/
    .long   CMP2_IRQHandler                                 /* Comparator 2*/
    .long   FTM3_IRQHandler                                 /* FlexTimer module 3 fault, overflow and channels*/
    .long   Reserved88_IRQHandler                           /* Reserved interrupt*/
    .long   HSADC0_CCB_IRQHandler                           /* High speed analog-to-digital converter 0 submodule B scan complete*/
    .long   HSADC1_CCA_IRQHandler                           /* High speed analog-to-digital converter 1 submodule A scan complete*/
    .long   CAN0_ORed_Message_buffer_IRQHandler             /* Flex controller area network 0 message buffer*/
    .long   CAN0_Bus_Off_IRQHandler                         /* Flex controller area network 0 bus off*/
    .long   CAN0_Error_IRQHandler                           /* Flex controller area network 0 error*/
    .long   CAN0_Tx_Warning_IRQHandler                      /* Flex controller area network 0 transmit*/
    .long   CAN0_Rx_Warning_IRQHandler                      /* Flex controller area network 0 receive*/
    .long   CAN0_Wake_Up_IRQHandler                         /* Flex controller area network 0 wake up*/
    .long   PWM0_CMP0_IRQHandler                            /* Pulse width modulator 0 channel 0 compare*/
    .long   PWM0_RELOAD0_IRQHandler                         /* Pulse width modulator 0 channel 0 reload*/
    .long   PWM0_CMP1_IRQHandler                            /* Pulse width modulator 0 channel 1 compare*/
    .long   PWM0_RELOAD1_IRQHandler                         /* Pulse width modulator 0 channel 1 reload*/
    .long   PWM0_CMP2_IRQHandler                            /* Pulse width modulator 0 channel 2 compare*/
    .long   PWM0_RELOAD2_IRQHandler                         /* Pulse width modulator 0 channel 2 reload*/
    .long   PWM0_CMP3_IRQHandler                            /* Pulse width modulator 0 channel 3 compare*/
    .long   PWM0_RELOAD3_IRQHandler                         /* Pulse width modulator 0 channel 3 reload*/
    .long   PWM0_CAP_IRQHandler                             /* Pulse width modulator 0 capture*/
    .long   PWM0_RERR_IRQHandler                            /* Pulse width modulator 0 reload error*/
    .long   PWM0_FAULT_IRQHandler                           /* Pulse width modulator 0 fault*/
    .long   CMP3_IRQHandler                                 /* Comparator 3*/
    .long   HSADC1_CCB_IRQHandler                           /* High speed analog-to-digital converter 1 submodule B scan complete*/
    .long   CAN1_ORed_Message_buffer_IRQHandler             /* Flex controller area network 1 message buffer*/
    .long   CAN1_Bus_Off_IRQHandler                         /* Flex controller area network 1 bus off*/
    .long   CAN1_Error_IRQHandler                           /* Flex controller area network 1 error*/
    .long   CAN1_Tx_Warning_IRQHandler                      /* Flex controller area network 1 transmit*/
    .long   CAN1_Rx_Warning_IRQHandler                      /* Flex controller area network 1 receive*/
    .long   CAN1_Wake_Up_IRQHandler                         /* Flex controller area network 1 wake up*/
    .long   ENET_1588_Timer_IRQHandler                      /* Ethernet MAC IEEE 1588 timer*/
    .long   ENET_Transmit_IRQHandler                        /* Ethernet MAC transmit*/
    .long   ENET_Receive_IRQHandler                         /* Ethernet MAC receive*/
    .long   ENET_Error_IRQHandler                           /* Ethernet MAC error and miscelaneous*/
    .long   PWM1_CMP0_IRQHandler                            /* Pulse width modulator 1 channel 0 compare*/
    .long   PWM1_RELOAD0_IRQHandler                         /* Pulse width modulator 1 channel 0 reload*/
    .long   PWM1_CMP1_IRQHandler                            /* Pulse width modulator 1 channel 1 compare*/
    .long   PWM1_RELOAD1_IRQHandler                         /* Pulse width modulator 1 channel 1 reload*/
    .long   PWM1_CMP2_IRQHandler                            /* Pulse width modulator 1 channel 2 compare*/
    .long   PWM1_RELOAD2_IRQHandler                         /* Pulse width modulator 1 channel 2 reload*/
    .long   PWM1_CMP3_IRQHandler                            /* Pulse width modulator 1 channel 3 compare*/
    .long   PWM1_RELOAD3_IRQHandler                         /* Pulse width modulator 1 channel 3 reload*/
    .long   PWM1_CAP_IRQHandler                             /* Pulse width modulator 1 capture*/
    .long   PWM1_RERR_IRQHandler                            /* Pulse width modulator 1 reload error*/
    .long   PWM1_FAULT_IRQHandler                           /* Pulse width modulator 1 fault*/
    .long   CAN2_ORed_Message_buffer_IRQHandler             /* Flex controller area network 2 message buffer*/
    .long   CAN2_Bus_Off_IRQHandler                         /* Flex controller area network 2 bus off*/
    .long   CAN2_Error_IRQHandler                           /* Flex controller area network 2 error*/
    .long   CAN2_Tx_Warning_IRQHandler                      /* Flex controller area network 2 transmit*/
    .long   CAN2_Rx_Warning_IRQHandler                      /* Flex controller area network 2 receive*/
    .long   CAN2_Wake_Up_IRQHandler                         /* Flex controller area network 2 wake up*/
    .long   DefaultISR                                      /* 137*/
    .long   DefaultISR                                      /* 138*/
    .long   DefaultISR                                      /* 139*/
    .long   DefaultISR                                      /* 140*/
    .long   DefaultISR                                      /* 141*/
    .long   DefaultISR                                      /* 142*/
    .long   DefaultISR                                      /* 143*/
    .long   DefaultISR                                      /* 144*/
    .long   DefaultISR                                      /* 145*/
    .long   DefaultISR                                      /* 146*/
    .long   DefaultISR                                      /* 147*/
    .long   DefaultISR                                      /* 148*/
    .long   DefaultISR                                      /* 149*/
    .long   DefaultISR                                      /* 150*/
    .long   DefaultISR                                      /* 151*/
    .long   DefaultISR                                      /* 152*/
    .long   DefaultISR                                      /* 153*/
    .long   DefaultISR                                      /* 154*/
    .long   DefaultISR                                      /* 155*/
    .long   DefaultISR                                      /* 156*/
    .long   DefaultISR                                      /* 157*/
    .long   DefaultISR                                      /* 158*/
    .long   DefaultISR                                      /* 159*/
    .long   DefaultISR                                      /* 160*/
    .long   DefaultISR                                      /* 161*/
    .long   DefaultISR                                      /* 162*/
    .long   DefaultISR                                      /* 163*/
    .long   DefaultISR                                      /* 164*/
    .long   DefaultISR                                      /* 165*/
    .long   DefaultISR                                      /* 166*/
    .long   DefaultISR                                      /* 167*/
    .long   DefaultISR                                      /* 168*/
    .long   DefaultISR                                      /* 169*/
    .long   DefaultISR                                      /* 170*/
    .long   DefaultISR                                      /* 171*/
    .long   DefaultISR                                      /* 172*/
    .long   DefaultISR                                      /* 173*/
    .long   DefaultISR                                      /* 174*/
    .long   DefaultISR                                      /* 175*/
    .long   DefaultISR                                      /* 176*/
    .long   DefaultISR                                      /* 177*/
    .long   DefaultISR                                      /* 178*/
    .long   DefaultISR                                      /* 179*/
    .long   DefaultISR                                      /* 180*/
    .long   DefaultISR                                      /* 181*/
    .long   DefaultISR                                      /* 182*/
    .long   DefaultISR                                      /* 183*/
    .long   DefaultISR                                      /* 184*/
    .long   DefaultISR                                      /* 185*/
    .long   DefaultISR                                      /* 186*/
    .long   DefaultISR                                      /* 187*/
    .long   DefaultISR                                      /* 188*/
    .long   DefaultISR                                      /* 189*/
    .long   DefaultISR                                      /* 190*/
    .long   DefaultISR                                      /* 191*/
    .long   DefaultISR                                      /* 192*/
    .long   DefaultISR                                      /* 193*/
    .long   DefaultISR                                      /* 194*/
    .long   DefaultISR                                      /* 195*/
    .long   DefaultISR                                      /* 196*/
    .long   DefaultISR                                      /* 197*/
    .long   DefaultISR                                      /* 198*/
    .long   DefaultISR                                      /* 199*/
    .long   DefaultISR                                      /* 200*/
    .long   DefaultISR                                      /* 201*/
    .long   DefaultISR                                      /* 202*/
    .long   DefaultISR                                      /* 203*/
    .long   DefaultISR                                      /* 204*/
    .long   DefaultISR                                      /* 205*/
    .long   DefaultISR                                      /* 206*/
    .long   DefaultISR                                      /* 207*/
    .long   DefaultISR                                      /* 208*/
    .long   DefaultISR                                      /* 209*/
    .long   DefaultISR                                      /* 210*/
    .long   DefaultISR                                      /* 211*/
    .long   DefaultISR                                      /* 212*/
    .long   DefaultISR                                      /* 213*/
    .long   DefaultISR                                      /* 214*/
    .long   DefaultISR                                      /* 215*/
    .long   DefaultISR                                      /* 216*/
    .long   DefaultISR                                      /* 217*/
    .long   DefaultISR                                      /* 218*/
    .long   DefaultISR                                      /* 219*/
    .long   DefaultISR                                      /* 220*/
    .long   DefaultISR                                      /* 221*/
    .long   DefaultISR                                      /* 222*/
    .long   DefaultISR                                      /* 223*/
    .long   DefaultISR                                      /* 224*/
    .long   DefaultISR                                      /* 225*/
    .long   DefaultISR                                      /* 226*/
    .long   DefaultISR                                      /* 227*/
    .long   DefaultISR                                      /* 228*/
    .long   DefaultISR                                      /* 229*/
    .long   DefaultISR                                      /* 230*/
    .long   DefaultISR                                      /* 231*/
    .long   DefaultISR                                      /* 232*/
    .long   DefaultISR                                      /* 233*/
    .long   DefaultISR                                      /* 234*/
    .long   DefaultISR                                      /* 235*/
    .long   DefaultISR                                      /* 236*/
    .long   DefaultISR                                      /* 237*/
    .long   DefaultISR                                      /* 238*/
    .long   DefaultISR                                      /* 239*/
    .long   DefaultISR                                      /* 240*/
    .long   DefaultISR                                      /* 241*/
    .long   DefaultISR                                      /* 242*/
    .long   DefaultISR                                      /* 243*/
    .long   DefaultISR                                      /* 244*/
    .long   DefaultISR                                      /* 245*/
    .long   DefaultISR                                      /* 246*/
    .long   DefaultISR                                      /* 247*/
    .long   DefaultISR                                      /* 248*/
    .long   DefaultISR                                      /* 249*/
    .long   DefaultISR                                      /* 250*/
    .long   DefaultISR                                      /* 251*/
    .long   DefaultISR                                      /* 252*/
    .long   DefaultISR                                      /* 253*/
    .long   DefaultISR                                      /* 254*/
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value*/

    .size    __isr_vector, . - __isr_vector

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFE

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
#ifndef __NO_SYSTEM_INIT
    bl SystemInit
#endif
    bl init_data_bss
    cpsie   i               /* Unmask interrupts */
#ifndef __START
#define __START _start
#endif
#ifndef __ATOLLIC__
    bl    __START
#else
    bl    __libc_init_array
    bl    main
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align	1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b	DefaultISR
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler	handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler
    def_irq_handler    DMA0_DMA16_IRQHandler
    def_irq_handler    DMA1_DMA17_IRQHandler
    def_irq_handler    DMA2_DMA18_IRQHandler
    def_irq_handler    DMA3_DMA19_IRQHandler
    def_irq_handler    DMA4_DMA20_IRQHandler
    def_irq_handler    DMA5_DMA21_IRQHandler
    def_irq_handler    DMA6_DMA22_IRQHandler
    def_irq_handler    DMA7_DMA23_IRQHandler
    def_irq_handler    DMA8_DMA24_IRQHandler
    def_irq_handler    DMA9_DMA25_IRQHandler
    def_irq_handler    DMA10_DMA26_IRQHandler
    def_irq_handler    DMA11_DMA27_IRQHandler
    def_irq_handler    DMA12_DMA28_IRQHandler
    def_irq_handler    DMA13_DMA29_IRQHandler
    def_irq_handler    DMA14_DMA30_IRQHandler
    def_irq_handler    DMA15_DMA31_IRQHandler
    def_irq_handler    DMA_Error_IRQHandler
    def_irq_handler    MCM_IRQHandler
    def_irq_handler    FTFE_IRQHandler
    def_irq_handler    Read_Collision_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    TRNG0_IRQHandler
    def_irq_handler    I2C0_IRQHandler
    def_irq_handler    I2C1_IRQHandler
    def_irq_handler    SPI0_IRQHandler
    def_irq_handler    SPI1_IRQHandler
    def_irq_handler    UART5_RX_TX_IRQHandler
    def_irq_handler    UART5_ERR_IRQHandler
    def_irq_handler    Reserved46_IRQHandler
    def_irq_handler    UART0_RX_TX_IRQHandler
    def_irq_handler    UART0_ERR_IRQHandler
    def_irq_handler    UART1_RX_TX_IRQHandler
    def_irq_handler    UART1_ERR_IRQHandler
    def_irq_handler    UART2_RX_TX_IRQHandler
    def_irq_handler    UART2_ERR_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    HSADC_ERR_IRQHandler
    def_irq_handler    HSADC0_CCA_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    FTM0_IRQHandler
    def_irq_handler    FTM1_IRQHandler
    def_irq_handler    UART3_RX_TX_IRQHandler
    def_irq_handler    UART3_ERR_IRQHandler
    def_irq_handler    UART4_RX_TX_IRQHandler
    def_irq_handler    UART4_ERR_IRQHandler
    def_irq_handler    PIT0_IRQHandler
    def_irq_handler    PIT1_IRQHandler
    def_irq_handler    PIT2_IRQHandler
    def_irq_handler    PIT3_IRQHandler
    def_irq_handler    PDB0_IRQHandler
    def_irq_handler    FTM2_IRQHandler
    def_irq_handler    XBARA_IRQHandler
    def_irq_handler    PDB1_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    PORTA_IRQHandler
    def_irq_handler    PORTB_IRQHandler
    def_irq_handler    PORTC_IRQHandler
    def_irq_handler    PORTD_IRQHandler
    def_irq_handler    PORTE_IRQHandler
    def_irq_handler    SWI_IRQHandler
    def_irq_handler    SPI2_IRQHandler
    def_irq_handler    ENC_COMPARE_IRQHandler
    def_irq_handler    ENC_HOME_IRQHandler
    def_irq_handler    ENC_WDOG_SAB_IRQHandler
    def_irq_handler    ENC_INDEX_IRQHandler
    def_irq_handler    CMP2_IRQHandler
    def_irq_handler    FTM3_IRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    HSADC0_CCB_IRQHandler
    def_irq_handler    HSADC1_CCA_IRQHandler
    def_irq_handler    CAN0_ORed_Message_buffer_IRQHandler
    def_irq_handler    CAN0_Bus_Off_IRQHandler
    def_irq_handler    CAN0_Error_IRQHandler
    def_irq_handler    CAN0_Tx_Warning_IRQHandler
    def_irq_handler    CAN0_Rx_Warning_IRQHandler
    def_irq_handler    CAN0_Wake_Up_IRQHandler
    def_irq_handler    PWM0_CMP0_IRQHandler
    def_irq_handler    PWM0_RELOAD0_IRQHandler
    def_irq_handler    PWM0_CMP1_IRQHandler
    def_irq_handler    PWM0_RELOAD1_IRQHandler
    def_irq_handler    PWM0_CMP2_IRQHandler
    def_irq_handler    PWM0_RELOAD2_IRQHandler
    def_irq_handler    PWM0_CMP3_IRQHandler
    def_irq_handler    PWM0_RELOAD3_IRQHandler
    def_irq_handler    PWM0_CAP_IRQHandler
    def_irq_handler    PWM0_RERR_IRQHandler
    def_irq_handler    PWM0_FAULT_IRQHandler
    def_irq_handler    CMP3_IRQHandler
    def_irq_handler    HSADC1_CCB_IRQHandler
    def_irq_handler    CAN1_ORed_Message_buffer_IRQHandler
    def_irq_handler    CAN1_Bus_Off_IRQHandler
    def_irq_handler    CAN1_Error_IRQHandler
    def_irq_handler    CAN1_Tx_Warning_IRQHandler
    def_irq_handler    CAN1_Rx_Warning_IRQHandler
    def_irq_handler    CAN1_Wake_Up_IRQHandler
    def_irq_handler    ENET_1588_Timer_IRQHandler
    def_irq_handler    ENET_Transmit_IRQHandler
    def_irq_handler    ENET_Receive_IRQHandler
    def_irq_handler    ENET_Error_IRQHandler
    def_irq_handler    PWM1_CMP0_IRQHandler
    def_irq_handler    PWM1_RELOAD0_IRQHandler
    def_irq_handler    PWM1_CMP1_IRQHandler
    def_irq_handler    PWM1_RELOAD1_IRQHandler
    def_irq_handler    PWM1_CMP2_IRQHandler
    def_irq_handler    PWM1_RELOAD2_IRQHandler
    def_irq_handler    PWM1_CMP3_IRQHandler
    def_irq_handler    PWM1_RELOAD3_IRQHandler
    def_irq_handler    PWM1_CAP_IRQHandler
    def_irq_handler    PWM1_RERR_IRQHandler
    def_irq_handler    PWM1_FAULT_IRQHandler
    def_irq_handler    CAN2_ORed_Message_buffer_IRQHandler
    def_irq_handler    CAN2_Bus_Off_IRQHandler
    def_irq_handler    CAN2_Error_IRQHandler
    def_irq_handler    CAN2_Tx_Warning_IRQHandler
    def_irq_handler    CAN2_Rx_Warning_IRQHandler
    def_irq_handler    CAN2_Wake_Up_IRQHandler

    .end
