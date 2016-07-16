/**
 * \file vectors.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 17.11.2015
 * \brief Vector table
 *
 */

#include "system_MK20D5.h"

/* ISR prototype */
extern uint32_t __SP_INIT;
extern
#ifdef __cplusplus
"C"
#endif
void __thumb_startup(void);

/*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */

__attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */

/* ISR name                                 No.  Address     Pri  Name               Description */
&__SP_INIT,                             /* 0x00  0x00000000   -   ivINT_Initial_Stack_Pointer    */
{ (tIsrFunc) & __thumb_startup,         /* 0x01  0x00000004   -   ivINT_Initial_Program_Counter  */
(tIsrFunc) & NMI_Handler,               /* 0x02  0x00000008   -2  ivINT_NMI                      */
(tIsrFunc) & HardFault_Handler,         /* 0x03  0x0000000C   -1  ivINT_Hard_Fault               */
(tIsrFunc) & MemManage_Handler,         /* 0x04  0x00000010   -   ivINT_Mem_Manage_Fault         */
(tIsrFunc) & BusFault_Handler,          /* 0x05  0x00000014   -   ivINT_Bus_Fault                */
(tIsrFunc) & UsageFault_Handler,        /* 0x06  0x00000018   -   ivINT_Usage_Fault              */
(tIsrFunc) & Reserved7_IRQHandler,      /* 0x07  0x0000001C   -   ivINT_Reserved7                */
(tIsrFunc) & Reserved8_IRQHandler,      /* 0x08  0x00000020   -   ivINT_Reserved8                */
(tIsrFunc) & Reserved9_IRQHandler,      /* 0x09  0x00000024   -   ivINT_Reserved9                */
(tIsrFunc) & Reserved10_IRQHandler,     /* 0x0A  0x00000028   -   ivINT_Reserved10               */
(tIsrFunc) & vPortSVCHandler,           /* 0x0B  0x0000002C   -   ivINT_SVCall                   */
(tIsrFunc) & DebugMon_Handler,          /* 0x0C  0x00000030   -   ivINT_DebugMonitor             */
(tIsrFunc) & Reserved13_IRQHandler,     /* 0x0D  0x00000034   -   ivINT_Reserved13               */
(tIsrFunc) & vPortPendSVHandler,        /* 0x0E  0x00000038   -   ivINT_PendableSrvReq           */
(tIsrFunc) & vPortTickHandler,           /* 0x0F  0x0000003C   -   ivINT_SysTick                  */
(tIsrFunc) & DMA0_IRQHandler,           /* 0x10  0x00000040   -   ivINT_DMA0                     */
(tIsrFunc) & DMA1_IRQHandler,           /* 0x11  0x00000044   -   ivINT_DMA1                     */
(tIsrFunc) & DMA2_IRQHandler,           /* 0x12  0x00000048   -   ivINT_DMA2                     */
(tIsrFunc) & DMA3_IRQHandler,           /* 0x13  0x0000004C   -   ivINT_DMA3                     */
(tIsrFunc) & DMA_Error_IRQHandler,      /* 0x14  0x00000050   -   ivINT_DMA_Error                */
(tIsrFunc) & Reserved21_IRQHandler,     /* 0x15  0x00000054   -   ivINT_Reserved21               */
(tIsrFunc) & FTF_IRQHandler,            /* 0x16  0x00000058   -   ivINT_FTFL                     */
(tIsrFunc) & Read_Collision_IRQHandler, /* 0x17  0x0000005C   -   ivINT_Read_Collision           */
(tIsrFunc) & LVD_LVW_IRQHandler,        /* 0x18  0x00000060   -   ivINT_LVD_LVW                  */
(tIsrFunc) & LLWU_IRQHandler,           /* 0x19  0x00000064   -   ivINT_LLW                      */
(tIsrFunc) & WDOG_IRQHandler,           /* 0x1A  0x00000068   -   ivINT_Watchdog                 */
(tIsrFunc) & I2C0_IRQHandler,           /* 0x1B  0x0000006C   -   ivINT_I2C0                     */
(tIsrFunc) & SPI0_IRQHandler,           /* 0x1C  0x00000070   -   ivINT_SPI0                     */
(tIsrFunc) & I2S0_Tx_IRQHandler,        /* 0x1D  0x00000074   -   ivINT_I2S0_Tx                  */
(tIsrFunc) & I2S0_Rx_IRQHandler,        /* 0x1E  0x00000078   -   ivINT_I2S0_Rx                  */
(tIsrFunc) & UART0_LON_IRQHandler,      /* 0x1F  0x0000007C   -   ivINT_UART0_LON                */
(tIsrFunc) & UART0_RX_TX_IRQHandler,    /* 0x20  0x00000080   -   ivINT_UART0_RX_TX              */
(tIsrFunc) & UART0_ERR_IRQHandler,      /* 0x21  0x00000084   -   ivINT_UART0_ERR                */
(tIsrFunc) & UART1_RX_TX_IRQHandler,    /* 0x22  0x00000088   -   ivINT_UART1_RX_TX              */
(tIsrFunc) & UART1_ERR_IRQHandler,      /* 0x23  0x0000008C   -   ivINT_UART1_ERR                */
(tIsrFunc) & UART2_RX_TX_IRQHandler,    /* 0x24  0x00000090   -   ivINT_UART2_RX_TX              */
(tIsrFunc) & UART2_ERR_IRQHandler,      /* 0x25  0x00000094   -   ivINT_UART2_ERR                */
(tIsrFunc) & ADC0_IRQHandler,           /* 0x26  0x00000098   -   ivINT_ADC0                     */
(tIsrFunc) & CMP0_IRQHandler,           /* 0x27  0x0000009C   -   ivINT_CMP0                     */
(tIsrFunc) & CMP1_IRQHandler,           /* 0x28  0x000000A0   -   ivINT_CMP1                     */
(tIsrFunc) & FTM0_IRQHandler,           /* 0x29  0x000000A4   -   ivINT_FTM0                     */
(tIsrFunc) & FTM1_IRQHandler,           /* 0x2A  0x000000A8   -   ivINT_FTM1                     */
(tIsrFunc) & CMT_IRQHandler,            /* 0x2B  0x000000AC   -   ivINT_CMT                      */
(tIsrFunc) & RTC_IRQHandler,            /* 0x2C  0x000000B0   -   ivINT_RTC                      */
(tIsrFunc) & RTC_Seconds_IRQHandler,    /* 0x2D  0x000000B4   -   ivINT_RTC_Seconds              */
(tIsrFunc) & PIT0_IRQHandler,           /* 0x2E  0x000000B8   -   ivINT_PIT0                     */
(tIsrFunc) & PIT1_IRQHandler,           /* 0x2F  0x000000BC   -   ivINT_PIT1                     */
(tIsrFunc) & PIT2_IRQHandler,           /* 0x30  0x000000C0   -   ivINT_PIT2                     */
(tIsrFunc) & PIT3_IRQHandler,           /* 0x31  0x000000C4   -   ivINT_PIT3                     */
(tIsrFunc) & PDB0_IRQHandler,           /* 0x32  0x000000C8   -   ivINT_PDB0                     */
(tIsrFunc) & USB0_IRQHandler,           /* 0x33  0x000000CC   -   ivINT_USB0                     */
(tIsrFunc) & USBCDC_IRQHandler,         /* 0x34  0x000000D0   -   ivINT_USBDCD                   */
(tIsrFunc) & TSI0_IRQHandler,           /* 0x35  0x000000D4   -   ivINT_TSI0                     */
(tIsrFunc) & MCG_IRQHandler,            /* 0x36  0x000000D8   -   ivINT_MCG                      */
(tIsrFunc) & LPTMR0_IRQHandler,         /* 0x37  0x000000DC   -   ivINT_LPTimer                  */
(tIsrFunc) & PORTA_IRQHandler,          /* 0x38  0x000000E0   -   ivINT_PORTA                    */
(tIsrFunc) & PORTB_IRQHandler,          /* 0x39  0x000000E4   -   ivINT_PORTB                    */
(tIsrFunc) & PORTC_IRQHandler,          /* 0x3A  0x000000E8   -   ivINT_PORTC                    */
(tIsrFunc) & PORTD_IRQHandler,          /* 0x3B  0x000000EC   -   ivINT_PORTD                    */
(tIsrFunc) & PORTE_IRQHandler,          /* 0x3C  0x000000F0   -   ivINT_PORTE                    */
(tIsrFunc) & SWI_IRQHandler             /* 0x3D  0x000000F4   -   ivINT_SWI                      */
} };

