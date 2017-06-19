readme.txt
----------

in Vectors_Config.h, use
#define VECTOR_SP_MAIN    &_vStackTop                            /* 0x00 -    ivINT_Initial_Stack_Pointer    used by PE */
#define VECTOR_1          (tIsrFunc)&ResetISR            /* 0x01 -    ivINT_Initial_Program_Counter  used by PE */

instead of:
#define VECTOR_SP_MAIN    &__SP_INIT                            /* 0x00 -    ivINT_Initial_Stack_Pointer    used by PE */
#define VECTOR_1          (tIsrFunc)&__thumb_startup            /* 0x01 -    ivINT_Initial_Program_Counter  used by PE */


and add
#if 1
extern void _vStackTop(void);
extern void ResetISR(void);
#endif
