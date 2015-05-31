/*
 * coverage_stubs.h
 *
 *  Created on: 26.12.2014
 *      Author: Erich Styger
 */

#ifndef COVERAGE_STUBS_H_
#define COVERAGE_STUBS_H_

#define DO_COVERAGE   	1  	/* 1 to enable coverage, 0 to disable it */
#define USE_NEWLIB_NANO 0 	/* 1: using newlib-nano, 0: using newlib */

void static_init(void);

void _exit(int);


#endif /* COVERAGE_STUBS_H_ */
