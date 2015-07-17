/*
 * wrapper.h
 *
 *  Created on: 16.07.2015
 *      Author: tastyger
 */

#ifndef SOURCES_WRAPPER_H_
#define SOURCES_WRAPPER_H_

#include <stdint.h>

// #ifdef __RTX

typedef uint32_t BOOL;
typedef uint8_t U8;
typedef uint16_t U16;
typedef int16_t S16;
typedef uint32_t U32;
typedef uint64_t U64;

#define __packed /* !!! */ /* << EST */
#define __task   /* !!! */
#define OS_TID  int
#define __weak /* */
#define __FALSE  0
#define __TRUE   1
#define __nop()  __asm volatile ("nop\n")
#define __inline /* */

#endif /* SOURCES_WRAPPER_H_ */
