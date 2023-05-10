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

/*! \brief start the UDP server */
void UDP_Server_Start(void);

/*! \brief stop the UDP server */
void UDP_Server_Stop(void);

/*! \brief Module initialization */
void UDP_Server_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_UDP_SERVER_H_ */
