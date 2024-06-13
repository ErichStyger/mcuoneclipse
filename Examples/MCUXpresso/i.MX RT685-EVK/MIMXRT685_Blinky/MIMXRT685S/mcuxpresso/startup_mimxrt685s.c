//*****************************************************************************
// MIMXRT685S_cm33 startup code for use with MCUXpresso IDE
//
// Version : 101121
//*****************************************************************************
//
// Copyright 2016-2021 NXP
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
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SecureFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void WDT0_IRQHandler(void);
WEAK void DMA0_IRQHandler(void);
WEAK void GPIO_INTA_IRQHandler(void);
WEAK void GPIO_INTB_IRQHandler(void);
WEAK void PIN_INT0_IRQHandler(void);
WEAK void PIN_INT1_IRQHandler(void);
WEAK void PIN_INT2_IRQHandler(void);
WEAK void PIN_INT3_IRQHandler(void);
WEAK void UTICK0_IRQHandler(void);
WEAK void MRT0_IRQHandler(void);
WEAK void CTIMER0_IRQHandler(void);
WEAK void CTIMER1_IRQHandler(void);
WEAK void SCT0_IRQHandler(void);
WEAK void CTIMER3_IRQHandler(void);
WEAK void FLEXCOMM0_IRQHandler(void);
WEAK void FLEXCOMM1_IRQHandler(void);
WEAK void FLEXCOMM2_IRQHandler(void);
WEAK void FLEXCOMM3_IRQHandler(void);
WEAK void FLEXCOMM4_IRQHandler(void);
WEAK void FLEXCOMM5_IRQHandler(void);
WEAK void FLEXCOMM14_IRQHandler(void);
WEAK void FLEXCOMM15_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void ACMP_IRQHandler(void);
WEAK void DMIC0_IRQHandler(void);
WEAK void Reserved42_IRQHandler(void);
WEAK void HYPERVISOR_IRQHandler(void);
WEAK void SECUREVIOLATION_IRQHandler(void);
WEAK void HWVAD0_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void RNG_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void DSPWAKE_IRQHandler(void);
WEAK void MU_A_IRQHandler(void);
WEAK void PIN_INT4_IRQHandler(void);
WEAK void PIN_INT5_IRQHandler(void);
WEAK void PIN_INT6_IRQHandler(void);
WEAK void PIN_INT7_IRQHandler(void);
WEAK void CTIMER2_IRQHandler(void);
WEAK void CTIMER4_IRQHandler(void);
WEAK void OS_EVENT_IRQHandler(void);
WEAK void FLEXSPI_IRQHandler(void);
WEAK void FLEXCOMM6_IRQHandler(void);
WEAK void FLEXCOMM7_IRQHandler(void);
WEAK void USDHC0_IRQHandler(void);
WEAK void USDHC1_IRQHandler(void);
WEAK void SGPIO_INTA_IRQHandler(void);
WEAK void SGPIO_INTB_IRQHandler(void);
WEAK void I3C0_IRQHandler(void);
WEAK void USB_IRQHandler(void);
WEAK void USB_WAKEUP_IRQHandler(void);
WEAK void WDT1_IRQHandler(void);
WEAK void USBPHY_DCD_IRQHandler(void);
WEAK void DMA1_IRQHandler(void);
WEAK void PUF_IRQHandler(void);
WEAK void POWERQUAD_IRQHandler(void);
WEAK void CASPER_IRQHandler(void);
WEAK void PMC_PMIC_IRQHandler(void);
WEAK void HASHCRYPT_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void WDT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_INTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_INTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UTICK0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MRT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM14_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMIC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved42_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HYPERVISOR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SECUREVIOLATION_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HWVAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DSPWAKE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MU_A_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OS_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SGPIO_INTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SGPIO_INTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I3C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_WAKEUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY_DCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PUF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void POWERQUAD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CASPER_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PMC_PMIC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HASHCRYPT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
extern void _image_size(void);
//*****************************************************************************
// External declaration for the pointer to the stack base from the Linker Script
//*****************************************************************************
extern void _vStackBase(void);
//*****************************************************************************
// External declaration for image type and load address from  Linker Script
//*****************************************************************************
WEAK extern void __imghdr_loadaddress();
WEAK extern void __imghdr_imagetype();

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
    // Core Level - CM33
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    SecureFault_Handler,               // The secure fault handler
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
    (void (*)())0x180000,                // Image length
#else
    (void (*)())((unsigned)_image_size), // Image length
#endif
    __imghdr_imagetype,                // Image type
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    (void (*)())g_pfnVectors,              // Image load address
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - MIMXRT685S_cm33
    WDT0_IRQHandler,             // 16: Windowed watchdog timer 0 (CM33 watchdog)
    DMA0_IRQHandler,             // 17: DMA controller 0 (secure or CM33 DMA)
    GPIO_INTA_IRQHandler,        // 18: GPIO interrupt A
    GPIO_INTB_IRQHandler,        // 19: GPIO interrupt B
    PIN_INT0_IRQHandler,         // 20: Pin interrupt 0 or pattern match engine slice 0 int
    PIN_INT1_IRQHandler,         // 21: Pin interrupt 1 or pattern match engine slice 1 int
    PIN_INT2_IRQHandler,         // 22: Pin interrupt 2 or pattern match engine slice 2 int
    PIN_INT3_IRQHandler,         // 23: Pin interrupt 3 or pattern match engine slice 3 int
    UTICK0_IRQHandler,           // 24: Micro-tick Timer
    MRT0_IRQHandler,             // 25: Multi-Rate Timer
    CTIMER0_IRQHandler,          // 26: Standard counter/timer CTIMER0
    CTIMER1_IRQHandler,          // 27: Standard counter/timer CTIMER1
    SCT0_IRQHandler,             // 28: SCTimer/PWM
    CTIMER3_IRQHandler,          // 29: Standard counter/timer CTIMER3
    FLEXCOMM0_IRQHandler,        // 30: Flexcomm Interface 0 (USART, SPI, I2C, I2S)
    FLEXCOMM1_IRQHandler,        // 31: Flexcomm Interface 1 (USART, SPI, I2C, I2S)
    FLEXCOMM2_IRQHandler,        // 32: Flexcomm Interface 2 (USART, SPI, I2C, I2S)
    FLEXCOMM3_IRQHandler,        // 33: Flexcomm Interface 3 (USART, SPI, I2C, I2S)
    FLEXCOMM4_IRQHandler,        // 34: Flexcomm Interface 4 (USART, SPI, I2C, I2S)
    FLEXCOMM5_IRQHandler,        // 35: Flexcomm Interface 5 (USART, SPI, I2C, I2S)
    FLEXCOMM14_IRQHandler,       // 36: Flexcomm Interface 14 (SPI only)
    FLEXCOMM15_IRQHandler,       // 37: Flexcomm Interface 15 (I2C only)
    ADC0_IRQHandler,             // 38: ADC0
    Reserved39_IRQHandler,       // 39: Reserved interrupt
    ACMP_IRQHandler,             // 40: Analog comparator
    DMIC0_IRQHandler,            // 41: Digital microphone and DMIC subsystem
    Reserved42_IRQHandler,       // 42: Reserved interrupt
    HYPERVISOR_IRQHandler,       // 43: Hypervisor
    SECUREVIOLATION_IRQHandler,  // 44: Secure violation
    HWVAD0_IRQHandler,           // 45: Hardware Voice Activity Detector
    Reserved46_IRQHandler,       // 46: Reserved interrupt
    RNG_IRQHandler,              // 47: Random number Generator
    RTC_IRQHandler,              // 48: RTC alarm and wake-up
    DSPWAKE_IRQHandler,          // 49: Wake-up from DSP
    MU_A_IRQHandler,             // 50: Messaging Unit port A for CM33
    PIN_INT4_IRQHandler,         // 51: Pin interrupt 4 or pattern match engine slice 4 int
    PIN_INT5_IRQHandler,         // 52: Pin interrupt 5 or pattern match engine slice 5 int
    PIN_INT6_IRQHandler,         // 53: Pin interrupt 6 or pattern match engine slice 6 int
    PIN_INT7_IRQHandler,         // 54: Pin interrupt 7 or pattern match engine slice 7 int
    CTIMER2_IRQHandler,          // 55: Standard counter/timer CTIMER2
    CTIMER4_IRQHandler,          // 56: Standard counter/timer CTIMER4
    OS_EVENT_IRQHandler,         // 57: OS event timer
    FLEXSPI_IRQHandler,          // 58: FLEXSPI interface
    FLEXCOMM6_IRQHandler,        // 59: Flexcomm Interface 6 (USART, SPI, I2C, I2S)
    FLEXCOMM7_IRQHandler,        // 60: Flexcomm Interface 7 (USART, SPI, I2C, I2S)
    USDHC0_IRQHandler,           // 61: USDHC0 (Enhanced SDHC) interrupt request
    USDHC1_IRQHandler,           // 62: USDHC1 (Enhanced SDHC) interrupt request
    SGPIO_INTA_IRQHandler,       // 63: Secure GPIO interrupt A
    SGPIO_INTB_IRQHandler,       // 64: Secure GPIO interrupt B
    I3C0_IRQHandler,             // 65: I3C interface 0
    USB_IRQHandler,              // 66: High-speed USB device/host
    USB_WAKEUP_IRQHandler,       // 67: USB Activity Wake-up Interrupt
    WDT1_IRQHandler,             // 68: Windowed watchdog timer 1 (HiFi 4 watchdog)
    USBPHY_DCD_IRQHandler,       // 69: USBPHY DCD
    DMA1_IRQHandler,             // 70: DMA controller 1 (non-secure or HiFi 4 DMA)
    PUF_IRQHandler,              // 71: Physical Unclonable Function
    POWERQUAD_IRQHandler,        // 72: PowerQuad math coprocessor
    CASPER_IRQHandler,           // 73: Casper cryptographic coprocessor
    PMC_PMIC_IRQHandler,         // 74: Power management IC
    HASHCRYPT_IRQHandler,        // 75: Hash-AES unit
}; /* End of g_pfnVectors */

#if defined(ENABLE_RAM_VECTOR_TABLE)
extern void * __VECTOR_TABLE __attribute__ ((alias ("g_pfnVectors")));
void (* __VECTOR_RAM[sizeof(g_pfnVectors) / 4])(void) __attribute__((aligned(128)));
unsigned int __RAM_VECTOR_TABLE_SIZE_BYTES = sizeof(g_pfnVectors);
#endif

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors.init_data")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors.init_bss")))
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
__attribute__ ((naked, section(".after_vectors.reset")))
void ResetISR(void) {
    // Disable interrupts
    __asm volatile ("cpsid i");
    // Config VTOR & MSPLIM register
    __asm volatile ("LDR R0, =0xE000ED08  \n"
                    "STR %0, [R0]         \n"
                    "LDR R1, [%0]         \n"
                    "MSR MSP, R1          \n"
                    "MSR MSPLIM, %1       \n"
                    :
                    : "r"(g_pfnVectors), "r"(_vStackBase)
                    : "r0", "r1");

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

WEAK_AV void MemManage_Handler(void)
{ while(1) {}
}

WEAK_AV void BusFault_Handler(void)
{ while(1) {}
}

WEAK_AV void UsageFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SecureFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SVC_Handler(void)
{ while(1) {}
}

WEAK_AV void DebugMon_Handler(void)
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
WEAK void WDT0_IRQHandler(void)
{   WDT0_DriverIRQHandler();
}

WEAK void DMA0_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void GPIO_INTA_IRQHandler(void)
{   GPIO_INTA_DriverIRQHandler();
}

WEAK void GPIO_INTB_IRQHandler(void)
{   GPIO_INTB_DriverIRQHandler();
}

WEAK void PIN_INT0_IRQHandler(void)
{   PIN_INT0_DriverIRQHandler();
}

WEAK void PIN_INT1_IRQHandler(void)
{   PIN_INT1_DriverIRQHandler();
}

WEAK void PIN_INT2_IRQHandler(void)
{   PIN_INT2_DriverIRQHandler();
}

WEAK void PIN_INT3_IRQHandler(void)
{   PIN_INT3_DriverIRQHandler();
}

WEAK void UTICK0_IRQHandler(void)
{   UTICK0_DriverIRQHandler();
}

WEAK void MRT0_IRQHandler(void)
{   MRT0_DriverIRQHandler();
}

WEAK void CTIMER0_IRQHandler(void)
{   CTIMER0_DriverIRQHandler();
}

WEAK void CTIMER1_IRQHandler(void)
{   CTIMER1_DriverIRQHandler();
}

WEAK void SCT0_IRQHandler(void)
{   SCT0_DriverIRQHandler();
}

WEAK void CTIMER3_IRQHandler(void)
{   CTIMER3_DriverIRQHandler();
}

WEAK void FLEXCOMM0_IRQHandler(void)
{   FLEXCOMM0_DriverIRQHandler();
}

WEAK void FLEXCOMM1_IRQHandler(void)
{   FLEXCOMM1_DriverIRQHandler();
}

WEAK void FLEXCOMM2_IRQHandler(void)
{   FLEXCOMM2_DriverIRQHandler();
}

WEAK void FLEXCOMM3_IRQHandler(void)
{   FLEXCOMM3_DriverIRQHandler();
}

WEAK void FLEXCOMM4_IRQHandler(void)
{   FLEXCOMM4_DriverIRQHandler();
}

WEAK void FLEXCOMM5_IRQHandler(void)
{   FLEXCOMM5_DriverIRQHandler();
}

WEAK void FLEXCOMM14_IRQHandler(void)
{   FLEXCOMM14_DriverIRQHandler();
}

WEAK void FLEXCOMM15_IRQHandler(void)
{   FLEXCOMM15_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void Reserved39_IRQHandler(void)
{   Reserved39_DriverIRQHandler();
}

WEAK void ACMP_IRQHandler(void)
{   ACMP_DriverIRQHandler();
}

WEAK void DMIC0_IRQHandler(void)
{   DMIC0_DriverIRQHandler();
}

WEAK void Reserved42_IRQHandler(void)
{   Reserved42_DriverIRQHandler();
}

WEAK void HYPERVISOR_IRQHandler(void)
{   HYPERVISOR_DriverIRQHandler();
}

WEAK void SECUREVIOLATION_IRQHandler(void)
{   SECUREVIOLATION_DriverIRQHandler();
}

WEAK void HWVAD0_IRQHandler(void)
{   HWVAD0_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void RNG_IRQHandler(void)
{   RNG_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void DSPWAKE_IRQHandler(void)
{   DSPWAKE_DriverIRQHandler();
}

WEAK void MU_A_IRQHandler(void)
{   MU_A_DriverIRQHandler();
}

WEAK void PIN_INT4_IRQHandler(void)
{   PIN_INT4_DriverIRQHandler();
}

WEAK void PIN_INT5_IRQHandler(void)
{   PIN_INT5_DriverIRQHandler();
}

WEAK void PIN_INT6_IRQHandler(void)
{   PIN_INT6_DriverIRQHandler();
}

WEAK void PIN_INT7_IRQHandler(void)
{   PIN_INT7_DriverIRQHandler();
}

WEAK void CTIMER2_IRQHandler(void)
{   CTIMER2_DriverIRQHandler();
}

WEAK void CTIMER4_IRQHandler(void)
{   CTIMER4_DriverIRQHandler();
}

WEAK void OS_EVENT_IRQHandler(void)
{   OS_EVENT_DriverIRQHandler();
}

WEAK void FLEXSPI_IRQHandler(void)
{   FLEXSPI_DriverIRQHandler();
}

WEAK void FLEXCOMM6_IRQHandler(void)
{   FLEXCOMM6_DriverIRQHandler();
}

WEAK void FLEXCOMM7_IRQHandler(void)
{   FLEXCOMM7_DriverIRQHandler();
}

WEAK void USDHC0_IRQHandler(void)
{   USDHC0_DriverIRQHandler();
}

WEAK void USDHC1_IRQHandler(void)
{   USDHC1_DriverIRQHandler();
}

WEAK void SGPIO_INTA_IRQHandler(void)
{   SGPIO_INTA_DriverIRQHandler();
}

WEAK void SGPIO_INTB_IRQHandler(void)
{   SGPIO_INTB_DriverIRQHandler();
}

WEAK void I3C0_IRQHandler(void)
{   I3C0_DriverIRQHandler();
}

WEAK void USB_IRQHandler(void)
{   USB_DriverIRQHandler();
}

WEAK void USB_WAKEUP_IRQHandler(void)
{   USB_WAKEUP_DriverIRQHandler();
}

WEAK void WDT1_IRQHandler(void)
{   WDT1_DriverIRQHandler();
}

WEAK void USBPHY_DCD_IRQHandler(void)
{   USBPHY_DCD_DriverIRQHandler();
}

WEAK void DMA1_IRQHandler(void)
{   DMA1_DriverIRQHandler();
}

WEAK void PUF_IRQHandler(void)
{   PUF_DriverIRQHandler();
}

WEAK void POWERQUAD_IRQHandler(void)
{   POWERQUAD_DriverIRQHandler();
}

WEAK void CASPER_IRQHandler(void)
{   CASPER_DriverIRQHandler();
}

WEAK void PMC_PMIC_IRQHandler(void)
{   PMC_PMIC_DriverIRQHandler();
}

WEAK void HASHCRYPT_IRQHandler(void)
{   HASHCRYPT_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
