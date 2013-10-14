;/*****************************************************************************
; * @file:    startup_MKL25Z4.s
; * @purpose: CMSIS Cortex-M0plus Core Device Startup File
; *           MKL25Z4
; * @version: 1.3
; * @date:    2012-10-4
; *----------------------------------------------------------------------------
; *
; * Copyright: 1997 - 2012 Freescale Semiconductor, Inc. All Rights Reserved.
; *
; ******************************************************************************/


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        
        EXTERN vPortSVCHandler, vPortPendSVHandler, vPortTickHandler
        
        PUBLIC  __vector_table
;        PUBLIC  __vector_table_0x1c ;violates MISRA compliance, varible is only used in this module hence cannot be PUBLIC
        PUBLIC  __Vectors
;        PUBLIC  __Vectors_End ;violates MISRA compliance, varible is only used in this module hence cannot be PUBLIC
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0
        DCD     0
        DCD     0
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     vPortSVCHandler ;SVC_Handler
        DCD     0
        DCD     0
        DCD     vPortPendSVHandler; PendSV_Handler
        DCD     vPortTickHandler; SysTick_Handler

        ; External Interrupts
        DCD     DMA0_IRQHandler  ; DMA channel 0 transfer complete/error interrupt
        DCD     DMA1_IRQHandler  ; DMA channel 1 transfer complete/error interrupt
        DCD     DMA2_IRQHandler  ; DMA channel 2 transfer complete/error interrupt
        DCD     DMA3_IRQHandler  ; DMA channel 3 transfer complete/error interrupt
        DCD     Reserved20_IRQHandler  ; Reserved interrupt 20
        DCD     FTFA_IRQHandler  ; FTFA command complete/read collision interrupt
        DCD     LVD_LVW_IRQHandler  ; Low Voltage Detect, Low Voltage Warning
        DCD     LLW_IRQHandler  ; Low Leakage Wakeup
        DCD     I2C0_IRQHandler  ; I2C0 interrupt
        DCD     I2C1_IRQHandler  ; I2C0 interrupt 25
        DCD     SPI0_IRQHandler  ; SPI0 interrupt
        DCD     SPI1_IRQHandler  ; SPI1 interrupt
        DCD     UART0_IRQHandler  ; UART0 status/error interrupt
        DCD     UART1_IRQHandler  ; UART1 status/error interrupt
        DCD     UART2_IRQHandler  ; UART2 status/error interrupt
        DCD     ADC0_IRQHandler  ; ADC0 interrupt
        DCD     CMP0_IRQHandler  ; CMP0 interrupt
        DCD     TPM0_IRQHandler  ; TPM0 fault, overflow and channels interrupt
        DCD     TPM1_IRQHandler  ; TPM1 fault, overflow and channels interrupt
        DCD     TPM2_IRQHandler  ; TPM2 fault, overflow and channels interrupt
        DCD     RTC_IRQHandler  ; RTC interrupt
        DCD     RTC_Seconds_IRQHandler  ; RTC seconds interrupt
        DCD     PIT_IRQHandler  ; PIT timer interrupt
        DCD     Reserved39_IRQHandler  ; Reserved interrupt 39
        DCD     USB0_IRQHandler  ; USB0 interrupt
        DCD     DAC0_IRQHandler  ; DAC0 interrupt
        DCD     TSI0_IRQHandler  ; TSI0 interrupt
        DCD     MCG_IRQHandler  ; MCG interrupt
        DCD     LPTimer_IRQHandler  ; LPTimer interrupt
        DCD     Reserved45_IRQHandler  ; Reserved interrupt 45
        DCD     PORTA_IRQHandler  ; Port A interrupt
        DCD     PORTD_IRQHandler  ; Port D interrupt
__Vectors_End
__FlashConfig
      	DCD	0xFFFFFFFF
      	DCD	0xFFFFFFFF
      	DCD	0xFFFFFFFF
      	DCD	0xFFFFFFFE
__FlashConfig_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(2)
NMI_Handler
        B       .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(2)
HardFault_Handler
        B       .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(2)
SVC_Handler
        B       .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(2)
PendSV_Handler
        B       .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(2)
SysTick_Handler
        B       .

        PUBWEAK DMA0_IRQHandler
        PUBWEAK DMA1_IRQHandler
        PUBWEAK DMA2_IRQHandler
        PUBWEAK DMA3_IRQHandler
        PUBWEAK Reserved20_IRQHandler
        PUBWEAK FTFA_IRQHandler
        PUBWEAK LVD_LVW_IRQHandler
        PUBWEAK LLW_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK ADC0_IRQHandler
        PUBWEAK CMP0_IRQHandler
        PUBWEAK TPM0_IRQHandler
        PUBWEAK TPM1_IRQHandler
        PUBWEAK TPM2_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_Seconds_IRQHandler
        PUBWEAK PIT_IRQHandler
        PUBWEAK Reserved39_IRQHandler
        PUBWEAK USB0_IRQHandler
        PUBWEAK DAC0_IRQHandler
        PUBWEAK TSI0_IRQHandler
        PUBWEAK MCG_IRQHandler
        PUBWEAK LPTimer_IRQHandler
        PUBWEAK Reserved45_IRQHandler
        PUBWEAK PORTA_IRQHandler
        PUBWEAK PORTD_IRQHandler
        PUBWEAK DefaultISR

        SECTION .text:CODE:REORDER(2)
        
DMA0_IRQHandler
DMA1_IRQHandler
DMA2_IRQHandler
DMA3_IRQHandler
Reserved20_IRQHandler
FTFA_IRQHandler
LVD_LVW_IRQHandler
LLW_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
TPM0_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT_IRQHandler
Reserved39_IRQHandler
USB0_IRQHandler
DAC0_IRQHandler
TSI0_IRQHandler
MCG_IRQHandler
LPTimer_IRQHandler
Reserved45_IRQHandler
PORTA_IRQHandler
PORTD_IRQHandler
DefaultISR
        B       .

        END
