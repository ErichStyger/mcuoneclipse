/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_UDP_SERVER_H_
#define SRC_UDP_SERVER_H_

void UdpServer_TaskSuspend(void);

void UdpServer_TaskResume(void);

void UdpServer_Init(void);

#endif /* SRC_UDP_SERVER_H_ */
