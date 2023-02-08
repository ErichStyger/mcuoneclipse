/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"

static void stdlib_test(void) {
  static const float f = 3.5f;
  static const double d = 7.25;
  char *buf;

  /* doing a few calls to the standard library for tests */
  printf("hello world!\n");
  printf("f: %f, d: %f\n", f, d);
  buf = malloc(64);
  if (buf!=NULL) {
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "hello!");
    printf("%s", buf);
    free(buf);
  }
  unsigned char ch;
  if (scanf("Enter a character: %c", &ch)==1) {
    printf("You entered %c\n", ch);
  }
}

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  stdlib_test();

  for(;;) {
  __asm volatile ("nop");
  }
  return 0 ;
}
