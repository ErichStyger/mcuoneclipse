/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_MQTT_CLIENT

#include "lwip/apps/mqtt.h"
#include "McuLog.h"

#if LWIP_TCP

static mqtt_client_t* mqtt_client;

static const struct mqtt_connect_client_info_t mqtt_client_info =
{
  "pico",
  "homeassistant", /* user */
  "mooM1Eik6uh9maepai6ia2pahw2xaiM3Oaril6ahrug7ihejae6eith9uec6sahc", /* pass */
  100,  /* keep alive */
  NULL, /* will_topic */
  NULL, /* will_msg */
  0,    /* will_qos */
  0     /* will_retain */
#if LWIP_ALTCP && LWIP_ALTCP_TLS
  , NULL
#endif
};

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
  const struct mqtt_connect_client_info_t* client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(data);

  McuLog_trace("MQTT client \"%s\" data cb: len %d, flags %d", client_info->client_id, (int)len, (int)flags);
}

static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  const struct mqtt_connect_client_info_t* client_info = (const struct mqtt_connect_client_info_t*)arg;

  McuLog_trace("MQTT client \"%s\" publish cb: topic %s, len %d", client_info->client_id, topic, (int)tot_len);
}

static void mqtt_request_cb(void *arg, err_t err) {
  const struct mqtt_connect_client_info_t* client_info = (const struct mqtt_connect_client_info_t*)arg;

  McuLog_trace("MQTT client \"%s\" request cb: err %d", client_info->client_id, (int)err);
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  const struct mqtt_connect_client_info_t* client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(client);

  McuLog_trace("MQTT client \"%s\" connection cb: status %d", client_info->client_id, (int)status);

  if (status == MQTT_CONNECT_ACCEPTED) {
    McuLog_trace("MQTT connect accepted");
#if 0
    mqtt_sub_unsub(client,
            "homeassistant/sensor/powerwall_site_now", 1,
            mqtt_request_cb, LWIP_CONST_CAST(void*, client_info),
            1);
#endif
    mqtt_sub_unsub(client,
            "PW2_Solar", 0,
            mqtt_request_cb, LWIP_CONST_CAST(void*, client_info),
            1);
  } else if (status==MQTT_CONNECT_DISCONNECTED) {
    McuLog_trace("MQTT connect disconnect");
  }
}
#endif /* LWIP_TCP */


static ip_addr_t mqttServerAddr;

void MqttClient_Connect(void) {
#if LWIP_TCP
  mqtt_client = mqtt_client_new();

  ip4_addr_set_u32(&mqttServerAddr, ipaddr_addr("192.168.1.10"));
  mqtt_set_inpub_callback(mqtt_client,
          mqtt_incoming_publish_cb,
          mqtt_incoming_data_cb,
          LWIP_CONST_CAST(void*, &mqtt_client_info));

  mqtt_client_connect(mqtt_client,
          &mqttServerAddr, MQTT_PORT,
          mqtt_connection_cb, LWIP_CONST_CAST(void*, &mqtt_client_info),
          &mqtt_client_info);
#endif /* LWIP_TCP */
}

void MqttClient_Init(void) {
  /* nothing needed */
}

#endif /* PL_CONFIG_USE_MQTT_CLIENT */
