/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUASAN_H_
#define MCUASAN_H_

#include <stddef.h>
#include "McuASANconfig.h"

#if McuASAN_CONFIG_IS_ENABLED && McuASAN_CONFIG_CHECK_MALLOC_FREE
  /* replace malloc and free calls */
  #define malloc   __asan_malloc
  #define free     __asan_free
#endif

/*! \brief
 * Allocate a memory block
 */
void *__asan_malloc(size_t size);

/*!
 * \brief
 * Free a memory block
 */
void __asan_free(void *p);

/*! \brief
 * Call the init function first to initialize the module.
 */
void McuASAN_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* MCUASAN_H_ */
