/*
 * coverage-support.h
 */

#ifndef COVERAGE_SUPPORT_H_
#define COVERAGE_SUPPORT_H_

#ifdef __cplusplus
 extern "C" {
#endif

 /* write data to file, from bufStart to bufEnd (not including) */
void gcov_writeDataHook(unsigned char* bufStart, unsigned char* bufEnd, const char *fileName);

void static_init(void);

void gcov_exit(void);

#ifdef __cplusplus
 }
#endif

#endif /* COVERAGE_SUPPORT_H_ */
