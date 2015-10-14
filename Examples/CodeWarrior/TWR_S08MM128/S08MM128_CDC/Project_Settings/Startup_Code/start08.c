/******************************************************************************
  FILE        : start08.c
  PURPOSE     : 68HC08 standard startup code
  LANGUAGE    : ANSI-C / INLINE ASSEMBLER
  ----------------------------------------------------------------------------
  HISTORY
    22 oct 93         Created.
    04/17/97          Also C++ constructors called in Init().
 ******************************************************************************/

/**********************************************************************/
/* NOTE:                                                              */
/* This version of the startup code assumes that main                 */
/* does never return (saving the 2 byte return address of _Startup on */
/* the stack).                                                        */
/**********************************************************************/

#define __NO_FLAGS_OFFSET   /* we do not need the flags field in the startup data descriptor */
#define __NO_MAIN_OFFSET    /* we do not need the main field in the startup data descriptor */

#include <start08.h>

#ifdef __cplusplus
#define __EXTERN_C  extern "C"
#else
#define __EXTERN_C
#endif

/*lint -esym(752, main) main is used in HLI */
__EXTERN_C extern void main(void); /* prototype of main function */

/*lint -e961 -e537 -e451 non_bank.sgm is not a regular header file - it contains a CODE_SEG pragma only */
#include "non_bank.sgm"
/*lint +e961 +e537 +e451 */

/***************************************************************************/
/* Macros to control how the startup code handles the COP:                 */
/* #define _DO_FEED_COP_   : do feed the COP                               */
/* Without defining any of these, the startup code does NOT handle the COP */
/***************************************************************************/
/* __ONLY_INIT_SP define:                                                  */
/* This define selects an shorter version of the startup code              */
/* which only loads the stack pointer and directly afterwards calls        */
/* main. This version does however NOT initialize global variables         */
/* (so this version is not ANSI compliant!).                               */
/***************************************************************************/

/*lint -esym(750, __FEED_COP_IN_HLI) '__FEED_COP_IN_HLI' is used in HLI */
/*lint -e961 the macro cannot be replaced by a function */
#if defined(_DO_FEED_COP_)
#define __FEED_COP_IN_HLI()  } _FEED_COP(); asm {
#else
#define __FEED_COP_IN_HLI() /* do nothing */
#endif
/*lint +e961 */

#ifndef __ONLY_INIT_SP

#pragma DATA_SEG FAR _STARTUP
struct _tagStartup _startupData;    /* read-only:
                                     _startupData is allocated in ROM and
                                     initialized by the linker */

#pragma MESSAGE DISABLE C20001 /* Warning C20001: Different value of stackpointer depending on control-flow */
/* the function _COPY_L releases some bytes from the stack internally */

#if defined(__OPTIMIZE_FOR_SIZE__) || defined(_DO_FEED_COP_)
#pragma NO_ENTRY
#pragma NO_EXIT
#pragma NO_FRAME
/*lint -esym(528, loadByte) inhibit warning about unreferenced loadByte function */
static void near loadByte(void) {
  asm {
             PSHH
             PSHX
#ifdef __HCS08__
             LDHX    5,SP
             LDA     0,X
             AIX     #1
             STHX    5,SP
#else
             LDA     5,SP
             PSHA
             LDX     7,SP
             PULH
             LDA     0,X
             AIX     #1
             STX     6,SP
             PSHH
             PULX
             STX     5,SP
#endif
             PULX
             PULH
             RTS
  }
}
#endif /* defined(__OPTIMIZE_FOR_SIZE__) || defined(_DO_FEED_COP_) */


#ifdef __cplusplus
static void Call_Constructors(void) {
  int i;
#ifdef __ELF_OBJECT_FILE_FORMAT__
  i = (int)(_startupData.nofInitBodies - 1);
  while (i >= 0) {
    (&_startupData.initBodies->initFunc)[i]();  /* call C++ constructors */
    i--;
  }
#else /* __ELF_OBJECT_FILE_FORMAT__ */
  /* HIWARE object file format */
  if (_startupData.mInits != NULL) {
    _PFunc *fktPtr;
    fktPtr = _startupData.mInits;
    while(*fktPtr != NULL) {
      (**fktPtr)(); /* call constructor */
      fktPtr++;
    }
  }
#endif /* __ELF_OBJECT_FILE_FORMAT__ */
}
#endif

/*lint -esym(752,_COPY_L)  inhibit message on function declared, but not used (it is used in HLI) */
__EXTERN_C extern void _COPY_L(void);
/* DESC:    copy very large structures (>= 256 bytes) in 16-bit address space (stack incl.)
   IN:      TOS count, TOS(2) @dest, H:X @src
   OUT:
   WRITTEN: X,H */
/*lint -esym(750, toCopyDownBegOffs) toCopyDownBegOffs is used in HLI */
#ifdef __ELF_OBJECT_FILE_FORMAT__
	#define toCopyDownBegOffs 0
#else
	#define toCopyDownBegOffs 2 /* for the hiware format, the toCopyDownBeg field is a long. Because the HC08 is big endian, we have to use an offset of 2 */
#endif
static void Init(void) {
/* purpose:     1) zero out RAM-areas where data is allocated
                2) init run-time data
                3) copy initialization data from ROM to RAM
 */
  /*lint -esym(529,p,i)  inhibit warning about symbols not used: it is used in HLI below */
  int i;
  int *far p;   /*lint !e625 accept unusual type modifier */

  asm {
ZeroOut:
             LDA    _startupData.nofZeroOuts:1 ; /* nofZeroOuts */
             INCA
             STA    i:1                        ; /* i is counter for number of zero outs */
             LDA    _startupData.nofZeroOuts:0 ; /* nofZeroOuts */
             INCA
             STA    i:0
             LDHX   _startupData.pZeroOut      ; /* *pZeroOut */
             BRA    Zero_5
Zero_3:
             ; /* CLR    i:1 is already 0 */
Zero_4:
             ; /* { HX == _pZeroOut } */
             PSHX
             PSHH
             ; /* { nof bytes in (int)2,X } */
             ; /* { address in (int)0,X   } */
             LDA    0,X
             PSHA
             LDA    2,X
             INCA
             STA    p                 ; /* p:0 is used for high byte of byte counter */
             LDA    3,X
             LDX    1,X
             PULH
             INCA
             BRA    Zero_0
Zero_1:
           ;  /* CLRA   A is already 0, so we do not have to clear it */
Zero_2:
             CLR    0,X
             AIX    #1
             __FEED_COP_IN_HLI()     	; /* it's necessary to feed the COP in the inner loop for the fast COP timeout of some derivatives */
Zero_0:
             DBNZA  Zero_2
Zero_6:
             DBNZ   p, Zero_1
             PULH
             PULX                     ; /* restore *pZeroOut */
             AIX    #4                ; /* advance *pZeroOut */
Zero_5:
             DBNZ   i:1, Zero_4
             DBNZ   i:0, Zero_3

CopyDown:

  }
  
  /* copy down */
  /* _startupData.toCopyDownBeg  --->  {nof(16) dstAddr(16) {bytes(8)}^nof} Zero(16) */
#if defined(__OPTIMIZE_FOR_SIZE__) || defined(_DO_FEED_COP_) /* for now: only -os version supports _DO_FEED_COP_ */
  asm {
#ifdef __HCS08__
             LDHX   _startupData.toCopyDownBeg:toCopyDownBegOffs
             PSHX
             PSHH
#else
             LDA    _startupData.toCopyDownBeg:(1+toCopyDownBegOffs)
             PSHA
             LDA    _startupData.toCopyDownBeg:(0+toCopyDownBegOffs)
             PSHA
#endif
Loop0:
             JSR    loadByte          ; /* load high byte counter */
             TAX                      ; /* save for compare */
             INCA
             STA    i
             JSR    loadByte          ; /* load low byte counter */
             INCA
             STA    i:1
             DECA
             BNE    notfinished
             CBEQX  #0, finished
notfinished:

             JSR    loadByte          ; /* load high byte ptr */
             PSHA
             PULH
             JSR    loadByte          ; /* load low byte ptr */
             TAX                      ; /* HX is now destination pointer */
             BRA    Loop1
Loop3:
Loop2:
             __FEED_COP_IN_HLI()
             JSR    loadByte          ; /* load data byte */
             STA    0,X
             AIX    #1
Loop1:
             DBNZ   i:1, Loop2
             DBNZ   i:0, Loop3
             BRA    Loop0

finished:
             AIS #2
    }
#else /*defined(__OPTIMIZE_FOR_SIZE__) || defined(_DO_FEED_COP_) */
  /* time optimized asm version. */
  asm {
#ifdef __HCS08__
             LDHX   _startupData.toCopyDownBeg:toCopyDownBegOffs
#else
             LDX    _startupData.toCopyDownBeg:(0+toCopyDownBegOffs)
             PSHX
             PULH
             LDX    _startupData.toCopyDownBeg:(1+toCopyDownBegOffs)
#endif
next:
             LDA   0,X                ; /* list is terminated by 2 zero bytes */
             ORA   1,X
             BEQ   copydone
             PSHX                     ; /* store current position */
             PSHH
             LDA   3,X                ; /* psh dest low */
             PSHA
             LDA   2,X                ; /* psh dest high */
             PSHA
             LDA   1,X                ; /* psh cnt low */
             PSHA
             LDA   0,X                ; /* psh cnt high */
             PSHA
             AIX   #4
             JSR   _COPY_L            ; /* copy one block */
             PULH
             PULX
             TXA
             ADD   1,X                ; /* add low */
             PSHA
             PSHH
             PULA
             ADC   0,X                ; /* add high */
             PSHA
             PULH
             PULX
             AIX   #4
             BRA next
copydone:
  }
#endif /* defined(__OPTIMIZE_FOR_SIZE__) || defined(_DO_FEED_COP_) */

  /* FuncInits: for C++, this are the global constructors */
#ifdef __cplusplus
  Call_Constructors();
#endif /* __cplusplus */

  /* implement ROM libraries initialization here (see startup.c) */
}
#endif /* __ONLY_INIT_SP */


#pragma NO_EXIT
__EXTERN_C void _Startup(void) {
/* set the reset vector to _Startup in the linker parameter file (*.prm):
    'VECTOR 0 _Startup'

    purpose:    1)  initialize the stack
                2)  initialize run-time, ...
                    initialize the RAM, copy down init data, etc (Init)
                3)  call main;
    called from: _PRESTART-code generated by the Linker
*/
  INIT_SP_FROM_STARTUP_DESC(); /*lint !e960 MISRA 14.3 REQ, not a null statement (instead: several HLI statements) */
  
#ifndef  __ONLY_INIT_SP
  Init(); /*lint !e522 function 'Init' contains inline assembly */
#endif
#ifndef __BANKED__
  __asm JMP main;  /* with a C style main(); we would push the return address on the stack wasting 2 RAM bytes */
#else
  __asm CALL main;
#endif
}
/*lint --e{766} non_bank.sgm is not a regular header file - it contains a CODE_SEG pragma only */
