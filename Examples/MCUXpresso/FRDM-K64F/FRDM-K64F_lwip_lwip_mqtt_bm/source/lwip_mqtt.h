/*
 * lwip_mqtt_bm.h
 *
 *  Created on: 21.04.2017
 *      Author: Erich Styger Local
 */

#ifndef LWIP_MQTT_H_
#define LWIP_MQTT_H_

#include "netif.h"
#include "config.h"
#if CONFIG_USE_SHELL
  #include "CLS1.h"

  uint8_t MQTT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

typedef enum {
  APP_MQTT_MSG_CONNECT,
  APP_MQTT_MSG_PUBLISH,
  APP_MQTT_MSG_SUBSCRIBE,
  APP_MQTT_MSG_DISCONNECT,
} APP_MQTT_MSG_Type_t;

typedef struct {
  APP_MQTT_MSG_Type_t msgKind;
  union {
    struct {
      unsigned char *topic; /* MQTT topic */
      unsigned char *payload;  /* content of topic */
    } publish;
    struct {
      unsigned char *topic; /* MQTT topic */
    } subscribe;
  };
} APP_MQTT_Msg_t;

int APP_SendMsg(APP_MQTT_Msg_t *msg);

struct netif *APP_GetNetworkInterface(void);

#endif /* LWIP_MQTT_H_ */
