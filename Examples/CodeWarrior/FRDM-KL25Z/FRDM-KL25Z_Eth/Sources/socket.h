/**
 * \file
 * \brief Socket interface for the W5100.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module is the interface to the sockets of the W5100 chip.
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stddef.h> /* for size_t */
#include "PE_Types.h"

/*!
 * \brief Opens a socket
 * \param sock
 * \param eth_protocol Ethernet protocol for the socket (W5100_SKT_MR_TCP, UPD, PPPOE, ...)
 * \param tcp_port TCP port to be used (typically 80 for HTTP)
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_OpenSocket(uint8_t sock, uint8_t eth_protocol, uint16_t tcp_port);

/*!
 * \brief Starts listening on the socket.
 * \param sock Socket number, 0..W5100_NUM_SOCKETS.
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_Listen(uint8_t sock);

/*!
 * \brief Returns the socket status
 * \param sock Socket number, 0..W5100_NUM_SOCKETS.
 * \param status Pointer to where to store the status.
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_GetStatus(uint8_t sock, uint8_t *status);

/*!
 * \brief Returns the received data size in the socket.
 * \param sock Socket number, 0..W5100_NUM_SOCKETS.
 * \param rxSize Pointer to where to store the amount bytes in socket.
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_ReceivedSize(uint8_t sock, uint16_t *rxSize);

/*!
 * \brief Receive data from a socket
 * \param sock Socket number, 0..W5100_NUM_SOCKETS
 * \param buf Pointer to buffer with data
 * \param bufSize Size of buf in bytes
 * \param readLen Size of data to read in bytes
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_Receive(uint8_t sock, uint8_t *buf, size_t bufSize, size_t readLen);

/*!
 * \brief Send data to a socket
 * \param sock Socket number, 0..W5100_NUM_SOCKETS
 * \param buf Pointer to buffer with data
 * \param bufLen Size of data in bytes
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_Send(uint8_t sock, const uint8_t *buf, size_t buflen);

/*!
 * \brief Disconnects a socket
 * \param sock Socket number, 0..W5100_NUM_SOCKETS
 * \return Error code, ERR_OK for success
 */
uint8_t SOCK_Disconnect(uint8_t sock);

/*!
 * \brief Close a socket
 * \param sock Socket number, 0..W5100_NUM_SOCKETS
 */
uint8_t SOCK_CloseSocket(uint8_t sock);

/*!
 * \brief Driver initialization.
 */
void SOCK_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void SOCK_Deinit(void);

#endif /* SOCKET_H_ */
