/**
 * \file gcov_support.h
 * \brief Support helpers to use gcov for embedded targets.
 * \author Erich Styger
 * \copyright
 * Web:         https://mcuoneclipse.com
 * SourceForge: https://sourceforge.net/projects/mcuoneclipse
 * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ###################################################################*/

#include <gcov_support.h>
#include <stdint.h>
#include <stdio.h>

void __gcov_flush(void); /* internal gcov function to write data */

int gcov_check(void) {
#if GCOV_DO_COVERAGE
  FILE *file = NULL;

  file = fopen ("c:\\tmp\\test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
    return 1; /* ok */
  }
  return 0; /* failed */
#else
  return 1; /* ok */
#endif
}

void gcov_write(void) {
#if GCOV_USE_TCOV
    tcov_print_all(); /* print coverage information */
#elif GCOV_USE_GCOV_EMBEDDED
  void gcov_exit(void);

  gcov_exit();
#elif GCOV_DO_COVERAGE
  __gcov_flush();
#endif
}

/* call the coverage initializers if not done by startup code */
void gcov_init(void) {
#if GCOV_DO_COVERAGE
  void (**p)(void);
  extern uint32_t __init_array_start, __init_array_end; /* linker defined symbols, array of function pointers */
  uint32_t beg = (uint32_t)&__init_array_start;
  uint32_t end = (uint32_t)&__init_array_end;

  while(beg<end) {
    p = (void(**)(void))beg; /* get function pointer */
    (*p)(); /* call constructor */
    beg += sizeof(p); /* next pointer */
  }
#endif /* GCOV_DO_COVERAGE */
}

#if 0 && GCOV_USE_GCOV_EMBEDDED

#include <stdio.h>
#include <stdlib.h>
#include "libgcov.h"

typedef struct tagGcovInfo {
    struct gcov_info *info;
    struct tagGcovInfo *next;
} GcovInfo;
static GcovInfo *headGcov = NULL;

void exit(int i) {
  for(;;)  {}
}

/*
 * __gcov_init is called by gcc-generated constructor code for each object
 * file compiled with -fprofile-arcs.
 */
void __gcov_init(struct gcov_info *info)
{
    //printf("__gcov_init called for %s!\n", gcov_info_filename(info));
    //fflush(stdout);
    GcovInfo *newHead = malloc(sizeof(GcovInfo));
    if (!newHead) {
        puts("Out of memory error!");
        exit(1);
    }
    newHead->info = info;
    newHead->next = headGcov;
    headGcov = newHead;
}

void __gcov_merge_add(gcov_type *counters, unsigned int n_counters) {
  puts("__gcov_merge_add isn't called, right? Right? RIGHT?");
  fflush(stdout);
  exit(1);
}


#endif /* GCOV_USE_GCOV_EMBEDDED */
