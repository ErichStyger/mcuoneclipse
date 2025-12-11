#include <stdint.h>

#if 0 /* they might get called by assert (if DEBUG is defined, or NDEBUG is not defined)? */
  int _isatty(void) {return -1;}
  int _fstat(void) {return -1;}
  int _write(void) {return -1;}
  int _sbrk(void) {return -1;}
  int _getpid(void) {return -1;}
  int _kill(void) {return -1;}
  int _exit(void) {return -1;}
  int _close(void) {return -1;}
  int _lseek(void) {return -1;}
  int _read(void) {return -1;}
#endif
/* required for release build with -lto enabled: */
int _kill(void) {return -1;}
int _getpid(void) {return -1;}
int _exit(void) {return -1;}

void __assert_func(const char *_file, int _line, const char *_func, const char *_expr) {
  (void)_file;
  (void)_line;
  (void)_func;
  (void)_expr;
  volatile int loop = 1;
  __asm volatile ("bkpt 0");
  do { ; } while( loop );
}

void *_sbrk (uint32_t delta ) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  extern char _pvHeapLimit; /* Defined by the linker */
#else
  extern char __HeapLimit;
#endif
static char *heap_end;
char *prev_heap_end;
 
  if (heap_end == 0) {
    #if McuLib_CONFIG_CPU_IS_KINETIS
    heap_end = &_pvHeapLimit;
    #else
    heap_end = &__HeapLimit;
    #endif
  }
 
  prev_heap_end = heap_end;
  //if (prev_heap_end+delta > get_stack_pointer()) {
  //       return (void *) -1L;
  //}
  heap_end += delta;
  return (void *) prev_heap_end;
}
