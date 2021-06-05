// These instructions define attributes of our chip and
// the assembly language we'll use:
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

// Global memory locations.
.global vtable
.global reset_handler

/*
 * The actual vector table.
 * Only the size of RAM and 'reset' handler are
 * included, for simplicity.
 */
.type vtable, %object
/* This is additional line that is required to be added so that
 * we create a new section header called vector_table in the object file
 * which will be placed in the vector_table section of the output elf by
 * the linker */
.section .vector_table,"a",%progbits 
vtable:
	.word _estack
	.word reset_handler

/*
 * The Reset handler. Called on reset/Power on
 */
.type reset_handler, %function
reset_handler:
	// Set the stack pointer to the end of the stack.
	// The '_estack' value is defined in our linker script.
	LDR  r0, =_estack
	MOV  sp, r0

	// Copy data from flash to RAM data init section.
	// R2 will store our progress along the sidata section.

	MOVS r0, #0

	// Load the start/end addresses of the data section,
	// and the start of the data init section.
	LDR  r1, =_sdata
	LDR  r2, =_edata
	LDR  r3, =_sidata
	B    copy_sidata_loop

	copy_sidata:
		// Offset the data init section by our copy progress.
        // Load from r3 offset by r0 to r4
		LDR  r4, [r3, r0]
		// Copy the current word into data, and increment.
        // Store r4 to r1 offset by r0
		STR  r4, [r1, r0]
		ADDS r0, r0, #4

	copy_sidata_loop:
		// Unless we've copied the whole data section, copy the
		// next word from sidata->data.
		ADDS r4, r0, r1
		CMP  r4, r2
		BCC  copy_sidata

	// Once we are done copying the data section into RAM,
	// move on to filling the BSS section with 0s.
	MOVS r0, #0
	LDR  r1, =_sbss
	LDR  r2, =_ebss
	B    reset_bss_loop

	// Fill the BSS segment with '0's.
	reset_bss:
		// Store a 0 and increment by a word.
		STR  r0, [r1]
		ADDS r1, r1, #4

	reset_bss_loop:
		// We'll use R1 to count progress here; if we aren't
		// done, reset the next word and increment.
		CMP  r1, r2
		BCC  reset_bss

	// For the single pic base option, we need to 
	// initialize r9 with the GOT base address
	LDR r9, =_sgot

    // And then branch off to main
    B main

    __main_loop:
        // Loop back.
        B    __main_loop

.size reset_handler, .-reset_handler
