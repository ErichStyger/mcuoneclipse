/*
 * Copyright (c) 2019, 2020, 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_UDP_SERVER_H_
#define SRC_UDP_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define UDP_SERVER_PORT    (1234) /*!< default UDP server port */

/*! \brief Resume the UDP server */
void UdpServer_Resume(void);

/*! \brief stop the UDP server */
void UdpServer_Suspend(void);

/*! \brief Module initialization */
void UdpServer_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_UDP_SERVER_H_ */
