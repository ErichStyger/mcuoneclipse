/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

void TcpServer_TaskSuspend(void);

void TcpServer_TaskResume(void);

void TcpServer_Init(void);

#endif /* TCP_SERVER_H_ */
