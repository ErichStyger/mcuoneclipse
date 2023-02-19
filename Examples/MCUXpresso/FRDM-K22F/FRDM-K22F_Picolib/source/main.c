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

void *McuArmTools_GetSP(void) {
#ifdef __GNUC__
  void *sp;

  __asm__ __volatile__ ("mrs %0, msp" : "=r"(sp));
  return sp;
#else
  #warning "only for GCC"
  return NULL;
#endif
}


#ifndef McuArmTools_CONFIG_STACK_CHECK_PATTERN
  #define McuArmTools_CONFIG_STACK_CHECK_PATTERN  (0xdeadbeef)
    /*!< Byte pattern on stack, to mark it is 'unused' */
#endif

/* The two symbols below shall be set by the linker script file to mark top and bottom of stack. Note that the two addresses need to be 32bit aligned! */
#ifndef McuArmTools_CONFIG_LINKER_SYMBOL_STACK_TOP
  #define McuArmTools_CONFIG_LINKER_SYMBOL_STACK_TOP  _vStackTop
#endif

#ifndef McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE
  #define McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE _vStackBase
#endif

/* on ARM Cortex, the stack grows from 'top' (higher address) to the 'bottom' (lower address) */
extern uint32_t McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE; /*!< base address of stack, this is a numerically lower address than the top */
extern uint32_t McuArmTools_CONFIG_LINKER_SYMBOL_STACK_TOP;  /*!< top or end of stack, at the top. Highest address. Stack is growing from base to top */

/*!
 * \brief Return the stack bottom, as configured in the linker file. The stack grows from the top (higher address) to the base (lower address).
 * \return Return the address of the top (last) stack unit
 */
uint32_t *McuArmTools_GetLinkerMainStackBase(void) {
  return &McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE;
}

/*!
 * \brief Return the stack top, as set in the linker file. The stack grows from the top (higher address) to the base (lower address).
 * \return Return the address of the top (last) stack unit
 */
uint32_t *McuArmTools_GetLinkerMainStackTop(void) {
  return &McuArmTools_CONFIG_LINKER_SYMBOL_STACK_TOP;
}

/*!
 * \brief Returns the size of the main (MSP) stack size, using linker symbols for top (higher address) and base (lower address).
 * \return Number of bytes allocated by the linker for the stack
 */
uint32_t McuArmTools_GetLinkerMainStackSize(void) {
  return (uint32_t)&McuArmTools_CONFIG_LINKER_SYMBOL_STACK_TOP - (uint32_t)&McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE;
}

/*!
 * \brief Fill the stack space with the checking pattern, up to the current MSP.
 */
void McuArmTools_FillMainStackSpace(void) {
  uint32_t *base = (uint32_t*)&McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE;
  uint32_t *msp = McuArmTools_GetSP(); /* get current MSP stack pointer */
  /* the current MSP is near the top */
  while(base<msp) { /* fill from the base to the top */
    *base = McuArmTools_CONFIG_STACK_CHECK_PATTERN;
    base++;
  }
}

/*!
 * \brief Calculates the unused stack space, based on the checking pattern.
 * \return Number of unused main stack space.
 */
uint32_t McuArmTools_GetUnusedMainStackSpace(void) {
  uint32_t unused = 0; /* number of unused bytes */
  uint32_t *p = (uint32_t*)&McuArmTools_CONFIG_LINKER_SYMBOL_STACK_BASE;

  /* check if the pattern stored on the stack has been changed */
  while (*p==McuArmTools_CONFIG_STACK_CHECK_PATTERN) {
    unused += sizeof(uint32_t); /* count number of unused bytes */
    p++;
  }
  return unused; /* return the number of unused bytes */
}

/*!
 * \brief Returns the used main stack space, based on the overwritten checking pattern.
 * \return Number of used main stack bytes
 */
uint32_t McuArmTools_GetUsedMainStackSpace(void) {
  return McuArmTools_GetLinkerMainStackSize()-McuArmTools_GetUnusedMainStackSpace();
}

int main(void) {
  McuArmTools_FillMainStackSpace();

  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  stdlib_test();

  printf("stack size used: %ld\n", McuArmTools_GetUsedMainStackSpace());

  for(;;) {
  __asm volatile ("nop");
  }
  return 0 ;
}
