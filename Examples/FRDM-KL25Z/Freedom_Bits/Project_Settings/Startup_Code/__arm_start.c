/* CodeWarrior ARM Runtime Support Library * Copyright © 2012 Freescale Semiconductors. All rights reserved. * * $Date: 2012/07/23 06:20:27 $ * $Revision: 1.5 $ */
/* *  __arm_start.c  -  entry-point for ARM programs * */
#include <string.h>#include <stdlib.h>#include <runtime_configuration.h>
_EWL_BEGIN_EXTERN_C
extern void main(void);extern void __init_registers(void);extern void __init_hardware(void);extern void __init_user(void);
extern void __copy_rom_sections_to_ram(void);extern char __S_romp[];
static void zero_fill_bss(void) {  extern char __START_BSS[];  extern char __END_BSS[];
  memset(__START_BSS, 0, (__END_BSS - __START_BSS));}
void __thumb_startup(void) _EWL_NAKED;
void __thumb_startup(void) {  __init_registers(); /* Setup registers */  __init_hardware();  /* setup hardware */  zero_fill_bss();    /*  zero-fill the .bss section */  if (__S_romp != 0L) { /* copy down */    __copy_rom_sections_to_ram();  }  __init_user(); /* initializations before main, user specific */  main(); /*  call main() */  /*  should never get here */}
_EWL_END_EXTERN_C
