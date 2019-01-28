//*****************************************************************************
// aeabi_romdiv_patch.s
//  - Provides "patch" versions of the aeabi integer divide functions to
//    replace the standard ones pulled in from the C library, which vector
//    integer divides onto the rom division functions contained in
//    specific NXP MCUs such as LPC8xx, LPC11Uxx and LPC12xx.
//  - Note that this patching will only occur if "__USE_ROMDIVIDE" is
//    defined for the project build for both the compiler and assembler.
//*****************************************************************************
//
// The Clear BSD License
// Copyright 2016-2018 NXP
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
// HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************
#if defined(__USE_ROMDIVIDE)

// Note that the romdivide "divmod" functions are not actually called from
// the below code, as these functions are actually just wrappers to the
// main romdivide "div" functions which push the quotient and remainder onto
// the stack, so as to be compatible with the way that C returns structures.
//
// This is not needed for the aeabi "divmod" functions, as the compiler
// automatically generates code that handles the return values being passed
// back in registers when it generates inline calls to __aeabi_idivmod and
// __aeabi_uidivmod routines.

	.syntax unified
	.text

// ========= __aeabi_idiv &  __aeabi_idivmod =========
	.align 2
	.section .text.__aeabi_idiv

	.global	__aeabi_idiv
	.set __aeabi_idivmod, __aeabi_idiv   // make __aeabi_uidivmod an alias
	.global __aeabi_idivmod
	.global pDivRom_idiv   // pointer to the romdivide 'idiv' functione
    .func
	.thumb_func
	.type	__aeabi_idiv, %function

__aeabi_idiv:
	push	{r4, lr}
	ldr	r3, =pDivRom_idiv
	ldr	r3, [r3, #0]     // Load address of function
	blx	r3               // Call divide function
	pop	{r4, pc}

	.endfunc

// ========  __aeabi_uidiv &  __aeabi_uidivmod ========
	.align 2

	.section .text.__aeabi_uidiv

	.global	__aeabi_uidiv
	.set __aeabi_uidivmod, __aeabi_uidiv  // make __aeabi_uidivmod an alias
	.global __aeabi_uidivmod
	.global pDivRom_uidiv	// pointer to the romdivide 'uidiv' function
    .func
	.thumb_func
	.type	__aeabi_uidiv, %function

__aeabi_uidiv:
	push	{r4, lr}
	ldr	r3, =pDivRom_uidiv
	ldr	r3, [r3, #0]      // Load address of function
	blx	r3               // Call divide function
	pop	{r4, pc}

	.endfunc

#endif // (__USE_ROMDIVIDE)
