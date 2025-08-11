/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MQTT_HEIDELBERG_H_
#define MQTT_HEIDELBERG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "mqtt_client.h"

typedef enum topic_ID_e { /* IDs for topics we can subscribe to */
  Topic_ID_None,
  Topic_ID_Solar_Power,       /* power from PV panels */
  Topic_ID_Site_Power,        /* power to the house/site */
  Topic_ID_Grid_Power,        /* power from/to grid */
  Topic_ID_Battery_Power,     /* power from/to battery */
  Topic_ID_Battery_Percentage,/* battery level percentage */
  Topic_ID_Charging_Power,    /* actual charging power */
} topic_ID_e;

int MqttHeidelberg_Publish_ChargingPower(uint32_t powerW);

void MqttHeidelberg_incoming_publish_cb(void *arg, const char *topic, uint32_t tot_len);

void MqttHeidelberg_incoming_data_cb(void *arg, const uint8_t *data, uint16_t len, uint8_t flags);

void MqttHeidelberg_connection_cb(mqtt_client_handle client, void *arg, int /*mqtt_connection_status_t*/ status);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MQTT_HEIDELBERG_H_ */
