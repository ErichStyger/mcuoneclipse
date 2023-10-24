/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"
#include <stdio.h>
#include "application.h"
#include "McuSemihost.h"

static void semihost_file_test(void) {
  FILE *file;

  McuSemihost_WriteString((unsigned char*)"testing file I/O with semihosting\n");
  file = fopen ("test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
  } else {
    McuSemihost_WriteString((unsigned char*)"failed fopen\n");
  }
}

int main(void) {
  PL_Init();
  printf("hello world with semihosting!\n");
  semihost_file_test();
  vTaskStartScheduler();
  return 0;
}
