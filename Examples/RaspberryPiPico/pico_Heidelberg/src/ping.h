#ifndef LWIP_PING_H
#define LWIP_PING_H

#include "lwip/ip_addr.h"

/**
 * PING_USE_SOCKETS: Set to 1 to use sockets, otherwise the raw api is used
 */
#ifndef PING_USE_SOCKETS
  #define PING_USE_SOCKETS    LWIP_SOCKET
#endif

void Ping_InitAddress(const ip_addr_t* ping_addr);

#if !PING_USE_SOCKETS
  void Ping_SendNow(void);
#endif /* !PING_USE_SOCKETS */

void Ping_Init(void);

#endif /* LWIP_PING_H */
