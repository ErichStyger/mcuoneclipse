/*
 * File: exceptions_cfv2.h
 * Purpose: Generic exception handling for ColdFire processors
 *
 * Notes:
 */

#ifndef _MCF_EXCEPTIONS_H
#define _MCF_EXCEPTIONS_H

#include "derivative.h"

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************/
/*
 * This is the handler for all exceptions which are not common to all 
 * ColdFire Chips.  
 *
 * Called by mcf_exception_handler
 * 
 */
void derivative_interrupt(unsigned long vector);

/***********************************************************************/
/*
 * This is the exception handler for all  exceptions common to all 
 * chips ColdFire.  Most exceptions do nothing, but some of the more 
 * important ones are handled to some extent.
 *
 * Called by asm_exception_handler 
 */
void mcf_exception_handler(void *framepointer);


/***********************************************************************/
/*
 * This is the assembly exception handler defined in the vector table.  
 * This function is in assembler so that the frame pointer can be read  
 * from the stack.
 * Note that the way to give the stack frame as argument to the c handler
 * depends on the used ABI (Register, Compact or Standard).
 *
 */
asm void __declspec(register_abi) asm_exception_handler(void);



/***********************************************************************/
/* MCF5xxx exceptions table initialization:
 *
 * Set VBR and performs RAM vector table initialization.
 * The following symbol should be defined in the lcf:
 * __VECTOR_RAM
 *
 * _vect is the start of the exception table in the code
 * In case _vect address is different from __VECTOR_RAM,
 * the vector table is copied from _vect to __VECTOR_RAM.
 * In any case VBR is set to __VECTOR_RAM.
 */ 
void initialize_exceptions(void);

asm void __declspec(register_abi) TrapHandler_printf(void);

/* User defined interrupt routines */

extern void __declspec(interrupt) USB_ISR(void);
extern void __declspec(interrupt) Timer_ISR(void);
extern void __declspec(interrupt) PIT1_ISR(void);
extern void __declspec(interrupt) UART0_ISR(void);

#if (defined __MCF52221_H__)||(defined __MCF52259_DEMO_)
	extern void __declspec(interrupt) IRQ_ISR(void);
#endif


/********************************************************************
 * MCF5xxx ASM utility functions
 */
asm void __declspec(register_abi) mcf5xxx_wr_vbr(unsigned long);

	
#ifdef __cplusplus
}
#endif

#endif   /* _MCF_EXCEPTIONS_H */

