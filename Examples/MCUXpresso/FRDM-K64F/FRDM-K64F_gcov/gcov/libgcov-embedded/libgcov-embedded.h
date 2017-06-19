/*
 * coverage-support.h
 */

#ifndef COVERAGE_SUPPORT_H_
#define COVERAGE_SUPPORT_H_

#ifdef __cplusplus
 extern "C" {
#endif

void static_init(void);

void gcov_exit(void);

#ifdef __cplusplus
 }
#endif

#endif /* COVERAGE_SUPPORT_H_ */
