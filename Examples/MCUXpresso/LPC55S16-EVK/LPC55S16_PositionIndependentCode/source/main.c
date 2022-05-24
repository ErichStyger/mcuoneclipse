/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S16.h"
#include "fsl_debug_console.h"
#include "module.h"
#include "myLib.h"
#include "myPic.h"

#if 0
int MyLib_Calc(int x) {
  glob++;
//   0: 4a03        ldr r2, [pc, #12] ; (10 <MyLib_Calc+0x10>)
//   2: 447a        add r2, pc
//   4: 6813        ldr r3, [r2, #0]
//   6: 3301        adds  r3, #1
//   8: 6013        str r3, [r2, #0]
  return x*2;
}
//   a: 0040        lsls  r0, r0, #1
//   c: 4770        bx  lr
//   e: bf00        nop
//  10: 0000000a  .word 0x0000000a
int MyLib_Mul2(int x) {
  return x*2;
}
// 838: 0040        lsls  r0, r0, #1
// 83a: 4770        bx  lr
void MyLib_Init(void) {
}
//  18: 4770        bx  lr
//  1a: bf00        nop

#else
static int16_t code[] = { /* this could would bet loaded by a loader e.g. into RAM */
// 0x0000:  int MyLib_Calc(int x) {
  0x4b03, //   0: 4a03        ldr r2, [pc, #12] ; (10 <MyLib_Calc+0x10>)
  0xf859, 0x2003, // ldr.w  r2, [r9, r3]
  0x6813, //   4: 6813        ldr r3, [r2, #0]
  0x3301, //   6: 3301        adds  r3, #1
  0x6013, //   8: 6013        str r3, [r2, #0]
  0x0040, //   lsls  r0, r0, #1
  0x4770, //       bx  lr
  0x0000, 0x0000, // .word 0x00000000: index into GOT table for address of variable 'glob'

// 0x0014:  int MyLib_Mul2(int x) {
  0x0040, //   a: 0040        lsls  r0, r0, #1
  0x4770, //   c: 4770        bx  lr

// 0x0018:  void MyLib_Init(void) {
  0x4770, //  18: 4770        bx  lr
  0xbf00  //  1a: bf00        nop
};
#endif

/*
 * The entries order below you can get from readelf from the final binary too:
 * Relocation section '.rel.dyn' at offset 0x10364 contains 3 entries:
 * Offset     Info    Type            Sym.Value  Sym. Name
 * 2000000c  00000116 R_ARM_JUMP_SLOT   00000000   MyLib_Init
 * 20000010  00000216 R_ARM_JUMP_SLOT   00000000   MyLib_Calc
 * 20000014  00000316 R_ARM_JUMP_SLOT   00000000   MyLib_Mul2
 */
typedef enum {
  GOT_PLT_INDEX_MyLib_glob=1,
  GOT_PLT_INDEX_MyLib_Init=3,
  GOT_PLT_INDEX_MyLib_Calc=4,
  GOT_PLT_INDEX_MyLib_Mul2=5,
} Got_Plt_Index_e;


/*! \brief
 * The information needed to perform the binding.
 * The offsets are the code offsets inside (Virtual address) from the beginning.
 * The got_plt index is used to identify the got PLT index.
 */
typedef struct {
  const char *name; /*!< name of function */
  size_t offset;    /*!< offset in loaded .code section */
  Got_Plt_Index_e got_plt_idx;  /*!< index in .got_plt table */
} binding_t;


static const binding_t code_bindings[] =
{ /* in this simple use case: the offsets are within the code[] array above */
    {"MyLib_Calc", 0x0000, GOT_PLT_INDEX_MyLib_Calc},
    {"MyLib_Mul2", 0x0014, GOT_PLT_INDEX_MyLib_Mul2},
    {"MyLib_Init", 0x0018, GOT_PLT_INDEX_MyLib_Init},
};

static const binding_t data_bindings[] = {
    {"MyLib glob", 0x0000, GOT_PLT_INDEX_MyLib_glob},
};

/* Force the counter to be placed into memory. */
volatile int i, j = 0 ;
void foobar(void) {}

extern unsigned int _sgot, _sgot_plt; /* symbols provided by the linker */

void BindLibrary(void *codeStart, void *dataStart) {
  /* code bindings */
  for(int i=0; i<sizeof(code_bindings)/sizeof(code_bindings[0]); i++) {
    ((uint32_t*)&_sgot_plt)[code_bindings[i].got_plt_idx] = (uint32_t)(codeStart+code_bindings[i].offset);
  }
  /* data bindings */
  for(int i=0; i<sizeof(data_bindings)/sizeof(data_bindings[0]); i++) {
    ((uint32_t*)&_sgot_plt)[data_bindings[i].got_plt_idx] = (uint32_t)(dataStart+data_bindings[i].offset);
  }
}

int main(void) {
  /* load lib into memory */
  /* bind methods of memory */
    BindLibrary((void*)code, (void*)&i); /* do the binding to the relocated code */

    //MyPic_Test();
    MyLib_Init();
    j = MyLib_Mul2(55);
    i = MyLib_Calc(30);
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++;
        j++;
        __asm volatile ("nop");
    }
    return 0 ;
}

