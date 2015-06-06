/*
 * coverage_stubs.c
 *
 *  These stubs are needed to generate coverage from an embedded target.
 */
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "UTIL1.h"
#include "coverage_stubs.h"

#if DO_COVERAGE
/* prototype */
void gcov_exit(void);

#define COV_FILE_BUFFER_SIZE	 0x5000
#define COV_FILE_HANDLE          17 /* valid file handle is >2 (which is STDERR_FILENO) */

static struct {
	const char *fileName;
	int fileSize;
	uint8_t *bufPtr;
	uint8_t buffer[COV_FILE_BUFFER_SIZE];
} COV_Buffer;
static unsigned char gdb_cmd[128]; /* command line which can be used for gdb */


/* call the coverage initializers if not done by startup code */
void static_init(void) {
  void (**p)(void);
  extern uint32_t __init_array_start, __init_array_end; /* linker defined symbols, array of function pointers */
  uint32_t beg = (uint32_t)&__init_array_start;
  uint32_t end = (uint32_t)&__init_array_end;

  while(beg<end) {
    p = (void(**)(void))beg; /* get function pointer */
    (*p)(); /* call constructor */
    beg += sizeof(p); /* next pointer */
  }
}

void _exit(int status) {
  (void) status;
  gcov_exit();
  for(;;){} /* does not return */
}

int _read(int file, char *ptr, int len) {
  if (file==COV_FILE_HANDLE) {
	  int nofRead;

	  nofRead = 0;
	  while(len>0) {
		  if (COV_Buffer.fileSize==0) { /* empty file */
			  return 0;
		  }
		  if (COV_Buffer.bufPtr >= &COV_Buffer.buffer[COV_Buffer.fileSize]) {
			  return 0; /* end of file */
		  }
		  *ptr++ = *COV_Buffer.bufPtr++;
		  nofRead++;
	  }
	  return nofRead;
  }
  return 0; /* return number of bytes read */
}

int _write(int file, char *ptr, int len) {
  int size;

#if 0
  /* In case of the file is written in one piece (newlib), you can dump it now.
   * But if using newlib-nano, it writes to the file byte by byte, so dumping is postponed
   */
  /* construct gdb command string to write gcda file */
  UTIL1_strcpy(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)"dump binary memory ");
  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), COV_Buffer.fileName);
  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)" 0x");
  UTIL1_strcatNum32Hex(gdb_cmd, sizeof(gdb_cmd), (uint32_t)ptr);
  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)" 0x");
  UTIL1_strcatNum32Hex(gdb_cmd, sizeof(gdb_cmd), (uint32_t)(ptr+len));
#endif
  if (file==COV_FILE_HANDLE) {
	  size = len;
	  while(size>0) {
		  if (COV_Buffer.bufPtr>=&COV_Buffer.buffer[COV_FILE_BUFFER_SIZE]) {
			  /* buffer overflow! */
			  for(;;);
		  }
		  *COV_Buffer.bufPtr++ = *ptr++;
		  size--;
	  }
	  COV_Buffer.fileSize = COV_Buffer.bufPtr-&COV_Buffer.buffer[0];
  }
  return len; /* on success, return number of bytes written */
}

int _open (const char *ptr, int mode) {
  (void)mode;
  COV_Buffer.fileName = ptr;
  COV_Buffer.bufPtr = &COV_Buffer.buffer[0];
  COV_Buffer.fileSize = 0;
  return COV_FILE_HANDLE;
}

int _close(int file) {
  if (file==COV_FILE_HANDLE) {
	  /* construct gdb command string to write .gcda file */
	  UTIL1_strcpy(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)"dump binary memory ");
	  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), COV_Buffer.fileName);
	  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)" 0x");
	  UTIL1_strcatNum32Hex(gdb_cmd, sizeof(gdb_cmd), (uint32_t)&COV_Buffer.buffer[0]);
	  UTIL1_strcat(gdb_cmd, sizeof(gdb_cmd), (unsigned char*)" 0x");
	  UTIL1_strcatNum32Hex(gdb_cmd, sizeof(gdb_cmd), (uint32_t)(&COV_Buffer.buffer[COV_Buffer.fileSize]));
  }
  return 0; /* success closing file */
}

int _fstat(int file, struct stat *st) {
  (void)file;
  st->st_mode = S_IFCHR;
  return 0;
}

int _getpid(void) {
  return 1;
}

int _isatty(int file) {
  switch (file) {
  case STDOUT_FILENO:
  case STDERR_FILENO:
  case STDIN_FILENO:
    return 1;
  default:
    errno = EBADF;
    return 0;
  }
}

int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return (-1);
}

int _lseek(int file, int ptr, int dir) {
  (void)dir;
  if (file==COV_FILE_HANDLE) {
	  if (ptr < COV_FILE_BUFFER_SIZE) {
		  COV_Buffer.bufPtr = &COV_Buffer.buffer[ptr];
	  } else {
		  return -1; /* failure */
	  }
  }
  return ptr; /* return offset in file */
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
__attribute__((naked)) static unsigned int get_stackpointer(void) {
  __asm volatile (
    "mrs r0, msp   \r\n"
    "bx lr         \r\n"
  );
}
#pragma GCC diagnostic pop

void *_sbrk(int incr) {
  extern char __HeapLimit; /* Defined by the linker */
  static char *heap_end = 0;
  char *prev_heap_end;
  char *stack;

  if (heap_end==0) {
    heap_end = &__HeapLimit;
  }
  prev_heap_end = heap_end;
  stack = (char*)get_stackpointer();

  if (heap_end+incr > stack) {
    _write (STDERR_FILENO, "Heap and stack collision\n", 25);
    errno = ENOMEM;
    return  (void *)-1;
  }
  heap_end += incr;
  return (void *)prev_heap_end;
}
#endif
