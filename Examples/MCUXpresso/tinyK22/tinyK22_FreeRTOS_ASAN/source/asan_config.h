/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef ASAN_CONFIG_H_
#define ASAN_CONFIG_H_

/* configuration for ASAN: define the memory area below */

#define APP_MEM_START 0x20000000 /* base RAM address */
#define APP_MEM_SIZE  0x10000  /* 64 kByte */
#define APP_MEM_END   (APP_MEM_START+APP_MEM_SIZE-1)

#endif /* ASAN_CONFIG_H_ */
