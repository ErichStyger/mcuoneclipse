/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL   (1)  /* if using shell interface */
#define PL_CONFIG_USE_FILES   (1)  /* if using file I/O */

/*!
 * \brief Module initialization
 */
void PL_Init(void);


#endif /* PLATFORM_H_ */
