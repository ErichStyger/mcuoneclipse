/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_

/* benchmark settings */
#define BENCHMARK_USE_STDLIB   (0) /* if using the standard library or McuLib for the benchmarking */
#define BENCHMARK_USE_FILE_IO  (1) /* if using file I/O operations */

void Benchmark_Run(void);

#endif /* BENCHMARK_H_ */
