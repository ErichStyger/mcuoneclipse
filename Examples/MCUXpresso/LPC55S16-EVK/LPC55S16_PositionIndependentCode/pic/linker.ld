ENTRY(reset_handler)

MEMORY
{
    FLASH   (rx)    : ORIGIN = 0x00000000, LENGTH = 32K
    RAM     (rxw)   : ORIGIN = 0x20000000, LENGTH = 64K
}

PHDRS
{
 /*  headers      PT_PHDR PHDRS;*/
 /* header_load  PT_LOAD PHDRS; */
  code         PT_LOAD;
  data         PT_LOAD;
/*   interp       PT_INTERP; */
 /* dynamic      PT_DYNAMIC; */
}

_estack = 0x20001000;

SECTIONS
{
  .vector_table :
  {
    . = ALIGN(4); /* The code memory ie FLASH of ARM Cortex-M micros need to be word aligned */
	              /* The word size is 32 bits or 4 bytes for the one i am using */
	  KEEP (*(.vector_table)) /* Use KEEP command to avoid removal of code if using link time garbage collection */
    . = ALIGN(4);
  } >FLASH :code

  .text : 
  { 
   . = ALIGN(4);
  	*(.text)
   . = ALIGN(4);
  } >FLASH :code
  
/*   .interp : { *(.interp) } :interp :headers :header_load*/
  .hash : { *(.hash) } >FLASH
  .dynsym : { *(.dynsym) }
  .dynstr : { *(.dynstr) }
  .rela.dyn : { *(.rela.dyn) }
  .rela.plt : { *(.rela.plt) }
  .plt : { *(.plt) }
  .header : { } >RAM  :header_load :headers
  
 /*  .dynamic : { *(.dynamic) } :data :dynamic */

  .got : { 
  	_sgot = .;
  	*(.got.plt) *(.got)
  	_edata = .;
  } >RAM AT> FLASH :data

  .data : { 
  	_sdata = .;
  	*(.data)
  } >RAM AT> FLASH :data
    
   _sidata = LOADADDR(.data);

  .bss : { 
  	_sbss = .;
  	*(.bss) *(.dynbss)
  	_ebss = .;
  } >RAM :data


  /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) }
}