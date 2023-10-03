#if 1 /* they might get called by assert (if DEBUG is defined, or NDEBUG is not defined)? */
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

void __assert_func(const char *_file, int _line, const char *_func, const char *_expr) {
  (void)_file;
  (void)_line;
  (void)_func;
  (void)_expr;
  volatile int loop = 1;
  __asm volatile ("bkpt 0");
  do { ; } while( loop );
}
