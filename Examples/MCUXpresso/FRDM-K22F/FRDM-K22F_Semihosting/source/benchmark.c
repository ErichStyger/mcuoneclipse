/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "benchmark.h"
#if BENCHMARK_DO_BENCHMARK
#include "cycles.h"
#include "McuSemihost.h"
#include "McuArmTools.h"
#include "McuWait.h"
#include <stdio.h>

static const uint8_t file_data[] =
{
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
};

#if !BENCHMARK_USE_STDLIB
static void BenchMark_McuLib(void) {
  CCOUNTER_START();
  McuSemihost_printf("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib printf hello world");

  CCOUNTER_START();
  McuSemihost_WriteString((unsigned char*)"hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib write string hello world");

  CCOUNTER_START();
  for(int j=0; j<128; j++) {
    for(int i=0; i<32; i++) {
      McuSemihost_StdIOSendChar('a');
    }
    McuSemihost_StdIOSendChar('\n');
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib putchar");

#if BENCHMARK_USE_FILE_IO ||(McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_PEMICRO) && (McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_PYOCD)  /* file I/O fails with PEMCIRCO && pyOCD */
  CCOUNTER_START();
  int file;
  unsigned char data[64];

  file = McuSemihost_SysFileOpen((unsigned char*)"c:\\tmp\\test1.txt", SYS_FILE_MODE_WRITE);
  if (file>=0) {
    for(int i=0; i<10; i++) {
      McuSemihost_SysFileWrite(file, file_data, sizeof(file_data));
    }
    if (McuSemihost_SysFileLen(file)<4000) {
      for(;;) {} /* error */
    }
    McuSemihost_SysFileClose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib file write");

  CCOUNTER_START();
  file = McuSemihost_SysFileOpen((unsigned char*)"c:\\tmp\\test1.txt", SYS_FILE_MODE_READ);
  if (file>=0) { /* success */
    for(int i=0; i<100; i++) {
      McuSemihost_SysFileRead(file, data, sizeof(data));
    }
    McuSemihost_SysFileClose(file);
  } else {
    for(;;) {} /* failed */
  }
  CCOUNTER_STOP();
  Cycles_LogTime("McuLib file read");
#endif
  McuSemihost_WriteString((unsigned char*)"finished!\n");
  McuSemihost_StdIOFlush();
}
#endif

#if BENCHMARK_USE_STDLIB
static void Benchmark_Stdlib(void) {
  CCOUNTER_START();
  printf("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib printf hello world");

  CCOUNTER_START();
  puts("hello world!\n");
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib write string hello world");

  CCOUNTER_START();
  for(int j=0; j<128; j++) {
    for(int i=0; i<32; i++) {
      putchar('a');
    }
    putchar('\n');
  }
  CCOUNTER_STOP();
  Cycles_LogTime("Stdlib putchar 1024 bytes");

#if BENCHMARK_USE_FILE_IO /* file I/O fails with PEMCIRCO? */
  CCOUNTER_START();
  FILE *file;
  unsigned char data[64];

  file = fopen("c:\\tmp\\test2.txt", "w");
  if (file!=NULL) {
    for(int i=0; i<10; i++) {
      (void)fwrite(file_data, sizeof(file_data), 1, file);
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
  puts("finished!\n");
}
#endif

void Benchmark_Run(void) {
  McuArmTools_FillMainStackSpace();
#if BENCHMARK_USE_STDLIB
  Benchmark_Stdlib();
#else
  BenchMark_McuLib();
#endif
  int32_t size = McuArmTools_GetUsedMainStackSpace();
#if BENCHMARK_USE_STDLIB
  printf("stack size: %ld\n", size);
#else
  McuSemihost_printf("stack size: %d\n", size);
  McuSemihost_StdIOFlush();
#endif
}

#endif /* BENCHMARK_DO_BENCHMARK */
