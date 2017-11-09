/*
 * gcov_init.c
 *
 *  Created on: 16.06.2017
 *      Author: Erich Styger Local
 */

#include <gcov_init.h>
#include <stdint.h>

/* call the coverage initializers if not done by startup code */
void gcov_static_init(void) {
  void (**p)(void);
  extern uint32_t __init_array_start, __init_array_end; /* linker defined symbols, array of function pointers */
  uint32_t beg = (uint32_t)&__init_array_start;
  uint32_t end = (uint32_t)&__init_array_end;

  while(beg<end) {
    p = (void(**)(void))beg; /* get function pointer */
    (*p)(); /* call constructor */
    beg += sizeof(p); /* next pointer */
  }
}
