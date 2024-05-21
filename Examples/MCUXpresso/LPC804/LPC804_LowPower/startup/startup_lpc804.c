//*****************************************************************************
// LPC804 startup code for use with MCUXpresso IDE
//
// Version : 160420
//*****************************************************************************
//
// Copyright 2016-2020 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************

#if defined (DEBUG)
#pragma GCC push_options
#pragma GCC optimize ("Og")
#endif // (DEBUG)

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define WEAK_AV __attribute__ ((weak, section(".after_vectors")))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
//*****************************************************************************
#include <NXP/crp.h>
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

//*****************************************************************************
// Declaration of external SystemInit function
//*****************************************************************************
#if defined (__USE_CMSIS)
extern void SystemInit(void);
#endif // (__USE_CMSIS)

//*****************************************************************************
// Forward declaration of the core exception handlers.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions.
// If your application is a C++ one, then any interrupt handlers defined
// in C++ files within in your main application will need to have C linkage
// rather than C++ linkage. To do this, make sure that you are using extern "C"
// { .... } around the interrupt handler within your main application code.
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void SPI0_IRQHandler(void);
WEAK void Reserved17_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void USART0_IRQHandler(void);
WEAK void USART1_IRQHandler(void);
WEAK void Reserved21_IRQHandler(void);
WEAK void Reserved22_IRQHandler(void);
WEAK void I2C1_IRQHandler(void);
WEAK void I2C0_IRQHandler(void);
WEAK void Reserved25_IRQHandler(void);
WEAK void MRT0_IRQHandler(void);
WEAK void CMP_CAPT_IRQHandler(void);
WEAK void WDT_IRQHandler(void);
WEAK void BOD_IRQHandler(void);
WEAK void FLASH_IRQHandler(void);
WEAK void WKT_IRQHandler(void);
WEAK void ADC_SEQA_IRQHandler(void);
WEAK void ADC_SEQB_IRQHandler(void);
WEAK void ADC_THCMP_IRQHandler(void);
WEAK void ADC_OVR_IRQHandler(void);
WEAK void Reserved36_IRQHandler(void);
WEAK void Reserved37_IRQHandler(void);
WEAK void Reserved38_IRQHandler(void);
WEAK void CTIMER0_IRQHandler(void);
WEAK void PIN_INT0_IRQHandler(void);
WEAK void PIN_INT1_IRQHandler(void);
WEAK void PIN_INT2_IRQHandler(void);
WEAK void PIN_INT3_IRQHandler(void);
WEAK void PIN_INT4_IRQHandler(void);
WEAK void PIN_INT5_IRQHandler(void);
WEAK void PIN_INT6_IRQHandler(void);
WEAK void PIN_INT7_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void SPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MRT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP_CAPT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WKT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_SEQA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_SEQB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_THCMP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_OVR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved36_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved38_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);

//*****************************************************************************
// External declaration for the pointer to the stack top from the Linker Script
//*****************************************************************************
extern void _vStackTop(void);
//*****************************************************************************
// External declaration for LPC MCU vector table checksum from  Linker Script
//*****************************************************************************
WEAK extern void __valid_user_code_checksum();

//*****************************************************************************
//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
// The vector table.
// This relies on the linker script to place at correct location in memory.
//*****************************************************************************



extern void (* const g_pfnVectors[])(void);
extern void * __Vectors __attribute__ ((alias ("g_pfnVectors")));

__attribute__ ((used, section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM0P
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    __valid_user_code_checksum,        // LPC MCU checksum
    0,                                 // ECRP
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    0,                                 // Reserved
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - LPC804
    SPI0_IRQHandler,         // 16: SPI0 interrupt
    Reserved17_IRQHandler,   // 17: Reserved interrupt
    DAC0_IRQHandler,         // 18: DAC0 interrupt
    USART0_IRQHandler,       // 19: USART0 interrupt
    USART1_IRQHandler,       // 20: USART1 interrupt
    Reserved21_IRQHandler,   // 21: Reserved interrupt
    Reserved22_IRQHandler,   // 22: Reserved interrupt
    I2C1_IRQHandler,         // 23: I2C1 interrupt
    I2C0_IRQHandler,         // 24: I2C0 interrupt
    Reserved25_IRQHandler,   // 25: Reserved interrupt
    MRT0_IRQHandler,         // 26: Multi-rate timer interrupt
    CMP_CAPT_IRQHandler,     // 27: Analog comparator interrupt or Capacitive Touch interrupt
    WDT_IRQHandler,          // 28: Windowed watchdog timer interrupt
    BOD_IRQHandler,          // 29: BOD interrupts
    FLASH_IRQHandler,        // 30: flash interrupt
    WKT_IRQHandler,          // 31: Self-wake-up timer interrupt
    ADC_SEQA_IRQHandler,     // 32: ADC sequence A completion.
    ADC_SEQB_IRQHandler,     // 33: ADC sequence B completion.
    ADC_THCMP_IRQHandler,    // 34: ADC threshold compare and error.
    ADC_OVR_IRQHandler,      // 35: ADC overrun
    Reserved36_IRQHandler,   // 36: Reserved interrupt
    Reserved37_IRQHandler,   // 37: Reserved interrupt
    Reserved38_IRQHandler,   // 38: Reserved interrupt
    CTIMER0_IRQHandler,      // 39: Timer interrupt
    PIN_INT0_IRQHandler,     // 40: Pin interrupt 0 or pattern match engine slice 0 interrupt
    PIN_INT1_IRQHandler,     // 41: Pin interrupt 1 or pattern match engine slice 1 interrupt
    PIN_INT2_IRQHandler,     // 42: Pin interrupt 2 or pattern match engine slice 2 interrupt
    PIN_INT3_IRQHandler,     // 43: Pin interrupt 3 or pattern match engine slice 3 interrupt
    PIN_INT4_IRQHandler,     // 44: Pin interrupt 4 or pattern match engine slice 4 interrupt
    PIN_INT5_IRQHandler,     // 45: Pin interrupt 5 or pattern match engine slice 5 interrupt
    PIN_INT6_IRQHandler,     // 46: Pin interrupt 6 or pattern match engine slice 6 interrupt
    PIN_INT7_IRQHandler,     // 47: Pin interrupt 7 or pattern match engine slice 7 interrupt


}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
//__attribute__ ((section(".after_vectors.init_data")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

//__attribute__ ((section(".after_vectors.init_bss")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
//__attribute__ ((naked, section(".after_vectors.reset")))
__attribute__ ((naked))
void ResetISR(void) {

    // Disable interrupts
    __asm volatile ("cpsid i");


    // Enable SRAM clock used by Stack
    __asm volatile ("LDR R0, =0x40000220\n\t"
                    "MOV R1, #56\n\t"
                    "STR R1, [R0]");

#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();

#endif // (__USE_CMSIS)

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }

    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }


#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will setup the VTOR register

    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }
#endif // (__USE_CMSIS)
#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

    // Reenable interrupts
    __asm volatile ("cpsie i");

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main();
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default core exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
WEAK_AV void NMI_Handler(void)
{ while(1) {}
}

WEAK_AV void HardFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SVC_Handler(void)
{ while(1) {}
}

WEAK_AV void PendSV_Handler(void)
{ while(1) {}
}

WEAK_AV void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//*****************************************************************************
WEAK_AV void IntDefaultHandler(void)
{ while(1) {}
}

//*****************************************************************************
// Default application exception handlers. Override the ones here by defining
// your own handler routines in your application code. These routines call
// driver exception handlers or IntDefaultHandler() if no driver exception
// handler is included.
//*****************************************************************************
WEAK_AV void SPI0_IRQHandler(void)
{   SPI0_DriverIRQHandler();
}

WEAK_AV void Reserved17_IRQHandler(void)
{   Reserved17_DriverIRQHandler();
}

WEAK_AV void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK_AV void USART0_IRQHandler(void)
{   USART0_DriverIRQHandler();
}

WEAK_AV void USART1_IRQHandler(void)
{   USART1_DriverIRQHandler();
}

WEAK_AV void Reserved21_IRQHandler(void)
{   Reserved21_DriverIRQHandler();
}

WEAK_AV void Reserved22_IRQHandler(void)
{   Reserved22_DriverIRQHandler();
}

WEAK_AV void I2C1_IRQHandler(void)
{   I2C1_DriverIRQHandler();
}

WEAK_AV void I2C0_IRQHandler(void)
{   I2C0_DriverIRQHandler();
}

WEAK_AV void Reserved25_IRQHandler(void)
{   Reserved25_DriverIRQHandler();
}

WEAK_AV void MRT0_IRQHandler(void)
{   MRT0_DriverIRQHandler();
}

WEAK_AV void CMP_CAPT_IRQHandler(void)
{   CMP_CAPT_DriverIRQHandler();
}

WEAK_AV void WDT_IRQHandler(void)
{   WDT_DriverIRQHandler();
}

WEAK_AV void BOD_IRQHandler(void)
{   BOD_DriverIRQHandler();
}

WEAK_AV void FLASH_IRQHandler(void)
{   FLASH_DriverIRQHandler();
}

WEAK_AV void WKT_IRQHandler(void)
{   WKT_DriverIRQHandler();
}

WEAK_AV void ADC_SEQA_IRQHandler(void)
{   ADC_SEQA_DriverIRQHandler();
}

WEAK_AV void ADC_SEQB_IRQHandler(void)
{   ADC_SEQB_DriverIRQHandler();
}

WEAK_AV void ADC_THCMP_IRQHandler(void)
{   ADC_THCMP_DriverIRQHandler();
}

WEAK_AV void ADC_OVR_IRQHandler(void)
{   ADC_OVR_DriverIRQHandler();
}

WEAK_AV void Reserved36_IRQHandler(void)
{   Reserved36_DriverIRQHandler();
}

WEAK_AV void Reserved37_IRQHandler(void)
{   Reserved37_DriverIRQHandler();
}

WEAK_AV void Reserved38_IRQHandler(void)
{   Reserved38_DriverIRQHandler();
}

WEAK_AV void CTIMER0_IRQHandler(void)
{   CTIMER0_DriverIRQHandler();
}

WEAK_AV void PIN_INT0_IRQHandler(void)
{   PIN_INT0_DriverIRQHandler();
}

WEAK_AV void PIN_INT1_IRQHandler(void)
{   PIN_INT1_DriverIRQHandler();
}

WEAK_AV void PIN_INT2_IRQHandler(void)
{   PIN_INT2_DriverIRQHandler();
}

WEAK_AV void PIN_INT3_IRQHandler(void)
{   PIN_INT3_DriverIRQHandler();
}

WEAK_AV void PIN_INT4_IRQHandler(void)
{   PIN_INT4_DriverIRQHandler();
}

WEAK_AV void PIN_INT5_IRQHandler(void)
{   PIN_INT5_DriverIRQHandler();
}

WEAK_AV void PIN_INT6_IRQHandler(void)
{   PIN_INT6_DriverIRQHandler();
}

WEAK_AV void PIN_INT7_IRQHandler(void)
{   PIN_INT7_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
