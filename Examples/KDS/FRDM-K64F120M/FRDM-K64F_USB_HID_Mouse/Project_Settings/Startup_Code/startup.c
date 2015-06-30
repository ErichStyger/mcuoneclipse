/* GNUC Startup library
 *    Copyright © 2005 Freescale semiConductor Inc. All Rights Reserved.
 *
 * $Date: 2011/09/21 06:41:34 $
 * $Revision: 1.4 $
 */


/*
 *	startup.c	-	entry-point for ARM programs
 *
 */
#include <string.h>
#include <stdlib.h>

#define __MAX_CMDLINE_ARGS 10
static char *argv[__MAX_CMDLINE_ARGS] = { 0 };

#if __GNUC__
#define __call_static_initializers __init_cpp
#endif
extern int __argc_argv(char **, int);
extern char __SP_INIT[];
extern void __call_static_initializers(void);
extern int main(int, char **);

extern void _start(void);

extern void __init_registers();
extern void __init_hardware();
extern void __init_user();


extern void __copy_rom_sections_to_ram(void);

/* format of the ROM table info entry ... */
typedef struct RomInfo {
	unsigned long	Source;
	unsigned long	Target;
	unsigned long 	Size;
} RomInfo;

extern RomInfo __S_romp[] __attribute__((weak));    /* linker defined symbol */

/*
 * Routine to flush cache follow the ROM to RAM copy
 */
void __flush_cache(unsigned long dst, unsigned long size)
{
	//TBD
}


/*
 *	Routine to copy a single section from ROM to RAM ...
 */
void __copy_rom_section(unsigned long dst, unsigned long src, unsigned long size)
{
	unsigned long len = size;

	const int size_int = sizeof(int);
	const int mask_int = sizeof(int)-1;

	const int size_short = sizeof(short);
	const int mask_short = sizeof(short)-1;

	const int size_char = sizeof(char);

	if( dst == src || size == 0)
	{
		return;
	}


	while( len > 0)
	{

		if( !(src & mask_int) && !(dst & mask_int) && len >= size_int)
		{
			*((int *)dst)  = *((int*)src);
			dst += size_int;
			src += size_int;
			len -= size_int;
		}
		else if( !(src & mask_short) && !(dst & mask_short) && len >= size_short)
		{
			*((short *)dst)  = *((short*)src);
			dst += size_short;
			src += size_short;
			len -= size_short;
		}
		else
		{
			*((char *)dst)  = *((char*)src);
			dst += size_char;
			src += size_char;
			len -= size_char;
		}
	}
}

/*
 *	Routine that copies all sections the user marked as ROM into
 *	their target RAM addresses ...
 *
 *	__S_romp is defined in the linker command file
 *  It is a table of RomInfo
 *	structures.  The final entry in the table has all-zero
 *	fields.
 */
void __copy_rom_sections_to_ram(void)
{

	int				index;

	if (__S_romp == 0L) return;

	/*
	 *	Go through the entire table, copying sections from ROM to RAM.
	 */
	for (index = 0;
		 __S_romp[index].Source != 0 ||
		 __S_romp[index].Target != 0 ||
		 __S_romp[index].Size != 0;
		 ++index)
	{
		__copy_rom_section( __S_romp[index].Target,
							__S_romp[index].Source,
							__S_romp[index].Size );

		__flush_cache( __S_romp[index].Target, __S_romp[index].Size);


	}
}


static void zero_fill_bss(void)
{
	extern char __START_BSS[];
	extern char __END_BSS[];

	unsigned long len = __END_BSS - __START_BSS;
  unsigned long dst = (unsigned long) __START_BSS;

	const int size_int = sizeof(int);
	const int mask_int = sizeof(int)-1;

	const int size_short = sizeof(short);
	const int mask_short = sizeof(short)-1;

	const int size_char = sizeof(char);

	if( len == 0)
	{
		return;
	}


	while( len > 0)
	{

		if( !(dst & mask_int) && len >= size_int)
		{
			*((int *)dst)  = 0;
			dst += size_int;
			len -= size_int;
		}
		else if( !(dst & mask_short) && len >= size_short)
		{
			*((short *)dst)  = 0;
			dst += size_short;
			len -= size_short;
		}
		else
		{
			*((char *)dst)  = 0;
			dst += size_char;
			len -= size_char;
		}
	}
}


// __init_registers, __init_hardware, __init_user suggested by Kobler
void __attribute__ ((weak)) __init_registers(void)
{

}

void __attribute__ ((weak)) __init_hardware(void)
{

}

void __attribute__ ((weak)) __init_user(void)
{

}


// To keep iar debugger happy
void __iar_program_start(void);
void __thumb_startup(void);
void __iar_program_start()
{
	__thumb_startup();
}

void __thumb_startup(void)
{
int addr = (int)__SP_INIT;

		// Setup registers
		__init_registers();

		// setup hardware
		__init_hardware();

		// setup the stack before we attempt anything else
		// skip stack setup if __SP_INIT is 0
		// assume sp is already setup.
		__asm (
		"mov	r0,%0\n\t"
		"cmp	r0,#0\n\t"
		"beq	skip_sp\n\t"
		"mov	sp,r0\n\t"
		"sub	sp,#4\n\t"
		"mov	r0,#0\n\t"
		"mvn	r0,r0\n\t"
		"str	r0,[sp,#0]\n\t"
		"add	sp,#4\n\t"
		"skip_sp:\n\t"
		::"r"(addr));


		//	zero-fill the .bss section
		zero_fill_bss();

    // SUPPORT_ROM_TO_RAM
			__copy_rom_sections_to_ram();

		//	call C++ static initializers
    //  __call_static_initializers();

		// initializations before main, user specific
		__init_user();

		main(0, argv);



		//	should never get here
		while (1);

}

