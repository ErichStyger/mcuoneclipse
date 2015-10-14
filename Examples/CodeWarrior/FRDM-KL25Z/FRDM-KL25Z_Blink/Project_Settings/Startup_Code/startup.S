/********************************************************************************
  * \file      startup.s
  * \brief     Startup file for Kinetis L (KL25Z).
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == __thumb_startup,
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  ******************************************************************************/
  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb
 
.global g_pfnVectors
.global Default_Handler
 
/* start address for the initialization values of the .data section. defined in linker script */
.word ___ROM_AT
/* start address for the .data section. defined in linker script */ 
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word __START_BSS
/* end address for the .bss section. defined in linker script */
.word __END_BSS
 
/**
 * \brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * \param  None
 * \retval : None
*/
  .section .text.__thumb_startup
  .weak __thumb_startup
  .type __thumb_startup, %function
__thumb_startup:
/* Copy the data segment initializers from flash to SRAM: */ 
  movs r1, #0
  b LoopCopyDataInit
 
CopyDataInit:
  ldr r3, =___ROM_AT
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4
 
LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =__START_BSS
  b LoopFillZerobss

/* Zero fill the bss segment: */ 
FillZerobss:
  movs r3, #0
  str r3, [r2]
  adds r2, r2, #4
 
LoopFillZerobss:
  ldr r3, = __END_BSS
  cmp r2, r3
  bcc FillZerobss
/* Call the clock system intitialization function: */
  bl  __init_hardware
/* Call the application's entry point: */
  bl main
  bx lr
.size __thumb_startup, .-__thumb_startup
 
/****END OF FILE****/
