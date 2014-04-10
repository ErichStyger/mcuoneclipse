/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
    rom (rx)     : ORIGIN = 0x00000000, LENGTH = 0x00100000
    vectram (rwx): ORIGIN = 0x1FFF0000, LENGTH = 0x00000410
    ram (rw)     : ORIGIN = 0x1FFF0410, LENGTH = 0x20030000 - 0x1FFF0410
}

/* Define output sections */
SECTIONS
{
    /* The startup code goes first into rom */
    __VECTOR_RAM = ORIGIN(vectram);

    /* The program code and other data goes into rom */
    .text :
    {
        __VECTOR_TABLE = .;
        KEEP(*(.isr_vector))
        _stext_ = .;

        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
         *crtbegin.o(.dtors)
         *crtbegin?.o(.dtors)
         *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
         *(SORT(.dtors.*))
         *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))


    } > rom

    .ARM_extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > rom

    __exidx_start = .;
    .ARM_exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > rom
    __exidx_end = .;

    __etext = .;

    __DATA_ROM = .;

    .data : AT(__DATA_ROM)
    {
        __DATA_RAM = .;
        __data_start__ = .;
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);


        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > ram
    __DATA_END = __DATA_ROM + SIZEOF(.data);

    /* bss */
    .bss :
    {
        . = ALIGN(4);
        __START_BSS = .;
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
        __END_BSS = .;
    } > ram

    .heap (COPY):
    {
        __end__ = .;
        PROVIDE(end = .);
        *(.heap*)
        __HeapLimit = .;
    } > ram

    .stack (COPY):
    {
        *(.stack*)
    } > ram

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack section */
    __StackTop = ORIGIN(ram) + LENGTH(ram);
    __StackLimit = __StackTop - SIZEOF(.stack);
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}



