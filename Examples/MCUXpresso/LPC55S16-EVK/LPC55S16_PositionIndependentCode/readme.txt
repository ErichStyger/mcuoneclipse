readme.txt
----------

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
 
 
 