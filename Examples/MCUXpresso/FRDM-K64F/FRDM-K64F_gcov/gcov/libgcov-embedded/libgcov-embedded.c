/*
 * coverage-support.c
 *
 *  We need only few basic things from the article http://tinyurl.com/jkegjzh
 *  These are - static_init and the get_stackpointer
 */

#include "gcov_support.h"

#ifndef ENABLE_LIBGCOV_PORT
  #error "ENABLE_LIBGCOV_PORT must be defined and set to 0 or 1"
#endif

#ifdef ENABLE_LIBGCOV_PORT

#include <stdio.h>
#include <stddef.h>
#include "libgcov-embedded.h"
#include "libgcov.h"
#if !GCOV_EEMBEDDED_FILE_IO
  #include "McuUtility.h"
#endif

/* Our stub for _exit that calls the gcov_exit */
void
_exit (int status)
{
  gcov_exit();
  for(;;){ }
}

void gcov_writeDataHook(unsigned char* bufStart, unsigned char *bufEnd, const char *fileName) {
#if GCOV_EMBEDDED_FILE_IO
  FILE *file = NULL;

  file = fopen (fileName, "w");
  if (file!=NULL) {
    (void)fwrite(bufStart, bufEnd-bufStart-1, 1, file);
    fclose(file);
  }
#else
  /* write bufStart...bufEnd-1 */
  static unsigned char gdbBuf[512];

  McuUtility_strcpy(gdbBuf, sizeof(gdbBuf), (unsigned char*)"dump binary memory \"");
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)fileName);
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)"\" 0x");
  McuUtility_strcatNum32Hex(gdbBuf, sizeof(gdbBuf), (uint32_t)bufStart);
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)" 0x");
  McuUtility_strcatNum32Hex(gdbBuf, sizeof(gdbBuf), (uint32_t)bufEnd);
#endif
}

#endif /* ENABLE_LIBGCOV_PORT */
