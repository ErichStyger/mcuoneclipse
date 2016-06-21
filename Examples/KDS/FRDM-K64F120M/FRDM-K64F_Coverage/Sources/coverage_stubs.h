/*
 * coverage_stubs.h
 *
 *  Created on: 26.12.2014
 *      Author: Erich Styger
 */

#ifndef COVERAGE_STUBS_H_
#define COVERAGE_STUBS_H_

#define DO_COVERAGE   	          1  	/* 1 to enable coverage, 0 to disable it */
#define USE_SEMIHOSTING_FILE_IO   1  /* full semihosting file I/O is supported with Segger, but not not with P&E! */
/* other linker flags/options:
 * without semihosting: -specs=nosys.specs -fprofile-arcs
 * with semihosting: -specs=rdimon.specs -fprofile-arcs
 * NOTE: it works with KDS V3.2.0 and newlib, but *not* with newlib-nano!
 */

void static_init(void);

void _exit(int);

#endif /* COVERAGE_STUBS_H_ */
