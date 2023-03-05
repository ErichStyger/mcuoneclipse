/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "benchmark.h"
#include "cycles.h"
#include "McuSemihost.h"
#include <stdio.h>

static void BenchMark_McuLib(void) {
  CCOUNTER_START();
  McuSemihost_WriteString((unsigned char*)"hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib write string hello world");

  CCOUNTER_START();
  McuSemihost_printf("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib printf hello world");

  CCOUNTER_START();
  for(int j=0; j<128; j++) {
    for(int i=0; i<32; i++) {
      McuSemihost_StdIOSendChar('a');
    }
    McuSemihost_StdIOSendChar('\n');
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib putchar");

#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_PEMICRO /* file I/O fails with PEMCIRCO */
  CCOUNTER_START();
  int file;
  unsigned char data[64];

  file = McuSemihost_FileOpen((unsigned char*)"c:\\tmp\\test2.txt", SYS_FILE_MODE_WRITE);
  if (file>=0) {
    for(int i=0; i<1024; i++) {
      McuSemihost_FileWrite(file, (unsigned char*)"hello world to a file\n", sizeof("hello world to a file\n")-1);
    }
    if (McuSemihost_FileLen(file)<4000) {
      for(;;) {} /* error */
    }
    McuSemihost_FileClose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib file write");

  CCOUNTER_START();
  file = McuSemihost_FileOpen((unsigned char*)"c:\\tmp\\test2.txt", SYS_FILE_MODE_READ);
  if (file>=0) { /* success */
    for(int i=0; i<100; i++) {
      McuSemihost_FileRead(file, data, sizeof(data));
    }
    McuSemihost_FileClose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib file read");
#endif
}

static void Benchmark_Stdlib(void) {
  CCOUNTER_START();
  puts("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib write string hello world");

  CCOUNTER_START();
  printf("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib printf hello world");

  CCOUNTER_START();
  for(int j=0; j<128; j++) {
    for(int i=0; i<32; i++) {
      putchar('a');
    }
    putchar('\n');
  }
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib putchar 1024 bytes");

#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_PEMICRO /* file I/O fails with PEMCIRCO */
  CCOUNTER_START();
  FILE *file;
  unsigned char data[64];

  file = fopen("c:\\tmp\\test2.txt", "w");
  if (file!=NULL) {
    for(int i=0; i<1024; i++) {
      (void)fwrite("hello world to a file\n", sizeof("hello world to a file\n")-1, 1, file);
    }
    if (ftell(file)<4000) {
      for(;;) {} /* error */
    }
    fclose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib write file");

  CCOUNTER_START();
  file = fopen("c:\\tmp\\test2.txt", "r");
  if (file!=NULL) { /* success */
    for(int i=0; i<100; i++) {
      fread(data, sizeof(data), 1, file);
    }
    fclose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib file read");
#endif
}

void Benchmark_Run(void) {
  BenchMark_McuLib();
  Benchmark_Stdlib();
}
