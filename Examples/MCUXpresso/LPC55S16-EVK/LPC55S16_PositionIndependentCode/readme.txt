readme.txt
----------
add-symbol-file ./Debug/libmystuff.so 0x718
info address MyLib_Mul2

discard all symbols: 
symbol-file

lib.so
.text starting at 0x740
MyLib_Mul2 is at  0x838  (+0xF8)

MyLib_Mul2 is loaded at 0x6d0
Set .text symbol base at 0x6d0-0xf8 => 0x5d8

add-symbol-file ./Debug/myLib.o 0x5d8
add symbol table from file "./Debug/myLib.o" at
	.text_addr = 0x5d8
(y or n) [answered Y; input not from terminal]
Reading symbols from ./Debug/myLib.o...
info address MyLib_Mul2
Symbol "MyLib_Mul2" is a function at address 0x6d0.


Links:
https://github.com/rgujju/STM32-projects/tree/master/got_plt
https://community.arm.com/developer/ip-products/processors/f/cortex-m-forum/45919/gcc-does-not-generate-correct-code-while-building-pic
https://answers.launchpad.net/gcc-arm-embedded/+question/669758
https://answers.launchpad.net/gcc-arm-embedded/+question/675869
https://eli.thegreenplace.net/2011/11/03/position-independent-code-pic-in-shared-libraries
https://community.arm.com/developer/ip-products/processors/f/cortex-m-forum/45864/shared-libraries-and-plt-using-gcc-toolchain




See https://github.com/rgujju/STM32-projects/tree/master/got_plt


/*------------------------------------------------------------- */
        LONG(LOADADDR(.got));
        LONG(    ADDR(.got));
        LONG(  SIZEOF(.got));
/*------------------------------------------------------------- */


       /* PLT section contains code for accessing the dynamically linked functions
     * ie functions from shared libraries in a position independent manner */
    .plt :
    {
        . = ALIGN(4);
        *(.plt)
        . = ALIGN(4);
    } >PROGRAM_FLASH
    
 /* The global offset table is the table for indirectly accessing the global variables
     * The table contains addresses of the global variables. The text section contains 
     * a address of the GOT base and a offset in it to access the appropriate variables.
     * This is done to access the variables in a position independent manner. */
    .got :
    {
        . = ALIGN(4);
        _sgot = .;
        *(.got)
    } >SRAM AT> PROGRAM_FLASH
    
    /* got.plt section contains entries which is used with the PLT to access the functions 
     * in a position independent manner. */
    .got.plt :
    {
        . = ALIGN(4);
        *(.got.plt)
        _edata = .;
    } >SRAM AT> PROGRAM_FLASH
    
    _etext = .;
 
 /////////////////////////////////////////////////////////////////////////////7
 .got in FLASH:
     .text : ALIGN(4)
    {
       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       /*--------------------------------------------------- */
       /*------ GOT Global Offset Table: place it into FLASH */
       *(.got*)
       /*--------------------------------------------------- */
       . = ALIGN(4);
    } > PROGRAM_FLASH
 ///////////////////////////////////////////////////////////////////////////////
 .got in RAM:
 
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
/*---------------------------------------------------------------------- */
/*--- Initialization of Global Offset Table ---------------------------- */
/* Adding the GOT here will place it in RAM, initialized during startup  */
/*        LONG(LOADADDR(.got));
        LONG(    ADDR(.got));
        LONG(  SIZEOF(.got));*/
/*---------------------------------------------------------------------- */
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } > PROGRAM_FLASH
 