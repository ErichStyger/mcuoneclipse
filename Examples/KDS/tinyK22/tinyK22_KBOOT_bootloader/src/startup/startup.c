/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include "fsl_device_registers.h"
#include "bootloader_core.h"

#if (defined(__ICCARM__))
#pragma section = ".intvec"
#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam"
#pragma section = "USBGlobal"
#endif

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : init_data_bss
 * Description   : Make necessary initializations for RAM.
 * - Copy initialized data from ROM to RAM.
 * - Clear the zero-initialized data section.
 * - Copy the vector table from ROM to RAM. This could be an option.
 *
 * Tool Chians:
 *   __GNUC__   : GCC
 *   __CC_ARM   : KEIL
 *   __ICCARM__ : IAR
 *
 *END**************************************************************************/
void init_data_bss(void)
{
/* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
#if defined(__CC_ARM)
    extern uint32_t Image$$VECTOR_ROM$$Base[];
    extern uint32_t Image$$VECTOR_RAM$$Base[];
    extern uint32_t Image$$RW_m_data$$Base[];

#define __VECTOR_TABLE Image$$VECTOR_ROM$$Base
#define __VECTOR_RAM Image$$VECTOR_RAM$$Base
#define __RAM_VECTOR_TABLE_SIZE (((uint32_t)Image$$RW_m_data$$Base - (uint32_t)Image$$VECTOR_RAM$$Base))
#elif defined(__ICCARM__)
    extern uint32_t __RAM_VECTOR_TABLE_SIZE[];
    extern uint32_t __VECTOR_TABLE[];
    extern uint32_t __VECTOR_RAM[];
#elif defined(__GNUC__)
    extern uint32_t __VECTOR_TABLE[];
#endif

#if (defined(__ICCARM__))
    SCB->VTOR = (uint32_t)__section_begin(".intvec");
#else
    SCB->VTOR = (uint32_t)__VECTOR_TABLE;
#endif

#if !defined(__CC_ARM)

    /* Declare pointers for various data sections. These pointers
     * are initialized using values pulled in from the linker file */
    uint8_t *data_ram, *data_rom, *data_rom_end;
    uint8_t *bss_start, *bss_end;
    uint32_t n;

// Get the addresses for the .data section (initialized data section)
#if defined(__GNUC__)
    extern uint32_t __DATA_ROM[];
    extern uint32_t __DATA_RAM[];
    extern char __DATA_END[];
    data_ram = (uint8_t *)__DATA_RAM;
    data_rom = (uint8_t *)__DATA_ROM;
    data_rom_end = (uint8_t *)__DATA_END; // This is actually a RAM address in CodeWarrior
    n = data_rom_end - data_rom;
#elif(defined(__ICCARM__))
    data_ram = __section_begin(".data");
    data_rom = __section_begin(".data_init");
    data_rom_end = __section_end(".data_init");
    n = data_rom_end - data_rom;
#endif

    if (data_ram != data_rom)
    {
        // Copy initialized data from ROM to RAM
        while (n)
        {
            *data_ram++ = *data_rom++;
            n--;
        }
    }

// Get the addresses for the .bss section (zero-initialized data)
#if defined(__GNUC__)
    extern char __START_BSS[];
    extern char __END_BSS[];
    bss_start = (uint8_t *)__START_BSS;
    bss_end = (uint8_t *)__END_BSS;
#elif(defined(__ICCARM__))
    bss_start = __section_begin(".bss");
    bss_end = __section_end(".bss");
#endif

    // Clear the zero-initialized data section
    n = bss_end - bss_start;
    while (n)
    {
        *bss_start++ = 0;
        n--;
    }

#if defined(USB_STACK_BM)
// Get the addresses for the USBGlobal section (zero-initialized data)
#if (defined(__ICCARM__))
    uint8_t *usbGlobal_start = __section_begin("USBGlobal");
    uint8_t *usbGlobal_end = __section_end("USBGlobal");
#elif(defined(__GNUC__))
    extern uint8_t __START_USBGLOBAL[];
    extern uint8_t __END_USBGLOBAL[];
    uint8_t *usbGlobal_start = (uint8_t *)__START_USBGLOBAL;
    uint8_t *usbGlobal_end = (uint8_t *)__END_USBGLOBAL;
#endif

    // Clear the zero-initialized data section
    n = usbGlobal_end - usbGlobal_start;
    while (n)
    {
        *usbGlobal_start++ = 0;
        n--;
    }
#endif // #if defined(USB_STACK_BM)

/* Get addresses for any code sections that need to be copied from ROM to RAM.
 * The IAR tools have a predefined keyword that can be used to mark individual
 * functions for execution from RAM. Add "__ramfunc" before the return type in
 * the function prototype for any routines you need to execute from RAM instead
 * of ROM. ex: __ramfunc void foo(void);
 */
#if (defined(__ICCARM__))
    uint8_t *code_relocate_ram = __section_begin("CodeRelocateRam");
    uint8_t *code_relocate = __section_begin("CodeRelocate");
    uint8_t *code_relocate_end = __section_end("CodeRelocate");

    // Copy functions from ROM to RAM
    n = code_relocate_end - code_relocate;
    while (n)
    {
        *code_relocate_ram++ = *code_relocate++;
        n--;
    }
#endif
#endif /* !__CC_ARM && !__ICCARM__*/
}

void init_interrupts(void)
{
    // Clear any IRQs that may be enabled, we only want the IRQs we enable to be active
    NVIC_ClearEnabledIRQs();

    // Clear any pending IRQs that may have been set
    NVIC_ClearAllPendingIRQs();
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
