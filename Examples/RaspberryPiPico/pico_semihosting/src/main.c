/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include <stdio.h>
#include "application.h"
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"
#endif

#if 0
#include "McuSemihost.h"

void file_check(void) {
  volatile int fh;

  McuSemihost_WriteString((unsigned char*)"Testing semihosting file I/O\n");
  fh = McuSemihost_SysFileOpen("c:\\tmp\\semihosting.txt", SYS_FILE_MODE_WRITEREADBINARY);
  if (fh != -1) {
    const unsigned char *msg = (const unsigned char*)"test file write 0123456789ABCDEF Hello World!";
    volatile int res = McuSemihost_SysFileWrite(fh, msg, strlen((char*)msg));
    if (res != 0) {
      McuSemihost_printf((unsigned char*)"SYS_WRITE: failed, res: %d\n", res);
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE OK\n");
    }
    if (McuSemihost_SysFileClose(fh)==0) {
      McuSemihost_WriteString((unsigned char*)"Close OK\n");
      printf("ok");
    }
  }
}
#endif

#if 1
static void semihost_file_test(void) {
  FILE *file;

  file = fopen ("test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
  }
}
#endif

int main(void) {
  PL_Init();
  semihost_file_test();
  vTaskStartScheduler();
  // GCOVR_EXCL_START
#if PL_CONFIG_USE_GCOV
   gcov_write_files(); /* write coverage files, might take a while depending how many files are covered */
#endif
  for(;;) {
    __asm("nop"); /* do not leave main() */
  }
  // GCOVR_EXCL_STOP
  return 0;
}
