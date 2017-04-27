/*
 * app_dhcp.h
 *
 *  Created on: 26.04.2017
 *      Author: Erich Styger
 */

#ifndef APP_DHCP_H_
#define APP_DHCP_H_

#include "config.h"
#include "netif.h"
#if CONFIG_USE_SHELL
  #include "CLS1.h"

  uint8_t DHCP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

u8_t DHCP_GetState(struct netif *netifp);

bool DHCP_IsBound(struct netif *netifp);

void DHCP_Start(struct netif *netifp);
void DHCP_Init(void);

#endif /* APP_DHCP_H_ */
