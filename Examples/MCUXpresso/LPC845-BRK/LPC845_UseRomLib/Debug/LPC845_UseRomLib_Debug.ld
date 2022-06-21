
INCLUDE "LPC845_UseRomLib_Debug_library.ld"
INCLUDE "LPC845_UseRomLib_Debug_memory.ld"

TARGET(binary) /* specify the file format of binary file */
INPUT ("../../LPC845_RomLib/Debug/LPC845_RomLib.bin") /* include the file */
OUTPUT_FORMAT(default) /* restore the out file format */

ENTRY(ResetISR)

SECTIONS
{

    .text 0xF000 : { /* as a convenience: include the ROM library as BLOB it the build */
      "../../LPC845_RomLib/Debug/LPC845_RomLib.bin"
    }
    
     /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > PROGRAM_FLASH
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > PROGRAM_FLASH

    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > PROGRAM_FLASH
 
    _etext = .;
        
    /* possible MTB section for IAP_SRAM */
    .mtb_buffer_RAM2 (NOLOAD) :
    {
        KEEP(*(.mtb.$RAM2*))
        KEEP(*(.mtb.$IAP_SRAM*))
    } > IAP_SRAM

    /* DATA section for IAP_SRAM */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_IAP_SRAM = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$IAP_SRAM)
        *(.data.$RAM2)
        *(.data.$IAP_SRAM)
        *(.data.$RAM2.*)
        *(.data.$IAP_SRAM.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_IAP_SRAM = .) ;
     } > IAP_SRAM AT>PROGRAM_FLASH

    /* MAIN DATA SECTION */
    /* Default MTB section */
    .mtb_buffer_default (NOLOAD) :
    {
        KEEP(*(.mtb*))
    } > SRAM AT > SRAM
    .uninit_RESERVED (NOLOAD) : ALIGN(4)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > SRAM AT> SRAM

    /* Main DATA section (SRAM) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(.data*)
       . = ALIGN(4) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM = .) ;
    } > SRAM AT>PROGRAM_FLASH

    /* BSS section for IAP_SRAM */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_IAP_SRAM = .) ;
       *(.bss.$RAM2)
       *(.bss.$IAP_SRAM)
       *(.bss.$RAM2.*)
       *(.bss.$IAP_SRAM.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_IAP_SRAM = .) ;
    } > IAP_SRAM AT> IAP_SRAM

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM = .) ;
        PROVIDE(end = .);
    } > SRAM AT> SRAM

    /* NOINIT section for IAP_SRAM */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_IAP_SRAM = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$IAP_SRAM)
       *(.noinit.$RAM2.*)
       *(.noinit.$IAP_SRAM.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_IAP_SRAM = .) ;
    } > IAP_SRAM AT> IAP_SRAM

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM = .) ;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM = .) ;        
    } > SRAM AT> SRAM

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x3f8;
    .heap :  ALIGN(4)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(4);
        _pvHeapLimit = .;
    } > SRAM

     _StackSize = 0x3f8;
     /* Reserve space in memory for Stack */
    .heap2stackfill  :
    {
        . += _StackSize;
    } > SRAM
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM) + LENGTH(SRAM) - _StackSize - 0:  ALIGN(4)
    {
        _vStackBase = .;
        . = ALIGN(4);
        _vStackTop = . + _StackSize;
    } > SRAM

    /* ## Create checksum value (used in startup) ## */
    PROVIDE(__valid_user_code_checksum = 0 - 
                                         (_vStackTop 
                                         + (ResetISR + 1) 
                                         + (( DEFINED(NMI_Handler) ? NMI_Handler : M0_NMI_Handler ) + 1) 
                                         + (( DEFINED(HardFault_Handler) ? HardFault_Handler : M0_HardFault_Handler ) + 1) 
                                         )
           );

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}