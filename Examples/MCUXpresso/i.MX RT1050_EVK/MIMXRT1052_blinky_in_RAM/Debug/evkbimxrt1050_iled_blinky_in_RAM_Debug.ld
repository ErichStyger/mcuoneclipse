/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008 - 2013 Code Red Technologies Ltd, 
 * Copyright 2015, 2018 NXP
 * (c) NXP Semiconductors 2013-2019
 * Generated linker script file for MIMXRT1052xxxxB
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.3.0 [Build 2200] [2018-12-03] on Jan 22, 2019 9:03:48 PM
 */

INCLUDE "evkbimxrt1050_iled_blinky_in_RAM_Debug_library.ld"
INCLUDE "evkbimxrt1050_iled_blinky_in_RAM_Debug_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
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
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        LONG(LOADADDR(.data_RAM5));
        LONG(    ADDR(.data_RAM5));
        LONG(  SIZEOF(.data_RAM5));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        LONG(    ADDR(.bss_RAM5));
        LONG(  SIZEOF(.bss_RAM5));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } > SRAM_ITC

    .text : ALIGN(4)
    {
       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > SRAM_ITC
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this. 
     */
    .ARM.extab : ALIGN(4) 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM_ITC

    __exidx_start = .;

    .ARM.exidx : ALIGN(4)
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SRAM_ITC
    __exidx_end = .;
 
    _etext = .;
        
    /* DATA section for SRAM_DTC */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$SRAM_DTC)
       *(NonCacheable.init)
       *(.isr_vectorRitschi)
        *(.data.$RAM2*)
        *(.data.$SRAM_DTC*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
     } > SRAM_DTC AT>SRAM_ITC
    /* DATA section for SRAM_OC */

    .data_RAM3 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$SRAM_OC)
        *(.data.$RAM3*)
        *(.data.$SRAM_OC*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM3 = .) ;
     } > SRAM_OC AT>SRAM_ITC
    /* DATA section for BOARD_SDRAM */

    .data_RAM4 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$BOARD_SDRAM)
        *(.data.$RAM4*)
        *(.data.$BOARD_SDRAM*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM4 = .) ;
     } > BOARD_SDRAM AT>SRAM_ITC
    /* DATA section for SRAM_ITC_reserved */

    .data_RAM5 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM5 = .) ;
        *(.ramfunc.$RAM5)
        *(.ramfunc.$SRAM_ITC_reserved)
        *(.data.$RAM5*)
        *(.data.$SRAM_ITC_reserved*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM5 = .) ;
     } > SRAM_ITC_reserved AT>SRAM_ITC
    /* MAIN DATA SECTION */
    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > SRAM_ITC

    /* Main DATA section (SRAM_ITC) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       *(vtable)
       *(.ramfunc*)
       *(.data*)
       . = ALIGN(4) ;
       _edata = . ;
    } > SRAM_ITC AT>SRAM_ITC

    /* BSS section for SRAM_DTC */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       *(NonCacheable)
       *(.bss.*)
       *(.bss.$RAM2*)
       *(.bss.$SRAM_DTC*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
    } > SRAM_DTC 

    /* BSS section for SRAM_OC */
    .bss_RAM3 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       *(.bss.$RAM3*)
       *(.bss.$SRAM_OC*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
    } > SRAM_OC 

    /* BSS section for BOARD_SDRAM */
    .bss_RAM4 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       *(.bss.$RAM4*)
       *(.bss.$BOARD_SDRAM*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
    } > BOARD_SDRAM 

    /* BSS section for SRAM_ITC_reserved */
    .bss_RAM5 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM5 = .) ;
       *(.bss.$RAM5*)
       *(.bss.$SRAM_ITC_reserved*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM5 = .) ;
    } > SRAM_ITC_reserved 

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > SRAM_ITC

    /* NOINIT section for SRAM_DTC */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM2*)
       *(.noinit.$SRAM_DTC*)
       . = ALIGN(4) ;
    } > SRAM_DTC 

    /* NOINIT section for SRAM_OC */
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM3*)
       *(.noinit.$SRAM_OC*)
       . = ALIGN(4) ;
    } > SRAM_OC 

    /* NOINIT section for BOARD_SDRAM */
    .noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM4*)
       *(.noinit.$BOARD_SDRAM*)
       . = ALIGN(4) ;
    } > BOARD_SDRAM 

    /* NOINIT section for SRAM_ITC_reserved */
    .noinit_RAM5 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM5*)
       *(.noinit.$SRAM_ITC_reserved*)
       . = ALIGN(4) ;
    } > SRAM_ITC_reserved 

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*) 
         . = ALIGN(4) ;
        _end_noinit = .;
    } > SRAM_ITC

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x1000;
    .heap :  ALIGN(4)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(4);
        _pvHeapLimit = .;
    } > SRAM_DTC

     _StackSize = 0x1000;
     /* Reserve space in memory for Stack */
    .heap2stackfill  :
    {
        . += _StackSize;
    } > SRAM_DTC
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM_DTC) + LENGTH(SRAM_DTC) - _StackSize - 0:  ALIGN(4)
    {
        _vStackBase = .;
        . = ALIGN(4);
        _vStackTop = . + _StackSize;
    } > SRAM_DTC

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}