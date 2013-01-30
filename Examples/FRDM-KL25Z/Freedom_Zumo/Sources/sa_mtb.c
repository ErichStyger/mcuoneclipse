/*
 * sa_mtb.c
 *
 *  Contains the definition of the buffer used for allocating SRAM space for the MTB trace.
 */

#if (defined(__SA_MTB_SIZE) && (__SA_MTB_SIZE > 0))
/* 
 * MTB (Micro Trace Buffer) is using its own section name, which is used in the linker script.
 */
 
#define SA_MTB_ALIGNEMENT  64  /* alignment of the MTB buffer */
unsigned char __attribute__((section (".mtb_buf"))) mtb_buf[__SA_MTB_SIZE] __attribute__ ((aligned (SA_MTB_ALIGNEMENT)));

#endif  /* __SA_MTB_SIZE */
