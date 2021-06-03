/* Explicitly mention label for the program's entry point */
ENTRY(reset_handler)

/* End of RAM / Start of stack */
/* (4KB SRAM) */
_estack = 0x20001000;

/* Set minimum size for stack and dynamic memory. */
/* (The linker will generate an error if there is
 *  less than this much RAM leftover.) 
 *  For the current application, 1KB is enough
 *  but as the complexity grow, you will have to
 *  increase this */
/* (1KB) */
_Min_Leftover_RAM = 0x400;

MEMORY
{
  FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x38000 /* 224K bytes (alias Flash) */  
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x10000 /* 64K bytes (alias RAM) */  
}

SECTIONS
{
    /* The vector table goes at the start of flash. */
    .vector_table :
    {
        . = ALIGN(4); /* The code memory ie FLASH of ARM Cortex-M micros need to be word aligned */
                      /* The word size is 32 bits or 4 bytes for the one i am using */
        KEEP (*(.vector_table)) /* Use KEEP command to avoid removal of code if using link time garbage collection */
        . = ALIGN(4);
    } >FLASH

    /* The 'text' section contains the main program code. */
    .text :
    {
        . = ALIGN(4);
        *(.text*)
        . = ALIGN(4);

    } >FLASH
    
    /* The 'rodata' section contains read-only data,
     * constants, strings, information that won't change. 
     * variables defined with const keyword in C */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);

    } >FLASH
    
    /* PLT section contains code for accessing the dynamically linked functions
     * ie funtions from shared libraries in a postion independent manner */
    .plt :
    {
        . = ALIGN(4);
        *(.plt)
        . = ALIGN(4);
    } >FLASH
    
    /* The 'data' section is space set aside in RAM for
     * things like non-zero global and static variables, which can change. */
   
    .data :
    {
        /* We cannot declare _sidata here, because it will be assigned the 
         * start of RAM (0x20000000), instead of end of FLASH */
        . = ALIGN(4);
        /* Mark start/end locations for the 'data' section. */
        _sdata = .;
        *(.data*)
        . = ALIGN(4);

    } >RAM AT> FLASH /* Mentioning RAM here, specifies the VMA ie virtual memory address ie address during execution */
    /* The AT defines the load address of the .data section. This is where the section will be loaded */
    
    /* _sidata will be the location .data section will be stored
     * in the flash, and _sdata will be the location of .data section 
     * in the RAM. We use these two addresses to copy data from _sidata
     * to _sdata*/
    _sidata = LOADADDR(.data);
        
    /* The global offset table is the table for indirectly accessing the global variables
     * The table contains addresses of the global variables. The text section contains 
     * a address of the GOT base and a offset in it to access the appropriate variables.
     * This is done to access the variables in a postion independent manner. */
    .got :
    {
        . = ALIGN(4);
        _sgot = .;
        *(.got)
    } >RAM AT> FLASH
    
    /* got.plt section contains entries which is used with the PLT to access the functions 
     * in a position independent manner. */
    .got.plt :
    {
        . = ALIGN(4);
        *(.got.plt)
        _edata = .;
    } >RAM AT> FLASH
    
    /* The 'bss' section is similar to the 'data' section,
    *  but its space is initialized to all 0s at the
    *  start of the program. */
    .bss :
    {
        . = ALIGN(4);
        /* Also mark the start/end of the BSS section. */
        _sbss = .;
        *(.bss*)
        /* A special notation is needed for common symbols, 
         * because in many object file formats common symbols 
         * do not have a particular input section. The linker 
         * treats common symbols as though they are in an 
         * input section named ‘COMMON’.*/ 
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;

    } >RAM
    
    /* Space set aside for the application's heap/stack. */
    .dynamic_allocations :
    {
        . = ALIGN(4);
        _ssystem_ram = .;
        . = . + _Min_Leftover_RAM;
        . = ALIGN(4);
        _esystem_ram = .;

    } >RAM

}
