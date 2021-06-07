/* startup.c */
#include <stdint.h>
#include <sys/types.h>

// ----------------------------------------------------------------------------
// Begin address for the initialization values of the .data section.
// defined in linker script
extern unsigned int _sidata;
// Begin address for the .data section; defined in linker script
extern unsigned int _sdata;
// End address for the .data section; defined in linker script
extern unsigned int _edata;

// Begin address for the .bss section; defined in linker script
extern unsigned int __bss_start__;
// End address for the .bss section; defined in linker script
extern unsigned int __bss_end__;

extern int main (void);

// The implementation for the exit routine; for embedded
// applications, a system reset might be performed.
extern void __attribute__((noreturn)) _exit (int);

// ----------------------------------------------------------------------------
static inline void __attribute__((always_inline)) __initialize_data(unsigned int *from, unsigned int *region_begin, unsigned int *region_end)
{
  // Iterate and copy word by word.
  // It is assumed that the pointers are word aligned.
  unsigned int *p = region_begin;
  while (p < region_end) {
    *p++ = *from++;
  }
}

static inline void __attribute__((always_inline)) __initialize_bss(unsigned int* region_begin, unsigned int* region_end) {
  // Iterate and clear word by word.
  // It is assumed that the pointers are word aligned.
  unsigned int *p = region_begin;
  while (p < region_end) {
    *p++ = 0;
  }
}

// These magic symbols are provided by the linker.
extern void (*__preinit_array_start[]) (void) __attribute__((weak));
extern void (*__preinit_array_end[]) (void) __attribute__((weak));
extern void (*__init_array_start[]) (void) __attribute__((weak));
extern void (*__init_array_end[]) (void) __attribute__((weak));
extern void (*__fini_array_start[]) (void) __attribute__((weak));
extern void (*__fini_array_end[]) (void) __attribute__((weak));

// Iterate over all the preinit/init routines (mainly static constructors).
inline void __attribute__((always_inline)) __run_init_array (void) {
  int count;
  int i;

  count = __preinit_array_end - __preinit_array_start;
  for (i = 0; i < count; i++)
    __preinit_array_start[i] ();

  // If you need to run the code in the .init section, please use
  // the startup files, since this requires the code in crti.o and crtn.o
  // to add the function prologue/epilogue.
  //_init(); // DO NOT ENABE THIS!

  count = __init_array_end - __init_array_start;
  for (i = 0; i < count; i++)
    __init_array_start[i] ();
}

// Run all the cleanup routines (mainly static destructors).
inline void __attribute__((always_inline)) __run_fini_array (void) {
  int count;
  int i;

  count = __fini_array_end - __fini_array_start;
  for (i = count; i > 0; i--)
    __fini_array_start[i - 1] ();

  // If you need to run the code in the .fini section, please use
  // the startup files, since this requires the code in crti.o and crtn.o
  // to add the function prologue/epilogue.
  //_fini(); // DO NOT ENABE THIS!
}

static void __initialize_hardware_early(void) {
	void SystemInit(void);
	SystemInit();
}

static void __initialize_hardware(void) {
}

void __attribute__ ((section(".after_vectors"),noreturn,weak)) _startup (void) {
  __initialize_hardware_early();
  __initialize_data(&_sidata, &_sdata, &_edata);
  __initialize_bss(&__bss_start__, &__bss_end__);
  __initialize_hardware ();

  // Call the standard library initialisation (mandatory for C++ to
  // execute the constructors for the static objects).
  __run_init_array ();

  // Call the main entry point, and save the exit code.
  //int code = main (argc, argv);
  int code = main();

  // Run the C++ static destructors.
  __run_fini_array ();

  _exit (code);

  // Should never reach this
  for (;;) {
	  __asm("nop");
  }
}
