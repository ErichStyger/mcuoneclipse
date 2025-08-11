/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_


#ifndef MQTT_CLIENT_CONFIG_EXTRA_LOGS
  #define MQTT_CLIENT_CONFIG_EXTRA_LOGS   (0)
    /*!< set to 1 to produce extra log output */
#endif

#ifndef MQTT_CLIENT_CONFIG_HEADER_FILE
  #define MQTT_CLIENT_CONFIG_HEADER_FILE            "my_header.h"
#endif 

#ifndef MQTT_CLIENT_INCOMING_PUBLISH_CALLBACK
  #define MQTT_CLIENT_INCOMING_PUBLISH_CALLBACK     My_incoming_publish_cb
#endif

#ifndef MQTT_CLIENT_INCOMING_DATA_CALLBACK
  #define MQTT_CLIENT_INCOMING_DATA_CALLBACK        My_incoming_data_cb
#endif

#ifndef MQTT_CLIENT_CONNECTION_CALLBACK
  #define MQTT_CLIENT_CONNECTION_CALLBACK           My_connection_cb
#endif

#endif /* MQTT_CLIENT_CONFIG_H_ */
