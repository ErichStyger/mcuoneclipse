INCLUDE "LPC845_RomLib_Debug_library.ld"

/* Memory used for the ROM library.
 * Make sure these areas are *not* part of the application 
 */
MEMORY
{
  PROGRAM_FLASH (rx) : ORIGIN = 0xF000, LENGTH = 0x1000 /* 4K bytes */  
  SRAM (rwx) : ORIGIN = 0x10000000, LENGTH = 0x10 /* 16 bytes */  
}

ENTRY(RomLib_Init)  /* makt it as entry point: everything used by it will not be discarded */

SECTIONS
{
     /* MAIN TEXT SECTION: code and constant data */
    .text  : ALIGN(4)
    {
        FILL(0xff)
        KEEP(*(.ROM_LIB_CODE)) /* do not discard anything marked as ROM Lib code */
        KEEP(*(.ROM_LIB_CONST)) /* do not discard anything marked as ROM constant */
       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > PROGRAM_FLASH

    /* Main DATA section (SRAM): data for initialized variables */
    .data : ALIGN(4)
    {
       FILL(0xff)
       KEEP(*(.ROM_LIB_RAM))
       *(.data*)
       . = ALIGN(4) ;
    } > SRAM AT>PROGRAM_FLASH

     /* MAIN BSS SECTION for un-initialized variables */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
    } > SRAM AT> SRAM

}