/*
 * coverage_stubs.h
 *
 *  Created on: 26.12.2014
 *      Author: Erich Styger
 */

#ifndef COVERAGE_STUBS_H_
#define COVERAGE_STUBS_H_

#define COV_DO_COVERAGE   	0  	/* 1 to enable coverage, 0 to disable it */
#define COV_USE_NEWLIB_NANO 1 	/* 1: using newlib-nano, 0: using newlib */
#define COV_USE_SEMIHOSTING 1   /* 1: using semihosting, 0: no semihosting */
#define COV_DO_PROFILING    1   /* 1: generate profiling information */

#define PL_WRITE_COVERAGE_FILE  0
#define PL_WRITE_POFILE_FILE    1

void COV_static_init(void);

void _exit(int); /* exit function */

/* internal prototypes */
void gcov_exit(void); /* coverage exit function to write coverage file */

void monstartup (size_t lowpc, size_t highpc); /* profiling monitor startup */
void _mcleanup(void);

#endif /* COVERAGE_STUBS_H_ */
