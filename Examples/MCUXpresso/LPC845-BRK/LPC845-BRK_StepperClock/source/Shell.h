/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHELL_H_
#define SHELL_H_

void SHELL_SendString(unsigned char *str);
void SHELL_SendChar(unsigned char ch);

void SHELL_Init(void);
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
