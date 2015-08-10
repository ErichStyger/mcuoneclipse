/*
 * profiler.S
 *
 *  Created on: 06.08.2015
 *      Author: tastyger
 */

    .syntax unified
    .arch armv7-m

.globl __gnu_mcount_nc
        .type __gnu_mcount_nc, %function
__gnu_mcount_nc:
#if 0 /* dummy version, doing nothing */
        mov    ip, lr
        pop    { lr }
        bx     ip
#else
   		push {r0, r1, r2, r3, lr}
		bic r1, lr, #1  /* R1 contains callee address, with thumb bit cleared */
		ldr r0, [sp, #20] /* R0 contains caller address */
		bic r0, r0, #1 /* clear thumb bit */
		bl _mcount_internal
		pop {r0, r1, r2, r3, ip, lr}
		bx ip
#endif

