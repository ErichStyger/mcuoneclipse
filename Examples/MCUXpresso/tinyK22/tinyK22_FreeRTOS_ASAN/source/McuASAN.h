/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUASAN_H_
#define MCUASAN_H_

#include <stddef.h>

void __asan_free(void *p);
void *__asan_malloc(size_t size);
void __asan_init(void);

#endif /* MCUASAN_H_ */
