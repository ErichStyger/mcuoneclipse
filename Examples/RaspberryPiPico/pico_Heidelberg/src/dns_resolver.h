/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DNS_RESOLVER_H_
#define DNS_RESOLVER_H_

#include "lwip/ip_addr.h"
#include <stdbool.h>

typedef struct DnsResolver_info_t {
  bool dns_request_sent;      /* flag set after sending a DNS response. Reset if received a good answer */
  bool dns_response_received; /* flag to indicate in DNS callback that we have received a response */
  ip_addr_t resolved_addr;    /* here the resolved address gets stored */
} DnsResolver_info_t;

/*!
 * \brief resolves a name (IP or hostname) string to an address
 * \param name IP ("192.168.1.1") or hostname ("server")
 * \param info Pointer to data, which is used to store the address found. Does not need to be initialized, but has to global or memory always accessible, as dns callback can happen later.
 * \param timeoutMs timeout in milliseconds. Uses FreeRTOS delay
 * \return negative number in case of error, 0 otherwise
 */
int DnsResolver_ResolveName(const char *name, DnsResolver_info_t *info, int32_t timeoutMs);


/*!
 * \brief Module intitialization function. Marked as 'weak' so it can be overwritten by fff (fake functions framework) for testing
 */
__attribute__((weak)) void DnsResolver_Init(void);

#endif /* DNS_RESOLVER_H_ */
