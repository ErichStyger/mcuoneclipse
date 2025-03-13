/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHELL_H_
#define SHELL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Module de-initialization
 */
void SHELL_Deinit(void);

/*!
 * \brief Module Initialization
 */
void SHELL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SHELL_H_ */
