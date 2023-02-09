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
  printf("Enter a character:\n");
  if (scanf("%c", &ch)==1) {
    printf("You entered %c\n", ch);
  }
}

extern uint32_t _vStackTop;
extern uint32_t _vStackBase;

static uint32_t getStackSize(void) {
  uint32_t base = (uint32_t)&_vStackBase;
  uint32_t top = (uint32_t)&_vStackTop;
  return top-base;
}

static void initStack(void) {
  uint32_t base = (uint32_t)&_vStackBase;
  uint32_t top = (uint32_t)&_vStackTop - 0x40; /* save offset from locals */
  memset((void*)base, 0xde, top-base);
}

static uint32_t stackUnused(void) {
  uint32_t unused = 0;
  char *p = (char*)&_vStackBase;

  while (*p==0xde) {
    p++;
    unused++;
  }
  return unused;
}

int main(void) {
  initStack();
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  stdlib_test();

  uint32_t used = getStackSize()-stackUnused();
  printf("stack size used: %ld\n", used);

  for(;;) {
  __asm volatile ("nop");
  }
  return 0 ;
}
