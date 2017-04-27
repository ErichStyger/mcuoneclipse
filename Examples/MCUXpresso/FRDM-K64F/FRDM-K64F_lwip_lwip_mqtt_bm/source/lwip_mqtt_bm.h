/*
 * lwip_mqtt_bm.h
 *
 *  Created on: 21.04.2017
 *      Author: Erich Styger Local
 */

#ifndef LWIP_MQTT_BM_H_
#define LWIP_MQTT_BM_H_

#include "netif.h"
#include "config.h"
#if CONFIG_USE_SHELL
  #include "CLS1.h"

  uint8_t MQTT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

struct netif *APP_GetNetworkInterface(void);

#endif /* LWIP_MQTT_BM_H_ */
