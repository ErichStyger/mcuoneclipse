/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DNS_RESOLVER_H_
#define DNS_RESOLVER_H_

#include "lwip/ip_addr.h"

/*!
 * \brief resolves a name (IP or hostname) string to an address
 * \param name IP ("192.168.1.1") or hostname ("server")
 * \param addr Where to store the IP address resolved
 * \param timeoutMs timeout in milliseconds. Uses FreeRTOS delay
 * \return negative number in case of error, 0 otherwise
 */
int DnsResolver_ResolveName(const char *name, ip_addr_t *addr, int32_t timeoutMs);

#endif /* DNS_RESOLVER_H_ */
